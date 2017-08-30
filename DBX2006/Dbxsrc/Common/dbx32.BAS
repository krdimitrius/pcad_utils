Attribute VB_Name = "DBX32"
'////////////////////////////////////////////////////////////////////////////
'/
'/    name:     dbx32.bas
'/
'/    abstract: This Visual Basic .BAS module contains the DBX function
'/              declarations and data structure declarations needed to
'/              request and receive data from ACCEL EDA PCB.
'/
'/              This version must be used to develop 32-bit Visual Basic DBX
'/              applications.  For 16-bit applications, use ACCELDBX.BAS
'/
'/    author:   John Bell / Steve Smith
'/
'/    $Header: $
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

                           
' Boolean Constants

Global Const DBX_FALSE = 0
Global Const DBX_TRUE  = 1

' String Lengths

Global Const DBX_MAX_NAME_LEN = 100
Global Const DBX_MAX_TYPE_LEN = 100
Global Const DBX_MAX_VALUE_LEN = 100
Global Const DBX_MAX_TEXTITEM_LEN = 256
Global Const DBX_MAX_ATTRIBUTE_LEN = 256
Global Const DBX_MAX_FILENAME_LEN = 256
Global Const DBX_MAX_GRIDSPACING_LEN = 256
Global Const DBX_MAX_FORMULA_LEN = 512

Global Const DBX_NUM_LAYER_VALS_TO_SET = 6

' Fatal Errors

Global Const DBX_CONNECTION_ERROR = 32001
Global Const DBX_DISCONNECT_ERROR = 32002
Global Const DBX_BAD_SERVER_DATA = 32003
Global Const DBX_SERVER_ERROR = 32004
Global Const DBX_FATAL_ERROR = 32005
Global Const DBX_VERSION_INCOMPATIBLE = 32006
Global Const DBX_CLIENT_ERROR = 32007
Global Const DBX_SECURITY_ERROR = 32008

Global Const DBX_FLIP_ERROR = 32009             ' 32009-32016 new for V12.0
Global Const DBX_ROTATE_ERROR = 32010
Global Const DBX_MOVE_ERROR = 32011
Global Const DBX_HIGHLIGHT_ERROR = 32012
Global Const DBX_DELETE_ERROR = 32013
Global Const DBX_MODIFY_ERROR = 32014
Global Const DBX_CREATE_ERROR = 32015
Global Const DBX_DATABASE_ERROR = 32016

' Status Return Values

Global Const DBX_OK = 0

Global Const DBX_INVALID_CONV_HANDLE = 32101
Global Const DBX_SERVER_TERMINATED = 32102
Global Const DBX_LOW_MEMORY = 32103
Global Const DBX_ALREADY_CONNECTED = 32104
Global Const DBX_NO_CONNECTION = 32105
Global Const DBX_SERVER_BUSY = 32106

Global Const DBX_ILLEGAL_OP = 32121
Global Const DBX_BAD_INPUT = 32122
Global Const DBX_ARRAY_TOO_SMALL = 32123
Global Const DBX_INVALID_ITEM_ID = 32124

Global Const DBX_ITEM_NOT_FOUND = 32141
Global Const DBX_ITEM_NOT_SUPPORTED = 32142
Global Const DBX_ILLEGAL_ITEM = 32143
Global Const DBX_SHAPE_NOT_DEFINED = 32144
Global Const DBX_GETFIRST_NOT_CALLED = 32145
Global Const DBX_GETCOMP_NOT_CALLED  = 32146
Global Const DBX_GETNET_NOT_CALLED   = 32147

Global Const DBX_NO_MORE_LAYERS = 32161
Global Const DBX_NO_MORE_NETS = 32162
Global Const DBX_NO_MORE_ITEMS = 32163
Global Const DBX_NO_MORE_NETCLASSES = 32164   
Global Const DBX_NO_MORE_CLASSTOCLASSES = 32165   
Global Const DBX_NO_MORE_ROOMS = 32166  
Global Const DBX_NO_MORE_ROOMPOINTS = 32167  
Global Const DBX_NO_MORE_COMPONENTS = 32168  

Global Const DBX_INVALID_ANGLE = 32170           ' New for V12.0
Global Const DBX_INVALID_HIGHLIGHT_COLOR = 32171
Global Const DBX_INVALID_ITEM_TYPE = 32172
Global Const DBX_INVALID_JUSTIFICATION = 32173
Global Const DBX_INVALID_LAYER = 32174
Global Const DBX_INVALID_LOCATION = 32175
Global Const DBX_INVALID_NET_ID = 32176
Global Const DBX_INVALID_NETNAME = 32177
Global Const DBX_INVALID_PADSTYLE = 32178
Global Const DBX_INVALID_PIN_NUMBER = 32279
Global Const DBX_INVALID_RADIUS = 32180
Global Const DBX_INVALID_REFDES = 32181
Global Const DBX_INVALID_ROTATION_ANGLE = 32182
Global Const DBX_INVALID_TEXTSTYLE = 32183
Global Const DBX_INVALID_WIDTH = 32184
Global Const DBX_INVALID_LAYERNAME = 32185
Global Const DBX_INVALID_COMPNAME = 32186
Global Const DBX_NOT_SAME_NUM_PARTS = 32187
Global Const DBX_NOT_SAME_NUM_PINS = 32188
Global Const DBX_NOT_SAME_COMP_TYPE = 32189
Global Const DBX_NOT_SAME_HETERO = 32190
Global Const DBX_INVALID_LINESTYLE = 32191
Global Const DBX_INVALID_PINLENGTH = 32192
Global Const DBX_INVALID_PINSTYLE = 32193
Global Const DBX_INVALID_ALTTYPE = 32194
Global Const DBX_INVALID_NETCLASSNAME = 32195
Global Const DBX_INVALID_CLASSTOCLASSID = 32196
Global Const DBX_INVALID_NETCLASS_ID = 32197
Global Const DBX_INVALID_LAYER_ID = 32198  
Global Const DBX_INVALID_ROOM_NAME = 32199 
Global Const DBX_INVALID_ATTRIBUTE_VALUE = 32200
Global Const DBX_INVALID_ATTRIBUTE_NAME = 32201 
Global Const DBX_INVALID_LAYER_BIAS = 32202
Global Const DBX_INVALID_VARIANT_NAME = 32203

Global Const DBX_DUPLICATE_ATTRIBUTE = 32205
Global Const DBX_DUPLICATE_NETNAME = 32206
Global Const DBX_DUPLICATE_NETCLASSNAME = 32207
Global Const DBX_DUPLICATE_CLASSTOCLASSNAME = 32208  
Global Const DBX_DUPLICATE_REFDES = 32209

Global Const DBX_COMPONENT_NOT_FOUND = 32215
Global Const DBX_LAYER_NOT_FOUND = 32216
Global Const DBX_NET_NOT_FOUND = 32217
Global Const DBX_NET_NOT_EMPTY = 32218
Global Const DBX_NET_EXISTS = 32219
Global Const DBX_NET_CONFLICT = 32220
Global Const DBX_NETCLASS_NOT_FOUND =     32221  
Global Const DBX_NETCLASS_NOT_EMPTY =     32222
Global Const DBX_NETCLASS_EXISTS    =     32223
Global Const DBX_CLASSTOCLASS_NOT_FOUND = 32224
Global Const DBX_ROOM_NOT_FOUND         = 32225
Global Const DBX_POINT_NOT_FOUND        = 32226
Global Const DBX_LAYER_EXISTS           = 32227


Global Const DBX_COMP_CACHE_CONFLICT = 32230
Global Const DBX_LIBRARY_NOT_OPEN = 32231
Global Const DBX_ITEM_OUTSIDE_WORKSPACE = 32232
Global Const DBX_NO_ATTACHED_PATTERN = 32233
Global Const DBX_TOO_FEW_PINS = 32234
Global Const DBX_PINDES_NOT_FOUND = 32235
Global Const DBX_NAME_TOO_LONG = 32236

Global Const DBX_PRINT_JOB_NOT_FOUND = 32237
Global Const DBX_NO_PRINT_JOBS_SELECTED = 32238
Global Const DBX_FILE_OPEN_FAILURE = 32239

' For Library Manager

Global Const DBX_INVALID_LIBRARY_NAME = 32250
Global Const DBX_LIBRARY_CANT_OPEN = 32251
Global Const DBX_COMP_ALREADY_OPEN = 32252
Global Const DBX_OPENCOMP_NOT_CALLED = 32253
Global Const DBX_SAVECOMP_FAILED = 32254
Global Const DBX_LIBRARY_READ_ONLY = 32255
Global Const DBX_SAVESYMBOL_FAILED = 32256
Global Const DBX_SAVEPATTERN_FAILED = 32257

' Internal Paramater Error (missing parameter, wrong size parameter)
Global Const DBX_INTERNAL_PARAMETER_ERROR = 32258


' Interface Description

Global Const DBX_VERSION = 18000
Global Const DBX_LANGUAGE = 0


' Item Type Definitions

Global Const DBX_PAD = 3            ' Component or Free Pad
Global Const DBX_VIA = 4            ' Via
Global Const DBX_LINE = 5           ' Line, Routed Connection or Mitered Line


Global Const DBX_FROM_TO = 6        ' Unrouted Net Connection
Global Const DBX_ARC = 7            ' Arc, Orthogonal 90/90 Arc, 90 Arc Miter


Global Const DBX_POLYGON = 8        ' Solid Filled Polygon
Global Const DBX_COMPONENT = 9      ' Component Shape
Global Const DBX_COPPERPOUR = 11    ' Copper Pour Polygon

Global Const DBX_TEXT = 13          ' Text
Global Const DBX_ATTR = 14          ' Attribute
Global Const DBX_FIELD = 15         ' Field
Global Const DBX_REFPOINT = 16      ' Point Type: Ref Point
Global Const DBX_GLUEPOINT = 17     ' Point Type: Glue Dot
Global Const DBX_PICKPOINT = 18     ' Point Type: Pick and Place
Global Const DBX_PATTERN = 19       ' Pattern
Global Const DBX_LINE_KEEPOUT = 20  ' Keepout Type: Line
Global Const DBX_POLY_KEEPOUT = 21  ' Keepout Type: Polygon

Global Const DBX_PAD_STYLE = 24     ' Description of Pad Style
Global Const DBX_VIA_STYLE = 25     ' Description of Via Style
Global Const DBX_TEXT_STYLE = 26    ' Description of Text Style
Global Const DBX_KEEPOUT = 27       '
Global Const DBX_COMP_PIN = 28      '
Global Const DBX_POLY_CUTOUT = 29   ' Cutout Polygon

Global Const DBX_LAYER = 33         ' Layer, sheet

Global Const DBX_SYMBOL = 35        ' Symbol
Global Const DBX_NET = 36           ' Net

Global Const DBX_PIN = 39           ' Pin
Global Const DBX_INFOPOINT = 40     ' Point Type: Info Point

Global Const DBX_WIRE = 44          ' Sch wire item
Global Const DBX_BUS = 45           ' Sch bus item

Global Const DBX_PORT = 50          ' Sch Net Port
Global Const DBX_POLY_PLANE = 51    ' Pcb Plane

Global Const DBX_NETCLASS = 54      ' NetClass

Global Const DBX_TABLE = 58             
Global Const DBX_METAFILE = 59         

Global Const DBX_DIAGRAM = 66         
Global Const DBX_DETAIL = 67         
Global Const DBX_CLASSTOCLASS = 68
Global Const DBX_ROOM = 69   
Global Const DBX_GRID = 70   

Global Const DBX_DESIGNVIEW = 74   
Global Const DBX_TESTPOINT  = 75   
Global Const DBX_COMP_GRAPHIC = 76


Global Const DBX_COORDINATE = 901   ' Coordinate Point for Polygon and Pour Outlines
Global Const DBX_PADVIA_SHAPE = 902 ' By Layer Shape Description of Pads and Vias
Global Const DBX_DESIGN_INFO = 903  ' Design Info object
Global Const DBX_PRINT_JOB = 905    ' Print job

' Text Info
' Text Justifications: Returned in TText.justPoin

Global Const DBX_JUSTIFY_TOP = 9          '    UL-----T-----UR  1000 1001 1010
Global Const DBX_JUSTIFY_BOTTOM = 1       '    |      |      |
Global Const DBX_JUSTIFY_LEFT = 4         '    L------C------R  0100 0101 0110
Global Const DBX_JUSTIFY_RIGHT = 6        '    |      |      |
Global Const DBX_JUSTIFY_CENTER = 5       '    LL-----B-----LR  0000 0001 0010
Global Const DBX_JUSTIFY_LOWER_LEFT = 0   '
Global Const DBX_JUSTIFY_LOWER_RIGHT = 2  ' TangoFont defines LL as the ref point.
Global Const DBX_JUSTIFY_UPPER_LEFT = 8   ' The two hi bits indicate how many
Global Const DBX_JUSTIFY_UPPER_RIGHT = 10 ' half-extents to move in the y-direction;

