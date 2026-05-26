#include "MainFrame.h"

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_SIZE()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_REFRESH_BTN,     &MainFrame::OnRefreshClicked)
    ON_BN_CLICKED(IDC_MENU_TOGGLE,     &MainFrame::OnMenuToggle)
    ON_BN_CLICKED(IDC_MENU_DASHBOARD,  &MainFrame::OnMenuDashboard)
END_MESSAGE_MAP()

// ──────────────────────────────────────────────────────────────────
//  Constructor
// ──────────────────────────────────────────────────────────────────
MainFrame::MainFrame(DashboardModel* pModel)
    : m_pModel(pModel), m_bSidebarVisible(true)
{
    CString cls = AfxRegisterWndClass(
        CS_HREDRAW | CS_VREDRAW,
        ::LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)::GetStockObject(WHITE_BRUSH),
        AfxGetApp()->LoadStandardIcon(IDI_APPLICATION));

    Create(cls, L"Dashboard – Observer Pattern",
        WS_OVERLAPPEDWINDOW,
        CRect(80, 60, 80 + 1280, 60 + 800));

    // ── Navbar: search field ────────────────────────────────────────
    m_edtSearch.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        CRect(0,0,10,10), this, IDC_NAVBAR_SEARCH);

    // ── Navbar: Refresh button ──────────────────────────────────────
    m_btnRefresh.Create(L"⟳ Refresh",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(0,0,10,10), this, IDC_REFRESH_BTN);

    // ── Navbar: User button ─────────────────────────────────────────
    m_btnUser.Create(L"👤 Admin",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(0,0,10,10), this, IDC_NAVBAR_USER);

    // ── Navbar: Menu Toggle ─────────────────────────────────────────
    m_btnDashboard.Create(L"≡",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        CRect(0,0,10,10), this, IDC_MENU_TOGGLE);

    // ── Sidebar buttons ─────────────────────────────────────────────
    const struct { CButton* btn; const wchar_t* label; int id; } items[] = {
        { &m_btnDashboard,  L"📊  Dashboard",   IDC_MENU_DASHBOARD  },
        { &m_btnUIElements, L"🎨  UI Elements", IDC_MENU_UIELEMENTS },
        { &m_btnForms,      L"📝  Forms",       IDC_MENU_FORMS      },
        { &m_btnTables,     L"📋  Tables",      IDC_MENU_TABLES     },
        { &m_btnCharts,     L"📈  Charts",      IDC_MENU_CHARTS     },
    };
    for (auto& item : items)
        item.btn->Create(item.label, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_LEFT,
            CRect(0,0,10,10), this, item.id);

    // ── Panels ──────────────────────────────────────────────────────
    m_statCards.Create(this, CRect(0,0,10,10));
    m_chart.Create(this, CRect(0,0,10,10));
    m_chat.Create(this, CRect(0,0,10,10));
    m_table.Create(this, CRect(0,0,10,10));

    // ── Observer pattern: đăng ký các panel với model ───────────────
    RegisterObservers();

    // ── Đẩy dữ liệu khởi tạo vào tất cả observer ───────────────────
    m_pModel->Notify(EVT_STATS_CHANGED, &m_pModel->stats);
    m_pModel->Notify(EVT_CHART_CHANGED, &m_pModel->chartPoints);
    m_pModel->Notify(EVT_CHAT_CHANGED,  &m_pModel->messages);
    m_pModel->Notify(EVT_TABLE_CHANGED, &m_pModel->tableRows);

    // ── Auto-refresh timer (5 giây) ─────────────────────────────────
    SetTimer(IDT_REFRESH_TIMER, 5000, NULL);
}

MainFrame::~MainFrame() {
    KillTimer(IDT_REFRESH_TIMER);
    m_pModel->Detach(&m_statCards);
    m_pModel->Detach(&m_chart);
    m_pModel->Detach(&m_chat);
    m_pModel->Detach(&m_table);
}

// ── Đăng ký Observer ──────────────────────────────────────────────
void MainFrame::RegisterObservers() {
    m_pModel->Attach(&m_statCards);
    m_pModel->Attach(&m_chart);
    m_pModel->Attach(&m_chat);
    m_pModel->Attach(&m_table);
}

