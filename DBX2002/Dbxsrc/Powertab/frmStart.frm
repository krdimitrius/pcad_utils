VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmStart 
   Caption         =   "Power Table"
   ClientHeight    =   4950
   ClientLeft      =   4155
   ClientTop       =   3060
   ClientWidth     =   7335
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4950
   ScaleWidth      =   7335
   Begin VB.CommandButton cmdRun 
      Caption         =   "Run"
      Enabled         =   0   'False
      Height          =   345
      Left            =   2280
      TabIndex        =   15
      Top             =   4440
      Width           =   975
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   345
      Left            =   4080
      TabIndex        =   14
      Top             =   4440
      Width           =   975
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   4215
      Left            =   0
      TabIndex        =   0
      Top             =   30
      Width           =   7335
      _ExtentX        =   12938
      _ExtentY        =   7435
      _Version        =   393216
      Tabs            =   4
      TabsPerRow      =   4
      TabHeight       =   520
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "Options"
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "lblTitle"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "lblSheetNumber"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "lblTextStyleId"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "lblRowSpacing"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "lblColumnSpacing"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "lblYOrigin"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "lblXOrigin"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).Control(7)=   "lblStatus"
      Tab(0).Control(7).Enabled=   0   'False
      Tab(0).Control(8)=   "chkHiddenPinsOnly"
      Tab(0).Control(8).Enabled=   0   'False
      Tab(0).Control(9)=   "txtTitle"
      Tab(0).Control(9).Enabled=   0   'False
      Tab(0).Control(10)=   "txtColumnSpacing"
      Tab(0).Control(10).Enabled=   0   'False
      Tab(0).Control(11)=   "txtRowSpacing"
      Tab(0).Control(11).Enabled=   0   'False
      Tab(0).Control(12)=   "txtYOrigin"
      Tab(0).Control(12).Enabled=   0   'False
      Tab(0).Control(13)=   "txtXOrigin"
      Tab(0).Control(13).Enabled=   0   'False
      Tab(0).Control(14)=   "ComboTextStyle"
      Tab(0).Control(14).Enabled=   0   'False
      Tab(0).Control(15)=   "ComboSheetName"
      Tab(0).Control(15).Enabled=   0   'False
      Tab(0).Control(16)=   "cmdRefresh"
      Tab(0).Control(16).Enabled=   0   'False
      Tab(0).ControlCount=   17
      TabCaption(1)   =   "Components"
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Label4"
      Tab(1).Control(1)=   "Label1"
      Tab(1).Control(2)=   "Command6"
      Tab(1).Control(3)=   "Command5"
      Tab(1).Control(4)=   "ListCompsNotSelected"
      Tab(1).Control(5)=   "ListCompsSelected"
      Tab(1).Control(6)=   "Command4"
      Tab(1).Control(7)=   "Command3"
      Tab(1).ControlCount=   8
      TabCaption(2)   =   "Attributes "
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "Label2"
      Tab(2).Control(1)=   "Label3"
      Tab(2).Control(2)=   "ListAttrsSelected"
      Tab(2).Control(3)=   "ListAttrsNotSelected"
      Tab(2).Control(4)=   "Command1"
      Tab(2).Control(5)=   "Command2"
      Tab(2).Control(6)=   "Command7"
      Tab(2).Control(7)=   "Command8"
      Tab(2).ControlCount=   8
      TabCaption(3)   =   "Nets"
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "lblNetsNotPicked"
      Tab(3).Control(1)=   "lblNetsPicked"
      Tab(3).Control(2)=   "cmdRemoveNets"
      Tab(3).Control(3)=   "cmdAddNets"
      Tab(3).Control(4)=   "listNetsSelected"
      Tab(3).Control(5)=   "listNetsNotSelected"
      Tab(3).Control(6)=   "cmdAddAll"
      Tab(3).Control(7)=   "cmdRemoveAll"
      Tab(3).ControlCount=   8
      Begin VB.CommandButton cmdRefresh 
         Caption         =   "Gather Design Info"
         Height          =   345
         Left            =   2520
         TabIndex        =   43
         Top             =   510
         Width           =   1695
      End
      Begin VB.ComboBox ComboSheetName 
         Height          =   315
         ItemData        =   "frmStart.frx":0000
         Left            =   4560
         List            =   "frmStart.frx":0002
         Style           =   2  'Dropdown List
         TabIndex        =   42
         Top             =   1770
         Width           =   1935
      End
      Begin VB.ComboBox ComboTextStyle 
         Height          =   315
         ItemData        =   "frmStart.frx":0004
         Left            =   4560
         List            =   "frmStart.frx":0006
         Style           =   2  'Dropdown List
         TabIndex        =   41
         Top             =   2160
         Width           =   1935
      End
      Begin VB.CommandButton cmdRemoveAll 
         Caption         =   "Remove All"
         Height          =   405
         Left            =   -71880
         TabIndex        =   38
         Top             =   2250
         Width           =   1095
      End
      Begin VB.CommandButton cmdAddAll 
         Caption         =   "Add All"
         Height          =   405
         Left            =   -71880
         TabIndex        =   37
         Top             =   1770
         Width           =   1095
      End
      Begin VB.ListBox listNetsNotSelected 
         Height          =   2790
         ItemData        =   "frmStart.frx":0008
         Left            =   -74640
         List            =   "frmStart.frx":000A
         MultiSelect     =   2  'Extended
         Sorted          =   -1  'True
         TabIndex        =   36
         Top             =   900
         Width           =   2055
      End
      Begin VB.ListBox listNetsSelected 
         Height          =   2790
         ItemData        =   "frmStart.frx":000C
         Left            =   -70080
         List            =   "frmStart.frx":000E
         MultiSelect     =   2  'Extended
         TabIndex        =   35
         Top             =   900
         Width           =   2055
      End
      Begin VB.CommandButton cmdAddNets 
         Caption         =   "Add"
         Height          =   405
         Left            =   -71880
         TabIndex        =   34
         Top             =   1050
         Width           =   1095
      End
      Begin VB.CommandButton cmdRemoveNets 
         Caption         =   "Remove"
         Height          =   405
         Left            =   -71880
         TabIndex        =   33
         Top             =   2940
         Width           =   1095
      End
      Begin VB.CommandButton Command3 
         Caption         =   "Remove"
         Height          =   405
         Left            =   -71880
         TabIndex        =   30
         Top             =   2940
         Width           =   1095
      End
      Begin VB.CommandButton Command4 
         Caption         =   "Add"
         Height          =   405
         Left            =   -71880
         TabIndex        =   29
         Top             =   1050
         Width           =   1095
      End
      Begin VB.ListBox ListCompsSelected 
         Height          =   2790
         ItemData        =   "frmStart.frx":0010
         Left            =   -70080
         List            =   "frmStart.frx":0012
         MultiSelect     =   2  'Extended
         TabIndex        =   28
         Top             =   900
         Width           =   2055
      End
      Begin VB.ListBox ListCompsNotSelected 
         Height          =   2790
         ItemData        =   "frmStart.frx":0014
         Left            =   -74640
         List            =   "frmStart.frx":0016
         MultiSelect     =   2  'Extended
         Sorted          =   -1  'True
         TabIndex        =   27
         Top             =   900
         Width           =   2055
      End
      Begin VB.CommandButton Command5 
         Caption         =   "Add All"
         Height          =   405
         Left            =   -71880
         TabIndex        =   26
         Top             =   1770
         Width           =   1095
      End
      Begin VB.CommandButton Command6 
         Caption         =   "Remove All"
         Height          =   405
         Left            =   -71880
         TabIndex        =   25
         Top             =   2250
         Width           =   1095
      End
      Begin VB.CommandButton Command8 
         Caption         =   "Add"
         Height          =   405
         Left            =   -71880
         TabIndex        =   24
         Top             =   1050
         Width           =   1095
      End
      Begin VB.CommandButton Command7 
         Caption         =   "Remove"
         Height          =   405
         Left            =   -71880
         TabIndex        =   23
         Top             =   2940
         Width           =   1095
      End
      Begin VB.CommandButton Command2 
         Caption         =   "Remove All"
         Height          =   405
         Left            =   -71880
         TabIndex        =   19
         Top             =   2250
         Width           =   1095
      End
      Begin VB.CommandButton Command1 
         Caption         =   "Add All"
         Height          =   405
         Left            =   -71880
         TabIndex        =   18
         Top             =   1770
         Width           =   1095
      End
      Begin VB.ListBox ListAttrsNotSelected 
         Height          =   2790
         ItemData        =   "frmStart.frx":0018
         Left            =   -74640
         List            =   "frmStart.frx":001A
         MultiSelect     =   2  'Extended
         Sorted          =   -1  'True
         TabIndex        =   17
         Top             =   900
         Width           =   2055
      End
      Begin VB.ListBox ListAttrsSelected 
         Height          =   2790
         ItemData        =   "frmStart.frx":001C
         Left            =   -70080
         List            =   "frmStart.frx":001E
         MultiSelect     =   2  'Extended
         TabIndex        =   16
         Top             =   900
         Width           =   2055
      End
      Begin VB.TextBox txtXOrigin 
         Height          =   285
         Left            =   1920
         TabIndex        =   6
         Text            =   "700"
         Top             =   1830
         Width           =   735
      End
      Begin VB.TextBox txtYOrigin 
         Height          =   285
         Left            =   1920
         TabIndex        =   5
         Text            =   "6200"
         Top             =   2160
         Width           =   735
      End
      Begin VB.TextBox txtRowSpacing 
         Height          =   285
         Left            =   1920
         TabIndex        =   4
         Text            =   "200"
         Top             =   2520
         Width           =   735
      End
      Begin VB.TextBox txtColumnSpacing 
         Height          =   285
         Left            =   1920
         TabIndex        =   3
         Text            =   "600"
         Top             =   2880
         Width           =   735
      End
      Begin VB.TextBox txtTitle 
         Height          =   285
         Left            =   1920
         TabIndex        =   2
         Text            =   "Power Table"
         Top             =   1290
         Width           =   4575
      End
      Begin VB.CheckBox chkHiddenPinsOnly 
         Caption         =   "Hidden Pins Only"
         Height          =   315
         Left            =   600
         TabIndex        =   1
         Top             =   540
         Value           =   1  'Checked
         Width           =   1695
      End
      Begin VB.Label lblNetsPicked 
         Caption         =   "Nets Selected"
         Height          =   315
         Left            =   -70080
         TabIndex        =   40
         Top             =   630
         Width           =   1335
      End
      Begin VB.Label lblNetsNotPicked 
         Caption         =   "Nets Not Selected"
         Height          =   315
         Left            =   -74640
         TabIndex        =   39
         Top             =   630
         Width           =   1695
      End
      Begin VB.Label Label1 
         Caption         =   "Components Not Selected"
         Height          =   315
         Left            =   -74640
         TabIndex        =   32
         Top             =   630
         Width           =   2055
      End
      Begin VB.Label Label4 
         Caption         =   "Components Selected"
         Height          =   315
         Left            =   -70080
         TabIndex        =   31
         Top             =   630
         Width           =   2055
      End
      Begin VB.Label lblStatus 
         Caption         =   "Gathering Design Info.  Please wait."
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   465
         Left            =   1440
         TabIndex        =   22
         Top             =   3630
         Width           =   5295
      End
      Begin VB.Label Label3 
         Caption         =   "Attributes Selected"
         Height          =   315
         Left            =   -70080
         TabIndex        =   21
         Top             =   630
         Width           =   2055
      End
      Begin VB.Label Label2 
         Caption         =   "Attributes Not Selected"
         Height          =   315
         Left            =   -74640
         TabIndex        =   20
         Top             =   630
         Width           =   2055
      End
      Begin VB.Label lblXOrigin 
         Caption         =   "UL X Origin"
         Height          =   285
         Left            =   600
         TabIndex        =   13
         Top             =   1860
         Width           =   975
      End
      Begin VB.Label lblYOrigin 
         Caption         =   "UL Y Origin"
         Height          =   285
         Left            =   600
         TabIndex        =   12
         Top             =   2220
         Width           =   975
      End
      Begin VB.Label lblColumnSpacing 
         Caption         =   "Row Spacing"
         Height          =   285
         Left            =   600
         TabIndex        =   11
         Top             =   2580
         Width           =   1095
      End
      Begin VB.Label lblRowSpacing 
         Caption         =   "Column Spacing"
         Height          =   285
         Left            =   600
         TabIndex        =   10
         Top             =   2940
         Width           =   1215
      End
      Begin VB.Label lblTextStyleId 
         Caption         =   "TextStyle Name"
         Height          =   285
         Left            =   3120
         TabIndex        =   9
         Top             =   2250
         Width           =   1455
      End
      Begin VB.Label lblSheetNumber 
         Caption         =   "Place on Sheet"
         Height          =   285
         Left            =   3120
         TabIndex        =   8
         Top             =   1860
         Width           =   1335
      End
      Begin VB.Label lblTitle 
         Caption         =   "Title"
         Height          =   285
         Left            =   600
         TabIndex        =   7
         Top             =   1290
         Width           =   855
      End
   End
