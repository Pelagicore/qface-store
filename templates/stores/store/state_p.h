{% set class = '{0}State'.format(interface) %}
#ifndef {{class|upper}}_P_H
#define {{class|upper}}_P_H

#include <QtCore>

class {{class}}Private : public QSharedData
{
public:
    {{class}}Private();
    {{class}}Private(const {{class}}Private &other);
    ~{{class}}Private();
{% for property in interface.properties %}
    {{property|returnType}} {{property}};
{% endfor %}
};

#endif // {{class|upper}}_P_H




