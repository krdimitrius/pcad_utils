VERSION 5.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Absolute Component Rotation"
   ClientHeight    =   3510
   ClientLeft      =   2685
   ClientTop       =   1740
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
   ScaleHeight     =   3510
   ScaleWidth      =   5175
   Begin VB.ListBox CompList 
      Appearance      =   0  'Flat
      Height          =   1395
      Left            =   120
      TabIndex        =   8
      Top             =   360
      Width           =   2532
   End
   Begin VB.CommandButton Get_Comps 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Get Component(s)"
      Height          =   375
      Left            =   3060
      TabIndex        =   2
      Top             =   360
      Width           =   1935
   End
   Begin VB.TextBox Angle 
      Appearance      =   0  'Flat
      Height          =   315
      Left            =   1440
      TabIndex        =   3
      Top             =   2040
      Width           =   1215
   End
   Begin VB.CommandButton Apply 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Apply"
      Height          =   375
      Left            =   3060
      TabIndex        =   7
      Top             =   900
      Width           =   1935
   End
   Begin VB.CommandButton Exit 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Exit"
      Height          =   375
      Left            =   3060
      TabIndex        =   0
      Top             =   1440
      Width           =   1935
   End
   Begin VB.Label statusLabel 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   180
      TabIndex        =   9
      Top             =   2820
      Width           =   4935
   End
   Begin VB.Label Label9 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Rotation Angle:"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   2100
      Width           =   1335
   End
   Begin VB.Label statusLabel2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   180
      TabIndex        =   5
      Top             =   3180
      Width           =   4935
   End
   Begin VB.Label Label5 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Status:"
      ForeColor       =   &H80000008&
      Height          =   195
      Left            =   120
      TabIndex        =   4
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Component List:"
      ForeColor       =   &H80000008&
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
Dim newAngle As Long
Dim tStatus As Long

Private Sub Apply_Click()
'
'  Update the component(s)
'
    statusLabel.Caption = ""
    statusLabel2.Caption = ""

    If (Angle.text = "") Then
        statusLabel.Caption = "Please enter new Rotation Angel."
        GoTo Done2
    End If

    Design_Open
    If (tStatus <> DBX_OK) Then
        statusLabel2.Caption = Return_error_message(tStatus)
        GoTo Done2
    Else
        I = 0
        While (I < CompList.ListCount)

            tStatus = TGetCompByRefDes(tContext, CompList.List(I), theComp)

            If (tStatus <> DBX_OK) Then
                statusLabel2.Caption = Return_error_message(tStatus)
                GoTo Done2
            Else
                If (theComp.isFlipped = 0) Then
                    newAngle = -theComp.rotationAng + (Val(Angle.text) * 10)
                Else
                    newAngle = 3600 + theComp.rotationAng - (Val(Angle.text) * 10)
                End If

                origpoint.x = -1
                origpoint.y = -1
                    tStatus = TRotateComponent(tContext, newAngle, origpoint, theComp)
                If (tStatus <> DBX_OK) Then
                    statusLabel2.Caption = Return_error_message(tStatus)
                    GoTo Done2
                Else
                    statusLabel.Caption = "Rotated " & theComp.refDes
                End If

            End If

            I = I + 1

        Wend

        statusLabel2.Caption = Return_error_message(tStatus)
        statusLabel.Caption = Str(CompList.ListCount) & Switch(CompList.ListCount = 1, " component rotated.", CompList.ListCount <> 1, " components rotated.")
    
    End If

Done2:

    DesignClose

End Sub


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
    Angle.text = ""
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
'
'  Get the first component in the selection set
'
    tStatus = TGetFirstSelectedItem(tContext, theItem)
        If (tStatus <> DBX_OK) Then
            statusLabel.Caption = "Please select the components you wish to rotate."
        ElseIf (theItem.itemType = DBX_COMPONENT) Then
         theComp = theItem.component
         CompList.AddItem theComp.refDes
         Angle.text = Str(theComp.rotationAng / 10)
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
            If (Angle.text <> Str(theComp.rotationAng / 10)) Then Angle.text = ""
        End If

    Wend

    statusLabel2.Caption = Return_error_message(tStatus)

End Sub

