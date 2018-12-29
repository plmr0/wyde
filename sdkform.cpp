#include "sdkform.h"
#include "ui_sdkform.h"

#include <QFile>
#include <QBitmap>
#include <QMessageBox>
#include <QString>

SDKForm::SDKForm(QWidget *parent, QString *py, QString *wys) :
    QWidget(parent),
    ui(new Ui::SDKForm)
{
    ui->setupUi(this);

    pyPath = *py;
    wysPath = *wys;

    /*

    fullPyPath = pyPath + "\\python.exe";
    fullWysPath = wysPath + "\\wys.py";

    QIcon pyIcon;
    QIcon wysIcon;

    QFile pyF(fullPyPath);
    if (pyF.exists())
    {
        QMessageBox::warning(this,"gay","yes py");
        pyIcon = QIcon::fromTheme(":/res/img/yes.ico");
        ui->label_3->setPixmap(pyIcon.pixmap(16,16));
    }
    else
    {
        QMessageBox::warning(this,"gay","no py");
        pyIcon = QIcon::fromTheme(":/res/img/no.ico");
        ui->label_3->setPixmap(pyIcon.pixmap(16,16));
    }

    QFile wysF(fullWysPath);
    if (wysF.exists())
    {
        QMessageBox::warning(this,"gay","yes wys");
        wysIcon = QIcon::fromTheme(":/res/img//es.ico");
        ui->label_3->setPixmap(wysIcon.pixmap(16,16));
    }
    else
    {
        QMessageBox::warning(this,"gay","no wys");
        wysIcon = QIcon::fromTheme(":/res/img/no.ico");
        ui->label_3->setPixmap(wysIcon.pixmap(16,16));
    }

    */

    ui->lineEdit->setText(*py);
    ui->lineEdit_2->setText(*wys);
}

SDKForm::~SDKForm()
{
    delete ui;
}
