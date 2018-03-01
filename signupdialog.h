#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include "User.h"

namespace Ui {
class signupdialog;
}

class signupdialog : public QDialog
{
    Q_OBJECT

public:
    explicit signupdialog(QWidget *parent = 0);
    ~signupdialog();



signals:
    void enterMainWindows(User *u);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_destroyed();

private:
    Ui::signupdialog *ui;
};

#endif // SIGNUPDIALOG_H
