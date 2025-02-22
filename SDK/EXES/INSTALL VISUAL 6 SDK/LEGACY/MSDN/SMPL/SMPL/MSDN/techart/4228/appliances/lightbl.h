// lightbl.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CLightBulb command target

class CLightBulb : public CCmdTarget
{
	DECLARE_DYNCREATE(CLightBulb)
protected:
	CLightBulb();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightBulb)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLightBulb();

	// Generated message map functions
	//{{AFX_MSG(CLightBulb)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLightBulb)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLightBulb)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    // Declare the interface map for this object
    DECLARE_INTERFACE_MAP()

    // IDrawing interface
    BEGIN_INTERFACE_PART(Drawing, IDrawing)
        STDMETHOD(Draw)(CDC* pDC,int x, int y);
        STDMETHOD(SetPalette)(CPalette* pPal);
    END_INTERFACE_PART(Drawing)

    // member variables
    CDIB m_dibImage;
    CPalette* m_pPal;
};

/////////////////////////////////////////////////////////////////////////////
