#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QThread>
#include <mythread.h>
class MyThread;
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

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_singal_clicked();

    void MyThreadStop();

private:
    Ui::Dialog *ui;
    MyThread* thread_ = nullptr;
signals:
    void MySignal();//自定义信号
};
#endif // DIALOG_H
