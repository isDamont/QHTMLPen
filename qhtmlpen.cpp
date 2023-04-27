#include "qhtmlpen.h"
#include "ui_qhtmlpen.h"

#include <QCloseEvent>
#include <QMessageBox>

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
        QMessageBox askSave(this);
        askSave.setText(tr("��������� �� ���������!"));
        askSave.setInformativeText(tr("������ ��������� ���������?"));
        askSave.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        askSave.setDefaultButton(QMessageBox::Save);
        int ansver = askSave.exec();

        switch (ansver) {
            case QMessageBox::Save:
                // �������� ����� ��� ���������� � ���������� ����� ��������

                event->ignore();
                break;
            case QMessageBox::Discard:
                // ������� �� ��������
                event->accept();
                break;
            case QMessageBox::Cancel:
                // ���������� ����� ��������
                event->ignore();
                break;
            default:
                // �� ������ ������� ����������, �� �� ������ ������ ������� ������������� ������
                event->ignore();
                break;
        }
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
    // �������� ���������� �����
    return false;
}

