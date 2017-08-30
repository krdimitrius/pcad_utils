Attribute VB_Name = "SCHIN"

Global designInfo As TDesign
Global Nets() As TNet
Global netcount As Integer
Global item As TItem
Global mycomp As TComponent
Global mysymbol As TSymbol
Global attr As TAttribute

Global net As TNet
Global pin As TPin
Global compPin As TCompPin
Global component As TComponent
Global layer As TLayer

Global tstatus2 As Long
Global coord As TCoord
Global refPoint As TCoord

Global x As Long
Global y As Long
Global lastId As Long
Global originx As Long
Global originy As Long
Global xSpacing As Long
Global ySpacing As Long
Global TextStyleId As Integer
Global skipNetName As Integer
Global CurrentX As Long
Global CurrentY As Long
Global firstx As Long
Global firsty As Long
Global layerId As Integer
Global pinName As String
Global maxX As Long
Global node As TNode
Global nodesArraySize As Integer
Global nodeCount As Integer
Global attrCount As Integer
Global text As TText
Global aLine As TLine
Global textStyle As TTextStyle

Global Attrs() As TAttribute
Global Nodes() As TNode

Global numInCompsList As Integer
Global numInNetsList As Integer
Global num As Integer
Global pinDes As String
Global refDes As String
Global patternPlaced As Integer
Global styleId As Integer
Global errorFound As Integer
Global errorFlag As Integer
Global pincount As Integer
Global tStatus3 As Long

Type TNode
    mypinDes As String * 256
    netId As Long
End Type













Public Sub Place_text()
        
        'Setup and Place the refDes.
        
        text.refPoint.x = x
        text.refPoint.y = y
        text.layerId = layerId
        text.TextStyleId = TextStyleId
        text.justPoint = 5
         
        tstatus2 = TPlaceText(tContext, text)
        
        If (tstatus2 <> DBX_OK) Then
            frmStart.lblStatus.Caption = "Error Placing Text: " & Return_error_message(tstatus2)
            frmStart.lblStatus.Visible = True
            errorFlag = 1
        End If
        
        

End Sub

Public Sub Is_Net_New()

'Go group all the pindes in the nodes array that have the same netId

Call group_pinDes


'Need to look at all the pins in the array and get the netname from its netId.

currentpin = 1

Do While (currentpin < pincount + 1)

    netId = Nodes(currentpin).netId
    tStatus = TGetNetById(tContext, netId, net)
    currentNetName$ = Trim(net.netName) & Chr(0)

    n = 0

    Do While (n <> frmStart.listNetsSelected.ListCount)

        If (Strip_Nulls(currentNetName$) = Strip_Nulls(frmStart.listNetsSelected.List(n))) Then
    
            'Set currentX to the position of the already existing netName.
    
            x = (frmStart.ListAttrsSelected.ListCount * xSpacing) + (n * xSpacing) + firstx
            text.text = Trim(Nodes(currentpin).mypinDes) & Chr(0)
                
            Call Place_text
        
        End If

        n = n + 1

    Loop
    
    
    currentpin = currentpin + 1

Loop




End Sub

Public Sub Place_Lines()


'Setup and place the top horizontal line and moving down fill in all horizontal lines.

Hlines = 3 + frmStart.ListCompsSelected.ListCount

h = 0

Do While (h < Hlines)

    aLine.startPt.x = originx
    aLine.startPt.y = originy - (h * ySpacing)

    aLine.endPt.x = originx + (xSpacing * frmStart.listNetsSelected.ListCount) + (frmStart.ListAttrsSelected.ListCount * xSpacing)

    aLine.endPt.y = originy - (h * ySpacing)

    aLine.lineType = 0
    aLine.width = mil_to_db(10)
    aLine.layerId = layerId

    tStatus = TPlaceLine(tContext, aLine)
    
    If (tStatus <> DBX_OK) Then
        frmStart.lblStatus.Caption = "Error Placing Line: " & Return_error_message(tStatus)
        frmStart.lblStatus.Visible = True
        errorFlag = 1
        GoTo DBXError
    End If

    h = h + 1

Loop



'Setup and place the left most vertical line and moving to the right fill in the rest.

Vlines = 1 + frmStart.ListAttrsSelected.ListCount + frmStart.listNetsSelected.ListCount

v = 0

Do While (v < Vlines)

aLine.startPt.x = originx + (v * xSpacing)
aLine.startPt.y = originy

aLine.endPt.x = originx + (v * xSpacing)
aLine.endPt.y = originy - ((frmStart.ListCompsSelected.ListCount + 2) * ySpacing)

If (v >= 1) Then
    aLine.startPt.y = originy - ySpacing
End If

If (v = Vlines - 1) Then
    aLine.startPt.y = originy
End If

