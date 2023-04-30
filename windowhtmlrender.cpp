#include "windowhtmlrender.h"

WindowHtmlRender::WindowHtmlRender(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("html render");
    this->resize(800, 600);

    webView = new QWebEngineView(this);
    setCentralWidget(webView);
}

WindowHtmlRender::~WindowHtmlRender()
{
}

void WindowHtmlRender::updateRender(QTextEdit *textEdit)
{
    QString html = textEdit->toPlainText();
    webView->setHtml(html);
}
