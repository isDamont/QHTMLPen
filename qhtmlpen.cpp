#include "qhtmlpen.h"
#include "ui_qhtmlpen.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QToolBar>
#include <QMenuBar>

QHTMLPen::QHTMLPen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QHTMLPen)
{
    ui->setupUi(this);
    
    tabWidget = new FileTabWidget(this);

    if(tabWidget)    // делаем проверку указателя
    {
        // при удалении последней вкладки создаём новую
        connect(tabWidget, &FileTabWidget::signalTabRemoved, this, [=](){
            if(tabWidget->count() == 0)
            {
                this->addNewTab();
            }
        });
    }

    this->addNewTab();
    
    menuInitial();
    
    setCentralWidget(tabWidget);
}

QHTMLPen::~QHTMLPen()
{
    delete ui;
    delete tabWidget;
}

void QHTMLPen::keyPressEvent(QKeyEvent *ev)
{
    if(ev->modifiers() == Qt::ShiftModifier)
    {
        switch (ev->key()) {
        // Выход
        case Qt::Key_Escape:
            close();
            return;
            /* Надо придумать комбинации клавишь
            по умолчанию Qt не работает с произвольными клавишами */
//        // Создать вкладку
//        case Qt::Key_N:
//            addNewTab();
//            return;
//        // Закрыть вкладку
//        case Qt::Key_C:
//            slotCloseTab();
//            return;
//        // Сохранить вкладку
//        case Qt::Key_S:
//            slotSave();
//            return;
//        // Открыть файл
//        case Qt::Key_O:
//            slotOpen();
//            return;
        }
    }

    QWidget::keyPressEvent(ev);
}

void QHTMLPen::addNewTab(QString tabName)
{
    QTextEdit *textEdit = new QTextEdit(this);
    tabWidget->addTab(textEdit, tabName);
}

void QHTMLPen::menuInitial()
{
    // меню Файл
    menuFile = menuBar()->addMenu(tr("Файл"));
    buttonMenu["Создать"] = menuFile->addAction(tr("Создать"));
    connect(buttonMenu.value("Создать"), &QAction::triggered, this, &QHTMLPen::slotCreate);

    buttonMenu["Открыть"] = menuFile->addAction(tr("Открыть"));
    connect(buttonMenu.value("Открыть"), &QAction::triggered, this, &QHTMLPen::slotOpen);

    buttonMenu["Сохранить"] = menuFile->addAction(tr("Сохранить"));
    connect(buttonMenu.value("Сохранить"), &QAction::triggered, tabWidget, &FileTabWidget::slotSaveCurrentTab);

    buttonMenu["Сохранить как"] = menuFile->addAction(tr("Сохранить как"));
    connect(buttonMenu.value("Сохранить как"), &QAction::triggered, tabWidget, &FileTabWidget::slotSaveCurrentTabAs);

    buttonMenu["Закрыть вкладку"] = menuFile->addAction(tr("Закрыть вкладку"));
    connect(buttonMenu.value("Закрыть вкладку"), &QAction::triggered, tabWidget, &FileTabWidget::slotCloseCurrentTab);
    menuFile->addSeparator();

    buttonMenu["Выход"] = menuFile->addAction(tr("Выход"));
    connect(buttonMenu.value("Выход"), &QAction::triggered, this, &QHTMLPen::close);

    // меню Правка
    menuCorrection = menuBar()->addMenu(tr("Правка"));
    buttonMenu["Отменить"] = menuCorrection->addAction(tr("Отменить"));
    menuCorrection->addSeparator();
    connect(buttonMenu.value("Отменить"), &QAction::triggered, this, &QHTMLPen::slotCancel);

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



void QHTMLPen::closeEvent(QCloseEvent *event)
{
    if(tabWidget->areAllTabsSaved())
    {
        // если все вкладки сохранены, то принимаем эвент
        event->accept();
    }
    else
    {
        QMessageBox askSave(this);
        askSave.setText(tr("Изменения не сохранены!"));
        askSave.setInformativeText(tr("Хотите выйти без сохранения?"));
        askSave.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        askSave.setDefaultButton(QMessageBox::Ok);

        int ansver = askSave.exec();

        switch (ansver) {
        case QMessageBox::Ok:
            // выходим без сохранения
            event->accept();
            break;
        case QMessageBox::Cancel:
            // игнорируем эвент закрытия
            event->ignore();
            break;
        default:
            // не должно никогда вызываться, но на всякий случай добавлю игнорирование эвента
            event->ignore();
            break;
        }
    }
}

void QHTMLPen::slotCreate()
{
    qDebug() << "slotCreate";
    addNewTab();
}

void QHTMLPen::slotOpen()
{
    qDebug() << "slotOpen";
}

void QHTMLPen::slotCancel()
{
    qDebug() << "slotCancel";
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
    
    if(!windowHTML)
    {
        windowHTML = new WindowHtmlRender(this);
    }

    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(tabWidget->currentWidget());

    if(currentQTextEditWidget)
    {
        QString html = currentQTextEditWidget->toPlainText();
        windowHTML -> updateRender(html);
        windowHTML -> show();
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Ошибка"), tr("Ошибка чтенения текущей вкладки"));
    }
}

void QHTMLPen::slotChangeTextFormat()
{
    qDebug() << "slotChangeTextFormat";
}

