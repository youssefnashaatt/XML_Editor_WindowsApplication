#include "graphvizdialog.h"
#include "ui_graphvizdialog.h"

GraphvizDialog::GraphvizDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphvizDialog)
{
    ui->setupUi(this);
}

GraphvizDialog::~GraphvizDialog()
{
    delete ui;
}

void GraphvizDialog::on_OK_PushButton_clicked()
{
    save();
    accept();
}




void GraphvizDialog::on_Cancel_PushButton_clicked()
{
    reject();
}


void GraphvizDialog::save(){
    Graphviz_PATH = ui->Line_Edit_Graphviz->text();
    OUTPUT_PATH = ui->Line_Edit_Output->text();
}


QString GraphvizDialog::getGraphviz_Path() const
{
    return Graphviz_PATH;
}


QString GraphvizDialog::getOutput_Path() const
{
    return OUTPUT_PATH;
}

