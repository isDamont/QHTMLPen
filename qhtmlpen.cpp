#include "qhtmlpen.h"
#include "savestatusmanager.h"
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
    statusManager = new SaveStatusManager;

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
    delete statusManager;
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

bool QHTMLPen::isCurrentTabSaved()
{
    // проверка сохранения файла
    if(tabWidget->count() == 0)
    {
         return true;
    }

    return statusManager->GetStatus(tabWidget->currentIndex());
}

void QHTMLPen::setTabIconStarVisibleTo(int index, bool visible)
{
    QString tabText = tabWidget->tabText(index);

    if(*(tabText.end() - 1) != '*' && visible)
    {
         tabText.push_back('*');
         tabWidget->setTabText(index, tabText);
    }

    if(*(tabText.end() - 1) == '*' && !visible)
    {
         tabText.erase(tabText.end() - 1);
         tabWidget->setTabText(index, tabText);
    }
}

void QHTMLPen::addNewTab(QString tabName)
{
    QTextEdit *textEdit = new QTextEdit(this);
    tabWidget->addTab(textEdit, tabName);

    if(statusManager)
    {
        statusManager->AddStatus(true);

        connect(textEdit, &QTextEdit::textChanged, this, [=](){
         statusManager->SetStatusTo(tabWidget->indexOf(textEdit), false);
         setTabIconStarVisibleTo(tabWidget->indexOf(textEdit), true);
        });
    }
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

    buttonMenu["Закрыть вкладку"] = menuFile->addAction(tr("Закрыть вкладку"));
    connect(buttonMenu.value("Закрыть вкладку"), &QAction::triggered, this, &QHTMLPen::slotCloseTab);
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
    bool allTabsSaved = true;

    if(statusManager)
    {
        for(int index = 0; index < tabWidget->count(); index++)
        {
             tabWidget->setCurrentIndex(index);

             if(!isCurrentTabSaved())
             {
                 allTabsSaved = false;
                 break;
             }
        }
    }

    if(allTabsSaved)
    {
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
    addNewTab("Новая вкладка");
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

    if(statusManager)
    {
        statusManager->SetStatusTo(tabWidget->currentIndex(), true);
        setTabIconStarVisibleTo(tabWidget->currentIndex(), false);
    }
}

void QHTMLPen::slotSaveAs()
{
    qDebug() << "slotSaveAs";

    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    QString text = currentQTextEditWidget->toPlainText();
    fileSystem->saveAs(text);

    if(statusManager)
    {
        statusManager->SetStatusTo(tabWidget->currentIndex(), true);
        setTabIconStarVisibleTo(tabWidget->currentIndex(), false);
    }
}

void QHTMLPen::slotCloseTab()
{
    qDebug() << "slotCloseTab";
    int index = tabWidget->currentIndex();
    if(index >= 0){

         if(false/*файл не сохранён*/){  // проверка на сохранение файла
             // вызов диалогового окна
         }
         else{
             tabWidget->currentWidget()->close();   // закрытие виджета
             tabWidget->removeTab(index);           // закрытие вкладки
         }
    }
}

void QHTMLPen::slotExit()
{
    qDebug() << "slotCloseTab";
    int index = tabWidget->currentIndex();
    if(index >= 0){

        if(!isCurrentTabSaved()){  // проверка на сохранение файла
            // вызов диалогового окна
            QMessageBox askSave(this);
            askSave.setText(tr("Изменения не сохранены!"));
            askSave.setInformativeText(tr("Хотите закрыть вкладку без сохранения?"));
            askSave.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            askSave.setDefaultButton(QMessageBox::Ok);

            if(askSave.exec() == QMessageBox::Cancel)
            {
                // если нажали "Отмена", то ничего не делвем
                return;
            }
        }

        if(statusManager)
        {
            statusManager->RemoveStatus(tabWidget->currentIndex());
        }

        tabWidget->currentWidget()->close();   // закрытие виджета
        tabWidget->removeTab(index);           // закрытие вкладки
    }
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

