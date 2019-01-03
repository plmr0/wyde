#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm::SettingsForm(QWidget *parent, QString fontFamily, int fontSize, int fontColor,
                                                bool isBold, bool isItalic, bool isUnderlined) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}