' Font Types:  Returned in TTextStyle.fontType

Global Const DBX_FONT_WINSTROKE = 1
Global Const DBX_FONT_OUTLINE = 2
Global Const DBX_FONT_STROKE = 3
Global Const DBX_FONT_TRUE_TYPE = 4

' Layer Info
                                            
Global Const DBX_LAYERTYPE_UNDEFINED = -1 ' For GetPadShapeByLayer if the layer doesn't exist
Global Const DBX_LAYERTYPE_SIGNAL = 0     ' Layer Type: Signal
Global Const DBX_LAYERTYPE_PLANE = 1      ' Layer Type: Plane
Global Const DBX_LAYERTYPE_NON_SIGNAL = 2 ' Layer Type: Non Signal

' Pre-defined Layers

Global Const DBX_LAYER_MULTI = 0          ' "Multi-Layer", used for comps, pads, etc.
Global Const DBX_LAYER_TOP_SIGNAL = 1
Global Const DBX_LAYER_BOTTOM_SIGNAL = 2
Global Const DBX_LAYER_BOARD = 3
Global Const DBX_LAYER_TOP_MASK = 4
Global Const DBX_LAYER_BOTTOM_MASK = 5
Global Const DBX_LAYER_TOP_SILK = 6
Global Const DBX_LAYER_BOTTOM_SILK = 7
Global Const DBX_LAYER_TOP_PASTE = 8
Global Const DBX_LAYER_BOTTOM_PASTE = 9
Global Const DBX_LAYER_TOP_ASSY = 10
Global Const DBX_LAYER_BOTTOM_ASSY = 11

'  Layer Bias: Returned in TLayer.layerBias

Global Const DBX_LAYERBIAS_AUTO = 0       ' AutoRouter Bias: Automatic
Global Const DBX_LAYERBIAS_HORIZ = 1      ' AutoRouter Bias: Horizontal
Global Const DBX_LAYERBIAS_VERT = 2       ' AutoRouter Bias: Vertical


' Pour Thermals

Global Const DBX_POUR_THERMAL_NONE = 0    ' Pour Thermals: None
Global Const DBX_POUR_THERMAL_45 = 1      ' Pour Thermals: 45 degree
Global Const DBX_POUR_THERMAL_90 = 2      ' Pour Thermals: 90 degree


' Pour Patterns

Global Const DBX_POUR_SOLID = 0           ' Pour Pattern: Solid
Global Const DBX_POUR_HORIZ = 1           ' Pour Pattern: Horizontal
Global Const DBX_POUR_VERT = 2            ' Pour Pattern: Vertical
Global Const DBX_POUR_HATCH45 = 3         ' Pour Pattern: 45 degree Cross
Global Const DBX_POUR_HATCH90 = 4         ' Pour Pattern: 90 degree Cross

' Pad and Via Shapes

Global Const DBX_SHAPE_ELLIPSE = 0        ' Elliptical, Including Circular
Global Const DBX_SHAPE_OVAL = 1           ' Oval
Global Const DBX_SHAPE_RECT = 2           ' "Square" Rectangle
Global Const DBX_SHAPE_RND_RECT = 3       ' "Rounded" Rectangle
Global Const DBX_SHAPE_THRM_2 = 4         ' "Two Spoke" Thermal
Global Const DBX_SHAPE_THRM_2_90 = 5      ' "Two Spoke With 90 Rotation" Thermal

Global Const DBX_SHAPE_THRM_4 = 6         ' "Four Spoke" Thermal
Global Const DBX_SHAPE_THRM_4_45 = 7      ' "Four Spoke With 45 Rotation" Thermal

Global Const DBX_SHAPE_DIRECT = 8         ' Direct Plane Connect
Global Const DBX_SHAPE_TARGET = 9         ' Registration Target (Not Used for Vias)

Global Const DBX_SHAPE_MT_HOLE = 10       ' Mounting Hole (Not Used for Vias)

Global Const DBX_SHAPE_POLYGON = 11       ' Polygonal

Global Const DBX_SHAPE_NOCONNECT = 12     ' Disconnect (plane layers)


' Pin Electrical Types

Global Const DBX_PIN_ETYPE_UNKNOWN = 0    ' Pin Electrical Type: Unknown
Global Const DBX_PIN_ETYPE_PASSIVE = 1    ' Pin Electrical Type: Passive
Global Const DBX_PIN_ETYPE_INPUT = 2      ' Pin Electrical Type: Input
Global Const DBX_PIN_ETYPE_OUTPUT = 3     ' Pin Electrical Type: Output
Global Const DBX_PIN_ETYPE_BIDIRECT = 4   ' Pin Electrical Type: Bidirectional
Global Const DBX_PIN_ETYPE_OPEN_H = 5     ' Pin Electrical Type: Open-H
Global Const DBX_PIN_ETYPE_OPEN_L = 6     ' Pin Electrical Type: Open-L
Global Const DBX_PIN_ETYPE_PASS_H = 7     ' Pin Electrical Type: Passive-H
Global Const DBX_PIN_ETYPE_PASS_L = 8     ' Pin Electrical Type: Passive-L
Global Const DBX_PIN_ETYPE_3STATE = 9     ' Pin Electrical Type: 3-State
Global Const DBX_PIN_ETYPE_POWER = 10     ' Pin Electrical Type: Power

' Port Types: Returned in TPort.portType

Global Const DBX_PORT_NOANGLE_SGL_VERT = 1
Global Const DBX_PORT_NOANGLE_SGL_HORZ = 2
Global Const DBX_PORT_LEFTANGLE_SGL_VERT = 3
Global Const DBX_PORT_LEFTANGLE_SGL_HORZ = 4
Global Const DBX_PORT_RIGHTANGLE_SGL_VERT = 5
Global Const DBX_PORT_RIGHTANGLE_SGL_HORZ = 6
Global Const DBX_PORT_BOTHANGLE_SGL_VERT = 7
Global Const DBX_PORT_BOTHANGLE_SGL_HORZ = 8
Global Const DBX_PORT_NOANGLE_DBL_VERT = 9
Global Const DBX_PORT_NOANGLE_DBL_HORZ = 10
Global Const DBX_PORT_LEFTANGLE_DBL_VERT = 11
Global Const DBX_PORT_LEFTANGLE_DBL_HORZ = 12
Global Const DBX_PORT_RIGHTANGLE_DBL_VERT = 13
Global Const DBX_PORT_RIGHTANGLE_DBL_HORZ = 14
Global Const DBX_PORT_BOTHANGLE_DBL_VERT = 15
Global Const DBX_PORT_BOTHANGLE_DBL_HORZ = 16
Global Const DBX_PORT_VERTLINE_SGL_VERT = 17
Global Const DBX_PORT_VERTLINE_SGL_HORZ = 18
Global Const DBX_PORT_NOOUTLINE_SGL_VERT = 19
Global Const DBX_PORT_NOOUTLINE_SGL_HORZ = 20
Global Const DBX_PORT_VERTLINE_DBL_VERT = 21
Global Const DBX_PORT_VERTLINE_DBL_HORZ = 22
Global Const DBX_PORT_NOOUTLINE_DBL_VERT = 23
Global Const DBX_PORT_NOOUTLINE_DBL_HORZ = 24

' Pin Length Types: Returned in TPort.pinLength

Global Const DBX_PORT_PIN_LONG = 300
Global Const DBX_PORT_PIN_SHORT = 100
Global Const DBX_PORT_PIN_CUSTOM = 0

' Line styles and widths
Global Const DBX_SOLID_LINE = 0
Global Const DBX_DASHED_LINE = 1
Global Const DBX_DOTTED_LINE = 2
Global Const DBX_THIN_LINE = 10
Global Const DBX_THICK_LINE = 30

' Pin Display Styles:  Returned in inside and outside styles

Global Const PIN_DISPLAY_O_NONE = 0
Global Const PIN_DISPLAY_O_FLOW_IN = 1
Global Const PIN_DISPLAY_O_FLOW_OUT = 2
Global Const PIN_DISPLAY_O_FLOW_BI = 3
Global Const PIN_DISPLAY_O_ANALOG = 4
Global Const PIN_DISPLAY_O_DIGITAL = 5
Global Const PIN_DISPLAY_O_NONLOGIC = 6

Global Const PIN_DISPLAY_OE_NONE = 0
Global Const PIN_DISPLAY_OE_DOT = 1
Global Const PIN_DISPLAY_OE_POL_IN = 2
Global Const PIN_DISPLAY_OE_POL_OUT = 3

Global Const PIN_DISPLAY_IE_NONE = 0
Global Const PIN_DISPLAY_IE_CLOCK = 1

Global Const PIN_DISPLAY_I_NONE = 0
Global Const PIN_DISPLAY_I_OPEN = 1
Global Const PIN_DISPLAY_I_OPEN_H = 2
Global Const PIN_DISPLAY_I_OPEN_L = 3
Global Const PIN_DISPLAY_I_PASS_UP = 4
Global Const PIN_DISPLAY_I_PASS_DOWN = 5
Global Const PIN_DISPLAY_I_3_STATE = 6
Global Const PIN_DISPLAY_I_AMPLIFIER = 7
Global Const PIN_DISPLAY_I_GENERATOR = 8
Global Const PIN_DISPLAY_I_HYSTERESIS = 9
Global Const PIN_DISPLAY_I_POSTPONED = 10
Global Const PIN_DISPLAY_I_SHIFT = 11

'  Symbol Alternate types

Global Const DBX_ALTTYPE_NORMAL = 0
Global Const DBX_ALTTYPE_IEE = 1
Global Const DBX_ALTTYPE_DEMORGAN = 2

' Drill Symbol Types:  Returned in TPadViaStyle.drillSymbol

Global Const DBX_DRILLSYM_UNDEFINED = -1
Global Const DBX_DRILLSYM_CROSS = 0
Global Const DBX_DRILLSYM_X = 1
Global Const DBX_DRILLSYM_Y = 2
Global Const DBX_DRILLSYM_T = 3
Global Const DBX_DRILLSYM_HOUR = 4
Global Const DBX_DRILLSYM_SIDE_HOUR = 5
Global Const DBX_DRILLSYM_BOX_LINE = 6
Global Const DBX_DRILLSYM_DIAMOND_LINE = 7
Global Const DBX_DRILLSYM_BOX_V = 8
Global Const DBX_DRILLSYM_DIAMOND_V = 9
Global Const DBX_DRILLSYM_BOX_X = 10
Global Const DBX_DRILLSYM_DIAMOND_CROSS = 11
Global Const DBX_DRILLSYM_BOX_CROSS = 12
Global Const DBX_DRILLSYM_DIAMOND_X = 13
Global Const DBX_DRILLSYM_BOX_Y = 14
Global Const DBX_DRILLSYM_DIAMOND_Y = 15
Global Const DBX_DRILLSYM_BOX_T = 16
Global Const DBX_DRILLSYM_DIAMOND_T = 17
Global Const DBX_DRILLSYM_CIRCLE_LINE = 18
Global Const DBX_DRILLSYM_CIRCLE_V = 19
Global Const DBX_DRILLSYM_CIRCLE_CROSS = 20
Global Const DBX_DRILLSYM_CIRCLE_X = 21
Global Const DBX_DRILLSYM_CIRCLE_Y = 22
Global Const DBX_DRILLSYM_CIRCLE_T = 23
Global Const DBX_DRILLSYM_UPPER_A = 24
Global Const DBX_DRILLSYM_UPPER_B = 25
Global Const DBX_DRILLSYM_UPPER_C = 26
Global Const DBX_DRILLSYM_UPPER_D = 27
Global Const DBX_DRILLSYM_UPPER_E = 28
Global Const DBX_DRILLSYM_UPPER_F = 29
Global Const DBX_DRILLSYM_UPPER_G = 30
Global Const DBX_DRILLSYM_UPPER_H = 31
Global Const DBX_DRILLSYM_UPPER_I = 32
Global Const DBX_DRILLSYM_UPPER_J = 33
Global Const DBX_DRILLSYM_UPPER_K = 34
Global Const DBX_DRILLSYM_UPPER_L = 35
Global Const DBX_DRILLSYM_UPPER_M = 36
Global Const DBX_DRILLSYM_UPPER_N = 37
Global Const DBX_DRILLSYM_UPPER_O = 38
Global Const DBX_DRILLSYM_UPPER_P = 39
Global Const DBX_DRILLSYM_UPPER_Q = 40
Global Const DBX_DRILLSYM_UPPER_R = 41
Global Const DBX_DRILLSYM_UPPER_S = 42
Global Const DBX_DRILLSYM_UPPER_U = 43
Global Const DBX_DRILLSYM_UPPER_V = 44
Global Const DBX_DRILLSYM_UPPER_W = 45
Global Const DBX_DRILLSYM_UPPER_Z = 46
Global Const DBX_DRILLSYM_LOWER_A = 47
Global Const DBX_DRILLSYM_LOWER_B = 48
Global Const DBX_DRILLSYM_LOWER_C = 49
Global Const DBX_DRILLSYM_LOWER_D = 50
Global Const DBX_DRILLSYM_LOWER_E = 51
Global Const DBX_DRILLSYM_LOWER_F = 52
Global Const DBX_DRILLSYM_LOWER_G = 53
Global Const DBX_DRILLSYM_LOWER_H = 54
Global Const DBX_DRILLSYM_LOWER_I = 55
Global Const DBX_DRILLSYM_LOWER_J = 56
Global Const DBX_DRILLSYM_LOWER_K = 57
Global Const DBX_DRILLSYM_LOWER_L = 58
Global Const DBX_DRILLSYM_LOWER_M = 59
Global Const DBX_DRILLSYM_LOWER_N = 60
Global Const DBX_DRILLSYM_LOWER_O = 61
Global Const DBX_DRILLSYM_LOWER_P = 62
Global Const DBX_DRILLSYM_LOWER_Q = 63
Global Const DBX_DRILLSYM_LOWER_R = 64
Global Const DBX_DRILLSYM_LOWER_S = 65
Global Const DBX_DRILLSYM_LOWER_T = 66
Global Const DBX_DRILLSYM_LOWER_U = 67
Global Const DBX_DRILLSYM_LOWER_V = 68
Global Const DBX_DRILLSYM_LOWER_W = 69
Global Const DBX_DRILLSYM_LOWER_Y = 70
Global Const DBX_DRILLSYM_LOWER_Z = 71

