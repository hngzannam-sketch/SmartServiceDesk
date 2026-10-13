#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX_NODES = 100;

struct Node {
    int id;
    string content;
    Node* left;
    Node* right;
    bool isLeaf;

    // Thong tin phu de nhap cay va quan ly cac nut da cap phat.
    int leftId;
    int rightId;
    int parentCount;
    bool visited;
    Node* nextAllocated;
};

Node* root = nullptr;
Node* allocatedHead = nullptr;
int n = 0;

int readInt(const string& message) {
    string line, extra;
    int value;
    while (true) {
        cout << message;
        if (!getline(cin, line)) exit(0);
        istringstream iss(line);
        if ((iss >> value) && !(iss >> extra)) return value;
        cout << "Vui long nhap mot so nguyen hop le!\n";
    }
}

string readContent() {
    string content;
    while (true) {
        cout << "Noi dung: ";
        if (!getline(cin, content)) exit(0);
        if (content.find_first_not_of(" \t\r\n") != string::npos && content.size() < 120)
            return content;
        cout << "Noi dung phai khac rong va ngan hon 120 ky tu!\n";
    }
}

Node* createNode(int id, const string& content, bool isLeaf) {
    Node* p = new Node{id, content, nullptr, nullptr, isLeaf,
                       0, 0, 0, false, nullptr};
    // Luu nut vao danh sach lien ket de quan ly va giai phong bo nho.
    p->nextAllocated = allocatedHead;
    allocatedHead = p;
    ++n;
    return p;
}

void clearTree() {
    while (allocatedHead != nullptr) {
        Node* old = allocatedHead;
        allocatedHead = allocatedHead->nextAllocated;
        delete old;
    }
    root = nullptr;
    n = 0;
}

Node* findById(int id) {
    for (Node* p = allocatedHead; p != nullptr; p = p->nextAllocated)
        if (p->id == id) return p;
    return nullptr;
}

void loadSampleTree() {
    clearTree();
    Node* a = createNode(1, "DTB < 2.0?", false);
    Node* b = createNode(2, "No >= 12 tin chi?", false);
    Node* c = createNode(3, "DTB >= 3.2?", false);
    Node* d = createNode(4, "Canh bao hoc vu muc 2", true);
    Node* e = createNode(5, "Canh bao hoc vu muc 1", true);
    Node* f = createNode(6, "De xuat khen thuong", true);
    Node* g = createNode(7, "Theo doi binh thuong", true);
    root = a;
    a->left = b; a->right = c;
    b->left = d; b->right = e;
    c->left = f; c->right = g;
    cout << "Da nap cay mau gom 7 nut, root ID = 1.\n";
}

bool visitTree(Node* p, int& visitedCount) {
    if (p == nullptr) return true;
    if (p->visited) return false; // Chu trinh hoac cung nut di toi nhieu lan.
    p->visited = true;
    ++visitedCount;
    // Khong dung && de van kiem tra ca hai nhanh.
    bool leftOK = visitTree(p->left, visitedCount);
    bool rightOK = visitTree(p->right, visitedCount);
    return leftOK && rightOK;
}

bool validateTree() {
    if (root == nullptr || n < 1 || n > MAX_NODES) return false;
    for (Node* p = allocatedHead; p != nullptr; p = p->nextAllocated) {
        p->parentCount = 0;
        p->visited = false;
        if (p->left != nullptr && p->left == p->right) return false;
        if (p->isLeaf) {
            if (p->left != nullptr || p->right != nullptr) return false;
        } else {
            if (p->left == nullptr || p->right == nullptr) return false;
        }
    }
    for (Node* p = allocatedHead; p != nullptr; p = p->nextAllocated) {
        if (p->left != nullptr) ++p->left->parentCount;
        if (p->right != nullptr) ++p->right->parentCount;
    }
    for (Node* p = allocatedHead; p != nullptr; p = p->nextAllocated) {
        if (p->parentCount != (p == root ? 0 : 1)) return false;
    }
    int visitedCount = 0;
    return visitTree(root, visitedCount) && visitedCount == n;
}

void inputTree() {
    int total = readInt("Nhap so nut (1..100): ");
    if (total < 1 || total > MAX_NODES) {
        cout << "So nut khong hop le!\n";
        return;
    }
    clearTree();
    cout << "Nhap ID cua cac nut; ID 0 duoc dung de chi khong co con.\n";
    for (int i = 1; i <= total; ++i) {
        cout << "\n--- Nhap nut thu " << i << " ---\n";
        int id = readInt("ID (khac 0): ");
        if (id == 0 || findById(id) != nullptr) {
            cout << "ID bang 0 hoac bi trung. Huy cay vua nhap.\n";
            clearTree();
            return;
        }
        string content = readContent();
        int leaf = readInt("La nut la? (1: Co, 0: Khong): ");
        if (leaf != 0 && leaf != 1) {
            cout << "Gia tri isLeaf khong hop le!\n";
            clearTree();
            return;
        }
        Node* p = createNode(id, content, leaf == 1);
        if (!p->isLeaf) {
            p->leftId = readInt("ID con trai (nhanh Co): ");
            p->rightId = readInt("ID con phai (nhanh Khong): ");
        }
        if (i == 1) root = p; // Giu quy uoc nut nhap dau tien la goc.
    }

    // Lan 2: gan dia chi cac nut theo ID, khong phu thuoc thu tu nhap.
    for (Node* p = allocatedHead; p != nullptr; p = p->nextAllocated) {
        if (p->isLeaf) continue;
        if (p->leftId == 0 || p->rightId == 0) {
            cout << "Nut cau hoi phai co du hai con. Huy cay.\n";
            clearTree();
            return;
        }
        p->left = findById(p->leftId);
        p->right = findById(p->rightId);
        if (p->left == nullptr || p->right == nullptr) {
            cout << "Co ID con khong ton tai. Huy cay.\n";
            clearTree();
            return;
        }
    }
    if (!validateTree()) {
        cout << "Cay khong hop le (chu trinh, cha-con, nut la hoac ket noi). Da huy du lieu.\n";
        clearTree();
        return;
    }
    cout << "Nhap cay thanh cong. Root ID = " << root->id << ".\n";
}

