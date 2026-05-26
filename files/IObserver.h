#pragma once
#include <afxwin.h>

// ──────────────────────────────────────────────────────────────────
//  IObserver  – mọi panel muốn nhận thông báo đều implement interface này
// ──────────────────────────────────────────────────────────────────
class IObserver {
public:
    virtual ~IObserver() = default;

    // eventType : một trong các EVT_* định nghĩa trong Resource.h
    // pData     : con trỏ tới dữ liệu mới (cast tùy event)
    virtual void OnUpdate(int eventType, void* pData) = 0;
};
