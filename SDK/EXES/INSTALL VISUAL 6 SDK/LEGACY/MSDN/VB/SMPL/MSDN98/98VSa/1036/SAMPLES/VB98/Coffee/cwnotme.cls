VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "NotifyMe"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' La classe NotifyMe impl�mente ICoffeeNotify de
'   sorte que sa m�thode de rappel
'   (CoffeeReady) peut �tre appel�e
'   au moyen d'une liaison pr�coce.
Implements ICoffeeNotify

' Stockage pour l'impl�mentation de NotifyID.
Private mlngNotifyID As Long

' La m�thode ICoffeeNotify.CoffeeReady est appel� par
' ============= -----------     l'objet
'   CoffeeMonitor2 dans Coffee2. Cette
'   impl�mentation ajoute l'heure de l'appel
'   � la zone de liste et efface le cas
'   �ch�ant les anciennes entr�es.
'
Private Sub ICoffeeNotify_CoffeeReady()
    With Form1.lstCallBacks
        .AddItem Format$(Now, "ddd hh:mm:ss"), 0
        If .ListCount > 10 Then .RemoveItem 10
    End With
End Sub

' La propri�t� ICoffeeNotify.NotifyID
' ============= --------       maintient
'   la cl� de l'objet de la notification
'   dans le tableau CoffeeMonitor2 des
'   objets du client. L'impl�mentation
'   du client ne fait que stocker et
'   renvoyer la valeur.
'
Private Property Let ICoffeeNotify_NotifyID(ByVal RHS As Long)
    mlngNotifyID = RHS
End Property
'
Private Property Get ICoffeeNotify_NotifyID() As Long
    ICoffeeNotify_NotifyID = mlngNotifyID
End Property
