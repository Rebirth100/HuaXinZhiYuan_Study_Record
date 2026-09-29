#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "myvideowidget.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    player_ = new QMediaPlayer;
    QAudioOutput* audio_output = new QAudioOutput;
    player_->setAudioOutput(audio_output);
    video_widget_ = new MyVideoWidget(this);
    player_->setVideoOutput(video_widget_);

    QHBoxLayout* hLayout_1 = new QHBoxLayout;
    hLayout_1->addStretch();
    hLayout_1->addWidget(ui->pushButton_play);
    hLayout_1->addStretch();
    hLayout_1->addWidget(ui->pushButton_full_screen);
    hLayout_1->addStretch();
    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(video_widget_);
    vLayout->addLayout(hLayout_1);
    setLayout(vLayout);

    player_->setSource(QUrl("Syn4FingerFlick.wmv"));
}

Dialog::~Dialog()
{
    delete ui;
}

/*
void Dialog::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "keyPressEvent";

    if (event->key() == Qt::Key_Escape
     || event->key() == Qt::Key_Space)
    {
        if (video_widget_)
        {
            video_widget_->setFullScreen(false);
        }
    }
}*/

void Dialog::on_pushButton_play_clicked()
{
    if (player_)
    {
        player_->play();
    }
}


void Dialog::on_pushButton_full_screen_clicked()
{
    if (video_widget_)
    {
        video_widget_->setFullScreen(true);
    }
}

