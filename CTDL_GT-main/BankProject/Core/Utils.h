#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    // Thiết lập console (codepage, handle)
    void thietLapConsole();
    // Đặt màu chữ
    void datMau(int mau);
    void xoaManHinh();
    // Chờ người dùng nhấn Enter để tiếp tục
    void dungManHinh();
    // Hiển thị tiêu đề chương trình
    void hienThiHeader(const std::string& title);
    // Hiển thị thông báo thành công (màu xanh) hoặc lỗi (màu đỏ)
    void hienThiThongBao(const std::string& thongBao, bool laLoi = false);
    // Nhập mật khẩu/PIN với ký tự *
    std::string nhapPassBiMat();
}

#endif // UTILS_H