aLine.lineType = 0  'frmStart.txtlineType.text
aLine.width = mil_to_db(10)    'frmStart.txtlineWidth.text
aLine.layerId = layerId

tStatus = TPlaceLine(tContext, aLine)
If (tStatus <> DBX_OK) Then
    frmStart.lblStatus.Caption = "Error Placing Line: " & Return_error_message(tStatus)
    frmStart.lblStatus.Visible = True
    errorFlag = 1
    GoTo DBXError
End If

v = v + 1

Loop

            
'Setup and Place title text.
text.text = Trim(frmStart.txtTitle.text) & Chr(0)
text.refPoint.x = originx + (((xSpacing * frmStart.listNetsSelected.ListCount) + (frmStart.ListAttrsSelected.ListCount * xSpacing)) / 2)
text.refPoint.y = originy - (0.5 * ySpacing)
text.layerId = layerId
text.TextStyleId = TextStyleId
text.justPoint = 5
                
tstatus2 = TPlaceText(tContext, text)

If (tstatus2 <> DBX_OK) Then
    frmStart.lblStatus.Caption = "Error Placing Text: " & Return_error_message(tstatus2)
    frmStart.lblStatus.Visible = True
    errorFlag = 1
End If

DBXError:

End Sub

Public Sub group_pinDes()


'There is an array called Nodes() that should contains all the power nodes in the form
'of Nodes(n).pinDes and Nodes(n).netId.  We need to take the first nodes netId and
'find out if any of the other nodes in this array have the same netId.  If they do
'have the same netId, merge the pinDeses from the two nodes to look like
'pinDes1, pinDes2, pinDes3, ... (3, 7, 22,...).  Once a merge has taken place we
'must remove the merged pinDes node from the array so it is not found later by this loop.

'When the end of the array is reached all nodes with the same netId should be merged and
'ready for placement.

Dim masterpin As Integer
Dim checkpin As Integer


masterpin = 1
checkpin = 2

Do While (masterpin < pincount)
        
    Do While (checkpin < pincount + 1)
        
                
        'If the pins have the same netId merge them together into one item.
        
        If (Nodes(masterpin).netId = Nodes(checkpin).netId) Then
            Dim masterpinDes As String
            Dim checkpinDes As String
            
            masterpinDes$ = Strip_Nulls(Nodes(masterpin).mypinDes)
            checkpinDes$ = Strip_Nulls(Nodes(checkpin).mypinDes)
            
            Nodes(masterpin).mypinDes = masterpinDes$ & "," & checkpinDes$
            'Debug.Print "Nodes(n).PinDes = "; Trim(Nodes(c).pinDes) & Chr(0)
                       
            
            'Delete nodes(checkpin) from the array and adjust the pinCount.
            
            If (checkpin = pincount) Then
                pincount = pincount - 1
            Else
                saveMe = checkpin
                pincount = pincount - 1
            End If
            
            
            'Colapse the array to remove the merged node.
            
            Do While (checkpin < pincount + 1)
                Nodes(checkpin) = Nodes(checkpin + 1)
                checkpin = checkpin + 1
            Loop
                        
            
            'Reset checkpin and saveMe
            
            If (saveMe <> 0) Then
                checkpin = saveMe - 1
                saveMe = 0
            End If
                  
        End If
        
    
        checkpin = checkpin + 1
    
    Loop        'End of Do While checkpin < pinCount + 1
        
         
    masterpin = masterpin + 1
    checkpin = masterpin + 1

    If (checkpin > pincount) Then
        GoTo finished
    End If

    Loop         'End of Do While masterpin < pinCount


finished:



End Sub



Public Sub Is_Attr_New()


'Need to find out if current comp attr is new to the Table.

currentAttrName$ = Trim(attr.name) & Chr(0)

a = 1

If (attrCount = 0) Then
    GoTo first_attr
End If


Do While (a <> attrCount + 1)

    arrayAttrName$ = Trim(Attrs(a).name) & Chr(0)

    If (Strip_Nulls(currentAttrName$) = Strip_Nulls(arrayAttrName$)) Then
        GoTo found_attr
    End If

    a = a + 1

Loop


'This is a new comp attr.  Add it to the AttrsNotSelected box.

first_attr:

frmStart.listAttrsNotSelected.AddItem Trim(attr.name) & Chr(0)
attrCount = attrCount + 1
Attrs(a).name = currentAttrName$

found_attr:


End Sub



Public Sub Get_Comps()


' Get first component

tStatus = TGetFirstComponent(tContext, mycomp)
'Debug.Print ; "First Comp = "; mycomp.refDes

If (tStatus <> DBX_OK) Then
    frmStart.lblStatus.Caption = "Component error: " & Return_error_message(tStatus)
    errorFlag = 1
    GoTo error_out2
