#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QException>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QFile>
#include <QStringList>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _arg = QCoreApplication::arguments();

    if (_arg.length() > 1 && _arg.length() == 2) {

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

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_actionOpen_triggered()
{

   QString name = qgetenv("USER");
       if (name.isEmpty())
           name = qgetenv("USERNAME");
   desktop = "C:\\Users\\" + name + "\\Desktop";

   QString currentFile;

   try {
       currentFile = QFileDialog::getOpenFileName(this, tr("Open File"), desktop, tr("WYS files (*.wys)"));
   } catch (QException e) {

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

}

void MainWindow::on_actionSave_triggered()
{
    if (alreadySaved) {
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
    }
    else {
        QString outputFileLocation = QFileDialog::getSaveFileName(this, tr("Save File"), desktop, tr("WYS files (*.wys)"));
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
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString outputFileLocation = QFileDialog::getSaveFileName(this, tr("Save File"), desktop, tr("WYS files (*.wys)"));
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
}
