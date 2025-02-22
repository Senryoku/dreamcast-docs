VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Connector"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = True
Option Explicit
' > Pour plus d'informations sur cet exemple d'application,
'   recherchez "Coffee" dans l'aide en ligne.
' > Le fichier AboutCof.txt, pr�sent dans le dossier
'   Documents associ�s de CoffWat2.vbp, contient �galement
'   des informations sur cet exemple.

' Classe Connector
' ---------------
' La classe Connector permet � plusieurs clients de partager
' ----------------  une instance unique de CoffeeMonitor. La
'   propri�t� Instancing de la classe Connector a pour
'   valeur MultiUse; ainsi, chaque client peut cr�er son
'   propre objet Connector. Tous les objets Connector
'   renvoient une r�f�rence � l'unique objet CoffeeMonitor
'   partag�; ainsi, tous les clients partagent le m�me objet
'   CoffeeMonitor (Reportez-vous � la propri�t� CoffeeMonitor
'   ci-dessous).
'
' La lecture du chapitre "Cr�ation d'un composant EXE ActiveX"
'   des Manuels en ligne fait appara�tre une diff�rence:
'   cette version de Connector ne dispose pas de "compte
'   d'utilisation" qui d�termine lorsqu'il faut affecter
'   la valeur Nothing � la variable gCoffeeMonitor. Le code de
'   l'�v�nement Initialize n'est pas indispensable pour
'   incr�menter ce compte d'utilisation, et celui de
'   l'�v�nement Terminate ne l'est pas pour d�cr�menter
'   et tester ce compte.
'
' Cela r�sout un bogue d�crit dans la section
'   "Utilisation du CoffeeMonitor partag�" du chapitre
'   mentionn� ci-dessus. Pour en savoir plus sur le
'   compte d'utilisation et sur sa mani�re de r�gler
'   le bogue, reportez-vous au module de classe
'   CoffeeMonitor.


' La propri�t� CoffeeMonitor renvoie toujours la
' --------------   r�f�rence globale unique �
'   l'instance partag�e de CoffeeMonitor (cr��e
'   lors de la premi�re demande d'un client �
'   CoffeeMonitor).
'
Public Property Get CoffeeMonitor() As CoffeeMonitor
    '' Si l'objet partag� CoffeeMonitor n'est pas cr��,
    '   le cr�e et y stocke une r�f�rence globale.
    If gCoffeeMonitor Is Nothing Then
        Set gCoffeeMonitor = New CoffeeMonitor
    End If
    
    Set CoffeeMonitor = gCoffeeMonitor
End Property
    
