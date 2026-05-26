#pragma once
#include <afxwin.h>
#include "IObserver.h"
#include "DashboardModel.h"

// ──────────────────────────────────────────────────────────────────
//  ChartPanel  – vẽ đường biểu đồ Sales Value theo tháng
//  Implements IObserver: cập nhật khi nhận EVT_CHART_CHANGED
// ──────────────────────────────────────────────────────────────────
class ChartPanel : public CWnd, public IObserver {
public:
    ChartPanel();
    bool Create(CWnd* pParent, const CRect& rect);

    void OnUpdate(int eventType, void* pData) override;

private:
    std::vector<ChartPoint> m_points;

    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    DECLARE_MESSAGE_MAP()
};
