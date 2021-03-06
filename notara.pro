QT +=  core widgets quick sql
HEADERS =   mainwindow.h \
    pdfview.h \
    pdfpage.h \
    pdfimageprovider.h \
    pdfpagemodel.h \
    treemodel.h \
    database.h \
    clip.h
SOURCES =   main.cpp \
    mainwindow.cpp \
    pdfview.cpp \
    pdfpage.cpp \
    pdfimageprovider.cpp \
    pdfpagemodel.cpp \
    treemodel.cpp \
    database.cpp \
    clip.cpp

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += /usr/include/poppler/qt5
LIBS        += -L/usr/lib -lpoppler-qt5

RESOURCES += \
    notara.qrc

OTHER_FILES +=
