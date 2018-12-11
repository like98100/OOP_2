#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include <conio.h>
#include <map>
#include <algorithm>

#include <iostream>
using namespace std;

enum class KeyCode
{
    None = 0,
    Backspace,
    Escape,
    Space,
    LeftArrow,
    RightArrow,
    UpArrow,
    DownArrow,
    A,
    D
};

class InputManager
{
    static int major;
    static int minor;

    static bool prefetch;

    static map<KeyCode, pair<int, int>> keyCodeTable;

public:
    InputManager() {}

    static bool GetKeyDown(KeyCode keyc)
    {
        if (!prefetch)
        {
            if (_kbhit())
            {
                major = _getch();
                if (major == 0 || major == 224) {
                    minor = _getch();
                }
            }
            cout << "major :: " << major << ", minor ::" << minor << endl;
            prefetch = true;
        }

        auto res = keyCodeTable[keyc];

        return(res.first == major && res.second == minor);
    }


    static void endOffFrame()
    {
        prefetch = false;
        major = -1;
        minor = 0;
    }
};

int InputManager::major = -1;
int InputManager::minor = 0;
bool InputManager::prefetch = false;
map<KeyCode, pair<int,int>> InputManager::keyCodeTable = {
    {KeyCode::None ,{-1, 0} }, 
    {KeyCode::Escape ,{27, 0} },
    {KeyCode::Space ,{ ' ', 0 } },
    {KeyCode::LeftArrow ,{ 224, 75 } },
    {KeyCode::RightArrow ,{ 224, 77 } },
    {KeyCode::UpArrow ,{ 224, 72 } },
    {KeyCode::DownArrow ,{ 224, 80 } },
};
#endif