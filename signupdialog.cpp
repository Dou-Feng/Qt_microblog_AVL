#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QDebug>

signupdialog::signupdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signupdialog)
{
    ui->setupUi(this);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

signupdialog::~signupdialog()
{
    ui->id->setText("");
    ui->name->setText("");
    ui->passwd->setText("");
    ui->description->setText("");
    delete ui;
}

void signupdialog::on_buttonBox_accepted()
{
    QString id = ui->id->text();
    int id_i = id.toInt();
    QString name = ui->name->text();
    QString passwd = ui->passwd->text();
    QByteArray qpasswd = passwd.toLocal8Bit();
    char *passwd_s = qpasswd.data();
    QString des = ui->description->text();
    QByteArray qname = name.toLocal8Bit();
    char *name_s = qname.data();
    QByteArray qdes = des.toLocal8Bit();
    char *des_s = qdes.data();
    User *u = new User(id_i,name_s, passwd_s,des_s);
    emit enterMainWindows(u);
    ui->id->setText("");
    ui->name->setText("");
    ui->passwd->setText("");
    ui->description->setText("");
}

void signupdialog::on_buttonBox_destroyed()
{
    ui->id->setText("");
    ui->name->setText("");
    ui->passwd->setText("");
    ui->description->setText("");
}