' Color Constants
Global Const DBX_COLOR_BLACK            = 1
Global Const DBX_COLOR_DARKRED          = 2
Global Const DBX_COLOR_DARKGREEN        = 3
Global Const DBX_COLOR_DARKYELLOW       = 4 
Global Const DBX_COLOR_DARKBLUE         = 5
Global Const DBX_COLOR_DARKMAGENTA      = 6
Global Const DBX_COLOR_DARKCYAN         = 7
Global Const DBX_COLOR_LIGHTGRAY        = 8
Global Const DBX_COLOR_DARKGRAY         = 9
Global Const DBX_COLOR_RED              = 10
Global Const DBX_COLOR_GREEN            = 11
Global Const DBX_COLOR_YELLOW           = 12
Global Const DBX_COLOR_BLUE             = 13 
Global Const DBX_COLOR_MAGENTA          = 14 
Global Const DBX_COLOR_CYAN             = 15 
Global Const DBX_COLOR_WHITE            = 16 
Global Const DBX_COLOR_POWDERGREEN      = 17 
Global Const DBX_COLOR_POWDERBLUE       = 18 
Global Const DBX_COLOR_POWDER           = 19 
Global Const DBX_COLOR_GRAY             = 20 

' Field Key Types
Global Const   DBX_FIELD_DATE      =      1
Global Const   DBX_FIELD_CURDATE   =      2
Global Const   DBX_FIELD_TIME      =      3
Global Const   DBX_FIELD_CURTIME   =      4
Global Const   DBX_FIELD_AUTHOR    =      5
Global Const   DBX_FIELD_REV       =      6
Global Const   DBX_FIELD_FILENAME  =      7
Global Const   DBX_FIELD_TITLE     =      8
Global Const   DBX_FIELD_SHEETNUM  =      10
Global Const   DBX_FIELD_NUMSHEETS =      11
Global Const   DBX_FIELD_DRAWING_NUMBER = 12     
Global Const   DBX_FIELD_NOTE           = 13     
Global Const   DBX_FIELD_REVISION_NOTE  = 14    


' Table Types 
Global Const   DBX_TABLE_NET_INDEX        = 0   
Global Const   DBX_TABLE_NOTES            = 1   
Global Const   DBX_TABLE_POWER            = 2   
Global Const   DBX_TABLE_SPARE_GATE       = 3   
Global Const   DBX_TABLE_DRILL            = 4   
Global Const   DBX_TABLE_REVISION_NOTES   = 5   


' Diagram Types

Global Const   DBX_DIAGRAM_LAYER_STACK  = 1         
Global Const   DBX_DIAGRAM_PROFILE      = 2        
Global Const   DBX_DIAGRAM_DESIGNVIEW   = 3        



' TRoom.roomFillPattern Types

Global Const   DBX_ROOM_UNDEFINED_FILLPATTERN = 0
Global Const   DBX_ROOM_CLEAR_FILLPATTERN     = 1
Global Const   DBX_ROOM_SOLID_FILLPATTERN     = 2
Global Const   DBX_ROOM_HATCHED_FILLPATTERN   = 3



' TRoom.placementSide Types

Global Const    DBX_ROOM_UNDEFINED_PLACEMENT     = 0
Global Const    DBX_ROOM_TOP_PLACEMENT           = 1
Global Const    DBX_ROOM_BOTTOM_PLACEMENT        = 2
Global Const    DBX_ROOM_TOP_OR_BOTTOM_PLACEMENT = 3


' TPoint.placementSide Types

Global Const    DBX_TESTPOINT_UNDEFINED_PLACEMENT = -1
Global Const    DBX_TESTPOINT_TOP_PLACEMENT       =  0
Global Const    DBX_TESTPOINT_BOTTOM_PLACEMENT    =  1


' TComponent.connectionType Types

Global Const  DBX_COMPONENT_CONNECTION_NORMAL          = 0
Global Const  DBX_COMPONENT_CONNECTION_POWER           = 1
Global Const  DBX_COMPONENT_CONNECTION_SHEET_CONNECTOR = 2
Global Const  DBX_COMPONENT_CONNECTION_MODULE          = 3
Global Const  DBX_COMPONENT_CONNECTION_LINK            = 4


'  RuleCategory

Global Const   DBX_RULE_CATEGORY_UNKNOWN                     =   0

Global Const   DBX_RULE_CATEGORY_ERC_BUS_NET                 =   1
Global Const   DBX_RULE_CATEGORY_ERC_COMPONENT               =   2
Global Const   DBX_RULE_CATEGORY_ERC_ELECTRICAL              =   3
Global Const   DBX_RULE_CATEGORY_ERC_HIERARCHY               =   4
Global Const   DBX_RULE_CATEGORY_ERC_NET_CONNECTIVITY        =   5
Global Const   DBX_RULE_CATEGORY_ERC_NO_NODE_NET             =   6
Global Const   DBX_RULE_CATEGORY_ERC_SINGLE_NODE_NET         =   7 
Global Const   DBX_RULE_CATEGORY_ERC_UNCONNECTED_PIN         =   8
Global Const   DBX_RULE_CATEGORY_ERC_UNCONNECTED_WIRE        =   9

Global Const   DBX_RULE_CATEGORY_DRC_CLEARANCE               =  10 
Global Const   DBX_RULE_CATEGORY_DRC_NETLIST                 =  11
Global Const   DBX_RULE_CATEGORY_DRC_UNROUTED_NETS           =  12
Global Const   DBX_RULE_CATEGORY_DRC_UNCONNECTED_PINS        =  13
Global Const   DBX_RULE_CATEGORY_DRC_NET_LENGTH              =  14
Global Const   DBX_RULE_CATEGORY_DRC_SILK                    =  15
Global Const   DBX_RULE_CATEGORY_DRC_TEXT                    =  16 
Global Const   DBX_RULE_CATEGORY_DRC_WIDTH                   =  17
Global Const   DBX_RULE_CATEGORY_DRC_POUR                    =  18
Global Const   DBX_RULE_CATEGORY_DRC_PLANE                   =  19
Global Const   DBX_RULE_CATEGORY_DRC_COMPONENT               =  20
Global Const   DBX_RULE_CATEGORY_DRC_DRILL                   =  21
Global Const   DBX_RULE_CATEGORY_DRC_TESTPOINT               =  22


'  RuleType

Global Const   DBX_RULE_TYPE_UNKNOWN                         =   0
                                             
Global Const   DBX_RULE_ERC_ELEC_3STATE_OUTPUT               =   1
Global Const   DBX_RULE_ERC_ELEC_3STATE_POWER                =   2
Global Const   DBX_RULE_ERC_ELEC_BI_OH                       =   3
Global Const   DBX_RULE_ERC_ELEC_BI_OL                       =   4
Global Const   DBX_RULE_ERC_ELEC_BI_OUTPUT                   =   5
Global Const   DBX_RULE_ERC_ELEC_BI_POWER                    =   6
Global Const   DBX_RULE_ERC_ELEC_OH_BI                       =   7
Global Const   DBX_RULE_ERC_ELEC_OH_OH                       =   8
Global Const   DBX_RULE_ERC_ELEC_OH_OL                       =   9
Global Const   DBX_RULE_ERC_ELEC_OH_OUTPUT                   =  10
Global Const   DBX_RULE_ERC_ELEC_OH_POWER                    =  11
Global Const   DBX_RULE_ERC_ELEC_OL_BI                       =  12
Global Const   DBX_RULE_ERC_ELEC_OL_OH                       =  13
Global Const   DBX_RULE_ERC_ELEC_OL_OUTPUT                   =  14
Global Const   DBX_RULE_ERC_ELEC_OL_POWER                    =  15
Global Const   DBX_RULE_ERC_ELEC_OUTPUT_BI                   =  16
Global Const   DBX_RULE_ERC_ELEC_OUTPUT_OUTPUT               =  17
Global Const   DBX_RULE_ERC_ELEC_OUTPUT_3STATE               =  18
Global Const   DBX_RULE_ERC_ELEC_OUTPUT_OH                   =  19
Global Const   DBX_RULE_ERC_ELEC_OUTPUT_OL                   =  20
Global Const   DBX_RULE_ERC_ELEC_OUTPUT_POWER                =  21
Global Const   DBX_RULE_ERC_ELEC_POWER_3STATE                =  22
Global Const   DBX_RULE_ERC_ELEC_POWER_BI                    =  23
Global Const   DBX_RULE_ERC_ELEC_POWER_OH                    =  24
Global Const   DBX_RULE_ERC_ELEC_POWER_OL                    =  25
Global Const   DBX_RULE_ERC_ELEC_POWER_OUTPUT                =  26
Global Const   DBX_RULE_ERC_ELEC_NO_INPUT                    =  27
Global Const   DBX_RULE_ERC_ELEC_NO_OUTPUT                   =  28
Global Const   DBX_RULE_ERC_NET_CON_DIFFRNT_NET_NAME         =  29
Global Const   DBX_RULE_ERC_NET_CON_MERGED_NETS_NOT          =  30
Global Const   DBX_RULE_ERC_NET_CON_NET_NAME_NOT_VIS         =  31
Global Const   DBX_RULE_ERC_NET_CON_PIN_NAME_MISSING         =  32
Global Const   DBX_RULE_ERC_HIER_EXCEED_SHEET_LIMIT          =  33
Global Const   DBX_RULE_ERC_HIER_INF_SHEET_DIFF              =  34
Global Const   DBX_RULE_ERC_HIER_INT_ATTR_NOT_DEFINED        =  35
Global Const   DBX_RULE_ERC_HIER_INT_ILLEGAL                 =  36
Global Const   DBX_RULE_ERC_HIER_INT_MULTIPLE                =  37
Global Const   DBX_RULE_ERC_HIER_INT_NOT_DEFINED             =  38
Global Const   DBX_RULE_ERC_HIER_INT_UNUSED                  =  39
Global Const   DBX_RULE_ERC_HIER_MULT_SHEET                  =  40
Global Const   DBX_RULE_ERC_HIER_PIN_DES_MISMATCH            =  41
Global Const   DBX_RULE_ERC_HIER_PIN_ELECT_TYPE              =  42
Global Const   DBX_RULE_ERC_HIER_PIN_MISMATCH                =  43
Global Const   DBX_RULE_ERC_HIER_RECURSIVE                   =  44
Global Const   DBX_RULE_ERC_HIER_SAME_SHEET                  =  45
Global Const   DBX_RULE_ERC_HIER_INFPIN_NOT_CONNECTED        =  46
Global Const   DBX_RULE_ERC_HIER_INFPIN_PASSTHROUGH          =  47
Global Const   DBX_RULE_ERC_HIER_MODPIN_NOT_CONNECTED        =  48
Global Const   DBX_RULE_ERC_COMP_TWO_COMPS                   =  49
Global Const   DBX_RULE_ERC_BUS_NET_BUS_NO_NET               =  50
Global Const   DBX_RULE_ERC_BUS_NET_BUS_SINGLE_NET           =  51
Global Const   DBX_RULE_ERC_NO_NODES                         =  52
Global Const   DBX_RULE_ERC_SINGLE_NODE                      =  53
Global Const   DBX_RULE_ERC_UNCON_PIN_BLANK_NET_NAME         =  54
Global Const   DBX_RULE_ERC_UNCON_PIN_UNCONNECTED_PIN        =  55
Global Const   DBX_RULE_ERC_UNCONNECTED_WIRE                 =  56
                                                       
