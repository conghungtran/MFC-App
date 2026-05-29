Tuyệt vời! MFC Dialog-based App là lựa chọn **đơn giản và dễ kiểm soát** nhất cho đồ án PrinterHub. Tôi sẽ hướng dẫn bạn thiết kế giao diện chi tiết.

## 🎨 **Thiết kế giao diện PrinterHub**

### **1. Main Dialog (IDD_PRINTERHUB_DIALOG) - Kích thước 800x600**

```
┌─────────────────────────────────────────────────────────────────┐
│  PrinterHub - Quản lý máy in                        [—] [□] [X]  │
├─────────────────────────────────────────────────────────────────┤
│                                                                   │
│  ┌─ Thanh công cụ ─────────────────────────────────────────────┐ │
│  │ [➕ Thêm] [✏️ Sửa] [🗑️ Xóa] [🔄 Undo] [↪️ Redo]  [🔍 Lọc] [📊 Sắp xếp] │ │
│  └─────────────────────────────────────────────────────────────┘ │
│                                                                   │
│  ┌─ Danh sách máy in ──────────────────────────────────────────┐ │
│  │ ┌────┬────────────┬──────────┬─────────┬────────────┬─────┐ │ │
│  │ │ ID │ Tên máy in  │ Hãng     │ Trạng thái│ Ngày mua   │ FW  │ │ │
│  │ ├────┼────────────┼──────────┼─────────┼────────────┼─────┤ │ │
│  │ │ 1  │ HP LaserJet │ HP       │ Active  │ 2024-01-15 │ v1.2│ │ │
│  │ │ 2  │ Epson Eco   │ Epson    │ InService│2024-02-20 │ v1.0│ │ │
│  │ │ 3  │ Canon X400  │ Canon    │ Retired │ 2023-11-10 │ v2.1│ │ │
│  │ └────┴────────────┴──────────┴─────────┴────────────┴─────┘ │ │
│  └─────────────────────────────────────────────────────────────┘ │
│                                                                   │
│  ┌─ Thông tin chi tiết ─┬─ Hàng đợi Firmware ─────────────────┐ │
│  │                       │                                      │ │
│  │ [Thông tin máy chọn]  │ [v2.0] [v2.1] [v3.0]                │ │
│  │                       │                     [🚀 Nâng cấp]   │ │
│  │ Tên: HP LaserJet      │                                      │ │
│  │ Hãng: HP              │ ┌──────────────────────────────────┐│ │
│  │ Serial: H12345        │ │ Firmware Queue (FIFO)            ││ │
│  │ Status: ● Active      │ │ 1. HP LaserJet → v2.0 (đang chờ)  ││ │
│  │                       │ │ 2. Epson Eco → v1.5 (đang chờ)   ││ │
│  │ [Lịch sử Firmware]    │ └──────────────────────────────────┘│ │
│  │ [Tạo Ticket bảo trì]  │                                      │ │
│  └───────────────────────┴──────────────────────────────────────┘ │
│                                                                   │
│  ┌─ Ticket bảo trì ─────────────────────────────────────────────┐ │
│  │ Priority: [🔴 Critical ▼]  [⚡ Xử lý tiếp theo]              │ │
│  │ ┌──────────────────────────────────────────────────────────┐│ │
│  │ │ [!] Ticket #101 - HP LaserJet (Critical) - Lỗi kẹt giấy   ││ │
│  │ │ [i] Ticket #102 - Epson Eco (High) - In mờ                ││ │
│  │ │ [→] Ticket #103 - Canon X400 (Medium) - Bảo trì định kỳ   ││ │
│  │ └──────────────────────────────────────────────────────────┘│ │
│  └──────────────────────────────────────────────────────────────┘ │
│                                                                   │
│  Status: Ready                                    [Exit]          │
└─────────────────────────────────────────────────────────────────┘
```

### **2. Add/Edit Printer Dialog (IDD_ADDPRINTER_DIALOG) - 400x350**

