#include "DashboardModel.h"
#include <cstdlib>
#include <ctime>

DashboardModel::DashboardModel() {
    std::srand((unsigned)std::time(nullptr));
    InitData();
}

// ── Khởi tạo dữ liệu mẫu ─────────────────────────────────────────
void DashboardModel::InitData() {
    // Stat cards
    stats = {
        { L"Total Revenue",  L"$45,231", L"USD",  L"+20.1%", RGB(99,  102, 241) },
        { L"Subscriptions",  L"+2,350",  L"users", L"+180.1%",RGB(16,  185, 129) },
        { L"Sales",          L"+12,234", L"orders",L"+19%",   RGB(245, 158,  11) },
        { L"Active Now",     L"+573",    L"online",L"+201",   RGB(239,  68,  68) },
    };

    // Chart data (12 tháng)
    const wchar_t* months[] = {
        L"Jan",L"Feb",L"Mar",L"Apr",L"May",L"Jun",
        L"Jul",L"Aug",L"Sep",L"Oct",L"Nov",L"Dec"
    };
    int baseVals[] = { 186,305,237,73,209,214,132,268,178,320,245,290 };
    chartPoints.clear();
    for (int i = 0; i < 12; ++i)
        chartPoints.push_back({ months[i], baseVals[i] });

    // Table rows
    tableRows = {
        { L"Alice Johnson",  L"Success",  L"$250.00",  L"2024-01-15" },
        { L"Bob Smith",      L"Pending",  L"$150.00",  L"2024-01-16" },
        { L"Carol White",    L"Failed",   L"$350.00",  L"2024-01-17" },
        { L"David Brown",    L"Success",  L"$450.00",  L"2024-01-18" },
        { L"Eva Martinez",   L"Success",  L"$200.00",  L"2024-01-19" },
    };

    // Chat messages
    messages = {
        { L"Sofia Davis",  L"Hey! How are you?",                L"09:30" },
        { L"John Lee",     L"Can we reschedule the meeting?",   L"09:45" },
        { L"Sarah Kim",    L"Dashboard looks great!",           L"10:00" },
    };
}

// ── Refresh ngẫu nhiên stat cards rồi Notify ─────────────────────
void DashboardModel::RefreshStats() {
    for (auto& s : stats) {
        int delta = (std::rand() % 200) - 100;
        CString newVal;
        newVal.Format(L"%d", 1000 + std::rand() % 50000);
        s.value = L"$" + newVal;

        int pct = std::rand() % 30;
        s.trend.Format(L"+%d%%", pct);
    }
    // Xáo trộn nhẹ chart
    for (auto& pt : chartPoints)
        pt.value = 50 + std::rand() % 300;

    Notify(EVT_STATS_CHANGED, &stats);
    Notify(EVT_CHART_CHANGED, &chartPoints);
}

// ── Thêm tin nhắn chat rồi Notify ────────────────────────────────
void DashboardModel::AddChatMessage(const CString& sender, const CString& text) {
    CTime t = CTime::GetCurrentTime();
    CString timeStr;
    timeStr.Format(L"%02d:%02d", t.GetHour(), t.GetMinute());
    messages.push_back({ sender, text, timeStr });
    if (messages.size() > 20) messages.erase(messages.begin());
    Notify(EVT_CHAT_CHANGED, &messages);
}

// ── Refresh table rồi Notify ──────────────────────────────────────
void DashboardModel::RefreshTable() {
    const wchar_t* names[]   = { L"Alice", L"Bob", L"Carol", L"David", L"Eva", L"Frank", L"Grace" };
    const wchar_t* statuses[]= { L"Success", L"Pending", L"Failed" };
    tableRows.clear();
    for (int i = 0; i < 5; ++i) {
        TableRow r;
        r.name   = names[std::rand() % 7];
        r.status = statuses[std::rand() % 3];
        r.amount.Format(L"$%d.00", 50 + std::rand() % 500);
        r.date   = L"2024-01-" + CString(std::to_wstring(10 + i).c_str());
        tableRows.push_back(r);
    }
    Notify(EVT_TABLE_CHANGED, &tableRows);
}