Global Const   DBX_RULE_DRC_CLEARANCE                        =  57
Global Const   DBX_RULE_DRC_SHORT                            =  58
Global Const   DBX_RULE_DRC_NET_SHORTED_TO_TIE               =  59
Global Const   DBX_RULE_DRC_COMP_PINS_SHORTED                =  60
Global Const   DBX_RULE_DRC_CONNECTED_POINT_TO_POINT         =  61
Global Const   DBX_RULE_DRC_PSEUDO                           =  62
Global Const   DBX_RULE_DRC_VIASTYLE_NONEXISTANT             =  63
Global Const   DBX_RULE_DRC_VIASTYLE_VIOLATION               =  64
Global Const   DBX_RULE_DRC_MAXVIAS                          =  65
Global Const   DBX_RULE_DRC_UNCONNECTED_PIN                  =  66
Global Const   DBX_RULE_DRC_CU_POUR_CLEARANCE                =  67
Global Const   DBX_RULE_DRC_CU_POUR_TERRA_INCOGNITA          =  68
Global Const   DBX_RULE_DRC_CU_POUR_UNFILLED                 =  69
Global Const   DBX_RULE_DRC_CU_POUR_NO_NET                   =  70
Global Const   DBX_RULE_DRC_DRILL_CLEARANCE                  =  71
Global Const   DBX_RULE_DRC_DRILL_HOLE_SAME_LAYER            =  72
Global Const   DBX_RULE_DRC_DRILL_HOLE_INTERFERENCE          =  73
Global Const   DBX_RULE_DRC_UNROUTED_NET                     =  74
Global Const   DBX_RULE_DRC_HOLE_NO_CONNECT                  =  75
Global Const   DBX_RULE_DRC_HOLE_RANGE_VIOLATION             =  76
Global Const   DBX_RULE_DRC_TIE_NET_WITH_NO_POLY             =  77
Global Const   DBX_RULE_DRC_TIE_POLY_WITHOUT_NETS            =  78
Global Const   DBX_RULE_DRC_NET_FREE_PIN                     =  79
Global Const   DBX_RULE_DRC_NET_LENGTH                       =  80
Global Const   DBX_RULE_DRC_SILK_CLEARANCE                   =  81
Global Const   DBX_RULE_DRC_TEXT_CLEARANCE                   =  82
Global Const   DBX_RULE_DRC_WIDTH                            =  83
Global Const   DBX_RULE_DRC_COMPONENT_SIDE                   =  84
Global Const   DBX_RULE_DRC_COMPONENT_HEIGHT                 =  85
Global Const   DBX_RULE_DRC_ROOM_INCLUDED_COMPS              =  86
Global Const   DBX_RULE_DRC_EMPTY_ROOM                       =  87
Global Const   DBX_RULE_DRC_PLANE_CLEARANCE                  =  88
Global Const   DBX_RULE_DRC_PLANE_SPLIT                      =  89
Global Const   DBX_RULE_DRC_PLANE_PARTIAL_CONNECTION         =  90
Global Const   DBX_RULE_DRC_PLANE_HOLE_SHORT                 =  91
Global Const   DBX_RULE_DRC_PLANE_NO_CONNECTIONS             =  92
Global Const   DBX_RULE_DRC_PLANE_NO_NET                     =  93
Global Const   DBX_RULE_DRC_PLANE_COPPER_INTERSECTION        =  94
Global Const   DBX_RULE_DRC_TESTPOINT_NO_NET                 =  95
Global Const   DBX_RULE_DRC_TESTPOINT_NOT_ON_TP_GRID         =  96
Global Const   DBX_RULE_DRC_TESTPOINT_SPACING                =  97
Global Const   DBX_RULE_DRC_TESTPOINT_INVALID_OBJECT         =  98
Global Const   DBX_RULE_DRC_TESTPOINT_NOT_ON_PAD_CENTER_SMT  =  99
Global Const   DBX_RULE_DRC_TESTPOINT_NOT_ON_PAD_CENTER_THRU = 100
Global Const   DBX_RULE_DRC_TESTPOINT_INVALID_PAD_AREA       = 101
Global Const   DBX_RULE_DRC_TESTPOINT_NET_MISSING            = 102
Global Const   DBX_RULE_DRC_TESTPOINT_WRONG_SIDE             = 103
Global Const   DBX_RULE_DRC_TESTPOINT_MULTIPLE_NETS          = 104
Global Const   DBX_RULE_DRC_MULTIPLE_TIE_POLY                = 105
Global Const   DBX_RULE_DRC_NET_FREE_PAD                     = 106
Global Const   DBX_RULE_DRC_COMPONENT_CLEARANCE              = 107
Global Const   DBX_RULE_DRC_NON_PLATED_HOLE_NO_CONNECT       = 108
Global Const   DBX_RULE_DRC_NON_PLATED_THROUGH_HOLE          = 109
                          

'  ViolationType

Global Const   DBX_ERROR_VIOLATION                           =   0
Global Const   DBX_WARNING_VIOLATION                         =   1
Global Const   DBX_IGNORED_VIOLATION                         =   2
Global Const   DBX_OVERRIDDEN_VIOLATION                      =   3


' Unit Definitions 

Global Const    DBX_UNIT_DB       =          0       ' database units
Global Const    DBX_UNIT_MIL      =          1       ' mil
Global Const    DBX_UNIT_MM       =          2       ' millimeter
Global Const    DBX_UNIT_CM       =          3       ' centimeter
Global Const    DBX_UNIT_INCH     =          4       ' inch
Global Const    DBX_UNIT_APP      =          5       '
Global Const    DBX_UNIT_GLOBAL   =          6       ' ie. Use gpDesign's current DBX_UNITs.
Global Const    DBX_UNIT_LAYER    =          7       ' String represents a layer name.
Global Const    DBX_UNIT_VIASTYLE =          8       ' String represents a via style name.
Global Const    DBX_UNIT_M        =          9       ' meter
Global Const    DBX_UNIT_UM       =          10      ' micrometer
Global Const    DBX_UNIT_NM       =          11      ' nanometer
Global Const    DBX_UNIT_PM       =          12      ' picometer
Global Const    DBX_UNIT_RAD      =          13      ' radian
Global Const    DBX_UNIT_DEG      =          14      ' degree
Global Const    DBX_UNIT_OHM      =          15      ' ohms
Global Const    DBX_UNIT_MHO      =          16      ' conductance
Global Const    DBX_UNIT_VOLT     =          17      ' volts
Global Const    DBX_UNIT_MVOLT    =          18      ' millivolts
Global Const    DBX_UNIT_UVOLT    =          19      ' microvolts
Global Const    DBX_UNIT_NVOLT    =          20      ' nanovolts
Global Const    DBX_UNIT_PVOLT    =          21      ' picovolts
Global Const    DBX_UNIT_AMP      =          22      ' ampere
Global Const    DBX_UNIT_MAMP     =          23      ' milliamp
Global Const    DBX_UNIT_UAMP     =          24      ' microamp
Global Const    DBX_UNIT_NAMP     =          25      ' nanoamp
Global Const    DBX_UNIT_PAMP     =          26      ' picoamp
Global Const    DBX_UNIT_HENRY    =          27      ' Henry
Global Const    DBX_UNIT_MHENRY   =          28      ' millihenry
Global Const    DBX_UNIT_UHENRY   =          29      ' microhenry
Global Const    DBX_UNIT_NHENRY   =          30      ' nanohenry
Global Const    DBX_UNIT_PHENRY   =          31      ' picohenry
Global Const    DBX_UNIT_FARAD    =          32      ' Farad
Global Const    DBX_UNIT_MFARAD   =          33      ' millifarad
Global Const    DBX_UNIT_UFARAD   =          34      ' microfarad
Global Const    DBX_UNIT_NFARAD   =          35      ' nanofarad
Global Const    DBX_UNIT_PFARAD   =          36      ' picofarad
Global Const    DBX_UNIT_SECOND   =          37      ' second
Global Const    DBX_UNIT_MSECOND  =          38      ' millisecond
Global Const    DBX_UNIT_USECOND  =          39      ' microsecond
Global Const    DBX_UNIT_NSECOND  =          40      ' nanosecond
Global Const    DBX_UNIT_PSECOND  =          41      ' picosecond
Global Const    DBX_UNIT_BOOL     =          42      ' Boolean
Global Const    DBX_UNIT_NUM      =          43      ' number (DBX_UNITless)
Global Const    DBX_UNIT_STRING   =          44      ' string
Global Const    DBX_UNIT_HERTZ    =          45      ' hertz
Global Const    DBX_UNIT_KHERTZ   =          46      ' kilohertz
Global Const    DBX_UNIT_MHERTZ   =          47      ' megahertz
Global Const    DBX_UNIT_WATT     =          48      ' wattage
Global Const    DBX_UNIT_MWATT    =          49      ' milliwatt
Global Const    DBX_UNIT_UWATT    =          50      ' microwatt
Global Const    DBX_UNIT_NWATT    =          51      ' nanowatt
Global Const    DBX_UNIT_PWATT    =          52      ' picowatt
Global Const    DBX_UNIT_GHERTZ   =          53      ' gigahertz
Global Const    DBX_UNIT_NO_UNIT  =          54      ' a unit has not been defined for the constraint


'  Component graphic orientation assignments

Global Const    DBX_COMP_GRAPHIC_ORIENT_TOP_0       = 0
Global Const    DBX_COMP_GRAPHIC_ORIENT_TOP_90      = 1
Global Const    DBX_COMP_GRAPHIC_ORIENT_TOP_180     = 2
Global Const    DBX_COMP_GRAPHIC_ORIENT_TOP_270     = 3
Global Const    DBX_COMP_GRAPHIC_ORIENT_BOTTOM_0    = 4
Global Const    DBX_COMP_GRAPHIC_ORIENT_BOTTOM_90   = 5
Global Const    DBX_COMP_GRAPHIC_ORIENT_BOTTOM_180  = 6
Global Const    DBX_COMP_GRAPHIC_ORIENT_BOTTOM_270  = 7


'  Pcb design solder flow direction indicators

Global Const    SOLDER_FLOW_TOP_TO_BOTTOM   = 0
Global Const    SOLDER_FLOW_RIGHT_TO_LEFT   = 1
Global Const    SOLDER_FLOW_BOTTOM_TO_TOP   = 2
Global Const    SOLDER_FLOW_LEFT_TO_RIGHT   = 3

' Conversation and Context Structure

Type DbxContext
   hConv As Long
   appInst As Long
   version As Long
   language As Long
   hWnd As Long             
   hMmf As Long
   pMmf As Long  ' placeholder for a C void pointer
End Type


' The following structures are the data structures for the extracted items,
' listed in alphabetical order


Type TCoord
    x As Long
    y As Long
End Type

Type TBoundRect
    lowerLeft As TCoord
    upperRight As TCoord
End Type

Type TArc
    itemId As Long
    width As Long
    radius As Long
    centerPt As TCoord
    startAng As Long
    sweepAng As Long
    boundRect As TBoundRect
    netId As Long
    layerId As Long
    isHighlighted As Long
    isFixed As Long
End Type

Type TAttribute
    itemId As Long
    name As String * DBX_MAX_TYPE_LEN
    value As String * DBX_MAX_ATTRIBUTE_LEN
    formula As String * DBX_MAX_FORMULA_LEN
    comment As String * DBX_MAX_TEXTITEM_LEN    
    typeLength As Long
    valueLength As Long
    formulaLength As Long
    commentLength As Long    
    textStyleId As Long
    justPoint As Long
    refPoint As TCoord
    boundRect As TBoundRect
    rotationAng As Long
    compId As Long        ' not used
    netId As Long         ' not used
    netClassId As Long    ' not used
    layerId As Long
    isFlipped As Long
    isHighlighted As Long
    isVisible As Long
    units As Long
