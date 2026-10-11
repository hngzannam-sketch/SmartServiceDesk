#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX = 100;
const int EMPTY = 0;

struct Node {
    int id;              
    string content;        
    int left;               
    int right;              
    int isLeaf;             
};
Node Tree[MAX + 1];
int root = 1;
int n = 0;
int readInt(const string &message) {
    string line;
    int value;
    string extra;
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
void clearTree() {
    for (int i = 0; i <= MAX; ++i) Tree[i] = Node{};
    root = 1;
    n = 0;
}
void loadSampleTree() {
    clearTree();
    n = 7;
    Tree[1] = {1, "DTB < 2.0?", 2, 3, 0};
    Tree[2] = {2, "No >= 12 tin chi?", 4, 5, 0};
    Tree[3] = {3, "DTB >= 3.2?", 6, 7, 0};
    Tree[4] = {4, "Canh bao hoc vu muc 2", 0, 0, 1};
    Tree[5] = {5, "Canh bao hoc vu muc 1", 0, 0, 1};
    Tree[6] = {6, "De xuat khen thuong", 0, 0, 1};
    Tree[7] = {7, "Theo doi binh thuong", 0, 0, 1};
    cout << "Da nap cay mau gom 7 nut, root = 1.\n";
}
bool visitTree(int i, bool visited[]) {
    if (i == EMPTY) return true;
    if (visited[i]) return false;
    visited[i] = true;
    return visitTree(Tree[i].left, visited)
        && visitTree(Tree[i].right, visited);
}

bool validateTree() {
    if (n < 1 || n > MAX) return false;
    int parents[MAX + 1] = {};
    bool visited[MAX + 1] = {};

    for (int i = 1; i <= n; ++i) {
        if (Tree[i].isLeaf != 0 && Tree[i].isLeaf != 1) return false;
        if (Tree[i].left < 0 || Tree[i].left > n ||
            Tree[i].right < 0 || Tree[i].right > n) return false;
        if (Tree[i].left != 0 && Tree[i].left == Tree[i].right) return false;

        if (Tree[i].isLeaf == 1) {
            if (Tree[i].left != 0 || Tree[i].right != 0) return false;
        } else if (Tree[i].left == 0 || Tree[i].right == 0) {
            return false; // Nut cau hoi can du 2 nhanh Co/Khong.
        }

        for (int j = 1; j < i; ++j) {
            if (Tree[i].id == Tree[j].id) return false;
        }
        if (Tree[i].left) ++parents[Tree[i].left];
        if (Tree[i].right) ++parents[Tree[i].right];
    }

    if (parents[root] != 0) return false;
    for (int i = 2; i <= n; ++i) {
        if (parents[i] != 1) return false;
    }
    if (!visitTree(root, visited)) return false;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) return false;
    }
    return true;
}
void inputTree() {
    int total = readInt("Nhap so nut (1..100): ");
    if (total < 1 || total > MAX) {
        cout << "So nut khong hop le!\n";
        return;
    }

    clearTree();
    n = total;
    for (int i = 1; i <= n; ++i) {
        cout << "\n--- Nhap nut tai chi so " << i << " ---\n";
        Tree[i].id = readInt("ID: ");
        Tree[i].content = readContent();
        Tree[i].left = readInt("Chi so con trai (0 neu khong co): ");
        Tree[i].right = readInt("Chi so con phai (0 neu khong co): ");
        Tree[i].isLeaf = readInt("La nut la? (1: Co, 0: Khong): ");
    }

    if (!validateTree()) {
        cout << "Cay khong hop le! Kiem tra ID, chi so, chu trinh,\n"
             << "quan he cha-con va tinh trang nut la. Da huy du lieu vua nhap.\n";
        clearTree();
        return;
    }
    cout << "Nhap cay thanh cong. Root = " << root << ".\n";
}
void showTree() {
    cout << "\n" << left << setw(7) << "Index"
         << setw(7) << "ID" << setw(30) << "Noi dung"
         << setw(7) << "Left" << setw(7) << "Right" << "isLeaf\n";
    for (int i = 1; i <= n; ++i) {
        cout << left << setw(7) << i
             << setw(7) << Tree[i].id
             << setw(30) << Tree[i].content.substr(0, 29)
             << setw(7) << Tree[i].left
             << setw(7) << Tree[i].right
             << Tree[i].isLeaf << '\n';
    }
}
void preorder(int i) {
    if (i == EMPTY) return;
    cout << Tree[i].id << ' ';
    preorder(Tree[i].left);
    preorder(Tree[i].right);
}

