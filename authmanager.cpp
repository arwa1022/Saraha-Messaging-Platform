#include "authmanager.h"
using namespace std;
User AuthManager::currentuser;
AuthManager::AuthManager() {
    loadData();
}

bool AuthManager::isValidEmail(const QString& email) {
    if (email.contains(' ')) {
        QMessageBox::warning(nullptr, "Invalid Email", "Email cannot contain spaces!");
        return false;
    }
    int atCount = email.count('@');
    if (atCount != 1) {
        QMessageBox::warning(nullptr, "Invalid Email", "Email must contain exactly one '@'!");
        return false;
    }
    int atPos = email.indexOf('@');
    QString domain = email.mid(atPos + 1);
    if (!domain.contains('.')) {
        QMessageBox::warning(nullptr, "Invalid Email", "Email must have a domain (e.g., .com, .org)!");
        return false;
    }
    QString localPart = email.mid(0, atPos);
    if (localPart.isEmpty()) {
        QMessageBox::warning(nullptr, "Invalid Email", "Email local part (before @) cannot be empty!");
        return false;
    }
    int dotPos = domain.indexOf('.');
    if (dotPos == 0 || dotPos == domain.length() - 1) {
        QMessageBox::warning(nullptr, "Invalid Email", "Invalid domain format!");
        return false;
    }
    return true;
}

bool AuthManager::registerUser(const QString& username, const QString& password, const QString& nickname,
                               const QString& email, const QString& gender) {
    if (username.isEmpty() || password.isEmpty() || nickname.isEmpty() || email.isEmpty() || gender.isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "Please fill in all fields!");
        return false;
    }
    if (users.contains(username)) {
        QMessageBox::warning(nullptr, "Error", "This username is already taken!");
        return false;
    }
    if (emailToUsername.contains(email)) {
        QMessageBox::warning(nullptr, "Error", "This email is already used!");
        return false;
    }
    if (gender != "Male" && gender != "Female") {
        QMessageBox::warning(nullptr, "Error", "Gender must be 'Male' or 'Female'!");
        return false;
    }
    if (!isValidEmail(email)) {
        return false;
    }
    int newId = users.size() + 1;
    users[username] = qMakePair(password, newId);
    emailToUsername[email] = username;
    userMap[username] = User(newId, username, password, nickname, email, gender);
       saveData();
    QMessageBox::information(nullptr, "Success", "Registration successful!");
    return true;
}

bool AuthManager::login(const QString& email, const QString& password, int& userId) {
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "Email and password are required!");
        return false;
    }
    auto emailIt = emailToUsername.find(email);
    if (emailIt == emailToUsername.end()) {
        QMessageBox::warning(nullptr, "Error", "Email not found!");
        return false;
    }
    QString username = emailIt.value();
    auto userIt = users.find(username);
    if (userIt != users.end() && userIt.value().first == password) {
        userId = userIt.value().second;
        QMessageBox::information(nullptr, "Success", "Login successful!");
        return true;
    }
    QMessageBox::warning(nullptr, "Error", "Wrong password!");
    return false;
}

void AuthManager::loadData() {
    QFile file("D:/QT_Creator_C++_GUI/QT_Projects/DS_Saraha_Project/users.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            int id = in.readLine().toInt();
            QString username = in.readLine();
            QString password = in.readLine();
            QString nickname = in.readLine();
            QString email = in.readLine();
            QString gender = in.readLine();
            users[username] = qMakePair(password, id);
            emailToUsername[email] = username;
            userMap[username] = User(id, username, password, nickname, email, gender);
        }
        file.close();
    }
}

void AuthManager::saveData() {
    QFile file("D:/QT_Creator_C++_GUI/QT_Projects/DS_Saraha_Project/users.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for (auto it = userMap.constBegin(); it != userMap.constEnd(); ++it) {
            const QString& username = it.key();
            const User& user = it.value();

            out << user.id << "\n"
                << username << "\n"
                << user.password << "\n"
                << user.nickname << "\n"
                << user.email << "\n"
                << user.gender << "\n";
        }

        file.close();
    } else {
        QMessageBox::warning(nullptr, "Error", "Could not open file for writing.");
    }
}
