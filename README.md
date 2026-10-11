# BÀI THỰC HÀNH: CÂY NHỊ PHÂN DẠNG MẢNG TRONG C++

## 1. Giới thiệu bài toán

**Tên chương trình:** `TreeArrayPractice.cpp`  
**Môn học:** Cấu trúc dữ liệu và giải thuật  
**Chủ đề:** Cài đặt cây nhị phân bằng mảng, ứng dụng vào **cây quyết định hỗ trợ cảnh báo học vụ cho sinh viên**.

Phòng đào tạo cần phân loại tình trạng học vụ của sinh viên thông qua các câu hỏi có hai đáp án **Có / Không**. Chương trình lần lượt đặt câu hỏi, đi theo nhánh tương ứng và đưa ra kết luận, chẳng hạn:

- Cảnh báo học vụ mức 2.
- Cảnh báo học vụ mức 1.
- Đề xuất khen thưởng.
- Theo dõi bình thường.

Chương trình sử dụng **mảng để lưu cây**, thay vì cấp phát nút bằng con trỏ động. Ngoài mô phỏng tư vấn, chương trình còn hỗ trợ duyệt cây, tìm kiếm, in đường đi và thống kê.

## 2. Cấu trúc dữ liệu

Mỗi nút được biểu diễn bằng cấu trúc:

```cpp
const int MAX = 100;
const int EMPTY = 0;

struct Node {
    int id;
    string content;       // Câu hỏi hoặc kết luận
    int left;        // Chỉ số nút con trái
    int right;       // Chỉ số nút con phải
    int isLeaf;      // 1: nút kết luận; 0: nút câu hỏi
};

Node Tree[MAX + 1];
int root = 1;
int n = 0;
```

**Quy ước:**

- Các nút hợp lệ được lưu tại `Tree[1]` đến `Tree[n]`, tối đa **100 nút**.
- `root = 1` là chỉ số nút gốc.
- `left` là nhánh **Có (y)**; `right` là nhánh **Không (n)**.
- `left = 0` hoặc `right = 0` nghĩa là không có nút con.
- `isLeaf = 0` là nút câu hỏi, cần có cả hai nhánh; `isLeaf = 1` là nút kết luận, không có nút con.
- `id` dùng để định danh nút và có thể khác chỉ số phần tử trong mảng.

### Cây mẫu có sẵn

```text
                  [1] DTB < 2.0?
                 /                \
              Có                   Không
             /                       \
  [2] No >= 12 tin chi?           [3] DTB >= 3.2?
       /         \                  /         \
      Có        Không              Có         Không
      /           \                /             \
[4] Canh bao   [5] Canh bao   [6] De xuat   [7] Theo doi
    muc 2          muc 1        khen thuong     binh thuong
```

| Index | ID | Nội dung | Left | Right | isLeaf |
|---:|---:|---|---:|---:|---:|
| 1 | 1 | DTB < 2.0? | 2 | 3 | 0 |
| 2 | 2 | No >= 12 tin chi? | 4 | 5 | 0 |
| 3 | 3 | DTB >= 3.2? | 6 | 7 | 0 |
| 4 | 4 | Canh bao hoc vu muc 2 | 0 | 0 | 1 |
| 5 | 5 | Canh bao hoc vu muc 1 | 0 | 0 | 1 |
| 6 | 6 | De xuat khen thuong | 0 | 0 | 1 |
| 7 | 7 | Theo doi binh thuong | 0 | 0 | 1 |

*Trong bảng, các nội dung dùng đúng chuỗi không dấu của chương trình C++ để hiển thị ổn định trên terminal.*

## 3. Chức năng chương trình

| Phím | Chức năng | Mô tả |
|---:|---|---|
| **1** | Khởi tạo cây mẫu | Nạp cây 7 nút như bảng trên. |
| **2** | Nhập cây thủ công | Nhập số nút và thông tin từng nút, kiểm tra cây hợp lệ. |
| **3** | Hiển thị bảng mảng | In chỉ số, ID, nội dung, `left`, `right`, `isLeaf`. |
| **4** | Duyệt cây | In ba thứ tự: tiền tự (NLR), trung tự (LNR), hậu tự (LRN). |
| **5** | Tìm nút và in đường đi | Tìm theo chỉ số hoặc ID; in đường đi từ gốc. |
| **6** | Thống kê | In tổng số nút, số nút lá và chiều cao cây tính theo số mức. |
| **7** | Mô phỏng tư vấn | Trả lời `y`/`n` để đi từ câu hỏi đến kết luận. |
| **0** | Thoát | Kết thúc chương trình. |

## 4. Hướng dẫn cài đặt và chạy

### Yêu cầu

- Có trình biên dịch **C++11** trở lên, ví dụ G++ hoặc MinGW G++.
- Có thể dùng **VS Code**, **Code::Blocks**, **Dev-C++** hoặc terminal.
- Không cần thư viện bên ngoài; dùng các thư viện chuẩn C++: `iostream`, `iomanip`, `sstream`, `string`, `cstdlib`.

### Chạy bằng G++ trên Windows

Mở terminal tại thư mục chứa `TreeArrayPractice.cpp`, nhập:

```powershell
gcc -std=c99 TreeArrayPractice.c -o TreeArrayPractice.exe
.\TreeArrayPractice.exe
```

### Chạy bằng G++ trên Linux / macOS