End Type

Type TBus
    itemId        As Long
    startPt       As TCoord
    endPt         As TCoord
    layerId       As Long
    busName       As String * DBX_MAX_NAME_LEN
    isFlipped     As Long
    isHighlighted As Long
    isNameVisible As Long
End Type

Type TClassToClass
    netClassId1   As Long
    netClassId2   As Long
    netClassName1 As String * DBX_MAX_NAME_LEN
    netClassName2 As String * DBX_MAX_NAME_LEN
End Type    

Type TComponent
    compId As Long
    refDes As String * DBX_MAX_NAME_LEN
    compType As String * DBX_MAX_TYPE_LEN
    value As String * DBX_MAX_VALUE_LEN
    patternName As String * DBX_MAX_NAME_LEN
    libraryName As String * DBX_MAX_FILENAME_LEN
    refPoint As TCoord
    boundRect As TBoundRect
    rotationAng As Long
    numberPads As Long
    numberPins As Long
    numberParts As Long
    isAlpha As Long
    isFlipped As Long
    isHighlighted As Long
    isHetero As Long
    connectionType As Long
    isFixed As Long

    numberGraphics As Long
    currentGraphicName  As String * DBX_MAX_NAME_LEN
    defaultGraphicName As String * DBX_MAX_NAME_LEN
    isAutoSwapGraphic As Long
End Type

Type TCompGraphic
    graphicName As String * DBX_MAX_NAME_LEN
    numberPads As Long
    numberAttrs As Long
    numberItems As Long
End Type

Type TCompPin
    'itemId As Long
    compPinNumber As Long
    pinDes As String * DBX_MAX_NAME_LEN
    gateNumber As Long
    symPinNumber As Long
    padNumber As Long
    pinName As String * DBX_MAX_NAME_LEN
    gateEq As Long
    pinEq As Long
    electype As Long
End Type

Type TDesign
    designName As String * DBX_MAX_NAME_LEN
    title As String * DBX_MAX_NAME_LEN
    designer As String * DBX_MAX_NAME_LEN
    version As String * DBX_MAX_NAME_LEN
    lastModifiedDate As String * DBX_MAX_NAME_LEN
    lastModifiedTime As String * DBX_MAX_NAME_LEN
    drawingNumber As String * DBX_MAX_NAME_LEN
	guidString As String  *  DBX_MAX_NAME_LEN
    workSpaceSize As TCoord
    layerExtents As TBoundRect
    absGridId As Long
    relGridId As Long
    isGridAbsolute As Long
    userUnits As Long
    relGridOrigin As TCoord
    isModified As Long
    solderFlowDir As Long
End Type

Type TField
    itemId As Long
    textStyleId As Long
    text As String * DBX_MAX_TEXTITEM_LEN
    layerId As Long
    justPoint As Long
    refPoint As TCoord
    rotationAng As Long
    isFlipped As Long
    isHighlighted As Long
    isVisible As Long
    fieldKeyType As Long
End Type

Type TGrid
    gridId      As Long
    gridSpacing As String * DBX_MAX_GRIDSPACING_LEN
End Type
    
Type TLayer
    layerId As Long
    layerName As String * DBX_MAX_NAME_LEN
    layerType As Long
    layerBias As Long
    planeNetId As Long
    lineLineClearance As Long
    padLineClearance As Long
    padPadClearance As Long
    viaPadClearance As Long
    viaLineClearance As Long
    viaViaClearance As Long
    isEnabled As Long
    layerPosition As Long
End Type

Type TLayerStackup
    layerName As String * DBX_MAX_NAME_LEN
    layerMaterial As String * DBX_MAX_NAME_LEN
    layerThickness As String * DBX_MAX_NAME_LEN
    layerDialectricConstant As String * DBX_MAX_NAME_LEN
End Type

Type TLine
    itemId As Long
    lineType As Long
    width As Long
    startPt As TCoord
    endPt As TCoord
    boundRect As TBoundRect
    netId As Long
    layerId As Long
    isHighlighted As Long
    isFixed As Long
End Type

Type TNet
    netId As Long
    netName As String * DBX_MAX_NAME_LEN
    nodeCount As Long
    length As Long
    isPlane As Long
End Type

Type TNetClass
    netClassId   As Long
    netClassName As String * DBX_MAX_NAME_LEN
    numberOfNets As Long
End Type

Type TPad
    itemId As Long
    'padNumber As Long
    compRefDes As String * DBX_MAX_NAME_LEN
    padStyleId As Long                     ' Not Used for Free Pads
    center As TCoord
    layerId As Long
    isFlipped As Long
    rotationAng As Long
    isHighlighted As Long
    netId As Long
    boundRect As TBoundRect
    compPin As TCompPin
    defaultPinDes As String * DBX_MAX_NAME_LEN
    isFixed As Long
End Type

Type TPadViaShape
    layerId As Long
    layerType As Long
    styleType As Long                   ' Pad or Via Style
    shape As Long
    holeDia As Long
    width As Long                       ' Used for Normal Types
    height As Long                      ' Used for Normal Types
    outerDia As Long                    ' Used for Thermals
    innerDia As Long                    ' Used for Thermals
    spokeWidth As Long                  ' Used for Thermals
    isPourNoConn As Long                ' Prohibit Cu pour thermalizing
End Type

Type TPadViaStyle
    styleId As Long
    styleType As Long                   ' Pad or Via Style
    name As String * DBX_MAX_NAME_LEN
    holeDia As Long
    isHolePlated As Long
    xOffset As Long
    yOffset As Long
    holeStartLayer As Long
    holeEndLayer As Long
    drillSymbol As Long
End Type

Type TPattern
    itemId As Long
    patternName As String * DBX_MAX_NAME_LEN
    rotationAng As Long
    isFlipped As Long
    isHighlighted As Long
End Type

Type TPin
    itemId As Long
    'symPinNumber As Long
    compRefDes As String * DBX_MAX_NAME_LEN
    outsideStyle As Long
    outsideEdgeStyle As Long
    insideStyle As Long
    insideEdgeStyle As Long
    refPoint As TCoord
    layerId As Long
    isFlipped As Long
    isHighlighted As Long
    rotationAng As Long
    netId As Long
    boundRect As TBoundRect
    pinLength As Long
    compPin As TCompPin
    defaultPinDes As String * DBX_MAX_NAME_LEN
End Type

Type TPoint
    itemId As Long
    x As Long
    y As Long
    pointType As Long                   ' =0 for DBX_COORDINATE Point Type
    number As Long
    textInfo As String * DBX_MAX_TEXTITEM_LEN
    layerId As Long
    isFlipped As Long
    isVisible As Long
    isHighlighted As Long
    ruleCategory As Long              ' ERC/DRC rule category;       InfoPoint only; new V15
    ruleType As Long                  ' ERC/DRC rule type;           InfoPoint only; new V15
    violationType As Long             ' violation type of InfoPoint; InfoPoint only; new V15 
    placementSide As Long             ' TestPoint only
    isSnapToCenter As Long            ' TestPoint only
    netId As Long                     ' TestPoint only
    isFixed As Long                   ' TestPoint only
End Type

Type TPoly
    itemId As Long
    polyType As Long
    numPts As Long
    boundRect As TBoundRect
    netId As Long
    layerId As Long
    isHighlighted As Long
End Type

Type TPort
    itemId As Long
    netId As Long
    portType As Long
    pinLength As Long
    rotationAng As Long
    isFlipped As Long
    isHighlighted As Long
    textStyleId As Long
    layerId As Long
    refPoint As TCoord
End Type

Type TPour
    itemId As Long
    lineSpacing As Long          ' in database units
    lineWidth As Long            ' in database units
    thermalType As Long
    pourType As Long
    numPts As Long               ' number of outline points
    boundRect As TBoundRect
    netId As Long
    layerId As Long
    isFlooded As Long
    isHighlighted As Long        ' Highlight color: 0,1,2,3,4
    isFixed As Long
End Type

Type TPrintJob
    isSelected As Long                            ' Is PrintJob selected for output.
    jobName As String * DBX_MAX_FILENAME_LEN      ' Print job name.
    isRotated As Long                             ' Is PrintJob marked for rotated output.
End Type

Type TRoom
    roomId          As Long
    roomName        As String * DBX_MAX_NAME_LEN
    layerId         As Long
    numberOfIncludedComps   As Long
    numberOfExcludedComps   As Long
    boundRect       As TBoundRect
    placementSide   As Long
    isFixed         As Long
    isFlipped       As Long
    isHighlighted   As Long
    roomFillPattern As Long
    refPoint        As TCoord
    rotationAngle   As Long
End Type

Type TSymbol
    symbolId As Long
    symbolName As String * DBX_MAX_NAME_LEN
    refDes As String * DBX_MAX_NAME_LEN
    numberPins As Long
    partnumber As Long
    altType As Long
    refPoint As TCoord
    boundRect As TBoundRect
    rotationAng As Long
    isFlipped As Long
    isHighlighted As Long
    layerId As Long
    compType As String * DBX_MAX_NAME_LEN
    libraryName As String * DBX_MAX_NAME_LEN
End Type

Type TText
    itemId As Long
    textStyleId As Long
    text As String * DBX_MAX_TEXTITEM_LEN
    layerId As Long
    justPoint As Long
    refPoint As TCoord
    boundRect As TBoundRect
    rotationAng As Long
    isFlipped As Long
    isVisible As Long
    isHighlighted As Long
End Type

Type TTextStyle
    styleId As Long
    name As String * DBX_MAX_NAME_LEN
    strokePenWidth As Long
    strokeHeight As Long
    tTypeFaceName As String * DBX_MAX_NAME_LEN
    tTypeHeight As Long
    isTrueTypeAllowed As Long
    isDisplayTrueType As Long
End Type

Type TVia
    itemId As Long
    netId As Long
    center As TCoord
    rotationAng As Long
    viaStyleId As Long
    boundRect As TBoundRect
    isFlipped As Long
    isHighlighted As Long
    isFixed As Long
End Type

Type TWire
    itemId As Long
    startPt As TCoord
    endPt As TCoord
    layerId As Long
    isFlipped As Long             ' =0 not flipped
    isHighlighted As Long         ' Highlight color: 0,1,2,3,4
    isNameVisible As Long
    netId As Long
    width As Long
End Type

 
Type TTable                ' (Pcb/Sch)
    itemId As Long
    refPoint As TCoord
    layerId As long
    boundRect As TBoundRect    
    rotationAng As Long
    isHighlighted As Long
    isFlipped As Long
    tableType As long
    tableTitle As String * DBX_MAX_TEXTITEM_LEN
    textStyleId As Long
    lineWidth As Long
End Type

 
Type TMetaFile        ' (Pcb)
    itemId As long
    refPoint As TCoord
    layerId As Long
    boundRect As TBoundRect
End Type

 

Type TDiagram            ' (Pcb)
    itemId As Long
    refPoint As TCoord
    layerId As long
    boundRect As TBoundRect
    diagramType As long
    title As String * DBX_MAX_TEXTITEM_LEN
    subTitle As String * DBX_MAX_TEXTITEM_LEN
    textStyleId As Long      ' of title, subtitle
    lineWidth As Long        ' Used only with StackUp diagram
End Type

 
Type TDetail            ' (Pcb)
    itemId As Long
    refPoint As TCoord        
    layerId As long
    boundRect As TBoundRect
    title As String * DBX_MAX_TEXTITEM_LEN
    subTitle As String * DBX_MAX_TEXTITEM_LEN
    fileName As String * DBX_MAX_FILENAME_LEN
    textStyleId As Long        ' of title, subtitle
End Type

Type TVariant            ' (Pcb/Sch)
    name As String * DBX_MAX_NAME_LEN
    description As String * DBX_MAX_TEXTITEM_LEN
    id As Long
End Type


' The following structure defines TItem, which can contain any of the
' extracted items.


Type TItem
    itemType    As Long
    arc         As TArc
    attribute   As TAttribute
    bus         As TBus
    classToClass As TClassToClass
    component   As TComponent
    compPin     As TCompPin
    design      As TDesign
    detail      As TDetail         
    diagram     As TDiagram         
    field       As TField
    grid        As TGrid
    layer       As TLayer
    layerStack  As TLayerStackup
    aline       As TLine
    metaFile    As TMetaFile     
    net         As TNet
    netClass    As TNetClass
    pad         As TPad
    padViaShape As TPadViaShape
    padViaStyle As TPadViaStyle
    pattern     As TPattern
    pin         As TPin
    apoint      As TPoint
    poly        As TPoly
    port        As TPort
    pour        As TPour
    printJob    As TPrintJob
    room        As TRoom
    symbol      As TSymbol
    table       As TTable         
    text        As TText
    textStyle   As TTextStyle
    via         As TVia
    wire        As TWire
    compGraphic As TCompGraphic
    variant     As TVariant
