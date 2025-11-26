#include "BankProject/Admin/Admin.h"
#include "BankProject/FileIO/FileManager.h"
#include "BankProject/Core/Utils.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// --- Triển khai LOP DU LIEU AdminAccount ---

AdminAccount::AdminAccount(string user, string pass)
    : _strUser(user), _strPass(pass) {}

string AdminAccount::layUser() const {
    return _strUser;
}

bool AdminAccount::kiemTraPass(const string& pass) const {
    return _strPass == pass;
}

istream& operator>>(istream& in, AdminAccount& ad) {
    // Đọc User và Pass từ file
    in >> ad._strUser >> ad._strPass;
    return in;
}

ostream& operator<<(ostream& out, const AdminAccount& ad) {
    out << ad._strUser << " " << ad._strPass;
    return out;
}


// --- Triển khai LOP LOGIC Admin ---

Admin::Admin(List<AdminAccount>* dsAdmin, List<Card>* dsCard)
    : _pDsAdmin(dsAdmin), _pDsCard(dsCard) {}

void Admin::run() {
    Utils::hienThiHeader("DANG NHAP ADMIN");
    string strUser, strPass;

    cout << "User: ";
    cin >> strUser;
    cout << "Pass: ";
    strPass = Utils::nhapPassBiMat(); // Nhập mật khẩu ẩn

    // Tìm kiếm tài khoản Admin theo username
    AdminAccount* admin = this->_pDsAdmin->timKiemTheoDieuKien(
        [&](const AdminAccount& ad){ return ad.layUser() == strUser; }
    );

    if (admin && admin->kiemTraPass(strPass)) {
        Utils::hienThiThongBao("Dang nhap Admin thanh cong!", false);

        int iLuaChon;
        while(true) {
            this->hienThiMenuAdmin();
            cout << "Chon chuc nang Admin: ";
            cin >> iLuaChon;

            if (cin.fail()) {
                // Xử lý khi người dùng nhập ký tự thay vì số
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Utils::hienThiThongBao("Lua chon khong hop le.", true);
                continue;
            }

            switch(iLuaChon) {
                case 1: this->xemDanhSachTaiKhoan(); break;
                case 2: this->themTaiKhoan(); break;
                case 3: this->xoaTaiKhoan(); break;
                case 4: this->moKhoaTaiKhoan(); break;
                case 5:
                    Utils::hienThiThongBao("Da dang xuat Admin.", false);
                    return;
                default: Utils::hienThiThongBao("Lua chon khong hop le.", true);
            }
        }
    } else {
        Utils::hienThiThongBao("User hoac Pass khong dung.", true);
    }
}

void Admin::hienThiMenuAdmin() {
    Utils::hienThiHeader("MENU ADMIN");
    Utils::datMau(10);
    cout << "1. Xem danh sach tai khoan" << endl;
    cout << "2. Them tai khoan moi" << endl;
    cout << "3. Xoa tai khoan" << endl;
    cout << "4. Mo khoa tai khoan" << endl;
    cout << "5. Dang xuat (Quay lai menu chinh)" << endl;
    Utils::datMau(15);
    cout << "**************************************************\n";
}

void Admin::xemDanhSachTaiKhoan() {
    Utils::hienThiHeader("DANH SACH TAI KHOAN");

    Utils::datMau(14);
    // Thiết lập định dạng header
    cout << left
              << setw(16) << "ID"
              << setw(8) << "PIN"
              << setw(8) << "KHOA"
              << setw(5) << "SAI" << endl;
    Utils::datMau(15);
    cout << "-----------------------------------------------\n";

    // Lặp qua danh sách Card và hiển thị thông tin
    this->_pDsCard->lapQua([](const Card& tt) {
        cout << left
                  << setw(16) << tt.layId()
                  << setw(8) << "******" // PIN không hiển thị
                  << setw(8) << (tt.biKhoa() ? "CO" : "KHONG")
                  << setw(5) << tt.laySoLanSai() << endl;
    });

    Utils::dungManHinh();
}

