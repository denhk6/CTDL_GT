#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <memory> // Sử dụng unique_ptr để quản lý bộ nhớ tự động

/**
 * @brief Lớp List template (Danh sách liên kết đơn)
 * Sử dụng unique_ptr để tự động quản lý bộ nhớ, tuân thủ nguyên tắc "Có new phải có delete".
 * @tparam T Kiểu dữ liệu mà danh sách sẽ lưu trữ
 */
template <typename T>
class List {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    std::unique_ptr<Node> head; // Con trỏ đến đầu danh sách
    int _iSize; // Kích thước danh sách

public:
    List() : head(nullptr), _iSize(0) {}

    ~List() {
        clear();
    }

    /**
     * @brief Thêm một phần tử vào cuối danh sách
     */
    void them(const T& val) {
        auto newNode = std::make_unique<Node>(val);
        if (!this->head) {
            this->head = std::move(newNode);
        } else {
            Node* current = this->head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::move(newNode);
        }
        this->_iSize++;
    }

    /**
     * @brief Tìm kiếm một phần tử theo điều kiện
     * @param dieuKien Một hàm lambda trả về true nếu phần tử khop
     * @return Con trỏ đến phần tử tìm thấy, hoặc nullptr nếu không tìm thấy
     */
    template<typename Func>
    T* timKiemTheoDieuKien(Func dieuKien) {
         Node* current = this->head.get();
        while(current) {
            if (dieuKien(current->data)) {
                return &current->data; // Trả về địa chỉ của data
            }
            current = current->next.get();
        }
        return nullptr;
    }

    /**
     * @brief Tìm kiếm một phần tử theo điều kiện (phiên bản const)
     */
    template<typename Func>
    const T* timKiemTheoDieuKien(Func dieuKien) const {
         Node* current = this->head.get();
        while(current) {
            if (dieuKien(current->data)) {
                return &current->data;
            }
            current = current->next.get();
        }
        return nullptr;
    }

    /**
     * @brief Xóa một phần tử theo điều kiện
     * @param dieuKien Một hàm lambda trả về true nếu phần tử khop
     * @return true nếu xoa thành công, false nếu không tìm thấy
     */
    template<typename Func>
    bool xoaTheoDieuKien(Func dieuKien) {
        Node* prev = nullptr;
        Node* current = this->head.get();
        while(current) {
            if (dieuKien(current->data)) {
                if (prev) {
                    // Node ở giữa hoặc cuối
                    prev->next = std::move(current->next);
                } else {
                    // Node ở đầu
                    this->head = std::move(current->next);
                }
                this->_iSize--;
                return true; // Xóa thành công
            }
            prev = current;
            current = current->next.get();
        }
        return false; // Không tìm thấy
    }

    /**
     * @brief Lấy kích thước (số lượng phần tử) của danh sách
     */
    int layKichThuoc() const {
        return this->_iSize;
    }

    /**
     * @brief Xóa tất cả phần tử khỏi danh sách
     */
    void clear() {
        while(this->head) {
            // unique_ptr cũ sẽ tự động bị hủy (delete)
            this->head = std::move(this->head->next);
        }
        this->_iSize = 0;
    }

    /**
     * @brief Lặp qua từng phần tử trong danh sách và thực thi một hàm (có thể thay đổi data)
     */
    template<typename Func>
    void lapQua(Func func) {
        Node* current = this->head.get();
        while(current) {
            func(current->data);
            current = current->next.get();
        }
    }

    /**
     * @brief Lặp qua từng phần tử (phiên bản const, không thay đổi data)
     */
    template<typename Func>
    void lapQua(Func func) const {
        Node* current = this->head.get();
        while(current) {
            func(current->data);
            current = current->next.get();
        }
    }
};

#endif // LIST_H