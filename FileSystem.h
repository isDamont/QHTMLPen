#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QFile>

class FileSystem
{
public:
    qint64 saveFile(const QString& text);
    qint64 saveAs(const QString& text);

private:
    void createFile();
    qint64 write(const QString& text);

private:
    std::unique_ptr<QFile> file;
};

#endif // FILESYSTEM_H
