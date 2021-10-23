#include "MsiObject.hpp"

MsiObject::~MsiObject(){
    cleanUpMsi();
}

std::wstring MsiObject::getOS(){
    std::wstring os;
    VARIANT var;
    getValueInProperty(L"name",L"Win32_OperatingSystem",L"ROOT/CIMV2",var);
    os=var.bstrVal;
    VariantClear(&var);
    return os;
}

int MsiObject::getBatteryAvailability(){
    int availBattery{0};
    VARIANT var;
    getValueInProperty(L"EstimatedChargeRemaining",L"Win32_Battery",L"ROOT/CIMV2",var);
    availBattery=var.intVal;
    VariantClear(&var);
    return availBattery;
}

std::wstring MsiObject::getMacAddress(){
    std::wstring macAddress;
    VARIANT var;
    getValueInProperty(L"PermanentAddress",L"MSFT_NetAdapter",L"ROOT/StandardCimv2",var);
    macAddress=var.bstrVal;
    VariantClear(&var);
    return macAddress;
}

short MsiObject::isCameraEnable(){
    short cameraEnable;
    VARIANT var;
    getValueInProperty(L"AllowCamera",L"MDM_Policy_Result01_Camera02",L"Root/CIMv2/MDM/DMMap",var);
    cameraEnable=var.iVal;
    VariantClear(&var);
    return cameraEnable;
}

short MsiObject::isDigitsPasswordEnable(){
    short isPassword;
    VARIANT var;
    getValueInProperty(L"Digits",L"MDM_PassportForWork_PINComplexity03",L"Root/CIMv2/MDM/DMMap",var);
    isPassword=var.iVal;
    VariantClear(&var);
    return isPassword;
}

short MsiObject::isSpecialCharacterPasswordEnable(){
    short isPassword;
    VARIANT var;
    getValueInProperty(L"SpecialCharacters",L"MDM_PassportForWork_PINComplexity03",L"Root/CIMv2/MDM/DMMap",var);
    isPassword=var.iVal;
    VariantClear(&var);
    return isPassword;
}

short MsiObject::getMaxPINLenghtPassword(){
    short isPassword;
    VARIANT var;
    getValueInProperty(L"MaximumPINLength",L"MDM_PassportForWork_PINComplexity03",L"Root/CIMv2/MDM/DMMap",var);
    isPassword=var.iVal;
    VariantClear(&var);
    return isPassword;
}

short MsiObject::getMinLenghtPassword(){
    short isPassword;
    VARIANT var;
    getValueInProperty(L"MinDevicePasswordLength",L"MDM_Policy_Config01_DeviceLock02",L"Root/CIMv2/MDM/DMMap",var);
    isPassword=var.iVal;
    VariantClear(&var);
    return isPassword;
}

void MsiObject::setCamera(const short value){
    std::cout << "Camera allow : " << isCameraEnable() << std::endl;
    putValueInProperty(L"AllowCamera",L"MDM_Policy_Result01_Camera02",L"Root/CIMv2/MDM/DMMap",value);
    std::cout << "Camera allow : " << isCameraEnable() << std::endl;
}

void MsiObject::setDigitsPassword(const short value){
    std::cout << "Digits password allow : " << isDigitsPasswordEnable() << std::endl;
    putValueInProperty(L"Digits",L"MDM_PassportForWork_PINComplexity03",L"Root/CIMv2/MDM/DMMap",value);
    std::cout << "Digits password allow : " << isDigitsPasswordEnable() << std::endl;
}

void MsiObject::setSpecialCharacterPassword(const short value){
    std::cout << "Special character password allow : " << isSpecialCharacterPasswordEnable() << std::endl;
    putValueInProperty(L"SpecialCharacters",L"MDM_PassportForWork_PINComplexity03",L"Root/CIMv2/MDM/DMMap",value);
    std::cout << "Special character allow : " << isSpecialCharacterPasswordEnable() << std::endl;
}

void MsiObject::setMaxPINLenghtPassword(const short value){
    std::cout << "Max pin length password : " << getMaxPINLenghtPassword() << std::endl;
    putValueInProperty(L"MaximumPINLength",L"MDM_PassportForWork_PINComplexity03",L"Root/CIMv2/MDM/DMMap",value);
    std::cout << "Max pin length password : " << getMaxPINLenghtPassword() << std::endl;
}

