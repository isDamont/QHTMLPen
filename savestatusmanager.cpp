
#include "savestatusmanager.h"



bool SaveStatusManager::GetStatus(_index index) const
{
    return saveStatusVector.at(index);
}

void SaveStatusManager::SetStatusTo(_index index, bool status)
{
    if(saveStatusVector.size() > index)
    {
        saveStatusVector[index] = status;
    }
    else
    {
        AddStatus(status);
    }
}

void SaveStatusManager::AddStatus(bool status)
{
    saveStatusVector.push_back(status);
}

void SaveStatusManager::RemoveStatus(_index index)
{
    if(saveStatusVector.size() <= index)
    {
        return;
    }

    saveStatusVector.erase(saveStatusVector.begin() + index);
}

