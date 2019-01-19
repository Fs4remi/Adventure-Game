
#include <iostream>
#include <fstream>
#include <string>
#include "Adventure.h"

using namespace std;

bool GetYesNo(string prompt);
void DisplayMenu();
int GetChoice(int startVal, int endVal);
bool AskContinue();		// May be useful to slow things down.

void TestAddingObjects(vector<AdvRoom> &rooms);
void TestRemovingObjects(vector<AdvRoom> &rooms);
void TestAdvRoom();
void CheckMotionTable(AdvRoom room);
void CheckRoomObjects(AdvRoom room);
void DisplayRooms(vector<AdvRoom> rooms);
void TestAdvObject();
void TestGame();

enum { DEBUG_OBJ, DEBUG_RM, PLAY, QUIT };

/*
 * The main is complete. You do not need to create any code for this file.
 * You may find it convenient to modify the code while debugging.
 */
int main()
{
    //int choice = PLAY;
    while (true)
    {
        DisplayMenu();
        int choice = GetChoice(1,4) - 1;
        cout << endl;
        // Sometimes it's useful to hardcode choice to save time while debugging...
        // int choice = 3;
        switch (choice)
        {
            case DEBUG_OBJ:
                TestAdvObject();
                break;
            case DEBUG_RM:
                TestAdvRoom();
                break;
            case PLAY:
                TestGame();
                break;
            case QUIT:
                cout << "Goodbye!";
                return 0;
        }
    }

    return 0;
}


/*
 * TestAdvRoom
 * -----------
 * Test the loading of the rooms and the add/remove object functionality.
 */
void TestAdvRoom()
{
    cout << "AdvRoom Testing" << endl;
    cout << "=====================================" << endl;
    cout << "Assumes AdvObjects is working." << endl << endl;

    vector<AdvRoom> rooms;
    ifstream fileRms;
    fileRms.open("SmallRooms.txt");
    while (true) {
        AdvRoom room;
        if (room.readRoom(fileRms)) // Read room
            rooms.push_back(room);  // Add to vector
        else
            break;	// Nothing else left to read
    }

    cout << "Before Adding Objects" << endl;
    cout << "-------------------------------" << endl;
    DisplayRooms(rooms);

    TestAddingObjects(rooms);
    DisplayRooms(rooms);

    TestRemovingObjects(rooms);
    DisplayRooms(rooms);
}


/*
 * TestRemovingObjects
 * -------------------
 * Remove objects to each room. If the room index is n then n objects are removed.
 * Reports an error if the number of objects doesn't match the expected count of 0.
 */
void TestRemovingObjects(vector<AdvRoom> &rooms) {
    cout << endl;
    cout << "After Deleting Objects" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "There should be no items in any of the rooms." << endl << endl;
    for (int i = 0; i < rooms.size(); i++) {
        // Add a objects to the room based on the room number. Testing purpose only.
        cout << "Removing Objects from " << rooms[i].getName() << "... ";
        for (int j = 0; j < rooms[i].getRoomNumber(); j++) {
            rooms[i].removeObject("Object " + to_string(j));
        }
        if (rooms[i].objectCount() != 0) {
            cout << "<-------------------------------------------- Error removing objects!!!" << endl;
        }
        else
            cout << "Removed Objects Successfully" << endl;
    }
}


/*
 * TestAddingObjects
 * -----------------
 * Add objects to each room. If the room index is n then n objects are added.
 * Reports an error if the number of objects doesn't match the expected count.
 */
void TestAddingObjects(vector<AdvRoom> &rooms) {
    cout << endl;
    cout << "After Adding Objects" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Room 0 should have 0 items, Room 1 should have 1 items, ... " << endl << endl;
    for (int i = 0; i < rooms.size(); i++) {
        // Add a objects to the room based on the room number. Testing purpose only.
        for (int j = 0; j < rooms[i].getRoomNumber(); j++) {
            AdvObject obj("Object " + to_string(j), "Test object " + to_string(j), 42);
            rooms[i].addObject(obj);
        }
        if (rooms[i].objectCount() != rooms[i].getRoomNumber()) {
            cout << "<-------------------------------------------- Error adding objects!!!" << endl;
        }
        else
            cout << "Objects added successfully" << endl;
    }
}


/*
 * DisplayRooms
 * ------------
 * Displays information about each room in the vector room.
 */
