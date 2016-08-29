#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <log.h>

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();

private:
    Ui::LogWidget *ui;

    void showLog(QVector<Log::Entry*> *entries);

private slots:
    void changeLog(int type);
};

#endif // LOGWIDGET_H
