#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
}

aboutDialog::~aboutDialog()
{
    delete ui;
}

void aboutDialog::on_githubPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/PinappleUnderTheSea/os223"));
}
