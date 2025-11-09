#include "BankProject/User/User.h"
#include "BankProject/FileIO/FileManager.h"
#include "BankProject/Core/Utils.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Constructor 1 tham so (da sua)
User::User(List<Card>* dsCard)
    : pDsCard(dsCard), pCurrentUserCard(nullptr) {}

void User::run() {
    if (!dangNhapUser()) {
        return;
    }

    taiLichSuVaTaiKhoanUser();

    if (!kiemTraPinLanDau()) {
        return;
    }

    int iLuaChon;
    while(true) {
        hienThiMenuUser();
        cout << "Chon chuc nang User: ";
        cin >> iLuaChon;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Utils::hienThiThongBao("Lua chon khong hop le.", true);
            continue;
        }

        switch(iLuaChon) {
            case 1: xemThongTinTaiKhoan(); break;
            case 2: rutTien(); break;
            case 3: chuyenTien(); break;
            case 4: xemNoiDungGiaoDich(); break;
            case 5: doiMaPin(); break;
            case 6:
                dangXuatUser();
                Utils::hienThiThongBao("Da dang xuat.", false);
                return;
            default: Utils::hienThiThongBao("Lua chon khong hop le.", true);
        }
    }
}

bool User::dangNhapUser() {
    Utils::hienThiHeader("DANG NHAP USER");
    string strId, strPin;

    cout << "ID (14 so): ";
    cin >> strId;
    cout << "PIN (6 so): ";
    strPin = Utils::nhapPassBiMat();

    pCurrentUserCard = pDsCard->timKiemTheoDieuKien(
        [&](const Card& tt){ return tt.layId() == strId; }
    );

    if (!pCurrentUserCard) {
        Utils::hienThiThongBao("ID khong ton tai.", true);
        return false;
    }

    if (pCurrentUserCard->biKhoa()) {
        Utils::hienThiThongBao("Tai khoan cua ban da bi khoa. Vui long lien he Admin.", true);
        pCurrentUserCard = nullptr;
        return false;
    }

    if (pCurrentUserCard->kiemTraPin(strPin)) {
        pCurrentUserCard->datLaiSoLanSai();
        luuDuLieuTheTu();
        Utils::hienThiThongBao("Dang nhap thanh cong!", false);
        return true;
    } else {
        pCurrentUserCard->tangSoLanSai();
        luuDuLieuTheTu();
        Utils::hienThiThongBao("PIN khong dung.", true);
        if(pCurrentUserCard->biKhoa()) {
            Utils::hienThiThongBao("Ban da nhap sai 3 lan. Tai khoan da bi khoa.", true);
        }
        pCurrentUserCard = nullptr;
        return false;
    }
}

void User::dangXuatUser() {
    pCurrentUserCard = nullptr;
    currentUserAccount = Account();
    currentUserHistory.clear();
}

void User::taiLichSuVaTaiKhoanUser() {
    if (!pCurrentUserCard) return;

    string id = pCurrentUserCard->layId();
    // Goi FileManager (da sua, khong can dataDir)
    if (!FileManager::docFileTaiKhoan(id, currentUserAccount)) {
        Utils::hienThiThongBao("Khong the tai thong tin tai khoan. File " + id + ".txt bi loi.", true);
        dangXuatUser();
        return;
    }
    currentUserHistory.clear();
    // Goi FileManager (da sua, khong can dataDir)
    FileManager::docFileLichSu(id, currentUserHistory);
}

void User::luuDuLieuTheTu() {
    // Su dung FILE_THETU da co duong dan day du
    if (!FileManager::ghiFileTheTu(FILE_THETU, *pDsCard)) {
        Utils::hienThiThongBao("Khong the luu thay doi vao TheTu.txt", true);
    }
}

void User::hienThiMenuUser() {
    Utils::hienThiHeader("MENU USER");
    Utils::datMau(10);
    cout << "Chao mung " << currentUserAccount.layTen() << "!\n\n";
    cout << "1. Xem thong tin tai khoan" << endl;
    cout << "2. Rut tien" << endl;
    cout << "3. Chuyen tien" << endl;
    cout << "4. Xem noi dung giao dich" << endl;
    cout << "5. Doi ma Pin" << endl;
    cout << "6. Dang xuat" << endl;
    Utils::datMau(15);
    cout << "--------------------------------------------------\n";
}

