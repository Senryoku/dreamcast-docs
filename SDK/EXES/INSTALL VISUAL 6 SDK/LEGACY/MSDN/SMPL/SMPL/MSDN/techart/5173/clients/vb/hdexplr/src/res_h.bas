Attribute VB_Name = "ResourceProperties"
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date    - 02/01/98
'Authors - Robert Coleridge, Steve Kirk, Fred Pace, Kevin Marzec, Dale Smith
'
Option Explicit

Private Const OBJNAME = "Resource_h.bas"

Public Enum RES_IDS
    icIDS_USEMSGASERROR = -1
    icIDI_AUDITTYPE = 118
    icIDI_DOMAIN_LOCATION = 119
    icIDI_DOMAIN_PRIORITY = 120
    icIDI_STDVOCRESP = 121
    icIDI_STATUS = 122
    icIDI_TECHSTATUS = 123
    icIDI_STDTEXTRESP = 124
    icIDI_SYSPARM = 126
    icIDI_SYSPARMTYPE = 127
    icIDI_TECHNICIAN = 128
    icIDI_DOMAIN_SKILL = 129
    icIDI_DOMAINS = 130
    icIDI_LOCATION = 131
    icIDI_PRIORITY = 132
    icIDI_REQDETTYPE = 133
    icIDI_SKILL = 134
    icIDI_DOMAIN = 136
    icIDS_DSN_NAME = 1087
    icIDS_ERR_ILLEGAL_VALUE = 1088
    icIDS_ERR_ENTRY_EXISTS = 1089
    icIDS_KWTV_TECHNICIAN = 1090
    icIDS_KWTV_DOMAINS = 1091
    icIDS_KWTV_LOCATIONS = 1092
    icIDS_KWTV_SKILLS = 1093
    icIDS_KWTV_PRIORITIES = 1094
    icIDS_KWTV_SYSTEMPARMS = 1095
    icIDS_KW_ALIAS = 1096
    icIDS_KW_DESCRIPTION = 1097
    icIDS_KW_CODE = 1098
    icIDS_PH_SELECTFROMLIST = 1099
    icIDS_BTN_ADDNEW = 1100
    icIDS_BTN_DELETE = 1101
    icIDS_BTN_UPDATE = 1102
    icIDS_SQLTB_SYSTEMPARMS = 1103
    icIDS_SQLTB_LOCATION = 1104
    icIDS_SQLTB_TECHNICIAN = 1105
    icIDS_SQLTB_SKILL = 1106
    icIDS_SQLTB_PRIORITY = 1107
    icIDS_ERR_INVALID_PASSWORD = 1108
    icIDS_KW_LOCATION = 1110
    icIDS_KW_SKILL = 1111
    icIDS_KW_PRIORITY = 1112
    icIDS_ERR_CANT_INSERT = 1113
    icIDS_ERR_CANT_UPDATE = 1114
    icIDS_ERR_CANT_DELETE = 1115
'@@    icIDS_KWTV_AUDITTYPES = 1116
'    icIDS_KWTV_REQDETTYPES = 1117
'    icIDS_KWTV_STATUS = 1118
'    icIDS_KWTV_STDTEXTRESP = 1119
'    icIDS_KWTV_STDVOCRESP = 1120
'    icIDS_KWTV_TECHSTATUS = 1121
    icIDS_ERR_INVALIDUSERNAME = 1122
    icIDS_LOGGINGWARNING = 1123
    icIDS_ERR_INVALIDTECHALIAS = 1124
    icIDS_VALIDTECHALIASSTARTS = 1125
    icIDS_ADDADMINTECH = 1126
    icIDS_INITIALADMINSKILL = 1127
    icIDS_INITIALADMINLOCATION = 1128
    icIDS_INITIALIREQUESTDATE = 1129
    'ic_APS_NEXT_RESOURCE_VALUE = 138
    'ic_APS_NEXT_COMMAND_VALUE = 40001
    'ic_APS_NEXT_CONTROL_VALUE = 1000
    'ic_APS_NEXT_SYMED_VALUE = 101
End Enum

Private Function InvokeError(ByVal ErrorID As RES_IDS, Optional ByVal ErrorMsg As String) As Boolean
    Dim sMsg As String
    Dim lErr As Long

    sMsg = Trim$(App.Title) & ":" & OBJNAME
    lErr = Err

    If ErrorID = icIDS_USEMSGASERROR Then
        sMsg = sMsg & " " & ErrorMsg
    Else
        sMsg = sMsg & " " & LoadResString(ErrorID)
    End If

    If Err < vbObjectError Then
        lErr = lErr + vbObjectError
    End If

    Err.Raise lErr, sMsg, Err.Description
End Function
