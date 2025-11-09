#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <memory> // Su dung unique_ptr de quan ly bo nho tu dong

/**
 * @brief Lop List template (Yeu cau cua de tai)
 * Cai dat mot danh sach lien ket don de quan ly cac doi tuong (Admin, Card, ...).
 * Su dung unique_ptr de tu dong quan ly bo nho, tranh memory leak (Coding standard muc 17).
 * @tparam T Kieu du lieu ma danh sach se luu tru
 */
template <typename T>
class List {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(T val) : data(val), next(nullptr) {}
    };
    std::unique_ptr<Node> head; // Con tro den dau danh sach
    int iSize; // Kich thuoc danh sach

public:
    List() : head(nullptr), iSize(0) {}

    ~List() {
        clear();
        // unique_ptr se tu dong giai phong bo nho khi List bi huy
    }

    /**
     * @brief Them mot phan tu vao cuoi danh sach
     */
    void them(const T& val) {
        auto newNode = std::make_unique<Node>(val);
        if (!head) {
            head = std::move(newNode);
        } else {
            Node* current = head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::move(newNode);
        }
        iSize++;
    }

    /**
     * @brief Tim kiem mot phan tu theo dieu kien (vi du: tim theo ID)
     * @param dieuKien Mot ham (lambda function) tra ve true neu phan tu khop
     * @return Con tro den phan tu tim thay, hoac nullptr neu khong tim thay
     */
    template<typename Func>
    T* timKiemTheoDieuKien(Func dieuKien) {
         Node* current = head.get();
        while(current) {
            if (dieuKien(current->data)) {
                return &current->data; // Tra ve dia chi cua data
            }
            current = current->next.get();
        }
        return nullptr; // Khong tim thay
    }

    /**
     * @brief Tim kiem mot phan tu theo dieu kien (phien ban const)
     */
    template<typename Func>
    const T* timKiemTheoDieuKien(Func dieuKien) const {
         Node* current = head.get();
        while(current) {
            if (dieuKien(current->data)) {
                return &current->data;
            }
            current = current->next.get();
        }
        return nullptr;
    }

    /**
     * @brief Xoa mot phan tu theo dieu kien (vi du: xoa theo ID)
     * @param dieuKien Mot ham (lambda) tra ve true neu phan tu khop
     * @return true neu xoa thanh cong, false neu khong tim thay
     */
    template<typename Func>
    bool xoaTheoDieuKien(Func dieuKien) {
        Node* prev = nullptr;
        Node* current = head.get();
        while(current) {
            if (dieuKien(current->data)) {
                if (prev) {
                    // Node o giua hoac cuoi
                    prev->next = std::move(current->next);
                } else {
                    // Node o dau
                    head = std::move(current->next);
                }
                iSize--;
                return true; // Xoa thanh cong
            }
            prev = current;
            current = current->next.get();
        }
        return false; // Khong tim thay
    }

    /**
     * @brief Lay kich thuoc (so luong phan tu) cua danh sach
     */
    int layKichThuoc() const {
        return iSize;
    }

    /**
     * @brief Xoa tat ca phan tu khoi danh sach
     */
    void clear() {
        while(head) {
            head = std::move(head->next); // Di chuyen con tro head, unique_ptr cu se tu dong bi xoa
        }
        iSize = 0;
    }

    /**
     * @brief Lap qua tung phan tu trong danh sach va thuc thi mot ham
     * @param func Ham de thuc thi tren moi phan tu (vi du: de ghi ra file)
     */
    template<typename Func>
    void lapQua(Func func) {
        Node* current = head.get();
        while(current) {
            func(current->data); // Cho phep thay doi data (vi du: moKhoaThe)
            current = current->next.get();
        }
    }

    /**
     * @brief Lap qua tung phan tu (phien ban const, khong thay doi data)
     * @param func Ham de thuc thi (vi du: de hien thi)
     */
    template<typename Func>
    void lapQua(Func func) const {
        Node* current = head.get();
        while(current) {
            func(current->data); // Khong the thay doi data
            current = current->next.get();
        }
    }
};

#endif // LIST_H