```bash
gcc -std=c99 TreeArrayPractice.c -o TreeArrayPractice
./TreeArrayPractice
```

### Chạy bằng IDE

1. Mở tệp `TreeArrayPractice.cpp` trong VS Code, Code::Blocks hoặc Dev-C++.
2. Chọn trình biên dịch C++ (G++) và thực hiện **Build/Compile**.
3. Chạy chương trình (**Run**) để xuất hiện menu.

## 5. Hướng dẫn sử dụng chi tiết

**Cách nhanh nhất để kiểm tra chương trình:**

1. Chạy chương trình.
2. Nhập `1` rồi nhấn **Enter** để nạp cây mẫu.
3. Nhập `3` để xem bảng mảng.
4. Nhập `4` để xem ba phép duyệt cây.
5. Nhập `5`, chọn tìm theo `1` (chỉ số), rồi nhập `5` để xem đường đi.
6. Nhập `6` để xem số nút lá và chiều cao.
7. Nhập `7`, trả lời `y` rồi `n` để thử mô phỏng tư vấn.
8. Nhập `0` để thoát.

### Tự nhập cây (chức năng 2)

Chương trình yêu cầu nhập lần lượt:

1. **Số nút:** từ 1 đến 100.
2. **ID:** mã riêng của từng nút, không được trùng.
3. **Nội dung:** câu hỏi hoặc kết luận (không để trống).
4. **Chỉ số con trái / phải:** 0 nếu không có; nếu có, phải thuộc khoảng `1..n`.
5. **isLeaf:** `0` nếu là câu hỏi; `1` nếu là kết luận.

Cây nhập phải có gốc tại vị trí 1, không có chu trình, không có nút có nhiều hơn một cha và tất cả các nút phải nối được từ gốc. Mỗi nút câu hỏi phải có đủ hai nhánh; nút kết luận không có nhánh nào. Nếu dữ liệu không hợp lệ, chương trình thông báo lỗi và hủy cây vừa nhập.

**Lưu ý:** Các chức năng 3–7 chỉ hoạt động sau khi đã nạp cây mẫu hoặc nhập cây hợp lệ. Nạp lại cây mẫu hay nhập cây mới sẽ thay thế dữ liệu cây hiện tại. Chương trình chưa lưu cây ra tệp; dữ liệu mất khi thoát.

## 6. Ví dụ kết quả kiểm thử

### Kiểm thử duyệt cây

Sau khi chọn `1` để khởi tạo, nhập `4`:

```text
Tien tu (NLR): 1 2 4 5 3 6 7
Trung tu (LNR): 4 2 5 1 6 3 7
Hau tu (LRN): 4 5 2 6 7 3 1
```

### Kiểm thử tìm kiếm

Sau khi chọn `5`:

```text
Tim theo (1: chi so, 2: ID): 1
Nhap gia tri can tim: 5
Tim thay: index = 5, ID = 5, noi dung = Canh bao hoc vu muc 1
Duong di theo chi so: 1 -> 2 -> 5
```

Nếu nhập chỉ số/ID không tồn tại, chương trình in `Khong tim thay nut!`.

### Kiểm thử thống kê

Sau khi chọn `6`:

```text
Tong so nut: 7
So nut la: 4
Chieu cao (tinh theo so muc): 3
```

### Kiểm thử mô phỏng tư vấn

Sau khi chọn `7`, trả lời câu hỏi bằng `y` (Có) hoặc `n` (Không):

```text
[1] DTB < 2.0? (y: Co, n: Khong): y
[2] No >= 12 tin chi? (y: Co, n: Khong): n

KET LUAN: Canh bao hoc vu muc 1 (nut 5)
```

## 7. Các hàm quan trọng

| Hàm | Nhiệm vụ |
|---|---|
| `loadSampleTree()` | Tạo cây mẫu gồm 7 nút. |
| `inputTree()` | Nhập cây mới từ bàn phím. |
| `validateTree()` | Kiểm tra cấu trúc cây, ID và liên kết cha–con. |
| `showTree()` | Xuất dữ liệu cây dưới dạng bảng. |
| `preorder()`, `inorder()`, `postorder()` | Duyệt cây bằng đệ quy. |
| `findIndexById()` | Tra ID để lấy vị trí nút trong mảng. |
| `findPath()` | Tìm đường đi từ gốc tới nút đích bằng đệ quy và quay lui. |
| `height()`, `countLeaves()` | Tính chiều cao và đếm lá. |
| `runDecisionTree()` | Di chuyển theo các lựa chọn Có/Không và in kết luận. |
| `main()` | Hiển thị menu và điều phối chức năng. |

## 8. Nhận xét và hướng phát triển

**Ưu điểm:** Cấu trúc đơn giản, dễ quan sát quan hệ cha–con thông qua chỉ số mảng, dễ thử nghiệm các thuật toán duyệt cây và tìm kiếm; không cần cấp phát động.

**Hạn chế:** Kích thước cây bị giới hạn bởi `MAX = 100`; dữ liệu chỉ nằm trong bộ nhớ khi chương trình đang chạy.

**Hướng phát triển:** Bổ sung lưu/đọc dữ liệu từ tệp, chức năng chỉnh sửa từng nút, hiển thị sơ đồ cây và lưu lại lịch sử câu trả lời để giải thích kết luận tư vấn.
