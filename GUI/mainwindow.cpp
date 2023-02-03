#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "XML_Minifying.h"
#include "XML_Validation.h"
#include "json.h"
#include "XML_fileHandling.h"
#include "prettify.h"
#include "finddialog.h"
#include "XML_Data.h"
#include "graph.h"
#include "graphvizdialog.h"
#include "compression.h"
#include "users_analysis.h"

#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <string>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("XML Editor");
    NewFile();
    ui->actionDecompress_XML_file->setEnabled(false);
    ui->Decompress_PushButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/***************************************************************************************************************
 *                                         MenuBar Actions
 **************************************************************************************************************/

void MainWindow::on_actionNew_triggered()
{
    CheckSave_INPUT();
    CheckSave_OUTPUT();
    NewFile();
}



void MainWindow::on_actionOpen_triggered()
{
    OpenFile();
}


void MainWindow::on_actionSave_triggered()
{

    Save_INPUT(INPUT_Path);
}


void MainWindow::on_actionSave_as_triggered()
{
    SaveAs_INPUT();
}


void MainWindow::on_actionSave_output_file_triggered()
{
    Save_OUTPUT(INPUT_Path);
}



void MainWindow::on_actionSave_as_Output_File_triggered()
{
    SaveAs_OUTPUT();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->INPUT_textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->INPUT_textEdit->redo();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->INPUT_textEdit->copy();
    ui->statusbar->showMessage("Copied to clipboard");
}


void MainWindow::on_actionCut_triggered()
{
    ui->INPUT_textEdit->cut();
    ui->statusbar->showMessage("Selected cutted");
}


void MainWindow::on_actionPaste_triggered()
{
    ui->INPUT_textEdit->paste();
}


void MainWindow::on_actionSelect_all_triggered()
{
    ui->INPUT_textEdit->selectAll();
}


void MainWindow::on_actionFind_triggered()
{

}


void MainWindow::on_actionInput_triggered()
{
    ui->INPUT_textEdit->zoomIn(1);
    ui->statusbar->showMessage("Input zoom in");
}


void MainWindow::on_actionOutput_triggered()
{
    ui->OUTPUT_textEdit->zoomIn(1);
    ui->statusbar->showMessage("Output zoom in");

}


void MainWindow::on_actionInput_2_triggered()
{
    ui->INPUT_textEdit->zoomOut(1);
    ui->statusbar->showMessage("Input zoom out");
}


void MainWindow::on_actionOutput_2_triggered()
{
    ui->OUTPUT_textEdit->zoomOut(1);
    ui->statusbar->showMessage("Output zoom out");
}


void MainWindow::on_actionValidate_XML_triggered()
{
    MainWindow::on_XML_Validate_clicked();
}


void MainWindow::on_actionMinify_XML_triggered()
{
    MainWindow::on_Minif_XML_clicked();
}


void MainWindow::on_actionPrettify_XML_triggered()
{
    MainWindow::on_Prettify_clicked();
}


void MainWindow::on_actionConvert_XML_to_JSON_triggered()
{
    MainWindow::on_XML_TO_JSON_clicked();
}

void MainWindow::on_actionAbout_us_triggered()
{
    QMessageBox::about(this, "About us", "Team Members\n1- Youssef Nashaat\n2- Engy Mohamed\n3- Nirvana Gamal");
}


void MainWindow::on_pushButton_clicked()
{
    FindDialog* dlg = new FindDialog(this);
    if(!dlg->exec()) return;

    QTextDocument::FindFlags flags;
    if(dlg->getM_Case_Sensitive()) flags = flags | QTextDocument::FindFlag::FindCaseSensitively;
    if(dlg->getM_Whole_Text()) flags = flags | QTextDocument::FindFlag::FindWholeWords;

    int count_find = 0;


    ui->INPUT_textEdit->moveCursor(QTextCursor::Start);

    QString Qword = dlg->getM_Text();
    std::string word = Qword.toUtf8().constData();
    PostSearch(word);

}



