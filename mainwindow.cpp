#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QException>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QTextEdit>
#include <QTextStream>
#include <QWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    eFile = ' ';

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
        this->setWindowTitle(mainTitle + " - " + eFile);
        ui->actionClose_file->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    QString outputFileLocation;
    do
    {
    outputFileLocation = QFileDialog::getSaveFileName(this, tr("Create File"), desktop, tr("WYS files (*.wys)"));
    } while (outputFileLocation.length() == 0);
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
    this->setWindowTitle(mainTitle + " - " + eFile);
    ui->actionClose_file->setEnabled(true);
}

void MainWindow::on_actionOpen_triggered()
{

   QString name = qgetenv("USER");
       if (name.isEmpty())
           name = qgetenv("USERNAME");
   desktop = "C:\\Users\\" + name + "\\Desktop";

   QString currentFile;

   try
   {
        currentFile = QFileDialog::getOpenFileName(this, tr("Open File"), desktop, tr("WYS files (*.wys)"));
   } catch (QException e)
   {

   }

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
   this->setWindowTitle(mainTitle + " - " + eFile);
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
    }
    else
    {
        QString outputFileLocation;
        do
        {
        outputFileLocation = QFileDialog::getSaveFileName(this, tr("Save File"), desktop, tr("WYS files (*.wys)"));
        } while (outputFileLocation.length() == 0);
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
        this->setWindowTitle(mainTitle + " - " + eFile);
        ui->actionClose_file->setEnabled(true);
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString outputFileLocation;
    do
    {
    outputFileLocation = QFileDialog::getSaveFileName(this, tr("Save File"), desktop, tr("WYS files (*.wys)"));
    } while (outputFileLocation.length() == 0);
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
    this->setWindowTitle(mainTitle + " - " + eFile);
    ui->actionClose_file->setEnabled(true);
}

void MainWindow::on_actionClose_file_triggered()
{
    ui->textEdit->clear();
    this->setWindowTitle(mainTitle);
    eFile = ' ';
    ui->actionClose_file->setDisabled(true);
    alreadySaved = false;
}

void MainWindow::on_actionExir_triggered()
{
    QApplication::exit();
}

void MainWindow::on_pushButton_clicked()
{

}
