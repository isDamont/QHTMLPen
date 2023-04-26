#ifndef QHTMLPEN_H
#define QHTMLPEN_H

#include <QMainWindow>

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

protected:
    virtual void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    bool isFileSaved();
};
#endif // QHTMLPEN_H
