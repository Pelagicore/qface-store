{% set class = '{0}State'.format(interface) %}
#include <QtCore>
#include "{{class|lower}}.h"
#include "{{class|lower}}_p.h"

// class {{class}}Private

{{class}}Private::{{class}}Private()
    : QSharedData()
{% for property in interface.properties %}
    , {{property}}({{property|defaultValue}})
{% endfor %}
{
    qDebug() << "{{class}}Private()";
}

{{class}}Private::{{class}}Private(const {{class}}Private &other)
    : QSharedData(other)
{% for property in interface.properties %}
    , {{property}}(other.{{property}})
{% endfor %}
{
    qDebug() << "{{class}}Private(other)";
}

{{class}}Private::~{{class}}Private()
{
}

// class {{class}}

{{class}}::{{class}}()
    : d(new {{class}}Private)
{
    qDebug() << "{{class}}()";
}

{{class}}::{{class}}(const {{class}} &other)
    : d(other.d)
{
    qDebug() << "{{class}}(other)";
}

{{class}}::~{{class}}()
{
}

{% for property in interface.properties %}
{{property|returnType}} {{class}}::{{property}}() const
{
    return d->{{property}};
}

void {{class}}::set{{property|upperfirst}}({{property|parameters}})
{
    d->{{property}} = {{property}};
}
{% endfor %}

{{class}} {{class}}::clone() const
{
   {{class}} other;
   other.d.detach();
   return other;
}

{{class}} &{{class}}::operator=(const {{class}} &other)
{
    if (this == &other) {
        return *this;
    }
    d = other.d;
    return (*this);
}

bool {{class}}::operator!=(const {{class}} &other) const
{
    return !operator==(other);
}

bool {{class}}::operator==(const {{class}} &other) const
{
    return (
{% for property in interface.properties %}
        {%+ if not loop.first %}&&{%endif%} d->{{property}} == other.d->{{property}}
{% endfor %}
    );
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const {{class}} &that)
{
    QDebugStateSaver saver(dbg);

    dbg.nospace() << "{{class}}(";
{% for property in interface.properties %}
    dbg << that.{{property}}(){%if not loop.last%} << ", "{%endif%};
{% endfor %}
    dbg << ')';

    return dbg;
}
#endif // QT_NO_DEBUG_STREAM

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &stream, const {{class}} &that)
{

{% for property in interface.properties %}
    stream << that.{{property}}();
{% endfor %}
    return stream;
}

QDataStream &operator>>(QDataStream &stream, {{class}} &that)
{

{% for property in interface.properties %}
    {{property|returnType}} {{property}};
    stream >> {{property}};
    that.set{{property|upperfirst}}({{property}});
{% endfor %}

    return stream;
}
#endif // QT_NO_DATASTREAM



