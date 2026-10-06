#include <iostream>
#include <string>
using namespace std;
const int MAX = 100;
// ==================== CUSTOMER ====================
class Customer {
public:
    string id;
    string ten;
    string loaiDichVu;
    int thoiGianDen;
    int tGXuLyDuKien;     // pj
    int trongSoChiPhiCho; // wj
};
// ==================== QUEUE ====================
class Queue {
private:
    class Node {
    public:
        Customer data;
        Node* next;

        Node(Customer c) {
            data = c;
            next = NULL;
        }
    };
    Node* front;
    Node* rear;
    int size;
public:
    Queue() {
        front = NULL;
        rear = NULL;
        size = 0;
    }
    bool isEmpty() {
        return front == NULL;
    }
    int getSize() {
        return size;
    }
    // Thêm khách vào cuối hàng đợi
    void enqueue(Customer c) {
        Node* p = new Node(c);
        if (front == NULL) {
            front = p;
            rear = p;
        }
        else {
            rear->next = p;
            rear = p;
        }

        size++;
    }
    // Lấy khách đầu hàng đợi
    bool dequeue(Customer& c) {
        if (front == NULL) {
            return false;
        }
        Node* p = front;
        c = p->data;
        front = front->next;
        if (front == NULL) {
            rear = NULL;
        }
        delete p;
        size--;
        return true;
    }
    // Thêm lại đầu Queue - dùng cho Undo SERVE
    void addFront(Customer c) {
        Node* p = new Node(c);
        p->next = front;
        front = p;
        if (rear == NULL) {
            rear = p;
        }
        size++;
    }
    // Xóa cuối Queue - dùng cho Undo ADD
    void removeRear() {
        if (front == NULL) {
            return;
        }
        // Chỉ có 1 phần tử
        if (front == rear) {
            delete front;
            front = NULL;
            rear = NULL;
            size = 0;
            return;
        }
        Node* p = front;
        while (p->next != rear) {
            p = p->next;
        }
        delete rear;
        rear = p;
        rear->next = NULL;
        size--;
    }
    bool updateById(string id, Customer newData) {
    Node* p = front;

    while (p != NULL) {
        if (p->data.id == id) {

            p->data = newData;

            return true;
        }

        p = p->next;
    }

    return false;
}
    void display() {
        if (front == NULL) {
            cout << "Hang doi rong!\n";
            return;
        }
        cout << "\n===== DANH SACH DANG CHO =====\n";
        Node* p = front;
        while (p != NULL) {
            cout << "Ma: " << p->data.id << endl;
            cout << "Ten: " << p->data.ten << endl;
            cout << "Dich vu: "
                 << p->data.loaiDichVu << endl;
            cout << "Thoi gian den: "
                 << p->data.thoiGianDen << endl;
            cout << "Thoi gian xu ly: "
                 << p->data.tGXuLyDuKien << endl;
            cout << "Nhap trong so chi phi cho: "
                 << p->data.trongSoChiPhiCho << endl;

            cout << "----------------------\n";

            p = p->next;
        }
    }
    bool removeById(string id){
        if (front == NULL){
            return false;
        }
        if (front->data.id==id){
            Node* p=front;
            front=front->next;
            if(front==NULL){
                rear=NULL;
            }
            delete p;
            size--;
            return true;
        }
        Node* p=front;
        while (p->next != NULL && 
               p->next->data.id != id){
            p=p->next;
            }
        if(p->next==NULL){
                return false;
        }
        Node* temp=p->next;
        p->next=temp->next;
        if(temp==rear){
            rear=p;
        }
        delete temp;
        size--;
        return true;

    }
};
// ==================== CUSTOMER LIST ====================
class CustomerList {
private:
    class Node {
    public:
        Customer data;
        Node* next;
        Node(Customer c) {
            data = c;
            next = NULL;
        }
    };
    Node* head;
    int size;
public:
    CustomerList() {
        head = NULL;
        size = 0;
    }
    void add(Customer c) {
        Node* p = new Node(c);
        if (head == NULL) {
            head = p;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = p;
        }
        size++;
    }
    // Tìm khách theo mã
    Customer* findById(string id) {
        Node* p = head;
        while (p != NULL) {
            if (p->data.id == id) {
                return &(p->data);
            }
            p = p->next;
        }
        return NULL;
    }
    // Xóa khách cuối cùng - phục vụ Undo ADD
    void removeLast() {
        if (head == NULL) {
            return;
        }
        if (head->next == NULL) {
            delete head;
            head = NULL;
            size = 0;
            return;
        }
        Node* p = head;
        while (p->next->next != NULL) {
            p = p->next;
        }
        delete p->next;
        p->next = NULL;
        size--;
    }
    void sortById() {
    if (head == NULL || head->next == NULL) {
        return;
    }

    Node* p = head;

    while (p != NULL) {
        Node* q = p->next;

        while (q != NULL) {
            if (p->data.id > q->data.id) {
                Customer temp = p->data;
                p->data = q->data;
                q->data = temp;
            }

            q = q->next;
        }

        p = p->next;
    }

    cout << "Da sap xep khach hang theo ma!\n";
}
    bool updateById(string id, Customer newData) {
    Node* p = head;

    while (p != NULL) {
        if (p->data.id == id) {

            p->data = newData;

            return true;
        }

        p = p->next;
    }

    return false;
}

