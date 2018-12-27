#include "sdkform.h"
#include "ui_sdkform.h"

SDKForm::SDKForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SDKForm)
{
    ui->setupUi(this);
}

SDKForm::~SDKForm()
{
    delete ui;
}
