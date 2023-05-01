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

    fileSystem = new FileSystem;

    installEventFilter(this);
    
    tabWidget = new QTabWidget(this);
    this->addNewTab(tr("Новая вкладка"));
    
    menuInitial();
    
    setCentralWidget(tabWidget);
}

QHTMLPen::~QHTMLPen()
{
    delete ui;
    delete fileSystem;
}

bool QHTMLPen::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this)
    {
         QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

         if(keyEvent)
         {
             if(keyEvent->modifiers() == Qt::ShiftModifier)
             {
                 if(keyEvent->key() == Qt::Key_Escape)
                 {
                     close();
                     return true;
                 }
             }
         }
    }

    return QObject::eventFilter(obj, event);
}

bool QHTMLPen::isFileSaved()
{
    // проверка сохранения файла
    return false;
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

void QHTMLPen::closeEvent(QCloseEvent *event)
{
    if(isFileSaved())
    {
         event->accept();
    }
    else
    {
         QMessageBox askSave(this);
         askSave.setText(tr("Изменения не сохранены!"));
         askSave.setInformativeText(tr("Хотите сохранить изменения?"));
         askSave.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
         askSave.setDefaultButton(QMessageBox::Save);
         int ansver = askSave.exec();

         switch (ansver) {
         case QMessageBox::Save:
             // Вызываем метод для сохранения и игнорируем эвент закрытия
             slotSave();
             event->ignore();
             break;
         case QMessageBox::Discard:
             // выходим не сохраняя
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
}

void QHTMLPen::slotOpen()
{
    qDebug() << "slotOpen";
}

void QHTMLPen::slotSave()
{
    qDebug() << "slotSave";

    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    QString text = currentQTextEditWidget->toPlainText();
    fileSystem->saveFile(text);
}

void QHTMLPen::slotSaveAs()
{
    qDebug() << "slotSaveAs";

    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    QString text = currentQTextEditWidget->toPlainText();
    fileSystem->saveAs(text);
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
    
    if(!windowHTML)
    {
        windowHTML = new WindowHtmlRender(this);
    }

    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(tabWidget->currentWidget());

    if(currentQTextEditWidget)
    {
        windowHTML -> updateRender(currentQTextEditWidget);
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




