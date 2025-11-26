#ifndef USER_H
#define USER_H

#include "BankProject/Core/List.h"
#include "BankProject/Core/Card.h"
#include "BankProject/Core/Account.h"
#include "BankProject/Core/Transaction.h"

/**
 * @brief Lop logic User, quan ly cac giao dich cua nguoi dung.
 */
class User {
private:
    List<Card>* _pDsCard;

    Card* _pCurrentUserCard;
    Account _currentUserAccount;
    List<Transaction> _currentUserHistory;

    // Định nghĩa hằng số cho đường dẫn file và PIN mặc định
    const std::string FILE_CARD_LIST = "BankProject/Data/TheTu.txt";
    const std::string PIN_DEFAULT = "123456";

public:
    User(List<Card>* dsCard);
    void run();

private:
    bool dangNhapUser();
    void dangXuatUser();
    void taiLichSuVaTaiKhoanUser();
    // Kiểm tra và yêu cầu đổi PIN nếu là lần đầu/PIN mặc định
    bool kiemTraPinLanDau();

    void hienThiMenuUser();
    void xemThongTinTaiKhoan();
    void rutTien();
    void chuyenTien();
    void xemNoiDungGiaoDich();
    void doiMaPin();

    // Lưu lại danh sách thẻ từ vào file TheTu.txt
    void luuDuLieuTheTu();
};

#endif // USER_H