    void display() {
    if (head == NULL) {
        cout << "Danh sach khach hang rong!\n";
        return;
    }

    Node* p = head;

    cout << "\n===== DANH SACH KHACH HANG =====\n";

    while (p != NULL) {
        cout << "Ma: " << p->data.id << endl;
        cout << "Ten: " << p->data.ten << endl;
        cout << "Dich vu: " << p->data.loaiDichVu << endl;
        cout << "Thoi gian den: "
             << p->data.thoiGianDen << endl;
        cout << "Thoi gian xu ly: "
             << p->data.tGXuLyDuKien << endl;
        cout << "Trong so chi phi cho: "
             << p->data.trongSoChiPhiCho << endl;

        cout << "---------------------\n";

        p = p->next;
    }
}
    bool removeById(string id, Customer& oldData) {
    if (head == NULL) {
        return false;
    }
    // Xoa node dau
    if (head->data.id == id) {
        Node* p = head;
        oldData = p->data;
        head = head->next;
        delete p;
        size--;
        return true;
    }
    Node* p = head;
    // Tim node dung truoc node can xoa
    while (p->next != NULL &&
           p->next->data.id != id) {
        p = p->next;
    }
    // Khong tim thay
    if (p->next == NULL) {
        return false;
    }
    // Tim thay
    Node* temp = p->next;
    oldData = temp->data;
    p->next = temp->next;
    delete temp;
    size--;
    return true;
}
    
};
// ==================== TICKET ====================
class Ticket {
public:
    string idPhieu;
    string customerId;
    string yeuCau;
    string trangThai;
};
// ==================== TICKET LIST ====================
class TicketList {
private:
    class Node {
    public:
        Ticket data;
        Node* next;

        Node(Ticket t) {
            data = t;
            next = NULL;
        }
    };
    Node* head;
    int size;
public:
    TicketList() {
        head = NULL;
        size = 0;
    }
    
    void add(Ticket t) {
        Node* p = new Node(t);
        if (head == NULL) {
            head = p;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = p;
        }
        size++;
    }
    Ticket* findByCustomerId(string customerId) {
        Node* p = head;
        while (p != NULL) {
            if (p->data.customerId == customerId) {
                return &(p->data);
            }
            p = p->next;
        }
        return NULL;
    }
    void updateStatus(string customerId, string status) {
        Ticket* t = findByCustomerId(customerId);
        if (t != NULL) {
            t->trangThai = status;
        }
    }
    bool removeById(string idPhieu) {
    if (head == NULL) {
        return false;
    }

    // Xoa node dau
    if (head->data.idPhieu == idPhieu) {
        Node* p = head;

        head = head->next;

        delete p;
        size--;

        return true;
    }

    Node* p = head;

    while (p->next != NULL &&
           p->next->data.idPhieu != idPhieu) {
        p = p->next;
    }

    if (p->next == NULL) {
        return false;
    }

    Node* temp = p->next;

    p->next = temp->next;

    delete temp;
    size--;

    return true;
}
    bool updateById(string idPhieu, Ticket newData) {
    Node* p = head;

    while (p != NULL) {
        if (p->data.idPhieu == idPhieu) {
            p->data = newData;
            return true;
        }

        p = p->next;
    }

    return false;
}
    void display() {
        if (head == NULL) {
            cout << "Danh sach ticket rong!\n";
            return;
        }
        Node* p = head;
        while (p != NULL) {
            cout << "\nMa phieu: "
                 << p->data.idPhieu << endl;
            cout << "Ma khach: "
                 << p->data.customerId << endl;
            cout << "Yeu cau: "
                 << p->data.yeuCau << endl;
            cout << "Trang thai: "
                 << p->data.trangThai << endl;
            cout << "----------------------\n";
            p = p->next;
        }
    }
};
// ==================== HISTORY STACK ====================
class History {
public:
    string action;

