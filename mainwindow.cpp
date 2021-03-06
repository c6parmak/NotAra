#include <QtWidgets>
#include <QQmlContext>
#include "mainwindow.h"
#include "pdfpagemodel.h"
#include "pdfimageprovider.h"

MainWindow::MainWindow(int placeholder) : QMainWindow()
{
    _splitter = new QSplitter(this);
    _locationEdit = new QLineEdit(this);
    _locationEdit->setSizePolicy(QSizePolicy::Expanding, _locationEdit->sizePolicy().verticalPolicy());
    connect(_locationEdit, SIGNAL(returnPressed()), SLOT(changeURL()));

    QToolBar *toolBar = addToolBar(tr("Navigation"));
    _actionRect = toolBar->addAction(QIcon("://images/rectangle_stroked.svg"), "Clip Rectangle");
    _actionRect->setCheckable(true);
    _actionHi = toolBar->addAction(QIcon("://images/bg_color.svg"), "Highlight");
    toolBar->addWidget(_locationEdit);

    PDFPageModel *pdfPageModel = new PDFPageModel;
    //pages.push_back(new PDFPage(nullptr, 0));
    //pages.push_back(new PDFPage(nullptr, 1));
    //pages.push_back(new PDFPage(nullptr, 2));

    _pdfQuickView = new QQuickView;
    // Image provider instantiated before QML
    PDFImageProvider *pdfImageProvider =  new PDFImageProvider;
    _pdfQuickView->setColor(palette().color(QPalette::Normal, QPalette::Window));
    _pdfQuickView->engine()->addImageProvider(QLatin1String("pdfImage"), pdfImageProvider);
    _pdfQuickView->engine()->rootContext()->setContextProperty("pdfModel", pdfPageModel);
    _pdfQuickView->setResizeMode(QQuickView::SizeRootObjectToView);
    _pdfQuickView->setSource(QUrl("qrc:/PDF.qml"));
    //_pdfQuickView->setSource(QUrl("qrc:/pdfview.qml"));
    //_pdfQuickView->setSource(QUrl("qrc:/test.qml"));
    qDebug() << _pdfQuickView->errors();

    // Provide images for PDFView
    QObject *object = _pdfQuickView->rootObject();
    _pdfView = qobject_cast<PDFView*>(object);
    _pdfView->setPageModel(pdfPageModel);
    pdfImageProvider->setPDFView(_pdfView);
    QObject::connect(_actionRect, SIGNAL(toggled(bool)), _pdfView, SLOT(rectToggled(bool)));
    QObject::connect(_actionHi, SIGNAL(triggered()), _pdfView, SLOT(clipRect()));

    _formQuickView = new QQuickView;
    _formQuickView->setColor(palette().color(QPalette::Normal, QPalette::Window));
    _formQuickView->setResizeMode(QQuickView::SizeRootObjectToView);
    _formQuickView->setSource(QUrl("qrc:/FormClip.qml"));
    _pdfQuickView->engine()->rootContext()->setContextProperty("clipData", _pdfView->clipData());
    qDebug() << _formQuickView->errors();

    // Add widgets to window
    QWidget *pdfContainer = QWidget::createWindowContainer(_pdfQuickView);
    QWidget *formContainer = QWidget::createWindowContainer(_formQuickView);
    setCentralWidget(_splitter);
    _splitter->addWidget(pdfContainer);
    _splitter->addWidget(formContainer);
    //_splitter->addWidget(new QTextEdit);
    //setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::_displayURL(QUrl const &url)
{
    _locationEdit->setText(url.toString());
}

void MainWindow::changeURL()
{
    QUrl url = QUrl::fromUserInput(_locationEdit->text());
    qDebug() << "MainWindow::changeURL:" << _locationEdit->text() << url.toString();
    _displayURL(url);
    _loadURL(url);
}

void MainWindow::_loadURL(QUrl const &url)
{
    _pdfView->load(url);
    qDebug() << _pdfQuickView->errors();
    //_pdfView->setFocus();
}





