#include "AdvObject.h"

AdvObject::AdvObject()
{
    objectName = "";
    objectDescription = "";
    objectLocation = 0;
}

AdvObject::AdvObject(string objName, string objDes, int loc)
{
    objectName = objName;
    objectDescription = objDes;
    objectLocation = loc;
}

bool AdvObject::readObject(ifstream &objFile)
{
    // True if able to read name,
    // description, and initial location.
    // Otherwise returns false.

//    if(!objFile.is_open() || !objFile.eof())
//        return false;
    /* getline(objFile, line);
     cout << int(line[0]) << endl;
     while(line == "" || line == "\r")
     {
         getline(objFile, line);
         if(objFile.eof())
         {
             return false;
         }

     }*/
    string line;
    getline(objFile,line);
    while (!objFile.eof()){
        if(line == "" || line == "\r")
        {
            getline(objFile,line);
        }
        else
        {
            if(line.back() == '\r')
            {
                line = line.substr(0, line.size() - 1);
            }

            objectName = line;

            getline(objFile, objectDescription);

            objFile >> objectLocation;
            objFile.ignore();
            return true;
        }
    }
    return false;
}

string AdvObject::getName()
{
    return objectName;
}

string AdvObject::getDescription()
{
    return objectDescription;
}

int AdvObject::getInitialLocation()
{
    return objectLocation;
}

bool AdvObject::operator==(const AdvObject &right)
{
    if(this->objectName == right.objectName )
    {
        return true;
    }
    else
        return false;
}