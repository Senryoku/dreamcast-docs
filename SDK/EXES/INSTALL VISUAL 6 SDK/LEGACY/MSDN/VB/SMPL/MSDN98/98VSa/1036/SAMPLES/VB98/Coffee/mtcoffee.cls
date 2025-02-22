VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Coffee"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Private Declare Function timeGetTime Lib "winmm.dll" () As Long

' L'objet Coffee pr�sente, par rapport � ce
'   qu'effectue l'objet CoffeeMonitors, un
'   style diff�rent de notifications asynchrones.
'   Au lieu des notifications p�riodiques,
'   l'objet Coffee fournit des rapports de
'   progression sur une t�che longue, ainsi
'   qu'un �v�nement d'ach�vement.
'
' Le m�canisme utilis� pour ces notifications est
'   de d�clencher des �v�nements.
'   Il est �galement possible d'utiliser les
'   m�thodes de rappel (CallBack), et ce avec un certain
'   nombre d'avantages. Ces m�thodes permettent
'   en effet � un composant de g�rer de mani�re
'   intelligente les erreurs du client, alors que
'   les �v�nements ne renvoient pas ces erreurs.
'   Cet aspect est abord� � la section
'   "Notifications asynchrones � l'aide de
'   m�thodes de rappel" des Manuels en ligne.

' Nombre d'it�rations � ex�cuter dans une t�che
'   de test.
Private mlngIterations As Long

' L'objet XTimer est utilis� pour d�marrer la
'   t�che longue en mode asynchrone.
Private WithEvents mwXTimer As XTimer
Attribute mwXTimer.VB_VarHelpID = -1

Event Progress(ByVal PercentDone As Single, _
        ByRef Cancel As Boolean)
Event Complete(ByVal Canceled As Boolean)
        
' La propri�t� ThreadID renvoie l'ID de la thread
'   du syst�me pour la thread sur
'   laquelle l'objet a �t� cr��.
'
Public Property Get ThreadID() As Long
    ThreadID = App.ThreadID
End Property

' La propri�t� NumberOnThread renvoie le nombre
' --------------    d'objets Coffee s'ex�cutant
'   sur cette thread. Il s'agit uniquement de
'   la valeur de la variable globale glngGlobalData
'   que les objets Coffee incr�mentent dans
'   leurs �v�nements Initialize et d�cr�mentent
'   dans leurs �v�nements Terminate.
'
' Si le projet MTCoffee a �t� compil� avec l'option
'   Thread par objet, les objets multiples ne
'   peuvent partager une thread (et l'instance
'   de donn�es globales associ�e) que si un autre
'   objet Coffee a �t� cr�� sur cette thread en
'   appelant GetCoffeeOnSameThread.
'
' Si le projet MTCoffee a �t� compil� avec l'option
'   Nb max de thread et que le nombre des
'   objets actifs est sup�rieur au nombre des
'   threads du regroupement, les objets Coffee
'   partageront les threads.
'
Public Property Get NumberOnThread() As Long
    NumberOnThread = glngGlobalData
End Property

' La m�thode StartLongTask pr�pare le terrain pour la t�che
' -------------     de test longue. Celle-ci est
'   en fait d�marr�e par un objet XTimer en code
'   seul qui est lanc� par la m�thode StartLongTask.
'
Public Sub StartLongTask(ByVal Iterations As Long)
    ' Ceci est un raccourci pour tester la d�pr�ciation
    '   des appels. Reportez-vous � la m�thode CallAnotherCoffee.
    If Iterations = 0 Then Exit Sub
    '
    ' Stocke la taille de la t�che de test.
    mlngIterations = Iterations
    '
    ' Affecte � la minuterie un intervalle
    '   court, puis le lance avant de le
    '   renvoyer.
    mwXTimer.Interval = 55
    mwXTimer.Enabled = True
End Sub

' La m�thode GetCoffeeOnSameThread cr�e un nouvel objet
' ---------------------     Coffee sur la m�me
'   thread, en simulant les effets du regroupement
'   de threads. Ceci ne peut �tre fait qu'en
'   interne, comme l'explique la section
'   "Cr�ation d'objets dans les composants
'   Visual Basic" des Manuels en ligne.
'
Public Function GetCoffeeOnSameThread() As Coffee
    ' Tous les objets cr��s en utilisant le mot cl�
    '   New seront sur la thread du concepteur, y
    '   compris un nouvel objet Coffee.
    Set GetCoffeeOnSameThread = New Coffee
End Function

