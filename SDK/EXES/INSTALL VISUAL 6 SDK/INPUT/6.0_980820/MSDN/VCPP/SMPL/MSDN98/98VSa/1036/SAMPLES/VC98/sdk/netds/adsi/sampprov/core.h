/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Core.h

Abstract:

    Core ADS Obect
    
Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CORE_H_
#define _CORE_H_

class CCoreADsObject
{

public:

    CCoreADsObject::CCoreADsObject();

    CCoreADsObject::~CCoreADsObject();

    HRESULT
    get_CoreName(BSTR * retval);

    HRESULT
    get_CoreADsPath(BSTR * retval);

    HRESULT
    get_CoreParent(BSTR * retval);

    HRESULT
    get_CoreSchema(BSTR * retval);

    HRESULT
    get_CoreADsClass(BSTR * retval);


    HRESULT
    get_CoreGUID(BSTR * retval);


    DWORD
    CCoreADsObject::GetObjectState()
    {
        return(_dwObjectState);
    }


    void
    CCoreADsObject::SetObjectState(DWORD dwObjectState)
    {
        _dwObjectState = dwObjectState;
    }


    HRESULT
    InitializeCoreObject(
        BSTR Parent,
        BSTR Name,
        BSTR ClassName,
        BSTR Schema,
        REFCLSID rclsid,
        DWORD   dwObjectState
        );

    STDMETHOD(GetInfo)(THIS_ BOOL fExplicit);



protected:

    DWORD       _dwObjectState;

    BSTR        _Name;
    BSTR        _ADsPath;
    BSTR        _Parent;
    BSTR        _ADsClass;
    BSTR        _ADsGuid;
    BSTR        _Schema;

};


#define     ADS_OBJECT_BOUND              1
#define     ADS_OBJECT_UNBOUND            2

#endif


























































































