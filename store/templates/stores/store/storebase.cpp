{% set class = '{0}StoreBase'.format(interface) %}
/****************************************************************************
** This is a preserved file.
** Changes will not be overriden by the generator.
** To reset the file you need to delete it first.
****************************************************************************/

#include "{{class|lower}}.h"

#include <QtCore>

{% for operation in interface.operations %}
const QByteArray {{class}}::{{operation|upper}}("{{operation|upper}}");
{% endfor %}

{{class}}::{{class}}(QObject *parent)
    : QObject(parent)
{
}

{{class}}::~{{class}}()
{
}

{% for property in interface.properties %}
{{property|returnType}} {{class}}::{{property}}() const
{
    return m_state.{{property}}();
}
{% endfor %}

{% for operation in interface.operations %}
{{operation|returnType}} {{class}}::{{operation}}({{operation|parameters}})
{
    QVariant payload;
    Action action({{operation|upper}}, payload);
    dispatch(action);
}
{% endfor %}

{{interface}}State {{class}}::getState() const
{
    return m_state;
}

void {{class}}::dispatch(const Action& action)
{
    qDebug() << "current state: " << m_state;
    qDebug() << "dispatch: " << action.type() << " payload: " << action.payload();
    m_state = reduce(action, m_state);
    emit stateChanged(m_state);
    qDebug() << "next state: " << m_state;
}

{{interface}}State {{class}}::reduce(const Action& action, const {{interface}}State& current)
{
    Q_UNUSED(action)
    return current;
}

