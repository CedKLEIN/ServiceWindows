# Windows Service

## Table of content
* [Description](#Description)
* [How to install](#How_to_install)
* [How to use](#How_to_use)
* [Bonus](#Bonus)

## Description
The software provides windows functionalities using the MDM bridge WMI.
It can be run at startup device and a msi setup is provided.

## How to install
There are two ways to execute the Windows Service.
- Use the executable *ServiceWindows/Executable/WindowsService.exe*
- Run the installer .exe or .msi in *ServiceWindows/Executable/Installer/WS_setup.*

## How to use
When you run the program, you will see a console interface :

![image](https://user-images.githubusercontent.com/66410614/138610198-e2a363bc-c6ce-4672-a198-bc337624ced8.png)

#### (1) - Does the program run when the computer starts up ?
This option will tell you in the program will run when you start your device.

#### (2) - Add the program to startup computer run list
Force the program to run automatically when you start your device.

#### (3) - Remove the program from startup computer run list
Remove the program from the run list. It won't run automatically when you start you device.

#### (4) - Display computer information
Display some computer data: operating system, battery and permanent address.

![image](https://user-images.githubusercontent.com/66410614/138563685-636e6135-afa9-4593-b4b8-1fd70c8ecdef.png)

#### (5) - Reboot the device
Allow to reboot the device.

/!\ However you cannot schedule a reboot if you don't have full user right.
Even running the app as administrator might not be enough.

That's why a tool is provided *ServiceWindows/Executable/Tools/PsExec.exe*.
To use it, use the following steps:
- Open a command console Prompt as administrator
- Go to tool directory : *cd Service_Windows/Executable/PSTools*
- Execute the command : *psexec.exe -i -s cmd.exe*
- It should open a new command prompt
- Then execute Windows Service software
- Choose to reboot the device and it should schedule a reboot

#### (0) - Exit
Exit the program.

## Bonus
The class MsiObject is not only provided read (GET) method using MDM class.
You also have write (PUT) method to allow camera, or digits in password for example.

However as for the GET method you need to have instance of those class in your user session.
You can check those instances using wbemtest software :

![image](https://user-images.githubusercontent.com/66410614/138610748-c72b7da3-f3d3-42fa-a1a6-cc1d88a5f027.png)
