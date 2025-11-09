#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "BankProject/Core/List.h"
#include "BankProject/Core/Card.h"
#include "BankProject/Core/Account.h"
#include "BankProject/Core/Transaction.h"
#include "BankProject/Admin/Admin.h" // Phai include de biet AdminAccount

using namespace std;

class FileManager {
private:
    // Ham noi bo de lay duong dan (da bao gom "BankProject/Data/")
    static string layTenFileTaiKhoan(const string& id);
    static string layTenFileLichSu(const string& id);

public:
    // --- Doc du lieu ---
    // main.cpp se truyen duong dan day du
    static bool docFileAdmin(const string& tenFile, List<AdminAccount>& dsAdmin);
    static bool docFileTheTu(const string& tenFile, List<Card>& dsTheTu);

    // Admin/User chi can truyen ID
    static bool docFileTaiKhoan(const string& id, Account& tk);
    static bool docFileLichSu(const string& id, List<Transaction>& dsGiaoDich);

    // --- Ghi du lieu ---
    static bool ghiFileTheTu(const string& tenFile, const List<Card>& dsTheTu);
    static bool ghiFileTaiKhoan(const string& id, const Account& tk);
    static bool ghiThemLichSu(const string& id, const Transaction& gd);

    // --- Tao file moi ---
    static bool taoFileTaiKhoanMoi(const string& id, const string& tenMacDinh, long long soDuMacDinh);
    static bool taoFileLichSuMoi(const string& id);

    // --- Xoa file ---
    static bool xoaFileTaiKhoan(const string& id);
    static bool xoaFileLichSu(const string& id);
};

#endif // FILEMANAGER_H