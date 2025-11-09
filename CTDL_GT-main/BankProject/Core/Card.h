#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {
private:
    std::string strCardID;
    std::string strPIN;
    bool bBiKhoa;
    int iSoLanSai;

public:
    Card(std::string id = "", std::string pin = "", bool biKhoa = false, int soLanSai = 0);

    std::string layId() const;
    std::string layPin() const;
    bool kiemTraPin(const std::string& pin);
    bool biKhoa() const;
    int laySoLanSai() const;

    void doiPin(const std::string& pinMoi);
    void khoaThe();
    void moKhoaThe();
    void tangSoLanSai();
    void datLaiSoLanSai();

    bool operator==(const Card& other) const {
        return strCardID == other.strCardID;
    }

    friend std::istream& operator>>(std::istream& in, Card& tt);
    friend std::ostream& operator<<(std::ostream& out, const Card& tt);
};

#endif // CARD_H