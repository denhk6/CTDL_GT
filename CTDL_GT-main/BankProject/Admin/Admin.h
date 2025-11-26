#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <iostream>
#include "BankProject/Core/List.h"
#include "BankProject/Core/Card.h"

// --- Lớp dữ liệu AdminAccount ---
class AdminAccount {
private:
    std::string _strUser;
    std::string _strPass;

public:
    AdminAccount(std::string user = "", std::string pass = "");
    std::string layUser() const;
    bool kiemTraPass(const std::string& pass) const;

    bool operator==(const AdminAccount& other) const {
        return this->_strUser == other._strUser;
    }

    friend std::istream& operator>>(std::istream& in, AdminAccount& ad);
    friend std::ostream& operator<<(std::ostream& out, const AdminAccount& ad);
};


// --- Lớp logic Admin ---
class Admin {
private:
    List<AdminAccount>* _pDsAdmin;
    List<Card>* _pDsCard;

    // Định nghĩa hằng số cho đường dẫn file và PIN mặc định
    const std::string FILE_CARD_LIST = "BankProject/Data/TheTu.txt";
    const std::string PIN_DEFAULT = "123456";

public:
    Admin(List<AdminAccount>* dsAdmin, List<Card>* dsCard);
    void run();

private:
    void hienThiMenuAdmin();
    void xemDanhSachTaiKhoan();
    void themTaiKhoan();
    void xoaTaiKhoan();
    void moKhoaTaiKhoan();
};

#endif // ADMIN_H