/***************************************************************************************************************
 *                                       Widgets Actions
 **************************************************************************************************************/


void MainWindow::on_INPUT_textEdit_textChanged()
{
    INPUT_Edited = true;
    ui->statusbar->clearMessage();

    if(OUTPUT_Edited == true)
    {
        ui->statusbar->showMessage("Input and Output Files are not saved !");
    }

    else
    {
        ui->statusbar->showMessage("Input Files is not saved !");
    }
}


void MainWindow::on_OUTPUT_textEdit_textChanged()
{
    OUTPUT_Edited = true;

    if(INPUT_Edited == true)
    {
        ui->statusbar->showMessage("Input and Output Files are not saved !");
    }

    else
    {
        ui->statusbar->showMessage("Output Files is not saved !");
    }
}


void MainWindow::on_XML_Validate_clicked()
{
    QString str = ui->INPUT_textEdit->toPlainText();
    std::string XML_Text = str.toUtf8().constData();

    XML_Validation* obj = new XML_Validation;
    int error_index = obj->XML_Validate(XML_Text);

    if(!error_index)
    {
        ui->OUTPUT_textEdit->clear();
        ui->OUTPUT_textEdit->setText(str);
        ui->statusbar->showMessage("File Validate Correctly");
    }

    else
    {
        if(obj->Inconsistent_Bracket)
        {
            string line_index = to_string(((error_index) / 500) + 1);
            string char_index = to_string((error_index) % 500);
            QString Qline_index = QString::fromStdString(line_index);
            QString Qchar_index = QString::fromStdString(char_index);

            ui->OUTPUT_textEdit->setText("Unclosed Bracket in line: " + Qline_index + " Char: " + Qchar_index);
            ui->statusbar->showMessage("File didn't Validate Correctly");
            //Highlight((error_index) / 500 + 1);
        }

        else if(obj->Incorrect_Tag_Syntax)
        {
            string line_index = to_string(((error_index) / 500) + 1);
            string char_index = to_string((error_index) % 500);
            QString Qline_index = QString::fromStdString(line_index);
            QString Qchar_index = QString::fromStdString(char_index);

            ui->OUTPUT_textEdit->setText("Unclosed Bracket in line: " + Qline_index + " Char: " + Qchar_index);
            ui->statusbar->showMessage("File didn't Validate Correctly");
            //Highlight((error_index) / 500 + 1);
        }

    }


    /*if(!XML_CheckBrackets(XML_Text))
    {
        if(!XML_TagSyntaxValidate(XML_Text))
        {
            ui->OUTPUT_textEdit->clear();
            ui->OUTPUT_textEdit->setText(str);
            ui->statusbar->showMessage("File Validate Correctly");
        }

        else
        {
            string line_index = to_string(((XML_TagSyntaxValidate(XML_Text)) / 500) + 1);
            string char_index = to_string((XML_TagSyntaxValidate(XML_Text)) % 500);
            QString Qline_index = QString::fromStdString(line_index);
            QString Qchar_index = QString::fromStdString(char_index);

            ui->statusbar->showMessage("Incorrect Tag or unclosed Tag in line: " + Qline_index + " Char: " + Qchar_index);
        }
    }

    else
    {
        string line_index = to_string(((XML_CheckBrackets(XML_Text)) / 500) + 1);
        string char_index = to_string((XML_CheckBrackets(XML_Text)) % 500);
        QString Qline_index = QString::fromStdString(line_index);
        QString Qchar_index = QString::fromStdString(char_index);

        ui->statusbar->showMessage("Unclosed Bracket in line: " + Qline_index + " Char: " + Qchar_index);
    }*/

    OUTPUT_File_Type = FileType_XML;
}


