; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "drawcli.h"
LastPage=0

ClassCount=9
Class1=CDrawApp
Class2=CAboutDlg
Class3=CDrawDoc
Class4=CDrawView
Class5=CMainFrame
Class6=CRectDlg
Class7=CSplitFrame
Class8=CStatPage
Class9=CSummPage

ResourceCount=8
Resource1=IDD_SUMM_PAGE
Resource2=IDR_MAINFRAME
Resource3=IDR_DRAWCLTYPE
Resource4=IDR_DRAWCLTYPE_CNTR_IP
Resource5=ID_POPUP_MENU
Resource6=IDD_ABOUTBOX
Resource7=IDD_PROP_RECT
Resource8=IDD_STAT_PAGE

[CLS:CDrawApp]
Type=0
BaseClass=CWinApp
HeaderFile=drawcli.h
ImplementationFile=drawcli.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=drawcli.cpp
ImplementationFile=drawcli.cpp

[CLS:CDrawDoc]
Type=0
BaseClass=COleDocument
HeaderFile=drawdoc.h
ImplementationFile=drawdoc.cpp

[CLS:CDrawView]
Type=0
BaseClass=CScrollView
HeaderFile=drawvw.h
ImplementationFile=drawvw.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CRectDlg]
Type=0
BaseClass=CDialog
HeaderFile=rectdlg.h
ImplementationFile=rectdlg.cpp

[CLS:CSplitFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=splitfrm.h
ImplementationFile=splitfrm.cpp

[CLS:CStatPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=statpage.h
ImplementationFile=statpage.cpp

[CLS:CSummPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=summpage.h
ImplementationFile=summpage.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROP_RECT]
Type=1
Class=CRectDlg
ControlCount=6
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_WEIGHT,edit,1350631552
Control4=IDC_SPIN1,msctls_updown32,1342177334
Control5=IDC_STATIC,button,1342177287
Control6=IDC_NOFILL,button,1342242819

[DLG:IDD_STAT_PAGE]
Type=1
Class=CStatPage
ControlCount=20
Control1=IDC_STATIC,static,1342308352
Control2=IDC_SAVEDBY,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDITTIME,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LASTPRINT,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_CREATEDATE,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_LASTSAVE,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_NUMPAGES,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_NUMWORDS,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_NUMCHARS,static,1342308352
Control18=IDC_REVNUM,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_SECURITY,static,1342308352

[DLG:IDD_SUMM_PAGE]
Type=1
Class=CSummPage
ControlCount=14
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_AUTHOR,edit,1350631552
Control8=IDC_KEYWORDS,edit,1350631552
Control9=IDC_COMMENTS,edit,1352732676
Control10=IDC_TITLE,edit,1350631552
Control11=IDC_SUBJECT,edit,1350631552
Control12=IDC_TEMPLATE,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_APPNAME,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=7

[MNU:IDR_DRAWCLTYPE]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CLEAR
Command16=ID_EDIT_SELECT_ALL
Command17=ID_EDIT_PROPERTIES
Command18=ID_OLE_INSERT_NEW
Command19=ID_OLE_EDIT_LINKS
Command20=ID_OLE_VERB_FIRST
Command21=ID_VIEW_GRID
Command22=ID_VIEW_PAPERCOLOR
Command23=ID_VIEW_SHOWOBJECTS
Command24=ID_VIEW_TOOLBAR
Command25=ID_VIEW_STATUS_BAR
Command26=ID_DRAW_SELECT
Command27=ID_DRAW_LINE
Command28=ID_DRAW_RECT
Command29=ID_DRAW_ROUNDRECT
Command30=ID_DRAW_ELLIPSE
Command31=ID_DRAW_POLYGON
Command32=ID_OBJECT_LINECOLOR
Command33=ID_OBJECT_FILLCOLOR
Command34=ID_OBJECT_MOVETOFRONT
Command35=ID_OBJECT_MOVETOBACK
Command36=ID_OBJECT_MOVEFORWARD
Command37=ID_OBJECT_MOVEBACK
Command38=ID_WINDOW_NEW
Command39=ID_WINDOW_CASCADE
Command40=ID_WINDOW_TILE_HORZ
CommandCount=40

[MNU:IDR_DRAWCLTYPE_CNTR_IP]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_WINDOW_NEW
Command12=ID_WINDOW_CASCADE
Command13=ID_WINDOW_TILE_HORZ
CommandCount=13

[MNU:ID_POPUP_MENU]
Type=1
CommandCount=0

[ACL:IDR_MAINFRAME]
Type=1
Command1=ID_OBJECT_MOVETOFRONT
Command2=ID_OBJECT_MOVEBACK
Command3=ID_OBJECT_MOVEFORWARD
Command4=ID_EDIT_SELECT_ALL
Command5=ID_EDIT_COPY
Command6=ID_DRAW_ELLIPSE
Command7=ID_VIEW_GRID
Command8=ID_DRAW_LINE
Command9=ID_DRAW_ROUNDRECT
Command10=ID_FILE_NEW
Command11=ID_FILE_OPEN
Command12=ID_FILE_PRINT
Command13=ID_APP_EXIT
Command14=ID_DRAW_RECT
Command15=ID_DRAW_SELECT
Command16=ID_FILE_SAVE
Command17=ID_EDIT_PASTE
Command18=ID_OBJECT_MOVEFORWARD
Command19=ID_OBJECT_MOVETOFRONT
Command20=ID_EDIT_UNDO
Command21=ID_EDIT_CLEAR
Command22=ID_EDIT_CUT
Command23=ID_CANCEL_EDIT
Command24=ID_NEXT_PANE
Command25=ID_PREV_PANE
Command26=ID_EDIT_COPY
Command27=ID_EDIT_PASTE
Command28=ID_EDIT_PROPERTIES
Command29=ID_OBJECT_MOVEBACK
Command30=ID_OBJECT_MOVETOBACK
Command31=ID_EDIT_CUT
Command32=ID_EDIT_UNDO
Command33=ID_OBJECT_MOVETOBACK
Command34=ID_DRAW_ELLIPSE
Command35=ID_VIEW_GRID
Command36=ID_DRAW_LINE
Command37=ID_DRAW_ROUNDRECT
Command38=ID_DRAW_RECT
Command39=ID_DRAW_SELECT
CommandCount=39

[ACL:IDR_DRAWCLTYPE_CNTR_IP]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT
Command4=ID_APP_EXIT
Command5=ID_FILE_SAVE
Command6=ID_CANCEL_EDIT
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_EDIT_CUT
Command4=ID_EDIT_PASTE
Command5=ID_DRAW_SELECT
Command6=ID_DRAW_RECT
Command7=ID_DRAW_ELLIPSE
Command8=ID_FILE_PRINT
Command9=ID_CONTEXT_HELP
CommandCount=9

