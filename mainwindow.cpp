#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui/pathdialog.h"
#include <qtoolbar.h>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pathDiglog(nullptr)
{
    ui->setupUi(this);
    QToolBar *mainBar = new QToolBar(this);
    this->addToolBar(mainBar);
    QAction *cfgLoadBtn = new QAction(QIcon(":/res/cfg_load.png"), "Load Search Configuration", this);
    mainBar->addAction(cfgLoadBtn);
    QAction *cfgSaveBtn = new QAction(QIcon(":/res/save.png"), "Save Search Configuration", this);
    mainBar->addAction(cfgSaveBtn);
    QAction *startSearchBtn = new QAction(QIcon(":/res/start.png"), "Start Search", this);
    mainBar->addAction(startSearchBtn);
    QAction *refreshResultBtn = new QAction(QIcon(":/res/refresh.png"), "Refresh Search Result", this);
    mainBar->addAction(refreshResultBtn);
    QAction *openFolderBtn = new QAction(QIcon(":/res/filefolder.png"), "Open Folder", this);
    mainBar->addAction(openFolderBtn);
    connect(openFolderBtn, &QAction::triggered, this, &MainWindow::openPathWindow);
    QAction *lastStepBtn = new QAction(QIcon(":/res/left.png"), "Last Step", this);
    mainBar->addAction(lastStepBtn);
    QAction *nextStepBtn = new QAction(QIcon(":/res/right.png"), "Next Step", this);
    mainBar->addAction(nextStepBtn);
    QAction *warningBtn = new QAction(QIcon(":/res/warning.png"), "Warning", this);
    mainBar->addAction(warningBtn);
    QAction *autoBtn = new QAction(QIcon(":/res/auto.png"), "Auto", this);
    mainBar->addAction(autoBtn);
    QAction *deleteTopBtn = new QAction(QIcon(":/res/delete_top.png"), "Delete Top", this);
    mainBar->addAction(deleteTopBtn);
    QAction *deleteBottomBtn = new QAction(QIcon(":/res/delete_bottom.png"), "Delete Bottom", this);
    mainBar->addAction(deleteBottomBtn);
    QAction *deleteAllBtn = new QAction(QIcon(":/res/delete_all.png"), "Delete All", this);
    mainBar->addAction(deleteAllBtn);
    QAction *TopToBottomBtn = new QAction(QIcon(":/res/top_to_bottom.png"), "Replace the image below with the one above.", this);
    mainBar->addAction(TopToBottomBtn);
    QAction *BottomToTopBtn = new QAction(QIcon(":/res/bottom_to_top.png"), "Replace the image above with the one below.", this);
    mainBar->addAction(BottomToTopBtn);
    // mainBar->setIconSize(QSize(40, 40));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openPathWindow()
{
    if (!pathDiglog)
    {
        pathDiglog = new PathDialog(this);
    }
    pathDiglog->show();           // 显示新窗口
    pathDiglog->raise();          // 将窗口提到最前面
    pathDiglog->activateWindow(); // 激活窗口
}
