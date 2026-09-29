#include "dialog.h"
#include "ui_dialog.h"
#include <QMediaPlayer>
#include <QAudioOutput>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    player_ = new QMediaPlayer;
    connect(player_,&QMediaPlayer::positionChanged,
            [this](qint64 position)
            {
                qDebug()<<"duration="<<player_->duration();
                qDebug()<<"position="<<position;
                ui->horizontalSlider->setSliderPosition(position*100.0f/player_->duration());
                qDebug()<<"Slider max="<<ui->horizontalSlider->maximum();

            });
    player_->setSource(QUrl("不谓侠.mp3"));
    QAudioOutput* output=new QAudioOutput;
    player_->setAudioOutput(output);

    ui->pushButton_play->setEnabled(true);
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);

    connect(ui->horizontalSlider,&QSlider::valueChanged,
            [this](int value)
            {
                qDebug()<<"value="<<value;
                player_->setPosition()
            });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_play_clicked()
{
    if(player_)
    {
        player_->play();
    }

    ui->pushButton_play->setEnabled(false);
    ui->pushButton_pause->setEnabled(true);
    ui->pushButton_stop->setEnabled(true);
}


void Dialog::on_pushButton_pause_clicked()
{
    if(player_)
    {
        player_->pause();
    }

    ui->pushButton_play->setEnabled(true);
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
}



void Dialog::on_pushButton_stop_clicked()
{
    if(player_)
    {
        player_->stop();
    }

    ui->pushButton_play->setEnabled(true);
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
}





void Dialog::on_pushButton_loop_clicked()
{
    if(ui->pushButton_loop->text().compare("单次")==0)
    {
        player_->setLoops(QMediaPlayer::Once);
        ui->pushButton_loop->setText("循环");
    }
    else if (ui->pushButton_loop->text().compare("循环")==0)
    {
        player_->setLoops(QMediaPlayer::Infinite);
        ui->pushButton_loop->setText("单次");
    }
}

