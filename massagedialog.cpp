#include "massagedialog.h"
#include "ui_massagedialog.h"
#include "item.h"
#include "mainwindow.h"
#include "QDebug"
#include "QMessageBox"
#define MAXMEMBER 500

MassageDialog::MassageDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::MassageDialog)
{
    ui->setupUi(this);
    // 设置背景
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

MassageDialog::~MassageDialog()
{
    ui->listWidget->clear();
    qDebug() << "hello";
    delete ui;
}


void MassageDialog::closeEvent(QCloseEvent *event)
{
    saveUsers();
    emit shutdownSignal();
    qDebug() << "hello";
}

void MassageDialog::openWindows(User u)
{
    User data = u;
    QString id = QString::number(data.getId());
    QString name = QString(QString::fromLocal8Bit(data.getName()));
    QString des = QString(QString::fromLocal8Bit(data.des));
    ui->id->setText(id);
    ui->name->setText(name);
    ui->des->setText(des);
    readUsers();
    ui->listWidget->clear();
    me = MainWindow::findUser(&users, data.id);
    QString follow_text = QString(QString::fromUtf8("关注(")) +
            QString::number(me->followed->getSize()) + ")";
    ui->follow->setText(follow_text);
    QString fd_text = QString(QString::fromUtf8("好友(")) +
            QString::number(me->friends->getSize()) + ")";
    ui->friends->setText(fd_text);
    QString fan = QString(QString::fromUtf8("粉丝(")) +
            QString::number(me->fans->getSize()) + ")";
    ui->fanns->setText(fan);
}


void MassageDialog::createList(vector<Member> *m) {
    ui->listWidget->clear();
    qDebug() << m->size();
    if (m->size() == 0) {
        QMessageBox *mb = new QMessageBox();
        mb->setText(QString(QString::fromUtf8("无结果！")));
        mb->exec();
    }
    for (int i = 0; i < m->size(); i++) {
        Member data = (*m)[i];
        QString id = QString::number(data.id);
        QString name = QString(QString::fromLocal8Bit(data.name));
        QString des = QString(QString::fromLocal8Bit(data.description));
        QString text = "ID:" + id + "\nName:" + name + "\ndescription:" + des;
        bool isFriend = false;
        bool isFollowed = false;
        if (me->find(FRIEND, data).id != UNINIT)
            isFriend = true;
        if(me->find(FOLLOWED, data).id != UNINIT)
            isFollowed = true;
        //创建可添加条目
        Item *item = new Item;
        connect(item, SIGNAL(addFollowedSignal(int,Member)), this,
                SLOT(addFollowed(int,Member)));
        connect(item, SIGNAL(addFriendSignal(Member)), this,
                SLOT(addFriends(Member)));
        connect(item, SIGNAL(removeFollowedSignal(int,Member)),
                this, SLOT(removeFollowed(int,Member)));
        connect(item, SIGNAL(removeFriendSignal(Member)), this,
                SLOT(removeFriends(Member)));
        item->init(text, isFriend, isFollowed);
        item->init2(data.id, data);
        QListWidgetItem *qItem = new QListWidgetItem;
        qItem->setSizeHint(QSize(260, 150));
        ui->listWidget->addItem(qItem);
        ui->listWidget->setItemWidget(qItem, item);
    }
}

void MassageDialog::readUsers()
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
    for (int i = 0; i < users.size(); ++i) {
        users[i].read();
    }
    fclose(f);
}

void MassageDialog::saveUsers()
{
    for (int i = 0; i < users.size(); ++i) {
        users[i].save();
    }
}

void MassageDialog::on_MainPage_clicked()
{
    vector<Member> m;
    for (int i = 0; i < users.size(); i++) {
        Member e;
        e.id = users[i].id;
        strcpy(e.name, users[i].name);
        strcpy(e.description, users[i].des);
        m.insert(m.end(), e);
    }
    createList(&m);
}

void MassageDialog::on_friends_clicked()
{
    ADT friends;
    friends = me->getFriends();
    Member m[MAXMEMBER];
    vector<Member> vm;
    memset(m, 0, sizeof(Member) * MAXMEMBER);
    friends.getAllElem(m);
    for (int i = 0; m[i].id != 0; i++) {
        vm.insert(vm.end(), m[i]);
    }
    createList(&vm);
}


