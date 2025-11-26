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
    // int mauMacDinh; // Không cần thiết
#endif

void thietLapConsole() {
#ifdef _WIN32
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set Console Output/Input CodePage sang UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#else
    // Linux/macOS
#endif
    setlocale(LC_ALL, ""); // Thiết lập locale cho tiếng Việt
}

void datMau(int mau) {
#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, mau);
#else
    // Dùng mã ANSI cho Linux/macOS
    if (mau == 10) cout << "\033[1;32m"; // Green
    else if (mau == 12) cout << "\033[1;31m"; // Red
    else if (mau == 14) cout << "\033[1;33m"; // Yellow
    else if (mau == 11) cout << "\033[1;36m"; // Cyan
    else if (mau == 15) cout << "\033[0;37m"; // White (reset)
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

void dungManHinh() {
    datMau(15);
    cout << "\nNhan Enter de tiep tuc...";

    // Xóa bộ đệm đầu vào (nếu còn ký tự \n)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Chờ người dùng nhấn Enter
    cin.get();
}

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
    dungManHinh();
}

string nhapPassBiMat() {
    string pass = "";
    char ch;
#ifdef _WIN32
    ch = _getch();
    while (ch != 13) { // 13 là mã ASCII của Enter
        if (ch == 8) { // 8 là mã ASCII của Backspace
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b"; // Xóa ký tự * trên màn hình
            }
        } else if (isprint(ch)) { // Chỉ nhận ký tự in được
            pass.push_back(ch);
            cout << '*';
        }
        ch = _getch();
    }
#else
    // Xử lý ẩn mật khẩu trên Linux/macOS
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO; // Tắt echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();
    while (ch != 10) { // 10 là mã ASCII của Enter
        if (ch == 127 || ch == 8) { // Xử lý Backspace (127 hoặc 8)
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
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Khôi phục cài đặt console
#endif
    cout << endl;
    return pass;
}

} // namespace Utils