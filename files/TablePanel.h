#pragma once
#include <afxwin.h>
#include "IObserver.h"
#include "DashboardModel.h"

// ──────────────────────────────────────────────────────────────────
//  TablePanel  – hiển thị bảng danh sách giao dịch
//  Implements IObserver: cập nhật khi nhận EVT_TABLE_CHANGED
// ──────────────────────────────────────────────────────────────────
class TablePanel : public CWnd, public IObserver {
public:
    TablePanel();
    bool Create(CWnd* pParent, const CRect& rect);

    void OnUpdate(int eventType, void* pData) override;

private:
    std::vector<TableRow> m_rows;

    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    DECLARE_MESSAGE_MAP()
};