void MsiObject::setMinLenghtPassword(const short value){
    std::cout << "Min length password : " << getMinLenghtPassword() << std::endl;
    putValueInProperty(L"MinDevicePasswordLength",L"MDM_Policy_Config01_DeviceLock02",L"Root/CIMv2/MDM/DMMap",value);
    std::cout << "Min length password : " << getMinLenghtPassword() << std::endl;
}

HRESULT putNewValueInInstance(IWbemClassObject* instance, BSTR property, unsigned int newValue)
{
    HRESULT hr{E_INVALIDARG};
    if (instance && property)
    {
        VARIANT var;
        VariantInit(&var);
        var.vt = VT_I4;
        var.intVal = newValue;
        hr = instance->Put(property, 0, &var, 0);
        VariantClear(&var);
    }

    return hr;
}

void MsiObject::putValueInProperty(const std::wstring& propertyName, const std::wstring& className, const std::wstring& domainName, const int& newValue){
    initComAndWbem(domainName.c_str());

    BSTR propertyNameBSTR{SysAllocString(propertyName.c_str())};

    IEnumWbemClassObject* wbemEnumClass{execQuery(L"SELECT * FROM "+className)};
    if(!wbemEnumClass){
        throw "IEnumWbemClassObject not created";
    }

    IWbemClassObject* instance{nullptr};
    ULONG uNumOfInstances{0};
    HRESULT result = wbemEnumClass->Next(WBEM_INFINITE, 1,&instance,&uNumOfInstances);

    if (FAILED(result))
    {
        std::cout << "Could not execute method. Error code = 0x" << std::hex << result << std::endl;
        SysFreeString(propertyNameBSTR);
        wbemEnumClass->Release();
        instance->Release();
        _wbemServices->Release();
        _wbemLocator->Release();
        CoUninitialize();

        throw "Cannot reboot the device";
    }

    result=putNewValueInInstance(instance,propertyNameBSTR,newValue);

    if (FAILED(result))
        std::cout << "Could not execute PUT. Error code = 0x" << std::hex << result << std::endl;

    SysFreeString(propertyNameBSTR);
    wbemEnumClass->Release();
    instance->Release();
    _wbemServices->Release();
    _wbemLocator->Release();
    CoUninitialize();
}

void MsiObject::getDataFromObject(IEnumWbemClassObject*& wbemEnumerator, const std::wstring& feature, VARIANT& var){
    // Get the data from the query in step 6 -------------------
    IWbemClassObject* wbemObject{nullptr};
    ULONG valueReturn{0};

    while (wbemEnumerator)
    {
        HRESULT result = wbemEnumerator->Next(WBEM_INFINITE, 1, &wbemObject, &valueReturn);
        if(valueReturn==0){
            break;
        }

        result = wbemObject->Get(feature.c_str(), 0, &var, 0, 0);

        if(FAILED(result))
            std::cout << "Failed to get data " << std::endl;

        wbemObject->Release();
    }
}

void MsiObject::getValueInProperty(const std::wstring& propertyName, const std::wstring& className, const std::wstring& domainName, VARIANT& var){        
    initComAndWbem(domainName);
    IEnumWbemClassObject* enumerator{execQuery(L"SELECT "+propertyName+L" FROM "+className)};
    getDataFromObject(enumerator,propertyName,var);
    enumerator->Release();
    cleanUpMsi();
}

void MsiObject::doReboot(){
    initComAndWbem(L"Root\\cimv2\\mdm\\dmmap");

    BSTR methodName{SysAllocString(L"RebootNowMethod")};
    BSTR className{SysAllocString(L"MDM_Reboot")};

    IEnumWbemClassObject* wbemEnumClass{nullptr};
    HRESULT result{_wbemServices->CreateInstanceEnum(className, WBEM_FLAG_RETURN_IMMEDIATELY , nullptr, &wbemEnumClass)};


    IWbemClassObject* instance{nullptr};
    ULONG numOfinstance{0};
    result = wbemEnumClass->Next(10000,1,&instance,&numOfinstance);

    if (FAILED(result))
    {
        std::cout << "Could not execute method. Error code = 0x" << std::hex << result << std::endl;
        SysFreeString(methodName);
        SysFreeString(className);
        wbemEnumClass->Release();
        instance->Release();
        _wbemServices->Release();
        _wbemLocator->Release();
        CoUninitialize();

        throw "Cannot reboot the device";
    }

    BSTR pathName{SysAllocString(L"__Path")};
    VARIANT path;
    result = instance->Get(pathName, 0,&path, 0, 0);

    if (FAILED(result))
    {
        std::cout << "Could not execute method. Error code = 0x" << std::hex << result << std::endl;
        SysFreeString(methodName);
        SysFreeString(className);
        SysFreeString(pathName);
        wbemEnumClass->Release();
        instance->Release();
        _wbemServices->Release();
        _wbemLocator->Release();
        CoUninitialize();

        throw "Cannot reboot the device";
    }

    IWbemClassObject* results{nullptr};
    result=_wbemServices->ExecMethod( path.bstrVal,methodName,0,nullptr,nullptr,&results, nullptr );
    if (FAILED(result))
        std::cout << "Could not execute method. Error code = 0x" << std::hex << result << std::endl;

    SysFreeString(methodName);
    SysFreeString(className);
    SysFreeString(pathName);
    wbemEnumClass->Release();
    instance->Release();
    _wbemServices->Release();
    _wbemLocator->Release();
    CoUninitialize();
}

