VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Sales"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Dim sngPubRevenue() As Single     ' Tableau mensuel des revenus
Dim sngAuthorRoyalty() As Single  ' Tableau  mensuel des royalties
Dim sngBookPrice() As Single      ' Tableau  mensuel des prix de livres

Public Function GetAuthors() As ADODB.Recordset
' Cette fonction retourne la liste compl�te des auteurs connus. Ceci est fourni comme un service
' aux clients, ainsi ils n'ont pas besoin de conna�tre l'�tat et l'emplacement des donn�es m�mes.
' De cette fa�on, il s'agit d'une sorte de "service de donn�es".  
' Normalement, les services de donn�es doivent �tre regroup�s et s�par�s des services d'entreprise
' afin d'�viter les d�pendances entre le d�veloppement et la maintenance.

    Dim strSQL As String
    
    strSQL = "SELECT Authors.Author FROM Authors"
    Set rsAuthors = New ADODB.Recordset
    With rsAuthors
      .CursorLocation = adUseClient
      .Open strSQL, gCN, adOpenStatic, adLockReadOnly
    End With
   Set GetAuthors = rsAuthors
End Function

Public Function GetTitles(ByVal strSQL As String) As ADODB.Recordset
   ' Lire les titres en utilisant une requ�te issue du client.
   Set rsTitles = New ADODB.Recordset
   With rsTitles
      .CursorLocation = adUseClient
      .Open strSQL, gCN, adOpenStatic, adLockReadOnly
   End With
   Set GetTitles = rsTitles
End Function
Public Function GetBookPages(ByVal strSQL As String) As ADODB.Recordset
   ' Lire les pages en utilisant une requ�te issue du client.
   Set rsBookPages = New ADODB.Recordset
   With rsBookPages
      .CursorLocation = adUseClient
      .Open strSQL, gCN, adOpenStatic, adLockReadOnly
   End With
   Set GetBookPages = rsBookPages

End Function
Public Function GetRsCOGS(ByVal strSQL As String) As ADODB.Recordset
   ' Lire les co�ts des marchandises en utilisant une requ�te issue du client.
   Set rsCOGS = New ADODB.Recordset
   With rsCOGS
      .CursorLocation = adUseClient
      .Open strSQL, gCN, adOpenStatic, adLockReadOnly
   End With
   Set GetRsCOGS = rsCOGS
End Function

Public Function GetRevenue(intSalesModel As Integer, _
                              curCostPerUnit As Currency, _
                              curAdvCost As Currency, _
                              intSalesPeriod As Integer, _
                              lngUnitsPerMonth As Long, _
                              bolIsDiscount As Boolean, _
                              strBookTitle As String) As Variant

  Dim i As Integer
  Dim iOldBound As Integer
  Dim iNewBound As Integer

  gintSalesModel = intSalesModel
  gcurCostPerUnit = curCostPerUnit
  gcurAdvertisingCost = curAdvCost
  gintSalesPeriod = intSalesPeriod
  glngUnitsPerMonth = lngUnitsPerMonth
  
  If GetPubRevenue(strBookTitle) = False Then
      ServerMsg Error$ & " - " & Str$(Err), vbOKOnly, "Erreur dans GetChartData"
    GetRevenue = 0
    Exit Function
  
  End If

  If GetAuthorRoyalty() = False Then
      ServerMsg Error$ & " - " & Str$(Err), vbOKOnly, "Erreur dans GetChartData"
    GetRevenue = 0
    Exit Function

  End If

  iOldBound = UBound(sngPubRevenue)

  For i = 0 To iOldBound
    sngPubRevenue(i, 1) = sngAuthorRoyalty(i)
  
  Next i

  GetRevenue = sngPubRevenue()

End Function

Public Function GetAuthorRoyalty() As Boolean
Dim i As Integer

Dim cGrossMonthlySalary As Currency
Dim cTaxAmount As Currency
Dim cTotalRevenue As Currency

' Cr�e une r�f�rence � la classe Taxes.
Dim objTax As New Taxes

frmBookSales.lblStatus(1).Caption = "Demande les royalties de l'auteur..."

ReDim sngAuthorRoyalty(gintSalesPeriod)

  For i = 0 To (gintSalesPeriod - 1)
    cGrossMonthlySalary = sngPubRevenue(i, 0) * gRoyalty
    sngAuthorRoyalty(i) = cGrossMonthlySalary - _
                                    objTax.CalcNationalIncomeTax(cGrossMonthlySalary) - _
                                    objTax.CalcSalesTax(cGrossMonthlySalary, 0)

  Next i

  ' Supprime la r�f�rence � la classe.
  Set objTax = Nothing
  
  frmBookSales.lblStatus(1).Caption = "Calcule les royalties de l'auteur..."
  GetAuthorRoyalty = True

End Function

Public Function GetPubRevenue(strTitle As String) As Variant
Dim sn As ADODB.Recordset
Dim strSQL As String
Dim i As Integer
Dim Price As Currency

' Cr�e une r�f�rence � la classe Model.
Dim objModel As New Model

Static strOldTitle As String
Static cUnitPrice As Currency

frmBookSales.lblStatus(0).Caption = "Demande les revenus de l'�diteur..."
frmBookSales.lblStatus(1).Caption = "Calcule les revenus de l' �diteur..."

On Error GoTo GetRevenueError

