#include "log.h"


QVector<Log::Entry*> *Log::entries;
QLabel *Log::output;

Log::Entry::Entry(type action, QString message)
{
    time = QDateTime::currentDateTime();
    this->action = action;
    this->message = message;
}

void Log::ua(QString message)
{
    entries->append(new Entry(Log::USERACTION, message));
    output->setText(message);
}

void Log::db(QString message)
{
    entries->append(new Entry(Log::DATABASE, message));
    output->setText(message);
}

void Log::initLog(QLabel *output)
{
    Log::output = output;
    entries = new QVector<Entry*>();
}

QVector<Log::Entry*>* Log::getAll()
{
    return entries;
}

QVector<Log::Entry*>* Log::getDatabase()
{
    QVector<Log::Entry*>* retEntries = new QVector<Log::Entry*>();
    for (int i = 0; i < entries->count(); ++i)
    {
        if (entries->at(i)->getAction() == DATABASE)
                retEntries->append(new Entry(*entries->at(i)));
    }
    return retEntries;
}

QVector<Log::Entry*>* Log::getUserActions()
{
    QVector<Log::Entry*>* retEntries = new QVector<Log::Entry*>();
    for (int i = 0; i < entries->count(); ++i)
    {
        if (entries->at(i)->getAction() == USERACTION)
                retEntries->append(new Entry(*entries->at(i)));
    }
    return retEntries;
}

Log::Entry::Entry(const Entry &entry)
{
    this->time = entry.time;
    this->message = entry.message;
    this->action = entry.action;
}

void Log::destructLog()
{
    delete entries;
}
