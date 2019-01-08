#include "settingsform.h"
#include "ui_settingsform.h"

#include <QMessageBox>
#include <QSettings>

SettingsForm::SettingsForm(QWidget *parent, QString *fontFamily, int *fontSize, int *fontColor, int *backgroundColor,
                                                bool *isBold, bool *isItalic, bool *isUnderline) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & (~Qt::WindowCloseButtonHint));

    currentFontFamily = fontFamily;
    currentFontSize = fontSize;
    currentFontColor = fontColor;
    currentBackgroundColor = backgroundColor;
    currentIsBold = isBold;
    currentIsItalic = isItalic;
    currentIsUnderline = isUnderline;

    // Settings values

    ui->spinBox->setValue(*fontSize);

    ui->fontComboBox->setCurrentFont(QFont(*fontFamily));

    if (ui->comboBox->findText(COLORS_LIST[*fontColor]))
        ui->comboBox->setCurrentIndex(*fontColor);

    if (ui->comboBox_2->findText(COLORS_LIST[*backgroundColor]))
        ui->comboBox_2->setCurrentIndex(*backgroundColor);

    if (*isBold)
        ui->checkBox->setCheckState(Qt::Checked);
    else
        ui->checkBox->setCheckState(Qt::Unchecked);

    if (*isItalic)
        ui->checkBox_2->setCheckState(Qt::Checked);
    else
        ui->checkBox_2->setCheckState(Qt::Unchecked);

    if (*isUnderline)
        ui->checkBox_3->setCheckState(Qt::Checked);
    else
        ui->checkBox_3->setCheckState(Qt::Unchecked);

    // QLineEdit style

    ui->lineEdit->setStyleSheet("");

    ui->lineEdit->setFont(QFont(*fontFamily));
    ui->lineEdit->setStyleSheet("color: " + COLORS_LIST[*fontColor] + ";");
    ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("font: " + QString::number(*fontSize) +"pt;"));
    ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("background-color: " + COLORS_LIST[*backgroundColor] + ";"));

    if (*isBold)
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("font-weight: bold;"));
    if (*isItalic)
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("font-style: italic;"));
    if (*isUnderline)
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("text-decoration: underline;"));

    ui->lineEdit->setCursorPosition(QTextCursor::Start);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::on_pushButton_clicked()
{
    *currentFontFamily = ui->fontComboBox->currentText();
    *currentFontSize = ui->spinBox->value();
    *currentFontColor = ui->comboBox->currentIndex();
    *currentBackgroundColor = ui->comboBox_2->currentIndex();
    *currentIsBold = ui->checkBox->isChecked();
    *currentIsItalic = ui->checkBox_2->isChecked();
    *currentIsUnderline = ui->checkBox_3->isChecked();

    QSettings editor(mw.editorList, QSettings::IniFormat);
    editor.setValue("FONT_SIZE", *currentFontSize);
    editor.setValue("FONT_FAMILY", *currentFontFamily);
    editor.setValue("FONT_COLOR", *currentFontColor);
    editor.setValue("BACKGROUND_COLOR", *currentBackgroundColor);
    editor.setValue("BOLD", *currentIsBold);
    editor.setValue("ITALIC", *currentIsItalic);
    editor.setValue("UNDERLINED", *currentIsUnderline);

    QWidget::close();

}

void SettingsForm::on_pushButton_3_clicked()
{
    a = QMessageBox::warning(this, "Set to Default", "Are You Sure?", QMessageBox::Yes, QMessageBox::No);

    if (a == 0x00004000)
    {
        ui->spinBox->setValue(defaultFontSize);
        ui->fontComboBox->setCurrentText(defaultFontFamily);
        ui->comboBox->setCurrentIndex(defaultFontColor);
        ui->comboBox_2->setCurrentIndex(defaulBackgroundColor);
        ui->checkBox->setCheckState(Qt::Unchecked);
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        ui->checkBox_3->setCheckState(Qt::Unchecked);
    }
    else
        return;
}

