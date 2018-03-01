#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include "User.h"
namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    explicit Item(QWidget *parent = 0);
    void init(QString text, bool isFriends, bool isFollowing);
    void init2(int id, Member m);
    ~Item();

private slots:
    void on_isFollowing_stateChanged(int arg1);

    void on_isFriend_stateChanged(int arg1);

signals:
    void addFriendSignal(Member m);
    void removeFriendSignal(Member m);
    void addFollowedSignal(int id_me, Member m);
    void removeFollowedSignal(int id_me, Member m);

private:
    Ui::Item *ui;
    Member m;
    int id_me;

};

#endif // ITEM_H
