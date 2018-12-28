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

    void on_actionClose_file_triggered();

    void on_actionExit_triggered();

    void on_actionNew_triggered();

    void on_textEdit_textChanged();

    void on_actionwyde_repository_triggered();

    void on_actionWYS_GitHub_Repository_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionProject_SDK_triggered();

private:
    Ui::MainWindow *ui;
    QString mainTitle = "WYDE - IDE for WYS";
    QString desktop;
    QStringList _arg;
    QString eFile;
    QString fullTitle;
    int action;
    bool alreadySaved = false;
    bool textChanged = false;
};

#endif // MAINWINDOW_H