void MainWindow::on_Correct_XML_Button_clicked()
{
    /* vector<string> XML_Strings, Right_XML;
    vector<int> Errors;
    tree x;
    QString str = ui->INPUT_textEdit->toPlainText();
    if (str != ""){
        string text = str.toUtf8().constData();
        XML_Strings = XML_Parsing_Data(text);
        int e = checking_errors(XML_Strings, Right_XML, Errors);
        if (e){
            string str = "";
            // Errors Position in Screen
            x.insert(Right_XML, Errors);
            // Pre-Order Traverse
            str = x.Pre_Order();
            ui->textEdit->setPlainText(QString::fromStdString(str));
        }
        else
            ui->statusBar->showMessage("No errors exist in the file");
    }
    else{
        ui->statusBar->showMessage("The file is empty");
    }*/
    ui->OUTPUT_textEdit->setPlainText(ui->INPUT_textEdit->toPlainText());
}

void MainWindow::on_Minif_XML_clicked()
{
    QString str = ui->INPUT_textEdit->toPlainText();
    std::string input_text = str.toUtf8().constData();

    std::string output_text = XML_Minifying(input_text);
    ui->OUTPUT_textEdit->setPlainText(QString::fromStdString(output_text));

    OUTPUT_File_Type = FileType_XML;
}


void MainWindow::on_XML_TO_JSON_clicked()
{
    QString str = ui->INPUT_textEdit->toPlainText();
    std::string XML_Text = str.toUtf8().constData();

    vector <string> file_lines = XML_Parsing_Data(XML_Text);
    vector <string> file_lines_without_comments;
    FileWithoutComments(file_lines_without_comments, file_lines);
    file_lines = file_lines_without_comments;
    vector <Node*> nodes;
    XML_tree tree;
    stack <int> tags;
    XML_tree_creation(file_lines, nodes ,tree , tags);
    string ss = xml_to_json(tree);
    ui->OUTPUT_textEdit->setPlainText(QString::fromStdString(ss));
    OUTPUT_File_Type = FileType_JSON;
}


void MainWindow::on_Prettify_clicked()
{
    QString str = ui->INPUT_textEdit->toPlainText();
    std::string input_text = str.toUtf8().constData();
    std::string output_text;

    XML_Validation* obj = new XML_Validation;
    int validate_error_index = obj->XML_Validate(input_text);

    if(!validate_error_index)
    {
        vector<string> m = prettify(input_text);
        for (auto x : m) output_text += x;

        ui->OUTPUT_textEdit->clear();
        ui->OUTPUT_textEdit->setPlainText(QString::fromStdString(output_text));
    }

    else
    {

        if(obj->Inconsistent_Bracket)
        {
            string line_index = to_string(((validate_error_index) / 500) + 1);
            string char_index = to_string((validate_error_index) % 500);
            QString Qline_index = QString::fromStdString(line_index);
            QString Qchar_index = QString::fromStdString(char_index);

            ui->statusbar->showMessage("Unclosed Bracket in line: " + Qline_index + " Char: " + Qchar_index);
        }

        else if(obj->Incorrect_Tag_Syntax)
        {
            string line_index = to_string(((validate_error_index) / 500) + 1);
            string char_index = to_string((validate_error_index) % 500);
            QString Qline_index = QString::fromStdString(line_index);
            QString Qchar_index = QString::fromStdString(char_index);

            ui->statusbar->showMessage("Incorrect Tag or unclosed Tag in line: " + Qline_index + " Char: " + Qchar_index);
        }

    }

    OUTPUT_File_Type = FileType_XML;
}


void MainWindow::on_CompressButton_clicked()
{
    QString XML_Text = ui->INPUT_textEdit->toPlainText();
    Compression(XML_Text);
    ui->Decompress_PushButton->setEnabled(true);
    ui->actionDecompress_XML_file->setEnabled(true);
}



//Decompression Button
void MainWindow::on_Decompress_PushButton_clicked()
{
    QString XML_Text = ui->INPUT_textEdit->toPlainText();
    DeCompression(XML_Text);
    ui->Decompress_PushButton->setEnabled(false);
    ui->actionDecompress_XML_file->setEnabled(false);
}


