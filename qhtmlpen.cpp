#include "qhtmlpen.h"
#include "ui_qhtmlpen.h"

QHTMLPen::QHTMLPen(QWidget *parent)
    : QMainWindow(parent)
    , fS(std::make_unique<FileSystem>())
    , ui(new Ui::QHTMLPen)
{
    ui->setupUi(this);
    connect(ui->action, &QAction::triggered, this, &QHTMLPen::slotSaveFile);
    connect(ui->action_2, &QAction::triggered, this, &QHTMLPen::slotSaveAs);

}

QHTMLPen::~QHTMLPen()
{
    delete ui;
}

void QHTMLPen::slotSaveFile()
{
    fS->saveFile(ui->textEdit->toPlainText());
}

void QHTMLPen::slotSaveAs()
{
    //fS->saveAs(ui->textEdit->toPlainText());
}

