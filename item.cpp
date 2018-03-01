#include "item.h"
#include "ui_item.h"
#include <QDebug>
#include "mainwindow.h"

Item::Item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);
}

void Item::init(QString text, bool isFriend, bool isFollowing)
{
    ui->Text->setText(text);
    ui->isFriend->setChecked(isFriend);
    ui->isFollowing->setChecked(isFollowing);
}

void Item::init2(int id, Member m)
{
    this->id_me = id;
    this->m = m;
}

Item::~Item()
{
    delete ui;
}

void Item::on_isFollowing_stateChanged(int arg1)
{
    if (arg1 > 0) {
        emit addFollowedSignal(id_me, m);
    } else if (arg1 == 0) {
        removeFollowedSignal(id_me, m);
    }
}

void Item::on_isFriend_stateChanged(int arg1)
{
    if (arg1 > 0) {
        emit addFriendSignal(m);
    } else if (arg1 == 0) {
        emit removeFriendSignal(m);
    }
}
