#include "BankProject/User/User.h"
#include "BankProject/FileIO/FileManager.h"
#include "BankProject/Core/Utils.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

User::User(List<Card>* dsCard)
    : _pDsCard(dsCard), _pCurrentUserCard(nullptr) {}

void User::run() {
    if (!this->dangNhapUser()) {
        return;
    }

    this->taiLichSuVaTaiKhoanUser();

    if (!this->kiemTraPinLanDau()) {
        return;
    }

    int iLuaChon;
    while(true) {
        this->hienThiMenuUser();
        cout << "Chon chuc nang User: ";
        cin >> iLuaChon;

        if (cin.fail()) {
            // Xử lý khi người dùng nhập ký tự thay vì số
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Utils::hienThiThongBao("Lua chon khong hop le.", true);
            continue;
        }

        switch(iLuaChon) {
            case 1: this->xemThongTinTaiKhoan(); break;
            case 2: this->rutTien(); break;
            case 3: this->chuyenTien(); break;
            case 4: this->xemNoiDungGiaoDich(); break;
            case 5: this->doiMaPin(); break;
            case 6:
                this->dangXuatUser();
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

    // Tìm kiếm Card trong danh sách thẻ
    this->_pCurrentUserCard = this->_pDsCard->timKiemTheoDieuKien(
        [&](const Card& tt){ return tt.layId() == strId; }
    );

    if (!this->_pCurrentUserCard) {
        Utils::hienThiThongBao("ID khong ton tai.", true);
        return false;
    }

    if (this->_pCurrentUserCard->biKhoa()) {
        Utils::hienThiThongBao("Tai khoan cua ban da bi khoa. Vui long lien he Admin.", true);
        this->_pCurrentUserCard = nullptr;
        return false;
    }

    if (this->_pCurrentUserCard->kiemTraPin(strPin)) {
        this->_pCurrentUserCard->datLaiSoLanSai(); // Đặt lại số lần sai PIN về 0
        this->luuDuLieuTheTu();
        Utils::hienThiThongBao("Dang nhap thanh cong!", false);
        return true;
    } else {
        this->_pCurrentUserCard->tangSoLanSai(); // Tăng số lần sai
        this->luuDuLieuTheTu();
        Utils::hienThiThongBao("PIN khong dung.", true);
        if(this->_pCurrentUserCard->biKhoa()) {
            Utils::hienThiThongBao("Ban da nhap sai 3 lan. Tai khoan da bi khoa.", true);
        }
        this->_pCurrentUserCard = nullptr;
        return false;
    }
}

void User::dangXuatUser() {
    this->_pCurrentUserCard = nullptr;
    this->_currentUserAccount = Account();
    this->_currentUserHistory.clear();
}

void User::taiLichSuVaTaiKhoanUser() {
    if (!this->_pCurrentUserCard) return;

    string id = this->_pCurrentUserCard->layId();
    // Tải thông tin tài khoản từ file [ID].txt
    if (!FileManager::docFileTaiKhoan(id, this->_currentUserAccount)) {
        Utils::hienThiThongBao("Khong the tai thong tin tai khoan. File " + id + ".txt bi loi.", true);
        this->dangXuatUser();
        return;
    }
    this->_currentUserHistory.clear();
    // Tải lịch sử giao dịch từ file [LichSuID].txt
    FileManager::docFileLichSu(id, this->_currentUserHistory);
}

void User::luuDuLieuTheTu() {
    // Ghi lại toàn bộ danh sách thẻ vào TheTu.txt
    if (!FileManager::ghiFileTheTu(FILE_CARD_LIST, *this->_pDsCard)) {
        Utils::hienThiThongBao("Khong the luu thay doi vao TheTu.txt", true);
    }
}

void User::hienThiMenuUser() {
    Utils::hienThiHeader("MENU USER");
    Utils::datMau(10);
    cout << "Chao mung " << this->_currentUserAccount.layTen() << "!\n\n";
    cout << "1. Xem thong tin tai khoan" << endl;
    cout << "2. Rut tien" << endl;
    cout << "3. Chuyen tien" << endl;
    cout << "4. Xem noi dung giao dich" << endl;
    cout << "5. Doi ma Pin" << endl;
    cout << "6. Dang xuat" << endl;
    Utils::datMau(15);
    cout << "**************************************************\n";
}

bool User::kiemTraPinLanDau() {
    // Kiểm tra nếu đang sử dụng PIN mặc định (lan dau dang nhap)
    if (this->_pCurrentUserCard->layPin() == PIN_DEFAULT) {
        Utils::hienThiThongBao("Day la lan dang nhap dau tien (hoac PIN mac dinh).", false);
        Utils::datMau(14);
        cout << "Ban PHAI doi ma PIN de tiep tuc.\n";
        Utils::datMau(15);
        Utils::dungManHinh();

        this->doiMaPin();

        // Kiểm tra lại sau khi đổi PIN, nếu vẫn là PIN mặc định thì bắt buộc thoát
        if (this->_pCurrentUserCard->layPin() == PIN_DEFAULT) {
            Utils::hienThiThongBao("Ban da khong doi PIN. Dang xuat...", true);
            this->dangXuatUser();
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
    cout << "So tai khoan: " << this->_currentUserAccount.layId() << endl;
    cout << "Ten chu khoan: " << this->_currentUserAccount.layTen() << endl;
    cout << "So du:          " << this->_currentUserAccount.laySoDu() << " " << this->_currentUserAccount.layLoaiTien() << endl;
    Utils::datMau(15);
    Utils::dungManHinh();
}

void User::rutTien() {
    Utils::hienThiHeader("RUT TIEN");
    long long lSoTienCanRut;

    Utils::datMau(11);
    cout << "So du hien tai: " << this->_currentUserAccount.laySoDu() << " VND\n";
    Utils::datMau(14);
    cout << "Luu y: So tien rut phai >= 50000, la boi so cua 50000,\n";
    cout << "va so du con lai phai >= 50000.\n\n";
    Utils::datMau(15);

    cout << "Nhap so tien can rut: ";
    
    // Kiểm tra đầu vào hợp lệ (là số)
    if (!(cin >> lSoTienCanRut)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Utils::hienThiThongBao("So tien khong hop le.", true);
        return;
    }

    // Ràng buộc 1: So tien rut phai >= 50000 VND
    if (lSoTienCanRut < 50000) {
        Utils::hienThiThongBao("So tien rut phai >= 50000 VND.", true);
        return;
    }
    // Ràng buộc 2: la boi so cua 50000 VND
    if (lSoTienCanRut % 50000 != 0) {
        Utils::hienThiThongBao("So tien rut phai la boi so cua 50000 VND.", true);
        return;
    }
    // Ràng buộc 3: So du con lai phai >= 50000 VND
    if (this->_currentUserAccount.laySoDu() - lSoTienCanRut < 50000) {
        Utils::hienThiThongBao("So du khong du (phai con lai 50000 VND).", true);
        return;
    }

    this->_currentUserAccount.rutTien(lSoTienCanRut);

    // Cập nhật file tài khoản [ID].txt
    FileManager::ghiFileTaiKhoan(this->_pCurrentUserCard->layId(), this->_currentUserAccount);

    // Ghi lịch sử giao dịch
    Transaction gd(this->_pCurrentUserCard->layId(), "RUT_TIEN", lSoTienCanRut, "");
    this->_currentUserHistory.them(gd);
    FileManager::ghiThemLichSu(this->_pCurrentUserCard->layId(), gd);

    Utils::hienThiThongBao("Rut tien thanh cong! So du moi: " + to_string(this->_currentUserAccount.laySoDu()), false);
}

void User::chuyenTien() {
    Utils::hienThiHeader("CHUYEN TIEN");
    string strIdNhan;
    long long lSoTienCanChuyen;

    Utils::datMau(11);
    cout << "So du hien tai: " << this->_currentUserAccount.laySoDu() << " VND\n";
    Utils::datMau(15);
    cout << "Nhap ID tai khoan nhan: ";
    cin >> strIdNhan;

    // Ràng buộc: Không tự chuyển cho mình
    if (strIdNhan == this->_pCurrentUserCard->layId()) {
        Utils::hienThiThongBao("Ban khong the tu chuyen cho chinh minh.", true);
        return;
    }

    // Ràng buộc: Tài khoản nhận phải tồn tại trong danh sách thẻ
    Card* theNhan = this->_pDsCard->timKiemTheoDieuKien(
        [&](const Card& tt){ return tt.layId() == strIdNhan; }
    );

    if (!theNhan) {
        Utils::hienThiThongBao("ID tai khoan nhan khong ton tai trong he thong.", true);
        return;
    }

    Account tkNhan;
    // Đọc thông tin TK nhận để hiển thị tên xác nhận
    if (!FileManager::docFileTaiKhoan(strIdNhan, tkNhan)) {
        Utils::hienThiThongBao("Loi khi doc thong tin tai khoan nhan.", true);
        return;
    }

    Utils::datMau(11);
    cout << "Chuyen den: " << tkNhan.layTen() << " - " << strIdNhan << endl;
    Utils::datMau(15);

    cout << "Nhap so tien can chuyen: ";
    
    // Kiểm tra đầu vào hợp lệ (là số)
    if (!(cin >> lSoTienCanChuyen)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Utils::hienThiThongBao("So tien khong hop le.", true);
        return;
    }

    // Ràng buộc 1: So tien chuyen phai >= 50000 VND
    if (lSoTienCanChuyen < 50000) {
        Utils::hienThiThongBao("So tien chuyen phai >= 50000 VND.", true);
        return;
    }
    // Ràng buộc 2: la boi so cua 50000 VND
    if (lSoTienCanChuyen % 50000 != 0) {
        Utils::hienThiThongBao("So tien chuyen phai la boi so cua 50000 VND.", true);
        return;
    }
    // Ràng buộc 3: So du con lai phai >= 50000 VND
    if (this->_currentUserAccount.laySoDu() - lSoTienCanChuyen < 50000) {
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

    // 1. Cập nhật tài khoản GỬI và ghi file
    this->_currentUserAccount.rutTien(lSoTienCanChuyen);
    FileManager::ghiFileTaiKhoan(this->_pCurrentUserCard->layId(), this->_currentUserAccount);

    // 2. Cập nhật tài khoản NHẬN (Đọc lại để đảm bảo dữ liệu mới nhất)
    Account tkNhanMoi;
    FileManager::docFileTaiKhoan(strIdNhan, tkNhanMoi);
    tkNhanMoi.napTien(lSoTienCanChuyen);
    FileManager::ghiFileTaiKhoan(strIdNhan, tkNhanMoi);

    // 3. Ghi lịch sử giao dịch GỬI (CHUYEN_TIEN)
    string chiTietChuyen = "Chuyen den " + strIdNhan + " (" + tkNhan.layTen() + ")";
    Transaction gdChuyen(this->_pCurrentUserCard->layId(), "CHUYEN_TIEN", lSoTienCanChuyen, chiTietChuyen);
    this->_currentUserHistory.them(gdChuyen);
    FileManager::ghiThemLichSu(this->_pCurrentUserCard->layId(), gdChuyen);

    // 4. Ghi lịch sử giao dịch NHẬN (NHAN_TIEN)
    string chiTietNhan = "Nhan tu " + this->_pCurrentUserCard->layId() + " (" + this->_currentUserAccount.layTen() + ")";
    Transaction gdNhan(strIdNhan, "NHAN_TIEN", lSoTienCanChuyen, chiTietNhan);
    FileManager::ghiThemLichSu(strIdNhan, gdNhan);

    Utils::hienThiThongBao("Chuyen tien thanh cong!", false);
}

void User::xemNoiDungGiaoDich() {
    Utils::hienThiHeader("LICH SU GIAO DICH");

    if (this->_currentUserHistory.layKichThuoc() == 0) {
        cout << "Khong co giao dich nao." << endl;
    } else {
        Utils::datMau(14);
        // Lặp qua danh sách lịch sử và hiển thị chi tiết từng giao dịch
        this->_currentUserHistory.lapQua([](const Transaction& gd){
            gd.hienThi();
        });
        Utils::datMau(15);
    }

    Utils::dungManHinh();
}

void User::doiMaPin() {
    Utils::hienThiHeader("DOI MA PIN");
    string strPinCu, strPinMoi1, strPinMoi2;

    // Yêu cầu nhập PIN cũ nếu không phải là PIN mặc định
    if (this->_pCurrentUserCard->layPin() != PIN_DEFAULT) {
        cout << "Nhap ma PIN cu: ";
        strPinCu = Utils::nhapPassBiMat();
        if (!this->_pCurrentUserCard->kiemTraPin(strPinCu)) {
            Utils::hienThiThongBao("Ma PIN cu khong dung.", true);
            return;
        }
    } else {
        cout << "Ban dang su dung PIN mac dinh. Vui long tao PIN moi.\n";
    }

    cout << "Nhap ma PIN moi (6 so): ";
    strPinMoi1 = Utils::nhapPassBiMat();

    // Ràng buộc 1: PIN mới phải có đúng 6 số
    if (strPinMoi1.length() != 6) {
        Utils::hienThiThongBao("Ma PIN moi phai co dung 6 so.", true);
        return;
    }

    // Ràng buộc 2: PIN mới không được trùng PIN mặc định
    if (strPinMoi1 == PIN_DEFAULT) {
        Utils::hienThiThongBao("Ma PIN moi khong duoc trung voi PIN mac dinh.", true);
        return;
    }

    // Ràng buộc 3: PIN mới không được trùng PIN cũ
    if (this->_pCurrentUserCard->kiemTraPin(strPinMoi1)) {
        Utils::hienThiThongBao("Ma PIN moi khong duoc trung voi PIN cu.", true);
        return;
    }

    cout << "Nhap lai ma PIN moi: ";
    strPinMoi2 = Utils::nhapPassBiMat();

    // Ràng buộc 4: Nhập lại PIN mới phải khớp
    if (strPinMoi1 != strPinMoi2) {
        Utils::hienThiThongBao("Ma PIN nhap lai khong khop.", true);
        return;
    }

    this->_pCurrentUserCard->doiPin(strPinMoi1);
    this->luuDuLieuTheTu();
    
    Utils::hienThiThongBao("Doi ma PIN thanh cong!", false);
}