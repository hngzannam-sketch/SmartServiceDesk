# TREE POINTER PRACTICE — Cây nhị phân bằng con trỏ (C++)

## 1. Mô tả bài toán

Chương trình xây dựng **cây nhị phân quyết định để mô phỏng tư vấn học vụ**. Mỗi nút là một câu hỏi có hai nhánh trả lời hoặc một kết luận. Người dùng có thể tạo cây mẫu, nhập cây thủ công, xem cấu trúc cây, duyệt cây, tìm kiếm, thống kê và chạy quá trình tư vấn.

Bài này là phiên bản **dùng con trỏ** của bài biểu diễn cây bằng mảng. Các nút được cấp phát động với `new`, liên kết trực tiếp bằng `Node* left` và `Node* right`, không dùng chỉ số mảng làm liên kết giữa các nút.

## 2. Yêu cầu môi trường

- Trình biên dịch C++ hỗ trợ C++11 trở lên (ví dụ `g++`).
- Có thể sử dụng VS Code với terminal hoặc bất kỳ IDE C++ phù hợp.
- Tệp mã nguồn: `TreePointerPractice.cpp`.

## 3. Cách biên dịch và chạy

Mở terminal trong thư mục chứa `TreePointerPractice.cpp`.

**Windows (PowerShell, VS Code):**

```powershell
g++ -std=c++11 TreePointerPractice.cpp -o TreePointerPractice.exe
.\TreePointerPractice.exe
```

**Linux/macOS:**

```bash
g++ -std=c++11 TreePointerPractice.cpp -o TreePointerPractice
./TreePointerPractice
```

Nếu terminal báo không nhận diện được `g++`, hãy cài trình biên dịch C++ và cấu hình PATH trước khi chạy. VS Code là trình soạn thảo, không tự cung cấp trình biên dịch `g++`.

## 4. Cấu trúc dữ liệu

```cpp
struct Node {
    int id;
    string content;
    Node* left;
    Node* right;
    bool isLeaf;

    int leftId;
    int rightId;
    int parentCount;
    bool visited;
    Node* nextAllocated;
};
```

| Trường | Ý nghĩa |
|---|---|
| `id` | Mã duy nhất của nút; ID `0` không hợp lệ. |
| `content` | Nội dung câu hỏi hoặc kết luận. |
| `left` | Con trỏ tới nhánh **Có** (`y`). |
| `right` | Con trỏ tới nhánh **Không** (`n`). |
| `isLeaf` | `true` nếu là nút kết luận, `false` nếu là câu hỏi. |
| `leftId`, `rightId` | ID con tạm thời khi nhập; sau đó chuyển thành con trỏ. |
| `parentCount`, `visited` | Dùng để kiểm tra cây hợp lệ. |
| `nextAllocated` | Nối các nút đã cấp phát để giải phóng bộ nhớ. |

Các biến quản lý chính:

```cpp
Node* root = nullptr;           // Nút gốc
Node* allocatedHead = nullptr;  // Đầu danh sách các nút được cấp phát
int n = 0;                      // Tổng số nút
```

**Lưu ý:** `nextAllocated` chỉ là danh sách phụ quản lý bộ nhớ, không phải cạnh của cây nhị phân.

## 5. Cây mẫu

```text
                         [1] DTB < 2.0?
                         /             \
                      Có/y             Không/n
                       /                  \
          [2] No >= 12 tin chi?      [3] DTB >= 3.2?
                /      \                  /      \
              Có        Không            Có       Không
              /           \              /          \
 [4] Canh bao hoc vu  [5] Canh bao   [6] De xuat  [7] Theo doi
         muc 2         hoc vu muc 1    khen thuong   binh thuong
```

Cây mẫu có **7 nút**, **4 nút lá**, **3 mức**. Nhánh trái ứng với trả lời **Có**, nhánh phải ứng với **Không**.

## 6. Hướng dẫn sử dụng menu

| Phím | Chức năng | Mô tả |
|---|---|---|
| `1` | Khởi tạo cây mẫu | Tạo cây tư vấn học vụ gồm 7 nút. |
| `2` | Nhập cây thủ công | Nhập ID, nội dung, loại nút và ID của hai nút con. |
| `3` | Hiển thị cây | In vị trí, ID, nội dung, ID hai con và `isLeaf`. |
| `4` | Duyệt cây | In thứ tự NLR, LNR, LRN. |
| `5` | Tìm nút | Tìm theo ID và in đường đi từ gốc. |
| `6` | Thống kê | In tổng nút, số nút lá, chiều cao theo số mức. |
| `7` | Tư vấn học vụ | Lần lượt trả lời `y` hoặc `n` để đến kết luận. |
| `0` | Thoát | Giải phóng bộ nhớ và kết thúc. |

Phải chọn **1 hoặc 2** để tạo cây trước khi dùng các chức năng từ **3 đến 7**.

## 7. Ví dụ chạy thử

### Ví dụ A — Dùng cây mẫu

Nhập `1`, sau đó nhập `4` để xem ba kiểu duyệt:

```text
Tien tu (NLR): 1 2 4 5 3 6 7
Trung tu (LNR): 4 2 5 1 6 3 7
Hau tu (LRN): 4 5 2 6 7 3 1
```

Nhập `6` để thống kê:

