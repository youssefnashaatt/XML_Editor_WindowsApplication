#include "finddialog.h"
#include "ui_finddialog.h"
#include "mainwindow.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_Ok_PushButton_clicked()
{
    save();
    accept();
}





void FindDialog::on_Back_PushButton_clicked()
{
    save();
    M_Backwords = true;
    accept();
}


void FindDialog::on_Cancel_PushButton_clicked()
{
    reject();
}



bool FindDialog::getM_Backwords() const
{
    return M_Backwords;
}

bool FindDialog::getM_Whole_Text() const
{
    return M_Whole_Text;
}

bool FindDialog::getM_Case_Sensitive() const
{
    return M_Case_Sensitive;
}

QString FindDialog::getM_Text() const
{
    return M_Text;
}


void FindDialog::save(){
    M_Text = ui->lineEdit->text();
    M_Case_Sensitive = ui->Case_Sensitive_CheckBox->isChecked();
    M_Whole_Text = ui->Match_Whole_Word_CheckBox->isChecked();
    M_Backwords = false;
}

