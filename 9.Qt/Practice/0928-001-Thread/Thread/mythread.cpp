#include "mythread.h"
#include <QDebug>
MyThread::MyThread(QObject *parent)
    : QThread{parent}
{
    /*
       （1）执行位置：thread_ = new MyThread;在 Dialog构造里面new对象。
       （2）MyThread 构造函数执行在主线程！
       > 只是 new 一个 QThread 派生对象，此时子线程还没有start()，操作系统子线程根本不存在。
       > 对象thread_归属主线程（thread_->thread() == 主线程）。
    */
    qDebug() << "Dialog MySignal threadId=" << QThread::currentThreadId();
}
void MyThread::run()
{
    //while(true)
    {
        /*
          （1）调用thread_->start()之后，操作系统开启真正子线程，进入run函数。
          （2）线程：子线程（新 OS 线程 ID，和主线程 ID 不一样）。
          （3）sleep(1); exec(); 全部运行在这个子线程；exec()是子线程的事件循环，阻塞在这里等待事件。
        */
        qDebug() << "MyThread run threadId=" << QThread::currentThreadId();
        static int count =0;
        qDebug() << "mythread count =" << count++;
        sleep(1);
        exec();
        //quit();
        //exit();
        //terminate();
        qDebug() << "Run finish";
    }
}

void MyThread::MySlot()
{
    qDebug() << "MyThread MySlot threadId=" << QThread::currentThreadId();//没有写 thread_->moveToThread(thread_);打印出来是主线程id；否则是子线程id
    qDebug() << "MySlot";
}
