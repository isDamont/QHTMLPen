#include "windowhtmlrender.h"

WindowHtmlRender::WindowHtmlRender(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(parent->size());

    webView = new QWebEngineView(this);
    setCentralWidget(webView);

    QObject::connect(webView, &QWebEngineView::titleChanged, this, [=](const QString& title){
        setWindowTitle(title + " - QHTMLPen Render");
    });
}

WindowHtmlRender::~WindowHtmlRender()
{
}

void WindowHtmlRender::updateRender(const QString& text)
{
    webView->setHtml(text);
}
