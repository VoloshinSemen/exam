#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QVector>
#include <QDateTime>
#include <QLabel>

class Log
{
public:
    enum type {DATABASE, USERACTION};
    class Entry
    {
        QDateTime time;
        type action;
        QString message;

    public:
        Entry(type action, QString message);
        Entry(const Entry &entry);
        QString getTime() {return this->time.toString();}
        QString getMessage() {return this->message;}
        type getAction() {return this->action;}
    };

    static void initLog(QLabel* output);
    //response to user actions
    static void ua(QString message);
    //database log
    static void db(QString message);
    static QVector<Entry *> *getAll();
    static QVector<Entry *> *getUserActions();
    static QVector<Entry *> *getDatabase();
    static void destructLog();

private:
    static QVector<Entry*> *entries;
    static QLabel *output;
};

#endif // LOG_H
