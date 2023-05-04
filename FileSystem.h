#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QFile>

#define writeErr -1
enum class FileExtension;

class FileSystem
{
public:
    FileSystem();
    qint64 saveFile(const QString& text);
    qint64 saveAs(const QString& text);

private:
    bool createFile();
    qint64 write(const QString& text);
    void fileExtensionMapInit();

private:
    std::unique_ptr<QFile> file;
    std::unordered_map<QString, FileExtension> fileExtension;
};

#endif // FILESYSTEM_H
