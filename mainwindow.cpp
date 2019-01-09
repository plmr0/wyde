#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sdkform.h"
#include "settingsform.h"

#include <QCloseEvent>
#include <QDateTime>
#include <QDesktopServices>
#include <QException>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
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

    eFile = ' '; // default file name

    QString name = qgetenv("USER"); // Getting %username%
        if (name.isEmpty())
            name = qgetenv("USERNAME");

    // list of paths

    desktop = "C:\\Users\\" + name + "\\Desktop";
    sdkList = "C:\\Users\\" + name + "\\Documents\\wyde\\wyde_sdk.ini";
    editorList = "C:\\Users\\" + name + "\\Documents\\wyde\\wyde_editor.ini";

    /* INI-File reading */

    QSettings sdk(sdkList, QSettings::IniFormat);
    QSettings editor(editorList, QSettings::IniFormat);

    QFile iniFileSDK(sdkList);
    if (!iniFileSDK.exists())
    {
        sdk.setValue("PYTHON_PATH", "");
        sdk.setValue("WYS_PATH", "");
    }

    QFile iniFileEditor(editorList);
    if (!iniFileEditor.exists())
    {
        editor.setValue("FONT_SIZE", 8);
        editor.setValue("FONT_FAMILY", "MS Shell Dlg 2");
        editor.setValue("FONT_COLOR", 0);
        editor.setValue("BACKGROUND_COLOR", 1);
        editor.setValue("BOLD", "FALSE");
        editor.setValue("ITALIC", "FALSE");
        editor.setValue("UNDERLINED", "FALSE");

    }

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

    FONT_SIZE = editor.value("FONT_SIZE", "").toInt();
    FONT_FAMILY = editor.value("FONT_FAMILY", "").toString();
    FONT_COLOR = editor.value("FONT_COLOR", "").toInt();
    BACKGROUND_COLOR = editor.value("BACKGROUND_COLOR", "").toInt();
    isBold = editor.value("BOLD", "").toBool();
    isItalic = editor.value("ITALIC", "").toBool();
    isUnderline = editor.value("UNDERLINED", "").toBool();

    if (!(FONT_SIZE >1 && FONT_SIZE < 73))
    {
        FONT_SIZE = 8;
        editor.setValue("FONT_SIZE", FONT_SIZE);
    }

    if (!(FONT_COLOR >= 0 && FONT_COLOR < 8))
    {
        FONT_COLOR = 0;
        editor.setValue("FONT_COLOR", FONT_COLOR);
    }

    if (!(BACKGROUND_COLOR >= 0 && BACKGROUND_COLOR < 8))
    {
        BACKGROUND_COLOR = 1;
        editor.setValue("BACKGROUND_COLOR", BACKGROUND_COLOR);
    }

    ui->textEdit->setFontFamily(FONT_FAMILY);
    ui->textEdit->setStyleSheet("color: " + _COLORS[FONT_COLOR] + ";");
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font: " + QString::number(FONT_SIZE) +"pt;"));
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("background-color: " + _COLORS[BACKGROUND_COLOR] + ";"));

    if (isBold)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-weight: bold;"));
    if (isItalic)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-style: italic;"));
    if (isUnderline)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("text-decoration: underline;"));

    /* ---------------- */

    /* Getting Application Arguments */

    // Also setting default window title

    _args = QCoreApplication::arguments();

    if (_args.length() > 1 && _args.length() == 2)
    {
        QString _line;
        QFile _inputFile(_args.at(1));
        eFile = _args.at(1);

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
        eFile = _args.at(1);
        eFile = eFile.replace('/','\\');
        fullTitle = mainTitle + " - " + eFile;
        this->setWindowTitle(fullTitle);
        textChanged = false;
        ui->actionClose_file->setEnabled(true);

        ui->textEdit->moveCursor(QTextCursor::Start);
    }

    /* ----------------------------- */

    // Initial log

    ui->textBrowser->insertPlainText("[" + QTime::currentTime().toString() + "] " + "IDE launched.\n");
    if (setList.length() == 0)
        ui->textBrowser->insertPlainText("[" + QTime::currentTime().toString() + "] " + "Python and WYS successully loaded.\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (textChanged)
    {
        action = QMessageBox::warning(this, "Unsaved changes", "You didn\'t save the file.\nDo You want to save it?", QMessageBox::Save, QMessageBox::Discard, QMessageBox::Cancel);
        if (action == 0x00000800)
        {
            on_actionSave_triggered();
            event->accept();
        }
        else if (action == 0x00800000)
            event->accept();
        else
            event->ignore();
    }
    else
        event->accept();
}

