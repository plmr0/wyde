#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr, QString *fontFamily = nullptr, int *fontSize = nullptr, int *fontColor = nullptr, int *backgroundColor = nullptr,
                                                    bool *isBold = nullptr, bool *isItalic = nullptr, bool *isUnderline = nullptr);
    ~SettingsForm();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_fontComboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::SettingsForm *ui;

    MainWindow mw;

    int a;

    const QString COLORS_LIST [8] = {"Black", "White", "Gray", "Red", "Green", "Blue", "Yellow", "Magenta"};

    const QString defaultFontFamily = "MS Shell Dlg 2";
    const int defaultFontSize = 8;
    const int defaultFontColor = 0;
    const int defaulBackgroundColor = 1;

    QString *currentFontFamily;
    int *currentFontSize;
    int *currentFontColor;
    int *currentBackgroundColor;
    bool *currentIsBold;
    bool *currentIsItalic;
    bool *currentIsUnderline;

    bool fontFamilyChanged = false;
    bool fontSizeChanged = false;
    bool fontColorChanged = false;
    bool backgroundColorChanged = false;
    bool isBoldChanged = false;
    bool isItalicChanged = false;
    bool isUnderlineChanged = false;

};

#endif // SETTINGSFORM_H
