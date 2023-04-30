#ifndef QHTMLPEN_H
#define QHTMLPEN_H

#include "windowhtmlrender.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QTabWidget>
#include <QMenu>
#include <QMap>


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

private:
    Ui::QHTMLPen *ui;

protected:
    virtual void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    bool isFileSaved();
    QTabWidget *tabWidget;

    WindowHtmlRender *windowHTML = nullptr;

    QMenu* menuFile;
    QMenu* menuCorrection;
    QMenu* menuView;

    QMap<QString, QAction*> buttonMenu;

    void menuInitial();

private slots:
    // слоты меню Файл
    void slotCreate();
    void slotOpen();
    void slotSave();
    void slotSaveAs();
    void slotExit();

    // слоты меню Правка
    void slotCansel();
    void slotCut();
    void slotCopy();
    void slotPaste();
    void slotDelete();

    // слоты меню Просмотр
    void slotRender();
    void slotChangeTextFormat();
};
#endif // QHTMLPEN_H
