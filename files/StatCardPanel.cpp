#include "StatCardPanel.h"

BEGIN_MESSAGE_MAP(StatCardPanel, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

StatCardPanel::StatCardPanel() {}

bool StatCardPanel::Create(CWnd* pParent, const CRect& rect) {
    return CWnd::Create(
        AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
            ::LoadCursor(NULL, IDC_ARROW),
            (HBRUSH)(COLOR_WINDOW + 1)),
        L"StatCardPanel",
        WS_CHILD | WS_VISIBLE,
        rect, pParent, 0) == TRUE;
}

// ── IObserver ─────────────────────────────────────────────────────
void StatCardPanel::OnUpdate(int eventType, void* pData) {
    if (eventType == EVT_STATS_CHANGED && pData) {
        m_stats = *static_cast<std::vector<StatData>*>(pData);
        Invalidate();
        UpdateWindow();
    }
}

// ── Paint ─────────────────────────────────────────────────────────
BOOL StatCardPanel::OnEraseBkgnd(CDC* pDC) {
    CRect r; GetClientRect(&r);
    pDC->FillSolidRect(&r, RGB(248, 250, 252));
    return TRUE;
}

void StatCardPanel::OnPaint() {
    CPaintDC dc(this);
    if (m_stats.empty()) return;

    CRect client; GetClientRect(&client);
    int n    = (int)m_stats.size();
    int pad  = 10;
    int w    = (client.Width() - pad * (n + 1)) / n;
    int h    = client.Height() - pad * 2;

    for (int i = 0; i < n; ++i) {
        CRect r(pad + i * (w + pad), pad, pad + i * (w + pad) + w, pad + h);
        DrawCard(dc, r, m_stats[i]);
    }
}

void StatCardPanel::DrawCard(CDC& dc, const CRect& r, const StatData& s) {
    // Shadow
    CRect shadow = r; shadow.OffsetRect(2, 2);
    dc.FillSolidRect(&shadow, RGB(200, 210, 220));

    // Card background
    dc.FillSolidRect(&r, RGB(255, 255, 255));

    // Left accent bar
    CRect bar(r.left, r.top, r.left + 5, r.bottom);
    dc.FillSolidRect(&bar, s.color);

    // Circle indicator
    int cx = r.right - 28, cy = r.top + 28, rad = 18;
    CBrush circBrush(s.color);
    CBrush* pOld = dc.SelectObject(&circBrush);
    CPen pen(PS_NULL, 0, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    dc.Ellipse(cx - rad, cy - rad, cx + rad, cy + rad);
    dc.SelectObject(pOldPen);
    dc.SelectObject(pOld);

    // Label
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(100, 116, 139));
    CFont fontLabel; fontLabel.CreateFont(13, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    CFont* pPrev = dc.SelectObject(&fontLabel);
    dc.TextOut(r.left + 14, r.top + 14, s.label);

    // Value
    dc.SetTextColor(RGB(15, 23, 42));
    CFont fontVal; fontVal.CreateFont(22, 0, 0, 0, FW_BOLD, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    dc.SelectObject(&fontVal);
    dc.TextOut(r.left + 14, r.top + 36, s.value);

    // Trend
    dc.SetTextColor(RGB(16, 185, 129));
    CFont fontTrend; fontTrend.CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    dc.SelectObject(&fontTrend);
    dc.TextOut(r.left + 14, r.top + 66, s.trend + L" vs last month");

    dc.SelectObject(pPrev);
}
