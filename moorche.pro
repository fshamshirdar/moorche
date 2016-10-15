SOURCES += \
    src/main.cpp \
    src/moorche.cpp \
    src/colony.cpp \
    src/trail.cpp \
    src/map.cpp

INCLUDEPATH += ${STAGEPATH} ../include

LIBPATH += ${STAGELIBPATH}
LIBS += ${STAGELIBS}

HEADERS += \
    include/moorche.h \
    include/colony.h \
    include/trail.h \
    include/config.h \
    include/map.h
