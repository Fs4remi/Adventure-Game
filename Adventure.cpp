#include "Adventure.h"

/*
* File: Adventure.cpp
* --------------------
* This program plays the Adventure game.
*/
Adventure::Adventure(){}

Adventure::Adventure(string objfile, string rmfile, string cmdfile)
{
    // Setup of the Adventure game using some files.

    currRoomInd = 1;

    LoadRooms(rmfile);
    LoadObjects(objfile);
    LoadSynonyms(cmdfile);
}

void Adventure::Play()
{
    while (currRoomInd != 0)
    {
        string cmd, objName;
        if(roomsVect[currRoomInd-1].hasBeenVisited())
        {
            cout << roomsVect[currRoomInd-1].getName() << endl;
        }
        else
        {
            print();
        }

        if(ForcedCmd())
        {
            roomsVect[currRoomInd-1].setVisited(false);
            MotionCmd("FORCED");
            continue;
        }

        GetUserCmd(cmd, objName);
        if (cmd == "QUIT")
        {
            QuitCmd();
            cout << "Goodbye!" << endl;
            return;
        }
        else if (cmd == "HELP")
        {
            HelpCmd();
        }
            // The rest of the commands go here.
        else if (cmd == "INVENTORY")
        {
            InventoryCmd();
        }
        else if (cmd == "LOOK")
        {
            LookCmd();
        }
        else if (cmd == "DROP")
        {
            DropCmd(objName);
        }
        else if (cmd == "TAKE")
        {
            TakeCmd(objName);
        }
        else if (cmd == "DROP")
        {
            DropCmd(objName);
        }
        else
        {
            MotionCmd(cmd);
        }
    }
    cout << "Goodbye!" << endl;
}

void Adventure::InventoryCmd()
{
    if(playerInventory.objectCount() < 1)
    {
        cout << "You are not holding anything." << endl;
    }
    else
    {
        for(int i =0; i < playerInventory.objectCount();i++)
        {
            cout << playerInventory.getObject(i).getDescription() << endl;
        }
    }
}
void Adventure::GetUserCmd(string &verb, string &obj)
{
    string cmdOrg = verb;

    cout << "> ";
    string line;
    getline(cin, line);

    // Add code here to figure out the verb and object from the line
    stringstream breakUp(line);
    breakUp >> cmdOrg >> obj;

    obj = GetSynonym(obj);
    verb = GetSynonym(cmdOrg);
}

bool Adventure::ForcedCmd()
{
    for(auto i: roomsVect[currRoomInd-1].getMotionTable())
    {
        if(i.getDirection() == "FORCED")
        {
            return true;
        }
    }
    return false;
}
int Adventure::MotionCmd(string motion)
{
    // Get the motion table of the room number where the player is currently.
    // For each table entry, check to see if there is an entry that matches
    // "motion".  If the entry matches, check if the motion requires
    // a key and if the player has the has the key. A successful match
    // moves the player into the destination room.

    vector<AdvMotionTableEntry> tempMotionTable;
    tempMotionTable = roomsVect[currRoomInd-1].getMotionTable();

    for(int i = 0; i < tempMotionTable.size(); i++)
    {
        if(tempMotionTable[i].getDirection() == motion)
        {
            if(tempMotionTable[i].getKeyName() != "")
            {
                string specialKey = tempMotionTable[i].getKeyName();
                if(playerInventory.containsObject(specialKey))
                {
                    return currRoomInd = tempMotionTable[i].getDestinationRoom();
                }
            }
            else
            {
                return currRoomInd = tempMotionTable[i].getDestinationRoom();
            }
        }
    }
    return -1;
}
void Adventure::LookCmd()
{/*
    for(string line: roomsVect[currRoomInd-1].getDescription())
    {
        cout << line << endl;
    }*/
    roomsVect[currRoomInd-1].setVisited(false);
}
void Adventure::print()
{
    //cout << roomsVect[currRoomInd-1].getName() << endl;
    for(string line: roomsVect[currRoomInd-1].getDescription())
    {
        cout << line << endl;
    }
    cout << endl;
    for(int i = 0; i < roomsVect[currRoomInd-1].objectCount(); i++)
    {
        cout << "There is ";
        cout << roomsVect[currRoomInd-1].getObject(i).getDescription() << endl;
    }
    roomsVect[currRoomInd-1].setVisited(true);
}
void Adventure::TakeCmd(string object)
{
    if(roomsVect[currRoomInd-1].containsObject(object))
    {
        playerInventory.addObject(roomsVect[currRoomInd-1].removeObject(object));
        cout << "Added to inventory." << endl;
    }
    else
    {
        cout << "The object you said is not in the current room." << endl;
        return;
    }
}
void Adventure::DropCmd(string object)
{
    //AdvObject AdvRoom::removeObject(string objName)
    if(playerInventory.containsObject(object))
    {
        roomsVect[currRoomInd-1].addObject(playerInventory.removeObject(object));
        cout << "Dropped the item in the room." << endl;
    }
    else
    {
        cout << "You don't have the object in your inventory." << endl;
    }
}

