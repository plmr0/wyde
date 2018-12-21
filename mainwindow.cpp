#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
   current_file = QFileDialog::getOpenFileName(this,
          tr("Open File"), "C:\\Users\\Ilya\\Desktop\\wys", tr("WYS files (*.wys)"));

   QString line;
   QFile inputFile(current_file);

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