End
Attribute VB_Name = "frmStart"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdAddAll_Click()


'Add all the netNames from NotSelected to Selected lists.  Remove all netNames from NotSelected list.


For j = 0 To (listNetsNotSelected.ListCount - 1) Step 1

    listNetsSelected.AddItem listNetsNotSelected.List(0)
    listNetsNotSelected.RemoveItem 0

Next


End Sub

Private Sub cmdAddNets_Click()

'Add all the selected netNames from NotSelected to Selected lists.
'Remove all selected netNames from NotSelected list.

num = 0

Do While (num <> listNetsNotSelected.ListCount)
    
    If (listNetsNotSelected.Selected(num) = True) Then
        listNetsSelected.AddItem listNetsNotSelected.List(num)
        listNetsNotSelected.RemoveItem num
    Else
        num = num + 1
    End If
    
Loop

End Sub


Private Sub cmdExit_Click()

End

End Sub


Private Sub cmdRefresh_Click()

'  Open the active design, exit if an error occurred.

tStatus = TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "SCH", tContext)
Debug.Print ; Return_error_message(tStatus)
    
If (tStatus <> DBX_OK) Then
    frmStart.lblStatus.Caption = "Error Opening Desing: " & Return_error_message(tStatus)
    frmStart.lblStatus.Visible = True
    GoTo DBXError
