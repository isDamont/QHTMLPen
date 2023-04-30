#include <QFileDialog>
#include "FileSystem.h"

//Возвращает количество записанных байт, если ошибка -1
qint64 FileSystem::saveFile(const QString& text)
{
    //Если объекта QFile не существует, создаём его
    if(!file)
    {
        //Если файл не создан не вызываем метод write иначе вылет
        if(!createFile())
            return writeErr;
    }
//
    return write(text);
}

//Возвращает количество записанных байт, если ошибка -1
qint64 FileSystem::saveAs(const QString &text)
{
    //Если файл не создан не вызываем метод write иначе вылет
    if(!createFile())
        return writeErr;

    return write(text);
}

//Метод создаёт новый объект QFile
bool FileSystem::createFile()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Сохранить файл",
    QDir::currentPath(), "All(*.*) ;; txt(*.txt)");

    if (!fileName.isEmpty())
    {
        //Освобождаем умный указатель для возможноти создания нового
        file.release();
        file = std::make_unique<QFile>(fileName);
        return true;
    }

    return false;
}

qint64 FileSystem::write(const QString& text)
{
    file->open(QFile::WriteOnly | QFile::Text);
    qint64 bytesWritten = file->write(text.toUtf8());
    file->close();

    return bytesWritten;
}
