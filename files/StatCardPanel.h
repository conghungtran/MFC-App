#pragma once
#include <afxwin.h>
#include "IObserver.h"
#include "DashboardModel.h"

// ──────────────────────────────────────────────────────────────────
//  StatCardPanel  – vẽ 4 thẻ thống kê (Revenue / Users / Sales / Active)
//  Implements IObserver: tự vẽ lại khi nhận EVT_STATS_CHANGED
// ──────────────────────────────────────────────────────────────────
class StatCardPanel : public CWnd, public IObserver {
public:
    StatCardPanel();
    bool Create(CWnd* pParent, const CRect& rect);

    // IObserver
    void OnUpdate(int eventType, void* pData) override;

private:
    std::vector<StatData> m_stats;

    void DrawCard(CDC& dc, const CRect& r, const StatData& s);

    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    DECLARE_MESSAGE_MAP()
};
