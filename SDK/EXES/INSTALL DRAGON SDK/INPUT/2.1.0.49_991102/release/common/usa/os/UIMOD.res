        ��  ��                     4   T E X T I N C L U D E   ��     0	        uiresource.h       4   T E X T I N C L U D E   ��     0	        #include "winres.h"
   �  <   �� V S _ V E R S I O N _ I N F O       0 	        �4   V S _ V E R S I O N _ I N F O     ���               ?                         ,   S t r i n g F i l e I n f o      0 4 0 9 0 4 B 0        C o m p a n y N a m e     D   F i l e D e s c r i p t i o n     i e c e u i   M o d u l e   6   F i l e V e r s i o n     1 ,   0 ,   0 ,   1     .   I n t e r n a l N a m e   I E C E U I     B   L e g a l C o p y r i g h t   C o p y r i g h t   1 9 9 7     >   O r i g i n a l F i l e n a m e   I E C E U I . D L L     <   P r o d u c t N a m e     i e c e u i   M o d u l e   :   P r o d u c t V e r s i o n   1 ,   0 ,   0 ,   1     (    O L E S e l f R e g i s t e r     D    V a r F i l e I n f o     $    T r a n s l a t i o n     	��  0   R E G I S T R Y   ��f       0	        HKCR
{
	Ieceui.ieui.1 = s 'ieui Class'
	{
		CLSID = s '{B048FC81-122D-11D3-9590-00C04FAEA6D4}'
	}
	Ieceui.ieui = s 'ieui Class'
	{
		CLSID = s '{B048FC81-122D-11D3-9590-00C04FAEA6D4}'
	}
	NoRemove CLSID
	{
		ForceRemove {B048FC81-122D-11D3-9590-00C04FAEA6D4} = s 'ieui Class'
		{
			ProgID = s 'Ieceui.ieui.1'
			VersionIndependentProgID = s 'Ieceui.ieui'
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'both'
			}
		}
	}
}
   �+  0   �� F I N D . D L G         0 	        <HTML id=dlgFind STYLE="font-family: ms sans serif; font-size: 8pt;