void inorder(int i) {
    if (i == EMPTY) return;
    inorder(Tree[i].left);
    cout << Tree[i].id << ' ';
    inorder(Tree[i].right);
}

void postorder(int i) {
    if (i == EMPTY) return;
    postorder(Tree[i].left);
    postorder(Tree[i].right);
    cout << Tree[i].id << ' ';
}

void traverseTree() {
    cout << "Tien tu (NLR): "; preorder(root);
    cout << "\nTrung tu (LNR): "; inorder(root);
    cout << "\nHau tu (LRN): "; postorder(root);
    cout << '\n';
}
int findIndexById(int targetId) {
    for (int i = 1; i <= n; ++i) {
        if (Tree[i].id == targetId) return i;
    }
    return EMPTY;
}

bool findPath(int current, int targetIndex, int path[], int &length) {
    if (current == EMPTY) return false;
    path[length++] = current;
    if (current == targetIndex) return true;

    if (findPath(Tree[current].left, targetIndex, path, length)) return true;
    if (findPath(Tree[current].right, targetIndex, path, length)) return true;

    --length; // Quay lui khi nhanh nay khong chua nut can tim.
    return false;
}

void searchAndPrintPath() {
    int mode = readInt("Tim theo (1: chi so, 2: ID): ");
    if (mode != 1 && mode != 2) {
        cout << "Lua chon khong hop le!\n";
        return;
    }
    int target = readInt("Nhap gia tri can tim: ");
    int index = (mode == 1) ? target : findIndexById(target);
    if (index < 1 || index > n) {
        cout << "Khong tim thay nut!\n";
        return;
    }

    cout << "Tim thay: index = " << index << ", ID = " << Tree[index].id
         << ", noi dung = " << Tree[index].content << '\n';

    int path[MAX + 1] = {};
    int length = 0;
    if (findPath(root, index, path, length)) {
        cout << "Duong di theo chi so: ";
        for (int i = 0; i < length; ++i) {
            if (i > 0) cout << " -> ";
            cout << path[i];
        }
        cout << '\n';
    }
}
int height(int i) {
    if (i == EMPTY) return 0;
    int hLeft = height(Tree[i].left);
    int hRight = height(Tree[i].right);
    return 1 + (hLeft > hRight ? hLeft : hRight);
}

int countLeaves(int i) {
    if (i == EMPTY) return 0;
    if (Tree[i].left == EMPTY && Tree[i].right == EMPTY) return 1;
    return countLeaves(Tree[i].left) + countLeaves(Tree[i].right);
}

void showStatistics() {
    cout << "Tong so nut: " << n << '\n';
    cout << "So nut la: " << countLeaves(root) << '\n';
    cout << "Chieu cao (tinh theo so muc): " << height(root) << '\n';
}
void runDecisionTree() {
    int current = root;
    string answer;
    while (current != EMPTY && Tree[current].isLeaf == 0) {
        cout << "\n[" << Tree[current].id << "] " << Tree[current].content
             << " (y: Co, n: Khong): ";
        if (!getline(cin, answer)) return;
        if (answer == "y" || answer == "Y") {
            current = Tree[current].left;
        } else if (answer == "n" || answer == "N") {
            current = Tree[current].right;
        } else {
            cout << "Chi duoc nhap y hoac n!\n";
        }
    }
    if (current != EMPTY) {
        cout << "\nKET LUAN: " << Tree[current].content
             << " (nut " << Tree[current].id << ")\n";
    } else {
        cout << "Du lieu cay bi loi.\n";
    }
}
void showMenu() {
    cout << "\n========== TREE ARRAY PRACTICE (C++) ==========\n"
         << "1. Khoi tao cay mau (7 nut)\n"
         << "2. Nhap cay thu cong\n"
         << "3. Hien thi bang mang\n"
         << "4. Duyet tien tu / trung tu / hau tu\n"
         << "5. Tim nut va in duong di\n"
         << "6. Thong ke so nut la va chieu cao\n"
         << "7. Mo phong tu van hoc vu\n"
         << "0. Thoat\n";
}

int main() {
    clearTree();
    while (true) {
        showMenu();
        int choice = readInt("Chon: ");
        if (choice == 0) {
            cout << "Tam biet!\n";
            break;
        }
        if (choice >= 3 && choice <= 7 && n == 0) {
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
    return 0;
}
