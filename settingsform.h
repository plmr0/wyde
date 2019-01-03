#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr, QString fontFamily = "Monospace", int fontSize = 8, int fontColor = 0,
                                                    bool isBold = false, bool isItalic = false, bool isUnderlined = false);
    ~SettingsForm();

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
