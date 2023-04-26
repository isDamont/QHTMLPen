#ifndef QHTMLPEN_H
#define QHTMLPEN_H

#include <QMainWindow>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class QHTMLPen; }
QT_END_NAMESPACE

class QHTMLPen : public QMainWindow
{
    Q_OBJECT

public:
    QHTMLPen(QWidget *parent = nullptr);
    ~QHTMLPen();

private:
    Ui::QHTMLPen *ui;
    QTextEdit *textEdit;
};
#endif // QHTMLPEN_H
