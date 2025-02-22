VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Triangle"
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

' La classe Triangle impl�mente l'interface
'   IShape et Polygon. Un objet Polygon
'   interne est maintenu et de nombreuses
'   activit�s sont d�l�gu�es (dessin,
'   stockage des points, etc). La propre
'   interface de la classe Triangle n'a
'   qu'une m�thode.

Implements IShape
Implements Polygon

' L'objet Polygon interne maintient
'   les donn�es et fait une grande
'   partie des op�rations. L'objet
'   Triangle garde des r�f�rences pour
'   les deux interfaces Polygon et IShape
'   de l'objet Polygon interne.
Private mpyg As Polygon
Private mish As IShape

' -------------------------------------
' L'impl�mentation de l'interface IShape
'   d�marre ici.

' La proc�dure IShape.DrawToPictureBox
' ------ ----------------   est appel�e pour
'   dessiner une forme; chaque classe de
'   forme doit donc fournir sa propre
'   impl�mentation.
'
Private Sub IShape_DrawToPictureBox(ByVal pb As PictureBox)
    ' D�l�gue � l'interface IShape de
    '   l'objet Polygon interne.
    Call mish.DrawToPictureBox(pb)
End Sub

' La m�thode IShape.TimeTest est utilis�e
' ====== --------       pour afficher la
'   d�pr�ciation r�duite de performances
'   de l'appel d'une m�thode appel�e sur
'   une interface qui impl�mente plusieurs
'   classes, en opposition � l'appel
'   d'une m�thode semblable sur les interfaces
'   par d�faut des classes.
'
Private Sub IShape_TimeTest()
End Sub

' -------------------------------------
' L'impl�mentation de l'interface Polygon
'   d�marre ici.

' Polygon.Color d�l�gue � l'objet
' ======= -----     Polygon interne.
'
Private Property Get Polygon_Color() As Long
    Polygon_Color = mpyg.Color
End Property
'
Private Property Let Polygon_Color(ByVal RHS As Long)
    mpyg.Color = RHS
End Property

' Polygon.TimeTest - L'objet Triangle dispose
' ======= --------  de trois m�thodes TimeTest:
'   une sur l'interface IShape (pour afficher
'   le polymorphisme et les liaisons pr�coces),
'   une sur sa propre interface (pour afficher
'   les liaisons tardives) et celle-ci qui est
'   le r�sultat de l'impl�mentation de l'interface
'   Polygon par l'objet Rectangle; elle n'est pas
'   utilis�e du tout.
Private Sub Polygon_TimeTest()
End Sub

' Polygon.GetPoint
' ======= --------
'
Private Sub Polygon_GetPoint(ByVal intPoint As Integer, X As Single, Y As Single)
    ' D�l�gue � l'objet Polygon interne.
    Call mpyg.GetPoint(intPoint, X, Y)
End Sub

' Polygon.GetPointCount
' ======= -------------
'
Private Property Get Polygon_GetPointCount() As Integer
    ' Il n'y a pas de point lors de la
    '   d�l�gation � l'objet Polygon interne:
    '   un triangle est toujours
    '   d�fini par trois points.
Polygon_GetPointCount = 3
End Property

' Polygon.SetPoints - Lors de l'impl�mentation
' ======= ---------     de la m�thode SetPoints
'   de l'interface Polygon, l'objet Triangle
'   ex�cute son propre code pour v�rifier que
'   le tableau d'entr�e contient uniquement
'   trois points (six Single), et d�l�gue
'   ensuite � l'objet Polygon interne.
Private Sub Polygon_SetPoints(asngPoints() As Single)
    Dim blnBadArray As Boolean
    On Error Resume Next
    If UBound(asngPoints) <> 5 Then blnBadArray = True
    If Err.Number <> 0 Then blnBadArray = True
    If blnBadArray Then
        Err.Raise vbObjectError + 2082, , _
            " Un triangle est sp�cifi� par un tableau commen�ant � z�ro avec six �l�ments, les valeurs paires (0 y compris) correspondant aux valeurs X et les valeurs impaires aux valeurs Y."
        Exit Sub
    End If
    ' D�l�gue � l'objet Polygon interne, qui
    '   effectue la validation du tableau
    '   et le stocke.
    Call mpyg.SetPoints(asngPoints)
End Sub

' --------------------------------------
' La propre interface (par d�faut) de
'   l'objet Triangle d�marre ici.

' La m�thode TimeTest ne prend pas
' --------   d'arguments, ne fait rien
'   et effectue imm�diatement un renvoi.
'   Elle montre une liaison tardive, en
'   opposition � la liaison pr�coce
'   fournie en appelant la m�thode
'   TimeTest sur l'interface IShape.
Public Sub TimeTest()
End Sub

' --------------------------------------
' Les proc�dures priv�es de la classe
'   Triangle (proc�dure d'aide et
'   proc�dure d'�v�nement) d�marrent ici.

Private Sub Class_Initialize()
    Dim asngPoints(0 To 5) As Single
    ' Code de d�bogage.
    mlngDebugID = DebugInit(Me)
    '
    ' Cr�e l'objet Polygon interne, et
    '   obtient une r�f�rence � son
    '   interface IShape.
    Set mpyg = New Polygon
    Set mish = mpyg
    ' Initialise l'objet Polygon interne.
    Call mpyg.SetPoints(asngPoints)
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


