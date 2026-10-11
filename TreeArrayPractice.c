#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define EMPTY 0

typedef struct {
    int id;                 // Ma nut
    char content[120];      // Cau hoi hoac ket luan
    int left;               // Chi so con trai (Co)
    int right;              // Chi so con phai (Khong)
    int isLeaf;             // 1: nut ket luan, 0: nut cau hoi
} Node;

Node Tree[MAX + 1];         // Dung chi so tu 1 den MAX
int root = 1;
int n = 0;

// -------------------- NHAP DU LIEU --------------------
int readInt(const char *message) {
    char line[128], extra;
    int value;
    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL) exit(0);
        if (sscanf(line, " %d %c", &value, &extra) == 1) return value;
        printf("Vui long nhap mot so nguyen hop le!\n");
    }
}

void readContent(char content[], int size) {
    while (1) {
        printf("Noi dung: ");
        if (fgets(content, size, stdin) == NULL) exit(0);
        if (strchr(content, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
        content[strcspn(content, "\n")] = '\0';
        if (content[0] != '\0') return;
        printf("Noi dung khong duoc rong!\n");
    }
}

void clearTree(void) {
    memset(Tree, 0, sizeof(Tree));
    root = 1;
    n = 0;
}

// -------------------- CAY MAU --------------------
void loadSampleTree(void) {
    clearTree();
    n = 7;
    Tree[1] = (Node){1, "DTB < 2.0?", 2, 3, 0};
    Tree[2] = (Node){2, "No >= 12 tin chi?", 4, 5, 0};
    Tree[3] = (Node){3, "DTB >= 3.2?", 6, 7, 0};
    Tree[4] = (Node){4, "Canh bao hoc vu muc 2", 0, 0, 1};
    Tree[5] = (Node){5, "Canh bao hoc vu muc 1", 0, 0, 1};
    Tree[6] = (Node){6, "De xuat khen thuong", 0, 0, 1};
    Tree[7] = (Node){7, "Theo doi binh thuong", 0, 0, 1};
    printf("Da nap cay mau gom 7 nut, root = 1.\n");
}

// Kiem tra tinh hop le, de ham de quy khong lap vo han.
int visitTree(int i, int visited[]) {
    if (i == EMPTY) return 1;
    if (visited[i]) return 0;
    visited[i] = 1;
    return visitTree(Tree[i].left, visited)
        && visitTree(Tree[i].right, visited);
}

int validateTree(void) {
    int parents[MAX + 1] = {0};
    int visited[MAX + 1] = {0};
    int i, j;

    for (i = 1; i <= n; i++) {
        if (Tree[i].isLeaf != 0 && Tree[i].isLeaf != 1) return 0;
        if (Tree[i].left < 0 || Tree[i].left > n ||
            Tree[i].right < 0 || Tree[i].right > n) return 0;
        if (Tree[i].left != 0 && Tree[i].left == Tree[i].right) return 0;

        if (Tree[i].isLeaf == 1) {
            if (Tree[i].left != 0 || Tree[i].right != 0) return 0;
        } else {
            // Nut cau hoi phai co du hai nhanh Co/Khong.
            if (Tree[i].left == 0 || Tree[i].right == 0) return 0;
        }

        for (j = 1; j < i; j++) {
            if (Tree[i].id == Tree[j].id) return 0;
        }
        if (Tree[i].left) parents[Tree[i].left]++;
        if (Tree[i].right) parents[Tree[i].right]++;
    }

    if (parents[root] != 0) return 0;
    for (i = 2; i <= n; i++) {
        if (parents[i] != 1) return 0;
    }
    if (!visitTree(root, visited)) return 0;
    for (i = 1; i <= n; i++) {
        if (!visited[i]) return 0;
    }
    return 1;
}

// -------------------- NHAP CAY THU CONG --------------------
void inputTree(void) {
    int i, total = readInt("Nhap so nut (1..100): ");
    if (total < 1 || total > MAX) {
        printf("So nut khong hop le!\n");
        return;
    }

    clearTree();
    n = total;
    for (i = 1; i <= n; i++) {
        printf("\n--- Nhap nut tai chi so %d ---\n", i);
        Tree[i].id = readInt("ID: ");
        readContent(Tree[i].content, (int)sizeof(Tree[i].content));
        Tree[i].left = readInt("Chi so con trai (0 neu khong co): ");
        Tree[i].right = readInt("Chi so con phai (0 neu khong co): ");
        Tree[i].isLeaf = readInt("La nut la? (1: Co, 0: Khong): ");
    }

    if (!validateTree()) {
        printf("Cay khong hop le! Kiem tra ID, chi so, chu trinh,\n");
        printf("quan he cha-con va tinh trang nut la. Da huy du lieu vua nhap.\n");
        clearTree();
        return;
    }
    printf("Nhap cay thanh cong. Root = %d.\n", root);
}

// -------------------- HIEN THI --------------------
void showTree(void) {
    int i;
    printf("\n%-7s %-7s %-30s %-7s %-7s %-7s\n",
           "Index", "ID", "Noi dung", "Left", "Right", "isLeaf");
    for (i = 1; i <= n; i++) {
        printf("%-7d %-7d %-30.30s %-7d %-7d %-7d\n",
               i, Tree[i].id, Tree[i].content,
               Tree[i].left, Tree[i].right, Tree[i].isLeaf);
    }
}

// -------------------- DUYET CAY --------------------
void preorder(int i) {
    if (i == EMPTY) return;
    printf("%d ", Tree[i].id);
    preorder(Tree[i].left);
    preorder(Tree[i].right);
}

void inorder(int i) {
    if (i == EMPTY) return;
    inorder(Tree[i].left);
    printf("%d ", Tree[i].id);
    inorder(Tree[i].right);
}

void postorder(int i) {
    if (i == EMPTY) return;
    postorder(Tree[i].left);
    postorder(Tree[i].right);
    printf("%d ", Tree[i].id);
}

void traverseTree(void) {
    printf("Tien tu (NLR): "); preorder(root);
    printf("\nTrung tu (LNR): "); inorder(root);
    printf("\nHau tu (LRN): "); postorder(root);
    printf("\n");
}

// -------------------- TIM KIEM, DUONG DI --------------------
int findIndexById(int targetId) {
    int i;
    for (i = 1; i <= n; i++) {
        if (Tree[i].id == targetId) return i;
    }
    return EMPTY;
}

int findPath(int current, int targetIndex, int path[], int *length) {
    if (current == EMPTY) return 0;
    path[(*length)++] = current;
    if (current == targetIndex) return 1;

    if (findPath(Tree[current].left, targetIndex, path, length)) return 1;
    if (findPath(Tree[current].right, targetIndex, path, length)) return 1;

    (*length)--; // Quay lui neu khong tim thay trong nhanh nay.
    return 0;
}

void searchAndPrintPath(void) {
    int mode = readInt("Tim theo (1: chi so, 2: ID): ");
    int target, index, path[MAX + 1], length = 0, i;
    if (mode != 1 && mode != 2) {
        printf("Lua chon khong hop le!\n");
        return;
    }

    target = readInt("Nhap gia tri can tim: ");
    index = (mode == 1) ? target : findIndexById(target);
    if (index < 1 || index > n) {
        printf("Khong tim thay nut!\n");
        return;
    }

    printf("Tim thay: index = %d, ID = %d, noi dung = %s\n",
           index, Tree[index].id, Tree[index].content);
    if (findPath(root, index, path, &length)) {
        printf("Duong di theo chi so: ");
        for (i = 0; i < length; i++) {
            if (i) printf(" -> ");
            printf("%d", path[i]);
        }
        printf("\n");
    }
}

// -------------------- THONG KE --------------------
int height(int i) {
    int hLeft, hRight;
    if (i == EMPTY) return 0;
    hLeft = height(Tree[i].left);
    hRight = height(Tree[i].right);
    return 1 + (hLeft > hRight ? hLeft : hRight);
}

int countLeaves(int i) {
    if (i == EMPTY) return 0;
    if (Tree[i].left == EMPTY && Tree[i].right == EMPTY) return 1;
    return countLeaves(Tree[i].left) + countLeaves(Tree[i].right);
}

void showStatistics(void) {
    printf("Tong so nut: %d\n", n);
    printf("So nut la: %d\n", countLeaves(root));
    printf("Chieu cao (tinh theo so muc): %d\n", height(root));
}

// -------------------- MO PHONG TU VAN --------------------
void runDecisionTree(void) {
    int current = root;
    char answer[32];
    while (current != EMPTY && Tree[current].isLeaf == 0) {
        printf("\n[%d] %s (y: Co, n: Khong): ",
               Tree[current].id, Tree[current].content);
        if (fgets(answer, sizeof(answer), stdin) == NULL) return;
        if (answer[0] == 'y' || answer[0] == 'Y') {
            current = Tree[current].left;
        } else if (answer[0] == 'n' || answer[0] == 'N') {
            current = Tree[current].right;
        } else {
            printf("Chi duoc nhap y hoac n!\n");
        }
    }
    if (current != EMPTY)
        printf("\nKET LUAN: %s (nut %d)\n", Tree[current].content, Tree[current].id);
    else
        printf("Du lieu cay bi loi.\n");
}

void showMenu(void) {
    printf("\n========== TREE ARRAY PRACTICE ==========\n");
    printf("1. Khoi tao cay mau (7 nut)\n");
    printf("2. Nhap cay thu cong\n");
    printf("3. Hien thi bang mang\n");
    printf("4. Duyet tien tu / trung tu / hau tu\n");
    printf("5. Tim nut va in duong di\n");
    printf("6. Thong ke so nut la va chieu cao\n");
    printf("7. Mo phong tu van hoc vu\n");
    printf("0. Thoat\n");
}

int main(void) {
    int choice;
    clearTree();
    do {
        showMenu();
        choice = readInt("Chon: ");
        if (choice == 0) {
            printf("Tam biet!\n");
            break;
        }
        if (choice >= 3 && choice <= 7 && n == 0) {
            printf("Cay chua duoc khoi tao! Chon 1 hoac 2 truoc.\n");
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
            default: printf("Chuc nang khong hop le!\n");
        }
    } while (1);
    return 0;
}
