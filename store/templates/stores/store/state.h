{% set class = '{0}State'.format(interface) %}
#ifndef {{class|upper}}_H
#define {{class|upper}}_H

#include <QtCore>

class {{class}}Private;
class {{class}}
{
    Q_GADGET
{% for property in interface.properties %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}})
{% endfor %}
public:
    {{class}}();
    {{class}}(const {{class}} &other);
    ~{{class}}();

{% for property in interface.properties %}
    {{property|returnType}} {{property}}() const;
    void set{{property|upperfirst}}({{property|parameters}});
{% endfor %}
    Q_INVOKABLE {{class}} clone() const;

    {{class}} &operator=(const {{class}} &other);
    bool operator!=(const {{class}} &other) const;
    bool operator==(const {{class}} &other) const;

private:
    QExplicitlySharedDataPointer<{{class}}Private> d;
    friend class {{class}}Private;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const {{class}} &);
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &stream, const {{class}} &that);
QDataStream &operator>>(QDataStream &stream, {{class}} &that);
#endif

Q_DECLARE_TYPEINFO({{class}}, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE({{class}})

#endif // {{class|upper}}_H