End If
    

'Show the form and keep it disabled until done gathering info.

frmStart.lblStatus.Caption = "Gathering Design Info. Please Wait."
frmStart.Show
frmStart.Enabled = False


'Show the Please wait msg.

frmStart.lblStatus.Visible = True

'Clear all list boxes

listNetsSelected.Clear
listNetsNotSelected.Clear
ListCompsNotSelected.Clear
ListCompsSelected.Clear
ListAttrsNotSelected.Clear
ListAttrsSelected.Clear

'Reset error flag
errorFlag = 0


'Enable the run button since gather has been run.

cmdRun.Enabled = True


'Get all the Sheet Names and populate the combobox.

ComboSheetName.Clear
tStatus = TGetFirstLayer(tContext, layer)

Do While (tStatus = DBX_OK)
    If (layer.layerId <> 0) Then
        ComboSheetName.AddItem layer.layerName
    End If
    
    tStatus = TGetNextLayer(tContext, layer)
Loop


'Set first sheet name as current combo box text

ComboSheetName.text = ComboSheetName.List(0)



'Get all the textstyle names and populate the combobox.

ComboTextStyle.Clear
styleId = 0


'Need to check for textstyles 0-99

Do While (styleId <> 100)
    tStatus = TGetTextStyle(tContext, styleId, textStyle)
    
    If (tStatus = DBX_OK) Then
        ComboTextStyle.AddItem textStyle.name
        ComboTextStyle.ItemData(ComboTextStyle.ListCount - 1) = textStyle.styleId
    End If
    
    styleId = styleId + 1
