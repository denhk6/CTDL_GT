#include "BankProject/Core/Card.h"
#include <string>
#include <iostream>

using namespace std;

Card::Card(string id, string pin, bool biKhoa, int soLanSai)
    : strCardID(id), strPIN(pin), bBiKhoa(biKhoa), iSoLanSai(soLanSai) {}

string Card::layId() const {
    return strCardID;
}

string Card::layPin() const {
    return strPIN;
}

bool Card::kiemTraPin(const string& pin) {
    return strPIN == pin;
}

bool Card::biKhoa() const {
    return bBiKhoa;
}

int Card::laySoLanSai() const {
    return iSoLanSai;
}

void Card::doiPin(const string& pinMoi) {
    strPIN = pinMoi;
}

void Card::khoaThe() {
    bBiKhoa = true;
}

void Card::moKhoaThe() {
    bBiKhoa = false;
    iSoLanSai = 0;
}

void Card::tangSoLanSai() {
    iSoLanSai++;
    if (iSoLanSai >= 3) {
        khoaThe();
    }
}

void Card::datLaiSoLanSai() {
    iSoLanSai = 0;
}

// Format file: ID PIN BiKhoa(0/1) SoLanSai
istream& operator>>(istream& in, Card& tt) {
    int iBiKhoa;
    in >> tt.strCardID >> tt.strPIN >> iBiKhoa >> tt.iSoLanSai;
    tt.bBiKhoa = (iBiKhoa == 1);
    return in;
}

ostream& operator<<(ostream& out, const Card& tt) {
    out << tt.strCardID << " " << tt.strPIN << " " << (tt.bBiKhoa ? 1 : 0) << " " << tt.iSoLanSai;
    return out;
}