End Type

' This type is used to add or modify the pad and via shape in PCB
' The shape is a regular polygon that is defined by the 
' number of sides, rotation angle and circular diameter

Type TPadViaRegularPolyShape  '(PCB)
	layerId      As Long   
	layerType    As Long
	styleType    As Long         ' Pad or Via Style
	numSides     As Long         ' Number of the polygon sides
	rotAngle     As Long         ' Rotation angle
	circDia      As Long         ' Circular diameter
	isPourNoConn As Long         ' Prohibit Cu pour thermalizing
End Type

' The DBX API

Declare Function TAddClassToClassAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, classToClassAttribute As TAttribute) As Long
Declare Function TAddClassToClassLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TAddCompAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, compAttribute As TAttribute) As Long
Declare Function TAddDesignAttribute Lib "dbx32.dll" (Context As DbxContext, designAttr As TAttribute) As Long
Declare Function TAddIncludedRoomComponent Lib "dbx32.dll" (Context As DbxContext, ByVal roomId As Long, component As TComponent) As Long
Declare Function TAddLayerAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal layerId As Long, layerAttr As TAttribute) As Long
Declare Function TAddNetAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, netAttribute As TAttribute) As Long
Declare Function TAddNetClassAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, netClassAttribute As TAttribute) As Long
Declare Function TAddNetClassLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TAddNetClassNet Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, net As TNet) As Long
Declare Function TAddNetLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TAddNetNode Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, netNode As TItem) As Long
Declare Function TAddRoomAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal roomId As Long, roomAttr As TAttribute) As Long

Declare Function TAddLayer Lib "dbx32.dll" (Context As DbxContext, layer As TLayer) As Long
Declare Function TAddSheet Lib "dbx32.dll" (Context As DbxContext, sheet As TLayer) As Long

Declare Function TAddVariant Lib "dbx32.dll" (Context As DbxContext, a_variant As TVariant) As Long
Declare Function TDeleteVariant Lib "dbx32.dll" (Context As DbxContext, a_variant As TVariant) As Long
Declare Function TRenameVariant Lib "dbx32.dll" (Context As DbxContext, a_variant As TVariant) As Long
Declare Function TGetFirstVariant Lib "dbx32.dll" (Context As DbxContext, a_variant As TVariant) As Long
Declare Function TGetNextVariant Lib "dbx32.dll" (Context As DbxContext, a_variant As TVariant) As Long

Declare Function TCloseComponent Lib "dbx32.dll" (Context As DbxContext) As Long
Declare Function TCloseDesign Lib "dbx32.dll" (Context As DbxContext, ByVal designName As String) As Long
Declare Function TCloseLibrary Lib "dbx32.dll" (Context As DbxContext, ByVal pLibraryName As String) As Long

Declare Function TCopyComponent Lib "dbx32.dll" (Context As DbxContext, ByVal pSCompType As String, ByVal pSLibName As String, ByVal pDCompType As String, ByVal pDLibName As String) As Long
Declare Function TCopySymbol Lib "dbx32.dll" (Context As DbxContext, ByVal pSSymbolName As String, ByVal pSLibName As String, ByVal pDSymbolName As String, ByVal pDLibName As String) As Long
Declare Function TCopyPattern Lib "dbx32.dll" (Context As DbxContext, ByVal pSPatName As String, ByVal pSLibName As String, ByVal pDPatName As String, ByVal pDLibName As String) As Long

Declare Function TCreateClassToClass Lib "dbx32.dll" (Context As DbxContext, classToClass As TClassToClass) As Long
Declare Function TCreateNet Lib "dbx32.dll" (Context As DbxContext, net As TNet) As Long
Declare Function TCreateNetClass Lib "dbx32.dll" (Context As DbxContext, netClass As TNetClass) As Long

Declare Function TDeleteArc Lib "dbx32.dll" (Context As DbxContext, deleteItem As TArc) As Long
Declare Function TDeleteAttribute Lib "dbx32.dll" (Context As DbxContext, deleteItem As TAttribute) As Long
Declare Function TDeleteBus Lib "dbx32.dll" (Context As DbxContext, deleteItem As TBus) As Long
Declare Function TDeleteClassToClass Lib "dbx32.dll" (Context As DbxContext, deleteItem As TClassToClass) As Long
Declare Function TDeleteClassToClassAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, classToClassAttribute As TAttribute) As Long
Declare Function TDeleteClassToClassLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TDeleteCompAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, compAttribute As TAttribute) As Long
Declare Function TDeleteComponent Lib "dbx32.dll" (Context As DbxContext, deleteItem As TComponent) As Long
Declare Function TDeleteDetail Lib "dbx32.dll" (Context As DbxContext, deleteItem As TDetail) As Long  
Declare Function TDeleteDesignAttribute Lib "dbx32.dll" (Context As DbxContext, designAttr As TAttribute) As Long
Declare Function TDeleteDiagram Lib "dbx32.dll" (Context As DbxContext, deleteItem As TDiagram) As Long  
Declare Function TDeleteField Lib "dbx32.dll" (Context As DbxContext, deleteItem As TField) As Long
Declare Function TDeleteIncludedRoomComponent Lib "dbx32.dll" (Context As DbxContext, ByVal roomId As Long, component As TComponent) As Long
Declare Function TDeleteItem Lib "dbx32.dll" (Context As DbxContext, deleteItem As TItem) As Long
Declare Function TDeleteLayerAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal layerId As Long, layerAttr As TAttribute) As Long
Declare Function TDeleteLine Lib "dbx32.dll" (Context As DbxContext, deleteItem As TLine) As Long
Declare Function TDeleteMetaFile Lib "dbx32.dll" (Context As DbxContext, deleteItem As TMetaFile) As Long  
Declare Function TDeleteNet Lib "dbx32.dll" (Context As DbxContext, deleteItem As TNet) As Long
Declare Function TDeleteNetAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, netAttribute As TAttribute) As Long
Declare Function TDeleteNetClass Lib "dbx32.dll" (Context As DbxContext, deleteItem As TNetClass) As Long
Declare Function TDeleteNetClassAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, netClassAttribute As TAttribute) As Long
Declare Function TDeleteNetClassLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TDeleteNetClassNet Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, net As TNet) As Long
Declare Function TDeleteNetLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TDeleteNetNode Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, netNode As TItem) As Long
Declare Function TDeletePad Lib "dbx32.dll" (Context As DbxContext, deleteItem As TPad) As Long
Declare Function TDeletePin Lib "dbx32.dll" (Context As DbxContext, deleteItem As TPin) As Long
Declare Function TDeletePoint Lib "dbx32.dll" (Context As DbxContext, deleteItem As TPoint) As Long
Declare Function TDeletePort Lib "dbx32.dll" (Context As DbxContext, deleteItem As TPort) As Long
Declare Function TDeleteRoomAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal roomId As Long, roomAttr As TAttribute) As Long
Declare Function TDeleteSymbol Lib "dbx32.dll" (Context As DbxContext, deleteItem As TSymbol) As Long
Declare Function TDeleteTable Lib "dbx32.dll" (Context As DbxContext, deleteItem As TTable) As Long  
Declare Function TDeleteText Lib "dbx32.dll" (Context As DbxContext, deleteItem As TText) As Long
Declare Function TDeleteVia Lib "dbx32.dll" (Context As DbxContext, deleteItem As TVia) As Long
Declare Function TDeleteWire Lib "dbx32.dll" (Context As DbxContext, deleteItem As TWire) As Long

Declare Function TDeselectPrintJob Lib "dbx32.dll" (Context As DbxContext, ByVal jobName As String) As Long

Declare Function TFlipArc Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipArc As TArc) As Long
Declare Function TFlipAttribute Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipAttribute As TAttribute) As Long
Declare Function TFlipBus Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipItem As TBus) As Long
Declare Function TFlipComponent Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipComponent As TComponent) As Long
Declare Function TFlipField Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipField As TField) As Long
Declare Function TFlipItem Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipItem As TItem) As Long
Declare Function TFlipLine Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipLine As TLine) As Long
Declare Function TFlipPad Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipPad As TPad) As Long
Declare Function TFlipPin Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipPin As TPin) As Long
Declare Function TFlipPoint Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipPoint As TPoint) As Long
Declare Function TFlipPort Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipPort As TPort) As Long
Declare Function TFlipSymbol Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipSymbol As TSymbol) As Long
Declare Function TFlipTable Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipTable As TTable) As Long
Declare Function TFlipText Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipText As TText) As Long
Declare Function TFlipVia Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipVia As TVia) As Long
Declare Function TFlipWire Lib "dbx32.dll" (Context As DbxContext, flipCoord As TCoord, flipWire As TWire) As Long

Declare Function TGetClassToClassById Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, classToClass As TClassToClass) As Long
Declare Function TGetCompByRefDes Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, component As TComponent) As Long
Declare Function TGetCompByType Lib "dbx32.dll" (Context As DbxContext, ByVal pCompType As String, component As TComponent) As Long
Declare Function TGetCompSymbolByRefDes Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, symbol As TSymbol) As Long
Declare Function TGetCompSymbolByPartNumber Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, ByVal partnumber As Long, symbol As TSymbol) As Long
Declare Function TGetDesignInfo Lib "dbx32.dll" (Context As DbxContext, designInfo As TDesign) As Long

Declare Function TGetFirstBusNet Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, pTNet As TNet) As Long
Declare Function TGetFirstClassToClass Lib "dbx32.dll" (Context As DbxContext, classToClass As TClassToClass) As Long
Declare Function TGetFirstClassToClassAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, classToClassAttribute As TAttribute) As Long
Declare Function TGetFirstClassToClassLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TGetFirstClassToClassLayerRuleLayerName Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, pLayer As TLayer) As Long
Declare Function TGetFirstCompAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, compAttribute As TAttribute) As Long

Declare Function TGetFirstCompGraphic Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, compGraphic As TCompGraphic) As Long
Declare Function TGetNextCompGraphic Lib "dbx32.dll" (Context As DbxContext, compGraphic As TCompGraphic) As Long
Declare Function TGetCompGraphicByOrientation Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, ByVal orientation As Long, compGraphic As TCompGraphic) As Long
Declare Function TGetFirstCompGraphicPad Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, ByVal compGraphicName As String, graphicPad As TPad) As Long
Declare Function TGetFirstCompGraphicAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String,  ByVal compGraphicName As String, graphicAttribute As TAttribute) As Long
Declare Function TGetFirstCompGraphicItem Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, ByVal compGraphicName As String, graphicItem As TItem) As Long
Declare Function TGetNextCompGraphicPad Lib "dbx32.dll" (Context As DbxContext, graphicPad As TPad) As Long
Declare Function TGetNextCompGraphicAttribute Lib "dbx32.dll" (Context As DbxContext, graphicAttribute As TAttribute) As Long
Declare Function TGetNextCompGraphicItem Lib "dbx32.dll" (Context As DbxContext, graphicItem As TItem) As Long