Loop


'Set the inital textstyle

frmStart.ComboTextStyle.text = ComboTextStyle.List(0)


'******************************************************************************
'Get all the comps with power pins and add them to the list.

If (frmStart.chkHiddenPinsOnly.value = 1) Then
    Call Get_Comps_Hidden_Pins
    GoTo skipGetComps
End If

Call Get_Comps

skipGetComps:

If (errorFlag = 1) Then
    GoTo DBXError
End If



'******************************************************************************
' Get all the power pin net names and populate the Selected nets list box.


tStatus = TGetFirstNet(tContext, net)

If (tStatus <> DBX_OK) Then
    frmStart.lblStatus.Caption = "Net Error: " & Return_error_message(tStatus)
    GoTo DBXError
End If


Do While (tStatus = DBX_OK)

    tStatus = TGetFirstNetNode(tContext, net.netId, item)
 
    'Not a valid check because placing a wire creates a no node net and we should not error on that.
    'If (tStatus <> DBX_OK) Then
        'frmStart.lblStatus.Caption = "Net Node Error: " & Return_error_message(tStatus)
        'GoTo DBXError
    'End If
    
    Do While (tStatus = DBX_OK)
    
        If (frmStart.chkHiddenPinsOnly.value = 1) Then
            If (Trim(item.pin.compPin.electype) & Chr(0) = 10 And item.pin.compPin.gateNumber = 0) Then
                refDes = Trim(item.pin.compRefDes) & Chr(0)
                tStatus = TGetCompByRefDes(tContext, refDes, component)
                If (component.connectionType = 0) Then
                    listNetsSelected.AddItem Trim(net.netName) & Chr(0)
                    GoTo foundPowerNode
                End If
            End If
        Else
            If (Trim(item.pin.compPin.electype) & Chr(0) = 10) Then
                refDes = Trim(item.pin.compRefDes) & Chr(0)
                tStatus = TGetCompByRefDes(tContext, refDes, component)
                If (component.connectionType = 0) Then
                    listNetsSelected.AddItem Trim(net.netName) & Chr(0)
                    GoTo foundPowerNode
                End If
            End If
        End If
        
        tStatus = TGetNextNetNode(tContext, item)
    
    Loop
    
