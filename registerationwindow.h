#ifndef REGISTERATIONWINDOW_H
#define REGISTERATIONWINDOW_H

#include <QDialog>
#include "authmanager.h"

namespace Ui {
class RegisterationWindow;
}

class RegisterationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterationWindow(QWidget *parent = nullptr);
    ~RegisterationWindow();

private slots:
    void on_login_clicked();
    void on_Submit_clicked();

private:
    Ui::RegisterationWindow *ui;
    AuthManager *authManager;
};

#endif // REGISTERATIONWINDOW_H
