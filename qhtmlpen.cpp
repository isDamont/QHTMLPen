#include "qhtmlpen.h"
#include "ui_qhtmlpen.h"

QHTMLPen::QHTMLPen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QHTMLPen)
{
    ui->setupUi(this);

    tabWidget = new QTabWidget(this);

    this->addNewTab(tr("Новая вкладка"));

    setCentralWidget(tabWidget);
}

QHTMLPen::~QHTMLPen()
{
    delete ui;
}

void QHTMLPen::addNewTab(QString tabName)
{
    QTextEdit *textEdit = new QTextEdit(this);
    tabWidget->addTab(textEdit, tabName);
}


void QHTMLPen::Slot_render_Init()
{
    if(windowHTML)
    {
        delete windowHTML;
    }

    windowHTML = new WindowHtmlRender(this);
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

