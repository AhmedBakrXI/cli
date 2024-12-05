#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include <QString>
#include <QVariant>

class AbstractCommand {
public:

    QString getName() const;
    void setName(const QString &newName);
    QStringList getParams() const;
    void setParams(const QStringList &newParams);
    void addParam(const QString &param);
    QString getDescription() const;
    void setDescription(const QString &newDescription);
    int getTimeout() const;
    void setTimeout(int newTimeout);
    QString toStringCommand();

    virtual QVariant parseResponse(const QString &response) = 0;

private:
    QString name;
    QStringList params;
    QString description;
    int timeout;
};

#endif // ABSTRACTCOMMAND_H
