QT       += network websockets
QT       -= gui

TARGET = QDiscord
TEMPLATE = lib
CONFIG += staticlib c++11

isEmpty(PREFIX) {
    PREFIX=/usr
} else {
    equals(PREFIX, "/") {
        PREFIX=""
    }
}

include(depends.pri)

unix {
    target.path = $$PREFIX/lib
    topheaders.files = $$TOPHEADERS
    topheaders.path = $$PREFIX/include
    dirheaders.files = $$DIRHEADERS
    dirheaders.path = $$PREFIX/include/qdiscord.d
    INSTALLS += target topheaders dirheaders
}
