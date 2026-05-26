Dựa trên tài liệu **MockProject_PrinterManagement**, đây là danh sách **đầy đủ các chức năng** mà ứng dụng **PrinterHub** phải có, được phân theo từng module:

---

## 📌 **Module A — Quản lý dữ liệu Máy in (CRUD + Filter)**

| ID | Chức năng |
|----|-----------|
| **A1** | Thêm máy in mới vào danh sách |
| **A2** | Sửa thông tin máy in hiện có |
| **A3** | Xóa máy in (có thể là soft-delete) |
| **A4** | Tìm kiếm/lọc máy in theo tiêu chí (tên, hãng, trạng thái...) |
| **A5** | Hiển thị danh sách máy in với đầy đủ thông tin |

---

## 📌 **Module B — Quản lý Firmware & Bảo trì**

| ID | Chức năng |
|----|-----------|
| **B1** | Xem danh sách firmware có sẵn (FirmwareCatalog - Singleton) |
| **B2** | Thêm firmware vào hàng đợi nâng cấp (FIFO queue) |
| **B3** | Xử lý nâng cấp firmware theo hàng đợi |
| **B4** | Ghi log lịch sử nâng cấp firmware vào file .txt |
| **B5** | Xem lịch sử firmware của một máy in cụ thể |

---

## 📌 **Module C — Hàng đợi Ticket & Sửa chữa**

| ID | Chức năng |
|----|-----------|
| **C1** | Tạo ticket bảo trì/sửa chữa mới |
| **C2** | Xem danh sách ticket với priority (Critical, High, Medium, Low) |
| **C3** | Sắp xếp ticket theo priority (dùng lambda) |
| **C4** | Tìm kiếm ticket theo từ khóa mô tả (std::find_if) |
| **C5** | Xóa/đóng ticket khi hoàn thành |

---

## 📌 **Module D — Kiến trúc & Design Patterns**

| ID | Pattern | Chức năng |
|----|---------|-----------|
| **D1** | **Namespace** | Tổ chức code trong `PrinterHub::Core`, `PrinterHub::UI`, `PrinterHub::Tests` |
| **D2** | **Generic Repository** | `DeviceRepository<T>` template dùng chung cho Printer và Firmware |
| **D3** | **Singleton** | `FirmwareCatalog` là catalog toàn cục, thread-safe |
| **D4** | **Observer** | Các View đăng ký nhận thông báo khi danh sách máy in thay đổi |
| **D5** | **Strategy** | Chiến lược sắp xếp máy in (theo tên, trạng thái, ngày mua) |
| **D6** | **State** | Quản lý vòng đời máy in (Active → InService → Retired) |
| **D7** | **Command** | Hỗ trợ Undo/Redo cho các thao tác (thêm/sửa/xóa/nâng cấp) |

---

## 📌 **Module E — File I/O & Persistence**

| ID | Chức năng |
|----|-----------|
| **E1** | Đọc/ghi file `.csv` cho danh sách máy in (dùng `fopen` hoặc `fstream`) |
| **E2** | Đọc/ghi file `.txt` log lịch sử firmware |
| **E3** | Validate dữ liệu khi đọc file (xử lý lỗi định dạng, thiếu trường) |
| **E4** | MFC Serialization (`CArchive`) cho Doc/View persistence |

---

## 📌 **Module F — Giao diện MFC (Dialog App)**

| ID | Chức năng |
|----|-----------|
| **F1** | **Main Dialog**: Hiển thị danh sách máy in (`CListCtrl`), các nút Thêm/Sửa/Xóa |
| **F2** | **Add/Edit Dialog**: Form nhập thông tin máy in với **DDX/DDV** validation |
| **F3** | **Firmware Dialog**: Xem hàng đợi và lịch sử firmware của máy đang chọn |
| **F4** | **Ticket Dialog**: Quản lý danh sách ticket bảo trì |
| **F5** | **Message Map**: Xử lý sự kiện `ON_BN_CLICKED`, `ON_LBN_SELCHANGE`, `ON_EN_CHANGE` |

---

## 📌 **Module G — Unit Test**

| ID | Chức năng |
|----|-----------|
| **G1** | Unit test cho logic đăng ký máy in (valid/invalid input) |
| **G2** | Fixture test cho vòng đời trạng thái máy in |
| **G3** | Regression test cho tính năng Undo/Redo |
| **G4** | ViewModel test: tách logic validation khỏi UI, test độc lập |
| **G5** | Coverage report: giải thích line coverage vs branch coverage cho ít nhất 2 module |

---

## 🔧 **Yêu cầu kỹ thuật bắt buộc (Cheat sheet)**

| Chương | Yêu cầu |
|--------|---------|
| **Ch.1** | `enum class` cho `PrinterStatus`, `Priority`, `Brand` |
| **Ch.2** | Tách file `.h`/`.cpp`, `#pragma once`, `PrinterConfig.h` |
| **Ch.3** | Dùng cả raw pointer và reference, không dangling pointer |
| **Ch.4** | Pass-by-value, pass-by-reference, pass-by-pointer |
| **Ch.5** | Đọc/ghi CSV, validate input, dùng debugger trace bug |
| **Ch.6** | Rule of 3/5, `operator==`, `operator<` |
| **Ch.7** | Interface `IPrinterObserver` thuần ảo, `dynamic_cast` |
| **Ch.8** | Namespace `PrinterHub::Core`, template `DeviceRepository<T>` |
| **Ch.9** | `vector`, `map`, `queue`, `stack`, `set`, lambda sort, `std::function` |
| **Ch.10** | Custom exception `PrinterHubException`, RAII, `unique_ptr`, `shared_ptr` |
| **Ch.11** | Move constructor, `std::move`, `reserve()` |
| **Ch.12** | GoogleTest (≥10 test cases) |
| **Ch.13** | ViewModel (`PrinterFormVM`), giải thích line vs branch coverage |
| **Ch.14** | Thread worker load CSV, `std::mutex`, `PostMessage` cập nhật UI |
| **Ch.15** | Singleton `FirmwareCatalog` (thread-safe), Observer |
| **Ch.16** | Strategy (sort), State (machine), Command (Undo/Redo) |
| **Ch.17** | MFC Dialog, DDX/DDV, `CString`, `_T()` |
| **Ch.18** | MFC Doc/View: `CPrinterDoc`, `CPrinterView`, `UpdateAllViews()` |

---

## ✅ **Tóm tắt các chức năng chính (End-user)**

Khi người dùng mở ứng dụng **PrinterHub**, họ có thể:

1. **Xem danh sách máy in** (hiển thị trong `CListCtrl`)
2. **Thêm máy in mới** (form nhập liệu có validation)
3. **Sửa thông tin máy in**
4. **Xóa máy in** (soft-delete)
5. **Lọc/sắp xếp máy in** (theo tên, trạng thái, ngày mua)
6. **Xem hàng đợi firmware** và nâng cấp firmware cho máy in
7. **Xem lịch sử nâng cấp firmware** (log file)
8. **Tạo và quản lý ticket bảo trì** (có priority)
9. **Undo/Redo** các thao tác (thêm/sửa/xóa/nâng cấp)
10. **Lưu/đọc dữ liệu** từ file CSV (tự động khi khởi động/đóng app)
11. **Giao diện tự động cập nhật** khi có thay đổi (Observer pattern)

Bạn muốn tôi hướng dẫn bắt đầu từ module nào trước? (Ví dụ: **Ngày 1 — Core Data Model** gồm `Printer`, `FirmwarePackage`, `MaintenanceTicket`)
