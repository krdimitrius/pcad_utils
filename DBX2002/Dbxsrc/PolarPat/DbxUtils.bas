'////////////////////////////////////////////////////////////////////////////
'/
'/    name:     dbxutils.bas
'/
'/    abstract: This Visual Basic .BAS module contains functions whose
'/              primarily uses are to convert between unit and data types.
'/
'/    author:   John Bell / Steve Smith
'/
'/    $Header:   F:\tangopro\cmn\dbxutils.bav   34.0   14 Mar 1996 08:51:08   AndyG  $
'/
'/
'/                           PROPRIETARY MATERIALS
'/
'/     ACCEL Technologies, Inc. (ATI) has prepared this material for use
'/     by ATI personnel, licensees, and customers.  The information con-
'/     tained herein  is the property of ATI and shall not be reproduced
'/     in whole or part without ATI prior written approval.
'/
'/
'/                          RESTRICTED RIGHTS LEGEND
'/
'/     U.S. Government  use,  duplication,  or disclosure  is subject to
'/     RESTRICTED RIGHTS under  applicable  government  regulations per-
'/     taining to trade secret,  commercial  computer software developed
'/     at private expense, including  FAR 227-14 subparagraph (g)(3)(i),
'/     Alternative III and DFAR 252.227-7013 subparagraph (c)(1)(ii).
'/
'/     All rights reserved,  including those under  U.S. Copyright Laws.
'/     This is confidential, unpublished property of ACCEL Technologies,
'/     Inc.  Use is subject to a written license agreement.
'/
'/                          Copyright (c) 1991-1993
'/                          ACCEL Technologies, Inc.
'/                            6825 Flanders Drive
'/                            San Diego, CA 92121
'/                               (619) 554-1000
'/
'/////////////////////////////////////////////////////////////////////////////

Function Db_Convert (userUnit As Single) As Long
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of db units, mm, or mils as type string and returns the
'   equivilent value in database units as type long,
'   depending on the value of the global variable Unit.
'
'

    Dim flag As Integer

    Select Case Unit

        Case DBX_UNIT_DB
            Db_Convert = userUnit
            flag = 1

        Case DBX_UNIT_MIL
            Db_Convert = mil_to_db(userUnit)
            flag = 1

        Case DBX_UNIT_MM
            Db_Convert = mm_To_DB(userUnit)
            flag = 1
    
    End Select

    If (flag <> 1) Then
        Db_Convert = userUnit
    End If

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of dbunits as type long and returns the
'   equivilent value in mil's as type single.
'
'
Function DB_To_Mil (dbunit As Long) As Single

  DB_To_Mil = (dbunit / 2540.0)

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of dbunits as type long and returns the
'   equivilent value in mil's as type string.
'
'
Function DB_To_Mil_Str (dbunit As Long) As String

  Dim mil As Single

  mil = (dbunit / 2540.0)
  DB_To_Mil_Str = Format(mil, "fixed")

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of dbunits as type long and returns the
'   equivilent value in mm's as type single.
'
'
Function DB_To_mm (dbunit As Long) As Single

  DB_To_mm = (dbunit / 100000.0)

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of dbunits as type long and returns the
'   equivilent value in mm's as type string.
'
'
Function DB_To_mm_Str (dbunit As Long) As String

  Dim mm As Single
  
  mm = (dbunit / 100000.0)
  DB_To_mm_Str = Format(mm, "fixed")
  
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'  Get the origin point for an input TItem
'
'
Function GetOriginPoint (item As TItem, originPoint As TCoord) As Long
      tstatus = DBX_OK
      Select Case item.itemtype

        Case DBX_ARC
            originPoint = item.arc.centerPt
        Case DBX_ATTR
            originPoint = item.attribute.refPoint
        Case DBX_COMPONENT
            originPoint = item.component.refPoint
        Case DBX_LINE
            originPoint = item.aline.startPt
        Case DBX_PAD
            originPoint = item.pad.center
        Case DBX_GLUEPOINT
            originPoint.x = item.apoint.x
            originPoint.y = item.apoint.y
        Case DBX_REFPOINT
            originPoint.x = item.apoint.x
            originPoint.y = item.apoint.y
        Case DBX_PICKPOINT
            originPoint.x = item.apoint.x
            originPoint.y = item.apoint.y
        Case DBX_INFOPOINT
            originPoint.x = item.apoint.x
            originPoint.y = item.apoint.y
        Case DBX_TEXT
            originPoint = item.text.refPoint
        Case DBX_VIA
            originPoint = item.via.center
        Case default
            tstatus = DBX_ILLEGAL_ITEM
      End Select
      GetOriginPoint = tstatus


