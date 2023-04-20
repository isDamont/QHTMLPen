#include "qhtmlpen.h"
#include "ui_qhtmlpen.h"

QHTMLPen::QHTMLPen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QHTMLPen)
{
    ui->setupUi(this);
}

QHTMLPen::~QHTMLPen()
{
    delete ui;
}

