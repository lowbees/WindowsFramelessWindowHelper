#ifndef BASICFRAMELESSHELPER_H
#define BASICFRAMELESSHELPER_H

#include <QObject>
#include <QWindow>
#include <QMargins>

class BasicFramelessHelper : public QObject
{
    Q_OBJECT
    // Note that a NOTIFY signal must be specified to allow QML property bindings.
    Q_PROPERTY(int titleHeight READ titleHeight WRITE setTitleHeight NOTIFY titleHeightChanged)
    Q_PROPERTY(int leftResizeMargin READ leftResizeMargin WRITE setLeftResizeMargin NOTIFY leftResizeMarginChanged)
    Q_PROPERTY(int topResizeMargin READ topResizeMargin WRITE setTopResizeMargin NOTIFY topResizeMarginChanged)
    Q_PROPERTY(int rightResizeMargin READ rightResizeMargin WRITE setRightResizeMargin NOTIFY rightResizeMarginChanged)
    Q_PROPERTY(int bottomResizeMargin READ bottomResizeMargin  WRITE setBottomResizeMargin NOTIFY bottomResizeMarginChanged)
public:
    explicit BasicFramelessHelper(QObject *parent = 0);
    ~BasicFramelessHelper();
public:
    virtual bool nativeEventFilter(void *message, long *result) = 0;

    // for the title bar which object can be pressed
    Q_INVOKABLE void addTitleObjects(const QObjectList &objs);
    Q_INVOKABLE void addTitleObject(QObject *obj);

    Q_INVOKABLE int titleHeight() const {
        return m_titleHeight;
    }
    Q_INVOKABLE void setTitleHeight(int h) {
        if (h >= 0 && h != m_titleHeight) {
            m_titleHeight = h;
            titleHeightChanged(h);
        }
    }
    Q_INVOKABLE int leftResizeMargin()  const {
        return m_leftResizeMargin;
    }
    Q_INVOKABLE void setLeftResizeMargin(int m) {
        if (m >= 0 && m != m_leftResizeMargin) {
            m_leftResizeMargin = m;
            leftResizeMarginChanged(m);
        }
    }

    Q_INVOKABLE int topResizeMargin()  const {
        return m_topResizeMargin;
    }
    Q_INVOKABLE void setTopResizeMargin(int m) {
        if (m >= 0 && m != m_topResizeMargin) {
            m_topResizeMargin = m;
            topResizeMarginChanged(m);
        }
    }
    Q_INVOKABLE int rightResizeMargin()  const {
        return m_rightResizeMargin;
    }
    Q_INVOKABLE void setRightResizeMargin(int m) {
        if (m >= 0 && m != m_rightResizeMargin) {
            m_rightResizeMargin = m;
            rightResizeMarginChanged(m);
        }
    }
    Q_INVOKABLE int bottomResizeMargin()  const {
        return m_leftResizeMargin;
    }
    Q_INVOKABLE void setBottomResizeMargin(int m) {
        if (m >= 0 && m != m_bottomResizeMargin) {
            m_bottomResizeMargin = m;
            bottomResizeMarginChanged(m);
        }
    }

signals:
    void titleHeightChanged(int);
    void leftResizeMarginChanged(int);
    void topResizeMarginChanged(int);
    void rightResizeMarginChanged(int);
    void bottomResizeMarginChanged(int);
protected:
    // subclass must implement this method
    virtual bool isCaption(int x, int y) = 0;

private:
    int hitTest(int x, int y);

protected:
    QWindow *m_window;
    QObjectList m_objects;
    int m_titleHeight;
    int m_leftResizeMargin;
    int m_topResizeMargin;
    int m_rightResizeMargin;
    int m_bottomResizeMargin;

};

#endif // BASICFRAMELESSHELPER_H
