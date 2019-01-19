#ifndef MOTION
#define MOTION

#include <iostream>
#include <string>
using namespace std;

class AdvMotionTableEntry
{
public:
    AdvMotionTableEntry(string dir, int room, string key);
    AdvMotionTableEntry(string dir, int room);

    int getDestinationRoom();
    string getDirection();
    string getKeyName();

private:
    string direction;
    int destinationRoom;
    string keyName;
};

#endif