End If
    
    
Do While (tStatus = DBX_OK)
    
    'Make sure its a Normal type comp.  If it's not goto the next comp.
    
    If (mycomp.connectionType <> 0) Then
        GoTo NextComp
    End If
        
    
    'Get first comp pin
    
    tStatus = TGetFirstCompPin(tContext, mycomp.refDes, pin)
        
    If (pin.compPin.electype = 10 And pin.netId <> 0) Then
        Debug.Print ; Trim(mycomp.refDes) & Chr(0)
        frmStart.ListCompsNotSelected.AddItem Trim(mycomp.refDes) & Chr(0)
        GoTo NextComp
    End If
    
    Do While (tStatus = DBX_OK)
    
    'Get next comp pin

    tStatus = TGetNextCompPin(tContext, pin)
        
    If (tStatus <> DBX_OK) Then
        GoTo NextComp
    End If
        
    If (pin.compPin.electype = 10 And pin.netId <> 0) Then
         frmStart.ListCompsNotSelected.AddItem Trim(mycomp.refDes) & Chr(0)
         GoTo NextComp
    End If
 
    Loop    'End of GetFirst/NextCompPin Loop.
 
NextComp:
 
 
    ' Get next component

    tStatus = TGetNextComponent(tContext, mycomp)
        
    If (tStatus <> DBX_OK) Then
        GoTo error_out2
    End If
    
Loop  'End of GetFirst/NextComp loop.
    

error_out2:


'All the comp refDes's were added to the "sorted" NotSelected list.
'Now add them to the unsorted Selected list in their sorted state.

For j = 0 To (frmStart.ListCompsNotSelected.ListCount - 1) Step 1

    frmStart.ListCompsSelected.AddItem frmStart.ListCompsNotSelected.List(0)
    frmStart.ListCompsNotSelected.RemoveItem 0

Next




End Sub

Public Sub Is_Attr_In_List()


currentAttrName$ = Strip_Nulls(attr.name)
Debug.Print "CurrentAttrName: "; currentAttrName$

attrSlotNumber = 0

Do While (attrSlotNumber <> frmStart.ListAttrsSelected.ListCount)

    slotAttrName$ = Strip_Nulls(frmStart.ListAttrsSelected.List(attrSlotNumber))
    
    
    ' Check attrs.
    
    If (Strip_Nulls(currentAttrName$) = Strip_Nulls(slotAttrName$)) Then
    
        'Set currentX to the position of the attr in the table.
    
        x = (attrSlotNumber * xSpacing) + firstx
        
        text.text = Trim(attr.value) & Chr(0)
                
        Call Place_text
        
        If (errorFlag = 1) Then
            GoTo DBXError
        End If

    End If
    
    
    'Need to check for pattern.  It's not an attr, it's a comp item.
    
    saveAttrName$ = "Pattern"
    If (Strip_Nulls(slotAttrName$) = Strip_Nulls(saveAttrName$) And patternPlaced <> 1) Then
                
        'Set currentX to the position of the attr in the table.
    
        x = (attrSlotNumber * xSpacing) + firstx
                
        tStatus = TGetCompByRefDes(tContext, refDes, component)
        text.text = Trim(component.patternName) & Chr(0)
                
        patternPlaced = 1
        
        Call Place_text
        
        If (errorFlag = 1) Then
            GoTo DBXError
        End If
                
    End If

attrSlotNumber = attrSlotNumber + 1

Loop

DBXError:


End Sub



Public Sub Place_Selected_Text()

    
    'Place the Selected Attrs in the table
    
    SlotNumber = 0
    
    Do While (SlotNumber <> frmStart.ListAttrsSelected.ListCount)
        
        text.text = Trim(frmStart.ListAttrsSelected.List(SlotNumber)) & Chr(0)
        text.refPoint.x = firstx + xSpacing * SlotNumber
        text.refPoint.y = firsty + ySpacing
        text.layerId = layerId
        text.TextStyleId = TextStyleId
        text.justPoint = 5
                
        tstatus2 = TPlaceText(tContext, text)
        'Debug.Print "PlaceText: "; tstatus2
        
        If (tstatus2 <> DBX_OK) Then
            frmStart.lblStatus.Caption = "Error Placing Text: " & Return_error_message(tstatus2)
            frmStart.lblStatus.Visible = True
            errorFlag = 1
            GoTo DBXError
        End If
        
        SlotNumber = SlotNumber + 1
        
    Loop
    
    
    'Place the Selected nets in the table
    
    SlotNumber = 0
    
    Do While (SlotNumber <> frmStart.listNetsSelected.ListCount)
        
        text.text = Trim(frmStart.listNetsSelected.List(SlotNumber)) & Chr(0)
        text.refPoint.x = firstx + (xSpacing * SlotNumber) + (frmStart.ListAttrsSelected.ListCount * xSpacing)
        text.refPoint.y = firsty + ySpacing
        text.layerId = layerId
        text.TextStyleId = TextStyleId
        text.justPoint = 5
                
        tstatus2 = TPlaceText(tContext, text)
        'Debug.Print "PlaceText: "; tstatus2
        
        If (tstatus2 <> DBX_OK) Then
            frmStart.lblStatus.Caption = "Error Placing Text: " & Return_error_message(tstatus2)
            frmStart.lblStatus.Visible = True
            errorFlag = 1
            GoTo DBXError
        End If
        
        SlotNumber = SlotNumber + 1
        
    Loop
    

