#include "pathdialog.h"
#include "ui_pathdialog.h"

PathDialog::PathDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PathDialog)
{
    ui->setupUi(this);
}

PathDialog::~PathDialog()
{
    delete ui;
}
