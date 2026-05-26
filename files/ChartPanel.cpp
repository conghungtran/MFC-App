#include "ChartPanel.h"

BEGIN_MESSAGE_MAP(ChartPanel, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

ChartPanel::ChartPanel() {}

bool ChartPanel::Create(CWnd* pParent, const CRect& rect) {
    return CWnd::Create(
        AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
            ::LoadCursor(NULL, IDC_ARROW),
            (HBRUSH)(COLOR_WINDOW + 1)),
        L"ChartPanel", WS_CHILD | WS_VISIBLE, rect, pParent, 0) == TRUE;
}

void ChartPanel::OnUpdate(int eventType, void* pData) {
    if (eventType == EVT_CHART_CHANGED && pData) {
        m_points = *static_cast<std::vector<ChartPoint>*>(pData);
        Invalidate(); UpdateWindow();
    }
}

BOOL ChartPanel::OnEraseBkgnd(CDC* pDC) {
    CRect r; GetClientRect(&r);
    pDC->FillSolidRect(&r, RGB(255, 255, 255));
    return TRUE;
}

void ChartPanel::OnPaint() {
    CPaintDC dc(this);
    CRect client; GetClientRect(&client);

    // Title
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(15, 23, 42));
    CFont fTitle; fTitle.CreateFont(15, 0, 0, 0, FW_BOLD, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    CFont* pPrev = dc.SelectObject(&fTitle);
    dc.TextOut(16, 12, L"Sales Value");
    dc.SelectObject(pPrev);

    if (m_points.empty()) return;

    // Vùng vẽ chart
    const int lm = 48, rm = 16, tm = 40, bm = 36;
    CRect chart(client.left + lm, client.top + tm,
                client.right - rm, client.bottom - bm);

    // Grid lines
    CPen gridPen(PS_SOLID, 1, RGB(226, 232, 240));
    CPen* pOld = dc.SelectObject(&gridPen);
    int   gridN = 4;
    for (int i = 0; i <= gridN; ++i) {
        int y = chart.top + i * chart.Height() / gridN;
        dc.MoveTo(chart.left, y); dc.LineTo(chart.right, y);
    }

    // Tìm max
    int maxVal = 1;
    for (auto& p : m_points) if (p.value > maxVal) maxVal = p.value;

    // Xây điểm
    int n = (int)m_points.size();
    std::vector<CPoint> pts(n);
    for (int i = 0; i < n; ++i) {
        pts[i].x = chart.left + i * chart.Width() / (n - 1);
        pts[i].y = chart.bottom - (int)((double)m_points[i].value / maxVal * chart.Height());
    }

    // Area fill (gradient mô phỏng bằng nhiều dải màu)
    for (int y = chart.bottom; y >= chart.top; --y) {
        double ratio = (double)(chart.bottom - y) / chart.Height();
        int alpha = (int)(60 * ratio);
        CPen linePen(PS_SOLID, 1, RGB(99 + alpha, 102 + alpha, 241));
        CPen* pL = dc.SelectObject(&linePen);

        // tìm x trái và phải cắt tại y
        for (int i = 0; i < n - 1; ++i) {
            int x1 = pts[i].x, y1 = pts[i].y;
            int x2 = pts[i+1].x, y2 = pts[i+1].y;
            if ((y1 <= y && y <= y2) || (y2 <= y && y <= y1)) {
                double t = (y2 != y1) ? (double)(y - y1) / (y2 - y1) : 0;
                int xc = x1 + (int)(t * (x2 - x1));
                dc.MoveTo(xc, y); dc.LineTo(xc + 2, y);
            }
        }
        dc.SelectObject(pL);
    }

    // Line
    CPen linePen(PS_SOLID, 2, RGB(99, 102, 241));
    dc.SelectObject(&linePen);
    dc.MoveTo(pts[0]);
    for (int i = 1; i < n; ++i) dc.LineTo(pts[i]);

    // Dots
    CBrush dotBrush(RGB(99, 102, 241));
    CBrush* pOldB = dc.SelectObject(&dotBrush);
    CPen noP(PS_NULL, 0, 0); dc.SelectObject(&noP);
    for (auto& p : pts)
        dc.Ellipse(p.x - 4, p.y - 4, p.x + 4, p.y + 4);
    dc.SelectObject(pOldB);

    // X-axis labels
    CFont fSmall; fSmall.CreateFont(11, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    dc.SelectObject(&fSmall);
    dc.SetTextColor(RGB(100, 116, 139));
    for (int i = 0; i < n; ++i) {
        int x = pts[i].x - 10;
        dc.TextOut(x, chart.bottom + 6, m_points[i].label);
    }

    // Y-axis labels
    for (int i = 0; i <= gridN; ++i) {
        int val = maxVal - i * maxVal / gridN;
        CString s; s.Format(L"%d", val);
        int y = chart.top + i * chart.Height() / gridN - 6;
        dc.TextOut(4, y, s);
    }

    dc.SelectObject(pOld);
    dc.SelectObject(pPrev);
}