bool User::kiemTraPinLanDau() {
    if (pCurrentUserCard->layPin() == PIN_MAC_DINH) {
        Utils::hienThiThongBao("Day la lan dang nhap dau tien (hoac PIN mac dinh).", false);
        Utils::datMau(14);
        cout << "Ban PHAI doi ma PIN de tiep tuc.\n";
        Utils::datMau(15);
        Utils::dungManHinh();

        doiMaPin();

        if (pCurrentUserCard->layPin() == PIN_MAC_DINH) {
            Utils::hienThiThongBao("Ban da khong doi PIN. Dang xuat...", true);
            dangXuatUser();
            return false;
        } else {
            Utils::hienThiThongBao("Doi PIN thanh cong. Ban co the tiep tuc.", false);
            return true;
        }
    }
    return true;
}

void User::xemThongTinTaiKhoan() {
    Utils::hienThiHeader("THONG TIN TAI KHOAN");
    Utils::datMau(11);
    cout << "So tai khoan: " << currentUserAccount.layId() << endl;
    cout << "Ten chu khoan: " << currentUserAccount.layTen() << endl;
    cout << "So du:          " << currentUserAccount.laySoDu() << " " << currentUserAccount.layLoaiTien() << endl;
    Utils::datMau(15);
    Utils::dungManHinh();
}

void User::rutTien() {
    Utils::hienThiHeader("RUT TIEN");
    long long lSoTienCanRut;

    Utils::datMau(11);
    cout << "So du hien tai: " << currentUserAccount.laySoDu() << " VND\n";
    Utils::datMau(14);
    cout << "Luu y: So tien rut phai >= 50000, la boi so cua 50000,\n";
    cout << "va so du con lai phai >= 50000.\n\n";
    Utils::datMau(15);

    cout << "Nhap so tien can rut: ";
    cin >> lSoTienCanRut;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Utils::hienThiThongBao("So tien khong hop le.", true);
        return;
    }

    if (lSoTienCanRut < 50000) {
        Utils::hienThiThongBao("So tien rut phai >= 50000 VND.", true);
        return;
    }
    if (lSoTienCanRut % 50000 != 0) {
        Utils::hienThiThongBao("So tien rut phai la boi so cua 50000 VND.", true);
        return;
    }
    if (currentUserAccount.laySoDu() - lSoTienCanRut < 50000) {
        Utils::hienThiThongBao("So du khong du (phai con lai 50000 VND).", true);
        return;
    }

    currentUserAccount.rutTien(lSoTienCanRut);

    FileManager::ghiFileTaiKhoan(pCurrentUserCard->layId(), currentUserAccount);

    Transaction gd(pCurrentUserCard->layId(), "RUT_TIEN", lSoTienCanRut, "");
    currentUserHistory.them(gd);
    FileManager::ghiThemLichSu(pCurrentUserCard->layId(), gd);

    Utils::hienThiThongBao("Rut tien thanh cong! So du moi: " + to_string(currentUserAccount.laySoDu()), false);
}

