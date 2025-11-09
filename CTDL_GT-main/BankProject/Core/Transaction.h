#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <ctime>

class Transaction {
private:
    std::string strIdTaiKhoan;
    std::string strLoaiGiaoDich;
    long long lSoTien;
    time_t thoiGian;
    std::string strChiTiet;

public:
    Transaction(std::string id = "", std::string loai = "", long long soTien = 0, std::string chiTiet = "");

    void hienThi() const;

    static std::string formatTime(const time_t& thoiGian);

    friend std::ostream& operator<<(std::ostream& out, const Transaction& gd);
    friend std::istream& operator>>(std::istream& in, Transaction& gd);
};

#endif // TRANSACTION_H