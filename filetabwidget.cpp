#include "filetabwidget.h"

#include <QMessageBox>
#include <QTextEdit>

FileTabWidget::FileTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    fileSystem = std::make_unique<FileSystem>();

    // актуализация индекса текущей вкладки
    connect(this, &FileTabWidget::currentChanged, this, [=](int newIndex){
        currentIndex = newIndex;
    });
}

bool FileTabWidget::areAllTabsSaved()
{
    bool allSaved = true;

    for(const bool &isSaved : saveStatusVector)
    {
        allSaved &= isSaved;
    }

    return allSaved;
}

void FileTabWidget::setTabIconStarVisibleTo(int index, bool visible)
{
    QString tabText = this->tabText(index);

    if(*(tabText.end() - 1) != '*' && visible)
    {
        tabText.push_back('*');
        setTabText(index, tabText);
    }
    else if(*(tabText.end() - 1) == '*' && !visible)
    {
        tabText.erase(tabText.end() - 1);
        setTabText(index, tabText);
    }
}

void FileTabWidget::slotSaveCurrentTab()
{
    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(currentWidget());

    if(!currentQTextEditWidget)
    {
        // на всякий случай делаем проверку указателя
        return;
    }

    QString text = currentQTextEditWidget->toPlainText();

    // если при сохранении вернётся ошибка, то мы выходим не меняя статуса
    if(fileSystem->saveFile(text) == writeErr)
    {
        return;
    }

    //меняем статус вкладки
    saveStatusVector.at(currentIndex) = true;
    // убираем звёздочку
    setTabIconStarVisibleTo(currentIndex, false);
}

void FileTabWidget::slotSaveCurrentTabAs()
{
    QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(currentWidget());

    if(!currentQTextEditWidget)
    {
        // на всякий случай делаем проверку указателя
        return;
    }

    QString text = currentQTextEditWidget->toPlainText();

    // если при сохранении вернётся ошибка, то мы выходим не меняя статуса
    if(fileSystem->saveAs(text) == writeErr)
    {
        return;
    }

    //меняем статус вкладки
    saveStatusVector.at(currentIndex) = true;
    // убираем звёздочку
    setTabIconStarVisibleTo(currentIndex, false);
}

void FileTabWidget::slotCloseCurrentTab()
{
    // проверяем индекс
    if(currentIndex >= 0){

        if(!saveStatusVector.at(currentIndex)){  // проверка на сохранение файла
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

        currentWidget()->close();   // закрытие виджета
        removeTab(currentIndex);    // закрытие вкладки
    }
}

void FileTabWidget::tabInserted(int index)
{
    // вызываем базовую реализацию
    QTabWidget::tabInserted(index);

    // вставляем новый статус
    saveStatusVector.insert(saveStatusVector.begin() + index, true);

    QTextEdit *textEdit = qobject_cast<QTextEdit*>(widget(index));

    // делаем проверку указателя
    if(textEdit)
    {
        // меняем статус при изменениях текста
        connect(textEdit, &QTextEdit::textChanged, this, [=](){
            saveStatusVector.at(indexOf(textEdit)) = false;
            setTabIconStarVisibleTo(indexOf(textEdit), true);
        });
    }

    setCurrentIndex(index);
}

void FileTabWidget::tabRemoved(int index)
{
    // вызываем базовую реализацию
    QTabWidget::tabRemoved(index);

    // удаляем статус
    saveStatusVector.erase(saveStatusVector.begin() + index);

    // подаём сигнал об удалении вкладки
    emit signalTabRemoved();
}

void FileTabWidget::slotOpen()
{
    qDebug() << "slotOpen";

    // сначала пытаемся откыть файл
    QString fileText = fileSystem->openFile();

    // усли нет текста, значит не открыли и можно выходить
    if(fileText == nullptr)
    {
        return;
    }

    // получаем индекс новой вкладки
    int index = addTab(new QTextEdit(this), "Файл открыли");

    QTextEdit *textEdit = qobject_cast<QTextEdit*>(widget(index));
    if(textEdit != nullptr)
        textEdit->setPlainText(fileText);

    // кастыль) так как у нас сработает сигнал textchanged() после setPlainText()
    saveStatusVector.at(index) = true;
    setTabIconStarVisibleTo(index, false);
}
