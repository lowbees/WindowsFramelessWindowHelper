# WindowsFramelessWindow
Windows版无边框窗口缩放，支持QML和Widget <br />
参考猫大的 https://github.com/qtdevs/FramelessHelper <br />
还有这个 http://www.cnblogs.com/dongc/p/5598053.html <br />

# 使用方法 #
QWidget
`
  FramelessWidgetHelper *helper = new FramelessWidgetHelper(this);
  helper->setTitleHeight(30);
  helper->addTitleObject(ui->pushButton);
`  
QML比较麻烦
`
  FramelessWindowHelper {
        Component.onCompleted: {
            addTitleObject(button)
            setTitleHeight(30)
        }
    }
    Item {
        anchors.fill: parent
        anchors.margins: rootWindow.visibility === ApplicationWindow.Maximized ?
                             8 : 0
    }
`
因为窗口在最大化时会超出屏幕大小所以你需要提供一个Item来作为整个qml程序的主界面，以提供margin 
