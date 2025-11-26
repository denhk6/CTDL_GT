#include "BankProject/Core/Account.h"
#include <string>
#include <iostream>

using namespace std;

Account::Account(string id, string ten, long long soDu, string loaiTien)
    : _strId(id), _strTenTaiKhoan(ten), _lSoDu(soDu), _strLoaiTienTe(loaiTien) {}

string Account::layId() const {
    return _strId;
}

string Account::layTen() const {
    return _strTenTaiKhoan;
}

long long Account::laySoDu() const {
    return _lSoDu;
}

string Account::layLoaiTien() const {
    return _strLoaiTienTe;
}

void Account::thietLapId(const string& id) {
    _strId = id;
}

void Account::thietLapTen(const string& ten) {
    _strTenTaiKhoan = ten;
}

void Account::thietLapSoDu(long long soDuMoi) {
    _lSoDu = soDuMoi;
}

bool Account::rutTien(long long soTien) {
    if (soTien < 0) return false;
    // Ràng buộc: Đảm bảo số dư còn lại >= 50000 VND
    if (soTien > (this->_lSoDu - 50000)) return false;

    _lSoDu -= soTien;
    return true;
}

void Account::napTien(long long soTien) {
    if (soTien > 0) {
        _lSoDu += soTien;
    }
}

// Đọc file [ID].txt: Tên Tài Khoản (dòng 1), Số Dư (dòng 2), Loại Tiền (dòng 3)
istream& operator>>(istream& in, Account& tk) {
    // >> ws để loại bỏ khoảng trắng dư thừa
    getline(in >> ws, tk._strTenTaiKhoan);
    in >> tk._lSoDu;
    in >> tk._strLoaiTienTe;
    return in;
}

// Ghi file [ID].txt
ostream& operator<<(ostream& out, const Account& tk) {
    out << tk._strTenTaiKhoan << endl;
    out << tk._lSoDu << endl;
    out << tk._strLoaiTienTe;
    return out;
}