void MassageDialog::on_follow_clicked()
{
    ADT followed;
    followed = me->getFollowed();
    Member m[MAXMEMBER];
    vector<Member> vm;
    memset(m, 0, sizeof(Member) * MAXMEMBER);
    followed.getAllElem(m);
    for (int i = 0; m[i].id != 0; i++) {
        vm.insert(vm.end(), m[i]);
    }
    createList(&vm);
}

void MassageDialog::on_fanns_clicked()
{
    ADT fans;
    fans = me->getFans();
    Member m[MAXMEMBER];
    vector<Member> vm;
    memset(m, 0, sizeof(Member) * MAXMEMBER);
    fans.getAllElem(m);
    for (int i = 0; m[i].id != 0; i++) {
        vm.insert(vm.end(), m[i]);
    }
    createList(&vm);
}

void MassageDialog::addFriends(Member m)
{
    me->add(FRIEND, m);
    QString fd_text = QString(QString::fromUtf8("好友(")) +
            QString::number(me->friends->getSize()) + ")";
    ui->friends->setText(fd_text);

}

void MassageDialog::addFollowed(int id_o, Member m)
{
    me->add(FOLLOWED, m);
    User *other = MainWindow::findUser(&users, id_o);
    if (other) {
        Member e(me->id, me->name, me->des);
        other->add(FAN, e);
    }
    QString follow_text = QString(QString::fromUtf8("关注(")) +
            QString::number(me->followed->getSize()) + ")";
    ui->follow->setText(follow_text);
}

void MassageDialog::removeFriends(Member m)
{
    me->remove(FRIEND, m);
    QString fd_text = QString(QString::fromUtf8("好友(")) +
            QString::number(me->friends->getSize()) + ")";
    ui->friends->setText(fd_text);
}

void MassageDialog::removeFollowed(int id_o, Member m)
{
    me->remove(FOLLOWED, m);
    User *other = MainWindow::findUser(&users, id_o);
    if (other) {
        Member e(me->id, me->name, me->des);
        other->remove(FAN, e);
    }
    QString follow_text = QString(QString::fromUtf8("关注(")) +
            QString::number(me->followed->getSize()) + ")";
    ui->follow->setText(follow_text);
}

void MassageDialog::on_ErDuFriend_clicked()
{
    Member coll[MAXMEMBER];
    vector<Member> vm;
    memset(coll, 0, sizeof(Member) * MAXMEMBER);
    User::InterFriends(coll, me, &users);
    for (int i = 0; coll[i].id != 0; i++) {
        vm.insert(vm.end(), coll[i]);
    }

    createList(&vm);
}

void MassageDialog::on_InterFollowing_clicked()
{
    Member coll[MAXMEMBER];
    vector<Member> vm;
    memset(coll, 0, sizeof(Member) * MAXMEMBER);
    int id = ui->inputId->text().toInt();
    User *b = MainWindow::findUser(&users, id);
    if (!b) {
        QMessageBox *mb = new QMessageBox();
        mb->setText(QString(QString::fromUtf8("无结果！")));
        mb->exec();
        ui->inputId->setText("");
        return ;
    }
    User::InterFollowings(coll, me, b);
    for (int i = 0; coll[i].id != 0; i++) {
        vm.insert(vm.end(), coll[i]);
    }
    createList(&vm);
    ui->inputId->setText("");
}



void MassageDialog::on_pushButton_clicked()
{
    int id = ui->search->text().toInt();
    User *find = MainWindow::findUser(&users, id);
    if (!find) {
        QMessageBox *mb = new QMessageBox();
        mb->setText(QString(QString::fromUtf8("无结果！")));
        mb->exec();
        ui->search->setText("");
        return ;
    }
    Member m(find->id, find->name, find->des);
    vector<Member> vm;
    vm.insert(vm.end(), m);
    createList(&vm);
    ui->search->setText("");
}

void MassageDialog::on_InterHobby_clicked()
{
    Member coll[MAXMEMBER];
    vector<Member> vm;
    vector<Member> user_info;
    for (int i = 0; i < users.size(); i++) {
        Member u(users[i].id, users[i].name, users[i].des);
        user_info.insert(user_info.end(), u);
    }
    memset(coll, 0, sizeof(Member) * MAXMEMBER);
    User::InterHobby(coll, me, user_info);
    for (int i = 0; coll[i].id != 0; i++) {
        vm.insert(vm.end(), coll[i]);
    }
    createList(&vm);
}
