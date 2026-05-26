#include "DashboardApp.h"
#include "DashboardModel.h"
#include "MainFrame.h"

// Global application object (bắt buộc với MFC)
DashboardApp theApp;

BOOL DashboardApp::InitInstance() {
    // Tạo Model (Subject trung tâm)
    DashboardModel* pModel = new DashboardModel();

    // Tạo Frame và truyền Model vào
    // MainFrame sẽ tự Attach các panel làm Observer
    MainFrame* pFrame = new MainFrame(pModel);
    m_pMainWnd = pFrame;

    pFrame->ShowWindow(SW_SHOWMAXIMIZED);
    pFrame->UpdateWindow();

    return TRUE;
}
