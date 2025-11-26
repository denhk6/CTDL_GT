#include "BankProject/Core/Transaction.h"
#include "BankProject/Core/Utils.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Constructor, tự động ghi nhận thời gian giao dịch
Transaction::Transaction(string id, string loai, long long soTien, string chiTiet)
    : _strIdTaiKhoan(id), _strLoaiGiaoDich(loai), _lSoTien(soTien), _strChiTiet(chiTiet) {
    _thoiGian = time(nullptr);
}

// Định dạng thời gian sang chuỗi "YYYY-MM-DD HH:MM:SS"
string Transaction::formatTime(const time_t& thoiGian) {
    char buf[80];
#ifdef _MSC_VER
    tm thoiGianInfo;
    // Sử dụng localtime_s an toàn hơn trong môi trường Windows
    localtime_s(&thoiGianInfo, &thoiGian);
#else
    tm thoiGianInfo = *localtime(&thoiGian);
#endif
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &thoiGianInfo);
    return string(buf);
}

void Transaction::hienThi() const {
    cout << "---------------------------------\n";
    cout << "Thoi gian: ";
    Utils::datMau(14); // Màu vàng cho thời gian
    cout << formatTime(this->_thoiGian) << endl;
    Utils::datMau(15);

    cout << "Loai GD:   ";
    // Đổi màu hiển thị theo loại giao dịch
    if (this->_strLoaiGiaoDich == "RUT_TIEN") Utils::datMau(12);
    else if (this->_strLoaiGiaoDich == "CHUYEN_TIEN") Utils::datMau(11);
    else if (this->_strLoaiGiaoDich == "NHAN_TIEN") Utils::datMau(10);
    cout << this->_strLoaiGiaoDich << endl;
    Utils::datMau(15);

    cout << "So tien:   ";
    Utils::datMau(11);
    cout << this->_lSoTien << " VND" << endl;
    Utils::datMau(15);

    if (!this->_strChiTiet.empty()) {
        cout << "Chi tiet:  ";
        Utils::datMau(14);
        cout << this->_strChiTiet << endl;
        Utils::datMau(15);
    }
}

// Ghi ra file LichSuID.txt
ostream& operator<<(ostream& out, const Transaction& gd) {
    string chiTietFile = gd._strChiTiet;
    // Thay thế khoảng trắng bằng dấu gạch dưới để đọc dễ hơn
    for (char& c : chiTietFile) {
        if (c == ' ') c = '_';
    }
    // Ghi KHONG nếu không có chi tiết
    if (chiTietFile.empty()) chiTietFile = "KHONG";

    // Format: ID Loai_GD SoTien ThoiGian ChiTiet
    out << gd._strIdTaiKhoan << " "
        << gd._strLoaiGiaoDich << " "
        << gd._lSoTien << " "
        << gd._thoiGian << " "
        << chiTietFile;
    return out;
}

// Đọc từ file LichSuID.txt
istream& operator>>(istream& in, Transaction& gd) {
    // Đọc theo format
    in >> gd._strIdTaiKhoan >> gd._strLoaiGiaoDich >> gd._lSoTien >> gd._thoiGian >> gd._strChiTiet;

    // Khôi phục lại chi tiết nếu là KHONG
    if (gd._strChiTiet == "KHONG") {
        gd._strChiTiet = "";
    } else {
        // Khôi phục lại khoảng trắng
        for (char& c : gd._strChiTiet) {
            if (c == '_') c = ' ';
        }
    }
    return in;
}