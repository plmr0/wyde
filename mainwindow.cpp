#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sdkform.h"

#include <QDesktopServices>
#include <QException>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QStringList>
#include <QTextEdit>
#include <QTextStream>
#include <QWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMainWindow::setAttribute(Qt::WA_ShowModal);

    eFile = ' ';

    QString name = qgetenv("USER"); // Getting %username%
        if (name.isEmpty())
            name = qgetenv("USERNAME");

    desktop = "C:\\Users\\" + name + "\\Desktop";
    sdkList = "C:\\Users\\" + name + "\\Documents\\wyde\\wyde_sdk.ini";

    /* INI-File reading */

    QSettings sdk(sdkList, QSettings::IniFormat);
    PYTHON_PATH = sdk.value("PYTHON_PATH", "").toString();
    WYS_PATH = sdk.value("WYS_PATH", "").toString();

    QFile pythP(PYTHON_PATH + "\\python.exe");
    QFile wysP(WYS_PATH + "\\wys.py");

    if (!pythP.exists())
        setList = "Python";
    if (!wysP.exists())
    {
        if (setList.length() > 0)
            setList = setList + " and WYS";
        else
            setList = "WYS";
    }

    if (setList.length() > 0)
        QMessageBox::warning(this, "No SDK found", setList + " directory ain\'t found.\nPlease go to \"Settings\" -> \"Project SDK\" to setup " + setList + " directory.");

    /* ---------------- */

    /* Getting Application Arguments */

    // Also setting default window title

    _arg = QCoreApplication::arguments();

    if (_arg.length() > 1 && _arg.length() == 2)
    {
        QString _line;
        QFile _inputFile(_arg.at(1));
        eFile = _arg.at(1);

        if (_inputFile.open(QIODevice::ReadOnly))
        {
           while (!_inputFile.atEnd())
           {
              _line = _inputFile.readLine();
              ui->textEdit->insertPlainText(_line);
           }
           _inputFile.close();
        }
        alreadySaved = true;
        eFile = _arg.at(1);
        fullTitle = mainTitle + " - " + eFile;
        this->setWindowTitle(fullTitle);
        textChanged = false;
        ui->actionClose_file->setEnabled(true);
    }

    /* ----------------------------- */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    QString outputFileLocation = QFileDialog::getSaveFileName(this, tr("Create File"), desktop, tr("WYS files (*.wys)"));
    if (outputFileLocation.length() == 0)
        return;
    QFile f(outputFileLocation);
    f.open( QIODevice::WriteOnly );
    f.close();
    eFile = outputFileLocation;
    QString str = ui->textEdit->toPlainText();
    QStringList strList = str.split('\n');
    QFile file(eFile);
    if (file.open(QIODevice::WriteOnly))
    {
        int i = 0;
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        while (true) {
            stream << strList.at(i) + "\n";
            i++;
            if (i==strList.size()) break;
        }
    }
    eFile = outputFileLocation;
    alreadySaved = true;
    fullTitle = mainTitle + " - " + eFile;
    this->setWindowTitle(fullTitle);
    textChanged = false;
    ui->actionClose_file->setEnabled(true);
}

void MainWindow::on_actionOpen_triggered()
{
   textChanged = false;

   QString currentFile = QFileDialog::getOpenFileName(this, tr("Open File"), desktop, tr("WYS files (*.wys)"));
   if (currentFile.length() == 0)
       return;

   QString line;
   QFile inputFile(currentFile);

   if (inputFile.open(QIODevice::ReadOnly))
   {
      while (!inputFile.atEnd())
      {
         line = inputFile.readLine();
         ui->textEdit->insertPlainText(line);
      }
      inputFile.close();
   }

   alreadySaved = true;
   eFile = currentFile;
   fullTitle = mainTitle + " - " + eFile;
   this->setWindowTitle(fullTitle);
   textChanged = false;
   ui->actionClose_file->setEnabled(true);

}

