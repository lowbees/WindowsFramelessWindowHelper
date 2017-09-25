#ifndef NATIVEEVENTFILTER_H
#define NATIVEEVENTFILTER_H

#include <QAbstractNativeEventFilter>

#include <QWindow>

class BasicFramelessHelper;
class NativeEventFilter : public QAbstractNativeEventFilter
{
public:
    /**
    *@brief 使用QHash来进行统一管理无边框窗口
    *@author lowbees
    *@date 2017/09/25
    *@param window, framelesss window, helpers, framelesshelper
    *@return void
    */
    static void deliver(QWindow* window, BasicFramelessHelper *helper);

    // QAbstractNativeEventFilter interface
public:
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;

protected:
    NativeEventFilter() { }
private:
    static NativeEventFilter *instance;
    static QHash<WId, BasicFramelessHelper*> helpers;
};

#endif // NATIVEEVENTFILTER_H