void MainWindow::on_actionNew_triggered()
{
    if (textChanged)
    {
        action = QMessageBox::warning(this, "Unsaved changes", "You didn\'t save the file.\nDo You want to save it?", QMessageBox::Save, QMessageBox::Discard, QMessageBox::Cancel);
        if (action == 0x00000800)
        {
            on_actionSave_triggered();
        }
        else if (action == 0x00800000) {}
        else return;
    }

    QString outputFileLocation = QFileDialog::getSaveFileName(this, tr("Create File"), desktop, tr("WYS files (*.wys)"));
    if (outputFileLocation.length() == 0)
        return;

    if ((ui->textEdit->toPlainText()).length() > 0)
        ui->textEdit->clear();

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
    eFile = eFile.replace('/','\\');
    alreadySaved = true;
    fullTitle = mainTitle + " - " + eFile;
    this->setWindowTitle(fullTitle);
    textChanged = false;
    ui->actionClose_file->setEnabled(true);

    ui->textEdit->moveCursor(QTextCursor::Start);
}

void MainWindow::on_actionOpen_triggered()
{
    ui->textEdit->setFontFamily(FONT_FAMILY);
    ui->textEdit->setStyleSheet("color: " + _COLORS[FONT_COLOR] + ";");
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font: " + QString::number(FONT_SIZE) +"pt;"));
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("background-color: " + _COLORS[BACKGROUND_COLOR] + ";"));

    if (isBold)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-weight: bold;"));
    if (isItalic)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-style: italic;"));
    if (isUnderline)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("text-decoration: underline;"));

    if (textChanged)
    {
        action = QMessageBox::warning(this, "Unsaved changes", "You didn\'t save the current file.\nDo You want to save it?", QMessageBox::Save, QMessageBox::Discard, QMessageBox::Cancel);
        if (action == 0x00000800)
        {
            on_actionSave_triggered();
        }
        else if (action == 0x00800000) {}
        else return;
    }

    textChanged = false;

    QString currentFile = QFileDialog::getOpenFileName(this, tr("Open File"), desktop, tr("WYS files (*.wys)"));
    if (currentFile.length() == 0)
        return;

    if ((ui->textEdit->toPlainText()).length() > 0)
        ui->textEdit->clear();

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
     eFile = eFile.replace('/','\\');
     fullTitle = mainTitle + " - " + eFile;
     this->setWindowTitle(fullTitle);
     textChanged = false;
     ui->actionClose_file->setEnabled(true);

     ui->textEdit->moveCursor(QTextCursor::Start);
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
        this->on_actionSave_as_triggered();
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
    eFile = eFile.replace('/','\\');
    alreadySaved = true;
    fullTitle = mainTitle + " - " + eFile;
    this->setWindowTitle(fullTitle);
    textChanged = false;
    ui->actionClose_file->setEnabled(true);
}

void MainWindow::on_actionClose_file_triggered()
{
    ui->textEdit->setFontFamily(FONT_FAMILY);
    ui->textEdit->setStyleSheet("color: " + _COLORS[FONT_COLOR] + ";");
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font: " + QString::number(FONT_SIZE) +"pt;"));
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("background-color: " + _COLORS[BACKGROUND_COLOR] + ";"));

    if (isBold)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-weight: bold;"));
    if (isItalic)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-style: italic;"));
    if (isUnderline)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("text-decoration: underline;"));

    if (textChanged)
    {
        action = QMessageBox::warning(this, "Unsaved changes", "You didn\'t save the file.\nDo You want to save it?", QMessageBox::Save, QMessageBox::Discard, QMessageBox::Cancel);
        if (action == 0x00000800)
        {
            on_actionSave_triggered();
        }
        else if (action == 0x00800000){}
        else return;
    }
    ui->textEdit->clear();
    this->setWindowTitle(mainTitle);
    eFile = ' ';
    ui->actionClose_file->setDisabled(true);
    alreadySaved = false;
    textChanged = false;
    fullTitle = mainTitle;

    ui->textEdit->moveCursor(QTextCursor::Start);
}

