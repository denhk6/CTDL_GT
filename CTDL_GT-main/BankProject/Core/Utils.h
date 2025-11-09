#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    void thietLapConsole();
    void datMau(int mau);
    void xoaManHinh();
    void dungManHinh();
    void hienThiHeader(const std::string& title);
    void hienThiThongBao(const std::string& thongBao, bool laLoi = false);
    std::string nhapPassBiMat();
}

#endif // UTILS_H