#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "BankProject/Core/List.h"
#include "BankProject/Core/Card.h"
#include "BankProject/Core/Account.h"
#include "BankProject/Core/Transaction.h"
#include "BankProject/Admin/Admin.h"

using namespace std;

class FileManager {
private:
    // Hàm nội bộ để xây dựng đường dẫn đầy đủ
    static string layTenFileTaiKhoan(const string& id);
    static string layTenFileLichSu(const string& id);

public:
    // --- Doc du lieu ---
    static bool docFileAdmin(const string& tenFile, List<AdminAccount>& dsAdmin);
    static bool docFileTheTu(const string& tenFile, List<Card>& dsTheTu);

    // Đọc thông tin tài khoản và lịch sử theo ID
    static bool docFileTaiKhoan(const string& id, Account& tk);
    static bool docFileLichSu(const string& id, List<Transaction>& dsGiaoDich);

    // --- Ghi du lieu ---
    static bool ghiFileTheTu(const string& tenFile, const List<Card>& dsTheTu);
    static bool ghiFileTaiKhoan(const string& id, const Account& tk);
    // Ghi thêm một giao dịch mới vào cuối file lịch sử
    static bool ghiThemLichSu(const string& id, const Transaction& gd);

    // --- Tao file moi ---
    static bool taoFileTaiKhoanMoi(const string& id, const string& tenMacDinh, long long soDuMacDinh);
    static bool taoFileLichSuMoi(const string& id);

    // --- Xoa file ---
    static bool xoaFileTaiKhoan(const string& id);
    static bool xoaFileLichSu(const string& id);
};

#endif // FILEMANAGER_H