#include "App.hpp"

App::App(const std::string& appName):
    _appName{appName}{}

bool App::isAppRunningAtStartUp(){
	LONG ln{RegGetValue(HKEY_CURRENT_USER,
        "SOFTWARE\\Microsoft\\Windows\\Currentversion\\Run",
        _appName.c_str(), RRF_RT_REG_SZ, 0, 0, 0)};

    return ln==ERROR_SUCCESS;
}

void App::removeAppFromRunList(){
    HKEY hkey{HKEY_CURRENT_USER};
    RegOpenKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\Currentversion\\Run", &hkey);
    RegDeleteValue(hkey,_appName.c_str());
    RegCloseKey(hkey);
}

void App::addAppToRunList(){
    char re[MAX_PATH];
	std::string pathApp{std::string(re, GetModuleFileName(nullptr, re, MAX_PATH))};
    HKEY hkey;
    LONG key{RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\Currentversion\\Run", 0, KEY_WRITE, &hkey)};
    if (key==ERROR_SUCCESS)
    {
        key = RegSetValueEx(hkey, _appName.c_str(), 0, REG_SZ, (BYTE*)pathApp.c_str(), strlen(pathApp.c_str()));
    }
}

void App::displayMenu() const{
    std::cout << "\n WINDOWS SERVICES !\n\n";
    std::cout << " (1) - Does the program run when the computer starts up ? \n";
    std::cout << " (2) - Add the program to startup computer run list \n";
    std::cout << " (3) - Remove the program from startup computer run list \n";
    std::cout << " (4) - Display computer information \n";
    std::cout << " (5) - Reboot the device \n";
    std::cout << " (0) - Exit \n";
}