void MsiObject::cleanUpMsi(){
    if(_wbemServices){
        _wbemServices->Release();
        _wbemServices=nullptr;
    }
    if(_wbemLocator){
        _wbemLocator->Release();
        _wbemLocator=nullptr;
    }
    CoUninitialize();
}

IEnumWbemClassObject* MsiObject::execQuery(const std::wstring& query){

        BSTR bstr_wql = SysAllocString(L"WQL" );
        BSTR bstr_sql = SysAllocString(query.c_str()); 

        IEnumWbemClassObject* enumerator{nullptr};
        HRESULT hres = _wbemServices->ExecQuery(
            bstr_wql, 
            bstr_sql,
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
            nullptr,
            &enumerator);

        SysFreeString(bstr_wql);
        SysFreeString(bstr_sql);

        if (FAILED(hres) || !enumerator)
        {
            std::cout << "Query for operating system name failed."
                << " Error code = 0x" 
                << std::hex << hres << std::endl;
            cleanUpMsi();
            throw "Failed to get OS";
        }
        return enumerator;
}

void MsiObject::initComAndWbem(const std::wstring& wmiNamespace){
        if(!initializeCom())
            throw "Initialization COM failed";

        if(!setUpWBEM(wmiNamespace))
            throw "Setting up WBEM failed";
}

bool MsiObject::initializeCom() const{
    // Initialize COM. ------------------------------------------
    HRESULT result{CoInitializeEx(0, COINIT_MULTITHREADED)}; 
    if (FAILED(result))
    {
        std::wcout << "Failed to initialize COM library. Error code = 0x" << std::hex << result << std::endl;
        return false;
    }

    // Set general COM security levels --------------------------
    result =  CoInitializeSecurity(
        nullptr, 
        -1,                          // COM authentication
        nullptr,                        // Authentication services
        nullptr,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
        nullptr,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities 
        nullptr                         // Reserved
        );

    if (FAILED(result))
    {
        std::wcout << "Failed to initialize security. Error code = 0x" << std::hex << result << std::endl;
        CoUninitialize();
        return false;
    }
    return true;
}

bool MsiObject::setUpWBEM(const std::wstring& wmiNamespace){
    // Obtain the initial locator to WMI -------------------------
    HRESULT result{CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &_wbemLocator)};
 
    if (FAILED(result))
    {
        std::cout << "Failed to create IWbemLocator object."<< " Err code = 0x"<< std::hex << result << std::endl;
        CoUninitialize();
        return false; 
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method
    result = _wbemLocator->ConnectServer(
         _bstr_t(wmiNamespace.c_str()), // Object path of WMI namespace
         nullptr,                    // User name. NULL = current user
         nullptr,                    // User password. NULL = current
         nullptr,                       // Locale. NULL indicates current
         0,                    // Security flags.
         0,                       // Authority (for example, Kerberos)
         0,                       // Context object 
         &_wbemServices            // pointer to IWbemServices proxy
         );
    
    if (FAILED(result))
    {
        std::wcout << "Could not connect. Error code = 0x" << std::hex << result << std::endl;
        _wbemLocator->Release();     
        CoUninitialize();
        return false;
    }

    // Set security levels on the proxy -------------------------
    result = CoSetProxyBlanket(
       _wbemServices,                // Indicates the proxy to set
       RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
       RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
       nullptr,                        // Server principal name 
       RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
       RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
       nullptr,                        // client identity
       EOAC_NONE                    // proxy capabilities 
    );

    if (FAILED(result))
    {
        std::cout << "Could not set proxy blanket. Error code = 0x" << std::hex << result << std::endl;
        _wbemServices->Release();
        _wbemLocator->Release();     
        CoUninitialize();
        return false;
    }
    return true;
}