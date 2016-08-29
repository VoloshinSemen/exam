#include "ugramed.h"
#include "ui_ugramed.h"

#include <QSql>
#include <QSqlDriver>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <log.h>
#include <logwidget.h>

UgraMed::UgraMed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UgraMed)
{
    ui->setupUi(this);
    this->initializeWidgets();
}

UgraMed::~UgraMed()
{
    delete ui;
    Log::destructLog();
}

void UgraMed::initializeWidgets()
{
    Log::initLog(ui->logLabel);
    sortOrder = false;

    db = QSqlDatabase::addDatabase("QSQLITE");
    QDir dir(QDir::current());
    dir.cdUp();
    db.setDatabaseName(dir.path() + "/UgraMed.db");
    Log::ua("Открыта " + dir.path() + "UgraMed.db");
    if (!db.open())
        Log::db("Не удалось найти базу. Укажите путь вручную");

    dbModel = new QSqlTableModel(0, db);
    dbModel->setTable("myTable");
    dbModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    dbModel->select();

    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(dbModel);
    ui->tableView->setModel(sortModel);
    setupTable();

    QObject::connect(ui->refreshButton, SIGNAL(clicked(bool)),
                     this, SLOT(refresh()));
    QObject::connect(ui->openButton, SIGNAL(clicked(bool)),
                     this, SLOT(open()));
    QObject::connect(ui->addRowButton, SIGNAL(clicked(bool)),
                     this, SLOT(addRow()));
    QObject::connect(ui->deleteRowButton, SIGNAL(clicked(bool)),
                     this, SLOT(deleteRow()));
    QObject::connect(ui->logButton, SIGNAL(clicked(bool)),
                     this, SLOT(viewLog()));
    QObject::connect(dbModel, SIGNAL(rowsInserted(QModelIndex,int,int)),
                     this, SLOT(checkInserted()));
    QObject::connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)),
                     this, SLOT(sortColumn(int)));
}

void UgraMed::refresh()
{
    dbModel->select();
}

void UgraMed::open()
{
    QString dbFile = QFileDialog::getOpenFileName(this, "Open", "",
                                                  "*.db *.sqlite *.db3 *.sqlite3");
    if (dbFile.isNull())
    {
        Log::ua("Открытие базы отменено");
        return;
    }
    db.close();
    db.addDatabase("QSQLITE", dbFile);
    db.setDatabaseName(dbFile);
    if (!db.open())
    {
        Log::db(db.lastError().text());
        return;
    }
    dbModel->setTable("myTable");
    dbModel->select();
    setupTable();
}

void UgraMed::addRow()
{
    ui->tableView->model()->insertRow((ui->tableView->model()->rowCount()));
}

void UgraMed::deleteRow()
{
    if (ui->tableView->selectionModel()->selectedIndexes().isEmpty())
    {
        Log::ua("Не выбрана запись для удаления");
        return;
    }
    if (!dbModel->removeRow(ui->tableView->selectionModel()->selectedIndexes().first().row()))
    {
        Log::db(db.lastError().text());
        Log::db(dbModel->lastError().text());
    }
    refresh();
}

void UgraMed::checkInserted()
{
    if (dbModel->lastError().isValid())
        Log::db(dbModel->lastError().text());
}

void UgraMed::sortColumn(int section)
{
    ui->tableView->sortByColumn(section, sortOrder ? Qt::DescendingOrder : Qt::AscendingOrder);
    ui->tableView->horizontalHeader()->setSortIndicator(section, sortOrder ? Qt::DescendingOrder : Qt::AscendingOrder);
    ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
    sortOrder = !sortOrder;
}

void UgraMed::viewLog()
{
    new LogWidget();
}

void UgraMed::setupTable()
{
    dbModel->setHeaderData(1, Qt::Horizontal, "a");
    dbModel->setHeaderData(2, Qt::Horizontal, "b");
    dbModel->setHeaderData(3, Qt::Horizontal, "c");

    const int columnWidth = (ui->tableView->width() - 1) / 3.0;
    ui->tableView->setColumnWidth(1, columnWidth);
    ui->tableView->setColumnWidth(2, columnWidth);
    ui->tableView->setColumnWidth(3, columnWidth);

    ui->tableView->verticalHeader()->hide();
    ui->tableView->hideColumn(0);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}
