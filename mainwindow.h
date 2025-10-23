/*
 * @Author: JKWTCN jkwtcn@icloud.com
 * @Date: 2025-10-15 20:05:55
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-10-23 21:29:32
 * @FilePath: \DejaView\mainwindow.h
 * @Description:
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui/pathdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PathDialog *pathDiglog = nullptr;
private slots:
    void openPathWindow();
};
#endif // MAINWINDOW_H
