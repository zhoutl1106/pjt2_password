#include "dialog.h"
#include "ui_dialog.h"
#include "encryption.h"
#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->calendarWidget,SIGNAL(clicked(QDate)),ui->dateEdit,SLOT(setDate(QDate)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString op = QString::number(ui->spinBox->value());
    if(op.length() == 1)
        op.insert(0,"0");
    QString code;
    if(ui->checkBox->isChecked())
        code = Encryption::genPasscode(ui->lineEdit->text(),QDate(2099,9,9),op);
    else
        code = Encryption::genPasscode(ui->lineEdit->text(),ui->dateEdit->date(),op);
    if(code.length() == 0)
        QMessageBox::critical(NULL,"警告","解锁码生成错误，请检查输入");
    else
        ui->lineEditResult->setText(code);
}

void Dialog::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->dateEdit->setEnabled(false);
        ui->calendarWidget->setEnabled(false);
    }
    else
    {
        ui->dateEdit->setEnabled(true);
        ui->calendarWidget->setEnabled(true);
    }
}
