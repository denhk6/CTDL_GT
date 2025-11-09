#include "BankProject/Core/Transaction.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

Transaction::Transaction(string id, string loai, long long soTien, string chiTiet)
    : strIdTaiKhoan(id), strLoaiGiaoDich(loai), lSoTien(soTien), strChiTiet(chiTiet) {
    thoiGian = time(nullptr);
}

string Transaction::formatTime(const time_t& thoiGian) {
    char buf[80];
#ifdef _MSC_VER
    tm thoiGianInfo;
    localtime_s(&thoiGianInfo, &thoiGian);
#else
    tm thoiGianInfo = *localtime(&thoiGian);
#endif
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &thoiGianInfo);
    return string(buf);
}

void Transaction::hienThi() const {
    cout << "---------------------------------\n";
    cout << "Thoi gian: " << formatTime(thoiGian) << endl;
    cout << "Loai GD:   " << strLoaiGiaoDich << endl;
    cout << "So tien:   " << lSoTien << " VND" << endl;
    if (!strChiTiet.empty()) {
        cout << "Chi tiet:  " << strChiTiet << endl;
    }
}

ostream& operator<<(ostream& out, const Transaction& gd) {
    string chiTietFile = gd.strChiTiet;
    for (char& c : chiTietFile) {
        if (c == ' ') c = '_';
    }
    if (chiTietFile.empty()) chiTietFile = "KHONG";

    out << gd.strIdTaiKhoan << " "
        << gd.strLoaiGiaoDich << " "
        << gd.lSoTien << " "
        << gd.thoiGian << " "
        << chiTietFile;
    return out;
}

istream& operator>>(istream& in, Transaction& gd) {
    in >> gd.strIdTaiKhoan >> gd.strLoaiGiaoDich >> gd.lSoTien >> gd.thoiGian >> gd.strChiTiet;
    if (gd.strChiTiet == "KHONG") {
        gd.strChiTiet = "";
    } else {
        for (char& c : gd.strChiTiet) {
            if (c == '_') c = ' ';
        }
    }
    return in;
}