#pragma once

#include <iostream>

#define _WIN32_DCOM
#include <windows.h>
#include <Wbemidl.h>
#include <comdef.h>

# pragma comment(lib, "wbemuuid.lib")

class MsiObject{
public:
    virtual ~MsiObject();
    std::wstring getOS();
    int getBatteryAvailability();
    std::wstring getMacAddress();
    short isCameraEnable();
    short isDigitsPasswordEnable();
    short isSpecialCharacterPasswordEnable();
    short getMaxPINLenghtPassword();
    short getMinLenghtPassword();

    void setCamera(const short value);
    void setDigitsPassword(const short value);
    void setSpecialCharacterPassword(const short value);
    void setMaxPINLenghtPassword(const short value);
    void setMinLenghtPassword(const short value);

    void doReboot();

private:
    void putValueInProperty(const std::wstring& propertyName,
        const std::wstring& className,
        const std::wstring& domainName,
        const int& newValue);
        
    void getDataFromObject(IEnumWbemClassObject*& wbemEnumerator,
        const std::wstring& feature,
        VARIANT& var);

    void getValueInProperty(const std::wstring& propertyName,
        const std::wstring& className,
        const std::wstring& domainName,
        VARIANT& var);

    void initComAndWbem(const std::wstring& wmiNamespace);
    bool initializeCom() const;
    bool setUpWBEM(const std::wstring& wmiNamespace);
    void cleanUpMsi();
    IEnumWbemClassObject* execQuery(const std::wstring& query);
    IWbemLocator* _wbemLocator{nullptr};
    IWbemServices* _wbemServices{nullptr};
};