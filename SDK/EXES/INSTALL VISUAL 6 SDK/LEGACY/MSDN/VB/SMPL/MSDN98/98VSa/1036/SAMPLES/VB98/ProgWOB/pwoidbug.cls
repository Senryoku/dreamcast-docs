VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "IDebug"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' L'interface IDebug est impl�ment�e par tous
' ======    les objets du projet. Elle
'   contient des m�thodes et des propri�t�s
'   de d�bogage (ProgWOb dispose seulement
'   de l'une d'entre elles: la propri�t� DebugID).
'
' Pourquoi une interface s�par�e? Dans ce
'   projet, la classe Polygon est utilis�e
'   de deux fa�ons: les objets Polygon sont
'   cr��s, et l'interface Polygon est
'   impl�ment�e par deux autres classes.
'   En pla�ant une propri�t� DebugID sur
'   l'interface Polygon par d�faut, nous
'   pourrions tout � fait  placer des
'   propri�t�s DebugID simul�es sur ces
'   impl�mentations, comme nous l'avons
'   fait avec la m�thode TimeTest.
'
' Une interface s�par�e ne demande qu'une
'   ligne de code suppl�mentaire (l'instruction
'   Implements IDebug) par rapport � l'ajout
'   de la propri�t� DebugID sur l'interface
'   par d�faut de chaque classe
'
'
' La propri�t� DebugID est impl�ment�e en
' -------       fournissant une variable
'   de type Long pour stocker l'identificateur
'   de d�bogage, et en appelant la propri�t�
'   DebugInit pour d�finir l'identificateur
'   (dans l'�v�nement Initialize).
'
Public Property Get DebugID() As Long
End Property
