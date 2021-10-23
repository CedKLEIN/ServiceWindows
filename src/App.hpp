#pragma once

#include <windows.h>
#include <iostream>
#include <conio.h>

class App{
public:
    App(const std::string& appName);
    bool isAppRunningAtStartUp();
    void removeAppFromRunList();
    void addAppToRunList();
    void displayMenu() const;
    
private:
    std::string _appName;
};