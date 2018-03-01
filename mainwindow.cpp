#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Find Your Friends ");
    this->setWindowIcon(QIcon(":/new/images/main17x.png"));
    this->setFixedSize(560, 420);
    // 设置背景
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->init();

    //更改button背景
}

MainWindow::~MainWindow()
{
    saveUsers();
    delete ui;
}

User *MainWindow::findUser(vector<User> *users, int id)
{
    User *user;
    for (int i = 0; i < users->size(); i++) {
        user = &(users->at(i));
        if (user->id == id)
            return user;
    }
    return nullptr;
}

void MainWindow::init()
{
    m_Massagedig = new MassageDialog;
    m_signupdig = new signupdialog;
    connect(this, SIGNAL(signalOpenMassageWin(User)), m_Massagedig, SLOT(openWindows(User)));
    connect(m_signupdig, SIGNAL(enterMainWindows(User*)), this, SLOT(slotAdduser(User*)));
    connect(m_Massagedig, SIGNAL(shutdownSignal()), this, SLOT(shutdown()));
    ui->passwd->setEchoMode(QLineEdit::Password);
    readUsers();
}

void MainWindow::readUsers()
{
    char *url = "./users.json";
    FILE *f = fopen(url, "r");
    if (!f) //打开失败，直接返回false
        return;
    char str_gets[200];
    int id;
    while (fscanf(f, "%d", &id) &&fgets(str_gets, 200, f) != NULL)
    {
        User *u = new User(0, "");
        u->id = id;
        char str_coll[4][150];
        AVLTree::split(str_coll, str_gets, "|*"); //以|*的分割符切割
        strcpy(u->name, str_coll[0]);
        char str_temp[150];
        strcpy(u->passwd, str_coll[1]);
        strcpy(str_temp, str_coll[2]);
        AVLTree::split(str_coll, str_temp, "\n");  //去掉尾部的\n
        strcpy(u->des, str_coll[0]);
        //初始化用户
        users.insert(users.end(), *u);
    }
    fclose(f);
}

void MainWindow::saveUsers()
{
    char *url = "./users.json";
    FILE *f = fopen(url, "w");
    for (int i = 0; i < users.size(); i++) {
        User T = users[i];
        fprintf(f, "%d|*%s|*%s|*%s\n", T.id, T.name, T.passwd, T.des);
    }
    fclose(f);
}

//点击登录按键
void MainWindow::on_login_clicked(bool checked)
{
    QString id = ui->id->text();
    QString passwd = ui->passwd->text();
    for (int i = 0; i < users.size(); i++) {
        QString id_u = QString::number(users[i].getId());
        QString passwd_u = QString(QLatin1String(users[i].getPasswd()));
        if (id == id_u && passwd_u == passwd) { //如果匹配的话
            //发送信息到新的对话框
            emit signalOpenMassageWin(users[i]);
            //打开新的对话框
            m_Massagedig->activateWindow();
            m_Massagedig->setWindowTitle(tr("Main Page"));
            m_Massagedig->setWindowIcon(QIcon(":/new/images/main17x.png"));
            m_Massagedig->exec();
            break;
        } else {
            if (id == "" || passwd == "") {
                qDebug() << "Empty!" << endl;
            } else {
                qDebug() << "Not match!" << endl;
            }
        }
    }
    if (users.size() == 0){
        qDebug() << "Please sign up a count!" << endl;
    }
    ui->id->setText("");
    ui->passwd->setText("");
}

void MainWindow::on_signUp_clicked()
{
    m_signupdig->activateWindow();
    m_signupdig->setWindowTitle(tr("Sign Up"));
    m_signupdig->setWindowIcon(QIcon(":/new/images/main17x.png"));
    m_signupdig->exec();
    ui->id->setText("");
    ui->passwd->setText("");
}

//添加一个新用户
void MainWindow::slotAdduser(User *u) {
    int i;
    for (i = 0; i  < users.size() && u->id != users[i].getId(); ++i);  //用户id从来没有被用过
    if (i == users.size() && u->id > UNINIT &&
            strcmp(u->passwd, "") != 0) {
        users.insert(users.end(), *u);
        qDebug() << "Create successfully!";
        saveUsers();
    } else {
        qDebug() << "Create failed!" << endl;
    }
}

void MainWindow::shutdown()
{
    this->close();
}
