# Windows Service

## Table of content
* [Description](#Description)
* [How to install](#How to install)
* [How to use](#How to use)

## Description
The software provides windows functionalities using the MDM bridged WMI.
It can be run at startup device and a msi setup is provided.

## How to install
There are two way to use the Windows Service.
#### 1) Use the executable ServiceWindows/Executable/WindowsService.exe
#### 2) Use the installer exe ServiceWindows/Executable/Installer/setup.exe or the installer msi ServiceWindows/Executable/Installer/WS_setup.msi

## How to use
Run the program.

It is providing a console interface :
![image](https://user-images.githubusercontent.com/66410614/138563526-e995a46d-6e0a-4572-8852-57d22f1497ca.png)

#### (1) - Is app running at device startup ?
This option will tell you in the programm will run at startup.

#### (2) - Make app run app automatically at startup
Force the program to run automatically when you start you device.

#### (3) - Make app not run app automatically at startup
remove the program from the run list. It won't run automatically when you start you device.

#### (4) - Display computer information
Display some computer data: operating system, battery and permanent address.
![image](https://user-images.githubusercontent.com/66410614/138563685-636e6135-afa9-4593-b4b8-1fd70c8ecdef.png)

#### (5) - Reboot the device
Allow to rebbot the device.
###### /!\ 
However you cannot schedule a reboot if you don't have full user right.
Even running the app as administrator might be not enough.

That's why a tool is provided ServiceWindows/Executable/Tools/PsExec.exe
To use it, use the following step:
- Open a commande console Prompt as administrator
- Go to your tool executable directory : cd Service_Windows/PSTools
- Execute the command : psexec.exe -i -s cmd.exe
- It should open a new command prompt.
- Then execute Windows Service software
- Choose to reboot the device and it should schedule a reboot

 #### (0) - Exit
 Exit the program
