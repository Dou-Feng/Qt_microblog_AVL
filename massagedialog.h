#ifndef MASSAGEDIALOG_H
#define MASSAGEDIALOG_H

#include <QDialog>
#include "user.h"
#include <QList>
#include "item.h"

namespace Ui {
class MassageDialog;
}

class MassageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MassageDialog(QWidget *parent = 0);
    ~MassageDialog();
    void erDuFriends(vector<Member> *coll, int id);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MassageDialog *ui;
    User *me;
    vector<User> users;
    void createList(vector<Member> *m);
    void readUsers();
    void saveUsers();



public slots:
    void openWindows(User data);
private slots:
    void on_friends_clicked();
    void on_MainPage_clicked();

    void on_follow_clicked();
    void on_fanns_clicked();
    void addFriends(Member m);
    void addFollowed(int id_o, Member m);
    void removeFriends(Member m);
    void removeFollowed(int id_o, Member m);

    void on_ErDuFriend_clicked();

    void on_InterFollowing_clicked();

    void on_pushButton_clicked();

    void on_InterHobby_clicked();

signals:
    void shutdownSignal();
};

#endif // MASSAGEDIALOG_H
