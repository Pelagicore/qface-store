TEMPLATE = lib

CONFIG += staticlib c++11
QT += core
DESTDIR = $$BUILD_DIR/libs
TARGET = {{module}}


include( {{module|lower|replace(".", "-")}}.pri )
include( $$SOURCE_DIR/shared/shared.pri )
