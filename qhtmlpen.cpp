#include "qhtmlpen.h"
#include "ui_qhtmlpen.h"

#include <QDebug>
#include <QToolBar>
#include <QMenuBar>

QHTMLPen::QHTMLPen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QHTMLPen)
{
    ui->setupUi(this);

    // меню Файл
    menuFile = menuBar()->addMenu(tr("Файл"));
    buttonMenu["Создать"] = menuFile->addAction(tr("Создать"));
    connect(buttonMenu.value("Создать"), &QAction::triggered, this, &QHTMLPen::slotCreate);

    buttonMenu["Открыть"] = menuFile->addAction(tr("Открыть"));
    connect(buttonMenu.value("Открыть"), &QAction::triggered, this, &QHTMLPen::slotOpen);

    buttonMenu["Сохранить"] = menuFile->addAction(tr("Сохранить"));
    connect(buttonMenu.value("Сохранить"), &QAction::triggered, this, &QHTMLPen::slotSave);

    buttonMenu["Сохранить как"] = menuFile->addAction(tr("Сохранить как"));
    connect(buttonMenu.value("Сохранить как"), &QAction::triggered, this, &QHTMLPen::slotSaveAs);
    menuFile->addSeparator();

    buttonMenu["Выход"] = menuFile->addAction(tr("Выход"));
    connect(buttonMenu.value("Выход"), &QAction::triggered, this, &QHTMLPen::slotExit);

    // меню Правка
    menuCorrection = menuBar()->addMenu(tr("Правка"));
    buttonMenu["Отменить"] = menuCorrection->addAction(tr("Отменить"));
    menuCorrection->addSeparator();
    connect(buttonMenu.value("Отменить"), &QAction::triggered, this, &QHTMLPen::slotCansel);

    buttonMenu["Вырезать"] = menuCorrection->addAction(tr("Вырезать"));
    connect(buttonMenu.value("Вырезать"), &QAction::triggered, this, &QHTMLPen::slotCut);

    buttonMenu["Копировать"] = menuCorrection->addAction(tr("Копировать"));
    connect(buttonMenu.value("Копировать"), &QAction::triggered, this, &QHTMLPen::slotCopy);

    buttonMenu["Вставить"] = menuCorrection->addAction(tr("Вставить"));
    connect(buttonMenu.value("Вставить"), &QAction::triggered, this, &QHTMLPen::slotPaste);

    buttonMenu["Удалить"] = menuCorrection->addAction(tr("Удалить"));
    connect(buttonMenu.value("Удалить"), &QAction::triggered, this, &QHTMLPen::slotDelete);

    // меню Просмотр
    menuView = menuBar()->addMenu(tr("Просмотр"));
    buttonMenu["Рендеринг"] = menuView->addAction(tr("Рендеринг"));
    connect(buttonMenu.value("Рендеринг"), &QAction::triggered, this, &QHTMLPen::slotRender);

    buttonMenu["Изменить форматирование"] = menuView->addAction(tr("Изменить форматирование"));
    connect(buttonMenu.value("Изменить форматирование"), &QAction::triggered, this, &QHTMLPen::slotChangeTextFormat);
}

QHTMLPen::~QHTMLPen()
{
    delete ui;
}

void QHTMLPen::slotCreate()
{
    qDebug() << "slotCreate";
}

void QHTMLPen::slotOpen()
{
    qDebug() << "slotOpen";
}

void QHTMLPen::slotSave()
{
    qDebug() << "slotSave";
}

void QHTMLPen::slotSaveAs()
{
    qDebug() << "slotSaveAs";
}

void QHTMLPen::slotExit()
{
    qDebug() << "slotExit";
}

void QHTMLPen::slotCansel()
{
    qDebug() << "slotCansel";
}

void QHTMLPen::slotCut()
{
    qDebug() << "slotCut";
}

void QHTMLPen::slotCopy()
{
    qDebug() << "slotCopy";
}

void QHTMLPen::slotPaste()
{
    qDebug() << "slotPaste";
}

void QHTMLPen::slotDelete()
{
    qDebug() << "slotDelete";
}

void QHTMLPen::slotRender()
{
    qDebug() << "slotRender";
}

void QHTMLPen::slotChangeTextFormat()
{
    qDebug() << "slotChangeTextFormat";
}

