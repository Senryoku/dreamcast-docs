VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 1  'vbDataSource
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MyDataSource"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private Sub Class_GetDataMember(DataMember As String, Data As Object)
    ' D�clare une instance de la classe MyObject
    Dim MyOSP As New MyOSPObject
    
    ' V�rifie que le DataMember est valide
    If DataMember = "" Then
        Err.Raise (E_FAIL)
    End If
    
    ' D�finit la propri�t� FilePath
    MyOSP.FilePath = DataMember
    
    ' Appelle la m�thode LoadData pour remplir la classe
    MyOSP.LoadData
    
    ' D�finit les donn�es de MyDataSource � partir des donn�es de MyOSPObject
    Set Data = MyOSP
End Sub


