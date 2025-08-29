#pragma once
#include "Date.h"
#include <string>

class Notification {
public:
    enum Type {
        RESERVATION_AVAILABLE,
        RESERVATION_EXPIRED
    };

private:
    Type type;
    std::string bookIsbn;
    std::string bookTitle;
    Date expiryDate;

public:
    Notification(Type type, const std::string& isbn, const std::string& title, const Date& expiry)
        : type(type), bookIsbn(isbn), bookTitle(title), expiryDate(expiry) {
    }

    Type getType() const { return type; }
    std::string getBookIsbn() const { return bookIsbn; }
    std::string getBookTitle() const { return bookTitle; }
    Date getExpiryDate() const { return expiryDate; }

    std::string getMessage() const {
        if (type == RESERVATION_AVAILABLE) {
            return "ԤԼͼ�顶" + bookTitle + "���ѿ��ã�����" + expiryDate.toString() + "ǰȷ�Ͻ���";
        }
        else {
            return "ԤԼͼ�顶" + bookTitle + "���ѹ���";
        }
    }
};