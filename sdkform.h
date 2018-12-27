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
    explicit SDKForm(QWidget *parent = nullptr);
    ~SDKForm();

private:
    Ui::SDKForm *ui;
};

#endif // SDKFORM_H
