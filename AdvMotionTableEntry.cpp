#include "AdvMotionTableEntry.h"

AdvMotionTableEntry::AdvMotionTableEntry(string dir, int room, string key)
{
    direction = dir;
    destinationRoom = room;
    keyName = key;
}

AdvMotionTableEntry::AdvMotionTableEntry(string dir, int room)
{
    direction = dir;
    destinationRoom = room;
}

int AdvMotionTableEntry::getDestinationRoom()
{
    return destinationRoom;
}

string AdvMotionTableEntry::getDirection()
{
    return direction;
}

string AdvMotionTableEntry::getKeyName()
{
    return keyName;
}