void showTreeNodes(Node* p, const string& position) {
    if (p == nullptr) return;
    cout << left << setw(10) << position
         << setw(7) << p->id
         << setw(30) << p->content.substr(0, 29)
         << setw(9) << (p->left ? to_string(p->left->id) : "NULL")
         << setw(9) << (p->right ? to_string(p->right->id) : "NULL")
         << (p->isLeaf ? 1 : 0) << '\n';
    showTreeNodes(p->left, "L-" + to_string(p->id));
    showTreeNodes(p->right, "R-" + to_string(p->id));
}

void showTree() {
    cout << "\n" << left << setw(10) << "Vi tri" << setw(7) << "ID"
         << setw(30) << "Noi dung" << setw(9) << "Left ID"
         << setw(9) << "Right ID" << "isLeaf\n";
    showTreeNodes(root, "ROOT");
}

void preorder(Node* p) {
    if (p == nullptr) return;
    cout << p->id << ' ';
    preorder(p->left);
    preorder(p->right);
}
void inorder(Node* p) {
    if (p == nullptr) return;
    inorder(p->left);
    cout << p->id << ' ';
    inorder(p->right);
}
void postorder(Node* p) {
    if (p == nullptr) return;
    postorder(p->left);
    postorder(p->right);
    cout << p->id << ' ';
}
void traverseTree() {
    cout << "Tien tu (NLR): "; preorder(root);
    cout << "\nTrung tu (LNR): "; inorder(root);
    cout << "\nHau tu (LRN): "; postorder(root);
    cout << '\n';
}

bool findPath(Node* current, Node* target, string& path) {
    if (current == nullptr) return false;
    if (current == target) {
        path = to_string(current->id);
        return true;
    }
    if (findPath(current->left, target, path) ||
        findPath(current->right, target, path)) {
        path = to_string(current->id) + " -> " + path;
        return true;
    }
    return false;
}

void searchAndPrintPath() {
    int id = readInt("Nhap ID can tim: ");
    Node* p = findById(id);
    if (p == nullptr) {
        cout << "Khong tim thay nut!\n";
        return;
    }
    cout << "Tim thay: ID = " << p->id << ", noi dung = " << p->content << '\n';
    string path;
    if (findPath(root, p, path)) cout << "Duong di (goc den dich): " << path << '\n';
}

int height(Node* p) {
    if (p == nullptr) return 0;
    int l = height(p->left), r = height(p->right);
    return 1 + (l > r ? l : r);
}
int countLeaves(Node* p) {
    if (p == nullptr) return 0;
    if (p->left == nullptr && p->right == nullptr) return 1;
    return countLeaves(p->left) + countLeaves(p->right);
}
void showStatistics() {
    cout << "Tong so nut: " << n << '\n';
    cout << "So nut la: " << countLeaves(root) << '\n';
    cout << "Chieu cao (tinh theo so muc): " << height(root) << '\n';
}

void runDecisionTree() {
    Node* current = root;
    string answer;
    while (current != nullptr && !current->isLeaf) {
        cout << "\n[" << current->id << "] " << current->content
             << " (y: Co, n: Khong): ";
        if (!getline(cin, answer)) return;
        if (answer == "y" || answer == "Y") current = current->left;
        else if (answer == "n" || answer == "N") current = current->right;
        else cout << "Chi duoc nhap y hoac n!\n";
    }
    if (current != nullptr)
        cout << "\nKET LUAN: " << current->content << " (nut " << current->id << ")\n";
    else cout << "Du lieu cay bi loi.\n";
}

void showMenu() {
    cout << "\n========== TREE POINTER PRACTICE (C++) =========="
         << "\n1. Khoi tao cay mau (7 nut)"
         << "\n2. Nhap cay thu cong bang ID"
         << "\n3. Hien thi cac nut va lien ket con tro"
         << "\n4. Duyet tien tu / trung tu / hau tu"
         << "\n5. Tim nut theo ID va in duong di"
         << "\n6. Thong ke so nut la va chieu cao"
         << "\n7. Mo phong tu van hoc vu"
         << "\n0. Thoat\n";
}

int main() {
    while (true) {
        showMenu();
        int choice = readInt("Chon: ");
        if (choice == 0) {
            cout << "Tam biet!\n";
            break;
        }
        if (choice >= 3 && choice <= 7 && root == nullptr) {
            cout << "Cay chua duoc khoi tao! Chon 1 hoac 2 truoc.\n";
            continue;
        }
        switch (choice) {
            case 1: loadSampleTree(); break;
            case 2: inputTree(); break;
            case 3: showTree(); break;
            case 4: traverseTree(); break;
            case 5: searchAndPrintPath(); break;
            case 6: showStatistics(); break;
            case 7: runDecisionTree(); break;
            default: cout << "Chuc nang khong hop le!\n";
        }
    }
    clearTree();
    return 0;
}
