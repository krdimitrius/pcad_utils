VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Update 2nd  Ref Des"
   ClientHeight    =   3135
   ClientLeft      =   2340
   ClientTop       =   1635
   ClientWidth     =   5175
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3135
   ScaleWidth      =   5175
   Begin VB.ListBox CompList2 
      Appearance      =   0  'Flat
      Height          =   1395
      Left            =   120
      TabIndex        =   8
      Top             =   360
      Visible         =   0   'False
      Width           =   2535
   End
   Begin VB.ListBox CompList 
      Height          =   1425
      Left            =   120
      TabIndex        =   7
      Top             =   360
      Width           =   2535
   End
   Begin VB.CommandButton Update 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Update RefDes2"
      Height          =   375
      Left            =   3000
      TabIndex        =   5
      Top             =   840
      Width           =   1935
   End
   Begin VB.CommandButton Get_Comps 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Get Component(s)"
      Height          =   375
      Left            =   3000
      TabIndex        =   2
      Top             =   360
      Width           =   1935
   End
   Begin VB.CommandButton Exit 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Exit"
      Height          =   375
      Left            =   3000
      TabIndex        =   0
      Top             =   1320
      Width           =   1935
   End
   Begin VB.Label statusLabel 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   180
      TabIndex        =   6
      Top             =   2340
      Width           =   4935
   End
   Begin VB.Label statusLabel2 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   180
      TabIndex        =   4
      Top             =   2700
      Width           =   4935
   End
   Begin VB.Label Label5 
      Caption         =   "Status:"
      Height          =   195
      Left            =   120
      TabIndex        =   3
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Component List:"
      Height          =   255
      Left            =   60
      TabIndex        =   1
      Top             =   120
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim newComp As TComponent
Dim theComp As TComponent
Dim theItem As TItem
Dim origpoint As TCoord
Dim I As Long
Dim J As Long
Dim newAngle As Long
Dim tStatus As Long
Dim tstatus2 As Long
Dim tstatus3 As Long
Dim tContext As DbxContext
Dim myComp As TComponent
Dim theAttr As TAttribute
Dim got_refdes2 As Long




Private Sub Design_Open()

    tStatus = TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "", tContext)

    If (tStatus <> DBX_OK) Then
        statusLabel2.Caption = Return_error_message(tStatus)
    End If

End Sub

Private Sub DesignClose()

    tStatus = TCloseDesign(tContext, "")

End Sub

Private Sub Exit_Click()
    End
End Sub

Private Sub Form_Load()

    statusLabel = ""
    statusLabel2 = ""

'
'  Open the design
'
    Design_Open
        If (tStatus <> DBX_OK) Then GoTo Done

'
'  Get selected components
'
    GetSelectedComponents

Done:

    DesignClose

End Sub

Private Sub Get_Comps_Click()
    
    statusLabel.Caption = ""
    statusLabel2.Caption = ""

    Design_Open

    If (tStatus <> DBX_OK) Then
        statusLabel2.Caption = Return_error_message(tStatus)
    Else
        GetSelectedComponents
    End If

    DesignClose

End Sub

Private Sub GetSelectedComponents()

CompList.Clear
CompList.Visible = -1
CompList2.Visible = 0

'
'  Get the first component in the selection set
'
    tStatus = TGetFirstSelectedItem(tContext, theItem)
        If (tStatus <> DBX_OK) Then
            statusLabel.Caption = "Please select the components to update RefDes2."
        ElseIf (theItem.itemType = DBX_COMPONENT) Then
         theComp = theItem.component
         CompList.AddItem theComp.refDes
         statusLabel.Caption = "One component selected."
     End If
'
'  Get the rest of the components
'
    While (tStatus = DBX_OK)

        tStatus = TGetNextSelectedItem(tContext, theItem)

        If (tStatus <> DBX_OK) Then
            statusLabel2.Caption = Return_error_message(tStatus)
        ElseIf (theItem.itemType = DBX_COMPONENT) Then
            theComp = theItem.component
            CompList.AddItem theComp.refDes
            statusLabel.Caption = CompList.ListCount & " components selected."
        End If

    Wend

    statusLabel2.Caption = Return_error_message(tStatus)

End Sub

Private Sub Update_Click()
'
'  Up RefDes2 on selected components
'

    statusLabel.Caption = ""
    statusLabel2.Caption = ""

    Design_Open
    
    If (tStatus <> DBX_OK) Then

        statusLabel2.Caption = Return_error_message(tStatus)

    Else

        CompList2.Clear
        CompList.Visible = 0
        CompList2.Visible = -1
        I = 0
        J = 1

        While (I < CompList.ListCount)

            got_refdes2 = 0

            tStatus = TGetCompByRefDes(tContext, CompList.List(I), theComp)


'  Get the first attribute of the current component

            tstatus2 = TGetFirstCompAttribute(tContext, theComp.refDes, theAttr)

            If (tstatus2 <> DBX_OK) Then
                statusLabel.Caption = Return_error_message(tstatus2)
                GoTo CloseDesign3
            End If


            While ((tstatus2 = DBX_OK) And (got_refdes2 = 0))

' If the attribute is RefDes2, set its value = Reference Designator

                If (UCase(Strip_Nulls(theAttr.name)) = "REFDES2") Then

                    theAttr.value = Trim(theComp.refDes)
                    got_refdes2 = 1
                    tstatus3 = TModifyCompAttribute(tContext, theComp.refDes, theAttr)

                    If (tstatus3 = DBX_OK) Then
                        If (J = 1) Then
                            statusLabel.Caption = "One component updated."
                        Else
                            statusLabel.Caption = J & " components updated."
                        End If

                    CompList2.AddItem "Updated - " & Trim(theComp.refDes)
                    J = J + 1

                    Else
                        statusLabel.Caption = Return_error_message(tstatus3)
                    End If

                End If

' //Get the next attribute of the current component

                tstatus2 = TGetNextCompAttribute(tContext, theAttr)

            Wend

            If (got_refdes2 = 0) Then
                statusLabel.Caption = Strip_Nulls(theComp.refDes) & " has no RefDes2 attribute."
                CompList2.AddItem "No RefDes2 - " & Trim(theComp.refDes)
            End If

' //Get the next component

            I = I + 1

        Wend

    End If

    statusLabel2.Caption = Return_error_message(tStatus)

CloseDesign3:
    
    DesignClose


End Sub

