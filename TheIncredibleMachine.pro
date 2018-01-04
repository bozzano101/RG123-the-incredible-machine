TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGL -lGLU -lglut -lm

SOURCES += \
    levels.cpp \
    object.cpp

HEADERS += \
    levels_draw.h \
    object.h \
    levels_animate.h \
    levels_global.h

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter -Wno-unused-variable
