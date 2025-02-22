VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "SmallBusiness3"
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

' La collection Employees de type Private
'   maintient les objets Employee.
Private emps As New Employees

' Plut�t que de d�clarer une variable Employees
'   de type Public en tant que New Employees,
'   il est pr�f�rable de coder la proc�dure
'   pour obtenir une collection priv�e et
'   cr�er une propri�t� en lecture seule
'   pour renvoyer la collection Employees.
'   Ainsi, la collection ne peut �tre lib�r�e
'   accidentellement en affectant la valeur
'   Nothing � la variable de type Public.
Public Property Get Employees() As Employees
    Set Employees = emps
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
'   d�clar�es dans module modFriend.
'
Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


