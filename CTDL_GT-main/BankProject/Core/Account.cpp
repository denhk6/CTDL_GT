#include "BankProject/Core/Account.h"
#include <string>
#include <iostream>

using namespace std;

Account::Account(string id, string ten, long long soDu, string loaiTien)
    : strId(id), strTenTaiKhoan(ten), lSoDu(soDu), strLoaiTienTe(loaiTien) {}

string Account::layId() const {
    return strId;
}

string Account::layTen() const {
    return strTenTaiKhoan;
}

long long Account::laySoDu() const {
    return lSoDu;
}

string Account::layLoaiTien() const {
    return strLoaiTienTe;
}

void Account::thietLapId(const string& id) {
    strId = id;
}

void Account::thietLapTen(const string& ten) {
    strTenTaiKhoan = ten;
}

void Account::thietLapSoDu(long long soDuMoi) {
    lSoDu = soDuMoi;
}

bool Account::rutTien(long long soTien) {
    if (soTien < 0) return false;
    if (soTien > (lSoDu - 50000)) return false;

    lSoDu -= soTien;
    return true;
}

void Account::napTien(long long soTien) {
    if (soTien > 0) {
        lSoDu += soTien;
    }
}

istream& operator>>(istream& in, Account& tk) {
    getline(in >> ws, tk.strTenTaiKhoan);
    in >> tk.lSoDu;
    in >> tk.strLoaiTienTe;
    return in;
}

ostream& operator<<(ostream& out, const Account& tk) {
    out << tk.strTenTaiKhoan << endl;
    out << tk.lSoDu << endl;
    out << tk.strLoaiTienTe;
    return out;
}