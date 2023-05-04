#include <QFileDialog>
#include "FileSystem.h"
#include "DataStructures.h"

//Возвращает количество записанных байт, если ошибка -1
FileSystem::FileSystem()
{
    fileExtensionMapInit();
}

qint64 FileSystem::saveFile(const QString& text)
{
    //Если объекта QFile не существует, создаём его
    if(!file)
    {
        //Если файл не создан не вызываем метод write иначе вылет
        if(!createFile())
            return writeErr;
    }

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
    QString strFilter="*.txt";

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Сохранить файл",
        QDir::currentPath(), "TXT(*.txt) ;; HTML(*.html) ;; CSS(*.css) ;;\
        JS(*.js) ;; PHP(*.php) ;; ALL(*.*)", &strFilter );

    if (!fileName.isEmpty())
    {
        //Освобождаем умный указатель для возможноти создания нового
        file.release();

        switch(fileExtension[strFilter])
        {
            case FileExtension::ALL:
                break;
            case FileExtension::TXT:
                fileName += ".txt";
                break;
            case FileExtension::HTML:
                fileName += ".html";
                break;
            case FileExtension::CSS:
                fileName += ".css";
                break;
            case FileExtension::JS:
                fileName += ".js";
                break;
            case FileExtension::PHP:
                fileName += ".php";
                break;
        }

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

void FileSystem::fileExtensionMapInit()
{
    fileExtension["TXT(*.txt)"] = FileExtension::TXT;
    fileExtension["HTML(*.html)"] = FileExtension::HTML;
    fileExtension["CSS(*.css)"] = FileExtension::CSS;
    fileExtension["JS(*.js)"] = FileExtension::JS;
    fileExtension["PHP(*.php)"] = FileExtension::PHP;
    fileExtension["ALL(*.*)"] = FileExtension::ALL;
}
