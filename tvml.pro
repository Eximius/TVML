#
#   Qmake project file
#    ...because qtcreator is awesome.
#
TEMPLATE = app
CONFIG += console
CONFIG -= qt

INCLUDEPATH += include

QMAKE_CXXFLAGS += -std=c++11 -O3

SOURCES += \
    src/test.cpp

HEADERS += \
    include/tvml/Matrix3x3.h \
    include/tvml/Matrix4x4.h \
    include/tvml/quart.h \
    include/tvml/Quarternion.h \
    include/tvml/stdmat.h \
    include/tvml/stdvec.h \
    include/tvml/Vector2.h \
    include/tvml/Vector3.h \
    include/tvml/Vector4.h \
    include/tvml/misc.h
