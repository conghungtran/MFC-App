#pragma once
#include <afxwin.h>
#include "IObserver.h"
#include "DashboardModel.h"

// ──────────────────────────────────────────────────────────────────
//  ChatPanel  – hiển thị danh sách tin nhắn trực tiếp
//  Implements IObserver: cập nhật khi nhận EVT_CHAT_CHANGED
// ──────────────────────────────────────────────────────────────────
class ChatPanel : public CWnd, public IObserver {
public:
    ChatPanel();
    bool Create(CWnd* pParent, const CRect& rect);

    void OnUpdate(int eventType, void* pData) override;

private:
    std::vector<ChatMessage> m_messages;

    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    DECLARE_MESSAGE_MAP()
};
