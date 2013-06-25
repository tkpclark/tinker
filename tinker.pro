QT       += xml

RESOURCES += \
    images.qrc

HEADERS += \
    src/include/tinkermainwindow.h \
    src/include/installationwidget.h \
    src/include/tinkertest.h \
    src/include/applist.h \
    src/include/appinfo.h \
    src/include/linuxcommand.h \
    src/include/detailwidget.h

SOURCES += \
    src/core/tinkermainwindow.cpp \
    src/core/main.cpp \
    src/core/installationwidget.cpp \
    src/base/applist.cpp \
    src/base/appinfo.cpp \
    src/test/tinkertest.cpp \
    src/base/linuxcommand.cpp \
    src/core/detailwidget.cpp

FORMS += \
    src/ui/mainwindow.ui \
    src/ui/installation.ui \
    src/ui/detail.ui

OTHER_FILES += \
    qss/style.qss
