VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CoffeeMonitor2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
' > Pour plus d'informations sur cet exemple d'application,
'   recherchez "Coffee" dans l'aide en ligne.
' > Le fichier AboutCof.Txt, pr�sent dans le dossier
'   Documents associ�s de CoffWat2.vbp, contient �galement
'   des informations sur cet exemple.

' Classe CoffeeMonitor2
' --------------------
' Tout comme l'objet CoffeeMonitor, l'objet
'   CoffeeMonitor2 surveille le fonctionnement d'une
'   cafeti�re "high tech" connect�e � une interface
'   s�rie imaginaire, en utilisant une minuterie qui
'   d�termine la fr�quence avec laquelle il faut
'   v�rifier le caf�.
'
' Au lieu de d�clencher un �v�nement lorsque le caf�
'   est pr�t, l'objet CoffeeMonitor2 invoque une
'   m�thode de rappel qui doit �tre impl�ment�e par
'   une des classes du client. La m�thode de rappel
'   est d�clar�e dans la classe ICallBack.
'
' (Bien entendu, ce type de cafeti�re "high tech"
'   n'ayant pas encore �t� invent�, cet exemple
'   d'application invoque donc simplement une m�thode
'   de rappel toutes les dix secondes.)
'
' IMPORTANT: Afin de simplifier un exemple somme toute
'   assez complexe, la classe ICallBack a �t� ajout�e
'   � ce projet. Ceci ne marchera PAS sur les vrais
'   syst�mes, qui utilisent de nombreuses versions. Si
'   une deuxi�me version de Coffee2 est r�alis�e, le
'   num�ro de version ID de l'interface sera incr�ment�,
'   et les anciens clients ne pourront PAS fonctionner
'   avec la nouvelle version de Coffee2. Les interfaces
'   standard telles que ICallBack devraient �tre cr��es
'   par elles-m�mes dans des petites DLL qui pourront
'   �tre r�f�renc�es � la fois par le client et par le
'   composant. Une interface utilis�e par des applications
'   qui sont termin�es ne devrait jamais changer. Pour
'   plus d'informations, recherchez "polymorphisme"
'   dans les Manuels en ligne.
'
' Note: la valeur PublicNotCreatable a �t� affect�e � la
'   propri�t� Instancing de la classe CoffeeMonitor2.
'   Cela signifie que les clients ne peuvent pas cr�er
'   un objet CoffeeMonitor2; ils ne peuvent qu'obtenir
'   une r�f�rence � la classe partag�e CoffeeMonitor2
'   en cr�ant un objet Connector2 et en acc�dant � sa
'   propri�t� CoffeeMonitor2.
'
' Tout comme la classe CoffeeMonitor, la classe
'   CoffeeMonitor2 corrige le bogue d�crit dans la section
'   "Utilisation du CoffeeMonitor partag�" du chapitre
'   "Cr�ation d'un composant EXE ActiveX", des Manuels
'   en ligne, au moyen duquel des objets CoffeeMonitor
'   multiples peuvent parfois �tre cr��s.

' =======================================================
'  AVERTISSEMENT!  Les minuteries en code seul sont
'   implicitement dangereuses dans l'environnement de
'   d�veloppement Visual Basic car le syst�me effectue
'   sans rel�che des appels dans votre code jusqu'� ce
'   que la minuterie soit arr�t�e par un appel d'API.
'   Il est plus s�r d'utiliser des contr�les Timer pendant
'   une grande partie de la proc�dure de d�veloppement,
'   et de repasser � des minuteries de rappel tout � la fin.
' =======================================================

Const ICN_ARRAYINCREMENT = 10

' maicnClients stocke des r�f�rences � tous les clients
' ------------   qui ont requis des rappels. Vous remarquerez
'   que cela diff�re de l'utilisation des �v�nements dans
'   l'objet CoffeeMonitor: un �v�nement peut �tre re�u par
'   plusieurs clients, alors que les rappels doivent �tre
'   faits un par un. Un tableau est utilis�, � la place
'   d'une Collection, car les objets Collection conservent
'   des objets dans des Variants, ce qui entra�ne des liaisons
'   tardives.
Private maicnClients() As ICoffeeNotify
Private mlngMaxClients As Long

