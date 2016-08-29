#ifndef UGRAMED_H
#define UGRAMED_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>

namespace Ui {
class UgraMed;
}

class UgraMed : public QMainWindow
{
    Q_OBJECT

    QSqlDatabase db;
    QSqlTableModel *dbModel;
public:
    explicit UgraMed(QWidget *parent = 0);
    ~UgraMed();

private:
    Ui::UgraMed *ui;
    bool sortOrder; //true is ascending

    void initializeWidgets();

private slots:
    void refresh();
    void open();
    void addRow();
    void deleteRow();
    void viewLog();
    void checkInserted();
    void sortColumn(int section);
    void setupTable();
};

#endif // UGRAMED_H
