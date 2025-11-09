#ifndef USER_H
#define USER_H

// --- SỬA Ở ĐÂY --- (Thêm lại BankProject/)
#include "BankProject/Core/List.h"
#include "BankProject/Core/Card.h"
#include "BankProject/Core/Account.h"
#include "BankProject/Core/Transaction.h"

/**
 * @brief Lop logic User
 */
class User {
private:
    List<Card>* pDsCard;

    Card* pCurrentUserCard;
    Account currentUserAccount;
    List<Transaction> currentUserHistory;

    const std::string FILE_THETU = "BankProject/Data/TheTu.txt";
    const std::string PIN_MAC_DINH = "123456";

public:
    // --- SỬA Ở ĐÂY --- (Xóa dataDir)
    User(List<Card>* dsCard);
    void run();

private:
    bool dangNhapUser();
    void dangXuatUser();
    void taiLichSuVaTaiKhoanUser();
    bool kiemTraPinLanDau();

    void hienThiMenuUser();
    void xemThongTinTaiKhoan();
    void rutTien();
    void chuyenTien();
    void xemNoiDungGiaoDich();
    void doiMaPin();

    void luuDuLieuTheTu();
};

#endif // USER_H