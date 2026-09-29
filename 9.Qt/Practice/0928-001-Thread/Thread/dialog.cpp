#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    thread_ = new MyThread;

    //信号槽连接：Dialog的MySignal连接 MyThread的MySlot
    /*
    （1）没有写 thread_->moveToThread(thread_);
       thread_对象默认归属主线程（new出来默认和父对象同一个线程，这里没有父对象，new在主线程，对象亲和性为主线程）。
       - 发送线程：发射 MySignal信号【主线程】。 接收线程：thread_作为接收者，归属主线程。槽函数MySlot()运行在接收者的线程：【主线程】
       → MySlot()就在主线程运行，不是子线程！
    （2）写了thread_->moveToThread(thread_);
        - 发送线程：发射 MySignal信号【主线程】。 接收线程：thread_作为接收者，依附在子线程。槽函数MySlot()运行在接收者的线程：【子线程】
        → MySlot()就在主线程运行，不是子线程！
    */
    connect(this,&Dialog::MySignal,thread_,&MyThread::MySlot);

    //监听线程finished【第一种，加一个this,connect(thread_,&QThread::finished,this,[this]{});】
    // connect(thread_,&QThread::finished,[this]
    //         {
    //         /*receiver = this（Dialog 对象，属于主线程）
    //         （1）AutoConnection 逻辑：
    //             -信号发送线程 (子线程) ≠ receiver 所在线程 (主线程) → 自动变成 Qt::QueuedConnection
    //             -lambda 被封装事件投递到this所属线程（主线程）执行，打印主线程 ID。
    //         */

    //         /*规则：没有接收对象 QObject
    //         （1）Qt::AutoConnection → 不做跨线程判断；信号在哪emit，lambda 就在哪个线程直接执行。
    //             - 不管有没有moveToThread(thread_)；
    //             - finished是子线程emit → lambda跑子线程，打印子线程 ID。
    //         */
    //             qDebug() << "QThread::finish threadId=" << QThread::currentThreadId();//打印出来是子线程id，如果想要打印出来是主线程id，并且弹窗不崩溃，就要在lambda表达式前加this
    //             QMessageBox::information(this,"标题", "线程停止！");//this是Dialog（QWidget），在子线程里创建 / 弹出UI控件，Qt 直接断言崩溃。所以connect要写四个参数，加一个this，再写lambda表达式

    //             qDebug() << "线程停止！";
    //         });

   //监听线程finished【第二种，八糟函数单独写在外面，也加了this，变成四个参数】
    connect(thread_,&MyThread::finished,this,&Dialog::MyThreadStop);

    //让MyThread类的处理信号的槽函数在线程thread_执行：这时候MyThread MySlot threadId= 0x700c和MyThread run threadId= 0x700c打印结果一致
    thread_->moveToThread(thread_);

    qDebug() << "Dialog::Dialog threadId=" << QThread::currentThreadId();//执行位置：main里面Dialog w;构造对话框对象。线程：主线程
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_start_clicked()
{
    //点击按钮触发的槽函数，所有 UI 按钮槽都跑主线程。线程：主线程。
    qDebug() << "Dialog::on_pushButton_start_clicked threadId=" << QThread::currentThreadId();
    if(thread_)
    {
        thread_->start();//主线程调用，通知操作系统开启子线程；run()：运行在子线程。
    }
    else
    {
        QMessageBox::critical(this,"标题","thread is null!");
    }

}


void Dialog::on_pushButton_stop_clicked()
{
    if(thread_)
    {
        //thread()->terminate();
        //thread_->quit();
        thread_->exit();
    }
    else
    {
        QMessageBox::critical(this,"标题","thread is null!");
    }
}


void Dialog::on_pushButton_singal_clicked()
{
    qDebug() << "Dialog MySignal threadId=" << QThread::currentThreadId();//点击按钮，UI槽，主线程执行。在这里发射信号MySignal
    emit MySignal();//主线程发射信号
}

void Dialog::MyThreadStop()
{
    qDebug() << "QThread::finish threadId=" << QThread::currentThreadId();//打印出来是主线程id
    QMessageBox::information(this,"标题", "线程停止！");
    qDebug() << "线程停止！";
}
//start → run → exec → quit → exec 返回 → run 结束 → finished 信号
