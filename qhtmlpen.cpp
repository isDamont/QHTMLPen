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

