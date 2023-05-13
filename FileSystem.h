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
    QString openFile();

private:
    bool createFile();
    qint64 write(const QString& text);
    void fileExtensionMapInit();

private:
    std::unique_ptr<QFile> file;
    std::unordered_map<QString, FileExtension> fileExtension;
    QString const strFilter = "ALL(*) ;; TXT(*.txt) ;; HTML(*.html) ;; CSS(*.css) ;;\
            JS(*.js) ;; PHP(*.php) ;; JSON(*.json)";
};

#endif // FILESYSTEM_H
