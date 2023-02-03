#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>


#define FileType_XML    0
#define FileType_JSON   1

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_Minif_XML_clicked();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_INPUT_textEdit_textChanged();

    void on_OUTPUT_textEdit_textChanged();

    void on_actionSave_output_file_triggered();

    void on_XML_Validate_clicked();

    void on_actionSave_as_Output_File_triggered();

    void on_actionExit_triggered();

    void on_XML_TO_JSON_clicked();

    void on_Prettify_clicked();

    void on_CompressButton_clicked();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionFind_triggered();

    void on_actionSelect_all_triggered();

    void on_actionInput_triggered();

    void on_actionOutput_triggered();

    void on_actionInput_2_triggered();

    void on_actionOutput_2_triggered();

    void on_actionAbout_us_triggered();

    void on_actionValidate_XML_triggered();

    void on_actionMinify_XML_triggered();

    void on_actionPrettify_XML_triggered();

    void on_actionConvert_XML_to_JSON_triggered();

    void on_pushButton_clicked();

    void on_Graph_XML_Button_clicked();

    void on_Decompress_PushButton_clicked();


    void on_Correct_XML_Button_clicked();



    void on_Network_Analysis_Button_clicked();

    void on_actionCompress_XML_File_triggered();

    void on_actionDecompress_XML_file_triggered();

private:
    Ui::MainWindow *ui;
    QString INPUT_Path, OUTPUT_Path, Text;
    bool INPUT_Edited, OUTPUT_Edited, INPUT_File_Type, OUTPUT_File_Type;



    void NewFile(void);
    void OpenFile(void);
    void CheckSave_INPUT(void);
    void CheckSave_OUTPUT(void);
    void Save_INPUT(QString Tab_Path);
    void Save_OUTPUT(QString Tab_Path);
    void SaveAs_INPUT(void);
    void SaveAs_OUTPUT(void);
    void Highlight(int index);
     //int checking_errors(vector<std::string> &strr, vector<std::string> &modified, vector<int> &error);
    void Compression(QString XML);
    void DeCompression(QString XML);
    void PostSearch(std::string word);
    void Network_Analysis(void);
};
#endif // MAINWINDOW_H
