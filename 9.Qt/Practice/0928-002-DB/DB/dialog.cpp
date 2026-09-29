#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("0928-002-Thread.db");
    db.open();
    //db.close();
    QSqlQuery query(db);
    QString sql_creat_table="CREATE TABLE Student ("
                            "Id   TEXT    PRIMARY KEY"
                            "             NOT NULL,"
                            "Name TEXT,"
                            "Age  INTEGER"
                            ");";
    query.exec(sql_creat_table);

    QString sql_insert = "INSERT INTO Student ("
                         "Id,Name,Age)"
                         "VALUES ("
                         "'10001','侯超','18'"
                         ");";
    query.exec(sql_insert);

    QString sql_insert_2=QString(
        "INSERT INTO Student (Id,Name,Age)VALUES "
                               "('%1','%2','%3',);").arg("10002").arg("李四").arg("18");
    query.exec(sql_insert_2);

    QString sql_select=QString("select * from Student;");
    query.exec(sql_select);

    while (query.next())
    {
        qDebug()<<query.value(0).toString();
        qDebug()<<query.value(1).toString();
        qDebug()<<query.value(2).toInt();
    }

    //qDebug()<<"Drivers="<<QSqlDatabase::drivers();

}

Dialog::~Dialog()
{
    delete ui;
}