```
┌─────────────────────────────────────────┐
│  [Thêm máy in mới] / [Sửa máy in]   [X] │
├─────────────────────────────────────────┤
│                                           │
│  Tên máy in:  [___________________]      │
│               (Bắt buộc, 3-50 ký tự)     │
│                                           │
│  Hãng sản xuất:                          │
│  ○ HP    ○ Epson    ○ Canon    ○ Brother │
│  ○ Dell  ○ Xerox    ○ Khác: [_____]      │
│                                           │
│  Serial Number:  [_________________]     │
│                  (Mã duy nhất)            │
│                                           │
│  Ngày mua:       [DD/MM/YYYY] 📅         │
│                                           │
│  Trạng thái ban đầu:                      │
│  [● Active]  [○ InService]  [○ Retired]  │
│                                           │
│  Firmware hiện tại: [v1.0 ▼]             │
│                                           │
│  ┌─────────────────────────────────────┐ │
│  │ ⓘ Thông tin validation sẽ hiển thị  │ │
│  │   ở đây nếu có lỗi                   │ │
│  └─────────────────────────────────────┘ │
│                                           │
│         [OK]              [Cancel]       │
└─────────────────────────────────────────┘
```

### **3. Firmware History Dialog (IDD_FIRMWAREHISTORY_DIALOG) - 600x400**

```
┌───────────────────────────────────────────────────┐
│  Lịch sử Firmware - HP LaserJet          [X]      │
├───────────────────────────────────────────────────┤
│                                                     │
│  ┌─────────────────────────────────────────────┐  │
│  │ Thời gian          │ Version │ Kết quả       │  │
│  ├────────────────────┼─────────┼───────────────┤  │
│  │ 2024-03-15 10:30  │ v2.1    │ ✓ Thành công  │  │
│  │ 2024-02-01 14:20  │ v2.0    │ ✓ Thành công  │  │
│  │ 2023-12-10 09:15  │ v1.5    │ ✗ Thất bại    │  │
│  │ 2023-11-05 16:45  │ v1.0    │ ✓ Thành công  │  │
│  └─────────────────────────────────────────────┘  │
│                                                     │
│  Log file: firmware_history.txt                   │
│  [📁 Xem file log]  [🖨️ In báo cáo]  [Đóng]       │
└───────────────────────────────────────────────────┘
```

### **4. Ticket Management Dialog (IDD_TICKET_DIALOG) - 500x400**

```
┌─────────────────────────────────────────────────┐
│  Quản lý Ticket bảo trì                [X]       │
├─────────────────────────────────────────────────┤
│                                                   │
│  Tạo ticket mới:                                 │
│  Máy in: [HP LaserJet ▼]                         │
│  Priority: [🔴 Critical        ▼]                │
│  Mô tả:  [________________________________]      │
│          [_______________________________]        │
│          [                           [Tạo] ]     │
│                                                   │
│  ┌─────────────────────────────────────────────┐ │
│  │ ☐ | Prio | Máy in     | Mô tả     | Ngày    │ │
│  ├────┼──────┼───────────┼───────────┼─────────┤ │
│  │ ☐ | 🔴   | HP Lase... | Kẹt giấy  | 15/3    │ │
│  │ ☐ | 🟠   | Epson Eco  | In mờ     | 14/3    │ │
│  │ ☐ | 🟡   | Canon X400 | BT định kỳ| 10/3    │ │
│  │ ☐ | 🟢   | Brother... | Hết mực   | 12/3    │ │
│  └─────────────────────────────────────────────┘ │
│                                                   │
│  [✅ Đóng ticket chọn]  [🗑️ Xóa]  [📋 Xuất CSV]  │
└─────────────────────────────────────────────────┘
```

## 📝 **Resource IDs cần định nghĩa (Resource.h)**

