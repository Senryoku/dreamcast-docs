VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "TestClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
' >> L'affichage complet du module donne de meilleurs r�sultats. <<
'
' Stockage pour le num�ro ID de d�bogage.
Private mlngDebugID As Long
Implements IDebug

' Stockage priv� pour le type d�fini par
'   l'utilisateur (UDT) pass� entre
'   les objets. Le type d�fini par l'utilisateur
'   est d�clar� en tant que Public dans un
'   module standard (reportez-vous au module
'   modFriends). Dans cet exemple, mDemo
'   sert de stockage pour la propri�t� Demo,
'   ainsi que pour la combinaison
'   Fonction/Proc�dure de GetDemo/SetDemo.
Private mDemo As udtDEMO

' Propri�t� Demo: les propri�t�s Get et Let
' -------------     de la propri�t� Demo
'   montre la mani�re dont les proc�dures
'   de propri�t� d�clar�es au moyen du mot
'   cl� Friend peuvent accepter et renvoyer
'   un type d�fini par l'utilisateur.
Friend Property Get Demo() As udtDEMO
    Demo = mDemo
End Property
' Vous remarquerez que l'argument de la propri�t�
'   Let doit �tre ByRef pour un type d�fini par
'   l'utilisateur.
Friend Property Let Demo(NewDemo As udtDEMO)
    mDemo = NewDemo
End Property

' Les propri�t�s GetDemo and SetDemo
' -------------------   montrent comment
'   les fonctions Friend peuvent renvoyer
'   des types d�finis par l'utilisateur,
'   et comment ces UDT peuvent �tre
'   des arguments des proc�dures Friend.
Friend Function GetDemo() As udtDEMO
    GetDemo = mDemo
End Function
' Vous remarquerez qu'un type d�fini par
'   l'utilisateur pour une proc�dure
'   doit �tre d�clar� comme ByRef.
Friend Sub SetDemo(NewDemo As udtDEMO)
    mDemo = NewDemo
End Sub

' SetDemoParts est une m�thode d'aide destin�e
' ------------      � remplir les �l�ments
'   du type d�fini par l'utilisateur, pour
'   permettre leur passage. Dans une vraie
'   application, les �l�ments du type d�fini
'   par l'utilisateur devront �tre remplis
'   par code dans l'objet TestClass.
Public Sub SetDemoParts(ByVal A As Integer, _
        ByVal B As Long, ByVal C As String)
    mDemo.intA = A
    mDemo.lngB = B
    mDemo.strC = C
End Sub

' La m�thode ShowDemo affiche les �l�ments du type
' --------      d�fini par l'utilisateur;
'   ils pourront ainsi �tre affich�s apr�s
'   le passage du type au deuxi�me objet.
Public Sub ShowDemo(ByVal Title As String, _
        ByVal Direction As String)
        
    MsgBox Direction & "  " _
        & GetDebugString(Me) & vbCrLf & vbCrLf _
        & mDemo.intA & vbCrLf _
        & mDemo.lngB & vbCrLf _
        & mDemo.strC, , Title
End Sub

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
'
Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property

