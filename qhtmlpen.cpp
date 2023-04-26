#include "qhtmlpen.h"
#include "ui_qhtmlpen.h"

#include <QCloseEvent>

QHTMLPen::QHTMLPen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QHTMLPen)
{
    ui->setupUi(this);

    installEventFilter(this);
}

QHTMLPen::~QHTMLPen()
{
    delete ui;
}

void QHTMLPen::closeEvent(QCloseEvent *event)
{
    if(isFileSaved())
    {
        event->accept();
    }
    else
    {
        event->ignore();
        // сохранение файла
    }
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
    return true;
}