```cpp
// Main Dialog Controls
#define IDC_LIST_PRINTERS              1001
#define IDC_BTN_ADD                    1002
#define IDC_BTN_EDIT                   1003
#define IDC_BTN_DELETE                 1004
#define IDC_BTN_UNDO                   1005
#define IDC_BTN_REDO                   1006
#define IDC_BTN_FILTER                 1007
#define IDC_BTN_SORT                   1008
#define IDC_BTN_UPGRADE                1009
#define IDC_BTN_FW_HISTORY             1010
#define IDC_BTN_CREATE_TICKET          1011
#define IDC_COMBO_PRIORITY_FILTER      1012
#define IDC_LIST_TICKETS               1013
#define IDC_STATIC_PRINTER_INFO        1014
#define IDC_LIST_FW_QUEUE              1015
#define IDC_BTN_PROCESS_QUEUE          1016

// Add/Edit Dialog Controls
#define IDC_EDIT_PRINTER_NAME          2001
#define IDC_RADIO_HP                   2002
#define IDC_RADIO_EPSON                2003
#define IDC_RADIO_CANON                2004
#define IDC_RADIO_BROTHER              2005
#define IDC_RADIO_DELL                 2006
#define IDC_RADIO_XEROX                2007
#define IDC_EDIT_OTHER_BRAND           2008
#define IDC_EDIT_SERIAL                2009
#define IDC_DATETIME_PURCHASE          2010
#define IDC_RADIO_ACTIVE               2011
#define IDC_RADIO_INSERVICE            2012
#define IDC_RADIO_RETIRED              2013
#define IDC_COMBO_FIRMWARE             2014
#define IDC_STATIC_VALIDATION_MSG      2015

// Additional controls for history and ticket
#define IDC_LIST_FW_HISTORY            3001
#define IDC_BTN_VIEW_LOG               3002
#define IDC_EDIT_TICKET_DESC           3003
#define IDC_BTN_CREATE_TICKET_SUBMIT   3004
#define IDC_BTN_CLOSE_TICKET           3005
```

## 🎯 **Cấu trúc class cho Dialog App**

```cpp
// PrinterHubDlg.h
class CPrinterHubDlg : public CDialogEx
{
public:
    CPrinterHubDlg(CWnd* pParent = nullptr);
    
    // DDX/DDV support
    virtual void DoDataExchange(CDataExchange* pDX);
    
    // Message map handlers
    afx_msg void OnBnClickedAdd();
    afx_msg void OnBnClickedEdit();
    afx_msg void OnBnClickedDelete();
    afx_msg void OnBnClickedUndo();
    afx_msg void OnBnClickedRedo();
    afx_msg void OnBnClickedUpgrade();
    afx_msg void OnLbnSelchangePrinters();
    afx_msg void OnBnClickedCreateTicket();
    
private:
    // UI Controls
    CListCtrl m_listPrinters;
    CListBox m_listFWQueue;
    CListCtrl m_listTickets;
    CComboBox m_comboPriorityFilter;
    CStatic m_staticPrinterInfo;
    
    // Business logic
    std::unique_ptr<PrinterRepository> m_repo;
    std::unique_ptr<CommandManager> m_cmdManager;
    
    // Helper methods
    void RefreshPrinterList();
    void RefreshFWQueue(int printerId);
    void RefreshTicketList();
    void UpdatePrinterInfo(int printerId);
    
    // Column indices for CListCtrl
    enum PrinterColumns {
        COL_ID = 0,
        COL_NAME,
        COL_BRAND,
        COL_STATUS,
        COL_PURCHASE_DATE,
        COL_FW_VERSION
    };
};
```

## 🚀 **Các bước tạo project trong Visual Studio**

1. **File → New → Project**
2. Chọn **MFC App** → tên **PrinterHub**
3. **Application Type**: Dialog based
4. **Features**: ✅ Use Unicode libraries
5. **Advanced Features**: 
   - ☐ ActiveX controls (bỏ chọn)
   - ☐ Common control manifest (giữ nguyên)
6. **Finish**

Sau đó bạn copy các resource IDs và implement từ từ.

---

**Bạn muốn tôi hướng dẫn tiếp phần nào?**

1. **Code xử lý sự kiện** cho nút Thêm/Sửa/Xóa?
2. **Cài đặt CListCtrl** để hiển thị danh sách máy in?
3. **Tạo Dialog con** (Add/Edit Printer Dialog) với DDX/DDV validation?
4. **Code xử lý Firmware Queue** với thread an toàn?

Chọn 1 option để tôi giúp bạn chi tiết nhé! 🎨
