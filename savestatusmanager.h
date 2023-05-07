
#ifndef SAVESTATUSMANAGER_H
#define SAVESTATUSMANAGER_H

#include <vector>

using _index = unsigned short;


class SaveStatusManager
{
public:
    bool GetStatus(_index index) const;
    void SetStatusTo(_index index, bool status);
    void AddStatus(bool status);
    void RemoveStatus(_index index);

private:
    // для проверки сохранения изменений
    std::vector<bool> saveStatusVector{};
};

#endif // SAVESTATUSMANAGER_H
