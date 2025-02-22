VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Employees"
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

' Collection priv� effectuant la totalit�
'   du travail.
Private colEmployees As New Collection

' La m�thode NewEnum rend possible l'utilisation de
' -------       l'instruction For Each avec la classe
'   de la collection Employees. Pour plus d'informations,
'   reportez-vous � la section "Cr�ation de votre propre classe
'   Collection : la maison en briques" des Manuels en ligne.
'
' Pour que la m�thode NewEnum travaille correctement, son
'   identificateur de proc�dure doit �tre -4. Pour v�rifier
'   cela, cliquez sur Attributs de Proc�dure
'   dans le menu Outils. Dans la zone Nom,
'   cliquez sur l'�l�ment, puis sur le bouton
'   Avanc�s. Vous pouvez voir que l'identificateur
'   de proc�dure est -4. (L'option Masquer ce
'   membre est coch�e �galement; la m�thode
'   NewEnum est donc cach�e dans l'Explorateur
'   d'objets.)
Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
    ' D�l�gue vers la m�thode _NewEnum de
    '   l'objet Collection priv�.
    Set NewEnum = colEmployees.[_NewEnum]
End Function

' La m�thode Add cr�� un nouvel employ�
' ---       dans la collection.
'
Public Function Add(ByVal Name As String, _
                ByVal Salary As Double) As Employee
    Dim empNew As New Employee
    Static intEmpNum As Integer
    ' L'utilisation de With raccourcit les r�f�rences � la propri�t� (.ID au lieu de empNew.ID)
    ' et acc�l�re l'ex�cution.
    With empNew
        ' G�n�re un identificateur unique pour le nouvel employ�.
        intEmpNum = intEmpNum + 1
        .ID = "E" & Format$(intEmpNum, "00000")
        .Name = Name
        .Salary = Salary
        ' Ajoute la r�f�rence de l'objet Employee � la collection,
        ' en utilisant sa propri�t� ID comme cl�.
        colEmployees.Add empNew, .ID
    End With
    ' Renvoyer une r�f�rence du nouveau membre est une bonne solution.
    Set Add = empNew
End Function

' Pour v�rifier comment la m�thode Item est devenue
'   la m�thode par d�faut pour la collection Employees,
'   cliquez sur Attributs de Proc�dure
'   dans le menu Outils. Dans la zone Nom,
'   cliquez sur l'�l�ment, puis sur le bouton
'   Avanc�s. Vous pouvez voir que (D�faut)
'   est s�lectionn� dans la zone ID
'   de proc�dure.
Public Function Item(ByVal Index As Variant) As Employee
    Set Item = colEmployees.Item(Index)
End Function

Public Function Count() As Long
    Count = colEmployees.Count
End Function

Public Sub Delete(ByVal Index As Variant)
    colEmployees.Remove Index
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

Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


