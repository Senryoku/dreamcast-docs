VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Widget"
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

' Les num�ros d'erreur d�finis dans
'   une instruction Enum de type Public
'   sont visibles dans la totalit�
'   du projet.
Public Enum WidgetErrors
    wdgERRTaskCanceled = 1059
End Enum

' L'�v�nement PercentDone est d�clench� �
'   intervalles r�guliers pendant la m�thode
'   LongTask, pour informer l'appelant de
'   l'avancement. L'�v�nement dispose d'un
'   argument de pourcentage complet et d'un
'   argument ByRef Cancel auxquels l'appelant
'   peut affecter la valeur True pour annuler
'   la m�thode LongTask.
Event PercentDone(ByVal Percent As Double, _
    Cancel As Boolean)
    
' La m�thode LongTask simule une t�che longue
' --------      qui d�clenche l'�v�nement
'   PercentDone et permet � l'appelant
'   d'annuler l'op�ration.
'
' Le premier argument demande � la m�thode
'   LongTask de d�finir la dur�e de simulation
'   de la t�che, que vous avez choisie. Le
'   deuxi�me argument d�finit le temps minimum
'   devant s'�couler avant de d�clencher des
'   �v�nements qui informent l'appelant de
'   l'avancement.
'
' L'utilisation d'intervalles de temps
'   pour d�terminer le moment o� les
'   �v�nements doivent �tre d�clench�s
'   donne des r�sultats plus probants
'   sur diff�rents ordinateurs. Pour une
'   approche diff�rente, reportez-vous �
'   la m�thode LongTask2.
'
Public Sub LongTask(ByVal Duration As Double, _
        ByVal MinimumInterval As Double)
    Dim dblThreshold As Double
    Dim dblStart As Double
    Dim blnCancel As Boolean
    
    dblStart = Timer
    dblThreshold = MinimumInterval
    
    Do While Timer < (dblStart + Duration)
        ' Dans une application r�elle, une
        '   portion du travail serait faite ici.
        '   Le travail doit �tre divis� en portions
        '   (unit�s) qui ne sont ni trop grandes
        '   (trop longues entre les notifications),
        '   ni trop petites (plus les tests sont
        '   nombreux, moins la m�thode LongTask
        '   est efficace).
        
        ' Apr�s chaque unit� de travail, faites un
        '   test pour v�rifier s'il convient
        '   d'informer l'appelant de l'avancement
        '   de la m�thode LongTask.
        If Timer > (dblStart + dblThreshold) Then
            ' D�clenche l'�v�nement; l'ex�cution de
            '   la m�thode LongTask sera interrompue
            '   jusqu'au renvoi de la proc�dure
            '   d'�v�nement de l'appelant!
            RaiseEvent PercentDone( _
                dblThreshold / Duration, _
                blnCancel)
            '
            ' Fait un test pour v�rifier si l'appelant
            '   veut annuler la m�thode LongTask.
            If blnCancel Then
                Err.Raise vbObjectError + wdgERRTaskCanceled, , _
                    "T�che annul�e"
