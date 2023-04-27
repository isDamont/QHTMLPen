#ifndef QHTMLPEN_H
#define QHTMLPEN_H

#include <QMainWindow>
#include <QAction>
#include "FileSystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QHTMLPen; }
QT_END_NAMESPACE

class QHTMLPen : public QMainWindow
{
    Q_OBJECT

public:
    QHTMLPen(QWidget *parent = nullptr);
    ~QHTMLPen();
    std::unique_ptr<FileSystem> fS;

public slots:
    void slotSaveFile();
    void slotSaveAs();

private:
    Ui::QHTMLPen *ui;
};
#endif // QHTMLPEN_H