void Adventure::LoadObjects(string filename)
{
    // Should load all the objects from a file.
    ifstream objectFile;
    objectFile.open(filename);

    if(!objectFile.is_open())
    {
        cout << "Objects file is not open" << endl;
        return;
    }
    while(!objectFile.eof())
    {
        AdvObject object;
        if(object.readObject(objectFile))
        {
            roomsVect[object.getInitialLocation()-1].addObject(object);
        }

            //objectsVect.push_back(object);
    }
    objectFile.close();
}

void Adventure::LoadRooms(string filename)
{
    // Should load all rooms from a file
    ifstream roomFile;
    roomFile.open(filename);

    if(!roomFile.is_open())
    {
        cout << "Rooms file is not open" << endl;
        return;
    }

    while(!roomFile.eof())
    {
        AdvRoom room;
        if(room.readRoom(roomFile))
            roomsVect.push_back(room);
    }
    roomFile.close();
}

void Adventure::LoadSynonyms(string filename)
{
    ifstream commandFile;
    commandFile.open(filename);

    if(!commandFile.is_open())
    {
        cout << "Synonym file is not open." << endl;
        return;
    }

    string tempWord;
    string tempSyn;
    int i = 0;

    while((commandFile >> tempWord >> tempSyn))
    {
        synonyms.push_back(Synonym());
        synonyms[i].word = tempWord;
        synonyms[i].synonym = tempSyn;
        i++;
    }
}

/*
 * Returns a synonym if one exists.  Otherwise returns original word.
 */
string Adventure::GetSynonym(string word)
{
    ConvertToUpper(word);
    for(int i = 0; i < synonyms.size(); i++)
    {
        if(synonyms[i].word == word)
        {
            return synonyms[i].synonym;
        }
    }
    return word;
}

vector<AdvRoom> Adventure::getRoomsVect()
{
    return roomsVect;
}

vector<AdvObject> Adventure::getObjectsVect()
{
    return objectsVect;
}
void Adventure::QuitCmd()
{
    // Ask if the uses would like to quit.  Should only take a yes or no.
    while (true) {
        string ans;
        cout << "Are you sure you want to quit now? ";
        getline(cin, ans);
        ConvertToUpper(ans);
        if (ans == "Y" || ans == "YES") {
            currRoomInd = 0;
            break;
        }
        if (ans == "N" || ans == "NO") {
            break;
        }
        cout << "Please answer yes or no." << endl;
    }
}

void Adventure::HelpCmd()
{
    cout << "Welcome to Adventure!" << endl;
    cout << "Somewhere nearby is Colossal Cave, where others have found fortunes in" << endl;
    cout << "treasure and gold, though it is rumored that some who enter are never" << endl;
    cout << "seen again. Magic is said to work in the cave.I will be your eyes" << endl;
    cout << "and hands. Direct me with natural English commands; I don't understand" << endl;
    cout << "all of the English language, but I do a pretty good job." << endl << endl;

    cout << "It's important to remember that cave passages turn a lot, and that" << endl;
    cout << "leaving a room to the north does not guarantee entering the next from" << endl;
    cout << "the south, although it often works out that way. You'd best make yourself" << endl;
    cout << "a map as you go along." << endl << endl;

    cout << "Much of my vocabulary describes places and is used to move you there." << endl;
    cout << "To move, try words like IN, OUT, EAST, WEST, NORTH, SOUTH, UP, or DOWN." << endl;
    cout << "I also know about a number of objects hidden within the cave which you" << endl;
    cout << "can TAKE or DROP.To see what objects you're carrying, say INVENTORY." << endl;
    cout << "To reprint the detailed description of where you are, say LOOK.If you" << endl;
    cout << "want to end your adventure, say QUIT." << endl;
}