// ──────────────────────────────────────────────────────────────────
//  Layout tất cả child controls theo kích thước window hiện tại
// ──────────────────────────────────────────────────────────────────
void MainFrame::LayoutPanels(int cx, int cy) {
    const int NB  = IDC_NAVBAR_HEIGHT;
    const int SW  = m_bSidebarVisible ? IDC_SIDEBAR_WIDTH : 0;
    const int PAD = IDC_PANEL_PAD;

    // Content area
    int contentX = SW + PAD;
    int contentW = cx - SW - PAD * 2;
    int contentY = NB + PAD;

    // ── Navbar controls ─────────────────────────────────────────────
    m_btnDashboard.SetWindowPos(NULL, 8, 8, 32, 32, SWP_NOZORDER);
    m_edtSearch.SetWindowPos(NULL, SW + 16, 12, 220, 24, SWP_NOZORDER);
    m_btnRefresh.SetWindowPos(NULL, cx - 200, 8, 100, 32, SWP_NOZORDER);
    m_btnUser.SetWindowPos(NULL, cx - 96, 8, 88, 32, SWP_NOZORDER);

    // ── Sidebar buttons (stacked vertically) ────────────────────────
    if (m_bSidebarVisible) {
        CButton* btns[] = { &m_btnDashboard, &m_btnUIElements,
                            &m_btnForms, &m_btnTables, &m_btnCharts };
        // skip index 0 – reused as toggle; use items 1..4 for sidebar
        const wchar_t* labels[] = {
            L"📊  Dashboard", L"🎨  UI Elements",
            L"📝  Forms", L"📋  Tables", L"📈  Charts"
        };
        for (int i = 0; i < 5; ++i) {
            btns[i]->SetWindowPos(NULL, 0, NB + 8 + i * 44,
                SW - 1, 40, SWP_NOZORDER);
            btns[i]->ShowWindow(SW_SHOW);
        }
    } else {
        CButton* btns[] = { &m_btnDashboard, &m_btnUIElements,
                            &m_btnForms, &m_btnTables, &m_btnCharts };
        for (auto* b : btns) b->ShowWindow(SW_HIDE);
    }

    // ── Stat cards (top strip) ──────────────────────────────────────
    int cardH = 100;
    m_statCards.SetWindowPos(NULL,
        contentX, contentY, contentW, cardH, SWP_NOZORDER);

    // ── Charts row: ChartPanel (left 65%) + ChatPanel (right 35%) ──
    int chartY  = contentY + cardH + PAD;
    int chartH  = (cy - chartY - PAD * 2) * 55 / 100;
    int chartW  = contentW * 65 / 100 - PAD / 2;
    int chatW   = contentW - chartW - PAD;

    m_chart.SetWindowPos(NULL, contentX, chartY, chartW, chartH, SWP_NOZORDER);
    m_chat.SetWindowPos(NULL,
        contentX + chartW + PAD, chartY, chatW, chartH, SWP_NOZORDER);

    // ── Table (bottom strip) ────────────────────────────────────────
    int tableY = chartY + chartH + PAD;
    int tableH = cy - tableY - PAD;
    m_table.SetWindowPos(NULL, contentX, tableY, contentW, tableH, SWP_NOZORDER);
}

// ── WM_SIZE ───────────────────────────────────────────────────────
void MainFrame::OnSize(UINT nType, int cx, int cy) {
    CFrameWnd::OnSize(nType, cx, cy);
    if (cx > 0 && cy > 0) LayoutPanels(cx, cy);
}

// ── WM_ERASEBKGND: vẽ nền tổng thể ──────────────────────────────
BOOL MainFrame::OnEraseBkgnd(CDC* pDC) {
    CRect r; GetClientRect(&r);
    pDC->FillSolidRect(&r, RGB(243, 244, 246));  // bg page
    return TRUE;
}

// ── WM_PAINT: vẽ Navbar và Sidebar ───────────────────────────────
void MainFrame::OnPaint() {
    CPaintDC dc(this);
    CRect client; GetClientRect(&client);

    const int NB = IDC_NAVBAR_HEIGHT;
    const int SW = m_bSidebarVisible ? IDC_SIDEBAR_WIDTH : 0;

    // Navbar
    CRect navR(0, 0, client.right, NB);
    DrawNavbar(dc, navR);

    // Sidebar
    if (m_bSidebarVisible) {
        CRect sideR(0, NB, SW, client.bottom);
        DrawSidebar(dc, sideR);
    }
}

void MainFrame::DrawNavbar(CDC& dc, const CRect& r) {
    dc.FillSolidRect(&r, RGB(255, 255, 255));

    // Bottom border
    CPen pen(PS_SOLID, 1, RGB(226, 232, 240));
    CPen* pOld = dc.SelectObject(&pen);
    dc.MoveTo(r.left, r.bottom - 1); dc.LineTo(r.right, r.bottom - 1);
    dc.SelectObject(pOld);

    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(15, 23, 42));
    CFont f; f.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    CFont* pPrev = dc.SelectObject(&f);
    dc.TextOut(50, 14, L"Dashboard");
    dc.SelectObject(pPrev);
}

void MainFrame::DrawSidebar(CDC& dc, const CRect& r) {
    dc.FillSolidRect(&r, RGB(30, 41, 59));   // dark sidebar

    // Right border
    CPen pen(PS_SOLID, 1, RGB(51, 65, 85));
    CPen* pOld = dc.SelectObject(&pen);
    dc.MoveTo(r.right - 1, r.top); dc.LineTo(r.right - 1, r.bottom);
    dc.SelectObject(pOld);

    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(148, 163, 184));
    CFont f; f.CreateFont(11, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    CFont* pPrev = dc.SelectObject(&f);
    dc.TextOut(12, r.top + 8, L"MAIN NAVIGATION");
    dc.SelectObject(pPrev);
}

// ── Timer: auto-refresh tất cả dữ liệu ───────────────────────────
void MainFrame::OnTimer(UINT_PTR nIDEvent) {
    if (nIDEvent == IDT_REFRESH_TIMER) {
        m_pModel->RefreshStats();    // → Notify(EVT_STATS_CHANGED) + EVT_CHART_CHANGED
        m_pModel->RefreshTable();    // → Notify(EVT_TABLE_CHANGED)
    }
    CFrameWnd::OnTimer(nIDEvent);
}

// ── Button handlers ───────────────────────────────────────────────
void MainFrame::OnRefreshClicked() {
    m_pModel->RefreshStats();
    m_pModel->RefreshTable();
    m_pModel->AddChatMessage(L"System", L"Data refreshed manually.");
}

void MainFrame::OnMenuToggle() {
    m_bSidebarVisible = !m_bSidebarVisible;
    CRect r; GetClientRect(&r);
    LayoutPanels(r.Width(), r.Height());
    Invalidate(); UpdateWindow();
}

void MainFrame::OnMenuDashboard() {
    // placeholder: active page switching
}
