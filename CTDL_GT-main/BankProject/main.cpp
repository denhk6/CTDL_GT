#include <iostream>
#include <string>
#include <limits>
#include <clocale> // Cho setlocale

#include "BankProject/Core/List.h"
#include "BankProject/Core/Card.h"
#include "BankProject/Admin/Admin.h"
#include "BankProject/User/User.h"
#include "BankProject/FileIO/FileManager.h"
#include "BankProject/Core/Utils.h"

using namespace std;

int main() {
    // Thiet lap locale va console
    setlocale(LC_ALL, "");
    Utils::thietLapConsole();

    // Tao cac danh sach chinh de quan ly du lieu
    List<AdminAccount> dsAdmin;
    List<Card> dsCard;

    // Duong dan phai la "BankProject/Data/"
    // vi Working Directory cua chung ta la $PROJECT_DIR$
    const string dataDir = "BankProject/Data/";

    Utils::datMau(15);
    cout << "Dang tai du lieu he thong..." << endl;

    // Yeu cau FileManager doc file
    // Them return 1; de thoat neu file loi
    if (!FileManager::docFileAdmin(dataDir + "Admin.txt", dsAdmin)) {
         Utils::hienThiThongBao("Khong tim thay " + dataDir + "Admin.txt. Kiem tra lai file.", true);
         return 1; // Thoat chuong trinh
    }
    if (!FileManager::docFileTheTu(dataDir + "TheTu.txt", dsCard)) {
        Utils::hienThiThongBao("Khong tim thay " + dataDir + "TheTu.txt. Kiem tra lai file.", true);
         return 1; // Thoat chuong trinh
    }

    cout << "Tai du lieu thanh cong." << endl;
    Utils::dungManHinh();

    // Vong lap chinh cua chuong trinh
    int iLuaChon;
    while (true) {
        Utils::hienThiHeader("TRANG CHU - NGAN HANG OOP");
        Utils::datMau(10); // Xanh
        cout << "1. Dang nhap Admin" << endl;
        cout << "2. Dang nhap User (Rut/Chuyen tien)" << endl;
        cout << "3. Thoat" << endl;
        Utils::datMau(15); // Trang
        cout << "--------------------------------------------------\n";
        cout << "Vui long chon chuc nang: ";
        cin >> iLuaChon;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Utils::hienThiThongBao("Lua chon phai la so.", true);
            continue;
        }

        switch (iLuaChon) {
            case 1: {
                // Goi constructor 2 tham so (da sua)
                Admin adminModule(&dsAdmin, &dsCard);
                adminModule.run();
                break;
            }
            case 2: {
                // Goi constructor 1 tham so (da sua)
                User userModule(&dsCard);
                userModule.run();
                break;
            }
            case 3:
                Utils::hienThiThongBao("Cam on ban da su dung dich vu!", false);
                return 0; // Thoat chuong trinh
            default:
                Utils::hienThiThongBao("Lua chon khong hop le (1-3).", true);
        }
    }

    return 0;
}