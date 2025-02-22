// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

#ifndef __COMMCTRL_H__
#define __COMMCTRL_H__

/////////////////////////////////////////////////////////////////////////////
// CCommCtrl wrapper class

class CCommCtrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCommCtrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x648a5600, 0x2c6e, 0x101b, { 0x82, 0xb6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x14 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	BOOL GetCDHolding();
	void SetCDHolding(BOOL);
	long GetCDTimeout();
	void SetCDTimeout(long);
	short GetCommID();
	void SetCommID(short);
	short GetCommPort();
	void SetCommPort(short);
	BOOL GetCTSHolding();
	void SetCTSHolding(BOOL);
	long GetCTSTimeout();
	void SetCTSTimeout(long);
	BOOL GetDSRHolding();
	void SetDSRHolding(BOOL);
	long GetDSRTimeout();
	void SetDSRTimeout(long);
	BOOL GetDTREnable();
	void SetDTREnable(BOOL);
	long GetHandshaking();
	void SetHandshaking(long);
	short GetInBufferSize();
	void SetInBufferSize(short);
	short GetInBufferCount();
	void SetInBufferCount(short);
	BOOL GetBreak();
	void SetBreak(BOOL);
	short GetInputLen();
	void SetInputLen(short);
	long GetInterval();
	void SetInterval(long);
	BOOL GetNullDiscard();
	void SetNullDiscard(BOOL);
	short GetOutBufferSize();
	void SetOutBufferSize(short);
	short GetOutBufferCount();
	void SetOutBufferCount(short);
	CString GetParityReplace();
	void SetParityReplace(LPCTSTR);
	BOOL GetPortOpen();
	void SetPortOpen(BOOL);
	short GetRThreshold();
	void SetRThreshold(short);
	BOOL GetRTSEnable();
	void SetRTSEnable(BOOL);
	CString GetSettings();
	void SetSettings(LPCTSTR);
	short GetSThreshold();
	void SetSThreshold(short);
	VARIANT GetOutput();
	void SetOutput(const VARIANT&);
	CString GetInput();
	void SetInput(LPCTSTR);
	short GetCommEvent();
	void SetCommEvent(short);

// Operations
public:
	void AboutBox();
};

#endif // __COMMCTRL_H__
