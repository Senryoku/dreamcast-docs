VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Source"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

Public cnMe        As rdoConnection
Public objError    As LayerError.Service
Public objEvtLog   As LayerLogInformation.Service
Public objTrnLog   As LayerLogDatabase.Service
Public sDBName     As String
Public sConnStr    As String
Public fReadOnly   As Boolean
Public fGoodConn   As Boolean
Public iTimeOut    As Integer

