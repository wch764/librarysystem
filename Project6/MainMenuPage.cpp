#include<iostream>
#include<string>
#include"Page.h"
#include"Action.h"
#include<vector>
#include"Reader.h"
#include"LoginPage.h"
#include"clearscreen.h"
#include"Book.h"
#include"BorrowInfo.h"
#include"MainMenuPage.h"
#include"BorrowStatisticsPage.h"
#include"ReaderInfoPage.h"
#include"Bookpage.h"
#include"failmanage.h"
#include"reservemanager.h"
using namespace std;
MainMenuPage::MainMenuPage(vector<Book>& bs, vector<BorrowInfo>& bis, User* user, vector<Reader>& rdrs, ReservationManager& rm)
    : books(bs), borrowInfos(bis), currentUser(user), readers(rdrs), reservationManager(rm) {
    cout << "MainMenuPage构造完成，使用共享的ReservationManager" << endl;
}

bool MainMenuPage::display() const {
    std::cout << "欢迎, " << currentUser->getName() << endl;
    std::cout << "=== 主菜单 ===" << endl;
    std::cout << "1. 图书管理" << endl;
    std::cout << "2. 读者信息" << endl;
    std::cout << "3. 借阅统计" << endl;
    std::cout << "4. 修改密码" << endl;
    if (currentUser->hasNotifications()) {
        cout << "5. 消息中心 (有新通知)\n";
    }
    else {
        cout << "5. 消息中心\n";
    }
    cout << "6. 退出登录\n";
    return 0;
}

void MainMenuPage::performAction() {
    while (true) {
        display();
        int choice;
        cout << "请选择操作: ";
        if (validateInt(choice)) {
            switch (choice) {
            case 1: {
                cout << "进入图书管理页面..." << endl;

                std::vector<Reader*> readerPointers;
                convertToPointerVector(readers, readerPointers);

                // 使用同一个ReservationManager实例
                BookPage bookPage{ books, borrowInfos, readerPointers, currentUser, reservationManager };
                bookPage.performAction();
                break;
            }
            case 2: {
                ReaderInfoPage readerInfoPage{ readers, currentUser };
                readerInfoPage.performAction();
                break;
            }
            case 3: {
                BorrowStatisticsPage borrowStatsPage{ borrowInfos, books, currentUser };
                borrowStatsPage.performAction();
                break;
            }
            case 4: {
                string newPassword;
                cout << "输入新密码: ";
                cin.ignore();
                getline(cin, newPassword);
                clearscreen();
                currentUser->changePassword(newPassword);
                cout << "密码修改成功!" << endl;
                break;
            }
            case 5: {
                cout << "进入消息中心..." << endl;
                std::vector<Reader*> readerPointers;
                convertToPointerVector(readers, readerPointers);

                // 使用同一个ReservationManager实例
                BookPage bookPage{ books, borrowInfos, readerPointers, currentUser, reservationManager };
                bookPage.showNotifications();
                break;
            }
            case 6:
                clearscreen();
                cout << "退出登录..." << endl;
                currentUser = nullptr;
                return;
            default:
                cout << "无效选择!" << endl;
            }
        }
    }
}