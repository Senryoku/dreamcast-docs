#ifndef __MSDGRID_H__
#define __MSDGRID_H__

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CMsDgridCtrl wrapper class

class CMsDgridCtrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMsDgridCtrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x28c00, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46 } };
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
	BOOL GetAllowDelete();
	void SetAllowDelete(BOOL);
	BOOL GetAllowAddNew();
	void SetAllowAddNew(BOOL);
	BOOL GetAllowRowSizing();
	void SetAllowRowSizing(BOOL);
	BOOL GetAllowUpdate();
	void SetAllowUpdate(BOOL);
	short GetBorderStyle();
	void SetBorderStyle(short);
	VARIANT GetBookmark();
	void SetBookmark(const VARIANT&);
	short GetCol();
	void SetCol(short);
	BOOL GetColumnHeaders();
	void SetColumnHeaders(BOOL);
	long GetDataMode();
	void SetDataMode(long);
	LPUNKNOWN GetDataSource();
	void SetDataSource(LPUNKNOWN);
	float GetDefColWidth();
	void SetDefColWidth(float);
	BOOL GetEnabled();
	void SetEnabled(BOOL);
	VARIANT GetFirstRow();
	void SetFirstRow(const VARIANT&);
	LPDISPATCH GetHeadFont();
	void SetHeadFont(LPDISPATCH);
	float GetHeadLines();
	void SetHeadLines(float);
	OLE_HANDLE GetHWnd();
	BOOL GetRecordSelectors();
	void SetRecordSelectors(BOOL);
	short GetRow();
	void SetRow(short);
	long GetRowDividerStyle();
	void SetRowDividerStyle(long);
	float GetRowHeight();
	void SetRowHeight(float);
	long GetScrollBars();
	void SetScrollBars(long);
	short GetSelStartCol();
	void SetSelStartCol(short);
	short GetSelEndCol();
	void SetSelEndCol(short);
	short GetVisibleCols();
	short GetVisibleRows();
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);
	OLE_COLOR GetForeColor();
	void SetForeColor(OLE_COLOR);
	CString GetCaption();
	void SetCaption(LPCTSTR);
	LPFONTDISP GetFont();
	void SetFont(LPFONTDISP);
	short GetLeftCol();
	void SetLeftCol(short);

// Operations
public:
	void AboutBox();
	LPDISPATCH GetColumns(const VARIANT& Index);
	VARIANT GetSelBookmarks(const VARIANT& Index);
	short ColContaining(float X);
	VARIANT GetBookmark(long RowNum);
	void ReBind();
	VARIANT RowBookmark(short RowNum);
	short RowContaining(float Y);
	float RowTop(short RowNum);
	void Scroll(long Cols, long Rows);
	void Refresh();
	LPDISPATCH CaptureImage();
};

#endif // __MSDGRID_H__