void MainWindow::on_Graph_XML_Button_clicked()
{
    /*GraphvizDialog* dlg = new GraphvizDialog(this);
    if(!dlg->exec()) return;

    QString Graphviz_path = dlg->getGraphviz_Path();
    QString Output_path = dlg->getOutput_Path();

    ui->OUTPUT_textEdit->clear();*/


    //std::string graphviz_path = Graphviz_path.toUtf8().constData();
    //std::string output_path = Output_path.toUtf8().constData();

    /*QString str = ui->INPUT_textEdit->toPlainText();
    std::string XML_Text = str.toUtf8().constData();
    vector <string> file_lines = XML_Parsing_Data(XML_Text);
    string Data = vectortostring(file_lines);
    string graph =  graph_representation(Data);
    ofstream myfile("test.dot");
    myfile<<graph;
    myfile.close();
    system("C:\\Program Files\\Graphviz\\bin\\dot -Tpng test.dot -o test.png");*/

    QString str = ui->INPUT_textEdit->toPlainText();
    std::string XML_Text = str.toUtf8().constData();
    vector <string> file_lines = XML_Parsing_Data(XML_Text);
    string Data = vectortostring(file_lines);
    string graph =  graph_representation(Data);
    ui->OUTPUT_textEdit->clear();
    ui->OUTPUT_textEdit->setPlainText(QString::fromStdString(graph));

}

/***************************************************************************************************************
 *                                       Functions Definition
 **************************************************************************************************************/


void MainWindow::NewFile(void)
{
    ui->INPUT_textEdit->clear();
    ui->OUTPUT_textEdit->clear();
    ui->statusbar->showMessage("New File");
    INPUT_Path = "";
    OUTPUT_Path = "";
    Text = "";
    INPUT_Edited = false;
    OUTPUT_Edited = false;
    INPUT_File_Type = FileType_XML;
}


void MainWindow::OpenFile(void)
{
    QString Path = QFileDialog::getOpenFileName(this, tr("Open File"));
    if(Path.isEmpty()) return;

    QFile File(Path);
    if(!File.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", File.errorString());
        return;
    }

    QTextStream in(&File);
    Text = in.readAll();

    int index;
    for(int i = 0; i < Path.length(); i++){
        if(Path[i] == '/')
            index = i;
    }
    QString Name = Path.mid(index+1, Path.length()-index-1);
    QFileInfo fi(Path);                     // get the data of file
    QString Extension = fi.suffix();        // get the extension of the file
    if(Extension == "xml"){
        ui->INPUT_textEdit->setText(Text);
        ui->statusbar->showMessage("Open File - " + Name);
        INPUT_File_Type = FileType_XML;

    }

    else if(Extension == "json")
    {
        ui->INPUT_textEdit->setText(Text);
        ui->statusbar->showMessage("Open File - " + Name);
        INPUT_File_Type = FileType_JSON;

    }

    else
        QMessageBox::critical(this, "Erorr", "File Type must be XML");

    File.close();
    INPUT_Path = Path;
    INPUT_Edited = false;
    //ui->actionBack_to_XML_file->setEnabled(false);
    //ui->actionMake_JSON_file->setEnabled(true);
}


void MainWindow::CheckSave_INPUT(void)
{
    if(!INPUT_Edited) return;
    QMessageBox::StandardButton value = QMessageBox::question(this, "Save Input File",
                                                              "Do you want to save input file before closing it?");
    if(value != QMessageBox::StandardButton::Yes) return;
    if(INPUT_Path.isEmpty())
        SaveAs_INPUT();
    else
        Save_INPUT(INPUT_Path);
}


void MainWindow::CheckSave_OUTPUT(void)
{
    if(!OUTPUT_Edited) return;
    QMessageBox::StandardButton value = QMessageBox::question(this, "Save Output File",
                                                              "Do you want to save output file before closing it?");
    if(value != QMessageBox::StandardButton::Yes) return;
    if(OUTPUT_Path.isEmpty())
        SaveAs_OUTPUT();
    else
        Save_OUTPUT(OUTPUT_Path);
}



