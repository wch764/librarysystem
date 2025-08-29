#pragma once
#include"Serializable.h"
#include<iostream>
#include"Date.h"
#include<fstream>
#include<string>
#include"notificationcenter.h"
using namespace std;
// 读者类
class User : public Serializable, public Date {
private:
    string username;
    string password;
    string name;
    Date registrationDate;
    std::vector<Notification> notifications;


public:
    User(const string& uname = "", const string& pwd = "", const string& nm = "");
    virtual ~User()
    {
        std::cout << "销毁User: " << username << std::endl;
    }
    //读取
    bool loadFromStream(istream& file) override;


    void saveToStream(ostream& file) const override;

    // 保持原有接口但修改实现
    void loadFromFile(const string& filename) override;


    void saveToFile(const string& filename) const override;
    void changePassword(const string& newPassword);
    string getUsername() const;
    string getPassword() const;
    string getName() const;
    virtual bool get_isadmin() = 0;
    Date getRegistrationDate() const;
    void addNotification(const Notification& noti) {
        notifications.push_back(noti);
    }

    std::vector<Notification> getNotifications() {
        auto result = notifications;
        notifications.clear(); // 读取后清空
        return result;
    }

    bool hasNotifications() const {
        return !notifications.empty();
    }
}

;