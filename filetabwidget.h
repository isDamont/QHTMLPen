#ifndef FILETABWIDGET_H
#define FILETABWIDGET_H

#include "FileSystem.h"
#include <QTabWidget>
#include <QObject>
#include <QWidget>
#include <vector>
#include <QTimer>



class FileTabWidget : public QTabWidget
{
    Q_OBJECT

public slots:
    void slotSaveCurrentTab();
    void slotSaveCurrentTabAs();
    void slotCloseCurrentTab();
    void slotOpen();

signals:
    // сигнал при удалении вкладки
    void signalTabRemoved();

public:
    FileTabWidget(QWidget *parent = nullptr);
    // проверка статуса всех вкладок
    bool areAllTabsSaved();
    // игнорирование вопроса о сохранении изменений
    bool doWithoutSaving(const QString& textResponse);

protected:
    // переопределяем для наших задач
    void tabInserted(int index) override;
    void tabRemoved(int index) override;

private:
    // отображения звёздочки взависимости от статуса
    void setTabIconStarVisibleTo(int index, bool visible);

private:
//    // для проверки сохранения изменений
//    std::vector<bool> saveStatusVector{};
    // для хранения последних сохраннёных данных
    std::vector<QString> lastSavedData{};
    // текущий индекс вкладки, чтобы не вызывать методы для его определения
    int currentIndex{};
    // умныйуказатель на менеджер записи/чтения чтобы не удалять вручную
    std::unique_ptr<FileSystem> fileSystem = nullptr;
    // проверка на соответствие сохпанённому тексту
    bool compareData(const QString& buffer, const QString& data);
    // таймер для установки задержки проверки сохранения
    std::unique_ptr<QTimer> timerToCheckStatus = nullptr;
};

#endif // FILETABWIDGET_H