void MainWindow::Save_INPUT(QString Path)
{
    if(Path.isEmpty()){
        SaveAs_INPUT();
        return;
    }

    QFile File(Path);
    if(!File.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", File.errorString());
        ui->statusbar->showMessage("Error, can't save the file.");
        SaveAs_INPUT();
        return;
    }

    QTextStream out(&File);
    out << ui->INPUT_textEdit->toPlainText();
    File.close();

    INPUT_Path = Path;
    ui->statusbar->showMessage("Saved at" + Path);
}




void MainWindow::Save_OUTPUT(QString Path)
{
    if(Path.isEmpty()){
        SaveAs_OUTPUT();
        return;
    }

    QFile File(Path);
    if(!File.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", File.errorString());
        ui->statusbar->showMessage("Error, can't save the file.");
        SaveAs_OUTPUT();
        return;
    }

    QTextStream out(&File);
    out << ui->OUTPUT_textEdit->toPlainText();
    File.close();

    OUTPUT_Path = Path;
    ui->statusbar->showMessage("Saved at" + Path);
}




void MainWindow::SaveAs_INPUT(void)
{
    if(INPUT_File_Type == FileType_XML){
        QString Path = QFileDialog::getSaveFileName(this, tr("Save Input File as"), "Untitled.xml",
                                                    tr("XML File (*.xml);;All Files (*)"));
        if(Path.isEmpty()) return;
        if(!Path.endsWith(".xml"))
            Path.append(".xml");
        Save_INPUT(Path);
    }

    else if(INPUT_File_Type == FileType_JSON)
    {
        QString Path = QFileDialog::getSaveFileName(this, tr("Save File as"), "Untitled.json",
                                                    tr("JSON File (*.json);;All Files (*)"));
        if(Path.isEmpty()) return;
        if(!Path.endsWith(".json"))
            Path.append(".json");
        Save_INPUT(Path);
    }
}



void MainWindow::SaveAs_OUTPUT(void)
{
    if(OUTPUT_File_Type == FileType_XML){
        QString Path = QFileDialog::getSaveFileName(this, tr("Save Output File as"), "Untitled.xml",
                                                    tr("XML File (*.xml);;All Files (*)"));
        if(Path.isEmpty()) return;
        if(!Path.endsWith(".xml"))
            Path.append(".xml");
        Save_OUTPUT(Path);
    }

    else if(OUTPUT_File_Type == FileType_JSON)
    {
        QString Path = QFileDialog::getSaveFileName(this, tr("Save File as"), "Untitled.json",
                                                    tr("JSON File (*.json);;All Files (*)"));
        if(Path.isEmpty()) return;
        if(!Path.endsWith(".json"))
            Path.append(".json");
        Save_OUTPUT(Path);
    }
}




void MainWindow::Compression(QString XML)
{
    std::string XML_Text = XML.toUtf8().constData();
    std::vector<unsigned int> charFreq(256, 0);
    string s = generateCompressedCode(XML_Text, charFreq);
    QString Compressed_XML = QString::fromStdString(s);
    ui->OUTPUT_textEdit->clear();
    ui->OUTPUT_textEdit->setPlainText(Compressed_XML);
}



void MainWindow::DeCompression(QString XML)
{
    std::string XML_Text = XML.toUtf8().constData();
    std::vector<unsigned int> charFreq(256, 0);
    string s = generateCompressedCode(XML_Text, charFreq);
    string DeCompress_Text = generateDecompressedCode(s, charFreq);
    QString DeCompressed_XML = QString::fromStdString(DeCompress_Text);
    ui->OUTPUT_textEdit->clear();
    ui->OUTPUT_textEdit->setPlainText(DeCompressed_XML);
}



