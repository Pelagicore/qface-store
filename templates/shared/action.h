#pragma once

#include <QtCore>


class Action {
    Q_GADGET
public:
    Action()
    {
    }
    Action(const QString& type, const QVariant& payload)
        : m_type(type)
        , m_payload(payload)
    {
    }
    QString type() const
    {
        return m_type;
    }
    QVariant payload() const
    {
        return m_payload;
    }
private:
    QString m_type;
    QVariant m_payload;
};

Q_DECLARE_METATYPE(Action)