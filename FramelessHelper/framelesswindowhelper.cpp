#include "framelesswindowhelper.h"
#include "nativeeventfilter.h"

#include <windows.h>
#include <QScreen>

FramelessWindowHelper::FramelessWindowHelper(QObject *parent)
    : BasicFramelessHelper(parent)
    , m_quickWindow(Q_NULLPTR)
{

}

void FramelessWindowHelper::classBegin()
{
}

void FramelessWindowHelper::componentComplete()
{
    auto obj = parent();
    while (Q_NULLPTR != obj) {
        if (obj->inherits("QQuickRootItem")) {
            auto rootItem = qobject_cast<QQuickItem *>(obj);
            m_quickWindow = qobject_cast<QQuickWindow *>(rootItem->window());
            m_window = qobject_cast<QWindow*>(m_quickWindow);
            if (m_window) {
                NativeEventFilter::deliver(m_window, this);
                break;
            }
        }
        obj = obj->parent();
    }
}

bool FramelessWindowHelper::nativeEventFilter(void *message, long *result)
{

    auto b = BasicFramelessHelper::nativeEventFilter(message, result);

    if (b)
        return true;

    auto lpMsg = (LPMSG)message;
    if (lpMsg->message == WM_GETMINMAXINFO) {
        auto screen = m_window->screen();
        auto frameRect = screen->availableGeometry();
        auto lpMMInfo = reinterpret_cast<LPMINMAXINFO>(lpMsg->lParam);

        lpMMInfo->ptMinTrackSize.x = m_window->minimumWidth();
        lpMMInfo->ptMinTrackSize.y = m_window->minimumHeight();
        lpMMInfo->ptMaxTrackSize.x = frameRect.width();
        lpMMInfo->ptMaxTrackSize.y = frameRect.height();

        // Because window can't set margin, so we don't set ptMaxPosition and ptMaxSize,
        // we set the margin in qml file
        return true;
    }
    return false;
}

bool FramelessWindowHelper::isCaption(int x, int y)
{
    if (m_quickWindow) {
        auto contentItem = m_quickWindow->contentItem();
        if (contentItem) {
            auto child = contentItem->childAt(x, y);

            // 如果当前child有我们需要处理的对象则返回
            if (m_objects.contains(child))
                return false;

            QPointF gPos = contentItem->mapToGlobal(QPointF(x, y));

            //! [0]
            if (child) {
                auto pos = child->mapFromGlobal(gPos);
                // skip rootItem
                child = child->childAt(pos.x(), pos.y());
                if (m_objects.contains(child))
                    return false;

                // 遍历整个child查找是否有我们需要处理的对象
                //! [1]
                while (child) {
                    auto items = child->childItems();
                    for (int i = 0; i < items.length(); ++i) {
                        pos = items[i]->mapFromGlobal(gPos);
                        auto item = items[i]->childAt(pos.x(), pos.y());
                        if (item && m_objects.contains(item)) return false;
                    }
                    pos = child->mapFromGlobal(gPos);
                    child = child->childAt(pos.x(), pos.y());
                } //! [1]
            } //! [0]

        }
    }
    return true;
}