Declare Function TGetFirstCompItem Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, compItem As TItem) As Long
Declare Function TGetFirstComponent Lib "dbx32.dll" (Context As DbxContext, component As TComponent) As Long
Declare Function TGetFirstCompPad Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, compPad As TPad) As Long
Declare Function TGetFirstCompPin Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, pin As TPin) As Long
Declare Function TGetFirstCompSymbol Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, symbol As TSymbol) As Long
Declare Function TGetFirstDesignAttribute Lib "dbx32.dll" (Context As DbxContext, designAttr As TAttribute) As Long
Declare Function TGetFirstGrid Lib "dbx32.dll" (Context As DbxContext, grid As TGrid) As Long
Declare Function TGetFirstIncludedRoomComponent Lib "dbx32.dll" (Context As DbxContext, ByVal roomId As Long, component As TComponent) As Long
Declare Function TGetFirstLayer Lib "dbx32.dll" (Context As DbxContext, layer As TLayer) As Long
Declare Function TGetFirstLayerAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal layerId As Long, layerAttr As TAttribute) As Long
Declare Function TGetFirstLayerItem Lib "dbx32.dll" (Context As DbxContext, ByVal layerId As Long, layerItem As TItem) As Long
Declare Function TGetFirstLayerStackup Lib "dbx32.dll" (Context As DbxContext, stackup As TLayerStackup) As Long
Declare Function TGetFirstNet Lib "dbx32.dll" (Context As DbxContext, net As TNet) As Long
Declare Function TGetFirstNetAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, netAttribute As TAttribute) As Long
Declare Function TGetFirstNetClass Lib "dbx32.dll" (Context As DbxContext, netClass As TNetClass) As Long
Declare Function TGetFirstNetClassAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, netClassAttribute As TAttribute) As Long
Declare Function TGetFirstNetClassLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TGetFirstNetClassLayerRuleLayerName Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, pLayer As TLayer) As Long
Declare Function TGetFirstNetClassNet Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, net As TNet) As Long
Declare Function TGetFirstNetItem Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, netItem As TItem) As Long
Declare Function TGetFirstNetLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TGetFirstNetLayerRuleLayerName Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, pLayer As TLayer) As Long
Declare Function TGetFirstNetNode Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, netNode As TItem) As Long
Declare Function TGetFirstPadStyle Lib "dbx32.dll" (Context As DbxContext, padStyle As TPadViaStyle) As Long
Declare Function TGetFirstPattern Lib "dbx32.dll" (Context As DbxContext, pattern As TPattern) As Long
Declare Function TGetFirstPolyPadPoint Lib "dbx32.dll" (Context As DbxContext, ByVal styleId As Long, ByVal layerNum as Long, polyPoint As TPoint) As Long
Declare Function TGetFirstPolyPoint Lib "dbx32.dll" (Context As DbxContext, ByVal polyId As Long, polyPoint As TPoint) As Long
Declare Function TGetFirstPrintJob Lib "dbx32.dll" (Context As DbxContext, printJob As TPrintJob) As Long
Declare Function TGetFirstRoom Lib "dbx32.dll" (Context As DbxContext, room As TRoom) As Long
Declare Function TGetFirstRoomAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal roomId As Long, roomAttr As TAttribute) As Long
Declare Function TGetFirstRoomPoint Lib "dbx32.dll" (Context As DbxContext, ByVal roomId As Long, roomPoint As TPoint) As Long
Declare Function TGetFirstSelectedItem Lib "dbx32.dll" (Context As DbxContext, selectItem As TItem) As Long
Declare Function TGetFirstSymAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal symRefDes As String, symAttribute As TAttribute) As Long
Declare Function TGetFirstSymbol Lib "dbx32.dll" (Context As DbxContext, symbol As TSymbol) As Long
Declare Function TGetFirstSymbolPin Lib "dbx32.dll" (Context As DbxContext, ByVal symbolRefDes As String, pin As TPin) As Long
Declare Function TGetFirstViaStyle Lib "dbx32.dll" (Context As DbxContext, viaStyle As TPadViaStyle) As Long

Declare Function TGetLayerById Lib "dbx32.dll" (Context As DbxContext, ByVal layerId As Long, layer As TLayer) As Long
Declare Function TGetLayerByName Lib "dbx32.dll" (Context As DbxContext, ByVal layerName As String, layer As TLayer) As Long
Declare Function TGetNetById Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, net As TNet) As Long
Declare Function TGetNetByName Lib "dbx32.dll" (Context As DbxContext, ByVal netName As String, net As TNet) As Long
Declare Function TGetNetClassByName Lib "dbx32.dll" (Context As DbxContext, ByVal netClassName As String, netClass As TNetClass) As Long
Declare Function TGetNetClassById Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, netClass As TNetClass) As Long

Declare Function TGetNextBusNet Lib "dbx32.dll" (Context As DbxContext, pTNet As TNet) As Long
Declare Function TGetNextClassToClass Lib "dbx32.dll" (Context As DbxContext, classToClass As TClassToClass) As Long
Declare Function TGetNextClassToClassAttribute Lib "dbx32.dll" (Context As DbxContext, classToClassAttribute As TAttribute) As Long
Declare Function TGetNextClassToClassLayerRule Lib "dbx32.dll" (Context As DbxContext, pAttr As TAttribute) As Long
Declare Function TGetNextClassToClassLayerRuleLayerName Lib "dbx32.dll" (Context As DbxContext, pLayer As TLayer) As Long
Declare Function TGetNextCompAttribute Lib "dbx32.dll" (Context As DbxContext, compAttribute As TAttribute) As Long
Declare Function TGetNextCompItem Lib "dbx32.dll" (Context As DbxContext, compItem As TItem) As Long
Declare Function TGetNextComponent Lib "dbx32.dll" (Context As DbxContext, component As TComponent) As Long
Declare Function TGetNextCompPad Lib "dbx32.dll" (Context As DbxContext, compPad As TPad) As Long
Declare Function TGetNextCompPin Lib "dbx32.dll" (Context As DbxContext, pin As TPin) As Long
Declare Function TGetNextCompSymbol Lib "dbx32.dll" (Context As DbxContext, symbol As TSymbol) As Long
Declare Function TGetNextDesignAttribute Lib "dbx32.dll" (Context As DbxContext, designAttr As TAttribute) As Long
Declare Function TGetNextGrid Lib "dbx32.dll" (Context As DbxContext, grid As TGrid) As Long
Declare Function TGetNextIncludedRoomComponent Lib "dbx32.dll" (Context As DbxContext, component As TComponent) As Long
Declare Function TGetNextLayer Lib "dbx32.dll" (Context As DbxContext, layer As TLayer) As Long
Declare Function TGetNextLayerAttribute Lib "dbx32.dll" (Context As DbxContext, layerAttr As TAttribute) As Long
Declare Function TGetNextLayerItem Lib "dbx32.dll" (Context As DbxContext, layerItem As TItem) As Long
Declare Function TGetNextLayerStackup Lib "dbx32.dll" (Context As DbxContext, stackup As TLayerStackup) As Long
Declare Function TGetNextNet Lib "dbx32.dll" (Context As DbxContext, net As TNet) As Long
Declare Function TGetNextNetAttribute Lib "dbx32.dll" (Context As DbxContext, netAttribute As TAttribute) As Long
Declare Function TGetNextNetClass Lib "dbx32.dll" (Context As DbxContext, netClass As TNetClass) As Long
Declare Function TGetNextNetClassAttribute Lib "dbx32.dll" (Context As DbxContext, netClassAttribute As TAttribute) As Long
Declare Function TGetNextNetClassNet Lib "dbx32.dll" (Context As DbxContext, net As TNet) As Long
Declare Function TGetNextNetClassLayerRule Lib "dbx32.dll" (Context As DbxContext, pAttr As TAttribute) As Long
Declare Function TGetNextNetClassLayerRuleLayerName Lib "dbx32.dll" (Context As DbxContext, pLayer As TLayer) As Long
Declare Function TGetNextNetItem Lib "dbx32.dll" (Context As DbxContext, netItem As TItem) As Long
Declare Function TGetNextNetLayerRule Lib "dbx32.dll" (Context As DbxContext, pAttr As TAttribute) As Long
Declare Function TGetNextNetLayerRuleLayerName Lib "dbx32.dll" (Context As DbxContext, pLayer As TLayer) As Long
Declare Function TGetNextNetNode Lib "dbx32.dll" (Context As DbxContext, netNode As TItem) As Long
Declare Function TGetNextPadStyle Lib "dbx32.dll" (Context As DbxContext, padStyle As TPadViaStyle) As Long
Declare Function TGetNextPattern Lib "dbx32.dll" (Context As DbxContext, pattern As TPattern) As Long
Declare Function TGetNextPolyPoint Lib "dbx32.dll" (Context As DbxContext, polyPoint As TPoint) As Long
Declare Function TGetNextPolyPadPoint Lib "dbx32.dll" (Context As DbxContext, polyPoint As TPoint) As Long
Declare Function TGetNextPrintJob Lib "dbx32.dll" (Context As DbxContext, printJob As TPrintJob) As Long
Declare Function TGetNextRoom Lib "dbx32.dll" (Context As DbxContext, room As TRoom) As Long
Declare Function TGetNextRoomAttribute Lib "dbx32.dll" (Context As DbxContext, roomAttr As TAttribute) As Long
Declare Function TGetNextRoomPoint Lib "dbx32.dll" (Context As DbxContext, roomPoint As TPoint) As Long
Declare Function TGetNextSelectedItem Lib "dbx32.dll" (Context As DbxContext, selectItem As TItem) As Long
Declare Function TGetNextSymAttribute Lib "dbx32.dll" (Context As DbxContext, symAttribute As TAttribute) As Long
Declare Function TGetNextSymbol Lib "dbx32.dll" (Context As DbxContext, symbol As TSymbol) As Long
Declare Function TGetNextSymbolPin Lib "dbx32.dll" (Context As DbxContext, pin As TPin) As Long
Declare Function TGetNextViaStyle Lib "dbx32.dll" (Context As DbxContext, viaStyle As TPadViaStyle) As Long

Declare Function TGetPadShapeByLayer Lib "dbx32.dll" (Context As DbxContext, ByVal padStyleId As Long, ByVal layerId As Long, padShape As TPadViaShape) As Long
Declare Function TGetPadStyle Lib "dbx32.dll" (Context As DbxContext, ByVal padStyleId As Long, padStyle As TPadViaStyle) As Long
Declare Function TGetPatternByName Lib "dbx32.dll" (Context As DbxContext, ByVal pPatternbName As String, pattern As TPattern) As Long
Declare Function TGetSymbolByName Lib "dbx32.dll" (Context As DbxContext, ByVal pSymbolName As String, symbol As TSymbol) As Long
Declare Function TGetTextStyle Lib "dbx32.dll" (Context As DbxContext, ByVal textStyleId As Long, textStyle As TTextStyle) As Long
Declare Function TGetViaShapeByLayer Lib "dbx32.dll" (Context As DbxContext, ByVal viaStyleId As Long, ByVal layerId As Long, viaShape As TPadViaShape) As Long
Declare Function TGetViaStyle Lib "dbx32.dll" (Context As DbxContext, ByVal viaStyleId As Long, viaStyle As TPadViaStyle) As Long

Declare Function THighlightArc Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TArc) As Long
Declare Function THighlightAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TAttribute) As Long
Declare Function THighlightBus Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TBus) As Long
Declare Function THighlightComponent Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TComponent) As Long
Declare Function THighlightDetail Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TDetail) As Long
Declare Function THighlightDiagram Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TDiagram) As Long
Declare Function THighlightField Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TField) As Long
Declare Function THighlightItem Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TItem) As Long
Declare Function THighlightLine Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TLine) As Long
Declare Function THighlightMetaFile Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TMetaFile) As Long
Declare Function THighlightNet Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightNet As TNet) As Long
Declare Function THighlightPad Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TPad) As Long
Declare Function THighlightPin Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TPin) As Long
Declare Function THighlightPoint Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TPoint) As Long
Declare Function THighlightPort Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TPort) As Long
Declare Function THighlightRoom Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, room As TRoom) As Long
Declare Function THighlightSymbol Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TSymbol) As Long
Declare Function THighlightTable Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long,highlightItem As TTable) As Long
Declare Function THighlightText Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TText) As Long
Declare Function THighlightVia Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TVia) As Long
Declare Function THighlightWire Lib "dbx32.dll" (Context As DbxContext, ByVal highlightColor As Long, highlightItem As TWire) As Long

