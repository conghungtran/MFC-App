#pragma once
#include <afxwin.h>
#include "Resource.h"
#include "DashboardModel.h"
#include "StatCardPanel.h"
#include "ChartPanel.h"
#include "ChatPanel.h"
#include "TablePanel.h"

// ──────────────────────────────────────────────────────────────────
//  MainFrame  – cửa sổ chính
//  Chứa: Navbar (top) · Sidebar (left) · tất cả panels (content)
//  Đăng ký các panel với DashboardModel (Observer pattern)
// ──────────────────────────────────────────────────────────────────
class MainFrame : public CFrameWnd {
public:
    explicit MainFrame(DashboardModel* pModel);
    ~MainFrame();

private:
    DashboardModel* m_pModel;

    // ── Child panels (Concrete Observers) ──────────────────────────
    StatCardPanel m_statCards;
    ChartPanel    m_chart;
    ChatPanel     m_chat;
    TablePanel    m_table;

    // ── Sidebar buttons ────────────────────────────────────────────
    CButton m_btnDashboard;
    CButton m_btnUIElements;
    CButton m_btnForms;
    CButton m_btnTables;
    CButton m_btnCharts;

    // ── Navbar controls ────────────────────────────────────────────
    CButton m_btnRefresh;
    CButton m_btnUser;
    CEdit   m_edtSearch;

    // ── State ──────────────────────────────────────────────────────
    bool m_bSidebarVisible;

    // ── Helpers ───────────────────────────────────────────────────
    void RegisterObservers();
    void LayoutPanels(int cx, int cy);
    void DrawNavbar(CDC& dc, const CRect& r);
    void DrawSidebar(CDC& dc, const CRect& r);

    // ── Message handlers ──────────────────────────────────────────
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnRefreshClicked();
    afx_msg void OnMenuToggle();
    afx_msg void OnMenuDashboard();

    DECLARE_MESSAGE_MAP()
};