DBXError:

End Sub

Public Sub Get_Comps_Hidden_Pins()

' Get first component

tStatus = TGetFirstComponent(tContext, mycomp)
'Debug.Print ; "First Comp = "; mycomp.refDes

If (tStatus <> DBX_OK) Then
    frmStart.lblStatus.Caption = "Component error: " & Return_error_message(tStatus)
    errorFlag = 1
    GoTo error_out2
End If
    
    
Do While (tStatus = DBX_OK)
    
    'Make sure its a Normal type comp.  If it's not goto the next comp.
    
    If (mycomp.connectionType <> 0) Then
        GoTo NextComp
    End If
        
    
    'Get first comp pin
    
    tStatus = TGetFirstCompPin(tContext, mycomp.refDes, pin)
        
    
    'Test for Hidden Pins
    
    If (pin.compPin.electype = 10 And pin.compPin.gateNumber = 0 And pin.netId <> 0) Then
        Debug.Print ; Trim(mycomp.refDes) & Chr(0)
        frmStart.ListCompsNotSelected.AddItem Trim(mycomp.refDes) & Chr(0)
        GoTo NextComp
    End If
    
    Do While (tStatus = DBX_OK)
    
    'Get next comp pin

    tStatus = TGetNextCompPin(tContext, pin)
        
    If (tStatus <> DBX_OK) Then
        GoTo NextComp
    End If
        
    If (pin.compPin.electype = 10 And pin.compPin.gateNumber = 0 And pin.netId <> 0) Then
         frmStart.ListCompsNotSelected.AddItem Trim(mycomp.refDes) & Chr(0)
         GoTo NextComp
    End If
 
    Loop    'End of GetFirst/NextCompPin Loop.
 
NextComp:
 
 
    ' Get next component

    tStatus = TGetNextComponent(tContext, mycomp)
        
    If (tStatus <> DBX_OK) Then
        GoTo DoneGettingComps
    End If
    
Loop  'End of GetFirst/NextComp loop.
    

DoneGettingComps:


'All the comp refDes's were added to the "sorted" NotSelected list.
'Now add them to the unsorted Selected list in their sorted state.

For j = 0 To (frmStart.ListCompsNotSelected.ListCount - 1) Step 1

    frmStart.ListCompsSelected.AddItem frmStart.ListCompsNotSelected.List(0)
    frmStart.ListCompsNotSelected.RemoveItem 0

Next

error_out2:
End Sub

Public Sub Only_Place_Hidden_Pins()


If (pin.compPin.electype = 10 And pin.compPin.gateNumber = 0 And pin.netId <> 0) Then
        tstatus2 = TGetNetById(tContext, netId, net)
                               
    'Store pins in nodes array for later grouping of same net pindeses.
    
    pincount = 1
    Nodes(pincount).mypinDes = Strip_Nulls(pin.compPin.pinDes) & Chr(0)
    Nodes(pincount).netId = Trim(pin.netId) & Chr(0)
    netId = Trim(pin.netId) & Chr(0)
        
End If
    
    Do While (tStatus = DBX_OK)
    
    
    'Get next CompPin

        tStatus = TGetNextCompPin(tContext, pin)
        
        If (tStatus <> DBX_OK) Then
            GoTo NoMorePins
        End If
        
            
        If (pin.compPin.electype = 10 And pin.compPin.gateNumber = 0 And pin.netId <> 0) Then
                
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



End Sub

Public Sub Error_Checking()

'Check that all user settings are within legal ranges.

frmStart.lblStatus.Caption = ""
frmStart.lblStatus.Visible = False

If (xSpacing = 0 Or ySpacing = 0) Then
    errorFlag = 1
    frmStart.lblStatus.Caption = "Illegal Column or Row Spacing."
    frmStart.lblStatus.Visible = True
End If


If (originx = 0 Or originx > mil_to_db(59999) Or originy = 0 Or originy > mil_to_db(59999)) Then
    errorFlag = 1
    frmStart.lblStatus.Caption = "Illegal origin."
    frmStart.lblStatus.Visible = True
End If


End Sub
