#include "TablePanel.h"

BEGIN_MESSAGE_MAP(TablePanel, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

TablePanel::TablePanel() {}

bool TablePanel::Create(CWnd* pParent, const CRect& rect) {
    return CWnd::Create(
        AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
            ::LoadCursor(NULL, IDC_ARROW),
            (HBRUSH)(COLOR_WINDOW + 1)),
        L"TablePanel", WS_CHILD | WS_VISIBLE, rect, pParent, 0) == TRUE;
}

void TablePanel::OnUpdate(int eventType, void* pData) {
    if (eventType == EVT_TABLE_CHANGED && pData) {
        m_rows = *static_cast<std::vector<TableRow>*>(pData);
        Invalidate(); UpdateWindow();
    }
}

BOOL TablePanel::OnEraseBkgnd(CDC* pDC) {
    CRect r; GetClientRect(&r);
    pDC->FillSolidRect(&r, RGB(255, 255, 255));
    return TRUE;
}

void TablePanel::OnPaint() {
    CPaintDC dc(this);
    CRect client; GetClientRect(&client);

    const int cols[] = { 0, 220, 350, 460, 600 };
    const wchar_t* heads[] = { L"Name", L"Status", L"Amount", L"Date" };
    const int rowH = 34, headH = 36;

    CFont fHead; fHead.CreateFont(13, 0, 0, 0, FW_BOLD, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    CFont fCell; fCell.CreateFont(13, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");

    dc.SetBkMode(TRANSPARENT);

    // Header row background
    dc.FillSolidRect(CRect(0, 0, client.right, headH), RGB(248, 250, 252));

    // Header text
    CFont* pPrev = dc.SelectObject(&fHead);
    dc.SetTextColor(RGB(100, 116, 139));
    for (int c = 0; c < 4; ++c)
        dc.TextOut(cols[c] + 12, 10, heads[c]);

    // Divider under header
    CPen divPen(PS_SOLID, 1, RGB(226, 232, 240));
    CPen* pOldP = dc.SelectObject(&divPen);
    dc.MoveTo(0, headH); dc.LineTo(client.right, headH);
    dc.SelectObject(pOldP);

    // Rows
    dc.SelectObject(&fCell);
    for (int i = 0; i < (int)m_rows.size(); ++i) {
        int y = headH + i * rowH;
        if (y + rowH > client.bottom) break;

        // Alternating row bg
        if (i % 2 == 0)
            dc.FillSolidRect(CRect(0, y, client.right, y + rowH), RGB(255, 255, 255));
        else
            dc.FillSolidRect(CRect(0, y, client.right, y + rowH), RGB(249, 250, 251));

        auto& r = m_rows[i];
        dc.SetTextColor(RGB(15, 23, 42));
        dc.TextOut(cols[0] + 12, y + 10, r.name);

        // Status badge
        COLORREF badgeBg = RGB(220, 252, 231);
        COLORREF badgeFg = RGB(22, 163, 74);
        if (r.status == L"Pending") { badgeBg = RGB(254, 243, 199); badgeFg = RGB(161, 98,  7);  }
        if (r.status == L"Failed")  { badgeBg = RGB(254, 226, 226); badgeFg = RGB(185,  28, 28); }

        CRect badge(cols[1] + 12, y + 8, cols[1] + 80, y + 26);
        dc.FillSolidRect(&badge, badgeBg);
        dc.SetTextColor(badgeFg);
        dc.TextOut(badge.left + 6, badge.top + 2, r.status);

        dc.SetTextColor(RGB(15, 23, 42));
        dc.TextOut(cols[2] + 12, y + 10, r.amount);

        dc.SetTextColor(RGB(100, 116, 139));
        dc.TextOut(cols[3] + 12, y + 10, r.date);

        // Row divider
        CPen rPen(PS_SOLID, 1, RGB(241, 245, 249));
        CPen* pOldR = dc.SelectObject(&rPen);
        dc.MoveTo(0, y + rowH - 1); dc.LineTo(client.right, y + rowH - 1);
        dc.SelectObject(pOldR);
    }

    dc.SelectObject(pPrev);
}
