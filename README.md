# WindowsFramelessWindow
Windows版无边框窗口缩放，支持QML和Widget <br />
参考猫大的 https://github.com/qtdevs/FramelessHelper <br />
还有这个 http://www.cnblogs.com/dongc/p/5598053.html <br />

# 使用方法 #
QWidget <br />
`
  FramelessWidgetHelper *helper = new FramelessWidgetHelper(this); <br />
  helper->setTitleHeight(30); <br />
  helper->addTitleObject(ui->pushButton); <br />
`  
QML比较麻烦 <br />
`
  FramelessWindowHelper { <br />
        Component.onCompleted: { <br />
            addTitleObject(button) <br />
            setTitleHeight(30) <br />
        } <br />
    } <br />
    Item { <br />
        anchors.fill: parent <br />
        anchors.margins: rootWindow.visibility === ApplicationWindow.Maximized ? 8 : 0 <br />
    } <br />
`
因为窗口在最大化时会超出屏幕大小所以你需要提供一个Item来作为整个qml程序的主界面，以提供margin 
