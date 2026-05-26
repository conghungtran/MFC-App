#include "ChatPanel.h"

BEGIN_MESSAGE_MAP(ChatPanel, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

ChatPanel::ChatPanel() {}

bool ChatPanel::Create(CWnd* pParent, const CRect& rect) {
    return CWnd::Create(
        AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
            ::LoadCursor(NULL, IDC_ARROW),
            (HBRUSH)(COLOR_WINDOW + 1)),
        L"ChatPanel", WS_CHILD | WS_VISIBLE, rect, pParent, 0) == TRUE;
}

void ChatPanel::OnUpdate(int eventType, void* pData) {
    if (eventType == EVT_CHAT_CHANGED && pData) {
        m_messages = *static_cast<std::vector<ChatMessage>*>(pData);
        Invalidate(); UpdateWindow();
    }
}

BOOL ChatPanel::OnEraseBkgnd(CDC* pDC) {
    CRect r; GetClientRect(&r);
    pDC->FillSolidRect(&r, RGB(255, 255, 255));
    return TRUE;
}

void ChatPanel::OnPaint() {
    CPaintDC dc(this);
    CRect client; GetClientRect(&client);

    dc.SetBkMode(TRANSPARENT);

    // Title
    CFont fTitle; fTitle.CreateFont(15, 0, 0, 0, FW_BOLD, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    CFont* pPrev = dc.SelectObject(&fTitle);
    dc.SetTextColor(RGB(15, 23, 42));
    dc.TextOut(16, 12, L"Direct Messages");
    dc.SelectObject(pPrev);

    // Messages
    CFont fName; fName.CreateFont(13, 0, 0, 0, FW_BOLD, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");
    CFont fMsg;  fMsg.CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, 0, L"Segoe UI");

    int y = 44;
    for (auto& m : m_messages) {
        if (y + 56 > client.bottom) break;

        // Avatar circle
        int cx = 28, cy = y + 20, r = 16;
        CBrush avBrush(RGB(99, 102, 241));
        CBrush* pOld = dc.SelectObject(&avBrush);
        CPen noP(PS_NULL, 0, 0); CPen* pOldP = dc.SelectObject(&noP);
        dc.Ellipse(cx - r, cy - r, cx + r, cy + r);
        dc.SelectObject(pOldP); dc.SelectObject(pOld);

        // Initial
        dc.SetTextColor(RGB(255, 255, 255));
        dc.SelectObject(&fName);
        CString init = m.sender.Left(1);
        dc.TextOut(cx - 5, cy - 7, init);

        // Name + time
        dc.SetTextColor(RGB(15, 23, 42));
        dc.TextOut(52, y + 6, m.sender);

        dc.SetTextColor(RGB(148, 163, 184));
        dc.SelectObject(&fMsg);
        dc.TextOut(client.right - 44, y + 8, m.time);

        // Message text
        dc.SetTextColor(RGB(71, 85, 105));
        dc.TextOut(52, y + 24, m.text);

        // Divider
        CPen divPen(PS_SOLID, 1, RGB(226, 232, 240));
        pOldP = dc.SelectObject(&divPen);
        dc.MoveTo(52, y + 46); dc.LineTo(client.right - 8, y + 46);
        dc.SelectObject(pOldP);

        y += 52;
    }
}
