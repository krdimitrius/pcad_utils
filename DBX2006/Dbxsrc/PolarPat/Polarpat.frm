VERSION 5.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Create Circular Component Pattern"
   ClientHeight    =   5625
   ClientLeft      =   1125
   ClientTop       =   1815
   ClientWidth     =   4605
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
   ScaleHeight     =   5625
   ScaleWidth      =   4605
   Begin VB.TextBox startValue 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   3120
      TabIndex        =   19
      Top             =   2760
      Width           =   735
   End
   Begin VB.TextBox prefix 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1320
      TabIndex        =   18
      Top             =   2760
      Width           =   855
   End
   Begin VB.CheckBox EndAngleCompChk 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Last Comp at End Angle"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1320
      TabIndex        =   17
      Top             =   3840
      Width           =   2535
   End
   Begin VB.TextBox endAngle 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   3000
      TabIndex        =   15
      Top             =   2160
      Width           =   975
   End
   Begin VB.TextBox startAngle 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1920
      TabIndex        =   14
      Top             =   2160
      Width           =   975
   End
   Begin VB.CheckBox rotatecomp 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Rotate Components"
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   1320
      TabIndex        =   11
      Top             =   3360
      Width           =   2535
   End
   Begin VB.TextBox pattcentery 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   3000
      TabIndex        =   9
      Top             =   1680
      Width           =   975
   End
   Begin VB.TextBox pattcenterx 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1920
      TabIndex        =   8
      Top             =   1680
      Width           =   975
   End
   Begin VB.TextBox pattradius 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1920
      TabIndex        =   4
      Top             =   1200
      Width           =   2055
   End
   Begin VB.TextBox numComps 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1920
      TabIndex        =   3
      Top             =   720
      Width           =   2055
   End
   Begin VB.TextBox compType 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1920
      TabIndex        =   2
      Top             =   240
      Width           =   2055
   End
   Begin VB.CommandButton Command2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Exit"
      Height          =   255
      Left            =   2640
      TabIndex        =   1
      Top             =   4920
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Start"
      Height          =   255
      Left            =   480
      TabIndex        =   0
      Top             =   4920
      Width           =   1455
   End
   Begin VB.Label Label8 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Start Value"
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   2400
      TabIndex        =   21
      Top             =   2760
      Width           =   615
   End
   Begin VB.Label Label7 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Refdes Prefix"
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   480
      TabIndex        =   20
      Top             =   2760
      Width           =   735
   End
   Begin VB.Label Label6 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Start/End Angle (blank=0,360)"
      ForeColor       =   &H80000008&
      Height          =   495
      Left            =   240
      TabIndex        =   16
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label statusLabel 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   1080
      TabIndex        =   13
      Top             =   4560
      Width           =   3135
   End
   Begin VB.Label Label5 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Status"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   480
      TabIndex        =   12
      Top             =   4200
      Width           =   1215
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Pattern Center"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   480
      TabIndex        =   10
      Top             =   1680
      Width           =   1335
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Pattern Radius"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   360
      TabIndex        =   7
      Top             =   1200
      Width           =   1455
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Number of Comps"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   720
      Width           =   1695
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Component Type"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   360
      TabIndex        =   5
      Top             =   240
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()



Dim radius, numPatterns, incNumPatterns, centerx, centery As Long
Dim pi, theta, thetaIncrement, thetaDegree, startTheta As Double
Dim dummy As Single
Dim suffixValue As Long
Dim refx, refy As Long
Dim newComp As TComponent
Dim origpoint As TCoord
Dim i As Long

    centerx = Val(pattcenterx.text)
    centery = Val(pattcentery.text)
    numPatterns = Val(numComps.text)
    radius = Val(pattradius)

    Unit = DBX_UNIT_MIL
'
'  Validate all fields
'
    If (centerx <= 0 Or centery <= 0) Then
        statusLabel.Caption = "Invalid Center Point"
        GoTo Done
    End If
    If ((startAngle.text <> "" And Val(startAngle) < 0) Or (endAngle <> "" And Val(endAngle) <= 0)) Then
        statusLabel.Caption = "Invalid Start or End Angle"
        GoTo Done
    End If

    If (radius <= 0) Then
        statusLabel.Caption = "Invalid Radius"
        GoTo Done
    End If
    If (numPatterns <= 0) Then
        statusLabel.Caption = "Invalid Number of Components"
        GoTo Done
    End If

    If (startAngle.text = "") Then
        startAngle.text = "0"
    End If
    If (endAngle.text = "") Then
        endAngle.text = "360"
    End If
    If (Val(endAngle.text) <= Val(startAngle)) Then
        statusLabel.Caption = "Start Angle Greater Than End Angle"
        GoTo Done
    End If

    If (prefix.text = "") Then
        prefix.text = "U"
    End If
    If (startValue.text = "" Or Val(startValue.text) < 0) Then
        startValue.text = "1"
    End If

'
'  Open the design
'
    tStatus = TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "", tContext)
    If (tStatus <> DBX_OK) Then
        statusLabel.Caption = Return_error_message(tStatus)
        GoTo Done
    End If

'
'  Determine the angular increment.  This depends on whether or not the final component
'  is placed at the end angle or not.
'
    incNumPatterns = numPatterns
    If (EndAngleCompChk.value = 1) Then
        incNumPatterns = incNumPatterns - 1
    End If

    pi = 4 * Atn(1)
    thetaIncrement = (Val(endAngle.text) - Val(startAngle.text)) / incNumPatterns   ' in degrees
    thetaIncrement = (thetaIncrement * pi) / 180                                    ' convert to radians
    startTheta = (Val(startAngle.text) * pi) / 180                                  ' convert to radians

'
'  Set the starting value for the new components and the rotation origin
'
    suffixValue = Val(startValue.text)
    origpoint.x = -1
    origpoint.y = -1

    For i = 0 To (numPatterns - 1)
    
        theta = startTheta + thetaIncrement * i
        dummy = centerx + (radius * (Cos(theta)))
        refx = Db_Convert(dummy)
        dummy = centery + (radius * (Sin(theta)))
        refy = Db_Convert(dummy)

        suffixValue = i + Val(startValue.text)

        newComp.libraryName = Chr(0)      '  uses the first open library with the correct comp type
        newComp.refPoint.x = refx
        newComp.refPoint.y = refy
        newComp.compType = Trim(compType.text) & Chr(0)
        newComp.refDes = Trim(prefix.text) & Format$(suffixValue) & Chr(0)

        '
        '  Place the comp
        '
        tStatus = TPlaceComponent(tContext, newComp)
        If (tStatus <> DBX_OK) Then
            statusLabel.Caption = Return_error_message(tStatus)
            GoTo CloseDesign
        Else
            statusLabel.Caption = "Component #" & Format$(i) & " placed."
        End If

        '
        '  Rotate if checkbox is checked.
        '
        If (rotatecomp.value = 1) Then
            thetaDegree = (theta * 1800) / pi
            tStatus = TRotateComponent(tContext, thetaDegree, origpoint, newComp)
            If (tStatus <> DBX_OK) Then
                statusLabel.Caption = Return_error_message(tStatus)
                GoTo CloseDesign
            End If
        End If
    Next
    statusLabel.Caption = Format$(i) & " Components placed."
            
CloseDesign:
    tStatus = TCloseDesign(tContext, "")

Done:


End Sub

Private Sub Command2_Click()
    End
End Sub

Private Sub Form_Load()

    startAngle.text = "0"
    endAngle.text = "360"
    prefix.text = "U"
    startValue.text = "1"

End Sub

