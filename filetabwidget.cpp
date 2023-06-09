#include "filetabwidget.h"

#include <QMessageBox>
#include <QTextEdit>

FileTabWidget::FileTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    timerToCheckStatus = std::make_unique<QTimer>(this);
    timerToCheckStatus->setInterval(std::chrono::seconds(1));

    // актуализация индекса текущей вкладки
    connect(this, &FileTabWidget::currentChanged, this, [=](int newIndex){
        currentIndex = newIndex;
    });

    if(timerToCheckStatus)
    {
        connect(timerToCheckStatus.get(), &QTimer::timeout, this, [=](){
            QTextEdit* currentTextEdit = qobject_cast<QTextEdit*>(currentWidget());
            if(currentTextEdit)
            {
                setTabIconStarVisibleTo(currentIndex, !compareData(lastSavedData.at(indexOf(currentTextEdit)), currentTextEdit->toPlainText()));
            }
        });

        timerToCheckStatus->setSingleShot(true);
        timerToCheckStatus->start();
    }
}

bool FileTabWidget::areAllTabsSaved()
{
    for(uint index = 0; index < lastSavedData.size(); index++)
    {
        QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(widget(index));
        if(!currentQTextEditWidget)
        {
            continue;
        }

        if(!compareData(lastSavedData.at(index), currentQTextEditWidget->toPlainText()))
        {
            return false;
        }
    }

    return true;
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

bool FileTabWidget::compareData(const QString &buffer, const QString &data)
{
    // сначала сравниваем размер
    if(buffer.size() != data.size())
    {
        return false;
    }

    // берём итераторы с конца
    QString::const_iterator bufferIter = buffer.cbegin();
    QString::const_iterator dataIter = data.cbegin();

    while (bufferIter != buffer.cend() && dataIter != data.cend())
    {
        if(*bufferIter != *dataIter)
        {
            return false;
        }

        bufferIter++;
        dataIter++;
    }

    return true;
}

bool FileTabWidget::doWithoutSaving(const QString &textResponse)
{
    // вызов диалогового окна
    QMessageBox askSave(this);
    askSave.setText(tr("Изменения не сохранены!"));
    askSave.setInformativeText(textResponse);
    askSave.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    askSave.setDefaultButton(QMessageBox::Ok);
    askSave.setWindowModality(Qt::ApplicationModal);

    switch (askSave.exec()) {
    case QMessageBox::Ok :
        return true;
    case QMessageBox::Cancel :
        return false;
    default:
        return false;
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

    //текущее название вкладки
    QString fileName = tabText(currentIndex);
    // если при сохранении вернётся ошибка, то мы выходим не меняя статуса
    if(fileSystem.at(currentIndex)->saveFile(text) == writeErr)
    {
        return;
    }

    fileName = fileSystem.at(currentIndex)->getFileName();
    setTabText(currentIndex, fileName);
    //меняем контрольный буфер
    lastSavedData.at(indexOf(currentQTextEditWidget)) = text;
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
  
    //меняем контрольный буфер
    lastSavedData.at(indexOf(currentQTextEditWidget)) = text;

    QString fileName ="Новая вкладка";
     // если при сохранении вернётся ошибка, то мы выходим не меняя статуса
    if(fileSystem.at(currentIndex)->saveAs(text) == writeErr)
    {
        return;
    }

    fileName = fileSystem.at(currentIndex)->getFileName();
    //меняем имя вкладки
    setTabText(currentIndex, fileName);
  
    // убираем звёздочку
    setTabIconStarVisibleTo(currentIndex, false);
}

void FileTabWidget::slotCloseCurrentTab()
{
    // проверяем индекс
    if(currentIndex >= 0)
    {
        QTextEdit* currentQTextEditWidget = qobject_cast<QTextEdit*>(currentWidget());
        // на всякий случай делаем проверку указателя
        if(currentQTextEditWidget)
        {
            if(!compareData(lastSavedData.at(currentIndex), currentQTextEditWidget->toPlainText()))
            {
                // проверка на сохранение файла
                // запрос на закрытие без сохранения
                if(!doWithoutSaving(tr("Хотите закрыть вкладку без сохранения?")))
                {
                    // если нажали "Отмена", то ничего не делвем
                    return;
                }
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

    QTextEdit *textEdit = qobject_cast<QTextEdit*>(widget(index));

    // делаем проверку указателя
    if(textEdit)
    {
      // сохраняем сохраннённые данные для сверки
        lastSavedData.insert(lastSavedData.begin() + index, textEdit->toPlainText());

         // откладываем проверку сохранения
        connect(textEdit, &QTextEdit::textChanged, this, [=](){
            if(timerToCheckStatus)
            {
                timerToCheckStatus->start();
            }
        });
    }

    setCurrentIndex(index);

    // создаём экземпляр класса для FileSystem для новой вкладки и добавляем его в вектор с тем-же индексом
    fileSystem.insert(fileSystem.cbegin() + index, std::make_unique<FileSystem>());
}

void FileTabWidget::tabRemoved(int index)
{
    // вызываем базовую реализацию
    QTabWidget::tabRemoved(index);

    // удаляем контрольный буфер
    lastSavedData.erase(lastSavedData.begin() + index);

    // удаляем экземпляр классы filesystem для удалённой вкладки
    fileSystem.erase(fileSystem.begin() + index);

    // подаём сигнал об удалении вкладки
    emit signalTabRemoved();
}

void FileTabWidget::slotOpen()
{
    qDebug() << "slotOpen";
  
    QString fileName = "Новая вкладка";

    // создаём новый экземпляр класса FileSystem для открытия нового файла
    std::unique_ptr<FileSystem> newFileSystem = std::make_unique<FileSystem>();
  
    // буффер для записи содержимого
    QString fileText;

    // если не удалось открыть, то можно выходить
    if(!newFileSystem->openFile(fileText))
    {
        return;
    }

    fileName = newFileSystem->getFileName();
    int newTabIndex = addTab(new QTextEdit(fileText, this), fileName);

    // перемещаем используемый экземпляр класса FileSystem в вектор с индексом созданной вкладки
    fileSystem.at(newTabIndex) = std::move(newFileSystem);
}
