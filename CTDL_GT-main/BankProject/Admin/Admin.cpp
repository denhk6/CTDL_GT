// --- SỬA Ở ĐÂY --- (Thêm lại BankProject/)
#include "BankProject/Admin/Admin.h"
#include "BankProject/FileIO/FileManager.h"
#include "BankProject/Core/Utils.h"
#include <iostream>
#include <string>
#include <iomanip> 
#include <limits>  

using namespace std;

// --- Phan LOP DU LIEU AdminAccount ---

AdminAccount::AdminAccount(string user, string pass) 
    : strUser(user), strPass(pass) {}

string AdminAccount::layUser() const {
    return strUser;
}

bool AdminAccount::kiemTraPass(const string& pass) const {
    return strPass == pass;
}

istream& operator>>(istream& in, AdminAccount& ad) {
    in >> ad.strUser >> ad.strPass;
    return in;
}

ostream& operator<<(ostream& out, const AdminAccount& ad) {
    out << ad.strUser << " " << ad.strPass;
    return out;
}


// --- Phan LOP LOGIC Admin ---

// --- SỬA Ở ĐÂY --- (Xóa dataDir)
Admin::Admin(List<AdminAccount>* dsAdmin, List<Card>* dsCard)
    : pDsAdmin(dsAdmin), pDsCard(dsCard) {} 

void Admin::run() {
    Utils::hienThiHeader("DANG NHAP ADMIN");
    string strUser, strPass;
    
    cout << "User: ";
    cin >> strUser;
    cout << "Pass: ";
    strPass = Utils::nhapPassBiMat(); 

    AdminAccount* admin = pDsAdmin->timKiemTheoDieuKien(
        [&](const AdminAccount& ad){ return ad.layUser() == strUser; }
    );
    
    if (admin && admin->kiemTraPass(strPass)) {
        Utils::hienThiThongBao("Dang nhap Admin thanh cong!", false);
        
        int iLuaChon;
        while(true) {
            hienThiMenuAdmin();
            cout << "Chon chuc nang Admin: ";
            cin >> iLuaChon;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Utils::hienThiThongBao("Lua chon khong hop le.", true);
                continue;
            }

            switch(iLuaChon) {
                case 1: xemDanhSachTaiKhoan(); break;
                case 2: themTaiKhoan(); break;
                case 3: xoaTaiKhoan(); break;
                case 4: moKhoaTaiKhoan(); break;
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
    cout << "--------------------------------------------------\n";
}

void Admin::xemDanhSachTaiKhoan() {
    Utils::hienThiHeader("DANH SACH TAI KHOAN");
    
    Utils::datMau(14); 
    cout << left
              << setw(16) << "ID" 
              << setw(8) << "PIN" 
              << setw(8) << "KHOA"
              << setw(5) << "SAI" << endl;
    Utils::datMau(15); 
    cout << "-----------------------------------------------\n";

    pDsCard->lapQua([](const Card& tt) {
        cout << left
                  << setw(16) << tt.layId()
                  << setw(8) << "******" 
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
    
    if (strId.length() != 14) {
        Utils::hienThiThongBao("ID phai co dung 14 so.", true);
        return;
    }
    
    if (pDsCard->timKiemTheoDieuKien([&](const Card& tt){ return tt.layId() == strId; })) {
        Utils::hienThiThongBao("ID nay da ton tai.", true);
        return;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Nhap ten chu tai khoan: ";
    getline(cin, strTen);
    
    cout << "Nhap so du ban dau (mac dinh 50000): ";
    cin >> lSoDuBanDau;
    if (cin.fail() || lSoDuBanDau < 50000) {
        lSoDuBanDau = 50000;
        cout << "So du khong hop le, dat mac dinh la 50000." << endl;
    }

    Card theMoi(strId, PIN_MAC_DINH, false, 0);
    pDsCard->them(theMoi);
    
    if (!FileManager::taoFileTaiKhoanMoi(strId, strTen, lSoDuBanDau)) {
        Utils::hienThiThongBao("Loi: Khong tao duoc file tai khoan.", true);
        pDsCard->xoaTheoDieuKien([&](const Card& tt){ return tt.layId() == strId; });
        return;
    }
    
    if (!FileManager::taoFileLichSuMoi(strId)) {
        Utils::hienThiThongBao("Loi: Khong tao duoc file lich su.", true);
        pDsCard->xoaTheoDieuKien([&](const Card& tt){ return tt.layId() == strId; });
        FileManager::xoaFileTaiKhoan(strId);
        return;
    }
    
    FileManager::ghiFileTheTu(FILE_THETU, *pDsCard);
    
    Utils::hienThiThongBao("Them tai khoan moi thanh cong!", false);
}

void Admin::xoaTaiKhoan() {
    Utils::hienThiHeader("XOA TAI KHOAN");
    string strId;
    cout << "Nhap ID tai khoan can xoa: ";
    cin >> strId;

    Card* theCanXoa = pDsCard->timKiemTheoDieuKien(
        [&](const Card& tt){ return tt.layId() == strId; }
    );

    if (!theCanXoa) {
        Utils::hienThiThongBao("Khong tim thay ID tai khoan.", true);
        return;
    }
    
    char cXacNhan;
    Utils::datMau(12); 
    cout << "Ban co chac chan muon xoa tai khoan " << strId << "? (y/n): ";
    Utils::datMau(15);
    cin >> cXacNhan;
    
    if (cXacNhan != 'y' && cXacNhan != 'Y') {
        Utils::hienThiThongBao("Da huy thao tac xoa.", false);
        return;
    }

    FileManager::xoaFileTaiKhoan(strId);
    FileManager::xoaFileLichSu(strId);
    pDsCard->xoaTheoDieuKien([&](const Card& tt){ return tt.layId() == strId; });
    FileManager::ghiFileTheTu(FILE_THETU, *pDsCard);

    Utils::hienThiThongBao("Xoa tai khoan thanh cong!", false);
}

void Admin::moKhoaTaiKhoan() {
    Utils::hienThiHeader("MO KHOA TAI KHOAN");
    string strId;
    cout << "Nhap ID tai khoan can mo khoa: ";
    cin >> strId;
    
    Card* theCanMo = pDsCard->timKiemTheoDieuKien(
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
    
    theCanMo->moKhoaThe(); 
    FileManager::ghiFileTheTu(FILE_THETU, *pDsCard); 
    
    Utils::hienThiThongBao("Mo khoa tai khoan thanh cong!", false);
}