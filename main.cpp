#include <iostream>

#include "src/MsiObject.hpp"
#include "src/App.hpp"

int main(int argc, char *argv[])
{
    try
    {
        MsiObject msi;
        App app{"WindowsService"};

        while(1)
        {
            app.displayMenu();

            char get{static_cast<char>(getch())};
            system("cls");
            std::cout << "\n => ";
            if (get == '1')
            {
                if(app.isAppRunningAtStartUp())
                    std::cout << "App is running at startup" << std::endl;
                else
                    std::cout << "App is NOT running at startup" << std::endl;
            }
            else if(get == '2')
            {
                if(!app.isAppRunningAtStartUp())
                {
                    app.addAppToRunList();
                    std::cout << "App is now running at startup" << std::endl;
                }
                else 
                    std::cout << "App is already running at startup" << std::endl;
            }
            else if(get == '3')
            {
                if(app.isAppRunningAtStartUp())
                {
                    app.removeAppFromRunList();
                    std::cout << "App is now NOT running at startup" << std::endl;
                }
                else 
                    std::cout << "App is already NOT running at startup" << std::endl;
            }
            else if(get == '4')
            {
                std::wcout << "Operating system : " << msi.getOS() << std::endl;
                std::cout << "Battery : " << msi.getBatteryAvailability() << "%" << std::endl;
                std::wcout << "Mac address : " << msi.getMacAddress() << std::endl; 
            }
            else if(get == '5')
            {
                msi.doReboot();
            }
            else if(get == '0')
            {
                return 0;
            }
        }
    }catch(char const* error)
    {
        std::cout << error << std::endl;
    }
    return 0;
}