void MainWindow::Highlight(int error_index)
{
    int index = 0;
    int new_lines_count = 0;
    QString str = ui->INPUT_textEdit->toPlainText();
    std::string XML_Text = str.toUtf8().constData();



    while(new_lines_count < error_index)
    {
        while(index < XML_Text.length())
        {

            if(XML_Text.at(index) == '\n')
            {
                new_lines_count++;
            }
            index++;

        }
    }

    XML_Text.insert(index, "    <= Incorrect or Misclosed Tag");
    ui->INPUT_textEdit->setPlainText(QString::fromStdString(XML_Text));

}



void MainWindow::PostSearch(std::string word)
{
    int i = 0;
    std::string print = "";

    ui->OUTPUT_textEdit->clear();
    QString QWord = QString::fromStdString(word);
    QString str = ui->INPUT_textEdit->toPlainText();
    std::string XML_Text = str.toUtf8().constData();
    vector <string> xml_cutted = XML_Parsing_Data(XML_Text);


    while(i < xml_cutted.size())
    {
        if(xml_cutted[i] == (word))
        {
            if(!(xml_cutted[i - 1].compare("<topic>")))
            {
                while(xml_cutted[i].compare("<body>"))
                {
                    i--;
                }
                i++;
                print = xml_cutted[i];
                QString Qprint = QString::fromStdString(print);
                ui->OUTPUT_textEdit->setPlainText(ui->OUTPUT_textEdit->toPlainText() + "The Topic (" + QWord + ") is mentioned in this post\n" + Qprint + ":\n");
                break;

            }


        }




        i++;
    }

    while(i < xml_cutted.size())
    {
        if(ui->INPUT_textEdit->find(QWord))
        {
            while(xml_cutted[i].compare("<body>"))
            {
                i--;
            }
            i++;
            print = xml_cutted[i];
            QString Qprint = QString::fromStdString(print);
            ui->OUTPUT_textEdit->setPlainText(ui->OUTPUT_textEdit->toPlainText() + "The Topic (" + QWord + ") is mentioned in this post:\n" + Qprint + "\n");

        }
    }
}



void MainWindow::Network_Analysis(void)
{
    QString input_Text = ui->INPUT_textEdit->toPlainText();
    std::string XML_Text = input_Text.toUtf8().constData();
    ui->OUTPUT_textEdit->clear();

    //make map and then analize the network
    vector<string> v = TextToString(XML_Text);
    map<string, vector<string>> users;
    NetworkAnalysis(users, v);
    //to print the analysis result
    /*for (auto m : users)
    {
        cout << m.first << "  ";
        for (auto x : m.second) cout << x << " ";
        cout << endl;
    }*/

    //user with most followers
    string s = mostInfluencer(users);

    ui->OUTPUT_textEdit->setPlainText((ui->OUTPUT_textEdit->toPlainText() + "Most influencer is user who's ID is: " + QString::fromStdString(s) + " \n"));


    // most active

    s= mostActive(users);
    ui->OUTPUT_textEdit->setPlainText(ui->OUTPUT_textEdit->toPlainText() + "Most Active is user who's ID is: " + QString::fromStdString(s) + " \n");

    //  suggest followers
    string user1 = "2", user2 = "3";
    s = followerSuggest(users, user1);
    ui->OUTPUT_textEdit->setPlainText(ui->OUTPUT_textEdit->toPlainText() + "Suggested users for user 1 are users who's ID/s is/are: " + QString::fromStdString(s) + " \n");

    // mutual followers
    s = mutualFollowers(users, user1,user2);
    ui->OUTPUT_textEdit->setPlainText(ui->OUTPUT_textEdit->toPlainText() + "Mutual users between User 1 & 2 is/are :" + QString::fromStdString(s) + " \n");
}




void MainWindow::on_Network_Analysis_Button_clicked()
{
    Network_Analysis();
}


void MainWindow::on_actionCompress_XML_File_triggered()
{
    on_CompressButton_clicked();
}




void MainWindow::on_actionDecompress_XML_file_triggered()
{
    on_Decompress_PushButton_clicked();
}

