#include "BankProject/Core/Utils.h"
#include <iostream>
#include <limits>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

using namespace std;

namespace Utils {

#ifdef _WIN32
    HANDLE hConsole;
    int mauMacDinh;
#endif

void thietLapConsole() {
#ifdef _WIN32
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    mauMacDinh = consoleInfo.wAttributes;
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#else
#endif
    setlocale(LC_ALL, "");
}

void datMau(int mau) {
#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, mau);
#else
    if (mau == 10) cout << "\033[1;32m"; // Green
    else if (mau == 12) cout << "\033[1;31m"; // Red
    else if (mau == 14) cout << "\033[1;33m"; // Yellow
    else if (mau == 11) cout << "\033[1;36m"; // Cyan
    else if (mau == 15) cout << "\033[0;37m"; // White
    else cout << "\033[0;37m";
#endif
}

void xoaManHinh() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// --- ĐÃ SỬA LỖI Ở HÀM NÀY ---
void dungManHinh() {
    datMau(15);
    cout << "\nNhan Enter de tiep tuc...";

    // 1. Xóa tất cả những gì còn sót lại trong bộ đệm (ví dụ: '\n')
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // 2. Bây giờ, chờ một cú nhấn Enter MỚI từ người dùng.
    cin.get();
}
// --- KẾT THÚC SỬA LỖI ---

void hienThiHeader(const string& title) {
    xoaManHinh();
    datMau(14);
    cout << "**************************************************\n";
    cout << "* MAY ATM NGAN HANG NHOM POPEYES         *\n";
    cout << "**************************************************\n";
    cout << "\n";
    datMau(11);
    cout << "               " << title << "\n";
    datMau(15);
    cout << "--------------------------------------------------\n\n";
}

void hienThiThongBao(const string& thongBao, bool laLoi) {
    if (laLoi) {
        datMau(12);
        cout << "LOI: " << thongBao << endl;
    } else {
        datMau(10);
        cout << "THONG BAO: " << thongBao << endl;
    }
    datMau(15);

    // Hàm hienThiThongBao đã bao gồm dungManHinh
    // nên chúng ta không cần lặp lại logic ở đây
    dungManHinh();
}

string nhapPassBiMat() {
    string pass = "";
    char ch;
#ifdef _WIN32
    ch = _getch();
    while (ch != 13) {
        if (ch == 8) {
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else if (isprint(ch)) {
            pass.push_back(ch);
            cout << '*';
        }
        ch = _getch();
    }
#else
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();
    while (ch != 10) {
        if (ch == 127 || ch == 8) {
             if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else if (isprint(ch)) {
            pass.push_back(ch);
            cout << '*';
        }
        ch = getchar();
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    cout << endl;
    return pass;
}

} // namespace Utils