#include "dialog.h"

#include <QApplication>
#include <QThread>
int main(int argc, char *argv[])
{
    qDebug() << "main threadId=" << QThread::currentThreadId();//执行位置：main()函数，程序刚启动。线程：主线程 (UI 线程)
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return QApplication::exec();
}
