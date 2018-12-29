#ifndef SDKFORM_H
#define SDKFORM_H

#include <QWidget>

namespace Ui {
class SDKForm;
}

class SDKForm : public QWidget
{
    Q_OBJECT

public:
    explicit SDKForm(QWidget *parent = nullptr, QString *py = nullptr, QString *wys = nullptr);
    ~SDKForm();

private:
    Ui::SDKForm *ui;
    QString pyPath;
    QString fullPyPath;
    QString wysPath;
    QString fullWysPath;
};

#endif // SDKFORM_H