foundPowerNode:
    
    tStatus = TGetNextNet(tContext, net)
    
Loop



'*******************************************************************************
'Get the selected component's attributes and populate the NotSelected Attrs list.

'Create attrs() array.

attrCount = 0
attrsArraySize = 100
ReDim Attrs(1 To 100) As TAttribute

SlotNumber = 0
    
    Do While (SlotNumber <> frmStart.ListCompsSelected.ListCount)
       
        refDes = Trim(frmStart.ListCompsSelected.List(SlotNumber)) & Chr(0)
            
        tStatus = TGetFirstCompAttribute(tContext, refDes, attr)
                
        If (tStatus <> DBX_OK) Then
            frmStart.lblStatus.Caption = "Attribute error: " & Return_error_message(tStatus)
            GoTo DBXError
        End If
        
        Do While (tStatus = DBX_OK)
            Call Is_Attr_New
            tStatus = TGetNextCompAttribute(tContext, attr)
        Loop
               
        SlotNumber = SlotNumber + 1
        
    Loop
        

'Add RefDes to the Selected list since it is needed to make sence of the table.
'Need to find and grab it from the Not Selected list and add to the Selected list.

currentAttrName$ = "RefDes"

listCounter = 0

Do While (listCounter <> frmStart.ListAttrsNotSelected.ListCount)

    arrayAttrName$ = frmStart.ListAttrsNotSelected.List(listCounter)

    If (Strip_Nulls(currentAttrName$) = Strip_Nulls(arrayAttrName$)) Then
        frmStart.ListAttrsNotSelected.RemoveItem (listCounter)
        frmStart.ListAttrsSelected.AddItem "RefDes"
        GoTo FoundRefdes
    End If

    listCounter = listCounter + 1

Loop

FoundRefdes:


'Add pattern to the list.  It is not an attribute and needs special attention.

frmStart.ListAttrsNotSelected.AddItem "Pattern"


'If there is no error hide the display of the Please wait msg.
frmStart.lblStatus.Visible = False

'Jump here when an error is detected
DBXError:

'Close the design
    
tStatus = TCloseDesign(tContext, "")

'Enable the dialog
frmStart.Enabled = True



End Sub

Private Sub cmdRemoveAll_Click()


