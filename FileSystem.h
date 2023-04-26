#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include<QFile>

class FileSystem
{
public:
    FileSystem();
    void loadFile();
    void saveFile(QString& text);

private:
    void openFile();
    void read();
    void write(QString& text);

private:
    std::unique_ptr<QFile> file;
};

#endif // FILESYSTEM_H
