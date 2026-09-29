#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
protected:
    void run() override;
public slots:
    void MySlot();//槽函数

signals:
};

#endif // MYTHREAD_H