' mwXTimer maintient une r�f�rence � la minuterie en code
' -------   seul qui indique � l'objet CoffeeMonitor2
'   � quel moment il faut surveiller le caf�. La
'   variable �tant d�clar�e en tant que WithEvents,
'   l'objet CoffeeMonitor2 re�oit les �v�nements Tick
'   de l'objet XTimer (reportez-vous � Sub mwXTimer_Tick,
'   plus bas). Le code pour l'objet XTimer se trouve
'   dans le fichier XTimers.vbp.
Private WithEvents mwXTimer As XTimer
Attribute mwXTimer.VB_VarHelpID = -1

Private Sub Class_Initialize()
    ' Alloue de l'espace dans le tableau des objets du client.
    mlngMaxClients = ICN_ARRAYINCREMENT
    ReDim maicnClients(1 To mlngMaxClients)
    '
    ' Cr�e l'objet XTimer. Lorsque l'affectation est faite,
    '   Visual Basic connecte l'�v�nement Tick de l'objet
    '   XTimer � la proc�dure d'�v�nement mwXTimer_Tick
    '   (Voir ci-dessous).
    Set mwXTimer = New XTimer
    '
    ' La minuterie est d�finie pour �mettre un �v�nement
    '   Tick toutes les dix secondes (10.000 millisecondes).
    mwXTimer.Interval = 10000
    mwXTimer.Enabled = True
End Sub

Private Sub Class_Terminate()
    Dim intCt As Integer
    
    ' Il est important de d�sactiver l'objet XTimer
    '   avant de le lib�rer. Comme cela est d�crit
    '   dans le fichier XTimers.vbp, l'abandon de
    '   l'ex�cution d'un objet XTimer provoque
    '   essentiellement une perte de la minuterie du
    '   syst�me, jusqu'� ce que le fichier XTimers.DLL
    '   ne soit d�charg�.
    mwXTimer.Enabled = False
    Set mwXTimer = Nothing
    '
    ' Lib�re tous les clients restants du rappel,
    '   au cas o� ils auraient lib�r� CoffeeMonitor2
    '   sans effectuer d'abord de demande de fin des
    '   notifications.
    For intCt = 1 To mlngMaxClients
        Set maicnClients(intCt) = Nothing
    Next
    '
    Debug.Print "CoffeeMonitor2 (rappels) s'est termin� � " & Now
End Sub

' La m�thode TellMeReady est appel� par un client voulant recevoir
' -----------   un rappel lorsque le caf� est pr�t. Le
'   client doit impl�menter l'interface ICoffeeNotify,
'   d�finie dans la classe ICoffeeNotify.
'
Public Sub TellMeReady(ByVal icn As ICoffeeNotify)
    Dim lngCt As Long
    
    ' Cherche un emplacement dans le tableau des interfaces.
    For lngCt = 1 To mlngMaxClients
        If maicnClients(lngCt) Is Nothing Then Exit For
    Next
    '
    ' S'il n'y a pas d'emplacements libres, redimensionne
    '   le tableau.
    If lngCt > mlngMaxClients Then
        mlngMaxClients = mlngMaxClients + ICN_ARRAYINCREMENT
        ReDim Preserve maicnClients(1 To mlngMaxClients)
    End If
    '
    Set maicnClients(lngCt) = icn
    '
    ' Donne � l'objet l'index de son entr�e, qui constituent
    '   une cl� pour un verrouillage rapide lorsque la
    '   d�connexion est demand�e.
    icn.NotifyID = lngCt
End Sub

' La m�thode CeaseCallBacks supprime le client de la liste des objets
' --------------   recevant des notifications de rappel, en
'   utilisant la cl� affect�e � l'objet lors de la demande
'   des notifications.
'
Public Sub CeaseCallBacks(ByVal icn As ICoffeeNotify)
    Set maicnClients(icn.NotifyID) = Nothing
End Sub

' mwXTimer_Tick est la proc�dure d'�v�nement que CoffeeMonitor2
' -------------   utilise pour recevoir les �v�nements Tick
'   de l'objet XTimer. Le nom d'une proc�dure d'�v�nement
'   associ�e avec une variable WithEvents prend toujours le
'   nom de la variable comme pr�fixe.
'
Private Sub mwXTimer_Tick()
    Dim lngCt As Long
    
    ' (Code de test du port s�rie omis.)
    '
    On Error Resume Next
    '
    ' La m�thode de rappel doit �tre appel�e pour chaque
    '   objet ayant demand� une notification.
    For lngCt = 1 To mlngMaxClients
        If Not maicnClients(lngCt) Is Nothing Then
            maicnClients(lngCt).CoffeeReady
            If Err.Number <> 0 Then
                ' L'erreur &H80010005 est ignor�e; elle peut
                '   avoir �t� caus�e par l'objet du client qui
                '   n'a pas r�pondu temporairement.
                If Err.Number <> &H80010005 Then
                    ' Si une application client s'est termin�e
                    '   sans avoir mis fin aux notifications,
                    '   supprimez-la de la liste.
                    Set maicnClients(lngCt) = Nothing
                End If
                '
                ' Si l'instruction On Error Resume Next est
                '   utilis�e, le num�ro d'erreur doit �tre
                '   effac� apr�s chaque erreur.
                Err.Number = 0
            End If
        End If
    Next
End Sub

