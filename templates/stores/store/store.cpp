{% set class = '{0}Store'.format(interface) %}
/****************************************************************************
** This is a preserved file.
** Changes will not be overriden by the generator.
** To reset the file you need to delete it first.
****************************************************************************/

#include <QtQml>
#include "{{class|lower}}.h"


{{class}}::{{class}}(QObject *parent)
    : {{class}}Base(parent)
{
    qDebug() << "{{class}}()";
}

{{class}}::~{{class}}()
{
    qDebug() << "~{{class}}()";
}

{{interface}}State {{class}}::reduce(const Action& action, const {{interface}}State& state)
{
    qDebug() << "{{class}}::reducer() implement reducer for " << action.type();
    return state;
}

void {{class}}::registerTypes(const char *uri)
{
    qmlRegisterType<{{class}}>(uri, 1, 0, "{{class}}");
}

