#include "AdvRoom.h"
#include "AdvObject.h"
#include "AdvMotionTableEntry.h"

AdvRoom::AdvRoom()
{
    beenVistied = false;
    roomNumber = 0;
    roomName = " ";
}

bool AdvRoom::readRoom(ifstream &roomFile)
{
    if(!roomFile.is_open())
    {
        cout << "File not opened" << endl;
        return false;
    }

    if(roomFile.eof())
    {
        cout << "End of file" << endl;
        return false;
    }

    string line;
    getline(roomFile, line);

    while(line == " " || line == "\r")
    {
        getline(roomFile, line);
    }

    roomNumber = stoi(line);

    if(roomNumber <= 0)
    {
        cout << "Room number is less than 0" << endl;
        return false;
    }
    getline(roomFile, line);
    roomName = line;
    if(roomName.back() == '\r')
        roomName = roomName.substr(0, roomName.size() - 1);

    while(line != "-----\r")
    {
        getline(roomFile, line);
        roomDescr.push_back(line);
    }

    //gets rid of -----
    roomDescr.pop_back();

    //temp variables to hold room information for MotionTable
    string motionDirection = "";
    string motionKeys = "";    //initialized for when there is no keys
    int motionDestinationRoom ; // because the room can't be 0

    getline(roomFile, line);

    while(line != " " && line != "\r")
    {
        stringstream breakUp(line);
        if(breakUp)
        {
            breakUp >> motionDirection >> motionDestinationRoom;
            if(motionDirection.back() == '\r')
                motionDirection = motionDirection.substr(0, motionDirection.size() - 1);
        }

        if(breakUp) {
            breakUp >> motionKeys;
            if(motionKeys.back() == '\r')
                motionKeys = motionKeys.substr(0, motionKeys.size() - 1);
            AdvMotionTableEntry motion(motionDirection, motionDestinationRoom, motionKeys);
            motionKeys="";
            motionTable.push_back(motion);
        }
        else {
            AdvMotionTableEntry motion(motionDirection, motionDestinationRoom);
            motionTable.push_back(motion);
        }

        getline(roomFile, line);
        if(roomFile.eof())
            return false;
    }

    return true;
}

vector<string> AdvRoom::getDescription()
{
    return roomDescr;
}

string AdvRoom::getName()
{
    return roomName;
}

void AdvRoom::addObject(AdvObject obj)
{
    // This function should add the obj to the room.
    // It however, should not add the object to the room
    // if the room already contains the object.
    for(int i = 0; i < objectsList.size(); i++)
    {
        if(objectsList[i] == obj)
            return;
    }
    objectsList.push_back(obj);
}

AdvObject AdvRoom::removeObject(string objName)
{
    // This function should remove the object with objName.
    int removingIndex;
    AdvObject obj;
    for(int i = 0; i < objectsList.size(); i++)
    {
        if(objectsList[i].getName()== objName)
        {
            removingIndex = i;
        }
    }
    obj = objectsList[removingIndex];
    objectsList.erase(objectsList.begin() + removingIndex);

    return obj;
}

bool AdvRoom::containsObject(string objName)
{
    // Returns true if object with objName is in the room.

    for(int i = 0; i < objectsList.size(); i++)
    {
       /* cout << objName << endl;

        for(int j = 0; j <= objName.size(); j++)
        {
            cout << int(objName[j]) << endl;
            cout <<"--\n" << int(objectsList[i].getName()[j]) << endl;
        }*/
        if(objectsList[i].getName() == objName)
        {

            return true;
        }
    }
    return false;
}

int AdvRoom::objectCount()
{
    return objectsList.size();
}

AdvObject AdvRoom::getObject(int index)
{
    return objectsList[index];
}

bool AdvRoom::hasBeenVisited()
{
    return beenVistied;
}

void AdvRoom::setVisited(bool flag)
{
    beenVistied = flag;
}

vector<AdvMotionTableEntry> AdvRoom::getMotionTable()
{
    return motionTable;
}

int AdvRoom::getRoomNumber()
{
    return roomNumber;
}