'Remove all the netNames from Selected to NotSelected lists.  Remove all netNames from Selected list.


For j = 0 To (listNetsSelected.ListCount - 1) Step 1

    listNetsNotSelected.AddItem listNetsSelected.List(0)
    listNetsSelected.RemoveItem 0

Next



End Sub

Private Sub cmdRemoveNets_Click()

'Remove all the selected netNames from Selected to NotSelected lists.  Remove all netNames from Selected list.

num = 0

Do While (num <> listNetsSelected.ListCount)
    
    If (listNetsSelected.Selected(num) = True) Then
        listNetsNotSelected.AddItem listNetsSelected.List(num)
        listNetsSelected.RemoveItem num
    Else
        num = num + 1
    End If
    
Loop



End Sub

Private Sub cmdRun_Click()

'Set inital UL corner of the table.

xSpacing = mil_to_db(Val(frmStart.txtColumnSpacing.text))
ySpacing = mil_to_db(Val(frmStart.txtRowSpacing.text))

originx = mil_to_db(Val(frmStart.txtXOrigin.text))
originy = mil_to_db(Val(frmStart.txtYOrigin.text))


'Set error flag to off or 0
errorFlag = 0


'Set the current tab to the first tab so messages can be seen.
SSTab1.Tab = 0


'Check all the user's settings and error if they are out of range.
Call Error_Checking

'If an error was found we need to skip to the end and don't exit.
If (errorFlag = 1) Then
    GoTo DBXError
End If


firstx = originx + (0.5 * xSpacing)  'mil_to_db(50)
firsty = originy - (2.5 * ySpacing)  '- mil_to_db(150)

x = firstx
y = firsty


'Set textStyleId to use in the table.

TextStyleId = frmStart.ComboTextStyle.ItemData(ComboTextStyle.ListIndex)


'Initalize variables

netId = 1

skipNetName = 1


'Set pattern flag to 0 so it will be placed.

patternPlaced = 0


'Create nets array

arraysize = 100
ReDim Nets(1 To 100) As TNet


'Placing the table, this could take a while so put up a msg.
frmStart.lblStatus.Caption = "Placing Table..."
frmStart.lblStatus.Visible = True


'  Open the active design, exit if an error occurred.

tStatus = TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "SCH", tContext)
Debug.Print ; Return_error_message(tStatus)

If (tStatus <> DBX_OK) Then
    frmStart.lblStatus.Caption = "Error Opening Desing: " & Return_error_message(tStatus)
    frmStart.lblStatus.Visible = True
    GoTo DBXError
End If


'Set layerId, so we know which sheet to place the table on.

tStatus = TGetLayerByName(tContext, ComboSheetName.text, layer)

If (tStatus <> DBX_OK) Then
    frmStart.lblStatus.Caption = "Layer Error : " & Return_error_message(tStatus)
    frmStart.lblStatus.Visible = True
    GoTo DBXError
End If

layerId = layer.layerId


'Place all the Attributes and Net Names from the selected list in the table.
Call Place_Selected_Text

If (errorFlag = 1) Then
    GoTo DBXError
End If
    

' Using each refdes from the selected group, go through their attrs and pins.
   
SlotNumber = 0

Dim maxSlot As Integer

maxSlot = Strip_Nulls(ListCompsSelected.ListCount)

Do While (SlotNumber <> maxSlot)
    
'Create Nodes array

    nodesArraySize = 100
    ReDim Nodes(1 To 100) As TNode
    pincount = 0
    
    nodeCount = 0
    n = 0
        
    
'Set the current refdes by looking at the selected comps slot number.
    
    refDes = frmStart.ListCompsSelected.List(SlotNumber)
        
    