void Admin::themTaiKhoan() {
    Utils::hienThiHeader("THEM TAI KHOAN MOI");
    string strId, strTen;
    long long lSoDuBanDau = 50000;

    cout << "Nhap ID moi (14 so): ";
    cin >> strId;

    // Ràng buộc: ID phải có đúng 14 số
    if (strId.length() != 14) {
        Utils::hienThiThongBao("ID phai co dung 14 so.", true);
        return;
    }

    // Ràng buộc: ID không được trùng
    if (this->_pDsCard->timKiemTheoDieuKien([&](const Card& tt){ return tt.layId() == strId; })) {
        Utils::hienThiThongBao("ID nay da ton tai.", true);
        return;
    }

    // Xóa bộ đệm trước khi dùng getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nhap ten chu tai khoan: ";
    getline(cin, strTen);

    cout << "Nhap so du ban dau (toi thieu 50000): ";

    // Kiểm tra tính hợp lệ và ràng buộc số dư ban đầu
    if (!(cin >> lSoDuBanDau) || lSoDuBanDau < 50000) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         lSoDuBanDau = 50000;
         Utils::hienThiThongBao("So du khong hop le/khong du. Dat mac dinh la 50000.", true);
    }

    // Tạo Card mới với PIN mặc định
    Card theMoi(strId, PIN_DEFAULT, false, 0);
    this->_pDsCard->them(theMoi);

    // Tạo file tài khoản [ID].txt
    if (!FileManager::taoFileTaiKhoanMoi(strId, strTen, lSoDuBanDau)) {
        Utils::hienThiThongBao("Loi: Khong tao duoc file tai khoan. Xoa the khoi bo nho.", true);
        this->_pDsCard->xoaTheoDieuKien([&](const Card& tt){ return tt.layId() == strId; });
        return;
    }

    // Tạo file lịch sử [LichSuID].txt
    if (!FileManager::taoFileLichSuMoi(strId)) {
        Utils::hienThiThongBao("Loi: Khong tao duoc file lich su. Xoa the khoi bo nho.", true);
        this->_pDsCard->xoaTheoDieuKien([&](const Card& tt){ return tt.layId() == strId; });
        FileManager::xoaFileTaiKhoan(strId);
        return;
    }

    // Ghi lại toàn bộ danh sách thẻ vào TheTu.txt
    FileManager::ghiFileTheTu(FILE_CARD_LIST, *this->_pDsCard);

    Utils::hienThiThongBao("Them tai khoan moi thanh cong!", false);
}

void Admin::xoaTaiKhoan() {
    Utils::hienThiHeader("XOA TAI KHOAN");
    string strId;
    cout << "Nhap ID tai khoan can xoa: ";
    cin >> strId;

    Card* theCanXoa = this->_pDsCard->timKiemTheoDieuKien(
        [&](const Card& tt){ return tt.layId() == strId; }
    );

    if (!theCanXoa) {
        Utils::hienThiThongBao("Khong tim thay ID tai khoan.", true);
        return;
    }

    char cXacNhan;
    Utils::datMau(12); // Dùng màu đỏ cho thông báo quan trọng
    cout << "Ban co chac chan muon xoa tai khoan " << strId << "? (y/n): ";
    Utils::datMau(15);
    cin >> cXacNhan;

    if (cXacNhan != 'y' && cXacNhan != 'Y') {
        Utils::hienThiThongBao("Da huy thao tac xoa.", false);
        return;
    }

    // Xóa file dữ liệu
    FileManager::xoaFileTaiKhoan(strId);
    FileManager::xoaFileLichSu(strId);
    // Xóa khỏi danh sách trong bộ nhớ và cập nhật file TheTu.txt
    this->_pDsCard->xoaTheoDieuKien([&](const Card& tt){ return tt.layId() == strId; });
    FileManager::ghiFileTheTu(FILE_CARD_LIST, *this->_pDsCard);

    Utils::hienThiThongBao("Xoa tai khoan thanh cong!", false);
}

void Admin::moKhoaTaiKhoan() {
    Utils::hienThiHeader("MO KHOA TAI KHOAN");
    string strId;
    cout << "Nhap ID tai khoan can mo khoa: ";
    cin >> strId;

    Card* theCanMo = this->_pDsCard->timKiemTheoDieuKien(
        [&](const Card& tt){ return tt.layId() == strId; }
    );

    if (!theCanMo) {
        Utils::hienThiThongBao("Khong tim thay ID tai khoan.", true);
        return;
    }

    if (!theCanMo->biKhoa()) {
        Utils::hienThiThongBao("Tai khoan nay khong bi khoa.", false);
        return;
    }

    theCanMo->moKhoaThe(); // Thực hiện mở khóa và đặt lại số lần sai
    FileManager::ghiFileTheTu(FILE_CARD_LIST, *this->_pDsCard); // Cập nhật file TheTu.txt

    Utils::hienThiThongBao("Mo khoa tai khoan thanh cong!", false);
}