#ifndef ADVOBJECTCOPY
#define ADVOBJECTCOPY

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

class AdvObject
{
public:
    AdvObject();
    AdvObject(string objName, string objDes, int loc);
    bool readObject(ifstream &objFile);
    bool operator==(const AdvObject& right);

    string getName();
    string getDescription();
    int getInitialLocation();

private:
    // Add your private variables here...
    string objectName;
    string objectDescription;
    int objectLocation;

};

#endif