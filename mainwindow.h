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

    QString setList;
    QString editorList;

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

    void on_actionWYDE_repository_triggered();

    void on_actionWYS_GitHub_Repository_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionIDE_Settings_triggered();

    void on_actionProject_SDK_triggered();

    void on_actionPaste_triggered();

    void on_actionCopy_triggered();

    void on_actionSelect_All_triggered();

    void on_actionCut_triggered();

    void on_actionLarger_triggered();

    void on_actionSmaller_triggered();

    void on_actionReset_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QString mainTitle = "WYDE - IDE for WYS";

    QString desktop;
    QString wydeF;
    QString sdkList;

    QStringList _args;

    QString eFile;
    QString fullTitle;

    QString PYTHON_PATH;
    QString WYS_PATH;

    /* Editor variables */

    const QString _COLORS [8] = {"Black", "White", "Gray", "Red", "Green", "Blue", "Yellow", "Magenta"};
    int FONT_COLOR = 0;
    int BACKGROUND_COLOR = 1;

    QString FONT_FAMILY;
    int FONT_SIZE = 8;

    bool isBold = false;
    bool isItalic = false;
    bool isUnderline = false;

    /* ---------------- */

    int action;

    bool alreadySaved = false;
    bool textChanged = false;
};

#endif // MAINWINDOW_H
