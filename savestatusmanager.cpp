
#include "savestatusmanager.h"

#include <qDebug>

SaveStatusManager::SaveStatusManager()
{
}

SaveStatusManager::~SaveStatusManager()
{
    saveStatusVector.clear();
}

bool SaveStatusManager::GetStatus(int index) const
{
    return saveStatusVector.at(index);
}

void SaveStatusManager::SetStatusTo(int index, bool status)
{
    if(saveStatusVector.size() > index)
    {
        saveStatusVector.at(index) = status;
    }
    else
    {
        AddStatus(index, status);
    }
}

void SaveStatusManager::AddStatus(int index, bool status)
{
    if(index >= saveStatusVector.size())
    {
        saveStatusVector.resize(index + 1);
        saveStatusVector.at(index) = status;
    }
    else
    {
        saveStatusVector.insert(saveStatusVector.begin() + index, status);
    }
}

void SaveStatusManager::RemoveStatus(int index)
{
    if(saveStatusVector.size() <= index)
    {
        return;
    }

    saveStatusVector.erase(saveStatusVector.begin() + index);
}

