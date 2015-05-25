#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QObject>
#include <QDate>

class Encryption : public QObject
{
    Q_OBJECT
public:
    explicit Encryption(QObject *parent = 0);
    ~Encryption();
    static QString genPasscode(QString s, QDate dat, QString op);
    static QDate checkPasscode(QString s, const QString code, int& op);

signals:

public slots:
};

#endif // ENCRYPTION_H