' La m�thode GetCoffeeOnNewThread cr�e un nouvel objet
' --------------------     Coffee sur une nouvelle 
'   thread en appelant la fonction CreateObject.
'   La diff�rence existant entre ce type de
'   cr�ation et la cr�ation interne r�alis�e
'   par la m�thode GetCoffeeOnSameThread est abord�e �
'   la section "Cr�ation d'objets dans les
'   composants Visual Basic" des Manuels en ligne.
'
' Note: cette technique peut �tre utilis�e pour
'   cr�er des objets sur diff�rentes threads qui
'   peuvent communiquer entre elles, sans que
'   le client doive passer � un objet une
'   r�f�rence � l'autre objet (comme le fait
'   CoffeeWatch). Si vous apppliquez cette technique,
'   la d�pr�ciation des appels de marshaling 
'   entre les threads est presque aussi
'   importante que la d�pr�ciation des appels
'   de marshaling entre les processus.
'
Public Function GetCoffeeOnNewThread() As Coffee
    ' Le cr�e comme un client externe.
    Set GetCoffeeOnNewThread = CreateObject("MTCoffee.Coffee")
End Function

' La m�thode CallAnotherCoffee donne un aper�u de la
' -----------------     d�pr�ciation des appels
'   entre les threads. Il lui passe un objet
'   Coffee sur une autre thread, ou sur la m�me
'   thread, puis compare les r�sultats. La
'   m�thode fait des appels de test � la m�thode
'   StartLongTask; ainsi, il mesure
'   essentiellement la d�pr�ciation de l'appel.
'
Public Function CallAnotherCoffee(ByVal cfe As Coffee) As Double
    Const TRIES = 10000
    Dim timeStart As Long
    Dim timeEnd As Long
    Dim lngTries As Long
    
    timeStart = timeGetTime
    For lngTries = 1 To TRIES
        cfe.StartLongTask 0
    Next
    timeEnd = timeGetTime
    '
    ' Renvoie un nombre de secondes (ss.mmm) par
    '   appel. Le r�sultat obtenu sera incorrect
    '   si vous ex�cutez la m�thode CallAnotherCoffee 
    '   au moment o� la minuterie du syst�me
    '   repasse � z�ro.
    CallAnotherCoffee = ((CDbl(timeEnd) - timeStart) / 1000#) / TRIES
End Function

Private Sub Class_Initialize()
    ' Incr�mente le nombre global des
    '   objets Coffee, pour cette thread.
    glngGlobalData = glngGlobalData + 1
    '
    ' Cr�e un objet XTimer.
    Set mwXTimer = New XTimer
End Sub

Private Sub Class_Terminate()
    ' D�cr�mente le nombre global des
    '   objets Coffee, pour cette thread.
    glngGlobalData = glngGlobalData - 1
    '
    ' Lib�re l'objet XTimer.
    Set mwXTimer = Nothing
End Sub

Private Sub mwXTimer_Tick()
    ' Arr�te la minuterie, pour commencer.
    mwXTimer.Enabled = False
    Call LongTask
End Sub

' La t�che de test.
'
Private Sub LongTask()
    Dim dblDummy As Double
    Dim lngCt As Long
    Dim sngNextMark As Single
    Dim blnCancel As Boolean
    
    ' Pour des petites transactions, n'effectue pas
    '   les rappels pendant l'ex�cution.
    If mlngIterations < 100000 Then
        sngNextMark = 1!
    Else
        sngNextMark = 0.1!
    End If
        
    ' Il s'agit juste d'une fa�on de perdre du temps.
    For lngCt = 1 To mlngIterations
        ' Dans le cas d'une vraie application, une
        '   partie du travail serait effectu�e ici.
        '   Il peut �tre int�ressant de remplacer
        '   cette activit� importante en termes de
        '   traitements par une activit� qui fait
        '   peu appel au syst�me, tels que des appels
        '   � une base de donn�es d'une autre machine
        '   ou la lecture d'un gros fichier. Le
        '   d�bit sur une station de travail � un
        '   seul processeur est beaucoup plus
        '   important lorsque de nombreuses threads
        '   sont bloqu�es, en attendant l'entr�e
        '   d'un fichier ou le r�sultat d'un appel
        '   � une base de donn�es.
        '
        dblDummy = 3033.14159 * 2081.14159 * 1138.14159
        '
        If CDbl(lngCt) / mlngIterations > sngNextMark Then
            RaiseEvent Progress(sngNextMark, blnCancel)
            If blnCancel Then
                ' Si le client ne veut plus attendre
                '   et annuler la t�che, il d�clenche
                '   l'�v�nement Complete avec la valeur
                '   True (annul�).
                RaiseEvent Complete(True)
                Exit Sub
            End If
            sngNextMark = sngNextMark + 0.1!
        End If
    Next
    ' Lorsque la t�che r�ussit, il d�clenche
    '   l'�v�nement Complete avec la valeur False
    '   (non annul�).
    RaiseEvent Complete(False)
End Sub
