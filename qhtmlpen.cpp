#include "qhtmlpen.h"

#include "formatdialog.h"
#include "ui_qhtmlpen.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QToolBar>
#include <QMenuBar>
#include <QClipboard>

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
    
    menuInitial();
    shortCutInitial();

    this->addNewTab();
       
    setCentralWidget(tabWidget);
}

QHTMLPen::~QHTMLPen()
{
    delete ui;
    delete tabWidget;
}

void QHTMLPen::addNewTab(QString tabName)
{
    QTextEdit *textEdit = new QTextEdit(this);
    tabWidget->addTab(textEdit, tabName);   
}

void QHTMLPen::shortCutInitial()
{
// Выход
    buttonMenu.value("Выход")->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
// Создать вкладку
    buttonMenu.value("Создать")->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
// Закрыть вкладку
    buttonMenu.value("Закрыть вкладку")->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_W));
// Сохранить вкладку
    buttonMenu.value("Сохранить")->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
// Открыть файл
    buttonMenu.value("Открыть")->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
// Рендер
    buttonMenu.value("Рендеринг")->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
}

void QHTMLPen::menuInitial()
{
    // меню Файл
    menuFile = menuBar()->addMenu(tr("&Файл"));
    buttonMenu["Создать"] = menuFile->addAction(tr("Соз&дать"));
    connect(buttonMenu.value("Создать"), &QAction::triggered, this, &QHTMLPen::slotCreate);


    buttonMenu["Открыть"] = menuFile->addAction(tr("&Открыть"));
    connect(buttonMenu.value("Открыть"), &QAction::triggered, tabWidget, &FileTabWidget::slotOpen);

    buttonMenu["Сохранить"] = menuFile->addAction(tr("&Сохранить"));
    connect(buttonMenu.value("Сохранить"), &QAction::triggered, tabWidget, &FileTabWidget::slotSaveCurrentTab);

    buttonMenu["Сохранить как"] = menuFile->addAction(tr("Сохранить &как"));
    connect(buttonMenu.value("Сохранить как"), &QAction::triggered, tabWidget, &FileTabWidget::slotSaveCurrentTabAs);

    buttonMenu["Закрыть вкладку"] = menuFile->addAction(tr("&Закрыть вкладку"));
    connect(buttonMenu.value("Закрыть вкладку"), &QAction::triggered, tabWidget, &FileTabWidget::slotCloseCurrentTab);
    menuFile->addSeparator();

    buttonMenu["Выход"] = menuFile->addAction(tr("&Выход"));
    connect(buttonMenu.value("Выход"), &QAction::triggered, this, &QHTMLPen::close);

    // меню Правка
    menuCorrection = menuBar()->addMenu(tr("&Правка"));
    buttonMenu["Отменить"] = menuCorrection->addAction(tr("&Отменить"));
    connect(buttonMenu.value("Отменить"), &QAction::triggered, this, &QHTMLPen::slotCancel);

    buttonMenu["Вырезать"] = menuCorrection->addAction(tr("&Вырезать"));
    connect(buttonMenu.value("Вырезать"), &QAction::triggered, this, &QHTMLPen::slotCut);

    buttonMenu["Повторить"] = menuCorrection->addAction(tr("Пов&торить"));
    connect(buttonMenu.value("Повторить"), &QAction::triggered, this, &QHTMLPen::slotRepeat);
    menuCorrection->addSeparator();

 

    buttonMenu["Копировать"] = menuCorrection->addAction(tr("&Копировать"));
    connect(buttonMenu.value("Копировать"), &QAction::triggered, this, &QHTMLPen::slotCopy);

    buttonMenu["Вставить"] = menuCorrection->addAction(tr("В&ставить"));
    connect(buttonMenu.value("Вставить"), &QAction::triggered, this, &QHTMLPen::slotPaste);

    buttonMenu["Удалить"] = menuCorrection->addAction(tr("&Удалить"));
    connect(buttonMenu.value("Удалить"), &QAction::triggered, this, &QHTMLPen::slotDelete);

    // меню Просмотр
    menuView = menuBar()->addMenu(tr("Прос&мотр"));
    buttonMenu["Рендеринг"] = menuView->addAction(tr("&Рендеринг"));
    connect(buttonMenu.value("Рендеринг"), &QAction::triggered, this, &QHTMLPen::slotRender);

    buttonMenu["Изменить форматирование"] = menuView->addAction(tr("&Изменить форматирование"));
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
        // запрос на выход без сохранения
        if(tabWidget->doWithoutSaving(tr("Хотите выйти без сохранения?")))
        {
            // если подтвердили, принимаем эвент
            event->accept();
        }
        else
        {
            // иначе игнорируем
            event->ignore();
        }
    }
}

void QHTMLPen::slotCreate()
{
    qDebug() << "slotCreate";
    addNewTab();
}

void QHTMLPen::slotCancel()
{
    qDebug() << "slotCancel";
    QTextEdit* tempTextEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if(tempTextEdit){
        tempTextEdit->undo();
    }
}

void QHTMLPen::slotRepeat()
{
    qDebug() << "slotRepeat";
    QTextEdit* tempTextEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if(tempTextEdit){
        tempTextEdit->redo();
    }
}

void QHTMLPen::slotCut()
{
    qDebug() << "slotCut";

    // Копируем текст в буфер обмена c помощью ранее созданного метода
    slotCopy();

    // Получаем текущий выделенный текст
    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(tabWidget->currentWidget());

    // Проверяем на удачный каст
    if(currentQTextEditWidget)
    {
        // Удаляем выделенный текст
        QTextCursor cursor = currentQTextEditWidget->textCursor();
        cursor.removeSelectedText();
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Ошибка"), tr("Ошибка чтенения текущей вкладки"));
    }
}

void QHTMLPen::slotCopy()
{
    qDebug() << "slotCopy";

    // Получаем текущий выделенный текст
    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(tabWidget->currentWidget());

    // Проверяем на удачный каст
    if(currentQTextEditWidget)
    {
        QString selectedText = currentQTextEditWidget->textCursor().selectedText();

        // Копируем текст в буфер обмена
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(selectedText);
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Ошибка"), tr("Ошибка чтенения текущей вкладки"));
    }
}

void QHTMLPen::slotPaste()
{
    qDebug() << "slotPaste";
    QTextEdit* tempTextEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if(tempTextEdit){
        tempTextEdit->paste();
    }
}

void QHTMLPen::slotDelete()
{
    qDebug() << "slotDelete";

    QTextEdit* tempTextEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if(tempTextEdit){
        tempTextEdit->textCursor().removeSelectedText();
    }
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

    FormatDialog formatDialog;

    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(tabWidget->currentWidget());

    if(currentQTextEditWidget)
    {
        formatDialog.initDialog(currentQTextEditWidget);
        formatDialog.exec();
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Ошибка"), tr("Ошибка чтенения текущей вкладки"));
    }
}