void MainWindow::on_actionSave_triggered()
{
    if (alreadySaved)
    {
        QString str = ui->textEdit->toPlainText();
        QStringList strList = str.split('\n');
        QFile file(eFile);
        if (file.open(QIODevice::WriteOnly))
        {
            int i = 0;
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            while (true)
            {
                stream << strList.at(i) + "\n";
                i++;
                if (i==strList.size()) break;
            }
        }
        fullTitle = mainTitle + " - " + eFile;
        textChanged = false;
        this->setWindowTitle(fullTitle);
    }
    else
    {
        QString outputFileLocation = QFileDialog::getSaveFileName(this, tr("Create File"), desktop, tr("WYS files (*.wys)"));
        if (outputFileLocation.length() == 0)
            return;
        QFile f(outputFileLocation);
        f.open( QIODevice::WriteOnly );
        f.close();
        eFile = outputFileLocation;
        QString str = ui->textEdit->toPlainText();
        QStringList strList = str.split('\n');
        QFile file(eFile);
        if (file.open(QIODevice::WriteOnly))
        {
            int i = 0;
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            while (true) {
                stream << strList.at(i) + "\n";
                i++;
                if (i==strList.size()) break;
            }
        }
        eFile = outputFileLocation;
        alreadySaved = true;
        fullTitle = mainTitle + " - " + eFile;
        this->setWindowTitle(fullTitle);
        textChanged = false;
        ui->actionClose_file->setEnabled(true);
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString outputFileLocation = QFileDialog::getSaveFileName(this, tr("Create File"), desktop, tr("WYS files (*.wys)"));
    if (outputFileLocation.length() == 0)
        return;
    QFile f(outputFileLocation);
    f.open( QIODevice::WriteOnly );
    f.close();
    eFile = outputFileLocation;
    QString str = ui->textEdit->toPlainText();
    QStringList strList = str.split('\n');
    QFile file(eFile);
    if (file.open(QIODevice::WriteOnly))
    {
        int i = 0;
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        while (true) {
            stream << strList.at(i) + "\n";
            i++;
            if (i==strList.size()) break;
        }
    }
    eFile = outputFileLocation;
    alreadySaved = true;
    fullTitle = mainTitle + " - " + eFile;
    this->setWindowTitle(fullTitle);
    textChanged = false;
    ui->actionClose_file->setEnabled(true);
}

void MainWindow::on_actionClose_file_triggered()
{
    if (textChanged)
    {
        action = QMessageBox::warning(this, "Unsaved changes", "You didn\'t save the file.\nDo You want to save it?", QMessageBox::Save, QMessageBox::Discard, QMessageBox::Close);
        if (action == 0x00000800)
        {
            on_actionSave_triggered();
        }
        else if (action == 0x00800000)
        {

        }
        else return;
    }
    ui->textEdit->clear();
    this->setWindowTitle(mainTitle);
    eFile = ' ';
    ui->actionClose_file->setDisabled(true);
    alreadySaved = false;
    textChanged = false;
    fullTitle = mainTitle;
}

void MainWindow::on_actionExit_triggered()
{
    if (textChanged)
    {
        action = QMessageBox::warning(this, "Unsaved changes", "You didn\'t save the file.\nDo You want to save it?", QMessageBox::Save, QMessageBox::Discard, QMessageBox::Close);
        if (action == 0x00000800)
        {
            on_actionSave_triggered();
            QApplication::exit();
        }
        else if (action == 0x00800000)
        {
            QApplication::exit();
        }
        else return;
    }
    else
        QApplication::exit();
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_textEdit_textChanged()
{
    textChanged = true;
    if (fullTitle.length() < 1)
        fullTitle = mainTitle + " - " + "unnamed";
    this->setWindowTitle(fullTitle + " *");
}

void MainWindow::on_actionProject_SDK_triggered()
{
    SDKForm *w = new SDKForm(nullptr, &PYTHON_PATH, &WYS_PATH, sdkList);
    w->show();
    w->setFocus();
}

void MainWindow::on_actionWYDE_repository_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/plmr0/wyde"));
}

void MainWindow::on_actionWYS_GitHub_Repository_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/mutedSpectre/wys"));
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}