'Check the Selected attributes against the current comp.  If selected
'atters are found place their text.
    
    tStatus3 = TGetFirstCompAttribute(tContext, refDes, attr)
    If (tStatus3 <> DBX_OK) Then
        frmStart.lblStatus.Caption = "Attribute Error: " & Return_error_message(tStatus3)
        frmStart.lblStatus.Visible = True
        GoTo DBXError
    End If
           
    Do While (tStatus3 = DBX_OK)
        Call Is_Attr_In_List
        
        If (errorFlag = 1) Then
            GoTo DBXError
        End If
        
        tStatus3 = TGetNextCompAttribute(tContext, attr)
    Loop

    
    'Get first comp pin.
    
    tStatus = TGetFirstCompPin(tContext, refDes, pin)
     
    
    'If Hidden Pins only options is checked call that function.
    
    If (frmStart.chkHiddenPinsOnly.value = 1) Then
        Call Only_Place_Hidden_Pins
        
        If (errorFlag = 1) Then
            GoTo DBXError
        End If
        
        GoTo skipNonHiddenPins
    End If
    
        
    If (pin.compPin.electype = 10 And pin.netId <> 0) Then
        
        'Store pins in nodes array for later grouping of same net pindeses.
    
        pincount = 1
        Nodes(pincount).mypinDes = Strip_Nulls(pin.compPin.pinDes) & Chr(0)
        Nodes(pincount).netId = Trim(pin.netId) & Chr(0)
        netId = Trim(pin.netId) & Chr(0)
                          
    End If
    
    
    'Get all the comp's pin.
    
    Do While (tStatus = DBX_OK)
        
        'Get next CompPin

        tStatus = TGetNextCompPin(tContext, pin)
        
        If (tStatus <> DBX_OK) Then
            GoTo NoMorePins
        End If
        
            
        If (pin.compPin.electype = 10 And pin.netId <> 0) Then
                   
        
        'Store pins in nodes array for later grouping of same net pindeses.
    
            pincount = pincount + 1
        
            If (pincount > nodesArraySize) Then
                nodesArraySize = nodesArraySize + 100
                ReDim Preserve Nodes(1 To nodesArraySize) As TNode
            End If
        
            Nodes(pincount).mypinDes = Strip_Nulls(pin.compPin.pinDes) & Chr(0)
            Nodes(pincount).netId = Trim(pin.netId) & Chr(0)
            netId = Trim(pin.netId) & Chr(0)
               
    End If
 
    Loop    'End of GetFirst/NextCompPin Loop.
    
NoMorePins:
skipNonHiddenPins:
    
    
    'All the power nodes are stored in the nodes array. Go group and place them.
        
    Call Is_Net_New
       
    If (errorFlag = 1) Then
        GoTo DBXError
    End If
    
 
    'Look at the next refdes selected
    SlotNumber = SlotNumber + 1
    
    
    'Move down to the next row in prep for the next comp.
    y = y - ySpacing
     
    
    'Set newComp flag to triger the y location change for a new refDes.
    'If this is the first comp in the table we don't want newcComp to = 1.
    
    If (netcount <> 0) Then
        newComp = 1
    End If
    
    
    'Clear flag so pattern will be placed for each comp.
    patternPlaced = 0
    
Loop  'End of CompsSelected loop.
    

error_out:



'Place the all the lines in the table as well as the title text.
Call Place_Lines

If (errorFlag = 1) Then
    GoTo DBXError
End If


'The table has been placed without an error.
'Display Done placing table msg.

frmStart.lblStatus.Caption = "Done Placing Table."
frmStart.lblStatus.Visible = True


'If there is an error jump to here
DBXError:

'Close the design
    
tStatus = TCloseDesign(tContext, "")



End Sub


Private Sub Command1_Click()


'Add all the comp attrs from NotSelected to Selected lists.  Remove all comp Attrs from NotSelected list.


For j = 0 To (ListAttrsNotSelected.ListCount - 1) Step 1

    ListAttrsSelected.AddItem ListAttrsNotSelected.List(0)
    ListAttrsNotSelected.RemoveItem 0

Next


End Sub

Private Sub Command2_Click()


'Remove all the comp attrs from Selected to NotSelected lists.  Remove all comp attrs from Selected list.


For j = 0 To (ListAttrsSelected.ListCount - 1) Step 1

    ListAttrsNotSelected.AddItem ListAttrsSelected.List(0)
    ListAttrsSelected.RemoveItem 0

Next


End Sub

Private Sub Command3_Click()

num = 0

