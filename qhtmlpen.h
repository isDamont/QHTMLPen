#ifndef QHTMLPEN_H
#define QHTMLPEN_H

#include "windowhtmlrender.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QTabWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class QHTMLPen; }
QT_END_NAMESPACE

class QHTMLPen : public QMainWindow
{
    Q_OBJECT

public:
    QHTMLPen(QWidget *parent = nullptr);
    ~QHTMLPen();

    void addNewTab(QString);

    void Slot_render_Init();

private:
    Ui::QHTMLPen *ui;
    QTabWidget *tabWidget;

    WindowHtmlRender *windowHTML = nullptr;
};
#endif // QHTMLPEN_H
