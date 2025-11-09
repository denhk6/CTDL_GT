#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>

class Account {
private:
    std::string strId;
    std::string strTenTaiKhoan;
    long long lSoDu;
    std::string strLoaiTienTe;

public:
    Account(std::string id = "", std::string ten = "", long long soDu = 0, std::string loaiTien = "VND");

    std::string layId() const;
    std::string layTen() const;
    long long laySoDu() const;
    std::string layLoaiTien() const;

    void thietLapId(const std::string& id);
    void thietLapTen(const std::string& ten);
    void thietLapSoDu(long long soDuMoi);

    bool rutTien(long long soTien);
    void napTien(long long soTien);

    friend std::istream& operator>>(std::istream& in, Account& tk);
    friend std::ostream& operator<<(std::ostream& out, const Account& tk);
};

#endif // ACCOUNT_H