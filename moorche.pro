SOURCES += \
    src/main.cpp \
    src/moorche.cpp \
    src/colony.cpp \
    src/trail.cpp \
    src/map.cpp

INCLUDEPATH += /home/faraz/workspace/stage/include/Stage-4.1 ./include

LIBS += -L/home/faraz/workspace/stage/lib64/ -lstage

HEADERS += \
    include/moorche.h \
    include/colony.h \
    include/trail.h \
    include/config.h \
    include/map.h
