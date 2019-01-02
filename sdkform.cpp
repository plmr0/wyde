#include "sdkform.h"
#include "ui_sdkform.h"

#include <QFile>
#include <QFileDialog>
#include <QBitmap>
#include <QMessageBox>
#include <QSettings>
#include <QString>

SDKForm::SDKForm(QWidget *parent, QString *py, QString *wys, QString sdkList) :
    QWidget(parent),
    ui(new Ui::SDKForm)
{
    ui->setupUi(this);

    pyPath = *py;
    wysPath = *wys;

    sdkLoc = sdkList;

    fullPyPath = pyPath + pythonT;
    fullWysPath = wysPath + wysT;

    QFile pyF(fullPyPath);
    if (pyF.exists())
    {
        pyIcon = QIcon::fromTheme(":/res/img/yes.ico");
        ui->label_3->setPixmap(pyIcon.pixmap(16,16));
    }
    else
    {
        pyIcon = QIcon::fromTheme(":/res/img/no.ico");
        ui->label_3->setPixmap(pyIcon.pixmap(16,16));
    }

    QFile wysF(fullWysPath);
    if (wysF.exists())
    {
        wysIcon = QIcon::fromTheme(":/res/img//yes.ico");
        ui->label_4->setPixmap(wysIcon.pixmap(16,16));
    }
    else
    {
        wysIcon = QIcon::fromTheme(":/res/img/no.ico");
        ui->label_4->setPixmap(wysIcon.pixmap(16,16));
    }

    ui->lineEdit->setText(*py);
    ui->lineEdit_2->setText(*wys);

    ui->lineEdit->setText(ui->lineEdit->text().replace('/','\\'));
    ui->lineEdit_2->setText(ui->lineEdit_2->text().replace('/','\\'));
}

SDKForm::~SDKForm()
{
    delete ui;
}

void SDKForm::on_pushButton_clicked()
{
   ui->lineEdit->setText(ui->lineEdit->text().replace('/','\\'));
   fullPyPath = ui->lineEdit->text() + pythonT;

    QFile pyF(fullPyPath);
    if (pyF.exists())
    {
        pyIcon = QIcon::fromTheme(":/res/img/yes.ico");
        ui->label_3->setPixmap(pyIcon.pixmap(16,16));

        for (int i = 0; i <= (fullPyPath.length() - 12); i++)
            pyPath[i] = fullPyPath[i];

        QSettings sdk(sdkLoc, QSettings::IniFormat);
        sdk.setValue("PYTHON_PATH", "");
        sdk.setValue("PYTHON_PATH", pyPath);
    }
    else
    {
        pyIcon = QIcon::fromTheme(":/res/img/no.ico");
        ui->label_3->setPixmap(pyIcon.pixmap(16,16));
    }
}

void SDKForm::on_pushButton_2_clicked()
{
    ui->lineEdit_2->setText(ui->lineEdit_2->text().replace('/','\\'));
    fullWysPath = ui->lineEdit_2->text() + wysT;

    QFile wysF(fullWysPath);
    if (wysF.exists())
    {
        wysIcon = QIcon::fromTheme(":/res/img//yes.ico");
        ui->label_4->setPixmap(wysIcon.pixmap(16,16));

        for (int i = 0; i <= (fullWysPath.length() - 8); i++)
            wysPath[i] = fullWysPath[i];

        QSettings sdk(sdkLoc, QSettings::IniFormat);
        sdk.setValue("WYS_PATH", "");
        sdk.setValue("WYS_PATH", wysPath);
    }
    else
    {
        wysIcon = QIcon::fromTheme(":/res/img/no.ico");
        ui->label_4->setPixmap(wysIcon.pixmap(16,16));
    }
}

void SDKForm::on_toolButton_clicked()
{
    QString pyDir = QFileDialog::getExistingDirectory(this, tr("Select Python Directory"), ui->lineEdit->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (pyDir.length()==0)
        return;

    ui->lineEdit->setText(pyDir);
    ui->lineEdit->setText(ui->lineEdit->text().replace('/','\\'));
    on_pushButton_clicked();
}

void SDKForm::on_toolButton_2_clicked()
{
    QString wysDir = QFileDialog::getExistingDirectory(this, tr("Select Wys Directory"), ui->lineEdit_2->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (wysDir.length()==0)
        return;

    ui->lineEdit_2->setText(wysDir);
    ui->lineEdit_2->setText(ui->lineEdit_2->text().replace('/','\\'));
    on_pushButton_2_clicked();
}
