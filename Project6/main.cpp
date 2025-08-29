#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <limits>
#include"Serializable.h"
#include"Action.h"
#include"Page.h"
#include"Date.h"
#include"Book.h"
#include"Reader.h"
#include"BorrowInfo.h"
#include"LoginPage.h"
#include"MainMenuPage.h"
#include"Admin.h"
#include"reservemanager.h"
using namespace std;

// 改进的数据加载函数，添加调试信息
template <typename T>
void loadDataFromFile(const string& filename, vector<T>& items) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "无法打开文件: " << filename << endl;
        return;
    }

    cout << "开始加载文件: " << filename << endl;
    T item;
    int count = 0;

    while (item.loadFromStream(file)) {
        // 不同类型的空状态判断方法
        bool isValid = false;

        if constexpr (is_same_v<T, Reader> || is_same_v<T, Admin>) {
            isValid = !item.getUsername().empty();
        }
        else if constexpr (is_same_v<T, Book>) {
            isValid = !item.getISBN().empty();
        }
        else if constexpr (is_same_v<T, BorrowInfo>) {
            isValid = !item.getBookISBN().empty();
        }

        if (isValid) {
            items.push_back(item);
            count++;
        }
    }

    cout << "从 " << filename << " 加载了 " << count << " 条记录" << endl;
    file.close();
}

// 改进的数据保存函数
template <typename T>
void saveDataToFile(const string& filename, const vector<T>& items) {
    cout << "保存 " << items.size() << " 条记录到 " << filename << endl;

    ofstream file(filename, ios::trunc); // 使用trunc模式清空文件
    if (!file.is_open()) {
        cout << "无法打开文件进行保存: " << filename << endl;
        return;
    }

    int count = 0;
    for (const auto& item : items) {
        item.saveToStream(file);
        count++;
    }

    file.close();
    cout << "成功保存了 " << count << " 条记录到 " << filename << endl;
}

int main() {
    vector<Reader> readers;
    vector<Admin> admins;
    vector<Book> books;
    vector<BorrowInfo> borrowInfos;

    cout << "=== 开始加载数据 ===" << endl;

    // 加载数据
    loadDataFromFile("readers.dat", readers);
    loadDataFromFile("books.dat", books);
    loadDataFromFile("borrowinfo.dat", borrowInfos);
    loadDataFromFile("admins.dat", admins);

    cout << "加载完成 - 读者: " << readers.size()
        << ", 管理员: " << admins.size()
        << ", 图书: " << books.size()
        << ", 借阅记录: " << borrowInfos.size() << endl;

    // 检查读者文件
    if (readers.empty()) {
        cout << "读者信息为空，请先注册用户！" << endl;
        return 0;
    }

    // 如果图书为空，添加一些示例图书
    if (books.empty()) {
        cout << "图书信息为空，添加示例图书..." << endl;
        books.emplace_back("9787111636667", "C++ Primer", "Stanley Lippman", "编程 C++ 计算机", "经典C++教程", 5);
        books.emplace_back("9787302517969", "深入理解计算机系统", "Randal Bryant", "计算机 系统", "计算机系统经典教材", 3);
        saveDataToFile("books.dat", books);
    }

    // 创建全局的ReservationManager实例
    ReservationManager globalReservationManager(borrowInfos);

    // 从已有的borrowInfos中重建预约队列
    globalReservationManager.rebuildFromBorrowInfos();

    // 创建登录页面
    LoginPage loginPage(readers, admins);

    while (true) {
        loginPage.display();
        loginPage.performAction();
        User* currentUser = loginPage.getCurrentUser();

        if (!currentUser) {
            break;  // 用户选择退出
        }

        cout << "用户登录成功: " << currentUser->getUsername() << endl;

        // 创建主菜单页面，传入全局ReservationManager
        MainMenuPage mainMenu(books, borrowInfos, currentUser, readers, globalReservationManager);
        mainMenu.performAction();
    }

    cout << "\n=== 开始保存数据 ===" << endl;
    cout << "保存前数据统计 - 读者: " << readers.size()
        << ", 图书: " << books.size()
        << ", 借阅记录: " << borrowInfos.size() << endl;

    // 保存数据
    saveDataToFile("readers.dat", readers);
    saveDataToFile("books.dat", books);
    saveDataToFile("borrowinfo.dat", borrowInfos);
    saveDataToFile("admins.dat", admins);

    cout << "系统退出，数据已保存。" << endl;
    return 0;
}