void DisplayRooms(vector<AdvRoom> rooms) {
    for (int i = 0; i < rooms.size(); i++) {
        cout << "Room " << i << ": " << rooms[i].getName() << endl;
        cout << "----------------------------------------" << endl;
        cout << "Rm Number: " << rooms[i].getRoomNumber() << endl << endl;
        CheckMotionTable(rooms[i]);
        CheckRoomObjects(rooms[i]);
        cout << endl;
    }
}


/*
 * CheckRoomObjects
 * ----------------
 * Prints out all the objects in a particular room.
 */
void CheckRoomObjects(AdvRoom room) {
    cout << endl;
    cout << "There are " << room.objectCount() << " objects in room " << room.getName() << ":" << endl;
    for (int i = 0; i < room.objectCount(); i++) {
        cout << "\t" << room.getObject(i).getName() << endl;
    }
}


/*
 * CheckMotionTable
 * ----------------
 * Prints out each entry in the motion table.
 */
void CheckMotionTable(AdvRoom room)
{
    vector<AdvMotionTableEntry> table = room.getMotionTable();
    cout << "\tMotion Table" << endl;
    cout << "\t---------------------" << endl;
    cout << "\tDir\tDest\tKey" << endl;
    for (int i = 0; i < table.size(); i++) {
        AdvMotionTableEntry motion = table[i];
        string key = motion.getKeyName();
        if (key.length() == 0) {
            key = "None";
        }
        cout << "\t" << motion.getDirection() << "\t" << motion.getDestinationRoom() << "\t" << key << endl;
    }
}


/*
 * TestAdvObject
 * -------------
 * Tests the reading of the objects file.
 */
void TestAdvObject()
{
    cout << "AdvObject Testing" << endl;
    cout << "============================================" << endl;
    cout << "This should be tested before room testing..." << endl << endl;
    vector<AdvObject> objects;
    ifstream fileObjs;
    fileObjs.open("SmallObjects.txt");	 // Try this one first.
    //fileObjs.open("CrowtherObjects.txt");  // Check after testing on small
    while (true) {
        AdvObject object;
        if (!object.readObject(fileObjs))
            break;
        objects.push_back(object);
    }

    cout << "Total Objects Read: " << objects.size() << endl << endl;

    for (int i = 0; i < objects.size(); i++) {
        cout << "Object " << i << ": " << objects[i].getName() << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Start Room: " << objects[i].getInitialLocation() << endl;
        cout << objects[i].getDescription() << endl << endl;
    }
    cout << endl;

}


/*
 * TestGame
 * --------
 * Uses the Adventure class to play the game.
 */
void TestGame() {
    while (true) {

        string gameName;
        cout << "Enter Game: ";
        getline(cin, gameName);
        cout << endl;

        Adventure game(gameName+"Objects.txt", gameName+"Rooms.txt", gameName+"Synonyms.txt");

//        Adventure game("SmallObjects.txt", "SmallRooms.txt", "SmallSynonyms.txt"); // Useful to hardcode for debugging

        game.Play();
        cout << endl;

        if (!GetYesNo("Would you like to play again? ")) {
            cout << "Thanks for playing." << endl;
            break;
        }

        cout << endl;
    }
}


/*
 * DisplayMenu
 * -----------
 * Show menu for options.
 */
void DisplayMenu()
{
    cout << "Choices:" << endl;
    cout << "1: Debug AdvObject" << endl;
    cout << "2: Debug AdvRoom (Debug after AdvObject is complete)" << endl;
    cout << "3: Play Adventure" << endl;
    cout << "4: Quit" << endl;
}


/*
 * GetChoice
 * ---------
 * Gets a choice between two values inclusive.
 */
int GetChoice(int startVal, int endVal)
{

    while (true) {
        int choice;
        cout << "> ";
        cin >> choice;
        cin.ignore();
        if (choice >= startVal || choice <= endVal) {
            return choice;
        }
        else {
            cout << "Please enter a choice between " << startVal << " and " << endVal << "." << endl;
        }
    }

    return 0;
}


/*
 * AskContinue
 * -----------
 * Waits for an enter to continue.
 */
bool AskContinue()
{
    string line;
    cout << "Press Enter to continue. Enter \"q\" to stop debugging." << endl;
    getline(cin, line);
    if (line == "q")
        false;

    return true;
}


/*
 * GetYesNo
 * --------
 * Gets a yes or no answer.
 */
bool GetYesNo(string prompt) {
    while (true) {
        cout << prompt;
        string answer;
        getline(cin, answer);
        ConvertToUpper(answer);
        if (answer == "Y" || answer == "YES")
            return true;
        else if (answer == "N" || answer == "NO")
            return false;
        else {
            cout << "Please answer yes or no." << endl;
        }
    }

    return false;
}