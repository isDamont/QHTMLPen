#include <QFileDialog>
#include "FileSystem.h"

//Возвращает количество записанных байт, если ошибка -1
qint64 FileSystem::saveFile(const QString& text)
{
    //Если объекта QFile не существует, создаём его
    if(!file)
        createFile();

    return write(text);
}

//Возвращает количество записанных байт, если ошибка -1
qint64 FileSystem::saveAs(const QString &text)
{
    createFile();

    return write(text);
}

//Метод создаёт новый объект QFile
void FileSystem::createFile()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Сохранить файл",
    QDir::currentPath(), "All(*.*) ;; txt(*.txt)");

    if (!fileName.isEmpty())
    {
        //Освобождаем умный указатель для возможноти создания нового
        file.release();
        file = std::make_unique<QFile>(fileName);
    }
}

qint64 FileSystem::write(const QString& text)
{
    file->open(QFile::WriteOnly | QFile::Text);
    qint64 bytesWritten = file->write(text.toUtf8(), text.size());
    file->close();

    return bytesWritten;
}