```text
Tong so nut: 7
So nut la: 4
Chieu cao (tinh theo so muc): 3
```

Nhập `5` và tìm ID `7`:

```text
Nhap ID can tim: 7
Tim thay: ID = 7, noi dung = Theo doi binh thuong
Duong di (goc den dich): 1 -> 3 -> 7
```

Nhập `7` và trả lời `n`, rồi `n`:

```text
[1] DTB < 2.0? (y: Co, n: Khong): n
[3] DTB >= 3.2? (y: Co, n: Khong): n

KET LUAN: Theo doi binh thuong (nut 7)
```

### Ví dụ B — Tự nhập cây 3 nút

Chọn menu `2` và nhập:

```text
Nhap so nut (1..100): 3

--- Nhap nut thu 1 ---
ID (khac 0): 1
Noi dung: Ban co di hoc khong?
La nut la? (1: Co, 0: Khong): 0
ID con trai (nhanh Co): 2
ID con phai (nhanh Khong): 3

--- Nhap nut thu 2 ---
ID (khac 0): 2
Noi dung: Di hoc
La nut la? (1: Co, 0: Khong): 1

--- Nhap nut thu 3 ---
ID (khac 0): 3
Noi dung: Nghi hoc
La nut la? (1: Co, 0: Khong): 1
```

Cây được tạo:

```text
         [1] Ban co di hoc khong?
           /                 \
     [2] Di hoc          [3] Nghi hoc
```

Sau đó chọn `7`, nhập `y` để nhận kết luận **Di hoc**.

## 8. Các hàm chính và thuật toán

| Hàm | Vai trò |
|---|---|
| `readInt()` / `readContent()` | Nhập và kiểm tra dữ liệu. |
| `createNode()` | Cấp phát một nút mới bằng `new`. |
| `clearTree()` | Dùng `delete` giải phóng tất cả các nút đã cấp phát. |
| `findById()` | Tìm nút theo ID trong danh sách quản lý cấp phát. |
| `loadSampleTree()` | Tạo và nối 7 nút mẫu bằng con trỏ. |
| `inputTree()` | Nhập các nút, ánh xạ ID con thành địa chỉ Node. |
| `validateTree()` / `visitTree()` | Kiểm tra số cha, nút lá, khả năng đi đến mọi nút và chu trình. |
| `showTree()` / `showTreeNodes()` | Hiển thị cây theo dạng bảng bằng đệ quy. |
| `preorder()` | Duyệt **Gốc – Trái – Phải** (NLR). |
| `inorder()` | Duyệt **Trái – Gốc – Phải** (LNR). |
| `postorder()` | Duyệt **Trái – Phải – Gốc** (LRN). |
| `findPath()` | Đệ quy tìm đường đi từ gốc đến nút đích. |
| `height()` | Tính chiều cao cây theo số mức. |
| `countLeaves()` | Đếm các nút không có con. |
| `runDecisionTree()` | Duyệt theo câu trả lời `y`/`n` cho đến nút lá. |

## 9. Quy tắc nhập cây

- Số nút: từ **1 đến 100**.
- Mọi ID phải khác `0` và **không trùng nhau**.
- **Nút đầu tiên** được nhập là **gốc**.
- Mỗi nút câu hỏi (`isLeaf = 0`) phải có **đúng hai nút con**.
- Nút lá (`isLeaf = 1`) không có nút con.
- Mỗi nút không phải gốc có đúng một nút cha; gốc không có cha.
- Toàn bộ nút phải kết nối thành một cây hợp lệ, không có chu trình.
- Nội dung không được để trống và phải ngắn hơn 120 ký tự.
- Có thể khai báo ID con trước khi nhập thông tin nút con, vì liên kết được thiết lập sau khi nhập đủ các nút.
- Nếu dữ liệu cây không hợp lệ, chương trình hủy cây vừa nhập.

## 10. So sánh với phiên bản lưu cây bằng mảng

| Phiên bản mảng | Phiên bản con trỏ |
|---|---|
| `Node Tree[MAX + 1]` | `Node* root` và các nút được `new` |
| `int left`, `int right` | `Node* left`, `Node* right` |
| `Tree[i].left` là chỉ số | `p->left` là địa chỉ nút con |
| Duyệt dựa trên chỉ số mảng | Duyệt theo các liên kết con trỏ |
| Quản lý vùng lưu trữ mảng | Cần `delete` khi không còn sử dụng |

Mục đích học tập chính là hiểu **cấp phát động**, **trỏ đến nút**, **liên kết cha–con**, **đệ quy trên cây** và **giải phóng bộ nhớ**.

## 11. Giới hạn hiện tại

- Chương trình chạy trên terminal, chưa có giao diện đồ họa.
- Dữ liệu chỉ lưu trong bộ nhớ; khi thoát sẽ mất. Chưa có chức năng ghi/đọc tệp.
- Chưa hỗ trợ thêm, xóa, sửa một nút trong cây sau khi tạo; muốn đổi toàn bộ cây hãy chọn chức năng `1` hoặc `2`.
- Đây là **cây quyết định nhị phân**, không phải **cây nhị phân tìm kiếm (BST)**: không có quy tắc ID con trái nhỏ hơn ID cha.

## 12. Cấu trúc thư mục gợi ý

```text
TreePointerPractice/
├── TreePointerPractice.cpp
└── README.md
```