End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of mm's as type string and returns the
'   equivilent value in dbunits as type long.
'
'
Function mil_Str_To_DB (mil As String) As Long

  mil_Str_To_DB = (Val(mil) * 2540.0)

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of mm's as type single and returns the
'   equivilent value in dbunits as type long.
'
'
Function mil_to_db (mil As Single) As Long

  mil_to_db = (mil * 2540.0)

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of mm's as type string and returns the
'   equivilent value in dbunits as type long.
'
'
Function mm_Str_To_DB (mm As String) As Long

  mm_Str_To_DB = (Val(mm) * 100000.0)

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of mm's as type single and returns the
'   equivilent value in dbunits as type long.
'
'
Function mm_To_DB (mm As Single) As Long

  mm_To_DB = (mm * 100000.0)

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input as the status returned by the TGet()
'   functions and returns the appropriate status message as type string.
'
'
Function Return_error_message (value As Long) As String

    Dim status As Integer
    Dim flag As Integer
    flag = 0

    status = value
    Select Case status

        Case DBX_CONNECTION_ERROR
            Return_error_message = "Connection Error"
            flag = 1
        
        Case DBX_DISCONNECT_ERROR
            Return_error_message = "Disconnect Error"
            flag = 1

        Case DBX_BAD_SERVER_DATA
            Return_error_message = "Bad Server Data"
            flag = 1
        
        Case DBX_SERVER_ERROR
            Return_error_message = "Server Error"
            flag = 1
        
        Case DBX_FATAL_ERROR
            Return_error_message = "Fatal DBX Error"
            flag = 1

        Case DBX_VERSION_INCOMPATIBLE
            Return_error_message = "Version Incompatible"
            flag = 1

        Case DBX_CLIENT_ERROR
            Return_error_message = "Client Error"
            flag = 1

        Case DBX_SECURITY_ERROR
            Return_error_message = "Security Error"
            flag = 1

        Case DBX_FLIP_ERROR
            Return_error_message = "Flip Error"
            flag = 1

        Case DBX_ROTATE_ERROR
            Return_error_message = "Rotate Error"
            flag = 1

        Case DBX_MOVE_ERROR
            Return_error_message = "Move Error"
            flag = 1

        Case DBX_HIGHLIGHT_ERROR
            Return_error_message = "Highlight Error"
            flag = 1

        Case DBX_DELETE_ERROR
            Return_error_message = "Delete Error"
            flag = 1

        Case DBX_MODIFY_ERROR
            Return_error_message = "Modify Error"
            flag = 1

        Case DBX_CREATE_ERROR
            Return_error_message = "Create Error"
            flag = 1

        Case DBX_DATABASE_ERROR
            Return_error_message = "Database Error"
            flag = 1

        Case DBX_OK
            Return_error_message = "Status: OK"
            flag = 1
        
        Case DBX_INVALID_CONV_HANDLE
            Return_error_message = "Invalid Conv Handle"
            flag = 1

        Case DBX_SERVER_TERMINATED
            Return_error_message = "Server Terminated"
            flag = 1

        Case DBX_LOW_MEMORY
            Return_error_message = "Low Memory"
            flag = 1

        Case DBX_ALREADY_CONNECTED
            Return_error_message = "Already Connected"
            flag = 1

        Case DBX_NO_CONNECTION
            Return_error_message = "No Connection"
            flag = 1

        Case DBX_SERVER_BUSY
            Return_error_message = "Server Busy"
            flag = 1

        Case DBX_ILLEGAL_OP
            Return_error_message = "Illegal Operation"
            flag = 1

        Case DBX_BAD_INPUT
            Return_error_message = "Bad Input"
            flag = 1

        Case DBX_ARRAY_TOO_SMALL
            Return_error_message = "Array Too Small"
            flag = 1

        Case DBX_INVALID_ITEM_ID
            Return_error_message = "Invalid Item ID"
            flag = 1

        Case DBX_ITEM_NOT_FOUND
            Return_error_message = "Item Not Found"
            flag = 1

        Case DBX_ITEM_NOT_SUPPORTED
            Return_error_message = "Item Not Supported"
            flag = 1

        Case DBX_ILLEGAL_ITEM
            Return_error_message = "Illegal Item"
            flag = 1

        Case DBX_SHAPE_NOT_DEFINED
            Return_error_message = "Shape Not Defined"
            flag = 1

        Case DBX_GETFIRST_NOT_CALLED
            Return_error_message = "GetFirst Not Called"
            flag = 1

        Case DBX_GETCOMP_NOT_CALLED
            Return_error_message = "GetComp Not Called"
            flag = 1

        Case DBX_GETNET_NOT_CALLED
            Return_error_message = "GetNet Not Called"
            flag = 1

        Case DBX_NO_MORE_LAYERS
            Return_error_message = "No More Layers"
            flag = 1

        Case DBX_NO_MORE_NETS
            Return_error_message = "No More Nets"
            flag = 1

        Case DBX_NO_MORE_ITEMS
            Return_error_message = "No More Items"
            flag = 1

        Case DBX_NO_MORE_NETCLASSES
            Return_error_message = "No More Net Classes"
            flag = 1
            
        Case DBX_NO_MORE_CLASSTOCLASSES
            Return_error_message = "No More Class To Class Rules"
            flag = 1
            
        Case DBX_NO_MORE_ROOMS
            Return_error_message = "No More Rooms"
            flag = 1

        Case DBX_NO_MORE_ROOMPOINTS      
            Return_error_message = "No More Room Points"
            flag = 1

        Case DBX_NO_MORE_COMPONENTS
            Return_error_message = "No More Components"
            flag = 1
            
        Case DBX_INVALID_ANGLE
            Return_error_message = "Invalid Angle"
            flag = 1

        Case DBX_INVALID_HIGHLIGHT_COLOR
            Return_error_message = "Invalid Highlight Color"
            flag = 1

        Case DBX_INVALID_ITEM_TYPE
            Return_error_message = "Invalid Item Type"
            flag = 1

        Case DBX_INVALID_JUSTIFICATION
            Return_error_message = "Invalid Justification"
            flag = 1

        Case DBX_INVALID_LAYER
            Return_error_message = "Invalid Layer"
            flag = 1

        Case DBX_INVALID_LOCATION
            Return_error_message = "Invalid Location"
            flag = 1

        Case DBX_INVALID_NET_ID
            Return_error_message = "Invalid Net Id"
            flag = 1
            
        Case DBX_INVALID_NETNAME
            Return_error_message = "Invalid Netname"
            flag = 1

        Case DBX_INVALID_PADSTYLE
            Return_error_message = "Invalid Padstyle"
            flag = 1

        Case DBX_INVALID_PIN_NUMBER
            Return_error_message = "Invalid Pin Number"
            flag = 1

        Case DBX_INVALID_RADIUS
            Return_error_message = "Invalid Radius"
            flag = 1

        Case DBX_INVALID_REFDES
            Return_error_message = "Invalid Refdes"
            flag = 1

        Case DBX_INVALID_ROTATION_ANGLE
            Return_error_message = "Invalid Rotation Angle"
            flag = 1

        Case DBX_INVALID_TEXTSTYLE
            Return_error_message = "Invalid TextStyle"
            flag = 1

        Case DBX_INVALID_WIDTH
            Return_error_message = "Invalid Width"
            flag = 1

        Case DBX_INVALID_LAYERNAME
            Return_error_message = "Invalid Layer Name"
            flag = 1
            
        Case DBX_INVALID_COMPNAME
            Return_error_message = "Invalid Component Name"
            flag = 1

        Case DBX_NOT_SAME_NUM_PARTS
            Return_error_message = "Mismatched Part Numbers"
            flag = 1
            
        Case DBX_NOT_SAME_NUM_PINS
            Return_error_messge = "Mismatched Pin Numbers"
            flag = 1
            
        Case DBX_NOT_SAME_COMP_TYPE
            Return_error_message = "Mismatched Component Type"
            flag = 1
            
        Case DBX_NOT_SAME_HETERO
            Return_error_message = "Mismatched Hetero"
            flag = 1

        Case DBX_INVALID_LINESTYLE
            Return_error_message = "Invalid Line Style"
            flag = 1

        Case DBX_INVALID_PINLENGTH
            Return_error_message = "Invalid Pin Length"
            flag = 1

        Case DBX_INVALID_PINSTYLE
            Return_error_message = "Invalid Pin Style"
              flag = 1
            
        Case DBX_INVALID_ALTTYPE
            Return_error_message = "Invalid Alt Type"
            flag = 1

        Case DBX_INVALID_NETCLASSNAME
            Return_error_message = "Invalid Net Class Name"
            flag = 1
             
        Case DBX_INVALID_CLASSTOCLASSID
            Return_error_message = "Invalid Class To Class Id"
            flag = 1
            
        Case DBX_INVALID_NETCLASS_ID
            Return_error_message =  "Invalid Net Class Id"
            flag = 1
            
        Case DBX_INVALID_LAYER_ID
            Return_error_message = "Invalid Layer Id"
            flag = 1
            
        Case DBX_INVALID_ROOM_NAME
            Return_error_message = "Invalid Room Name"
            flag = 1

        Case DBX_INVALID_ATTRIBUTE_VALUE
            Return_error_message = "Invalid Attribute Value"
            flag = 1
            
        Case DBX_INVALID_ATTRIBUTE_NAME
            Return_error_message = "Invalid Attribute Name"
            flag = 1
        
        Case DBX_DUPLICATE_ATTRIBUTE
            Return_error_message = "Duplicate Attribute"
            flag = 1

        Case DBX_DUPLICATE_NETNAME
            Return_error_message = "Duplicate Netname"
            flag = 1

        Case DBX_DUPLICATE_NETCLASSNAME
            Return_error_message = "Duplicate Net Class Name"
            flag = 1
            
        Case DBX_DUPLICATE_CLASSTOCLASSNAME
            Return_error_message = "Duplicate Class To Class Name"
            flag = 1
            
        Case DBX_DUPLICATE_REFDES
            Return_error_message = "Duplicate Refdes"
            flag = 1

        Case DBX_COMPONENT_NOT_FOUND
            Return_error_message = "Component Not Found"
            flag = 1

        Case DBX_LAYER_NOT_FOUND
            Return_error_message = "Layer Not Found"
            flag = 1

        Case DBX_NET_NOT_FOUND
            Return_error_message = "Net Not Found"
            flag = 1

        Case DBX_NET_NOT_EMPTY
            Return_error_message = "Net Not Empty"
            flag = 1

        Case DBX_NET_EXISTS
            Return_error_message = "Net Exists"
            flag = 1

        Case DBX_NET_CONFLICT
            Return_error_message = "Net Conflict"
            flag = 1

        Case DBX_NETCLASS_NOT_FOUND
            Return_error_message = "Net Class Not Found"
            flag = 1
            
        Case DBX_NETCLASS_NOT_EMPTY 
            Return_error_message = "Net Class Not Empty"
            flag = 1
            
        Case DBX_NETCLASS_EXISTS
            Return_error_message = "Net Class Exists"
            flag = 1
            
        Case DBX_CLASSTOCLASS_NOT_FOUND
            Return_error_message = "Class To Class Not Found"
            flag = 1
            
        Case DBX_ROOM_NOT_FOUND
            Return_error_message = "Room Not Found"
            flag = 1

        Case DBX_POINT_NOT_FOUND            
            Return_error_message = "Point Not Found"
            flag = 1
            
        Case DBX_COMP_CACHE_CONFLICT
            Return_error_message = "Component Cache Conflict"
            flag = 1

        Case DBX_LIBRARY_NOT_OPEN
            Return_error_message = "Library Not Open"
            flag = 1

        Case DBX_ITEM_OUTSIDE_WORKSPACE
            Return_error_message = "Item Outside Workspace"
            flag = 1

        Case DBX_NO_ATTACHED_PATTERN
            Return_error_message = "No Attached Pattern"
            flag = 1

        Case DBX_TOO_FEW_PINS
            Return_error_message = "Too Few Pins"
            flag = 1

        Case DBX_PINDES_NOT_FOUND
            Return_error_message = "Pindes Not Found"
            flag = 1

        Case DBX_NAME_TOO_LONG
            Return_error_message = "Name Too Long"
            flag = 1 

        Case DBX_PRINT_JOB_NOT_FOUND
            Return_error_message = "Print Job Not Found"
            flag = 1 

        Case DBX_NO_PRINT_JOBS_SELECTED
            Return_error_message = "No Print Jobs Selected"
            flag = 1 

        Case DBX_FILE_OPEN_FAILURE
            Return_error_message = "Unable to open file"
            flag = 1 

        Case DBX_INVALID_LIBRARY_NAME
            Return_error_message = "Invalid Library Name"
            flag = 1

        Case DBX_LIBRARY_CANT_OPEN
            Return_error_message = "Unable to open Library"
            flag = 1

        Case DBX_COMP_ALREADY_OPEN
            Return_error_message = "Component Already Open"
            flag = 1

        Case DBX_OPENCOMP_NOT_CALLED
            Return_error_message = "Open Component Not Called"
            flag = 1

        Case DBX_SAVECOMP_FAILED
            Return_error_message = "Save Component Failed"
            flag = 1

        Case DBX_LIBRARY_READ_ONLY
            Return_error_message = "Library is READ Only"
            flag = 1

        Case DBX_SAVESYMBOL_FAILED
            Return_error_message = "Save Symbol Failed"
            flag = 1 

        Case DBX_SAVEPATTERN_FAILED
            Return_error_message = "Save Pattern Failed"
            flag = 1 
        
        Case DBX_INTERNAL_PARAMETER_ERROR
            Return_error_message = "Internal Parameter Error"
            flag = 1

    End Select
  
    If flag <> 1 Then
        Return_error_message = "Status: " & Format$(status)
    End If

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of a string padded with nulls and
'   returns a string trimmed of nulls as well as leading and trailing
'   spaces.
'
'
Function Strip_Nulls (strExpression As String) As String

    Dim position As Integer

    position = InStr(1, strExpression, Chr$(0))
    
    If (position = 0) Then
        Strip_Nulls = Trim(strExpression)
    Else
        Strip_Nulls = Trim(Left$(strExpression, position - 1))
    End If

End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'
'   This function accepts an input of dbunits as type long and returns the
'   equivilent value in either dbunits, mil's or mm's as type string,
'   depending on the value of the global variable Unit.
'
'
Function Unit_Convert (dbunit As Long) As Variant

    Dim flag As Integer

    Select Case Unit

        Case DBX_UNIT_DB
            Unit_Convert = Format(dbunit, "general number")
            flag = 1

        Case DBX_UNIT_MIL
            Unit_Convert = DB_To_Mil_Str(dbunit)
            flag = 1

        Case DBX_UNIT_MM
            Unit_Convert = DB_To_mm_Str(dbunit)
            flag = 1
    
    End Select

    If (flag <> 1) Then
        Unit_Convert = Format(dbunit, "general number")
    End If

End Function

