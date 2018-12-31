#ifndef SDKFORM_H
#define SDKFORM_H

#include <QIcon>
#include <QWidget>

namespace Ui {
class SDKForm;
}

class SDKForm : public QWidget
{
    Q_OBJECT

public:
    explicit SDKForm(QWidget *parent = nullptr, QString *py = nullptr, QString *wys = nullptr, QString sdkList = "");
    ~SDKForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::SDKForm *ui;
    QString pyPath;
    QString fullPyPath;
    QString wysPath;
    QString fullWysPath;
    QString pythonT = "\\python.exe";
    QString wysT = "\\wys.py";
    QIcon pyIcon;
    QIcon wysIcon;
    QString sdkLoc;
};

#endif // SDKFORM_H