width: 33.5em; height: 11.2em">
<HEAD>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<TITLE id=dialogTitle>
Find
</TITLE>
<SCRIPT LANGUAGE="JavaScript" defer>
function callHelp(elm)
{
if (null != elm.helpid)
{
 window.showHelp(elm.helpfile, "" + parseInt(elm.helpid),
  "popup");
}
else
{
 if ("BODY" != elm.tagName)
 {
  callHelp(elm.parentElement);
 }
}
} 
function btnCancelClick()
{
window.close();
} 
function getTextRange(elm)
{
var r = elm.parentTextEdit.createTextRange();
r.moveToElementText(elm);
return r;
} 
function mouseClick()
{
if (window.event.srcElement.id.substring(0,3)
 == "txt")
{
 return;
}
if (window.event.button == 2)
{
 callHelp(window.event.srcElement);
}
} 
function txtDefaultESC()
{
if (event.keyCode == 27)
{
 window.close();
 return;
}
} 
window.onerror = HandleError
function HandleError(message, url, line)
{
var L_Dialog_ErrorMessage = "An error has occured in this dialog.";
var L_ErrorNumber_Text = "Error: ";
var str = L_Dialog_ErrorMessage + "\n\n" 
 + L_ErrorNumber_Text + line + "\n"
 + message;
alert (str);
window.close();
return true;
}
function setFindState(fKeyPress) { var htmlKeyAlt = 18; if (!fKeyPress || htmlKeyAlt != event.keyCode) { if (("" == txtFindText.value) == g_fFindEnabled) { btnFind.disabled = g_fFindEnabled; g_fFindEnabled = !g_fFindEnabled; } } else { window.setTimeout("set" + "Find" + "State(false)", 50); } }
var g_fFindEnabled = false; 
var g_docLastFound; 
var g_fFrameset = false; 
var g_arrFrames = new Array(); 
var g_fSearchTopFrame = false; 
var g_fFollowIframes = true;  
function findFlags()
{
var htmlMatchWord = 2;
var htmlMatchCase = 4;
return (htmlMatchWord * document.all.chkWholeWord.checked)
 | (htmlMatchCase * document.all.chkMatchCase.checked)
} 
function CrawlPath()
{
var win = window.dialogArguments.unsecuredWindowOfDocument;
var i = 0;
if (g_fSearchTopFrame)
{
 return win;
}
while (g_arrFrames[i] >= 0)
{
 win = win.frames[g_arrFrames[i]];
 i++;
}
return win;
} 
function AtFrameset()
{
var win = CrawlPath();
return win.frames.length;
} 
function AtIframe()
{
var win = CrawlPath();
return win.document.all.tags("IFRAME").length;
} 
function GetCurrentPos()
{
var i = GetCurrentDepth();
return g_arrFrames[i];
} 
function GetCurrentDepth()
{
var i = 0;
while (g_arrFrames[i] >= 0)
{
 i++;
}
return i-1;
} 
function MovePossible(fForward)
{
var intCurPos = GetCurrentPos();
var win = CrawlPath();
var winParent = win.parent;
if (fForward)
{
 return winParent.frames.length - intCurPos - 1;
}
else
{
 return (intCurPos != 0);
}
} 
function MoveUpFrameset()
{
var i = GetCurrentDepth();
g_arrFrames[i] = -1;
} 
function MoveDownFrameset(fForward)
{
var i = GetCurrentDepth();
var win = CrawlPath();
g_arrFrames[i+1] = fForward ? 0 : win.frames.length - 1;
g_arrFrames[i+2] = -1;
} 
function MoveWin(fForward)
{
var intDepth = GetCurrentDepth();
var intPos = GetCurrentPos();
g_arrFrames[intDepth] = fForward ? ++intPos : --intPos;
} 
function MoveDoc(fForward)
{
if (g_fSearchTopFrame) 
{ 
 if (fForward)
 {
  g_fSearchTopFrame = false;
  return true;
 }
 else
 {
  return false;
 }
}
if (!fForward && (g_arrFrames[0] == 0) && (g_arrFrames[1] < 0)
 && window.dialogArguments.document.all.tags("IFRAME").length)
{
 g_fSearchTopFrame = true;
 return true;
}
if (g_fFollowIframes && AtIframe())
{
 MoveDownFrameset(fForward);
 while (!AtIframe() && AtFrameset())
 {
  MoveDownFrameset(fForward);
 }
 return true;
}
if (MovePossible(fForward))
{
 MoveWin(fForward);
 g_fFollowIframes = true;
 while (!AtIframe() && AtFrameset())
 {
  MoveDownFrameset(fForward);
 }
 return true;
}
else
{
 if (GetCurrentDepth() > 0)
 {
  MoveUpFrameset();
  while (AtIframe() && !MovePossible(fForward)
   && (GetCurrentDepth() >= 0))
  {
   MoveUpFrameset();
  }
  if (AtIframe() && MovePossible(fForward))
  {
   g_fFollowIframes = false;
  }
  return MoveDoc(fForward);
 }
}
return false;
} 
function GetFirstDoc()
{
var win;
var doc = window.dialogArguments.document;
if (doc.all.tags("IFRAME").length)
{
 g_fSearchTopFrame = true;
 return doc;
}
while (!AtIframe() && AtFrameset())
{
 MoveDownFrameset(true);
}
win = CrawlPath();
return win.document;
} 
function btnFindClick()
{
var docSearch; 
var L_FinishedDocument_Text = "Finished searching the document.";
var intDirection;  
var rngWorking;   
var rngFoundText;  
var fFoundText = false; 
var index;
if (g_fFrameset)
{
 var win;
 if (!AtIframe() && AtFrameset())
 {
  MoveDownFrameset(!radDirection[0].checked);
  while (!AtIframe() && AtFrameset())
  {
   MoveDownFrameset(!radDirection[0].checked);
  }
 }
 win = CrawlPath();
 docSearch = win.document;
}
else
{
 docSearch = window.dialogArguments.document;
}
if (docSearch.queryCommandState("BrowseMode")
 && docSearch.selection.type != "Text")
{
 if (docSearch.body == null)
  return;
 rngWorking = docSearch.body.createTextRange();
}
else
{
 rngWorking = docSearch.selection.createRange();
}
fFoundText = (docSearch.selection.type == "Text");
if (radDirection[0].checked) 
{
 if (fFoundText)
 {
  rngWorking.moveEnd("character" , -1);
 }
 while (0 != rngWorking.moveStart("textedit", -1))
 {
 }
 intDirection = -1000000;
}
else       
{
 if (fFoundText)
 {
  rngWorking.moveStart("character", 1);
 }
 while (0 != rngWorking.moveEnd("textedit", 1))
 {
 }
 intDirection = 1000000; 
}
rngFoundText = rngWorking.duplicate();
success = rngFoundText.findText(txtFindText.value, 
 intDirection, findFlags());
if (!success) 
{
 if (g_fFrameset)
 {
  if (MoveDoc(!radDirection[0].checked))
  {
   btnFindClick();
   return;
  }
 }
 alert(L_FinishedDocument_Text);
 txtFindText.focus();
}
else      
{
 if (g_fFrameset)
 {
  g_docLastFound.execCommand("Unselect", false);
  g_docLastFound = docSearch;
 }
 rngFoundText.select();
 rngFoundText.scrollIntoView(true);
}
} 
function btnCancelClick2()
{
window.dialogArguments.findText = txtFindText.value;
window.close();
} 
function loadBdy()
{
var win = window.dialogArguments.unsecuredWindowOfDocument;
var doc = window.dialogArguments.document;
btnFind.onclick  = new 
 Function("btnFindClick()");
btnCancel.onclick = new Function("btnCancelClick2()");
document.onhelp  = new Function("callHelp(window.event.srcElement)");
document.onmouseup = new Function("mouseClick()");
txtFindText.onkeyup = new Function("setFindState(true)");
txtFindText.onfocus = new Function("txtFindText.select()");
txtFindText.onkeypress = new Function("txtDefaultESC()");
if (win.frames.length)
{
 var win2;
 g_fFrameset = true;
 g_arrFrames[0] = 0;
 g_arrFrames[1] = -1;
 win2 = CrawlPath();
 doc2 = win2.document;
 while (doc2.selection.type == "None")
 {
  if (MoveDoc(true))
  {
   win2 = CrawlPath();
   doc2 = win2.document;
  }
  else 
  {
   g_arrFrames[0] = 0;
   g_arrFrames[1] = -1;
   break;
  }
 }
 doc = CrawlPath().document;
 g_docLastFound = doc;
}
if (doc.selection.type == "Control")
{
 var r = doc.selection.createRange();
 r = getTextRange(r(0));
 r.select();
}
txtFindText.value = window.dialogArguments.findText;
txtFindText.focus();
txtFindText.select();
setFindState(false);
} 
</SCRIPT>
</HEAD>
<BODY ID=bdy onLoad="loadBdy()" style="font-family: 'ms sans serif';
font-size: 8pt; background: threedface;" topmargin=0 scroll=no>
<BUTTON id=btnFind ACCESSKEY=f DISABLED=1 tabIndex=55 helpid=50026
helpfile="iexplore.hlp"
style="font-family: ms sans serif; font-size: 8pt; position: absolute;
left: 24.78em; top: 1.0647em; width: 7em; height: 2.2em; " type=submit>
<U>F</U>ind Next
</BUTTON>
<DIV align=absMiddle
style="font-family: ms sans serif; font-size: 8pt; position: absolute;
left: 0.98em; top: 1.2168em; width: 4.8em; height: 1.2168em; ">
<LABEL FOR=txtFindText ID=lblFindText tabIndex=-1 helpid=50027
helpfile="iexplore.hlp">
Fi<U>n</U>d what:
</LABEL>
</DIV>
<INPUT type=text id=txtFindText ACCESSKEY=n tabIndex=15 helpid=50027
helpfile="iexplore.hlp"
style="font-family: ms sans serif; font-size: 8pt; position: absolute;
left: 6.16em; top: 1.0647em; width: 17.36em; height: 2.1294em; ">
<BUTTON id=btnCancel tabIndex=60 helpid="0x6F1C" helpfile="windows.hlp"
style="font-family: ms sans serif; font-size: 8pt; position: absolute;
left: 24.78em; top: 3.6504em; width: 7em; height: 2.2em; " type=reset>
Cancel
</BUTTON>
<INPUT id=chkWholeWord ACCESSKEY=w type=checkbox tabIndex=25 
helpfile="iexplore.hlp" helpid=50022
style="font-family: ms sans serif; font-size: 8pt; position: absolute;
left: 0.68em; top: 3.8588em; width: 1em; height: 1em; ">
<INPUT ACCESSKEY=c type=checkbox tabIndex=35 helpid=50023
helpfile="iexplore.hlp"
id=chkMatchCase style="font-family: ms sans serif; font-size: 8pt;
position: absolute; left: 0.68em; top: 5.684em; width: 1em;
height: 1em; ">
<DIV
style="font-family: ms sans serif; font-size: 8pt; position: absolute;
left: 2.6em; top: 4.2588em; width: 12.46em; height: 1.521em; border-width:medium">
<LABEL FOR=chkWholeWord ID=lblWholeWord tabIndex=-1 helpid=50022
helpfile="iexplore.hlp">
&nbsp;Match <U>w</U>hole word only
</LABEL>
</DIV>
<DIV style="font-family: ms sans serif; font-size: 8pt; position: absolute;
left: 2.6em; top: 6.084em; width: 7.42em; height: 1.521em; border-width:medium">
<LABEL FOR=chkMatchCase ID=lblMatchCase tabIndex=-1 helpid=50023
helpfile="iexplore.hlp">
&nbsp;Match <U>c</U>ase
</LABEL>
</DIV>
<FIELDSET id=fldDirection style="font-family: ms sans serif; font-size: 8pt; 
position: absolute; left: 14.0em; top: 3.5em; width: 9.8em; 
height: 4.2em;">
<LEGEND>
Direction
</LEGEND>
</FIELDSET>
 <INPUT id=radDirectionUp type=radio name=radDirection ACCESSKEY=u
 tabIndex=42 helpid=50025 helpfile="iexplore.hlp"
 style="font-family: ms sans serif; font-size: 8pt; position: absolute;
 left: 14.26em; top: 5.1235em; width: 1em; height: 1em; ">
 <DIV style="font-family: ms sans serif; font-size: 8pt;
 position: absolute; left: 16.2em; top: 5.3235em; width: 3.5em;
 height: 1.521em; ">
 <LABEL ID=lblDirectionUp style="font-family: 'ms sans serif'; font-size: 8pt; border-width:medium"
 FOR=radDirectionUp
 tabIndex=45 helpid=50025
 helpfile="iexplore.hlp">&nbsp;<U>U</U>p </LABEL>
 </DIV>
 <INPUT id=radDirectionDown type=radio CHECKED name=radDirection
 ACCESSKEY=d tabIndex=47 helpid=50024 helpfile="iexplore.hlp"
 style="font-family: ms sans serif; font-size: 8pt; position: absolute;
 left: 18.18em; top: 5.1235em; width: 1em; height: 1em; ">
 <DIV style="font-family: ms sans serif; font-size: 8pt;
 position: absolute; left: 20.1em; top: 5.3235em; width: 4.9em;
 height: 1.521em; ">
 <LABEL ID=lblDirectionDown style="font-family: 'ms sans serif'; font-size: 8pt; border-width:medium"
 FOR=radDirectionDown helpid=50024 helpfile="iexplore.hlp"
 tabIndex=50>&nbsp;<U>D</U>own </LABEL>
 </DIV>
