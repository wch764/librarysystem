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
    cout << "MainMenuPage������ɣ�ʹ�ù����ReservationManager" << endl;
}

bool MainMenuPage::display() const {
    std::cout << "��ӭ, " << currentUser->getName() << endl;
    std::cout << "=== ���˵� ===" << endl;
    std::cout << "1. ͼ�����" << endl;
    std::cout << "2. ������Ϣ" << endl;
    std::cout << "3. ����ͳ��" << endl;
    std::cout << "4. �޸�����" << endl;
    if (currentUser->hasNotifications()) {
        cout << "5. ��Ϣ���� (����֪ͨ)\n";
    }
    else {
        cout << "5. ��Ϣ����\n";
    }
    cout << "6. �˳���¼\n";
    return 0;
}

void MainMenuPage::performAction() {
    while (true) {
        display();
        int choice;
        cout << "��ѡ�����: ";
        if (validateInt(choice)) {
            switch (choice) {
            case 1: {
                cout << "����ͼ�����ҳ��..." << endl;

                std::vector<Reader*> readerPointers;
                convertToPointerVector(readers, readerPointers);

                // ʹ��ͬһ��ReservationManagerʵ��
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
                cout << "����������: ";
                cin.ignore();
                getline(cin, newPassword);
                clearscreen();
                currentUser->changePassword(newPassword);
                cout << "�����޸ĳɹ�!" << endl;
                break;
            }
            case 5: {
                cout << "������Ϣ����..." << endl;
                std::vector<Reader*> readerPointers;
                convertToPointerVector(readers, readerPointers);

                // ʹ��ͬһ��ReservationManagerʵ��
                BookPage bookPage{ books, borrowInfos, readerPointers, currentUser, reservationManager };
                bookPage.showNotifications();
                break;
            }
            case 6:
                clearscreen();
                cout << "�˳���¼..." << endl;
                currentUser = nullptr;
                return;
            default:
                cout << "��Чѡ��!" << endl;
            }
        }
    }
}