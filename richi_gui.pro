QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++14

INCLUDEPATH += \
    inc \
    fftw \
    src/common \
    src/hostapi/alsa \
    src/hostapi/asihpi \
    src/hostapi/asio/ASIOSDK \
    src/hostapi/asio/ASIOSDK/common \
    src/hostapi/asio/ASIOSDK/host \
    src/hostapi/asio/ASIOSDK/host/pc \
    src/hostapi/coreaudio \
    src/hostapi/dsound \
    src/hostapi/jack \
    src/hostapi/oss \
    src/hostapi/skeleton \
    src/hostapi/wasapi \
    src/hostapi/wdmks \
    src/hostapi/wmme \
    src/os/win \
    src/os/unix


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
win32{
DEFINES += _WIN64
#DEFINES += _DEBUG
DEFINES += _USRDLL
DEFINES += PA_ENABLE_DEBUG_OUTPUT
DEFINES += _CRT_SECURE_NO_DEPRECATE
DEFINES += PAWIN_USE_WDMKS_DEVICE_INFO
DEFINES += _AFXDLL
DEFINES -= UNICODE
DEFINES += _USE_MATH_DEFINES
DEFINES += PA_USE_ASIO=1
DEFINES += PA_USE_DS=0
DEFINES += PA_USE_WMME=1
DEFINES += PA_USE_WASAPI=0
DEFINES += PA_USE_WDMKS=1

}
unix{
DEFINES += PA_USE_ALSA=1
DEFINES += PA_USE_ASIHPI=0
DEFINES += PA_USE_JACK=0
DEFINES += PA_USE_OSS=0
}

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myobject.cpp \
    src/qcustomplot.cpp

HEADERS += \
    inc/qcustomplot.h \
    mainwindow.h \
    myobject.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
win32{
LIBS += -luser32 -ladvapi32
}

unix{
LIBS+= -lasound -lhpi -ljack -lfftw3 -lpthread
SOURCES += \
    src/hostapi/alsa/pa_linux_alsa.c \
    src/hostapi/asihpi/pa_linux_asihpi.c \
    src/hostapi/jack/pa_jack.c \
    src/os/unix/pa_unix_hostapis.c \
    src/os/unix/pa_unix_util.c
}

win32-msvc*{
LIBS += -L$$PWD/fftw libfftw3-3.lib
}
win32-g++{
LIBS+= -lole32 -lwinmm -lsetupapi -lhid -L$$PWD/fftw -llibfftw3-3
}

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    stylesheet.qss