</BODY>
</HTML>
   x  0   �� E R R O R . D L G       0 	        <HTML id=dlgFind STYLE="font-family: ms sans serif; font-size: 8pt;
width: 42em; height: 20em">
<HEAD>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<TITLE id=dialogTitle>
Internet Explorer Script Error
</TITLE>
<SCRIPT LANGUAGE="JavaScript" defer>
window.onerror = HandleError
function HandleError(message, url, line)
{
var L_Dialog_ErrorMessage = "An error has occurred in this dialog.";
var L_ErrorNumber_Text = "Error: ";
var str = L_Dialog_ErrorMessage + "\n\n" 
 + L_ErrorNumber_Text + line + "\n"
 + message;
alert (str);
window.close();
return true;
}
function loadBdy()
{
var L_ContinueScript_Message = "Do you want to continue running scripts on this page?";
var objOptions = window.dialogArguments; 
btnNo.onclick = new Function("btnOKClick()");
btnYes.onclick = new Function("btnYesClick()");
document.onkeypress = new Function("docKeypress()");
spnLine.innerText  = objOptions.errorLine;
spnCharacter.innerText = objOptions.errorCharacter;
spnError.innerText  = objOptions.errorMessage;
spnCode.innerText  = objOptions.errorCode;
if (!objOptions.errorDebug)
{
 divDebug.innerText = L_ContinueScript_Message;
}
btnYes.focus();
} 
function btnOKClick()
{
window.close();
} 
function btnYesClick()
{
window.dialogArguments.errorDebug = true;
window.close();
} 
function docKeypress()
{
var L_AffirmativeKeyCodeLowerCase_Number = 121;
var L_AffirmativeKeyCodeUpperCase_Number = 89;
var L_NegativeKeyCodeLowerCase_Number  = 110;
var L_NegativeKeyCodeUpperCase_Number  = 78;
var intKeyCode = window.event.keyCode;
if (intKeyCode == L_AffirmativeKeyCodeLowerCase_Number
 || intKeyCode == L_AffirmativeKeyCodeUpperCase_Number)
{
 btnYesClick();
}
if (intKeyCode == L_NegativeKeyCodeLowerCase_Number
 || intKeyCode == L_NegativeKeyCodeUpperCase_Number)
{
 btnOKClick();
}
} 
</SCRIPT>
</HEAD>
<BODY ID=bdy onLoad="loadBdy()" style="font-family: 'ms sans serif';
font-size: 8pt; background: threedface;" topmargin=0>
<CENTER>
<table cellPadding=3 cellspacing=3 border=0 id=tbl1 
style="background: buttonface; font-family: ms sans serif; font-size: 8pt;">
<TR>
<TD>
<img src=warning.gif width=36 height=38 border=0 align=middle>
</TD>
<TD>
An error has occurred in the script on this page.
</TD>
</TR>
</TABLE>
</CENTER>
<DIV id=divTop style="background: threedface; font-family: ms sans serif; 
font-size: 8pt; margin-left: 1.5em">
<TABLE border=0 id=tbl2
style="background: buttonface; font-family: ms sans serif; font-size: 8pt;
margin-left: 1em">
<TR valign=top>
<TD nowrap>
Line:&nbsp;&nbsp;&nbsp;&nbsp;
</TD>
<TD>
<SPAN id=spnLine></SPAN>
</TD>
</TR>
<TR valign=top>
<TD nowrap>
Char:&nbsp;&nbsp;&nbsp;&nbsp;
</TD>
<TD>
<SPAN id=spnCharacter></SPAN>
</TD>
</TR>
<TR valign=top>
<TD nowrap>
Error:&nbsp;&nbsp;&nbsp;&nbsp;
</TD>
<TD>
<DIV id=spnError style="background: threedface;
font-family: ms sans serif; font-size: 8pt; width: 31em;"></DIV>
</TD>
</TR>
<TR valign=top>
<TD nowrap>
Code:&nbsp;&nbsp;&nbsp;&nbsp;
</TD>
<TD>
<SPAN id=spnCode></SPAN>
</TD>
</TR>
</TABLE>
</DIV>
<DIV id=divButttons style="background: buttonface; position: absolute;
font-family: ms sans serif; font-size: 8pt; top: 13em">
<CENTER>
<SPAN id=divDebug >Do you want to debug the current page?&nbsp;&nbsp;&nbsp;&nbsp;</SPAN>
<BUTTON ID=btnYes style="font-family: ms sans serif; font-size: 8pt;
width: 3.8em; height: 2.2em;" type=submit accesskey=y>
<U>Y</U>es
</BUTTON>
&nbsp;
<BUTTON ID=btnNo style="font-family: ms sans serif; font-size: 8pt;
width: 3.8em; height: 2.2em" type=reset accesskey=n>
<U>N</U>o
</BUTTON>
</CENTER>
</DIV>
</BODY>
</HTML>
&  4   �� W A R N I N G . G I F       0 	        GIF89a$ & �     h  �  �  �  �   h hh �h �h �h �h  � h� �� �� � ��  � h� �� �� �� ��  � h� �� �� �� ��  � h� �� �� �� ��   hh h� h� h� h� h hhhhh�hh�hh�hh�hh �hh�h��h��h�h��h �hh�h��h��h��h��h �hh�h��h��h��h��h �hh�h��h��h��h��h  �h �� �� �� �� � h�hh��h��h��h��h� ��h��������ᙙ��� ��h�������������� �hᙙ������� ��h��������������  �h �� �� �� �� � h�hh��h��h��h��h� ��h������������� ��h�������������� ��h�������������� ��h��������������  �h � �� �� �� � h�hh�h��h��h��h� ��h�ᙙ��������� ��h������������� ��h������������� ��h�������������  �h �� �� �� �� � h�hh��h��h��h��h� ��h������������� ��h�������������� ��h�������������� ��h��������������                                                                                                                        !�  � ,    $ & @� 	H����<0��� VXQH��C 1>�(��@�C�tq"BS�\�r�D�	Z �M�41"���Ǒ��<r䈜;�r4鳩ӧP]��ԋ+�T-��N��x�1�:��TdD��^j�W�r���y���V Lx0ت�):8p q܇4;��f`�r-K���(��P̥�tө]�~��lʍ�o��Y��j��G��|;ag�JcՋԨp�z!���{`���K�������^߮�;��/'�w ;  �      �� ���     0 	        (   S   �         T                        �  �   �� �   � � ��  ��� ���   �  �   �� �   � � ��  ��� fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  ffffffffffffffffffffffffff`w ffffffffffff`  fffffffffffffffffffffffff`�wfffffffffff`  fffffffffffffffffffffffffx�wpfffffffffff`  fffffffffffffffffffffff`���wwwfffffffff`  fffffffffffffffffffffffx���wwwpffffffff`  fffffffffffffffffffff`w�����wwwww fffffff`  ffffffffffffffffffff`������wwwwwwffffff`  fffffffffffffffffff`x�������wwwwwww fffff`  ffffffffffffffffff`��������wwwwwwwwffff`  ffffffffffffffffffx�����x��wwwwwwwwpfff`  ffffffffffffffff`w������x���wwwwwwwwwwff`  ffffffffffffffff������x����wwwwwwwwwwpf`  ffffffffffffff`w��������������wwwwwwwwwf`  fffffffffffff`���������������wwwwwwwwwf`  fffffffffffffx������������www�wwwwwwwwf`  fffffffffffff������������wwwwwwx�wwwwwwf`  fffffffffffff������������wwwwwwwxwwwwwwf`  fffffffffffff����������wwwwwwwww�wwwwf`  fffffffffffff���������wwwpxwpwwwwwxwwwwf`  fffffffffffff��������wwwx�wwwwwwww�wwf`  fffffffffffff�������www x��wwwwwwwwx�wf`  fffffffffffff�������wwpw���wwwwwwwwwxwf`  fffffffffffff�����www x�(��wwwwwwwwwwff`  fffffffffffff����wwwpw�����wwwwwwwwwpfff`  fffffffffffff���wwwx�����wwwpwwwwffff`  fffffffffffffo��wwpx������wwwwww fffff`  fffffffffffffff��x�������www wwp ffffff`  ffffffffffffffff x��������wwwww ffffff`  fffffffffffffff`w���������wwwwwwwfffff`  fffffffffffffffx����������wwwwwww ffff`  fffffffffffffff����������wwwwwwwwwfff`  fffffffffffffff�����3���wwwwwwwwfff`  fffffffffffffff�������3���wwwwwpwwwfff`  fffffffffffffff���苸�3���wwwwwwwwwfff`  fffffffffffffff���苸�3���wwwwwwpwwfff`  fffffffffffffff���狋�3���wwwwwwwwwfff`  fffffffffffffff���狷�p���wwwwwwwpwfff`  fffffffffffffff����xw���wwwwwwwwwfff`  fffffffffffffff�������wwwwwwwwpfff`  fffffffffffffff���� �����wwwwwwwwwfff`  fffffffffffffff���������wwwwwwwwwvfff`  fffffffffffffff�����{���爈wwwwwwwwwpfff`  fffffffffffffff������w��x��wwwwwwwwwpfff`  fffffffffffffff�������w����wwwwwwwwwpfff`  fffffffffffffff������爈����wwwwwwwwpfff`  fffffffffffffff�����x��������wwwwwwwpfff`  fffffffffffffff����爈��������wwwwwwpfff`  fffffffffffffff����x����������wwwwwwpfff`  fffffffffffffff��w��������������wwwwwpfff`  fffffffffffffff�����������������wwwwwpfff`  fffffffffffffff�������������������wwwpfff`  fffffffffffffff�������������������wwwpfff`  fffffffffffffff��������������������wwpfff`  fffffffffffffff���������������������wpfff`  fffffffffffffff����������������������pfff`  fffffffffffffff����������������������ffff`  fffffffffffffffo��������������������fffff`  fffffffffffffffff������������������ffffff`  fffffffffffffffffo��o�������������fffffff`  ffffffffffffffffffofff������������fffffff`  fffffffffffffffffffffffffo������fffffffff`  fffffffffffffffffffffffffo����fffffffff`  fffffffffffff`����fffffffffffffffffffffff`  fffffffffffff�����ffffffffffffffffffffff`  fffffffffff`��������fffffffffffffffffffff`  fffffffffff���������ffffffffffffffffffff`  ffffffffff����������fffffffffffffffffff`  fffffffff�������̼�����ffffffffffffffffff`  ffffffff��������������fffffffffffffffff`  fffffff�����������������ffffffffffffffff`  fffffffg���������������ffffffffffffffff`  ffffffffg����������o����wffffffffffffffff`  ffffffffff�������&D����ffffffffffffffff`  ffffffffffg������r�K��w�ffffffffffffffff`  ffffffffffff�����df��wvffffffffffffffff`  fffffffffkffg����F`���ffffffffffffffffff`  ffffffffffffffw������wfffffffffffffffffff`  ffffffffkfff�ff�����ffffffffffffffffffff`  ffffffff�ffkfffg����vffffffffffffffffffff`  fffffffffff�fkfff�ffffffffffffffffffffff`  fffffff�ffkffffffgvffffffffffffffffffffff`  ffffffkfffffkff�fffffffffffffffffffffffff`  fffffffffkfffffffffffffffffffffffffffffff`  ffffff�ffffkff�ffffffffffffffffffffffffff`  fffffkffkffffkfffffffffffffffffffffffffff`  ffffffff�ff�fffffffffffffffffffffffffffff`  fffff�ffff�fkffffffffffffffffffffffffffff`  fffff�f�fffffffffffffffffffffffffffffffff`  ffffkfkff�fkfffffffffffffffffffffffffffff`  ffff�ffffffffffffffffffffffffffffffffffff`  ffffff�f�fkffffffffffffffffffffffffffffff`  ffffff�kffkffffffffffffffffffffffffffffff`  fffffkfkff�ffffffffffffffffffffffffffffff`  fffkfffffkfffffffffffffffffffffffffffffff`  fffkfff�f�fffffffffffffffffffffffffffffff`  fffkf�kfkffffffffffffffffffffffffffffffff`  fffkkfffkffffffffffffffffffffffffffffffff`  fffkkfff�ffffffffffffffffffffffffffffffff`  fffkkf�kfffffffffffffffffffffffffffffffff`  fffkkkfffffffffffffffffffffffffffffffffff`  ffffkkf�fffffffffffffffffffffffffffffffff`  ffffkkf�fffffffffffffffffffffffffffffffff`  ffffkkf�fffffffffffffffffffffffffffffffff`  ffff��kffffffffffffffffffffffffffffffffff`  ffff��kffffffffffffffffffffffffffffffffff`  ffffkf�ffffffffffffffffffffffffffffffffff`  fffff��ffffffffffffffffffffffffffffffffff`  fffffkf�fffffffffffffffffffffffffffffffff`  fffffk��fffffffffffffffffffffffffffffffff`  ffffffkffffffffffffffffffffffffffffffffff`  ffffffk�fffffffffff   ffffffffffffffffff`  fffffff�ffffffffff DDD@fffffffffffffffff`  ffffffff�fffffff`DDDDDDD@ffffffffffffffff`  ffffffffkfffffffLD�DDDDDfffffffffffffff`  fffffffff�ffffft����B$L��Dffffffffffffff`  ffffffffffffffff����",�LB$Fffffffffffffff`  ffffffffff�fffgl����""��B$@ffffffffffffff`  fffffffffffffgf�����"",��"D@fffffffffffff`  fffffffffffk�gf�����"",���$@fffffffffffff`  ffffffffffffkfh�����"""���DDfffffffffffff`  fffffffffffffvfl����""",���Dffffffffffff`  ffffffffffffgfbf���""""",��D@ffffffffffff`  ffffffffffffghh��̂""""",���@ffffffffffff`  ffffffffffffgf�ḧ"""""""�LD@ffffffffffff`  ffffffffffffhf�̈�""""""",�LDffffffffffff`  fffffffffffff�h��"""""""",��Dffffffffffff`  fffffffffffff�o��""""""",,L�Dffffffffffff`  ffffffffffffhh���"""""""�$���ffffffffffff`  fffffffffffffh���/"""""�"$L�$ffffffffffff`  fffffffffffff������""",�"��$Bffffffffffff`  fffffffffffffh����("�""",,B"$ffffffffffff`  ffffffffffffgh���",�"�"""�"B ffffffffffff`  ffffffffffffg����",��",","$$@ffffffffffff`  fffffffffffff���""�""�,�"$$ffffffffffff`  fffffffffffffx�/�""""",,�""Bfffffffffffff`  fffffffffffffo���"""""""""$$fffffffffffff`  fffffffffffffg��""",�"""""$ fffffffffffff`  ffffffffffffffvo�"""""""""$fffffffffffff`  fffffffffffffff���,"""""""&ffffffffffffff`  fffffffffffffffh","""""""vffffffffffffff`  ffffffffffffffff��"""""�vfffffffffffffff`  ffffffffffffffffg���"�",�ffffffffffffffff`  fffffffffffffffffw����&gvffffffffffffffff`  fffffffffffffffffffwwwvffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`  fffffffffffffffffffffffffffffffffffffffff`        �� ��j     0	        � Ȁ         A>     E x p l o r e r   U s e r   P r o m p t    M S   S h e l l   D l g   � �P     * 3 l ���        P     2   ��� O K         P     2   ��� C a n c e l         P      � 
 ����� J a v a S c r i p t   P r o m p t :         P      �  k ���       �       �� ��     0	        @��     ( ( x (     P r i n t   C a n c e l    M S   S h e l l   D l g    P      x  ����� C a n c e l   P r i n t i n g       P    ,      ��� C a n c e l       N      �� ���     0	        �ɀ     < < � k     F i l e   D o w n l o a d    M S   S h e l l   D l g       P        � ��� ���   �  P     & � 
 � ��� G e t t i n g   F i l e   I n f o r m a t i o n :       P     0 � 
 � ���         �@     : �  � m s c t l s _ p r o g r e s s 3 2         �  @     D < 
 � ��� F i l e   s i z e   u n k n o w n     �  P     D A 
 ����� E s t i m a t e d   t i m e   l e f t :       �  P     N A 
 ����� D o w n l o a d   t o :       �  P     X A 
 ����� T r a n s f e r   r a t e :       �  P    K D � 
 � ���       �  P    K N � 
 � ���       �  P    K X U 
 � ���       �      �� ���     0	        �
Ȁ   � < < � k     F i l e   D o w n l o a d    M S   S h e l l   D l g       P    <  �  ����� Y o u   h a v e   c h o s e n   t o   d o w n l o a d   a   f i l e   f r o m   t h i s   l o c a t i o n .         P    <  �  � ���         P      2 Z ����� ���     P    < + �  ����� W h a t   w o u l d   y o u   l i k e   t o   d o   w i t h   t h i s   f i l e ?     	  P    < 8 � 
 � ��� & R u n   t h i s   p r o g r a m   f r o m   i t s   c u r r e n t   l o c a t i o n     	  P    < D � 
 � ��� & S a v e   t h i s   p r o g r a m   t o   d i s k        P    < P �  � ��� A l & w a y s   a s k   b e f o r e   o p e n i n g   t h i s   t y p e   o f   f i l e       @      �� ��     0	                 I e c e u i 
 i e u i   C l a s s      R e p o s t   f o r m   d a t a ?  M i c r o s o f t   I n t e r n e t   E x p l o r e r       � T h i s   f o r m   i s   b e i n g   s u b m i t t e d   u s i n g   e - m a i l . 
 S u b m i t t i n g   t h i s   f o r m   w i l l   r e v e a l   y o u r   e - m a i l   a d d r e s s   t o   t h e   r e c i p i e n t , 
 a n d   w i l l   s e n d   t h e   f o r m   d a t a   w i t h o u t   e n c r y p t i n g   i t   f o r   p r i v a c y . 
 
 Y o u   m a y   c o n t i n u e   o r   c a n c e l   t h i s   s u b m i s s i o n . � A n   A c t i v e X   c o n t r o l   o n   t h i s   p a g e   i s   n o t   s a f e .     
 Y o u r   c u r r e n t   s e c u r i t y   s e t t i n g s   p r o h i b i t   r u n n i n g   u n s a f e   c o n t r o l s   o n   t h i s   p a g e .     
 A s   a   r e s u l t ,   t h i s   p a g e   m a y   n o t   d i s p l a y   a s   i n t e n d e d . � T h i s   p a g e   p r o v i d e s   p o t e n t i a l l y   u n s a f e   i n f o r m a t i o n   t o   a n   A c t i v e X   c o n t r o l .     Y o u r   c u r r e n t   s e c u r i t y   s e t t i n g s   p r o h i b i t   r u n n i n g   c o n t r o l s   i n   t h i s   m a n n e r .     A s   a   r e s u l t ,   t h i s   p a g e   m a y   n o t   d i s p l a y   c o r r e c t l y . �      �� ��     0	         D o c u m e n t  % 1 ! s !   D o c u m e n t  % 1 ! s !   ( % 2 ! s !   c o p i e d ) 
 % 1   f r o m   % 2 + N o   d e s c r i p t i o n   i s   a v a i l a b l e   f o r   t h i s   e r r o r . 7 I n t e r n e t   E x p l o r e r   c a n n o t   o p e n   t h e   I n t e r n e t   s i t e   % 1 . 
 
 % 2     - U n e x p e c t e d   c a l l   t o   m e t h o d   o r   p r o p e r t y   a c c e s s .  U n s p e c i f i e d   e r r o r .  I n v a l i d   a r g u m e n t . r C a n ' t   m o v e   f o c u s   t o   t h e   c o n t r o l   b e c a u s e   i t   i s   i n v i s i b l e ,   n o t   e n a b l e d ,   o r   o f   a   t y p e   t h a t   d o e s   n o t   a c c e p t   t h e   f o c u s . $ T h e   c o n t r o l   n e e d s   t o   h a v e   t h e   f o c u s . " T h e   v a l u e   i s   n o t   a   p i c t u r e   o b j e c t .  T h e   p i c t u r e   t y p e   i s   n o t   v a l i d .  I n v a l i d   p r o p e r t y   a r r a y   i n d e x .   �      �� ��     0	        � Y o u r   c u r r e n t   s e c u r i t y   s e t t i n g s   p r o h i b i t   r u n n i n g   A c t i v e X   c o n t r o l s   o n   t h i s   p a g e .     A s   a   r e s u l t ,   t h e   p a g e   m a y   n o t   d i s p l a y   c o r r e c t l y .  % 2       @ I n t e r n e t   E x p l o r e r   c a n n o t   d o w n l o a d   f r o m   t h e   I n t e r n e t   s i t e   % 1 . 
 
 % 2   5 T h i s   i t e m   c a n n o t   b e   d i s p l a y e d . 
 
 T r y   a   d i f f e r e n t   i t e m . D C a n n o t   f i n d   ' % 1 ' .   M a k e   s u r e   t h e   p a t h   o r   I n t e r n e t   a d d r e s s   i s   c o r r e c t . ` C a n n o t   s t a r t   t h e   O L E   s e r v e r   f o r   t h i s   t y p e   o f   d o c u m e n t . 
 % 1 
 
 D o   y o u   w a n t   t o   d o w n l o a d   i t   a s   a   f i l e ? ^ T h e   a s s o c i a t e d   O L E   s e r v e r   c a n n o t   l o a d   t h i s   d o c u m e n t . 
 % 1 
 
 D o   y o u   w a n t   t o   d o w n l o a d   i t   a s   a   f i l e ?  S e c u r i t y   A l e r t G Y o u r   c u r r e n t   s e c u r i t y   s e t t i n g s   d o   n o t   a l l o w   t h i s   f i l e   t o   b e   d o w n l o a d e d .  D o w n l o a d   c o m p l e t e 
 % 1 ^ T h e   W e b   p a g e   y o u   a r e   v i e w i n g   i s   t r y i n g   t o   c l o s e   t h e   w i n d o w . 
 
 D o   y o u   w a n t   t o   c l o s e   t h i s   w i n d o w ?   :       �� ��	     0	         F i l e   D o w n l o a d                                 �      �� ��     0	         I n v a l i d   p r o p e r t y   v a l u e . * T h i s   m e t h o d   c a n ' t   b e   u s e d   i n   t h i s   c o n t e x t . 	 O v e r f l o w .  P e r m i s s i o n   d e n i e d .   C a n   n o t   s e t   p r o p e r t y   a t   r u n t i m e . ) I n v a l i d   t a r g e t   e l e m e n t   f o r   t h i s   o p e r a t i o n & I n v a l i d   s o u r c e   H T M L   f o r   t h i s   o p e r a t i o n E T h e   c o n t r o l   c o u l d   n o t   b e   c r e a t e d   b e c a u s e   i t   i s   n o t   p r o p e r l y   l i c e n s e d .  T h i s   c o m m a n d   i s   n o t   s u p p o r t e d . < T h i s   a d d r e s s   i s   n o t   v a l i d .   C h e c k   t h e   a d d r e s s ,   a n d   t r y   a g a i n . H T h e   s i t e   w a s   n o t   f o u n d .   M a k e   s u r e   t h e   a d d r e s s   i s   c o r r e c t ,   a n d   t r y   a g a i n . e T h e   p r o t o c o l   s p e c i f i e d   i n   t h i s   a d d r e s s   i s   n o t   v a l i d .   M a k e   s u r e   t h e   a d d r e s s   i s   c o r r e c t ,   a n d   t r y   a g a i n . B T h e   s i t e   w a s   f o u n d   b u t   e x c e e d e d   t h e   s y s t e m   l i m i t s   f o r   r e d i r e c t i o n .         ,      �� ��     0	        4 C o u l d   n o t   c o m p l e t e   t h e   o p e r a t i o n   d u e   t o   e r r o r   % 1 ! X ! . x A r e   y o u   s u r e   y o u   w a n t   t o   n a v i g a t e   a w a y   f r o m   t h i s   p a g e ? 
 
 % s 
 
 P r e s s   O K   t o   c o n t i n u e ,   o r   C a n c e l   t o   s t a y   o n   t h e   c u r r e n t   p a g e . � A   s c r i p t   o n   t h i s   p a g e   i s   c a u s i n g   I n t e r n e t   E x p l o r e r   t o   r u n   s l o w l y .     I f   i t   c o n t i n u e s   t o   r u n ,   y o u r   c o m p u t e r   m a y   b e c o m e   u n r e s p o n s i v e . 
 
 D o   y o u   w a n t   t o   a b o r t   t h e   s c r i p t ?  C o u l d   n o t   s a v e   t h e   p i c t u r e .  C o u l d   n o t   s e t   t h e   w a l l p a p e r .                       �      �� ��
     0	                 D o w n l o a d   c o u l d   n o t   c o m p l e t e ! 	 % 1 ! s ! / S e c  T e m p o r a r y   F o l d e r 	 A l l   F i l e s  S a v i n g :  O p e n i n g :  % 1 ! s !   o f   % 2 ! s !   C o p i e d  % 1 ! d ! % %   o f   % 2 ! s !   C o m p l e t e d  N o t   k n o w n   ( O p e n e d   s o   f a r   % 1 ! s ! ) ) & O p e n   t h i s   f i l e   f r o m   i t s   c u r r e n t   l o c a t i o n  & S a v e   t h i s   f i l e   t o   d i s k     �      �� ��    0	        < T h i s   a d d r e s s   i s   n o t   v a l i d .   C h e c k   t h e   a d d r e s s ,   a n d   t r y   a g a i n . H T h e   s i t e   w a s   n o t   f o u n d .   M a k e   s u r e   t h e   a d d r e s s   i s   c o r r e c t ,   a n d   t r y   a g a i n . e T h e   p r o t o c o l   s p e c i f i e d   i n   t h i s   a d d r e s s   i s   n o t   v a l i d .   M a k e   s u r e   t h e   a d d r e s s   i s   c o r r e c t ,   a n d   t r y   a g a i n . B T h e   s i t e   w a s   f o u n d   b u t   e x c e e d e d   t h e   s y s t e m   l i m i t s   f o r   r e d i r e c t i o n . � T h e   d o w n l o a d e d   f i l e   i s   n o t   a v a i l a b l e .   T h i s   c o u l d   b e   d u e   t o   y o u r   S e c u r i t y   o r   L a n g u a g e   s e t t i n g s   o r   b e c a u s e   t h e   s e r v e r   w a s   u n a b l e   t o   r e t r i e v e   t h e   r e q u e s t e d   f i l e                       