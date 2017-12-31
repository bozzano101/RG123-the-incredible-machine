TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lGLU -lglut -lm

SOURCES += \
    levels.cpp

HEADERS += \
    levels_draw.h

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