    Customer oldData;
    Customer newData;
};
class HistoryStack {
private:
    History stack[MAX];
    int top;
public:
    HistoryStack() {
        top = -1;
    }
    void push(string action, Customer oldData, Customer newData) {
        if (top == MAX - 1) {
            cout << "Lich su da day!\n";
            return;
        }
        top++;
        stack[top].action = action;
        stack[top].newData = newData;
        stack[top].oldData = oldData;
    }
    bool pop(History& h) {
        if (top == -1) {
            return false;
        }
        h = stack[top];
        top--;
        return true;
    }
};
// ==================== CHUONG TRINH CHINH ====================
class ServiceDesk {
private:
    Queue q;
    CustomerList customerList;
    TicketList ticketList;
    HistoryStack history;
public:

    // ---------- Thêm khách ----------
    void addCustomer() {
        Customer empty;
        Customer c;
        cout << "Nhap ma khach hang: ";
        cin >> c.id;
        // Kiểm tra mã trùng
        if (customerList.findById(c.id) != NULL) {
            cout << "Ma khach hang da ton tai!\n";
            return;
        }
        cin.ignore();
        cout << "Nhap ten khach hang: ";
        getline(cin, c.ten);
        cout << "Nhap loai dich vu: ";
        getline(cin, c.loaiDichVu);
        cout << "Nhap thoi gian den: ";
        cin >> c.thoiGianDen;
        cout << "Nhap thoi gian xu ly du kien: ";
        cin >> c.tGXuLyDuKien;
        cout << "Nhap trong so chi phi cho: ";
        cin >> c.trongSoChiPhiCho;
        // Thêm vào Queue
        q.enqueue(c);
        // Thêm vào danh sách khách
        customerList.add(c);
        // Lưu lịch sử
        history.push("ADD",empty,c);
        cout << "Da them khach hang!\n";
    }
    // ---------- Phục vụ ----------
    void serveCustomer() {
        Customer c;
        if (!q.dequeue(c)) {
            cout << "Khong co khach hang nao cho!\n";
            return;
        }
        cout << "\nKhach hang dang duoc phuc vu:\n";
        cout << "Ma: " << c.id << endl;
        cout << "Ten: " << c.ten << endl;
        cout << "Dich vu: "
             << c.loaiDichVu << endl;
        // Ticket chuyển sang đã xử lý
        ticketList.updateStatus(c.id, "Da xu ly");
        cout << "Da phuc vu khach hang!\n";
    }
    // ---------- Tạo Ticket ----------
    void addTicket() {
        Ticket t;
        cout << "Nhap ma phieu: ";
        cin >> t.idPhieu;
        cout << "Nhap ma khach hang: ";
        cin >> t.customerId;
        // Kiểm tra khách có tồn tại
        if (customerList.findById(t.customerId) == NULL) {
            cout << "Khong ton tai khach hang nay!\n";
            return;
        }
        cin.ignore();
        cout << "Nhap yeu cau: ";
        getline(cin, t.yeuCau);
        t.trangThai = "Dang cho";
        ticketList.add(t);
        cout << "Da tao ticket!\n";
    }
    // ---------- Tìm Customer ----------
    void searchCustomer() {
        string id;
        cout << "Nhap ma khach hang can tim: ";
        cin >> id;
        Customer* c = customerList.findById(id);
        if (c == NULL) {
            cout << "Khong tim thay khach hang!\n";
            return;
        }
        cout << "\n===== THONG TIN KHACH HANG =====\n";
        cout << "Ma: " << c->id << endl;
        cout << "Ten: " << c->ten << endl;
        cout << "Loai dich vu: "
             << c->loaiDichVu << endl;
        cout << "Thoi gian den: "
             << c->thoiGianDen << endl;
        cout << "Thoi gian xu ly: "
             << c->tGXuLyDuKien << endl;
        cout << "Trong so chi phi cho: "
             << c->trongSoChiPhiCho << endl;
    }
    // ---------- Tìm Ticket ----------
    void searchTicket() {
        string id;
        cout << "Nhap ma khach hang: ";
        cin >> id;
        Ticket* t = ticketList.findByCustomerId(id);
        if (t == NULL) {
            cout << "Khong tim thay ticket!\n";
            return;
        }
        cout << "\nMa phieu: "
             << t->idPhieu << endl;
        cout << "Ma khach: "
             << t->customerId << endl;
        cout << "Yeu cau: "
             << t->yeuCau << endl;
        cout << "Trang thai: "
             << t->trangThai << endl;
    }
    // ---------- Undo ----------
    void undo() {
    History h;
    if (!history.pop(h)) {
        cout << "Khong co thao tac de hoan tac!\n";
        return;
    }
    if (h.action == "ADD") {
        Customer temp;
        customerList.removeById(
            h.newData.id,
            temp
        );
        q.removeById(h.newData.id);
        cout << "Da hoan tac them khach hang: "
             << h.newData.ten << endl;
    }
    else if (h.action == "DELETE") {
        customerList.add(h.oldData);
        q.enqueue(h.oldData);
        cout << "Da hoan tac xoa khach hang: "
             << h.oldData.ten << endl;
    }
    else if (h.action == "UPDATE") {
    customerList.updateById(
        h.oldData.id,
        h.oldData
    );
    q.updateById(
        h.oldData.id,
        h.oldData
    );
    cout << "Da hoan tac cap nhat khach hang: "
         << h.oldData.ten << endl;
    }
}
    void updateCustomer() {
    string id;
    cout << "Nhap ma khach hang can cap nhat: ";
    cin >> id;
    Customer* c = customerList.findById(id);
    if (c == NULL) {
        cout << "Khong tim thay khach hang!\n";
        return;
    }
    // Luu thong tin cu de Undo
    Customer oldData = *c;
    // Tao thong tin moi
    Customer newData = oldData;
    cin.ignore();
    cout << "Nhap ten moi: ";
    getline(cin, newData.ten);
    cout << "Nhap loai dich vu moi: ";
    getline(cin, newData.loaiDichVu);
    cout << "Nhap thoi gian den moi: ";
    cin >> newData.thoiGianDen;
    cout << "Nhap thoi gian xu ly du kien moi: ";
    cin >> newData.tGXuLyDuKien;
    cout << "Nhap trong so chi phi cho moi: ";
    cin >> newData.trongSoChiPhiCho;
    // Cap nhat danh sach
    customerList.updateById(id, newData);
    // Neu khach dang cho thi cap nhat Queue
    q.updateById(id, newData);
    // Luu lich su
    history.push("UPDATE", oldData, newData);
    cout << "Da cap nhat khach hang!\n";
}
    void deleteCustomer() {
    string id;
    cout << "Nhap ma khach hang can xoa: ";
    cin >> id;
    Customer oldData;
    if (!customerList.removeById(id, oldData)) {
        cout << "Khong tim thay khach hang!\n";
        return;
    }
    q.removeById(id);
    Customer empty;
    history.push("DELETE", oldData, empty);
    cout << "Da xoa khach hang: "
         << oldData.ten << endl;
    }
    // ---------- Menu ----------
    void hienThiMenu() {
        cout << "\n===== SMART SERVICE DESK =====\n";
        cout << "1. Them khach hang\n";
        cout << "2. Phuc vu khach hang\n";
        cout << "3. Xem hang doi\n";
        cout << "4. Hoan tac\n";
        cout << "5. Tao ticket\n";
        cout << "6. Xem danh sach ticket\n";
        cout << "7. Tim ticket theo ma khach\n";
        cout << "8. Tim khach hang theo ma\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
    }
    // ---------- Chạy chương trình ----------
    void run() {
        int choice;
        do {
            hienThiMenu();

            cin >> choice;

            switch (choice) {
                case 1:
                    addCustomer();
                    break;
                case 2:
                    serveCustomer();
                    break;
                case 3:
                    q.display();
                    break;
                case 4:
                    undo();
                    break;
                case 5:
                    addTicket();
                    break;
                case 6:
                    ticketList.display();
                    break;
                case 7:
                    searchTicket();
                    break;
                case 8:
                    searchCustomer();
                    break;
                case 9:
                    deleteCustomer();
                    break;
                case 10:
                    updateCustomer();
                    break;
                case 11:
                    customerList.display();
                    break;
                case 12:
                    customerList.sortById();
                    break;
                case 0:
                    cout << "Thoat chuong trinh!\n";
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
            }
        } while (choice != 0);
    }
};
// ==================== MAIN ====================
int main() {
    ServiceDesk app;
    app.run();
    return 0;
}