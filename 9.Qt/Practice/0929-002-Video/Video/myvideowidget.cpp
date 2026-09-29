#include "myvideowidget.h"

#include <QKeyEvent>

MyVideoWidget::MyVideoWidget(QWidget *parent)
    : QVideoWidget{parent}
{}

void MyVideoWidget::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "MyVideoWidget::keyPressEvent";

    if (event->key() == Qt::Key_Escape
     || event->key() == Qt::Key_Space)
    {
        setFullScreen(false);
    }
}