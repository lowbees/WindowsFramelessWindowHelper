#include "basicframelesshelper.h"
#include "nativeeventfilter.h"
#include <windows.h>
#include <windowsx.h>
#include <QtWin>
BasicFramelessHelper::BasicFramelessHelper(QObject *parent)
    : QObject(parent)
    , m_window(Q_NULLPTR)
    , m_titleHeight(0)
    , m_leftResizeMargin(6)
    , m_topResizeMargin(6)
    , m_rightResizeMargin(6)
    , m_bottomResizeMargin(6)
{

}

BasicFramelessHelper::~BasicFramelessHelper()
{
    // This is very important for the qml application,
    // if you do not have the following statement, call the Qt.quit method will crash
    if (m_window) NativeEventFilter::deliver(m_window, Q_NULLPTR);
}

void BasicFramelessHelper::addTitleObjects(const QObjectList &objs)
{
    m_objects.append(objs);
}

void BasicFramelessHelper::addTitleObject(QObject *obj)
{
    m_objects.append(obj);
}

int BasicFramelessHelper::hitTest(int x, int y)
{
    int w = m_window->width();
    int h = m_window->height();

    bool onLeft = (x >= 0 && x <= m_leftResizeMargin);
    bool onTop = (y >= 0 && y <= m_topResizeMargin);
    bool onRight = (x >= w - m_rightResizeMargin && x <= w);
    bool onBottom = (y >= h - m_bottomResizeMargin && y <= h);


    if (onLeft && onTop)
        return HTTOPLEFT;
    else if (onLeft && onBottom)
        return HTBOTTOMLEFT;
    else if (onRight && onTop)
        return HTTOPRIGHT;
    else if (onRight && onBottom)
        return HTBOTTOMRIGHT;
    else if (onLeft)
        return HTLEFT;
    else if (onTop)
        return HTTOP;
    else if (onRight)
        return HTRIGHT;
    else if (onBottom)
        return HTBOTTOM;
    if (y > 0 && y < m_titleHeight) {
        if (isCaption(x, y)) return HTCAPTION;
    }
    return HTCLIENT;
}

bool BasicFramelessHelper::nativeEventFilter(void *message, long *result)
{
    auto lpMsg = (LPMSG)message;

    if (m_window && m_window->winId() == reinterpret_cast<WId>(lpMsg->hwnd)) {
        if (lpMsg->message == WM_NCHITTEST) {
            int nX = GET_X_LPARAM(lpMsg->lParam) - m_window->x();
            int nY = GET_Y_LPARAM(lpMsg->lParam) - m_window->y();
            *result = hitTest(nX, nY);
            return true;
        }
        else if (lpMsg->message == WM_NCACTIVATE) {
            *result = 1;
            return true;
        }
        else if (lpMsg->message == WM_NCCALCSIZE)
            return true;

    }

    return false;
}
