TARGET = harbour-systemmonitord

CONFIG += console
CONFIG += link_pkgconfig

QT -= gui
QT += dbus sql

PKGCONFIG += mlite5 keepalive
QMAKE_CXXFLAGS += -std=c++0x

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

linux-g++{
   !contains(QT_ARCH, arm64){
       LIB=lib
       message("Building for 32bit system")
    } else {
       LIB=lib64
       message("Building for 64bit system")
   }
}
linux-g++-32 {
    message("Building for emulator / jolla tablet (i486)")
    LIB=lib
}

SOURCES += \
    daemon.cpp \
    dbusadapter.cpp \
    dbusconnector.cpp \
    service.cpp \
    storage.cpp \
    datasource.cpp \
    datasourcecpu.cpp \
    datasourcebattery.cpp \
    datasourcewlan.cpp \
    datasourcecell.cpp \
    datasourcememory.cpp \
    systemsnapshot.cpp \
    datasourcecpusleep.cpp \
    datasourcesuspend.cpp \
    datasourcetemp.cpp \
    datasourcesignal.cpp \
    datasourceinternet.cpp

HEADERS += \
    settings.h \
    dbusadapter.h \
    dbusconnector.h \
    service.h \
    storage.h \
    datasource.h \
    datasourcecpu.h \
    datasourcebattery.h \
    datasourcewlan.h \
    datasourcecell.h \
    datasourcememory.h \
    systemsnapshot.h \
    datasourcecpusleep.h \
    datasourcesuspend.h \
    datasourcetemp.h \
    datasourcesignal.h \
    datasourceinternet.h

INSTALLS += target sysmond

target.path = /usr/bin

sysmond.files = $${TARGET}.service
sysmond.path = /usr/$${LIB}/systemd/user

#qtcreator is bugged
INCLUDEPATH += $$[QT_HOST_PREFIX]/include/mlite5
INCLUDEPATH += $$[QT_HOST_PREFIX]/include/keepalive
