#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
    ui->comboBox->setCurrentIndex(0);
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeLog(int)));
    showLog(Log::getAll());
    this->show();
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::showLog(QVector<Log::Entry *> *entries)
{
    ui->textEdit->clear();
    for (int i = 0; i < entries->count(); ++i)
    {
        ui->textEdit->setText(ui->textEdit->toPlainText().append(
                                  entries->at(i)->getTime() + "   " + entries->at(i)->getMessage() + "\n"));
    }
}

void LogWidget::changeLog(int type)
{
    switch (type)
    {
        case 0:
            showLog(Log::getAll());
            break;
        case 1:
            showLog(Log::getDatabase());
            break;
        case 2:
            showLog(Log::getUserActions());
            break;
    }
}
