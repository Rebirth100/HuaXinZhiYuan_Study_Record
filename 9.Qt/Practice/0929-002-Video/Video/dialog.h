#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVideoWidget>
#include <QMediaPlayer>

class MyVideoWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

protected:
    //void keyPressEvent(QKeyEvent* event) override;

private slots:
    void on_pushButton_play_clicked();

    void on_pushButton_full_screen_clicked();

private:
    Ui::Dialog *ui;
    QMediaPlayer* player_ = nullptr;
    MyVideoWidget* video_widget_ = nullptr;
};
#endif // DIALOG_H
