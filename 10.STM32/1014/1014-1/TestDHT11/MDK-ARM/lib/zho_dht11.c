#include "main.h"
#include "zho_util.h"
#include "zho_delay.h"

#include "zho_dht11.h"

#if USING_DHT11_DEBUG
#include <stdio.h>
#endif

static GPIO_TypeDef *dht11_port = NULL;
static uint16_t dht11_pin;

static void set_dht11_outpp(void);
static void set_dht11_inf(void);
static void write_dht11_data(uint8_t data);
static uint8_t read_dht11_data(void);
static boolean get_dht11_bit(uint8_t *bit);

void init_zho_dht11(GPIO_TypeDef *port, uint16_t pin) {
	dht11_port = port;
	dht11_pin = pin;
	
	set_dht11_outpp();
	write_dht11_data(HIGH);
	zho_delay_ms(1000);
}

boolean get_dht11_humidity_temperature(uint16_t *humi, float *temp) {
	if (!is_dht11_exist())	return FALSE;
	
	uint16_t index;
	uint8_t bit_value;
	uint8_t values[5] = {0};
	uint8_t value = 0;
	uint16_t bit_index = 0;
	uint16_t value_index = 0;
	
	for (index = 0; index < 40; index++) {
		if (!get_dht11_bit(&bit_value)) return FALSE;
		
		value <<= 1;
		value |= bit_value;
		
		if (++bit_index >= 8) {
			values[value_index++] = value;
			value = bit_index = 0;
		}
	}
	
#if USING_DHT11_DEBUG
	printf("%02X %02X %02X %02X %02X", 
			values[0], values[1], values[2], values[3], values[4]);
#endif
	
	if (values[0] + values[1] + values[2] + values[3] != values[4])	return FALSE;
	
	*humi = values[0];
	*temp = (float) values[2] + (float) (values[3] * 0.1);
	
	return TRUE;
}

boolean is_dht11_exist(void) {
	uint16_t count = 0;
	
	set_dht11_outpp();
	write_dht11_data(HIGH);
	
	write_dht11_data(LOW);
	zho_delay_ms(20);
	set_dht11_inf();
	
	while (read_dht11_data() == LOW && ++count < 200) {
		zho_delay_us(1);
	}
	if (count >= 200) return FALSE;
	
	count = 0;
	while (read_dht11_data() == HIGH && ++count < 200) {
		zho_delay_us(1);
	}
	if (count >= 200) return FALSE;
	
	count = 0;
	while (read_dht11_data() == LOW && ++count < 200) {
		zho_delay_us(1);
	}
	if (count >= 200) return FALSE;
	
	count = 0;
	while (read_dht11_data() == HIGH && ++count < 200) {
		zho_delay_us(1);
	}
	
	return count < 200;
}

static boolean get_dht11_bit(uint8_t *bit) {
	uint16_t count = 0;
	
	while (read_dht11_data() == LOW && ++count < 200) {
		zho_delay_us(1);
	}
	if (count >= 200) return FALSE;
	
	zho_delay_us(45);
	
	*bit = read_dht11_data();
	
	count = 0;
	while (read_dht11_data() == HIGH && ++count < 200) {
		zho_delay_us(1);
	}
	
	return count < 200;
}

static uint8_t read_dht11_data(void) {
	return HAL_GPIO_ReadPin(dht11_port, dht11_pin);
}

static void write_dht11_data(uint8_t data) {
	HAL_GPIO_WritePin(dht11_port, dht11_pin, data ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static void set_dht11_inf(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = dht11_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(dht11_port, &GPIO_InitStruct);
}

static void set_dht11_outpp(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = dht11_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(dht11_port, &GPIO_InitStruct);
}
