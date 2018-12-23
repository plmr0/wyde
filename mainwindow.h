#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

private:
    Ui::MainWindow *ui;
    QString mainTitle = "WYDE - IDE for WYS";
    QString desktop;
    QStringList _arg;
    QString eFile;
    bool alreadySaved = false;
};

#endif // MAINWINDOW_H