void SettingsForm::on_pushButton_2_clicked()
{
    if (
            (*currentFontSize != ui->spinBox->value())
         || (*currentFontFamily != ui->fontComboBox->currentText())
         || (*currentFontColor != ui->comboBox->currentIndex())
         || (*currentBackgroundColor != ui->comboBox_2->currentIndex())
         || (*currentIsBold != ui->checkBox->isChecked())
         || (*currentIsItalic != ui->checkBox_2->isChecked())
         || (*currentIsUnderline != ui->checkBox_3->isChecked())
       )
    {
        a = QMessageBox::warning(this, "Unsaved data", "Are You sure You want to leave without saving?", QMessageBox::Save, QMessageBox::Discard, QMessageBox::Cancel);

        if (a == 0x00000800)
        {
            *currentFontFamily = ui->fontComboBox->currentText();
            *currentFontSize = ui->spinBox->value();
            *currentFontColor = ui->comboBox->currentIndex();
            *currentBackgroundColor = ui->comboBox_2->currentIndex();
            *currentIsBold = ui->checkBox->isChecked();
            *currentIsItalic = ui->checkBox_2->isChecked();
            *currentIsUnderline = ui->checkBox_3->isChecked();

            QSettings editor(mw.editorList, QSettings::IniFormat);
            editor.setValue("FONT_SIZE", *currentFontSize);
            editor.setValue("FONT_FAMILY", *currentFontFamily);
            editor.setValue("FONT_COLOR", *currentFontColor);
            editor.setValue("BACKGROUND_COLOR", *currentBackgroundColor);
            editor.setValue("BOLD", *currentIsBold);
            editor.setValue("ITALIC", *currentIsItalic);
            editor.setValue("UNDERLINED", *currentIsUnderline);

            QWidget::close();
        }
        else if (a == 0x00800000)
        {
            QWidget::close();
        }
        else
            return;
    }
    else
        QWidget::close();
}

void SettingsForm::on_pushButton_4_clicked()
{
    *currentFontFamily = ui->fontComboBox->currentText();
    *currentFontSize = ui->spinBox->value();
    *currentFontColor = ui->comboBox->currentIndex();
    *currentBackgroundColor = ui->comboBox_2->currentIndex();
    *currentIsBold = ui->checkBox->isChecked();
    *currentIsItalic = ui->checkBox_2->isChecked();
    *currentIsUnderline = ui->checkBox_3->isChecked();

    QSettings editor(mw.editorList, QSettings::IniFormat);
    editor.setValue("FONT_SIZE", *currentFontSize);
    editor.setValue("FONT_FAMILY", *currentFontFamily);
    editor.setValue("FONT_COLOR", *currentFontColor);
    editor.setValue("BACKGROUND_COLOR", *currentBackgroundColor);
    editor.setValue("BOLD", *currentIsBold);
    editor.setValue("ITALIC", *currentIsItalic);
    editor.setValue("UNDERLINED", *currentIsUnderline);
}

void SettingsForm::on_spinBox_valueChanged(int arg1)
{
    ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("font: " + QString::number(arg1) +"pt;"));
}

void SettingsForm::on_fontComboBox_currentTextChanged(const QString &arg1)
{
    ui->lineEdit->setFont(QFont(arg1, ui->spinBox->value()));
}

void SettingsForm::on_comboBox_currentIndexChanged(int index)
{
    ui->lineEdit->setStyleSheet("color: " + COLORS_LIST[index] + ";");
    ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("background-color: " + COLORS_LIST[ui->comboBox_2->currentIndex()] + ";"));
}

void SettingsForm::on_comboBox_2_currentIndexChanged(int index)
{
    ui->lineEdit->setStyleSheet("color: " + COLORS_LIST[ui->comboBox->currentIndex()] + ";");
    ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("background-color: " + COLORS_LIST[index] + ";"));
}

void SettingsForm::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("font-weight: bold;"));
    else
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("font-weight: normal;"));
}

void SettingsForm::on_checkBox_2_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("font-style: italic;"));
    else
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("font-style: normal;"));
}

void SettingsForm::on_checkBox_3_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("text-decoration: underline;"));
    else
        ui->lineEdit->setStyleSheet(ui->lineEdit->styleSheet().append("text-decoration: none;"));
}
