#include <iostream>
#include <string>
#include <limits>
#include <clocale>

#include "BankProject/Core/List.h"
#include "BankProject/Core/Card.h"
#include "BankProject/Admin/Admin.h"
#include "BankProject/User/User.h"
#include "BankProject/FileIO/FileManager.h"
#include "BankProject/Core/Utils.h"

using namespace std;

// Định nghĩa hằng số cho đường dẫn file
const string DATA_DIR = "BankProject/Data/";
const string ADMIN_FILE = DATA_DIR + "Admin.txt";
const string CARD_FILE = DATA_DIR + "TheTu.txt";


int main() {
    // Thiết lập console và locale
    setlocale(LC_ALL, "");
    Utils::thietLapConsole();

    List<AdminAccount> dsAdmin;
    List<Card> dsCard;

    Utils::datMau(15);
    cout << "Dang tai du lieu he thong..." << endl;

    // Tải danh sách Admin
    if (!FileManager::docFileAdmin(ADMIN_FILE, dsAdmin)) {
         Utils::hienThiThongBao("Khong tim thay " + ADMIN_FILE + ". Kiem tra lai file.", true);
         return 1;
    }
    // Tải danh sách Thẻ từ
    if (!FileManager::docFileTheTu(CARD_FILE, dsCard)) {
        Utils::hienThiThongBao("Khong tim thay " + CARD_FILE + ". Kiem tra lai file.", true);
         return 1;
    }

    cout << "Tai du lieu thanh cong." << endl;
    Utils::dungManHinh();

    int iLuaChon;
    while (true) {
        Utils::hienThiHeader("TRANG CHU - NGAN HANG OOP");
        Utils::datMau(10); // Xanh
        cout << "1. Dang nhap Admin" << endl;
        cout << "2. Dang nhap User (Rut/Chuyen tien)" << endl;
        cout << "3. Thoat" << endl;
        Utils::datMau(15); // Trang
        cout << "**************************************************\n";
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
                Admin adminModule(&dsAdmin, &dsCard);
                adminModule.run();
                break;
            }
            case 2: {
                User userModule(&dsCard);
                userModule.run();
                break;
            }
            case 3:
                Utils::hienThiThongBao("Cam on ban da su dung dich vu!", false);
                return 0;
            default:
                Utils::hienThiThongBao("Lua chon khong hop le (1-3).", true);
        }
    }

    return 0;
}