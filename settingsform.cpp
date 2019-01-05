#include "settingsform.h"
#include "ui_settingsform.h"

#include <QMessageBox>
#include <QSettings>

SettingsForm::SettingsForm(QWidget *parent, QString *fontFamily, int *fontSize, int *fontColor,
                                                bool *isBold, bool *isItalic, bool *isUnderline) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & (~Qt::WindowCloseButtonHint));

    currentFontFamily = fontFamily;
    currentFontSize = fontSize;
    currentFontColor = fontColor;
    currentIsBold = isBold;
    currentIsItalic = isItalic;
    currentIsUnderline = isUnderline;

    ui->spinBox->setValue(*fontSize);

    ui->fontComboBox->setCurrentFont(QFont(*fontFamily));

    if (ui->comboBox->findText(COLORS_LIST[*fontColor]))
        ui->comboBox->setCurrentIndex(*fontColor);

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
    *currentIsBold = ui->checkBox->isChecked();
    *currentIsItalic = ui->checkBox_2->isChecked();
    *currentIsUnderline = ui->checkBox_3->isChecked();

    QSettings editor(mw.editorList, QSettings::IniFormat);
    editor.setValue("FONT_SIZE", *currentFontSize);
    editor.setValue("FONT_FAMILY", *currentFontFamily);
    editor.setValue("FONT_COLOR", *currentFontColor);
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
            *currentIsBold = ui->checkBox->isChecked();
            *currentIsItalic = ui->checkBox_2->isChecked();
            *currentIsUnderline = ui->checkBox_3->isChecked();

            QSettings editor(mw.editorList, QSettings::IniFormat);
            editor.setValue("FONT_SIZE", *currentFontSize);
            editor.setValue("FONT_FAMILY", *currentFontFamily);
            editor.setValue("FONT_COLOR", *currentFontColor);
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
