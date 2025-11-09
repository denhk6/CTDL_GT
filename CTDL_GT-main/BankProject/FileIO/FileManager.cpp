#include "BankProject/FileIO/FileManager.h"
#include <fstream>
#include <iostream>
#include <cstdio> // Cho ham remove

using namespace std;

// --- Dinh nghia cac ham Helper ---
// Duong dan "BankProject/Data/" duoc xu ly noi bo tai day
string FileManager::layTenFileTaiKhoan(const string& id) {
    return "BankProject/Data/" + id + ".txt";
}

string FileManager::layTenFileLichSu(const string& id) {
    return "BankProject/Data/LichSu" + id + ".txt";
}

// --- Doc du lieu ---
bool FileManager::docFileAdmin(const string& tenFile, List<AdminAccount>& dsAdmin) {
    ifstream fileIn(tenFile); // tenFile la "BankProject/Data/Admin.txt"
    if (!fileIn.is_open()) {
        cerr << "Loi: Khong mo duoc file " << tenFile << endl;
        return false;
    }
    dsAdmin.clear();
    AdminAccount admin;
    while (fileIn >> admin) {
        dsAdmin.them(admin);
    }
    fileIn.close();
    return true;
}

bool FileManager::docFileTheTu(const string& tenFile, List<Card>& dsTheTu) {
    ifstream fileIn(tenFile); // tenFile la "BankProject/Data/TheTu.txt"
    if (!fileIn.is_open()) {
        cerr << "Loi: Khong mo duoc file " << tenFile << endl;
        return false;
    }
    dsTheTu.clear();
    Card theTu;
    while (fileIn >> theTu) {
        dsTheTu.them(theTu);
    }
    fileIn.close();
    return true;
}

bool FileManager::docFileTaiKhoan(const string& id, Account& tk) {
    string tenFile = layTenFileTaiKhoan(id);
    ifstream fileIn(tenFile);
    if (!fileIn.is_open()) {
        cerr << "Loi: Khong mo duoc file " << tenFile << endl;
        return false;
    }
    fileIn >> tk;
    tk.thietLapId(id);
    fileIn.close();
    return true;
}

bool FileManager::docFileLichSu(const string& id, List<Transaction>& dsGiaoDich) {
    string tenFile = layTenFileLichSu(id);
    ifstream fileIn(tenFile);
    if (!fileIn.is_open()) {
        return true;
    }
    dsGiaoDich.clear();
    Transaction gd;
    while (fileIn >> gd) {
        dsGiaoDich.them(gd);
    }
    fileIn.close();
    return true;
}

// --- Ghi du lieu ---
bool FileManager::ghiFileTheTu(const string& tenFile, const List<Card>& dsTheTu) {
    ofstream fileOut(tenFile); // tenFile la "BankProject/Data/TheTu.txt"
    if (!fileOut.is_open()) {
        cerr << "Loi: Khong ghi duoc file " << tenFile << endl;
        return false;
    }
    dsTheTu.lapQua([&](const Card& tt) {
        fileOut << tt << endl;
    });
    fileOut.close();
    return true;
}

bool FileManager::ghiFileTaiKhoan(const string& id, const Account& tk) {
    string tenFile = layTenFileTaiKhoan(id);
    ofstream fileOut(tenFile);
    if (!fileOut.is_open()) {
        cerr << "Loi: Khong ghi duoc file " << tenFile << endl;
        return false;
    }
    fileOut << tk;
    fileOut.close();
    return true;
}

bool FileManager::ghiThemLichSu(const string& id, const Transaction& gd) {
    string tenFile = layTenFileLichSu(id);
    ofstream fileOut(tenFile, ios::app);
    if (!fileOut.is_open()) {
        cerr << "Loi: Khong ghi duoc file " << tenFile << endl;
        return false;
    }
    fileOut << gd << endl;
    fileOut.close();
    return true;
}

// --- Tao file moi ---
bool FileManager::taoFileTaiKhoanMoi(const string& id, const string& tenMacDinh, long long soDuMacDinh) {
    string tenFile = layTenFileTaiKhoan(id);
    ofstream fileOut(tenFile);
    if (!fileOut.is_open()) {
        cerr << "Loi: Khong tao duoc file " << tenFile << endl;
        return false;
    }
    fileOut << tenMacDinh << endl;
    fileOut << soDuMacDinh << endl;
    fileOut << "VND";
    fileOut.close();
    return true;
}

bool FileManager::taoFileLichSuMoi(const string& id) {
    string tenFile = layTenFileLichSu(id);
    ofstream fileOut(tenFile);
    if (!fileOut.is_open()) {
        cerr << "Loi: Khong tao duoc file " << tenFile << endl;
        return false;
    }
    fileOut.close();
    return true;
}

// --- Xoa file ---
bool FileManager::xoaFileTaiKhoan(const string& id) {
    string tenFile = layTenFileTaiKhoan(id);
    return remove(tenFile.c_str()) == 0;
}

bool FileManager::xoaFileLichSu(const string& id) {
    string tenFile = layTenFileLichSu(id);
    return remove(tenFile.c_str()) == 0;
}