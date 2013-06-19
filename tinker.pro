
RESOURCES += \
    images.qrc

HEADERS += \
    src/include/tinkermainwindow.h \
    src/include/installationwidget.h \
    src/include/tinkertest.h \
    src/include/applist.h \
    src/include/appinfo.h

SOURCES += \
    src/core/tinkermainwindow.cpp \
    src/core/main.cpp \
    src/core/installationwidget.cpp \
    src/base/applist.cpp \
    src/base/appinfo.cpp \
    src/test/tinkertest.cpp

FORMS += \
    src/ui/mainwindow.ui \
    src/ui/installation.ui

OTHER_FILES += \
    qss/style.qss
