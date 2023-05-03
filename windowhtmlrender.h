#ifndef WINDOWHTMLRENDER_H
#define WINDOWHTMLRENDER_H

#include <QWebEngineView>
#include <QMainWindow>
#include <QTextEdit>

class WindowHtmlRender : public QMainWindow
{
    Q_OBJECT
public:
    WindowHtmlRender(QWidget *parent = nullptr);
    ~WindowHtmlRender();

    void updateRender(QTextEdit *textEdit);
private:
    QWebEngineView *webView;
};

#endif // WINDOWHTMLRENDER_H
