#include "registerationwindow.h"
#include "ui_registerationwindow.h"
#include "login.h"
#include "mainwindow.h"
#include <QMessageBox>

RegisterationWindow::RegisterationWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterationWindow)
    , authManager(new AuthManager())
{
    ui->setupUi(this);
    setWindowTitle("Registeration");
}

RegisterationWindow::~RegisterationWindow()
{
    delete ui;
    delete authManager;
}

void RegisterationWindow::on_login_clicked()
{
    login *Login = new login(this);
    hide();
    Login->show();
}

void RegisterationWindow::on_Submit_clicked()
{
    QString email = ui->Email->text();
    QString username = ui->Username->text();
    QString password = ui->password->text();
    QString confirmPassword = ui->confirm_password->text();
    QString nickname = ui->nickname->text();
    QString gender;

    if (ui->Gender->isChecked()) {
        gender = "Male";
    } else if (ui->G_female->isChecked()) {
        gender = "Female";
    } else {
        QMessageBox::warning(this, "Error", "Please select a gender!");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
        return;
    }

    if (authManager->registerUser(username, password, nickname, email, gender)) {
      login *loginWindow = new login();
       loginWindow->show();
        close();
    }
}
