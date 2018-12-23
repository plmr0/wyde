#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QFile>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _arg = QCoreApplication::arguments();

    if (_arg.length() > 1 && _arg.length() == 2) {

        QString _line;
        QFile _inputFile(_arg.at(1));

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

   QString currentFile;
   currentFile = QFileDialog::getOpenFileName(this,
          tr("Open File"), "C:\\Users\\" + name + "\\Desktop", tr("WYS files (*.wys)"));

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