void MainWindow::on_actionExit_triggered()
{
    if (textChanged)
    {
        action = QMessageBox::warning(this, "Unsaved changes", "You didn\'t save the file.\nDo You want to save it?", QMessageBox::Save, QMessageBox::Discard, QMessageBox::Cancel);
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
    if (fullTitle.length() < 1 || fullTitle == "WYDE - IDE for WYS")
        fullTitle = mainTitle + " - " + "unnamed";
    this->setWindowTitle(fullTitle + " *");

    if (ui->textEdit->toPlainText().length() == 0)
        ui->textEdit->setFontFamily(FONT_FAMILY);
}

void MainWindow::on_actionIDE_Settings_triggered()
{
    bool beforeChanged = (textChanged) ? true : false;

    QString fullText = ui->textEdit->toPlainText();

    SettingsForm *w = new SettingsForm(nullptr, &FONT_FAMILY, &FONT_SIZE, &FONT_COLOR, &BACKGROUND_COLOR, &isBold, &isItalic, &isUnderline);
    w->show();
    w->setFocus();
    w->setAttribute(Qt::WA_DeleteOnClose);

    // This loop will wait for the window is destroyed
    QEventLoop loop;
    connect(w, SIGNAL(destroyed()), & loop, SLOT(quit()));
    loop.exec();

    ui->textEdit->clear();

    ui->textEdit->setFontFamily(FONT_FAMILY);

    ui->textEdit->setStyleSheet("color: " + _COLORS[FONT_COLOR] + ";");
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font: " + QString::number(FONT_SIZE) +"pt;"));
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("background-color: " + _COLORS[BACKGROUND_COLOR] + ";"));

    if (isBold)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-weight: bold;"));
    if (isItalic)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-style: italic;"));
    if (isUnderline)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("text-decoration: underline;"));

    ui->textEdit->insertPlainText(fullText);
    ui->textEdit->moveCursor(QTextCursor::Start);
    if ((fullText == ui->textEdit->toPlainText()) && (textChanged == true) && (beforeChanged == false))
    {
        if (fullTitle == (mainTitle + " - unnamed"))
            fullTitle = mainTitle;
        else
            fullTitle = mainTitle + " - " + eFile;
        textChanged = false;
        this->setWindowTitle(fullTitle);
    }
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

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionLarger_triggered()
{
    ui->textEdit->setStyleSheet("font: " + QString::number(++FONT_SIZE) +"pt;");

    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("color: " + _COLORS[FONT_COLOR] + ";"));
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("background-color: " + _COLORS[BACKGROUND_COLOR] + ";"));

    if (isBold)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-weight: bold;"));
    if (isItalic)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-style: italic;"));
    if (isUnderline)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("text-decoration: underline;"));

    QSettings editor(editorList, QSettings::IniFormat);
    editor.setValue("FONT_SIZE", FONT_SIZE);
}

void MainWindow::on_actionSmaller_triggered()
{
    ui->textEdit->setStyleSheet("font: " + QString::number(--FONT_SIZE) +"pt;");

    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("color: " + _COLORS[FONT_COLOR] + ";"));
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("background-color: " + _COLORS[BACKGROUND_COLOR] + ";"));

    if (isBold)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-weight: bold;"));
    if (isItalic)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-style: italic;"));
    if (isUnderline)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("text-decoration: underline;"));

    QSettings editor(editorList, QSettings::IniFormat);
    editor.setValue("FONT_SIZE", FONT_SIZE);
}

void MainWindow::on_actionReset_triggered()
{
    ui->textEdit->setStyleSheet("font: 8pt;");

    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("color: " + _COLORS[FONT_COLOR] + ";"));
    ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("background-color: " + _COLORS[BACKGROUND_COLOR] + ";"));

    if (isBold)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-weight: bold;"));
    if (isItalic)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("font-style: italic;"));
    if (isUnderline)
        ui->textEdit->setStyleSheet(ui->textEdit->styleSheet().append("text-decoration: underline;"));

    QSettings editor(editorList, QSettings::IniFormat);
    editor.setValue("FONT_SIZE", 8);
}
