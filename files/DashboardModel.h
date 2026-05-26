#pragma once
#include "ISubject.h"
#include "Resource.h"
#include <vector>
#include <afxwin.h>

// ── Struct dữ liệu cho từng stat card ────────────────────────────
struct StatData {
    CString label;
    CString value;
    CString unit;
    CString trend;   // e.g. "+12%"
    COLORREF color;
};

// ── Struct một điểm dữ liệu biểu đồ ─────────────────────────────
struct ChartPoint {
    CString label;   // tháng / ngày
    int     value;
};

// ── Struct một dòng bảng ─────────────────────────────────────────
struct TableRow {
    CString name;
    CString status;
    CString amount;
    CString date;
};

// ── Struct một tin nhắn chat ──────────────────────────────────────
struct ChatMessage {
    CString sender;
    CString text;
    CString time;
};

// ──────────────────────────────────────────────────────────────────
//  DashboardModel  – Subject trung tâm
//  Khi dữ liệu thay đổi nó gọi Notify() để tất cả panel tự cập nhật
// ──────────────────────────────────────────────────────────────────
class DashboardModel : public ISubject {
public:
    std::vector<StatData>    stats;
    std::vector<ChartPoint>  chartPoints;
    std::vector<TableRow>    tableRows;
    std::vector<ChatMessage> messages;

    DashboardModel();

    // Thay đổi dữ liệu + phát thông báo tương ứng
    void RefreshStats();
    void AddChatMessage(const CString& sender, const CString& text);
    void RefreshTable();

private:
    void InitData();
};
