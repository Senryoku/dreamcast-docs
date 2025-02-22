VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Employee"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
' >> L'affichage complet du module donne de meilleurs r�sultats. <<
'
' Stockage pour le num�ro ID de d�bogage.
Private mlngDebugID As Long
Implements IDebug

' Propri�t�s de la classe Employee.
Public Name As String
Public Salary As Double

' Donn�es priv�es pour la propri�t� ID d�finie une seule fois.
Private mstrID As String

Property Get ID() As String
    ID = mstrID
End Property
'
' La premi�re fois que la propri�t� ID est
' d�finie, la variable statique de type Boolean est �galement
' d�finie. Les appels suivants ne font rien.
'(Il serait pr�f�rable de d�clencher une erreur.)
Property Let ID(strNew As String)
    Static blnAlreadySet As Boolean
    If Not blnAlreadySet Then
        blnAlreadySet = True
        mstrID = strNew
    End If
End Property

Private Sub Class_Initialize()
    mlngDebugID = DebugInit(Me)
End Sub

Private Sub Class_Terminate()
    DebugTerm Me
End Sub

' -------- Impl�mentation de IDebug --------
'
' IDebug.DebugID permet de distinguer
' ====== -------    les diff�rents objets. Il
'   est requis par les proc�dures de d�bogage
'   DebugInit, DebugTerm et DebugShow
'   d�clar�es dans le module modFriend.

Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