' NOTE: Si votre programme s'arr�te ici, faites
'   un clic droit pour faire appara�tre le menu
'   contextuel de la fen�tre Code. Cliquez sur
'   Activer, puis sur Arr�t sur les erreurs non
'   g�r�es. Appuyez sur F5 pour continuer
'   l'ex�cution du programme (vous devez appuyer
'   sur Alt+Tab pour rappeler la feuille frmEvents).
'   Explications: l'option par d�faut, Arr�t dans
'   les modules de classe, est tr�s utile si vous
'   obtenez une erreur lors d'un appel � une
'   m�thode d'une classe, car elle permet � Visual
'   Basic de provoquer un arr�t � l'INT�RIEUR du
'   module de classe, � l'endroit de l'erreur. Rien
'   n'est plus pratique que de voir la classe
'   d�clencher des erreurs automatiquement, comme
'   ici!
' Vous pouvez d�finir l'option par d�faut Arr�t
'   sur les erreurs non g�r�es dans l'onglet
'   G�n�ral de la bo�te de dialogue Options,
'   accessible � partir du menu Outils. En
'   faisant cela, n'oubliez pas que lorsque vous
'   effectuez un arr�t sur un appel de m�thode,
'   et que vous voulez aller � l'endroit o�
'   l'erreur s'est produite, vous pouvez utiliser
'   le menu contextuel de la fen�tre Code pour
'   activer l'option Arr�t dans les modules de
'   classe.
' Note: Vous pouvez �galement utiliser la combinaison
'   Alt+F5 pour ignorer une erreur en utilisant
'   l'option Arr�t dans les modules de classe
'   (ou Alt+F8 pour ignorer l'erreur et continuer
'   le d�bogage). Si ces touches ne provoquent
'   de d�placement dans le code, aucun gestionnaire
'   d'erreur n'est disponible. Pour plus
'   d'informations, reportez-vous � la section
'   "D�bogage des modules de classe" des
'   Manuels en ligne.
' [Fin de la digression]
            End If
            '
            ' D�finit le seuil pour la
            '   notification suivante.
            dblThreshold = dblThreshold + MinimumInterval
       End If
    Loop
End Sub
 
' La m�thode LongTask2 simule �galement
' ---------     une t�che longue qui
'   d�clenche l'�v�nement PercentDone
'   et permet � l'appelant d'annuler
'   l'op�ration.
'
' La t�che simul�e consiste en des calculs
'   r�p�t�s en virgule flottante. Le
'   premier argument demande � la m�thode
'   LongTask2 de d�finir le nombre d'it�rations
'   de la t�che, que vous avez choisi. Le
'   deuxi�me argument donne les modifications
'   du pourcentage, qui d�clenche l'�v�nement
'   de notification. Vous remarquerez que cette
'   m�thode est le r�sultat d'une longueur
'   variable de temps entre les notifications,
'   une variation qui peut comprendre les
'   diff�rences des performances des machines.
'
' En revanche, la m�thode LongTask
'   utilise un intervalle de temps pour
'   d�terminer la fr�quence de d�clenchement
'   de l'�v�nement; cela donne des r�sultats
'   plus probants sur diff�rents ordinateurs.
'
Public Sub LongTask2(ByVal Iterations As Long, _
        ByVal PercentChange As Byte)
    Dim lngThreshold As Long
    Dim dblIterationsPerEvent As Double
    Dim lngCt As Long
    Dim dblDummy As Double
    Dim blnCancel As Boolean
    
    dblIterationsPerEvent = Iterations _
        * (CDbl(PercentChange) / 100)
    lngThreshold = dblIterationsPerEvent
    
    For lngCt = 1 To Iterations
        ' Dans une application r�elle, une
        '   portion du travail serait faite ici.
        '   Le travail doit �tre divis� en portions
        '   (unit�s) qui ne sont ni trop grandes
        '   (trop longues entre les notifications),
        '   ni trop petites (plus les tests sont
        '   nombreux, moins la m�thode LongTask
        '   est efficace).
        dblDummy = 3.14159 * 2640 * 2640
        
        ' Apr�s chaque unit� de travail, faites un
        '   test pour v�rifier s'il convient
        '   d'informer l'appelant de l'avancement
        '   de la m�thode LongTask.
        If lngCt > lngThreshold Then
            ' D�clenche l'�v�nement; l'ex�cution de
            '   la m�thode LongTask2 sera interrompue
            '   jusqu'au renvoi de la proc�dure
            '   d'�v�nement de l'appelant!
            RaiseEvent PercentDone( _
                lngCt * 100 / Iterations, _
                blnCancel)
            '
            ' Fait un test pour v�rifier si l'appelant
            '   veut annuler la m�thode LongTask2.
            If blnCancel Then
                Err.Raise vbObjectError + wdgERRTaskCanceled, , _
                    " T�che annul�e "
            End If
            '
            ' D�finit le seuil pour la
            '   notification suivante.
            lngThreshold = lngThreshold + dblIterationsPerEvent
        End If
    Next
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


