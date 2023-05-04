
#ifndef SAVESTATUSMANAGER_H
#define SAVESTATUSMANAGER_H

#include <vector>

class SaveStatusManager
{
public:
    SaveStatusManager();
    ~SaveStatusManager();
    bool GetStatus(int index) const;
    void SetStatusTo(int index, bool status);
    void AddStatus(int index, bool status);
    void RemoveStatus(int index);

private:
    // для проверки сохранения изменений
    std::vector<bool> saveStatusVector{};
};

#endif // SAVESTATUSMANAGER_H
