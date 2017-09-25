#ifndef FRAMELESSWINDOWHELPER_H
#define FRAMELESSWINDOWHELPER_H

#include "basicframelesshelper.h"
#include <QQmlParserStatus>
#include <QQuickWindow>
#include <QQuickItem>

class FramelessWindowHelper : public BasicFramelessHelper, public QQmlParserStatus
{
    Q_INTERFACES(QQmlParserStatus)
public:
    FramelessWindowHelper(QObject *parent = 0);

    // QQmlParserStatus interface
public:
    virtual void classBegin() Q_DECL_FINAL;
    virtual void componentComplete() Q_DECL_FINAL;

    // BasicFramelessHelper interface
public:
    virtual bool nativeEventFilter(void *message, long *result) Q_DECL_FINAL;

protected:
    virtual bool isCaption(int x, int y) Q_DECL_FINAL;

private:
    QQuickWindow *m_quickWindow;
};

#endif // FRAMELESSWINDOWHELPER_H
