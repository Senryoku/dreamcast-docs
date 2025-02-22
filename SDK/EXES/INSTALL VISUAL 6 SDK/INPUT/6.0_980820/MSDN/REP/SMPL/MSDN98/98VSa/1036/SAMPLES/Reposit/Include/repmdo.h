// ------------------------------------------------------------------------
// Copyright (c) 1998 by Microsoft Corporation, All Rights Reserved
// 
// This software is provided as is without warranty of any kind.  The entire
// risk as to the results and performance of this software is assumed by the user.
// Microsoft disclaims all warranties, either express or implied, including but
// not limited, the implied warranties of merchantability, fitness for a
// particular purpose, title and noninfringement, with respect to this software.
// ------------------------------------------------------------------------
//*****************************************************************************
// REPMDO.H
//
// This module contains the .odl generated interface definitions for the
// MDO meta model.
//
// Copyright (c) 1995-1996 by Microsoft Corporation, All Rights Reserved
//*****************************************************************************
/* This header file machine-generated by mktyplib.exe */
/* Interface to type library: MdoTypeLib */

#ifndef _MdoTypeLib_H_
#define _MdoTypeLib_H_

DEFINE_GUID(LIBID_MdoTypeLib,0x4A165950L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);
#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#endif

DEFINE_GUID(IID_IMdoModel,0x4A165951L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoModel */
#undef INTERFACE
#define INTERFACE IMdoModel

DECLARE_INTERFACE_(IMdoModel, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoModel methods */
};

DEFINE_GUID(IID_IMdoModelItem,0x4A165952L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoModelItem */
#undef INTERFACE
#define INTERFACE IMdoModelItem

DECLARE_INTERFACE_(IMdoModelItem, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoModelItem methods */
    STDMETHOD(get_Description)(THIS_ BSTR FAR* pDescription) PURE;
    STDMETHOD(get_FileName)(THIS_ BSTR FAR* pFileName) PURE;
    STDMETHOD(get_TimeStamp)(THIS_ DATE FAR* pTimeStamp) PURE;
};

DEFINE_GUID(IID_IMdoControl,0x4A165953L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoControl */
#undef INTERFACE
#define INTERFACE IMdoControl

DECLARE_INTERFACE_(IMdoControl, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoControl methods */
    STDMETHOD(get_Index)(THIS_ long FAR* piIndex) PURE;
    STDMETHOD(get_ClassName)(THIS_ BSTR FAR* pClassName) PURE;
    STDMETHOD(get_ProgID)(THIS_ BSTR FAR* pProgID) PURE;
    STDMETHOD(get_Description)(THIS_ BSTR FAR* pDescription) PURE;
};

DEFINE_GUID(IID_IMdoProject,0x4A165954L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoProject */
#undef INTERFACE
#define INTERFACE IMdoProject

DECLARE_INTERFACE_(IMdoProject, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoProject methods */
    STDMETHOD(get_MdoComponents)(THIS_ ITargetObjectCol FAR* pComponentCol) PURE;
    STDMETHOD(get_MdoReferences)(THIS_ ITargetObjectCol FAR* pReferenceCol) PURE;
};

DEFINE_GUID(IID_IMdoControlContainer,0x4A165955L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoControlContainer */
#undef INTERFACE
#define INTERFACE IMdoControlContainer

DECLARE_INTERFACE_(IMdoControlContainer, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoControlContainer methods */
    STDMETHOD(get_MdoControls)(THIS_ ITargetObjectCol FAR* pControlCol) PURE;
};

DEFINE_GUID(IID_IMdoReference,0x4A165956L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoReference */
#undef INTERFACE
#define INTERFACE IMdoReference

DECLARE_INTERFACE_(IMdoReference, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoReference methods */
};

DEFINE_GUID(IID_IMdoComponent,0x4A165957L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoComponent */
#undef INTERFACE
#define INTERFACE IMdoComponent

DECLARE_INTERFACE_(IMdoComponent, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoComponent methods */
};

DEFINE_GUID(IID_IMdoISVControl,0x4A165958L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoISVControl */
#undef INTERFACE
#define INTERFACE IMdoISVControl

DECLARE_INTERFACE_(IMdoISVControl, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoISVControl methods */
};

DEFINE_GUID(IID_IMdoControlUsage,0x4A165959L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

/* Definition of interface: IMdoControlUsage */
#undef INTERFACE
#define INTERFACE IMdoControlUsage

DECLARE_INTERFACE_(IMdoControlUsage, IRepositoryDispatch)
{
BEGIN_INTERFACE
#ifndef NO_BASEINTERFACE_FUNCS

    /* IRepositoryDispatch methods */
/* You must describe methods for this interface here */
#endif

    /* IMdoControlUsage methods */
};

DEFINE_GUID(CLSID_MdoProject,0x4A16595AL,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoProject;
#endif

DEFINE_GUID(CLSID_MdoStdModule,0x4A16595BL,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoStdModule;
#endif

DEFINE_GUID(CLSID_MdoClassModule,0x4A16595CL,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoClassModule;
#endif

DEFINE_GUID(CLSID_MdoVBForm,0x4A16595DL,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoVBForm;
#endif

DEFINE_GUID(CLSID_MdoMDIForm,0x4A16595EL,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoMDIForm;
#endif

DEFINE_GUID(CLSID_MdoResourceFile,0x4A16595FL,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoResourceFile;
#endif

DEFINE_GUID(CLSID_MdoMSForm,0x4A165960L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoMSForm;
#endif

DEFINE_GUID(CLSID_MdoPropertyPage,0x4A165961L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoPropertyPage;
#endif

DEFINE_GUID(CLSID_MdoUserControl,0x4A165962L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoUserControl;
#endif

DEFINE_GUID(CLSID_MdoUserDocument,0x4A165963L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoUserDocument;
#endif

DEFINE_GUID(CLSID_MdoDesigner,0x4A165964L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoDesigner;
#endif

DEFINE_GUID(CLSID_MdoRelatedDocument,0x4A165965L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoRelatedDocument;
#endif

DEFINE_GUID(CLSID_MdoTypeLibRef,0x4A165966L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoTypeLibRef;
#endif

DEFINE_GUID(CLSID_MdoProjectRef,0x4A165967L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoProjectRef;
#endif

DEFINE_GUID(CLSID_MdoControl,0x4A165968L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoControl;
#endif

DEFINE_GUID(CLSID_MdoISVControl,0x4A165969L,0xEC7C,0x11CF,0x90,0x7D,0x00,0xA0,0xC9,0x13,0xF7,0xC7);

#ifdef __cplusplus
class MdoISVControl;
#endif

#endif
