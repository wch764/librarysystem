#pragma once
#include<iostream>
#include<string>
#include"Page.h"
#include"Action.h"
#include<vector>
#include"Reader.h"
#include"Book.h"
#include"BorrowInfo.h"
#include"User.h"
#include"reservemanager.h"

class MainMenuPage : public Page, public Action {
private:
    vector<Book>& books;
    vector<BorrowInfo>& borrowInfos;
    User* currentUser;
    vector<Reader>& readers;
    ReservationManager& reservationManager; // 改为引用，确保使用同一个实例

public:
    MainMenuPage(vector<Book>& bs, vector<BorrowInfo>& bis, User* user, vector<Reader>& rdrs, ReservationManager& rm);
    bool display() const override final;
    void performAction() override final;

    static void convertToPointerVector(vector<Reader>& readers, vector<Reader*>& pointers) {
        pointers.clear();
        pointers.reserve(readers.size());

        for (size_t i = 0; i < readers.size(); ++i) {
            pointers.push_back(&readers[i]);
        }
    }
};