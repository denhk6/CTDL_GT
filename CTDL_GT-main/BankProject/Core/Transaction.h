#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <ctime>

class Transaction {
private:
    std::string _strIdTaiKhoan;
    std::string _strLoaiGiaoDich;
    long long _lSoTien;
    time_t _thoiGian;
    std::string _strChiTiet;

public:
    Transaction(std::string id = "", std::string loai = "", long long soTien = 0, std::string chiTiet = "");

    void hienThi() const;

    // Hàm tĩnh để định dạng thời gian từ time_t sang chuỗi
    static std::string formatTime(const time_t& thoiGian);

    friend std::ostream& operator<<(std::ostream& out, const Transaction& gd);
    friend std::istream& operator>>(std::istream& in, Transaction& gd);
};

#endif // TRANSACTION_H