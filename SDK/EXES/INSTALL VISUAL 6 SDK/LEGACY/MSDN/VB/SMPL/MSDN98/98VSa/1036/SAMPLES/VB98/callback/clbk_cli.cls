VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CbClientClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
' Cette classe interne est cr��e par le client et pass�e au composant distant.
' Le composant distant se fixe � elle et l'alimente � intervalles r�guliers.
' Note: les propri�t�s de la classe (appuyez sur F4) marquent cette classe comme Public.
' Cela lui permet d'�tre utilis� par l'horloge externe du syst�me externe.

Private Sub class_terminate()
  Debug.Print "CbClientProj.CbClientClass Termin�."
End Sub

Private Sub class_initialize()
  Debug.Print "CbClientProj.CbClientClass Initialis�."
End Sub

Public Sub TellTime(sCurTime As String)
  ' Il s'agit de la m�thode *public* que le composant appelle pour
  ' mettre � jour l'heure du client. Dans un sc�nario r�el, le
  ' composant ferait des op�rations un peu plus importantes, telles
  ' que la fourniture de cotations boursi�res, la proposition de
  ' nouveaux articles � des utilisateurs, ou des rapports
  ' d'activit�. Notez cependant que si cette proc�dure n'est pas
  ' marqu�e comme Public, le composant ne pourra pas l'appeler.
  
    frmCBCli.lblTime.Caption = sCurTime
End Sub

