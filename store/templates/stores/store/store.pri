QT *= core qml

INCLUDEPATH += $$PWD

{% for interface in module.interfaces %}
# {{interface}} store
HEADERS += $$PWD/{{interface|lower}}store.h
SOURCES += $$PWD/{{interface|lower}}store.cpp
HEADERS += $$PWD/{{interface|lower}}storebase.h
SOURCES += $$PWD/{{interface|lower}}storebase.cpp
# {{interface}} state
HEADERS += $$PWD/{{interface|lower}}state.h
HEADERS += $$PWD/{{interface|lower}}state_p.h
SOURCES += $$PWD/{{interface|lower}}state.cpp

{% endfor %}