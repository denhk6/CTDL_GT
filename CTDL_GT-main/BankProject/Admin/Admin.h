#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <iostream>
// --- SỬA Ở ĐÂY --- (Thêm lại BankProject/)
#include "BankProject/Core/List.h"
#include "BankProject/Core/Card.h"

// --- Lop du lieu Admin ---
class AdminAccount {
private:
    std::string strUser;
    std::string strPass;

public:
    AdminAccount(std::string user = "", std::string pass = "");
    std::string layUser() const;
    bool kiemTraPass(const std::string& pass) const;

    bool operator==(const AdminAccount& other) const {
        return strUser == other.strUser;
    }

    friend std::istream& operator>>(std::istream& in, AdminAccount& ad);
    friend std::ostream& operator<<(std::ostream& out, const AdminAccount& ad);
};


// --- Lop logic Admin ---
class Admin {
private:
    List<AdminAccount>* pDsAdmin;
    List<Card>* pDsCard;

    const std::string FILE_THETU = "BankProject/Data/TheTu.txt";
    const std::string PIN_MAC_DINH = "123456";

public:
    // --- SỬA Ở ĐÂY --- (Xóa dataDir)
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