void User::chuyenTien() {
    Utils::hienThiHeader("CHUYEN TIEN");
    string strIdNhan;
    long long lSoTienCanChuyen;

    Utils::datMau(11);
    cout << "So du hien tai: " << currentUserAccount.laySoDu() << " VND\n";
    Utils::datMau(15);
    cout << "Nhap ID tai khoan nhan: ";
    cin >> strIdNhan;

    if (strIdNhan == pCurrentUserCard->layId()) {
        Utils::hienThiThongBao("Ban khong the tu chuyen cho chinh minh.", true);
        return;
    }

    Card* theNhan = pDsCard->timKiemTheoDieuKien(
        [&](const Card& tt){ return tt.layId() == strIdNhan; }
    );

    if (!theNhan) {
        Utils::hienThiThongBao("ID tai khoan nhan khong ton tai trong he thong.", true);
        return;
    }

    Account tkNhan;
    if (!FileManager::docFileTaiKhoan(strIdNhan, tkNhan)) {
        Utils::hienThiThongBao("Loi khi doc thong tin tai khoan nhan.", true);
        return;
    }

    Utils::datMau(11);
    cout << "Chuyen den: " << tkNhan.layTen() << " - " << strIdNhan << endl;
    Utils::datMau(15);

    cout << "Nhap so tien can chuyen: ";
    cin >> lSoTienCanChuyen;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Utils::hienThiThongBao("So tien khong hop le.", true);
        return;
    }

    if (lSoTienCanChuyen < 50000) {
        Utils::hienThiThongBao("So tien chuyen phai >= 50000 VND.", true);
        return;
    }
    if (lSoTienCanChuyen % 50000 != 0) {
        Utils::hienThiThongBao("So tien chuyen phai la boi so cua 50000 VND.", true);
        return;
    }
    if (currentUserAccount.laySoDu() - lSoTienCanChuyen < 50000) {
        Utils::hienThiThongBao("So du khong du (phai con lai 50000 VND).", true);
        return;
    }

    char cXacNhan;
    Utils::datMau(14);
    cout << "Xac nhan chuyen " << lSoTienCanChuyen << " VND den " << tkNhan.layTen() << "? (y/n): ";
    Utils::datMau(15);
    cin >> cXacNhan;

    if (cXacNhan != 'y' && cXacNhan != 'Y') {
        Utils::hienThiThongBao("Da huy giao dich chuyen tien.", false);
        return;
    }

    currentUserAccount.rutTien(lSoTienCanChuyen);
    FileManager::ghiFileTaiKhoan(pCurrentUserCard->layId(), currentUserAccount);

    Account tkNhanMoi;
    FileManager::docFileTaiKhoan(strIdNhan, tkNhanMoi);
    tkNhanMoi.napTien(lSoTienCanChuyen);
    FileManager::ghiFileTaiKhoan(strIdNhan, tkNhanMoi);

    string chiTietChuyen = "Chuyen den " + strIdNhan + " (" + tkNhan.layTen() + ")";
    Transaction gdChuyen(pCurrentUserCard->layId(), "CHUYEN_TIEN", lSoTienCanChuyen, chiTietChuyen);
    currentUserHistory.them(gdChuyen);
    FileManager::ghiThemLichSu(pCurrentUserCard->layId(), gdChuyen);

    string chiTietNhan = "Nhan tu " + pCurrentUserCard->layId() + " (" + currentUserAccount.layTen() + ")";
    Transaction gdNhan(strIdNhan, "NHAN_TIEN", lSoTienCanChuyen, chiTietNhan);
    FileManager::ghiThemLichSu(strIdNhan, gdNhan);

    Utils::hienThiThongBao("Chuyen tien thanh cong!", false);
}

void User::xemNoiDungGiaoDich() {
    Utils::hienThiHeader("LICH SU GIAO DICH");

    if (currentUserHistory.layKichThuoc() == 0) {
        cout << "Khong co giao dich nao." << endl;
    } else {
        Utils::datMau(14);
        currentUserHistory.lapQua([](const Transaction& gd){
            gd.hienThi();
        });
        Utils::datMau(15);
    }

    Utils::dungManHinh();
}

void User::doiMaPin() {
    Utils::hienThiHeader("DOI MA PIN");
    string strPinCu, strPinMoi1, strPinMoi2;

    if (pCurrentUserCard->layPin() != PIN_MAC_DINH) {
        cout << "Nhap ma PIN cu: ";
        strPinCu = Utils::nhapPassBiMat();
        if (!pCurrentUserCard->kiemTraPin(strPinCu)) {
            Utils::hienThiThongBao("Ma PIN cu khong dung.", true);
            return;
        }
    } else {
        cout << "Ban dang su dung PIN mac dinh. Vui long tao PIN moi.\n";
    }

    cout << "Nhap ma PIN moi (6 so): ";
    strPinMoi1 = Utils::nhapPassBiMat();

    if (strPinMoi1.length() != 6) {
        Utils::hienThiThongBao("Ma PIN moi phai co dung 6 so.", true);
        return;
    }

    if (strPinMoi1 == PIN_MAC_DINH) {
        Utils::hienThiThongBao("Ma PIN moi khong duoc trung voi PIN mac dinh.", true);
        return;
    }

    if (pCurrentUserCard->kiemTraPin(strPinMoi1)) {
        Utils::hienThiThongBao("Ma PIN moi khong duoc trung voi PIN cu.", true);
        return;
    }

    cout << "Nhap lai ma PIN moi: ";
    strPinMoi2 = Utils::nhapPassBiMat();

    if (strPinMoi1 != strPinMoi2) {
        Utils::hienThiThongBao("Ma PIN nhap lai khong khop.", true);
        return;
    }

    pCurrentUserCard->doiPin(strPinMoi1);
    luuDuLieuTheTu();
    
    Utils::hienThiThongBao("Doi ma PIN thanh cong!", false);
}
