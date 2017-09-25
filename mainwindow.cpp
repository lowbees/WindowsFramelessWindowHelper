#include "mainwindow.h"
#include "FramelessHelper/framelesswidgethelper.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    FramelessWidgetHelper *helper = new FramelessWidgetHelper(this);

    helper->setTitleHeight(30);
    helper->addTitleObject(ui->pushButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}
