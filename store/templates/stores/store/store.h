{% set class = '{0}Store'.format(interface) %}
#pragma once

/****************************************************************************
** This is a preserved file.
** Changes will not be overriden by the generator.
** To reset the file you need to delete it first.
****************************************************************************/

#include <QtCore>
#include "{{class|lower}}base.h"

class {{class}} : public {{class}}Base
{
    Q_OBJECT
public:
    {{class}}(QObject *parent = nullptr);
    virtual ~{{class}}();
public:
    virtual {{interface}}State reduce(const Action& action, const {{interface}}State& current);
    static void registerTypes(const char *uri);
};
