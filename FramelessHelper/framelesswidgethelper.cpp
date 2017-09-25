#include "framelesswidgethelper.h"
#include "nativeeventfilter.h"
#include <windows.h>
#include <QScreen>
FramelessWidgetHelper::FramelessWidgetHelper(QWidget *parent)
    : BasicFramelessHelper(parent)
    , m_widget(parent)
{
    if (parent && (parent->windowFlags() & Qt::FramelessWindowHint))
        parent->installEventFilter(this);

}


bool FramelessWidgetHelper::eventFilter(QObject *watched, QEvent *event)
{
    // The window system identifer for this native widget has changed.
    // The WId should get only this event changed
    if (event->type() == QEvent::WinIdChange && m_widget) {
        // Our purpose has been reached, so remove event filter
        m_widget->removeEventFilter(this);
        // set parent m_widow for WM_NCHITTEST event
        m_window = m_widget->windowHandle();

        NativeEventFilter::deliver(m_window, this);
    }
    return QObject::eventFilter(watched, event);
}

bool FramelessWidgetHelper::nativeEventFilter(void *message, long *result)
{

    auto b = BasicFramelessHelper::nativeEventFilter(message, result);

    if (b)
        return true;

    auto lpMsg = (LPMSG)message;
    if (lpMsg->message == WM_GETMINMAXINFO) {
        static QMargins margins = m_widget->contentsMargins();
        // widget will large than screen size when maximized, so extend margins for it

        auto screen = m_window->screen();
        auto frameRect = screen->availableGeometry();
        auto lpMMInfo = reinterpret_cast<LPMINMAXINFO>(lpMsg->lParam);

        lpMMInfo->ptMinTrackSize.x = m_window->minimumWidth();
        lpMMInfo->ptMinTrackSize.y = m_window->minimumHeight();
        lpMMInfo->ptMaxTrackSize.x = frameRect.width();
        lpMMInfo->ptMaxTrackSize.y = frameRect.height();
        if (IsZoomed(lpMsg->hwnd)) {
            RECT frame = { 0, 0, 0, 0 };
            AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
            frame.left = abs(frame.left);
            frame.top = abs(frame.bottom);
            m_widget->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
        }
        else
            m_widget->setContentsMargins(margins);
        return true;
    }
    return false;
}

bool FramelessWidgetHelper::isCaption(int x, int y)
{
    if (m_widget && m_objects.size() > 0) {
        auto child = m_widget->childAt(x, y);
        return !m_objects.contains(child);
    }
    return true;
}
