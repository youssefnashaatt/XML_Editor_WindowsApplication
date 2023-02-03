#ifndef GRAPHVIZDIALOG_H
#define GRAPHVIZDIALOG_H

#include <QDialog>

namespace Ui {
class GraphvizDialog;
}

class GraphvizDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraphvizDialog(QWidget *parent = nullptr);
    ~GraphvizDialog();

    QString getGraphviz_Path() const;
    QString getOutput_Path() const;

private slots:
    void on_OK_PushButton_clicked();

    void on_Cancel_PushButton_clicked();

private:
    Ui::GraphvizDialog *ui;
    void save();
    QString Graphviz_PATH;
    QString OUTPUT_PATH;
};

#endif // GRAPHVIZDIALOG_H
