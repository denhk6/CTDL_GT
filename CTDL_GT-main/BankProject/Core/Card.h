#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card {
private:
    std::string _strCardID;
    std::string _strPIN;
    bool _bBiKhoa;
    int _iSoLanSai;

public:
    Card(std::string id = "", std::string pin = "", bool biKhoa = false, int soLanSai = 0);

    std::string layId() const;
    std::string layPin() const;
    // Kiểm tra PIN, không phải là hàm const vì nó cần thay đổi số lần sai
    bool kiemTraPin(const std::string& pin);
    bool biKhoa() const;
    int laySoLanSai() const;

    void doiPin(const std::string& pinMoi);
    void khoaThe();
    void moKhoaThe();
    // Tăng số lần nhập sai PIN, có thể dẫn đến khóa thẻ
    void tangSoLanSai();
    void datLaiSoLanSai();

    bool operator==(const Card& other) const {
        return this->_strCardID == other._strCardID;
    }

    friend std::istream& operator>>(std::istream& in, Card& tt);
    friend std::ostream& operator<<(std::ostream& out, const Card& tt);
};

#endif // CARD_H