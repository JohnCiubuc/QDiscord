QT += websockets network
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        discordbot.cpp \
        main.cpp \
        qdiscordinterpreter.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#QDiscord Lib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QDiscord-Desktop-Release/src/release/ -lQDiscord
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QDiscord-Desktop-Release/src/debug/ -lQDiscord
else:unix: LIBS += -L$$PWD/../build-QDiscord-Desktop-Release/src/ -lQDiscord
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-QDiscord-Desktop-Release/src/release/libQDiscord.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-QDiscord-Desktop-Release/src/debug/libQDiscord.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-QDiscord-Desktop-Release/src/release/QDiscord.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-QDiscord-Desktop-Release/src/debug/QDiscord.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-QDiscord-Desktop-Release/src/libQDiscord.a

#QDiscord Includes
INCLUDEPATH += $$PWD/../QDiscord/src/
DEPENDPATH += $$PWD/../QDiscord/src/


HEADERS += \
    discordbot.h \
    qdiscordinterpreter.h
