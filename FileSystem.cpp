#include"FileSystem.h"

FileSystem::FileSystem()
{
}

void FileSystem::loadFile()
{

}

void FileSystem::saveFile(QString& text)
{
    if(!file.get()->isOpen())
    {
        openFile();
        write(text);
        //Создать файл и вызвать функцию write();
    }


}

void FileSystem::openFile()
{

}

void FileSystem::read()
{

}

void FileSystem::write(QString& text)
{

}