Do While (num <> ListCompsSelected.ListCount)
    
    If (ListCompsSelected.Selected(num) = True) Then
        ListCompsNotSelected.AddItem ListCompsSelected.List(num)
        ListCompsSelected.RemoveItem num
    Else
        num = num + 1
    End If
    
Loop


End Sub

Private Sub Command4_Click()

num = 0

Do While (num <> ListCompsNotSelected.ListCount)
    
    If (ListCompsNotSelected.Selected(num) = True) Then
        ListCompsSelected.AddItem ListCompsNotSelected.List(num)
        ListCompsNotSelected.RemoveItem num
    Else
        num = num + 1
    End If
    
Loop


End Sub

Private Sub Command5_Click()

'Add all the comp attrs from NotSelected to Selected lists.  Remove all comp Attrs from NotSelected list.


For j = 0 To (ListCompsNotSelected.ListCount - 1) Step 1

    ListCompsSelected.AddItem ListCompsNotSelected.List(0)
    ListCompsNotSelected.RemoveItem 0

Next


End Sub

Private Sub Command6_Click()

'Remove all the comp refDes from Selected to NotSelected lists.  Remove all comp refdes from Selected list.


For j = 0 To (ListCompsSelected.ListCount - 1) Step 1

    ListCompsNotSelected.AddItem ListCompsSelected.List(0)
    ListCompsSelected.RemoveItem 0

Next



End Sub

Private Sub Command7_Click()

num = 0

Do While (num <> ListAttrsSelected.ListCount)
    
    If (ListAttrsSelected.Selected(num) = True) Then
        ListAttrsNotSelected.AddItem ListAttrsSelected.List(num)
        ListAttrsSelected.RemoveItem num
    Else
        num = num + 1
    End If
    
Loop


End Sub

Private Sub Command8_Click()

num = 0

Do While (num <> ListAttrsNotSelected.ListCount)
    
    If (ListAttrsNotSelected.Selected(num) = True) Then
        ListAttrsSelected.AddItem ListAttrsNotSelected.List(num)
        ListAttrsNotSelected.RemoveItem num
    Else
        num = num + 1
    End If
    
Loop


End Sub

Private Sub Form_Load()

frmStart.lblStatus.Visible = False
frmStart.Enabled = True



End Sub

Private Sub listAttrsNotSelected_DblClick()

'When you doubble click on an item in this list it gets added to the
'other list and deleted from this list.


ListAttrsSelected.AddItem ListAttrsNotSelected.List(ListAttrsNotSelected.ListIndex)

ListAttrsNotSelected.RemoveItem ListAttrsNotSelected.ListIndex



End Sub


Private Sub ListAttrsSelected_DblClick()

'When you doubble click on an item in this list it gets added to the
'other list and deleted from this list.


ListAttrsNotSelected.AddItem ListAttrsSelected.List(ListAttrsSelected.ListIndex)

ListAttrsSelected.RemoveItem ListAttrsSelected.ListIndex



End Sub


Private Sub ListCompsNotSelected_DblClick()

'When you doubble click on an item in this list it gets added to the
'other list and deleted from this list.


ListCompsSelected.AddItem ListCompsNotSelected.List(ListCompsNotSelected.ListIndex)

ListCompsNotSelected.RemoveItem ListCompsNotSelected.ListIndex



End Sub


Private Sub ListCompsSelected_DblClick()

'When you doubble click on an item in this list it gets added to the
'other list and deleted from this list.


ListCompsNotSelected.AddItem ListCompsSelected.List(ListCompsSelected.ListIndex)

ListCompsSelected.RemoveItem ListCompsSelected.ListIndex



End Sub


Private Sub listNetsNotSelected_DblClick()

'When you doubble click on an item in this list it gets added to the
'other list and deleted from this list.


listNetsSelected.AddItem listNetsNotSelected.List(listNetsNotSelected.ListIndex)

listNetsNotSelected.RemoveItem listNetsNotSelected.ListIndex



End Sub


Private Sub listNetsSelected_DblClick()

'When you doubble click on an item in this list it gets added to the
'other list and deleted from this list.


listNetsNotSelected.AddItem listNetsSelected.List(listNetsSelected.ListIndex)

listNetsSelected.RemoveItem listNetsSelected.ListIndex



End Sub




