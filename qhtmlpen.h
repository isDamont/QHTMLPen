#ifndef QHTMLPEN_H
#define QHTMLPEN_H

#include "windowhtmlrender.h"
#include "filetabwidget.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QTabWidget>
#include <QMenu>
#include <QMap>


class SaveStatusManager;

QT_BEGIN_NAMESPACE
namespace Ui { class QHTMLPen; }
QT_END_NAMESPACE

class QHTMLPen : public QMainWindow
{
    Q_OBJECT

public:
    QHTMLPen(QWidget *parent = nullptr);
    ~QHTMLPen();

    void addNewTab(QString = tr("Новая вкладка"));

private:
    Ui::QHTMLPen *ui;

    FileTabWidget *tabWidget = nullptr;
    WindowHtmlRender *windowHTML = nullptr;

    QMenu* menuFile;
    QMenu* menuCorrection;
    QMenu* menuView;

    QMap<QString, QAction*> buttonMenu;

protected:
    virtual void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *ev) override;

private:
    void menuInitial();

private slots:
    // слоты меню Файл
    void slotCreate();
    void slotOpen();

    // слоты меню Правка
    void slotCancel();
    void slotRepeat();
    void slotCut();
    void slotCopy();
    void slotPaste();
    void slotDelete();

    // слоты меню Просмотр
    void slotRender();
    void slotChangeTextFormat();
};
#endif // QHTMLPEN_H
