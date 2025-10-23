#ifndef PATHDIALOG_H
#define PATHDIALOG_H

#include <QDialog>

namespace Ui {
class PathDialog;
}

class PathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PathDialog(QWidget *parent = nullptr);
    ~PathDialog();

private:
    Ui::PathDialog *ui;
};

#endif // PATHDIALOG_H
