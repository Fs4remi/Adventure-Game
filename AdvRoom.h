#ifndef ADVROOM
#define ADVROOM

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "AdvObject.h"
#include "AdvMotionTableEntry.h"
using namespace std;

/**
* This class defines a single room in the Adventure game.  A room
* is characterized by the following properties:
*
*   - A room number, which must be greater than zero
*   - Its name, which is a one-line string identifying the room
*   - Its description, which is a line array describing the room
*   - A list of objects contained in the room
*   - A flag indicating whether the room has been visited
*   - A motion table specifying the exits and where they lead
*
* The external format of the room file is described in the
* assignment handout.
*/

class AdvRoom
{
public:
    AdvRoom();
    bool readRoom(ifstream &roomFile);	   // Reads room data from an open file.
    // Returns true if successful.

    vector<string> getDescription();	   // Return the room description.
    string getName();					   // Returns the room name.

    void addObject(AdvObject obj);		   // Adds an object to the room.
    AdvObject removeObject(string objName);// Removes an object with name objName and returns the object.
    AdvObject getObject(int index);		   // Returns object index from the room.
    int objectCount();					   // Returns how many objects are in the room.
    bool containsObject(string objName);   // Return true if the room contains an object with objName.


    bool hasBeenVisited();		// Returns true if the room has been visited. False otherwise.
    void setVisited(bool flag); // Sets if the room has been visited.

    vector<AdvMotionTableEntry> getMotionTable();  // Returns a motion table for the room.
    int getRoomNumber();						   // Returns the room number.

private:
    // Enter the room properties here.
    bool beenVistied;
    int roomNumber;
    string roomName;
    vector<AdvObject> objectsList;
    vector<string> roomDescr;
    vector<AdvMotionTableEntry> motionTable;
};

#endif
