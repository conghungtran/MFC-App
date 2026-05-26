#pragma once
#include "IObserver.h"
#include <vector>

// ──────────────────────────────────────────────────────────────────
//  ISubject  – Subject quản lý danh sách Observer và phát thông báo
// ──────────────────────────────────────────────────────────────────
class ISubject {
protected:
    std::vector<IObserver*> m_observers;

public:
    virtual ~ISubject() = default;

    void Attach(IObserver* obs) {
        m_observers.push_back(obs);
    }

    void Detach(IObserver* obs) {
        auto it = std::find(m_observers.begin(), m_observers.end(), obs);
        if (it != m_observers.end())
            m_observers.erase(it);
    }

    // Gửi thông báo tới tất cả observer đang đăng ký
    void Notify(int eventType, void* pData = nullptr) {
        for (IObserver* obs : m_observers)
            obs->OnUpdate(eventType, pData);
    }
};
