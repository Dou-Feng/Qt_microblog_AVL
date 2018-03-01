#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include<QLabel>
#include <QMouseEvent>
#include<QPalette>
#include "User.h"
#include <vector>
#include "massagedialog.h"
#include "signupdialog.h"

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static User *findUser(vector<User> *users, int id);

private:
    void init();
    void readUsers();
    void saveUsers();

private slots:
    void on_login_clicked(bool checked);

    void on_signUp_clicked();

public:
    vector<User> users;


private:
    Ui::MainWindow *ui;
    MassageDialog *m_Massagedig;
    signupdialog *m_signupdig;

signals:
    void signalOpenMassageWin(User u);

public slots:
    void slotAdduser(User *u);
    void shutdown();
};

#endif // MAINWINDOW_H
