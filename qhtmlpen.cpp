#include "qhtmlpen.h"
#include "ui_qhtmlpen.h"

QHTMLPen::QHTMLPen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QHTMLPen)
{
    ui->setupUi(this);

    textEdit = new QTextEdit(this);

    setCentralWidget(textEdit);
}

QHTMLPen::~QHTMLPen()
{
    delete ui;
}


void QHTMLPen::Slot_render_Init()
{
    if(windowHTML)
    {
        delete windowHTML;
    }
    windowHTML = new WindowHtmlRender(this);
    windowHTML -> updateRender(textEdit);
    windowHTML -> show();
}