If strTitle <> strOldTitle Then
  frmBookSales.lblStatus(1).Caption = "R�cup�re les enregistrements" & strTitle & "..."
  strSQL = "SELECT Titles.Price " & _
                "FROM Titles " & _
                "WHERE ((Titles.Title=" & Chr$(34) & strTitle & Chr$(34) & "));"
  
    ' Initialiser la variable ADODB Recordset et l'ouvrir 
    ' en l'utilisant l'objet de connexion global gCN.
  Set sn = New ADODB.Recordset
  sn.Open strSQL, gCN, adOpenForwardOnly, adLockReadOnly
  'Set sn = gdb.OpenRecordset(strSQL, dbOpenSnapshot)
  cUnitPrice = sn.Fields("Price")
  
Else
  frmBookSales.lblStatus(1).Caption = "Utilise les derni�res valeurs..."
  
End If

ReDim sngPubRevenue(gintSalesPeriod - 1, 1)
ReDim sngBookPrice(gintSalesPeriod - 1)

For i = 0 To gintSalesPeriod - 1
   sngPubRevenue(i, 0) = cUnitPrice * _
                          objModel.intGetMonthSales(i, _
                          gintSalesPeriod, _
                          gintSalesModel)
Next i

' Supprime la r�f�rence � la classe.
Set objModel = Nothing

frmBookSales.lblStatus(1).Caption = "Envoie les revenus de l'�diteur vers le client..."
GetPubRevenue = True

' N'essaie pas de fermer l'objet si l'instantan� n'a jamais �t� cr��.
' La variable sn n'est jamais d�finie quand strTitle = strOldTitle.
  If strTitle <> strOldTitle Then
    sn.Close
    Set sn = Nothing
  End If

  strOldTitle = strTitle

  Exit Function
  If IsObject(sn) Then sn.Close
  Set sn = Nothing

GetRevenueError:
  frmBookSales.lblStatus(1).Caption = Error$ & " - " & Str$(Err)
  GetPubRevenue = False
  
End Function

Private Sub Class_Initialize()
' Classe initialis�e lorsqu'elle est instanci�e par le client.
  
On Error GoTo InitErr
  
  If gintInstanceCount = 0 Then
    frmBookSales.Show
    gintInstanceCount = 0
  ' Cr�er une connexion ADODB globale, d�finir ConnnectionString et ouvrir.
    LoadDB
    frmBookSales.lblStatus(1).Caption = "ouverture de " & gDBName & "..."
  
    frmBookSales.lblStatus(1).Caption = "Attente de commande..."
  End If
    
  gintInstanceCount = gintInstanceCount + 1
  frmBookSales.lblInstanceCount.Caption = Format$(gintInstanceCount)

  Exit Sub

InitExit:
Screen.MousePointer = vbDefault
Exit Sub
  
InitErr:
  
  frmBookSales.lblStatus(1).Caption = Error$ & " - " & Str$(Err)
  
If Err <> 0 Then ' Une autre erreur.
      ServerMsg Error$ & " - " & Str$(Err), vbCritical, "Erreur de d�marrage du serveur Vente de livres."
      End
  End If
  
  Resume InitExit
  
End Sub

Private Sub LoadDB()
  ' Charger booksale.mdb. Si le fichier n'est pas dans le
  ' r�pertoire attendu, affiche le contr�le CommonDialog
  ' qui permet � l'utilisateur de rechercher le fichier.
   
   gDBName = "booksale.mdb"
   On Error GoTo LoadDBError
   Set gCN = New ADODB.Connection ' Objet Connection global.

   ' D�finir la cha�ne de connexion pour l'objet Connection.
   gCN.ConnectionString = "Provider=Microsoft.Jet.OLEDB.3.51;Data Source=" & _
   Left(App.Path, Len(App.Path) - Len("client")) & gDBName
   gCN.Open ' Ouvrir la connexion.
  
  Exit Sub
LoadDBError:
   Select Case Err.Number
   Case -2147467259
      ' Fichier introuvable, utiliser CommonDialog pour le rechercher.
      gCN.ConnectionString = "Provider=Microsoft.Jet.OLEDB.3.51;Data Source=" & _
      GetBooksale
      Resume
   Case Else ' Autres erreurs inconnues
       MsgBox Err.Number & ": " & Err.Description
   End Select
End Sub

Private Function GetBooksale() As String
   ' Retourne le chemin de booksale.mdb.
   ' Si booksale.mdb n'est pas � l'emplacement par d�faut,
   ' pr�sente � l'utilisateur un contr�le CommonDialog et
   ' et lui demande de localiser la base de donn�es.
    On Error GoTo ErrHandler

   With frmBookSales.dlgFindDB
      .DialogTitle = "Veuillez rechercher Booksale.mdb"
      .InitDir = App.Path
      .FileName = gDBName
      .Filter = "Access (*.mdb)| *.mdb"
      .CancelError = True 'Cause une erreur si l'utilisateur clique sur annuler
      .ShowOpen
   End With
    
   Do While UCase(Right(Trim(frmBookSales.dlgFindDB.FileName), Len("booksale.mdb"))) <> "BOOKSALE.MDB"
         MsgBox "Le nom du fichier est diff�rent de BOOKSALE.MDB"
         frmBookSales.dlgFindDB.ShowOpen
   Loop
   
   GetBooksale = frmBookSales.dlgFindDB.FileName
   Exit Function
ErrHandler:
    If Err = 32755 Then 'Annuler cause une erreur
      End
    End If
End Function


Private Sub Class_Terminate()
  gintInstanceCount = gintInstanceCount - 1
  frmBookSales.lblInstanceCount.Caption = Format$(gintInstanceCount)
  
  If gintInstanceCount = 0 Then
    Unload frmBookSales
  End If
End Sub


