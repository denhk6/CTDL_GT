#include "BankProject/Core/Card.h"
#include <string>
#include <iostream>

using namespace std;

Card::Card(string id, string pin, bool biKhoa, int soLanSai)
    : _strCardID(id), _strPIN(pin), _bBiKhoa(biKhoa), _iSoLanSai(soLanSai) {}

string Card::layId() const {
    return _strCardID;
}

string Card::layPin() const {
    return _strPIN;
}

// Hàm kiểm tra PIN
bool Card::kiemTraPin(const string& pin) {
    return _strPIN == pin;
}

bool Card::biKhoa() const {
    return _bBiKhoa;
}

int Card::laySoLanSai() const {
    return _iSoLanSai;
}

void Card::doiPin(const string& pinMoi) {
    _strPIN = pinMoi;
}

void Card::khoaThe() {
    _bBiKhoa = true;
}

void Card::moKhoaThe() {
    _bBiKhoa = false;
    _iSoLanSai = 0;
}

void Card::tangSoLanSai() {
    _iSoLanSai++;
    // Nếu nhập sai 3 lần, khóa thẻ
    if (this->_iSoLanSai >= 3) {
        this->khoaThe();
    }
}

void Card::datLaiSoLanSai() {
    _iSoLanSai = 0;
}

// Format file TheTu.txt: ID PIN BiKhoa(0/1) SoLanSai
istream& operator>>(istream& in, Card& tt) {
    int iBiKhoa;
    in >> tt._strCardID >> tt._strPIN >> iBiKhoa >> tt._iSoLanSai;
    tt._bBiKhoa = (iBiKhoa == 1);
    return in;
}

ostream& operator<<(ostream& out, const Card& tt) {
    out << tt._strCardID << " " << tt._strPIN << " " << (tt._bBiKhoa ? 1 : 0) << " " << tt._iSoLanSai;
    return out;
}