Declare Function TModifyArc Lib "dbx32.dll" (Context As DbxContext, modifyItem As TArc) As Long
Declare Function TModifyAttribute Lib "dbx32.dll" (Context As DbxContext, modifyItem As TAttribute) As Long
Declare Function TModifyBus Lib "dbx32.dll" (Context As DbxContext, modifyItem As TBus) As Long
Declare Function TModifyClassToClassAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, classToClassAttribute As TAttribute) As Long
Declare Function TModifyClassToClassLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId1 As Long, ByVal netClassId2 As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TModifyCompAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal compRefDes As String, compAttribute As TAttribute) As Long
Declare Function TModifyComponent Lib "dbx32.dll" (Context As DbxContext, modifyItem As TComponent) As Long
Declare Function TModifyDesignAttribute Lib "dbx32.dll" (Context As DbxContext, designAttr As TAttribute) As Long
Declare Function TModifyDesignInfo Lib "dbx32.dll" (Context As DbxContext, designInfo As TDesign) As Long
Declare Function TModifyField Lib "dbx32.dll" (Context As DbxContext, modifyItem As TField) As Long
Declare Function TModifyItem Lib "dbx32.dll" (Context As DbxContext, modifyItem As TItem) As Long
Declare Function TModifyLayerAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal layerId As Long, layerAttr As TAttribute) As Long
Declare Function TModifyLine Lib "dbx32.dll" (Context As DbxContext, modifyItem As TLine) As Long
Declare Function TModifyNet Lib "dbx32.dll" (Context As DbxContext, modifyItem As TNet) As Long
Declare Function TModifyNetAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, netAttribute As TAttribute) As Long
Declare Function TModifyNetClass Lib "dbx32.dll" (Context As DbxContext, modifyItem As TNetClass) As Long
Declare Function TModifyNetClassAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, netClassAttribute As TAttribute) As Long
Declare Function TModifyNetClassLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netClassId As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TModifyNetLayerRule Lib "dbx32.dll" (Context As DbxContext, ByVal netId As Long, ByVal layerName As String, pAttr As TAttribute) As Long
Declare Function TModifyPad Lib "dbx32.dll" (Context As DbxContext, modifyItem As TPad) As Long
Declare Function TModifyPin Lib "dbx32.dll" (Context As DbxContext, modifyItem As TPin) As Long
Declare Function TModifyPoint Lib "dbx32.dll" (Context As DbxContext, modifyItem As TPoint) As Long
Declare Function TModifyPort Lib "dbx32.dll" (Context As DbxContext, modifyItem As TPort) As Long
Declare Function TModifyPrintJob Lib "dbx32.dll" (Context As DbxContext, printJob As TPrintJob) As Long
Declare Function TModifyRoom Lib "dbx32.dll" (Context As DbxContext, room As TRoom) As Long
Declare Function TModifyRoomAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal roomId As Long, roomAttr As TAttribute) As Long
Declare Function TModifySymbol Lib "dbx32.dll" (Context As DbxContext, modifyItem As TSymbol) As Long
Declare Function TModifySymbolAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal symbRefDes As String, attr As TAttribute) As Long
Declare Function TModifyText Lib "dbx32.dll" (Context As DbxContext, modifyItem As TText) As Long
Declare Function TModifyVia Lib "dbx32.dll" (Context As DbxContext, modifyItem As TVia) As Long
Declare Function TModifyWire Lib "dbx32.dll" (Context As DbxContext, modifyItem As TWire) As Long

Declare Function TMoveArc Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveArc As TArc) As Long
Declare Function TMoveAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveAttribute As TAttribute) As Long
Declare Function TMoveBus Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveBus As TBus) As Long
Declare Function TMoveComponent Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveComponent As TComponent) As Long
Declare Function TMoveDetail Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long,moveDetail As TDetail) As Long
Declare Function TMoveDiagram Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long,moveDiagram As TDiagram) As Long
Declare Function TMoveField Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveLine As TField) As Long
Declare Function TMoveLine Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveLine As TLine) As Long
Declare Function TMoveMetaFile Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long,moveMetaFile As TMetaFile) As Long
Declare Function TMovePad Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, movePad As TPad) As Long
Declare Function TMovePin Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, movePin As TPin) As Long
Declare Function TMovePoint Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, movePoint As TPoint) As Long
Declare Function TMovePort Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, movePort As TPort) As Long
Declare Function TMoveSymbol Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveSymbol As TSymbol) As Long
Declare Function TMoveText Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveText As TText) As Long
Declare Function TMoveVia Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveVia As TVia) As Long
Declare Function TMoveWire Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveWire As TWire) As Long
Declare Function TMoveItem Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long, moveItem As TItem) As Long
Declare Function TMoveTable Lib "dbx32.dll" (Context As DbxContext, ByVal incx As Long, ByVal incy As Long,moveTable As TTable) As Long

Declare Function TOpenDesign Lib "dbx32.dll" (ByVal language As Long, ByVal version As Long, ByVal designName As String, Context As DbxContext) As Long

Declare Function TOpenLibrary Lib "dbx32.dll" (ByVal language As Long, ByVal version As Long, ByVal designName As String, Context As DbxContext) As Long
Declare Function TOpenComponent Lib "dbx32.dll" (Context As DbxContext, ByVal pCompName As String) As Long

Declare Function TOutputPrintJobByName Lib "dbx32.dll" (Context As DbxContext, ByVal jobName As String) As Long
Declare Function TOutputSelectedPrintJobs Lib "dbx32.dll" (Context As DbxContext) As Long

Declare Function TPlaceArc Lib "dbx32.dll" (Context As DbxContext, placeItem As TArc) As Long
Declare Function TPlaceAttribute Lib "dbx32.dll" (Context As DbxContext, placeItem As TAttribute) As Long
Declare Function TPlaceBus Lib "dbx32.dll" (Context As DbxContext, placeItem As TBus) As Long
Declare Function TPlaceComponent Lib "dbx32.dll" (Context As DbxContext, placeItem As TComponent) As Long
Declare Function TPlaceField Lib "dbx32.dll" (Context As DbxContext, placeItem As TField) As Long
Declare Function TPlaceLine Lib "dbx32.dll" (Context As DbxContext, placeItem As TLine) As Long
Declare Function TPlacePad Lib "dbx32.dll" (Context As DbxContext, placeItem As TPad) As Long
Declare Function TPlacePin Lib "dbx32.dll" (Context As DbxContext, placeItem As TPin) As Long
Declare Function TPlacePoint Lib "dbx32.dll" (Context As DbxContext, placeItem As TPoint) As Long
Declare Function TPlacePort Lib "dbx32.dll" (Context As DbxContext, placeItem As TPort) As Long
Declare Function TPlaceSymbol Lib "dbx32.dll" (Context As DbxContext, placeItem As TSymbol) As Long
Declare Function TPlaceText Lib "dbx32.dll" (Context As DbxContext, placeItem As TText) As Long
Declare Function TPlaceVia Lib "dbx32.dll" (Context As DbxContext, placeItem As TVia) As Long
Declare Function TPlaceWire Lib "dbx32.dll" (Context As DbxContext, placeItem As TWire) As Long

Declare Function TRotateArc Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotArc As TArc) As Long
Declare Function TRotateAttribute Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotAttribute As TAttribute) As Long
Declare Function TRotateBus Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotBus As TBus) As Long
Declare Function TRotateComponent Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotComponent As TComponent) As Long
Declare Function TRotateField Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotLine As TField) As Long
Declare Function TRotateItem Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotateItem As TItem) As Long
Declare Function TRotateLine Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotLine As TLine) As Long
Declare Function TRotatePad Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotPad As TPad) As Long
Declare Function TRotatePin Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotPin As TPin) As Long
Declare Function TRotatePort Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotPort As TPort) As Long
Declare Function TRotateSymbol Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotSymbol As TSymbol) As Long
Declare Function TRotateTable Lib "dbx32.dll" (Context As DbxContext,ByVal rotation As Long, rotCoord As TCoord, rotateTable As TTable) As Long
Declare Function TRotateText Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotText As TText) As Long
Declare Function TRotateVia Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotVia As TVia) As Long
Declare Function TRotateWire Lib "dbx32.dll" (Context As DbxContext, ByVal rotation As Long, rotCoord As TCoord, rotWire As TWire) As Long

Declare Function TSaveComponent Lib "dbx32.dll" (Context As DbxContext) As Long
Declare Function TSaveDesign Lib "dbx32.dll" (Context As DbxContext) As Long

Declare Function TSelectAllPrintJobs Lib "dbx32.dll" (Context As DbxContext) As Long
Declare Function TSelectPrintJob Lib "dbx32.dll" (Context As DbxContext, ByVal jobName As String) As Long

Declare Function TUnFixAll Lib "dbx32.dll" (Context As DbxContext) As Long

Declare Function TUnHighlightAll Lib "dbx32.dll" (Context As DbxContext) As Long

Declare Function TUnHighlightArc Lib "dbx32.dll" (Context As DbxContext, highlightItem As TArc) As Long
Declare Function TUnHighlightAttribute Lib "dbx32.dll" (Context As DbxContext, highlightItem As TAttribute) As Long
Declare Function TUnHighlightBus Lib "dbx32.dll" (Context As DbxContext, highlightItem As TBus) As Long
Declare Function TUnHighlightComponent Lib "dbx32.dll" (Context As DbxContext, highlightItem As TComponent) As Long
Declare Function TUnHighlightDetail Lib "dbx32.dll" (Context As DbxContext, highlightItem As TDetail) As Long
Declare Function TUnHighlightDiagram Lib "dbx32.dll" (Context As DbxContext, highlightItem As TDiagram) As Long
Declare Function TUnHighlightField Lib "dbx32.dll" (Context As DbxContext, highlightItem As TField) As Long
Declare Function TUnHighlightItem Lib "dbx32.dll" (Context As DbxContext, highlightItem As TItem) As Long
Declare Function TUnHighlightLine Lib "dbx32.dll" (Context As DbxContext, highlightItem As TLine) As Long
Declare Function TUnHighlightMetaFile Lib "dbx32.dll" (Context As DbxContext, highlightItem As TMetaFile) As Long
Declare Function TUnHighlightNet Lib "dbx32.dll" (Context As DbxContext, highlightNet As TNet) As Long
Declare Function TUnHighlightPad Lib "dbx32.dll" (Context As DbxContext, highlightItem As TPad) As Long
Declare Function TUnHighlightPin Lib "dbx32.dll" (Context As DbxContext, highlightItem As TPin) As Long
Declare Function TUnHighlightPoint Lib "dbx32.dll" (Context As DbxContext, highlightItem As TPoint) As Long
Declare Function TUnHighlightPort Lib "dbx32.dll" (Context As DbxContext, highlightItem As TPort) As Long
Declare Function TUnHighlightRoom Lib "dbx32.dll" (Context As DbxContext, room As TRoom) As Long
Declare Function TUnHighlightSymbol Lib "dbx32.dll" (Context As DbxContext, highlightItem As TSymbol) As Long
Declare Function TUnHighlightTable Lib "dbx32.dll" (Context As DbxContext, highlightItem As TTable) As Long
Declare Function TUnHighlightText Lib "dbx32.dll" (Context As DbxContext, highlightItem As TText) As Long
Declare Function TUnHighlightVia Lib "dbx32.dll" (Context As DbxContext, highlightItem As TVia) As Long
Declare Function TUnHighlightWire Lib "dbx32.dll" (Context As DbxContext, highlightItem As TWire) As Long

Declare Function TCreatePadStyle Lib "dbx32.dll" (Context As DbxContext, ByVal fromId as Long, ByVal styleName As String, padStyle As TPadViaStyle) As Long
Declare Function TDeletePadStyle Lib "dbx32.dll" (Context As DbxContext, ByVal padStyleId as Long) As Long
Declare Function TAddPadShape Lib "dbx32.dll" (Context As DbxContext, ByVal padStyleId as Long, padShape As TPadViaShape) As Long
Declare Function TAddPadRegularPolyShape Lib "dbx32.dll" (Context As DbxContext, ByVal padStyleId as Long, regPolyPadShape As TPadViaRegularPolyShape) As Long
Declare Function TAddPadIrregularPolyShape Lib "dbx32.dll" (ByRef Context As DbxContext, ByVal viaStyleId As Long, ByVal layerId As Long, ByVal layerType As Long, ByVal isPourNoConn As Long, ByVal numberOfPoints As Long, ByRef pPoint As TCoord) As Long
Declare Function TDeletePadShape Lib "dbx32.dll" (Context As DbxContext, ByVal padStyleId as Long, ByVal layerId As Long) As Long

Declare Function TCreateViaStyle Lib "dbx32.dll" (Context As DbxContext, ByVal fromId as Long, ByVal styleName As String, viaStyle As TPadViaStyle) As Long
Declare Function TDeleteViaStyle Lib "dbx32.dll" (Context As DbxContext, ByVal viaStyleId as Long) As Long
Declare Function TAddViaShape Lib "dbx32.dll" (Context As DbxContext, ByVal viaStyleId as Long, viaShape As TPadViaShape) As Long
Declare Function TAddViaRegularPolyShape Lib "dbx32.dll" (Context As DbxContext, ByVal viaStyleId as Long, regPolyViaShape As TPadViaRegularPolyShape) As Long
Declare Function TAddViaIrregularPolyShape Lib "dbx32.dll" (ByRef Context As DbxContext, ByVal viaStyleId As Long, ByVal layerId As Long, ByVal layerType As Long, ByVal isPourNoConn As Long, ByVal numberOfPoints As Long, ByRef pPoint As TCoord) As Long
Declare Function TDeleteViaShape Lib "dbx32.dll" (Context As DbxContext, ByVal viaStyleId as Long, ByVal layerId As Long) As Long

Declare Function TAddTextStyle Lib "dbx32.dll" (Context As DbxContext, ByVal fromId As Long, textStyle As TTextStyle) As Long
Declare Function TDeleteTextStyle Lib "dbx32.dll" (Context As DbxContext, ByVal styleId As Long) As Long
Declare Function TModifyTextStyle Lib "dbx32.dll" (Context As DbxContext, textStyle As TTextStyle) As Long

Global tContext As DbxContext
Global tStatus As Long
Global Unit As Integer
