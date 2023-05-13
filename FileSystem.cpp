#include <QFileDialog>
#include "FileSystem.h"
#include "DataStructures.h"

//Возвращает количество записанных байт, если ошибка -1
FileSystem::FileSystem()
    : file(std::make_unique<QFile>())
{
    fileExtensionMapInit();
}

qint64 FileSystem::saveFile(const QString& text)
{
    //Если объекта QFile не существует, создаём его
    if(!file->isOpen())
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

//Возвращает текст из файла
QString FileSystem::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Открыть файл",
        QDir::currentPath(), strFilter);

    if (!fileName.isEmpty())
    {
        file->setFileName(fileName);
        if (file->open(QFile::ReadOnly | QFile::WriteOnly | QFile::ExistingOnly))
        {
            QTextStream stream(file.get());
            return stream.readAll();
        }
    }

    return nullptr;
}

//Метод создаёт новый объект QFile
bool FileSystem::createFile()
{
    QString strSelFilter="*.txt";

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Сохранить файл",
        QDir::currentPath(), strFilter, &strSelFilter );

    if (!fileName.isEmpty())
    {
        if(fileName.indexOf('.') == -1)
        {
            switch(fileExtension[strSelFilter])
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
                case FileExtension::JSON:
                    fileName += ".json";
                    break;
            }
        }

        file->setFileName(fileName);

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
    fileExtension["JSON(*.json)"] = FileExtension::JSON;
    fileExtension["ALL(*)"] = FileExtension::ALL;
}
