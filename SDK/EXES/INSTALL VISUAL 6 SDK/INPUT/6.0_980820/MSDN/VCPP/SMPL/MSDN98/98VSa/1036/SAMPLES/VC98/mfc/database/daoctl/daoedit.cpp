// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "daoedit.h"

/////////////////////////////////////////////////////////////////////////////
// CDaoEdit

IMPLEMENT_DYNCREATE(CDaoEdit, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CDaoEdit properties

CString CDaoEdit::GetText()
{
	CString result;
	GetProperty(DISPID_TEXT, VT_BSTR, (void*)&result);
	return result;
}

void CDaoEdit::SetText(LPCTSTR propVal)
{
	SetProperty(DISPID_TEXT, VT_BSTR, propVal);
}

CString CDaoEdit::Get_Text()
{
	CString result;
	GetProperty(0x0, VT_BSTR, (void*)&result);
	return result;
}

void CDaoEdit::Set_Text(LPCTSTR propVal)
{
	SetProperty(0x0, VT_BSTR, propVal);
}

short CDaoEdit::GetBorderStyle()
{
	short result;
	GetProperty(DISPID_BORDERSTYLE, VT_I2, (void*)&result);
	return result;
}

void CDaoEdit::SetBorderStyle(short propVal)
{
	SetProperty(DISPID_BORDERSTYLE, VT_I2, propVal);
}

CString CDaoEdit::GetFieldName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CDaoEdit::SetFieldName(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CDaoEdit operations

void CDaoEdit::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
