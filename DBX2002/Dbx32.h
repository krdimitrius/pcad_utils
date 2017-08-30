//////////////////////////////////////////////////////////////////////////////
//                                                                          
//    name:     Dbx32.h
//
//    abstract: These are the data structures and API used for dbx communication
//              between user C/VB programs and PCB.
//
//    author:   Steve Smith
//              Ported 12.1 to Win32 by Nick Choate.
//
//    $Header: /P-CAD 2002/AccelEDA/cmn/Dbx32.h 5     28/09/02 10:05a Rolson $
//                                                                          
//                           PROPRIETARY MATERIALS                          
//                                                                          
//     ACCEL Technologies, Inc. (ATI) has prepared this material for use    
//     by ATI personnel, licensees, and customers.  The information con-    
//     tained herein  is the property of ATI and shall not be reproduced    
//     in whole or part without ATI prior written approval.                 
//                                                                          
//                                                                          
//                          RESTRICTED RIGHTS LEGEND                        
//                                                                          
//     Use, duplication  or disclosure  by the  Government is subject to    
//     restrictions as set forth in subdivision (b)(3)(ii) of the Rights    
//     in Technical Data and Computer Software clause at 52.227-7013.       
//                                                                          
//                          Copyright (c) 1991-1998
//                          ACCEL Technologies, Inc.                        
//                            6825 Flanders Drive                           
//                            San Diego, CA 92121                           
//                               (619) 554-1000                             
//                                                                          
//////////////////////////////////////////////////////////////////////////////
#ifndef DBX32_H
#define DBX32_H

//#include "StdAfx.h"

#include <string.h>
#include <ddeml.h>

//
//  The following are interface constants used to define error messages,
//  array sizes, object types, and various design data.  These values MUST
//  NOT BE MODIFIED by the user or by user programs or results may be
//  undefined, including design data corruption.
//


//
//     Boolean Constants
//
#define DBX_FALSE                   0
#define DBX_TRUE                    1


//
//     String Lengths
//
#define DBX_MAX_NAME_LEN            100     //  Name variables                
#define DBX_MAX_TYPE_LEN            100     //  Type attributes
#define DBX_MAX_VALUE_LEN           100     //  Value attributes
#define DBX_MAX_TEXTITEM_LEN        256     //  Text Items
#define DBX_MAX_ATTRIBUTE_LEN       256     //  Attribute Values
#define DBX_MAX_FILENAME_LEN        256     //  Filenames
#define DBX_MAX_GRIDSPACING_LEN     256     //  Grid spacing
#define DBX_MAX_FORMULA_LEN         512     //  Formula, comment in TAttribute

#define DBX_NUM_LAYER_VALS_TO_SET     6     //  Number of fields to set in TLayer during call to ModifyLayer


//
//     Fatal Errors
//
#define DBX_CONNECTION_ERROR        32001
#define DBX_DISCONNECT_ERROR        32002
#define DBX_BAD_SERVER_DATA         32003
#define DBX_SERVER_ERROR            32004
#define DBX_FATAL_ERROR             32005
#define DBX_VERSION_INCOMPATIBLE    32006
#define DBX_CLIENT_ERROR            32007
#define DBX_SECURITY_ERROR          32008  

#define DBX_FLIP_ERROR              32009  // 32009-32016 new for V12.0
#define DBX_ROTATE_ERROR            32010
#define DBX_MOVE_ERROR              32011
#define DBX_HIGHLIGHT_ERROR         32012
#define DBX_DELETE_ERROR            32013
#define DBX_MODIFY_ERROR            32014
#define DBX_CREATE_ERROR            32015
#define DBX_DATABASE_ERROR          32016


//
//     Status Return Values - Normal return values indicating 
//  success or failure due to normal run-time conditions
//
#define DBX_OK                      0

#define DBX_INVALID_CONV_HANDLE     32101
#define DBX_SERVER_TERMINATED       32102
#define DBX_LOW_MEMORY              32103
#define DBX_ALREADY_CONNECTED       32104
#define DBX_NO_CONNECTION           32105
#define DBX_SERVER_BUSY             32106  

#define DBX_ILLEGAL_OP              32121
#define DBX_BAD_INPUT               32122
#define DBX_ARRAY_TOO_SMALL         32123
#define DBX_INVALID_ITEM_ID         32124   

#define DBX_ITEM_NOT_FOUND          32141   
#define DBX_ITEM_NOT_SUPPORTED      32142   
#define DBX_ILLEGAL_ITEM            32143
#define DBX_SHAPE_NOT_DEFINED       32144
#define DBX_GETFIRST_NOT_CALLED     32145
#define DBX_GETCOMP_NOT_CALLED      32146
#define DBX_GETNET_NOT_CALLED       32147


#define DBX_NO_MORE_LAYERS          32161
#define DBX_NO_MORE_NETS            32162   
#define DBX_NO_MORE_ITEMS           32163   
#define DBX_NO_MORE_NETCLASSES      32164   
#define DBX_NO_MORE_CLASSTOCLASSES  32165  // New for v14.0 
#define DBX_NO_MORE_ROOMS           32166  // New for v14.0 
#define DBX_NO_MORE_ROOMPOINTS      32167  // New for v14.0 
#define DBX_NO_MORE_COMPONENTS      32168  // New for v14.0 

#define DBX_INVALID_ANGLE           32170  // New for V12.0
#define DBX_INVALID_HIGHLIGHT_COLOR 32171
#define DBX_INVALID_ITEM_TYPE       32172
#define DBX_INVALID_JUSTIFICATION   32173
#define DBX_INVALID_LAYER           32174
#define DBX_INVALID_LOCATION        32175  
#define DBX_INVALID_NET_ID          32176
#define DBX_INVALID_NETNAME         32177
#define DBX_INVALID_PADSTYLE        32178
#define DBX_INVALID_PIN_NUMBER      32279
#define DBX_INVALID_RADIUS          32180
#define DBX_INVALID_REFDES          32181
#define DBX_INVALID_ROTATION_ANGLE  32182
#define DBX_INVALID_TEXTSTYLE       32183
#define DBX_INVALID_WIDTH           32184
#define DBX_INVALID_LAYERNAME       32185
#define DBX_INVALID_COMPNAME        32186
#define DBX_NOT_SAME_NUM_PARTS      32187  // New for 13.0
#define DBX_NOT_SAME_NUM_PINS       32188  // New for 13.0
#define DBX_NOT_SAME_COMP_TYPE      32189  // New for 13.0
#define DBX_NOT_SAME_HETERO         32190  // New for 13.0
#define DBX_INVALID_LINESTYLE       32191
#define DBX_INVALID_PINLENGTH       32192
#define DBX_INVALID_PINSTYLE        32193
#define DBX_INVALID_ALTTYPE         32194
#define DBX_INVALID_NETCLASSNAME    32195  // New for v14.0
#define DBX_INVALID_CLASSTOCLASSID  32196  // New for v14.0
#define DBX_INVALID_NETCLASS_ID     32197  // New for v14.0
#define DBX_INVALID_LAYER_ID        32198  // New for v14.0
#define DBX_INVALID_ROOMNAME        32199  // New for v14.0
#define DBX_INVALID_ATTRIBUTE_VALUE 32200
#define DBX_INVALID_ATTRIBUTE_NAME  32201

#define DBX_DUPLICATE_ATTRIBUTE     32205
#define DBX_DUPLICATE_NETNAME       32206
#define DBX_DUPLICATE_NETCLASSNAME  32207  // New for v14.0
#define DBX_DUPLICATE_CLASSTOCLASSNAME 32208  // New for v14.0
#define DBX_DUPLICATE_REFDES        32209

#define DBX_COMPONENT_NOT_FOUND     32215
#define DBX_LAYER_NOT_FOUND         32216
#define DBX_NET_NOT_FOUND           32217
#define DBX_NET_NOT_EMPTY           32218
#define DBX_NET_EXISTS              32219
#define DBX_NET_CONFLICT            32220
#define DBX_NETCLASS_NOT_FOUND      32221  // New for v14.0
#define DBX_NETCLASS_NOT_EMPTY      32222
#define DBX_NETCLASS_EXISTS         32223
#define DBX_CLASSTOCLASS_NOT_FOUND  32224
#define DBX_ROOM_NOT_FOUND          32225
#define DBX_POINT_NOT_FOUND         32226

#define DBX_COMP_CACHE_CONFLICT     32230
#define DBX_LIBRARY_NOT_OPEN        32231
#define DBX_ITEM_OUTSIDE_WORKSPACE  32232     
#define DBX_NO_ATTACHED_PATTERN     32233
#define DBX_TOO_FEW_PINS            32234
#define DBX_PINDES_NOT_FOUND        32235
#define DBX_NAME_TOO_LONG           32236

#define DBX_PRINT_JOB_NOT_FOUND     32237
#define DBX_NO_PRINT_JOBS_SELECTED  32238
#define DBX_FILE_OPEN_FAILURE       32239


//
// For Library Manager
//
#define DBX_INVALID_LIBRARY_NAME    32250
#define DBX_LIBRARY_CANT_OPEN       32251
#define DBX_COMP_ALREADY_OPEN       32252
#define DBX_OPENCOMP_NOT_CALLED     32253
#define DBX_SAVECOMP_FAILED         32254
#define DBX_LIBRARY_READ_ONLY       32255
#define DBX_SAVESYMBOL_FAILED       32256
#define DBX_SAVEPATTERN_FAILED      32257


//
// Internal Parameter Error
//
#define DBX_INTERNAL_PARAMETER_ERROR 32258


//
//     Interface Description
//
#define DBX_VERSION                 16000   // Currently working on 16.000 
#define DBX_LANGUAGE                0


//
//  Item Types: Returned in TItem.itemType
//
#define DBX_PAD                     3       //  Component Pad 
#define DBX_VIA                     4       //  Via
#define DBX_LINE                    5       //  Line  
                                            //  Routed Connection 
                                            //  Mitered Line 
#define DBX_FROM_TO                 6       //  Unrouted Net Conn. 
#define DBX_ARC                     7       //  Arc 
                                            //  Ortho 90/90 Arc
                                            //  90 Arc Miter 
#define DBX_POLYGON                 8       //  Filled Polygon
#define DBX_COMPONENT               9       //  Component
#define DBX_COPPERPOUR              11      //  Copper Pour

#define DBX_TEXT                    13      //  Text
#define DBX_ATTR                    14      //  Attribute
#define DBX_FIELD                   15      //  Field
#define DBX_REFPOINT                16      //  Ref Point
#define DBX_GLUEPOINT               17      //  Glue Dot Point
#define DBX_PICKPOINT               18      //  Pick and Place Pt.
#define DBX_PATTERN                 19
#define DBX_LINE_KEEPOUT            20      //  Line Keepout
#define DBX_POLY_KEEPOUT            21      //  Polygon Keepout

#define DBX_PAD_STYLE               24      //  Pad Style
#define DBX_VIA_STYLE               25      //  Via Style
#define DBX_TEXT_STYLE              26      //  Text Style
#define DBX_KEEPOUT                 27      //     
#define DBX_COMP_PIN                28      //  Component pin
#define DBX_POLY_CUTOUT             29      //  Cutout Polygon

#define DBX_LAYER                   33      //  Layer, sheet

#define DBX_SYMBOL                  35      //  Symbol
#define DBX_NET                     36      //  Net

#define DBX_PIN                     39      //  Pin
#define DBX_INFOPOINT               40      //  Info Point

#define DBX_WIRE                    44      //  Sch field item
#define DBX_BUS                     45      //  Sch field item

#define DBX_PORT                    50      //  Sch net port
#define DBX_POLY_PLANE              51      //  Pcb plane

#define DBX_NETCLASS                54      //  NetClass

#define DBX_TABLE                   58
#define DBX_METAFILE                59

#define DBX_DIAGRAM                 66
#define DBX_DETAIL                  67
#define DBX_CLASSTOCLASS            68      //  ClassToClass
#define DBX_ROOM                    69
#define DBX_GRID                    70

#define DBX_DESIGNVIEW              74
#define DBX_TESTPOINT               75
#define DBX_COMP_GRAPHIC            76


#define DBX_COORDINATE              901     //  Coordinate Point 
                                            //  for Polygon and 
                                            //  Pour Outlines
#define DBX_PADVIA_SHAPE            902     //  Shape Description
                                            //  for Pads and Vias
#define DBX_DESIGN_INFO             903     //  Design Information
                                            //
#define DBX_POINT                   904     //  Point for Room boundaries
                                            //
#define DBX_PRINT_JOB               905     //  Print job


//
//  Text Justifications: Returned in TText.justPoint 
//
#define DBX_JUSTIFY_TOP          9   //  UL-----T-----UR 
#define DBX_JUSTIFY_BOTTOM       1   //  |      |      |
#define DBX_JUSTIFY_LEFT         4   //  L------C------R  
#define DBX_JUSTIFY_RIGHT        6   //  |      |      |
#define DBX_JUSTIFY_CENTER       5   //  LL-----B-----LR  
#define DBX_JUSTIFY_LOWER_LEFT   0   //
#define DBX_JUSTIFY_LOWER_RIGHT  2   //  TangoFont defines LL as 
#define DBX_JUSTIFY_UPPER_LEFT   8   //  the Ref Point.  
#define DBX_JUSTIFY_UPPER_RIGHT  10  //  


//
// Font Types:  Returned in TTextStyle.fontType
//
#define DBX_FONT_WINSTROKE       1
#define DBX_FONT_OUTLINE         2
#define DBX_FONT_STROKE          3
#define DBX_FONT_TRUE_TYPE       4


//
//  Layer Types: Returned in TLayer.layerType
//
#define DBX_LAYERTYPE_UNDEFINED -1   //  Used by GetPadShapeByLayer
                                     //  if the layer doesn't exist
#define DBX_LAYERTYPE_SIGNAL     0   //  Layer Type: Signal
#define DBX_LAYERTYPE_PLANE      1   //  Layer Type: Plane
#define DBX_LAYERTYPE_NON_SIGNAL 2   //  Layer Type: Non Signal


//
//  Pre-defined Layers
//
#define DBX_LAYER_MULTI          0   // "Multi-Layer', used for comps, pads, etc.            
#define DBX_LAYER_TOP_SIGNAL     1      
#define DBX_LAYER_BOTTOM_SIGNAL  2    
#define DBX_LAYER_BOARD          3          
#define DBX_LAYER_TOP_MASK       4         
#define DBX_LAYER_BOTTOM_MASK    5      
#define DBX_LAYER_TOP_SILK       6         
#define DBX_LAYER_BOTTOM_SILK    7      
#define DBX_LAYER_TOP_PASTE      8         
#define DBX_LAYER_BOTTOM_PASTE   9     
#define DBX_LAYER_TOP_ASSY      10         
#define DBX_LAYER_BOTTOM_ASSY   11      


//
//  Layer Bias: Returned in TLayer.layerBias
//
#define DBX_LAYERBIAS_AUTO       0   //  AutoRouter Bias: Automatic
#define DBX_LAYERBIAS_HORIZ      1   //  AutoRouter Bias: Horizontal
#define DBX_LAYERBIAS_VERT       2   //  AutoRouter Bias: Vertical


//
//  Pour Thermals: Returned in TPour.thermalType
//
#define DBX_POUR_THERMAL_NONE    0   //  Pour Thermals: None
#define DBX_POUR_THERMAL_45      1   //  Pour Thermals: 45 degree
#define DBX_POUR_THERMAL_90      2   //  Pour Thermals: 90 degree


//
//  Pour Patterns: Returned in TPour.pourType
//
#define DBX_POUR_SOLID           0   //  Pour Pattern: Solid
#define DBX_POUR_HORIZ           1   //  Pour Pattern: Horizontal
#define DBX_POUR_VERT            2   //  Pour Pattern: Vertical
#define DBX_POUR_HATCH45         3   //  Pour Pattern: 45 deg Cross
#define DBX_POUR_HATCH90         4   //  Pour Pattern: 90 deg Cross


//
//    Pad and Via Shapes: Returned in TPadViaShape.shape
//
#define DBX_SHAPE_ELLIPSE        0   //  Elliptical, Circular
#define DBX_SHAPE_OVAL           1   //  Oval
#define DBX_SHAPE_RECT           2   //  "Square" Rectangle
#define DBX_SHAPE_RND_RECT       3   //  "Rounded" Rectangle
#define DBX_SHAPE_THRM_2         4   //  "Two Spoke" Thermal
#define DBX_SHAPE_THRM_2_90      5   //  "Two Spoke With 90 
                                     //   Rotation" Thermal
#define DBX_SHAPE_THRM_4         6   //  "Four Spoke" Thermal
#define DBX_SHAPE_THRM_4_45      7   //  "Four Spoke With 45 
                                     //  Rotation" Thermal
#define DBX_SHAPE_DIRECT         8   //  Direct Plane Connect
#define DBX_SHAPE_TARGET         9   //  Registration Target 
                                     //  (Not Used for Vias)
#define DBX_SHAPE_MT_HOLE        10  //  Mounting Hole 
                                     //  (Not Used for Vias)
#define DBX_SHAPE_POLYGON        11  //  Polygonal
#define DBX_SHAPE_NOCONNECT      12  //  Disconnect (plane layers)


//
//    Pin Electrical Types: Returned in TPad.pinType
//
#define DBX_PIN_ETYPE_UNKNOWN    0   //  Elec. Type: Unknown
#define DBX_PIN_ETYPE_PASSIVE    1   //  Elec. Type: Passive
#define DBX_PIN_ETYPE_INPUT      2   //  Elec. Type: Input
#define DBX_PIN_ETYPE_OUTPUT     3   //  Elec. Type: Output
#define DBX_PIN_ETYPE_BIDIRECT   4   //  Elec. Type: Bidirectional
#define DBX_PIN_ETYPE_OPEN_H     5   //  Elec. Type: Open-H
#define DBX_PIN_ETYPE_OPEN_L     6   //  Elec. Type: Open-L
#define DBX_PIN_ETYPE_PASS_H     7   //  Elec. Type: Passive-H
#define DBX_PIN_ETYPE_PASS_L     8   //  Elec. Type: Passive-L
#define DBX_PIN_ETYPE_3STATE     9   //  Elec. Type: 3-State
#define DBX_PIN_ETYPE_POWER     10  //  Elec. Type: Power


//
//    Port Types: Returned in TPort.portType
//
#define DBX_PORT_NOANGLE_SGL_VERT    1 
#define DBX_PORT_NOANGLE_SGL_HORZ    2 
#define DBX_PORT_LEFTANGLE_SGL_VERT  3 
#define DBX_PORT_LEFTANGLE_SGL_HORZ  4 
#define DBX_PORT_RIGHTANGLE_SGL_VERT 5 
#define DBX_PORT_RIGHTANGLE_SGL_HORZ 6 
#define DBX_PORT_BOTHANGLE_SGL_VERT  7 
#define DBX_PORT_BOTHANGLE_SGL_HORZ  8 
#define DBX_PORT_NOANGLE_DBL_VERT    9 
#define DBX_PORT_NOANGLE_DBL_HORZ    10 
#define DBX_PORT_LEFTANGLE_DBL_VERT  11 
#define DBX_PORT_LEFTANGLE_DBL_HORZ  12 
#define DBX_PORT_RIGHTANGLE_DBL_VERT 13 
#define DBX_PORT_RIGHTANGLE_DBL_HORZ 14 
#define DBX_PORT_BOTHANGLE_DBL_VERT  15 
#define DBX_PORT_BOTHANGLE_DBL_HORZ  16 
#define DBX_PORT_VERTLINE_SGL_VERT   17 
#define DBX_PORT_VERTLINE_SGL_HORZ   18 
#define DBX_PORT_NOOUTLINE_SGL_VERT  19
#define DBX_PORT_NOOUTLINE_SGL_HORZ  20
#define DBX_PORT_VERTLINE_DBL_VERT   21 
#define DBX_PORT_VERTLINE_DBL_HORZ   22 
#define DBX_PORT_NOOUTLINE_DBL_VERT  23
#define DBX_PORT_NOOUTLINE_DBL_HORZ  24


//
//  Pin Length Types: Returned in TPort.pinLength
//
#define DBX_PORT_PIN_LONG            300 
#define DBX_PORT_PIN_SHORT           100
#define DBX_PORT_PIN_CUSTOM             0


//
//  Line Style & Widths (in mils)
//
#define DBX_SOLID_LINE      0
#define DBX_DASHED_LINE     1
#define DBX_DOTTED_LINE     2
#define DBX_THIN_LINE       10
#define DBX_THICK_LINE      30


//
//  Pin Display Styles:  Returned in inside and outside styles
//
#define DBX_PIN_DISPLAY_O_NONE       0
#define DBX_PIN_DISPLAY_O_FLOW_IN    1
#define DBX_PIN_DISPLAY_O_FLOW_OUT   2
#define DBX_PIN_DISPLAY_O_FLOW_BI    3
#define DBX_PIN_DISPLAY_O_ANALOG     4
#define DBX_PIN_DISPLAY_O_DIGITAL    5
#define DBX_PIN_DISPLAY_O_NONLOGIC   6

#define DBX_PIN_DISPLAY_OE_NONE      0
#define DBX_PIN_DISPLAY_OE_DOT       1
#define DBX_PIN_DISPLAY_OE_POL_IN    2
#define DBX_PIN_DISPLAY_OE_POL_OUT   3

#define DBX_PIN_DISPLAY_IE_NONE      0
#define DBX_PIN_DISPLAY_IE_CLOCK     1

#define DBX_PIN_DISPLAY_I_NONE       0
#define DBX_PIN_DISPLAY_I_OPEN       1
#define DBX_PIN_DISPLAY_I_OPEN_H     2
#define DBX_PIN_DISPLAY_I_OPEN_L     3
#define DBX_PIN_DISPLAY_I_PASS_UP    4
#define DBX_PIN_DISPLAY_I_PASS_DOWN  5
#define DBX_PIN_DISPLAY_I_3_STATE    6
#define DBX_PIN_DISPLAY_I_AMPLIFIER  7
#define DBX_PIN_DISPLAY_I_GENERATOR  8
#define DBX_PIN_DISPLAY_I_HYSTERESIS 9
#define DBX_PIN_DISPLAY_I_POSTPONED  10
#define DBX_PIN_DISPLAY_I_SHIFT      11


//
//  Symbol Alternate types
//
#define DBX_ALTTYPE_NORMAL       0   
#define DBX_ALTTYPE_IEE          1   
#define DBX_ALTTYPE_DEMORGAN     2   


//
//  Drill Symbol Types:  Returned in TPadViaStyle.drillSymbol
//
#define DBX_DRILLSYM_UNDEFINED      -1
#define DBX_DRILLSYM_CROSS           0
#define DBX_DRILLSYM_X               1
#define DBX_DRILLSYM_Y               2
#define DBX_DRILLSYM_T               3
#define DBX_DRILLSYM_HOUR            4
#define DBX_DRILLSYM_SIDE_HOUR       5
#define DBX_DRILLSYM_BOX_LINE        6
#define DBX_DRILLSYM_DIAMOND_LINE    7
#define DBX_DRILLSYM_BOX_V           8
#define DBX_DRILLSYM_DIAMOND_V       9
#define DBX_DRILLSYM_BOX_X           10
#define DBX_DRILLSYM_DIAMOND_CROSS   11
#define DBX_DRILLSYM_BOX_CROSS       12
#define DBX_DRILLSYM_DIAMOND_X       13
#define DBX_DRILLSYM_BOX_Y           14
#define DBX_DRILLSYM_DIAMOND_Y       15
#define DBX_DRILLSYM_BOX_T           16
#define DBX_DRILLSYM_DIAMOND_T       17
#define DBX_DRILLSYM_CIRCLE_LINE     18
#define DBX_DRILLSYM_CIRCLE_V        19
#define DBX_DRILLSYM_CIRCLE_CROSS    20
#define DBX_DRILLSYM_CIRCLE_X        21
#define DBX_DRILLSYM_CIRCLE_Y        22
#define DBX_DRILLSYM_CIRCLE_T        23
#define DBX_DRILLSYM_UPPER_A         24
#define DBX_DRILLSYM_UPPER_B         25
#define DBX_DRILLSYM_UPPER_C         26
#define DBX_DRILLSYM_UPPER_D         27
#define DBX_DRILLSYM_UPPER_E         28
#define DBX_DRILLSYM_UPPER_F         29
#define DBX_DRILLSYM_UPPER_G         30
#define DBX_DRILLSYM_UPPER_H         31
#define DBX_DRILLSYM_UPPER_I         32
#define DBX_DRILLSYM_UPPER_J         33
#define DBX_DRILLSYM_UPPER_K         34
#define DBX_DRILLSYM_UPPER_L         35
#define DBX_DRILLSYM_UPPER_M         36
#define DBX_DRILLSYM_UPPER_N         37
#define DBX_DRILLSYM_UPPER_O         38
#define DBX_DRILLSYM_UPPER_P         39
#define DBX_DRILLSYM_UPPER_Q         40
#define DBX_DRILLSYM_UPPER_R         41
#define DBX_DRILLSYM_UPPER_S         42
#define DBX_DRILLSYM_UPPER_U         43
#define DBX_DRILLSYM_UPPER_V         44
#define DBX_DRILLSYM_UPPER_W         45
#define DBX_DRILLSYM_UPPER_Z         46
#define DBX_DRILLSYM_LOWER_A         47
#define DBX_DRILLSYM_LOWER_B         48
#define DBX_DRILLSYM_LOWER_C         49
#define DBX_DRILLSYM_LOWER_D         50
#define DBX_DRILLSYM_LOWER_E         51
#define DBX_DRILLSYM_LOWER_F         52
#define DBX_DRILLSYM_LOWER_G         53
#define DBX_DRILLSYM_LOWER_H         54
#define DBX_DRILLSYM_LOWER_I         55
#define DBX_DRILLSYM_LOWER_J         56
#define DBX_DRILLSYM_LOWER_K         57
#define DBX_DRILLSYM_LOWER_L         58
#define DBX_DRILLSYM_LOWER_M         59
#define DBX_DRILLSYM_LOWER_N         60
#define DBX_DRILLSYM_LOWER_O         61
#define DBX_DRILLSYM_LOWER_P         62
#define DBX_DRILLSYM_LOWER_Q         63
#define DBX_DRILLSYM_LOWER_R         64
#define DBX_DRILLSYM_LOWER_S         65
#define DBX_DRILLSYM_LOWER_T         66
#define DBX_DRILLSYM_LOWER_U         67
#define DBX_DRILLSYM_LOWER_V         68
#define DBX_DRILLSYM_LOWER_W         69
#define DBX_DRILLSYM_LOWER_Y         70
#define DBX_DRILLSYM_LOWER_Z         71

//  DBX Color Index Types for Hilight 
#define DBX_COLOR_BLACK              1
#define DBX_COLOR_DARKRED            2
#define DBX_COLOR_DARKGREEN          3
#define DBX_COLOR_DARKYELLOW         4 
#define DBX_COLOR_DARKBLUE           5
#define DBX_COLOR_DARKMAGENTA        6
#define DBX_COLOR_DARKCYAN           7
#define DBX_COLOR_LIGHTGRAY          8
#define DBX_COLOR_DARKGRAY           9
#define DBX_COLOR_RED                10
#define DBX_COLOR_GREEN              11
#define DBX_COLOR_YELLOW             12
#define DBX_COLOR_BLUE               13 
#define DBX_COLOR_MAGENTA            14 
#define DBX_COLOR_CYAN               15 
#define DBX_COLOR_WHITE              16 
#define DBX_COLOR_POWDERGREEN        17 
#define DBX_COLOR_POWDERBLUE         18 
#define DBX_COLOR_POWDER             19 
#define DBX_COLOR_GRAY               20 


//
//  Field Key Types
//
#define DBX_FIELD_DATE            1
#define DBX_FIELD_CURDATE         2
#define DBX_FIELD_TIME            3
#define DBX_FIELD_CURTIME         4
#define DBX_FIELD_AUTHOR          5
#define DBX_FIELD_REV             6
#define DBX_FIELD_FILENAME        7
#define DBX_FIELD_TITLE           8
#define DBX_FIELD_SHEETNUM        10
#define DBX_FIELD_NUMSHEETS       11
#define DBX_FIELD_DRAWING_NUMBER  12
#define DBX_FIELD_NOTE            13
#define DBX_FIELD_REVISION_NOTE   14


//
//    Table types
//
#define DBX_TABLE_NET_INDEX            0
#define DBX_TABLE_NOTES                1
#define DBX_TABLE_POWER                2
#define DBX_TABLE_SPARE_GATE           3
#define DBX_TABLE_DRILL                4
#define DBX_TABLE_REVISION_NOTES       5


//
//    Diagram Types
//
#define    DBX_DIAGRAM_LAYER_STACK        1
#define    DBX_DIAGRAM_PROFILE            2
#define    DBX_DIAGRAM_DESIGNVIEW         3


//
//    Fill Pattern Types: Returned in TRoom.roomFillPattern
//
#define DBX_ROOM_UNDEFINED_FILLPATTERN   0
#define DBX_ROOM_CLEAR_FILLPATTERN       1
#define DBX_ROOM_SOLID_FILLPATTERN       2
#define DBX_ROOM_HATCHED_FILLPATTERN     3


//
//    Placement Types: Returned in TRoom.placementSide
//
#define DBX_ROOM_UNDEFINED_PLACEMENT     0
#define DBX_ROOM_TOP_PLACEMENT           1
#define DBX_ROOM_BOTTOM_PLACEMENT        2
#define DBX_ROOM_TOP_OR_BOTTOM_PLACEMENT 3


//
//    Placement Types: Returned in TPoint.placementSide
//
#define DBX_TESTPOINT_UNDEFINED_PLACEMENT    -1
#define DBX_TESTPOINT_TOP_PLACEMENT           0
#define DBX_TESTPOINT_BOTTOM_PLACEMENT        1


//
//    Connection Types: Returned in TComponent.connectionType
//
#define DBX_COMPONENT_CONNECTION_NORMAL           0
#define DBX_COMPONENT_CONNECTION_POWER            1
#define DBX_COMPONENT_CONNECTION_SHEET_CONNECTOR  2
#define DBX_COMPONENT_CONNECTION_MODULE           3
#define DBX_COMPONENT_CONNECTION_LINK             4


//
//  RuleCategory
//
#define DBX_RULE_CATEGORY_UNKNOWN                       0

#define DBX_RULE_CATEGORY_ERC_BUS_NET                   1
#define DBX_RULE_CATEGORY_ERC_COMPONENT                 2
#define DBX_RULE_CATEGORY_ERC_ELECTRICAL                3
#define DBX_RULE_CATEGORY_ERC_HIERARCHY                 4
#define DBX_RULE_CATEGORY_ERC_NET_CONNECTIVITY          5
#define DBX_RULE_CATEGORY_ERC_NO_NODE_NET               6
#define DBX_RULE_CATEGORY_ERC_SINGLE_NODE_NET           7
#define DBX_RULE_CATEGORY_ERC_UNCONNECTED_PIN           8
#define DBX_RULE_CATEGORY_ERC_UNCONNECTED_WIRE          9

#define DBX_RULE_CATEGORY_DRC_CLEARANCE                10 
#define DBX_RULE_CATEGORY_DRC_NETLIST                  11
#define DBX_RULE_CATEGORY_DRC_UNROUTED_NETS            12
#define DBX_RULE_CATEGORY_DRC_UNCONNECTED_PINS         13
#define DBX_RULE_CATEGORY_DRC_NET_LENGTH               14
#define DBX_RULE_CATEGORY_DRC_SILK                     15
#define DBX_RULE_CATEGORY_DRC_TEXT                     16
#define DBX_RULE_CATEGORY_DRC_WIDTH                    17
#define DBX_RULE_CATEGORY_DRC_POUR                     18
#define DBX_RULE_CATEGORY_DRC_PLANE                    19
#define DBX_RULE_CATEGORY_DRC_COMPONENT                20
#define DBX_RULE_CATEGORY_DRC_DRILL                    21
#define DBX_RULE_CATEGORY_DRC_TESTPOINT                22


//
//  RuleType
//
#define DBX_RULE_TYPE_UNKNOWN                           0
                                             
#define DBX_RULE_ERC_ELEC_3STATE_OUTPUT                 1
#define DBX_RULE_ERC_ELEC_3STATE_POWER                  2
#define DBX_RULE_ERC_ELEC_BI_OH                         3
#define DBX_RULE_ERC_ELEC_BI_OL                         4
#define DBX_RULE_ERC_ELEC_BI_OUTPUT                     5
#define DBX_RULE_ERC_ELEC_BI_POWER                      6
#define DBX_RULE_ERC_ELEC_OH_BI                         7
#define DBX_RULE_ERC_ELEC_OH_OH                         8
#define DBX_RULE_ERC_ELEC_OH_OL                         9
#define DBX_RULE_ERC_ELEC_OH_OUTPUT                    10
#define DBX_RULE_ERC_ELEC_OH_POWER                     11
#define DBX_RULE_ERC_ELEC_OL_BI                        12
#define DBX_RULE_ERC_ELEC_OL_OH                        13
#define DBX_RULE_ERC_ELEC_OL_OUTPUT                    14
#define DBX_RULE_ERC_ELEC_OL_POWER                     15
#define DBX_RULE_ERC_ELEC_OUTPUT_BI                    16
#define DBX_RULE_ERC_ELEC_OUTPUT_OUTPUT                17
#define DBX_RULE_ERC_ELEC_OUTPUT_3STATE                18
#define DBX_RULE_ERC_ELEC_OUTPUT_OH                    19
#define DBX_RULE_ERC_ELEC_OUTPUT_OL                    20
#define DBX_RULE_ERC_ELEC_OUTPUT_POWER                 21
#define DBX_RULE_ERC_ELEC_POWER_3STATE                 22
#define DBX_RULE_ERC_ELEC_POWER_BI                     23
#define DBX_RULE_ERC_ELEC_POWER_OH                     24
#define DBX_RULE_ERC_ELEC_POWER_OL                     25
#define DBX_RULE_ERC_ELEC_POWER_OUTPUT                 26
#define DBX_RULE_ERC_ELEC_NO_INPUT                     27
#define DBX_RULE_ERC_ELEC_NO_OUTPUT                    28
#define DBX_RULE_ERC_NET_CON_DIFFRNT_NET_NAME          29
#define DBX_RULE_ERC_NET_CON_MERGED_NETS_NOT           30
#define DBX_RULE_ERC_NET_CON_NET_NAME_NOT_VIS          31
#define DBX_RULE_ERC_NET_CON_PIN_NAME_MISSING          32
#define DBX_RULE_ERC_HIER_EXCEED_SHEET_LIMIT           33
#define DBX_RULE_ERC_HIER_INF_SHEET_DIFF               34
#define DBX_RULE_ERC_HIER_INT_ATTR_NOT_DEFINED         35
#define DBX_RULE_ERC_HIER_INT_ILLEGAL                  36
#define DBX_RULE_ERC_HIER_INT_MULTIPLE                 37
#define DBX_RULE_ERC_HIER_INT_NOT_DEFINED              38
#define DBX_RULE_ERC_HIER_INT_UNUSED                   39
#define DBX_RULE_ERC_HIER_MULT_SHEET                   40
#define DBX_RULE_ERC_HIER_PIN_DES_MISMATCH             41
#define DBX_RULE_ERC_HIER_PIN_ELECT_TYPE               42
#define DBX_RULE_ERC_HIER_PIN_MISMATCH                 43
#define DBX_RULE_ERC_HIER_RECURSIVE                    44
#define DBX_RULE_ERC_HIER_SAME_SHEET                   45
#define DBX_RULE_ERC_HIER_INFPIN_NOT_CONNECTED         46
#define DBX_RULE_ERC_HIER_INFPIN_PASSTHROUGH           47
#define DBX_RULE_ERC_HIER_MODPIN_NOT_CONNECTED         48
#define DBX_RULE_ERC_COMP_TWO_COMPS                    49
#define DBX_RULE_ERC_BUS_NET_BUS_NO_NET                50
#define DBX_RULE_ERC_BUS_NET_BUS_SINGLE_NET            51
#define DBX_RULE_ERC_NO_NODES                          52
#define DBX_RULE_ERC_SINGLE_NODE                       53
#define DBX_RULE_ERC_UNCON_PIN_BLANK_NET_NAME          54
#define DBX_RULE_ERC_UNCON_PIN_UNCONNECTED_PIN         55
#define DBX_RULE_ERC_UNCONNECTED_WIRE                  56
                                             
#define DBX_RULE_DRC_CLEARANCE                         57
#define DBX_RULE_DRC_SHORT                             58
#define DBX_RULE_DRC_NET_SHORTED_TO_TIE                59
#define DBX_RULE_DRC_COMP_PINS_SHORTED                 60
#define DBX_RULE_DRC_CONNECTED_POINT_TO_POINT          61
#define DBX_RULE_DRC_PSEUDO                            62
#define DBX_RULE_DRC_VIASTYLE_NONEXISTANT              63
#define DBX_RULE_DRC_VIASTYLE_VIOLATION                64
#define DBX_RULE_DRC_MAXVIAS                           65
#define DBX_RULE_DRC_UNCONNECTED_PIN                   66
#define DBX_RULE_DRC_CU_POUR_CLEARANCE                 67
#define DBX_RULE_DRC_CU_POUR_TERRA_INCOGNITA           68
#define DBX_RULE_DRC_CU_POUR_UNFILLED                  69
#define DBX_RULE_DRC_CU_POUR_NO_NET                    70
#define DBX_RULE_DRC_DRILL_CLEARANCE                   71
#define DBX_RULE_DRC_DRILL_HOLE_SAME_LAYER             72
#define DBX_RULE_DRC_DRILL_HOLE_INTERFERENCE           73
#define DBX_RULE_DRC_UNROUTED_NET                      74
#define DBX_RULE_DRC_HOLE_NO_CONNECT                   75
#define DBX_RULE_DRC_HOLE_RANGE_VIOLATION              76
#define DBX_RULE_DRC_TIE_NET_WITH_NO_POLY              77
#define DBX_RULE_DRC_TIE_POLY_WITHOUT_NETS             78
#define DBX_RULE_DRC_NET_FREE_PIN                      79
#define DBX_RULE_DRC_NET_LENGTH                        80
#define DBX_RULE_DRC_SILK_CLEARANCE                    81
#define DBX_RULE_DRC_TEXT_CLEARANCE                    82
#define DBX_RULE_DRC_WIDTH                             83
#define DBX_RULE_DRC_COMPONENT_SIDE                    84
#define DBX_RULE_DRC_COMPONENT_HEIGHT                  85
#define DBX_RULE_DRC_ROOM_INCLUDED_COMPS               86
#define DBX_RULE_DRC_EMPTY_ROOM                        87
#define DBX_RULE_DRC_PLANE_CLEARANCE                   88
#define DBX_RULE_DRC_PLANE_SPLIT                       89
#define DBX_RULE_DRC_PLANE_PARTIAL_CONNECTION          90
#define DBX_RULE_DRC_PLANE_HOLE_SHORT                  91
#define DBX_RULE_DRC_PLANE_NO_CONNECTIONS              92
#define DBX_RULE_DRC_PLANE_NO_NET                      93
#define DBX_RULE_DRC_PLANE_COPPER_INTERSECTION         94
#define DBX_RULE_DRC_TESTPOINT_NO_NET                  95
#define DBX_RULE_DRC_TESTPOINT_NOT_ON_TP_GRID          96
#define DBX_RULE_DRC_TESTPOINT_SPACING                 97
#define DBX_RULE_DRC_TESTPOINT_INVALID_OBJECT          98
#define DBX_RULE_DRC_TESTPOINT_NOT_ON_PAD_CENTER_SMT   99
#define DBX_RULE_DRC_TESTPOINT_NOT_ON_PAD_CENTER_THRU 100
#define DBX_RULE_DRC_TESTPOINT_INVALID_PAD_AREA       101
#define DBX_RULE_DRC_TESTPOINT_NET_MISSING            102
#define DBX_RULE_DRC_TESTPOINT_WRONG_SIDE             103
#define DBX_RULE_DRC_TESTPOINT_MULTIPLE_NETS          104
#define DBX_RULE_DRC_MULTIPLE_TIE_POLY                105
#define DBX_RULE_DRC_NET_FREE_PAD                     106
#define DBX_RULE_DRC_COMPONENT_CLEARANCE              107



//
//  ViolationType
//
#define DBX_ERROR_VIOLATION                             0
#define DBX_WARNING_VIOLATION                           1
#define DBX_IGNORED_VIOLATION                           2
#define DBX_OVERRIDDEN_VIOLATION                        3


//
//  Unit Definitions 
//
#define DBX_UNIT_DB                 0       // database units
#define DBX_UNIT_MIL                1       // mil
#define DBX_UNIT_MM                 2       // millimeter
#define DBX_UNIT_CM                 3       // centimeter
#define DBX_UNIT_INCH               4       // inch
#define DBX_UNIT_APP                5       //
#define DBX_UNIT_GLOBAL             6       // ie. Use gpDesign's current DBX_UNITs.
#define DBX_UNIT_LAYER              7       // String represents a layer name.
#define DBX_UNIT_VIASTYLE           8       // String represents a via style name.
#define DBX_UNIT_M                  9       // meter
#define DBX_UNIT_UM                 10      // micrometer
#define DBX_UNIT_NM                 11      // nanometer
#define DBX_UNIT_PM                 12      // picometer
#define DBX_UNIT_RAD                13      // radian
#define DBX_UNIT_DEG                14      // degree
#define DBX_UNIT_OHM                15      // ohms
#define DBX_UNIT_MHO                16      // conductance
#define DBX_UNIT_VOLT               17      // volts
#define DBX_UNIT_MVOLT              18      // millivolts
#define DBX_UNIT_UVOLT              19      // microvolts
#define DBX_UNIT_NVOLT              20      // nanovolts
#define DBX_UNIT_PVOLT              21      // picovolts
#define DBX_UNIT_AMP                22      // ampere
#define DBX_UNIT_MAMP               23      // milliamp
#define DBX_UNIT_UAMP               24      // microamp
#define DBX_UNIT_NAMP               25      // nanoamp
#define DBX_UNIT_PAMP               26      // picoamp
#define DBX_UNIT_HENRY              27      // Henry
#define DBX_UNIT_MHENRY             28      // millihenry
#define DBX_UNIT_UHENRY             29      // microhenry
#define DBX_UNIT_NHENRY             30      // nanohenry
#define DBX_UNIT_PHENRY             31      // picohenry
#define DBX_UNIT_FARAD              32      // Farad
#define DBX_UNIT_MFARAD             33      // millifarad
#define DBX_UNIT_UFARAD             34      // microfarad
#define DBX_UNIT_NFARAD             35      // nanofarad
#define DBX_UNIT_PFARAD             36      // picofarad
#define DBX_UNIT_SECOND             37      // second
#define DBX_UNIT_MSECOND            38      // millisecond
#define DBX_UNIT_USECOND            39      // microsecond
#define DBX_UNIT_NSECOND            40      // nanosecond
#define DBX_UNIT_PSECOND            41      // picosecond
#define DBX_UNIT_BOOL               42      // Boolean
#define DBX_UNIT_QUANTITY           43      // quantity
#define DBX_UNIT_STRING             44      // string
#define DBX_UNIT_HERTZ              45      // hertz
#define DBX_UNIT_KHERTZ             46      // kilohertz
#define DBX_UNIT_MHERTZ             47      // megahertz
#define DBX_UNIT_WATT               48      // wattage
#define DBX_UNIT_MWATT              49      // milliwatt
#define DBX_UNIT_UWATT              50      // microwatt
#define DBX_UNIT_NWATT              51      // nanowatt
#define DBX_UNIT_PWATT              52      // picowatt
#define DBX_UNIT_GHERTZ             53      // gigahertz
#define DBX_UNIT_NO_UNIT            54      // a unit has not been defined for the constraint


//
//  Component graphic orientation assignments
//
#define DBX_COMP_GRAPHIC_ORIENT_TOP_0       0
#define DBX_COMP_GRAPHIC_ORIENT_TOP_90      1
#define DBX_COMP_GRAPHIC_ORIENT_TOP_180     2
#define DBX_COMP_GRAPHIC_ORIENT_TOP_270     3
#define DBX_COMP_GRAPHIC_ORIENT_BOTTOM_0    4
#define DBX_COMP_GRAPHIC_ORIENT_BOTTOM_90   5
#define DBX_COMP_GRAPHIC_ORIENT_BOTTOM_180  6
#define DBX_COMP_GRAPHIC_ORIENT_BOTTOM_270  7


//
//  Pcb design solder flow direction indicators
//
#define SOLDER_FLOW_TOP_TO_BOTTOM   0
#define SOLDER_FLOW_RIGHT_TO_LEFT   1
#define SOLDER_FLOW_BOTTOM_TO_TOP   2
#define SOLDER_FLOW_LEFT_TO_RIGHT   3


//
//     Conversation and Context Structure - Returned by TOpenDesign
//
    
typedef struct                //           (pcb/sch/cmp)
{
    HCONV     hConv;          // Converstation handle
    long      appInst;        // Application instance
    long      version;        // DBX version
    long      language;       // Language type
    HWND      hWnd;           // Server's window handle.
    HANDLE    hMmf;           // Handle to memory mapped file.
    void*     pMmf;           // Pointer to mapped view of MMF.

} DbxContext;

//
//    TCoord and TBoundRect are declared first.  They are 
//    used in the definition of structures for other items
//
                            
typedef struct  // (pcb/sch/cmp)
{
    long            x;             
    long            y;             
} TCoord;
                                         
typedef struct  // (pcb/sch)
{
    TCoord          lowerLeft;              //  point structures      
    TCoord          upperRight;             //  as defined above
} TBoundRect;

//
//    The following structures are the data structures for 
//      all extracted items, listed in alphabetical order
//

typedef struct  // (pcb)
{
    long            itemId;
    long            width;             // in database units
    long            radius;            // in database units
    TCoord          centerPt;          // in database units
    long            startAng;          // in database units
    long            sweepAng;          // in database units
    TBoundRect      boundRect;
    long            netId;
    long            layerId;
    long            isHighlighted;
    long            isFixed;
} TArc;

typedef struct  // (pcb/sch)
{
    long            itemId;                          // pcb  sch
    char            type[DBX_MAX_TYPE_LEN];          // pcb  sch
    char            value[DBX_MAX_ATTRIBUTE_LEN];    // pcb  sch 
    char            formula[DBX_MAX_FORMULA_LEN];    // pcb  sch
    char            comment[DBX_MAX_TEXTITEM_LEN];   // pcb  sch    
    long            typeLength;                      // pcb  sch
    long            valueLength;                     // pcb  sch    
    long            formulaLength;                   // pcb  sch
    long            commentLength;                   // pcb  sch    
    long            textStyleId;                     // pcb  sch
    long            justPoint;                       // pcb  sch
    TCoord          refPoint;                        // pcb  sch
    TBoundRect      boundRect;                       // pcb  sch
    long            rotationAng;                     // pcb  sch
    long            compId;                          // not used
    long            netId;                           // not used
    long            netClassId;                      // not used
    long            layerId;                         // pcb  sch
    long            isFlipped;                       // pcb  sch
    long            isHighlighted;                   // pcb  sch
    long            isVisible;                       // pcb  sch    
    long            units;                           // pcb  sch; one of the unit types defined above
} TAttribute;

typedef struct  // (sch)
{
    long            itemId;
    TCoord          startPt;
    TCoord          endPt;
    long            layerId;
    char            busName[DBX_MAX_NAME_LEN];
    long            isFlipped;
    long            isHighlighted;
    long            isNameVisible;               //  =0 not visible
} TBus;

typedef struct  // (pcb/sch)
{                                                
    long            netClassId1;                            // pcb  sch
    long            netClassId2;                            // pcb  sch
    char            netClassName1[DBX_MAX_NAME_LEN];        // pcb  sch
    char            netClassName2[DBX_MAX_NAME_LEN];        // pcb  sch
} TClassToClass;

typedef struct  // (pcb/sch/cmp)
{
    long            compId;                          // pcb  sch
    char            refDes[DBX_MAX_NAME_LEN];        // pcb  sch
    char            compType[DBX_MAX_TYPE_LEN];      // pcb  sch
    char            value[DBX_MAX_VALUE_LEN];        // pcb  sch
    char            patternName[DBX_MAX_NAME_LEN];   // pcb  sch 
    char            libraryName[DBX_MAX_FILENAME_LEN];//pcb  sch
    TCoord          refPoint;                        // pcb  
    TBoundRect      boundRect;                       // pcb  
    long            rotationAng;                     // pcb  
    long            numberPads;                      // pcb  
    long            numberPins;                      // pcb  sch
    long            numberParts;                     // pcb  sch
    long            isAlpha;                         // pcb  sch
    long            isFlipped;                       // pcb  
    long            isHighlighted;                   // pcb  sch
    long            isHetero;                        // heterogeneous vs. homogeneous
    long            connectionType;                  // the type of component: power, connector, or link...
    long            isFixed;                         // pcb (only)
    long            numberGraphics;                         // pcb (only)
    char            currentGraphicName[DBX_MAX_NAME_LEN];   // pcb (only)
    char            defaultGraphicName[DBX_MAX_NAME_LEN];   // pcb (only)
    long            isAutoSwapGraphic;                      // pcb (only)
} TComponent;

typedef struct  // (pcb/cmp)
{
    char            graphicName[DBX_MAX_NAME_LEN];
    long            numberPads;
    long            numberAttrs;
    long            numberItems;
} TCompGraphic;

typedef struct  // (pcb/sch/cmp)
{
    //long            itemId;
    long            compPinNumber;
    char            pinDes[DBX_MAX_NAME_LEN];
    long            gateNumber;
    long            symPinNumber;
    long            padNumber;
    char            pinName[DBX_MAX_NAME_LEN];
    long            gateEq;
    long            pinEq;
    long            electype;                    // pin type
} TCompPin;

typedef struct  // (pcb/sch)
{
    char            designName[DBX_MAX_NAME_LEN];
    char            title[DBX_MAX_NAME_LEN];
    char            designer[DBX_MAX_NAME_LEN];      //  Author
    char            version[DBX_MAX_NAME_LEN];
    char            lastModifiedDate[DBX_MAX_NAME_LEN];
    char            lastModifiedTime[DBX_MAX_NAME_LEN];
    char            drawingNumber[DBX_MAX_NAME_LEN];  
    char            guidString[DBX_MAX_NAME_LEN];
    TCoord          workSpaceSize;                   //  in database units
    TBoundRect      layerExtents;                    //  in database units
    long            absGridId;                       //  absolute grid index
    long            relGridId;                       //  relative grid index
    long            isGridAbsolute;                  //  1=absolute mode; 0=relative mode
    long            userUnits;                       //  DBX_UNIT_MILS, DBX_UNIT_MM
    TCoord          relGridOrigin;                   //  coordinates of relative grid origin 
    long            isModified;                      //  1=Design has been modified; 0=no modification
    long            solderFlowDir;                   //  pcb only
} TDesign;

typedef struct  // (sch)
{                                                
    long            itemId;                      // 
    long            textStyleId;                 //
    char            text[DBX_MAX_TEXTITEM_LEN];  //
    long            layerId;                     // 
    long            justPoint;                   // 
    TCoord          refPoint;                    // 
    long            rotationAng;                 // 
    long            isFlipped;                   // 
    long            isHighlighted;               // 
    long            isVisible;                   //
    long            fieldKeyType;                //
} TField;

typedef struct  // (pcb/sch)
{                                                
    long            gridId;                                 //  ordinal number
    char            gridSpacing[DBX_MAX_GRIDSPACING_LEN];   //  the grid spacing; values are held as a string
} TGrid;

typedef struct  // (pcb/sch)
{                                                
    long            layerId;                     // pcb  sch
    char            layerName[DBX_MAX_NAME_LEN]; // pcb  sch
    long            layerType;                   // pcb
    long            layerBias;                   // pcb
    long            planeNetId;                  // pcb      =0 if none
    long            lineLineClearance;           // pcb      in database units
    long            padLineClearance;            // pcb      in database units
    long            padPadClearance;             // pcb      in database units
    long            viaPadClearance;             // pcb      in database units
    long            viaLineClearance;            // pcb      in database units
    long            viaViaClearance;             // pcb      in database units
    long            isEnabled;                   // pcb      =0 not enabled
    long            layerPosition;               // pcb  sch ordinal position of the layer in the design
} TLayer;

typedef struct  // (pcb/sch)
{
    long            itemId;
    long            lineType;                    //  DBX item type
    long            width;                       //  in database units
    TCoord          startPt;
    TCoord          endPt;
    TBoundRect      boundRect;
    long            netId;
    long            layerId;
    long            isHighlighted;
    long            isFixed;
} TLine;

typedef struct  // (pcb/sch)
{                                                
    long            netId;                       // pcb  sch
    char            netName[DBX_MAX_NAME_LEN];   // pcb  sch
    long            nodeCount;                   // pcb  sch
    long            length;                      // pcb      in database units
    long            isPlane;                     // pcb      =0 not plane
} TNet;

typedef struct  // (pcb/sch)
{                                                
    long            netClassId;                     // pcb  sch
    char            netClassName[DBX_MAX_NAME_LEN]; // pcb  sch
    long            numberOfNets;                   // pcb  sch
} TNetClass;

typedef struct // (pcb)
{
    long            itemId;
    char            compRefDes[DBX_MAX_NAME_LEN];//      "
    long            padStyleId;
    TCoord          center;
    long            layerId;
    long            isFlipped;                   //  =0 not flipped
    long            rotationAng;                 //  in database units
    long            isHighlighted;
    long            netId;
    TBoundRect      boundRect;
    TCompPin        compPin;
    char            defaultPinDes[DBX_MAX_NAME_LEN];// may be NULL     
    long            isFixed;
} TPad;

typedef struct  // (pcb)
{
    long            layerId;
    long            layerType;        
    long            styleType;                   // Pad, Via Style    
    long            shape; 
    long            holeDia;                     // in database units  
    long            width;                       // Normal Types, in db units
    long            height;                      // Normal Types, in db units
    long            outerDia;                    // Thermals, in db units
    long            innerDia;                    // Thermals, in db units
    long            spokeWidth;                  // Thermals, in db units
    long            isPourNoConn;                // Prohibit Cu pour thermalizing
} TPadViaShape;
  
  
typedef struct  // (pcb)
{
    long            styleId;
    long            styleType;                   // DBX_PAD or DBX_VIA 
    char            name[DBX_MAX_NAME_LEN];
    long            holeDia;                     // in database units   
    long            isHolePlated;                // =0 nonplated   
    long            xOffset;                     // in database units
    long            yOffset;                     // in database units
    long            holeStartLayer;
    long            holeEndLayer;
    long            drillSymbol;
} TPadViaStyle;

typedef struct  // (cmp)
{
    long            itemId;
    char            patternName[DBX_MAX_NAME_LEN];
    long            rotationAng;    // for future use in PCB
    long            isFlipped;        // for future use in PCB
    long            isHighlighted;    // for future use in PCB
} TPattern;


typedef struct  // (sch/cmp)
{
    long            itemId;
    char            compRefDes[DBX_MAX_NAME_LEN];   
    long            outsideStyle; 
    long            outsideEdgeStyle; 
    long            insideStyle; 
    long            insideEdgeStyle;
    TCoord          refPoint;
    long            layerId;
    long            isFlipped;                   //  =0 not flipped
    long            isHighlighted;
    long            rotationAng;                 // 
    long            netId;
    TBoundRect      boundRect;
    long            pinLength;
    TCompPin        compPin;
    char            defaultPinDes[DBX_MAX_NAME_LEN];// may be NULL     
} TPin;

typedef struct  // (pcb/sch)
{
    long            itemId;                     //  =0 for DBX_COORDINATE 
    long            x;                          //  x value in database units                             
    long            y;                          //  y value in database units
    long            pointType;                  //  Glue, Pick, Ref, Info
    long            number;                     // Used for InfoPoint only
    char            textInfo[DBX_MAX_TEXTITEM_LEN]; // Used for InfoPoint only
    long            layerId;
    long            isFlipped;                  //
    long            isVisible;                  //
    long            isHighlighted;
    long            ruleCategory;               // ERC/DRC rule category;       InfoPoint only; new V15
    long            ruleType;                   // ERC/DRC rule type;           InfoPoint only; new V15
    long            violationType;              // violation type of InfoPoint; InfoPoint only; new V15
    long            placementSide;              // TestPoint only
    long            isSnapToCenter;             // TestPoint only
    long            netId;                      // TestPoint only
    long            isFixed;                    // TestPoint only
} TPoint;
 

typedef struct  // (pcb)
{
    long            itemId;
    long            polyType;
    long            numPts;
    TBoundRect      boundRect;
    long            netId;
    long            layerId;
    long            isHighlighted;
} TPoly ;

typedef struct // (sch)
{
    long            itemId;
    long            netId;
    long            portType;
    long            pinLength;
    long            rotationAng;
    long            isFlipped;
    long            isHighlighted;
    long            textStyleId;
    long            layerId;
    TCoord          refPoint;
} TPort;

typedef struct // (pcb)
{
    long            itemId;
    long            lineSpacing;                 //  in database units
    long            lineWidth;                   //  in database units
    long            thermalType;
    long            pourType;
    long            numPts;                      //  number of outline points
    TBoundRect      boundRect;
    long            netId;
    long            layerId;
    long            isFlooded;                   //  =0 not flooded
    long            isHighlighted;               //  Highlight color: 0,1,2,3,4
    long            isFixed;
} TPour;

typedef struct // (pcb/sch)
{
    long            isSelected;                     // Is PrintJob selected for output.
    char            jobName[DBX_MAX_FILENAME_LEN];  // Print job name.
    long            isRotated;                      // Is PrintJob marked for rotated output.
} TPrintJob;

typedef struct  // (pcb)
{
    long            roomId;
    char            roomName[DBX_MAX_NAME_LEN];
    long            layerId;
    long            numberOfIncludedComps;  
    long            numberOfExcludedComps;  
    TBoundRect      boundRect;                   
    long            placementSide;
    long            isFixed;                 
    long            isFlipped;                   
    long            isHighlighted; 
    long            roomFillPattern;               
    TCoord          refPoint;      
    long            rotationAngle;              
} TRoom;

typedef struct  // (sch/cmp)
{
    long            symbolId;
    char            symbolName[DBX_MAX_NAME_LEN];
    char            refDes[DBX_MAX_NAME_LEN];
    long            numberPins;  
    long            partNumber;
    long            altType;  
    TCoord          refPoint;                    // reserved for future use
    TBoundRect      boundRect;                   // reserved for future use
    long            rotationAng;                 // reserved for future use
    long            isFlipped;                   // reserved for future use
    long            isHighlighted;               // reserved for future use
    long             layerId;                     // new
    char            compType[DBX_MAX_NAME_LEN];     // component name
    char libraryName[DBX_MAX_NAME_LEN];             // library name
} TSymbol;
        
        
typedef struct  // (pcb/sch)
{
    long            itemId;
    long            textStyleId;
    char            text[DBX_MAX_TEXTITEM_LEN];
    long            layerId;
    long            justPoint;
    TCoord          refPoint;                    
    TBoundRect      boundRect;
    long            rotationAng;                 //  in database units
    long            isFlipped;                   //  =0 not flipped
    long            isVisible;                   //  =0 not visible
    long            isHighlighted;               //  Highlight color: 0,1,2,3,4
} TText;

typedef struct  // (pcb)
{
    long            styleId;
    char            name[DBX_MAX_NAME_LEN];
    long            strokePenWidth;                  //  in integer widths                    
    long            strokeHeight;                    //  in database units
    char            tTypeFaceName[DBX_MAX_NAME_LEN]; //  in integer widths                    
    long            tTypeHeight;                     //  in database units
    long            isTrueTypeAllowed;               //  = 0  TrueType not allowed
    long            isDisplayTrueType;               //  = 0  display stroke
} TTextStyle;

typedef struct  // (pcb)
{
    long            itemId;
    long            netId;
    TCoord          center;
    long            rotationAng;
    long            viaStyleId;
    TBoundRect      boundRect;
    long            isFlipped;                   //  =0 not flipped
    long            isHighlighted;               //  Highlight color: 0,1,2,3,4
    long            isFixed;
} TVia;

typedef struct  // (pcb/sch)
{
    long            itemId;
    TCoord          startPt;
    TCoord          endPt;
    long            layerId;
    long            isFlipped;                   //  =0 not flipped
    long            isHighlighted;               //  Highlight color: 0,1,2,3,4
    long            isNameVisible;               //  =0 not visible
    long            netId;
    long            width;
} TWire;

 
typedef struct    // (pcb/sch)
{
    long            itemId;    
    TCoord          refPoint;
    long            layerId;
    TBoundRect      boundRect;
    long            rotationAng;
    long            isHighlighted;
    long            isFlipped;
    long            tableType;
    char            tableTitle[DBX_MAX_TEXTITEM_LEN];
    long            textStyleId;
    long            lineWidth;
} TTable;

 
typedef struct    // (pcb)
{
    long            itemId;    
    TCoord          refPoint;
    long            layerId;
    TBoundRect      boundRect;
} TMetaFile;

 
typedef struct    // (pcb)
{
    long            itemId;    
    TCoord          refPoint;
    long            layerId;
    TBoundRect      boundRect;
    long            diagramType;
    char            title[DBX_MAX_TEXTITEM_LEN];
    char            subTitle[DBX_MAX_TEXTITEM_LEN];
    long            textStyleId;    // of title, subtitle
    long            lineWidth;      // for stackup diagram type only
} TDiagram;


typedef struct    // (pcb)
{
    long            itemId;    
    TCoord          refPoint;
    long            layerId;
    TBoundRect      boundRect;
    char            title[DBX_MAX_TEXTITEM_LEN];
    char            subTitle[DBX_MAX_TEXTITEM_LEN];
    char            fileName[DBX_MAX_FILENAME_LEN];
    long            textStyleId;    // of title, subtitle
} TDetail;


//
//  The following structure defines TItem, which may contain 
//  any one of the supported item types.
//

typedef struct  // (pcb/sch)
{
    long            itemType;        // pcb  sch      DBX Item type
    TArc            arc;             // pcb  sch
    TAttribute      attribute;       // pcb  sch
    TBus            bus;             //      sch
    TClassToClass   classToClass;    // pcb  sch
    TComponent      component;       // pcb  sch
    TCompPin        compPin;         //      sch  clm
    TDesign         design;          // pcb  sch
    TDetail         detail;          // pcb         
    TDiagram        diagram;         // pcb         
    TField          field;           //      sch
    TGrid           grid;            // pcb
    TLayer          layer;           // pcb  sch
    TLine           line;            // pcb  sch
    TMetaFile       metaFile;        // pcb         
    TNet            net;             // pcb  sch
    TNetClass       netClass;        // pcb  sch
    TPad            pad;             // pcb       clm
    TPadViaShape    padViaShape;     // pcb  
    TPadViaStyle    padViaStyle;     // pcb  
    TPattern        pattern;         //           clm
    TPin            pin;             //      sch  clm
    TPoint          point;           // pcb  
    TPoly           poly;            // pcb  
    TPort           port;            //      sch
    TPour           pour;            // pcb  
    TPrintJob       printJob;        // pcb  sch
    TRoom           room;            // pcb
    TSymbol         symbol;          //      sch  clm
    TTable          table;           // pcb  sch     
    TText           text;            // pcb  sch
    TTextStyle      textStyle;       // pcb
    TVia            via;             // pcb
    TWire           wire;            //      sch 
    TCompGraphic    compGraphic;     // pcb
}TItem;



extern DbxContext     tContext;       //  Global DBX Conversation Data
extern long           tStatus;        //  Global Return status variable

#define DLLX __stdcall


long 
DLLX TAddClassToClassAttribute     (DbxContext* pContext,       // (i/o)
                                    long      netClassId1,      // (i)
                                    long      netClassId2,      // (i)
                                    TAttribute* TAttribute);    // (i/o)
//
// TAddClassToClassAttribute - (PCB) Add an attribute (rule) to the given class to class.
// -------------------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         net  class Id number #1
//  netClassId2         long         net  class Id number #1
//  pAttribute          TAttribute*  Attribute to add
//
//  Returns             long         DBX completion status
//

  
long 
DLLX TAddClassToClassLayerRule(DbxContext* pContext,    // (i/o)
                               long        netClassId1, // (i)
                               long        netClassId2, // (i)
                         const char*       layerName,   // (i)
                               TAttribute* pAttr);      // (o)
//
// TAddClassToClassLayerRule - (PCB/Sch) Add a rule to the class to class
// -------------------------             denoted by the two netclass ids.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         id #1 of net class containing the rule
//  netClassId2         long         id #2 of net class containing the rule
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long
DLLX TAddCompAttribute     (DbxContext* pContext,       // (i/o)
                                  char* pCompRefDes,    // (i)
                            TAttribute* TAttribute);    // (i/o)
//
// TAddCompAttribute - (PCB) Add an attribute to a component
// -----------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pCompRefDes         char*        Input string containing the 
//                                   Component RefDes
//  pAttribute          TAttribute*  Attribute to add
//
//  Returns       long         DBX completion status
//


long  
DLLX  TAddDesignAttribute     (DbxContext* pContext,     // (i) dbx context info
                               TAttribute* pTAttr);      // (i/o) design attribute
//
// TAddDesignAttribute - Add an attribute to the Design
// -------------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Attribute to add
//
//  Returns       long         DBX completion status
//


long  
DLLX  TAddIncludedRoomComponent (DbxContext* pContext,        // (i/o) dbx context info
                                 long        roomId,          // (i) room to add component to
                                 TComponent* pTComponent);    // (i/o) the component to add
//
// TAddIncludedRoomComponent - Add a component to the included room component list
// -------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  roomId              long         Room to add the component to
//  pTComponent         TComponent*  Component to add
//
//  Returns       long         DBX completion status
//


long  
DLLX  TAddLayerAttribute     (DbxContext* pContext,     // (i) dbx context info
                              long        layerId,      // (i) layer id
                              TAttribute* pTAttr);      // (o) design attribute
//
// TAddLayerAttribute - (PCB) Add an attribute to the specified layer.
// ------------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  layerId             long         layer Id number
//  pTAttr              TAttribute*  Attribute to add
//
//  Returns             long         DBX completion status
//                                                 


long 
DLLX TAddNetAttribute     (DbxContext* pContext,       // (i/o)
                           long        netId,          // (i)
                           TAttribute* TAttribute);    // (i/o)
//
// TAddNetAttribute - (PCB) Add an attribute to the given net.
// ----------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         net Id number
//  pAttribute          TAttribute*  Attribute to add
//
//  Returns             long         DBX completion status
//                                                 


long 
DLLX TAddNetClassAttribute     (DbxContext* pContext,       // (i/o)
                                long      netClassId,       // (i)
                               TAttribute* TAttribute);     // (i/o)
//
// TAddNetClassAttribute - (PCB) Add an attribute to the given net class.
// ---------------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         net  class Id number
//  pAttribute          TAttribute*  Attribute to add
//
//  Returns             long         DBX completion status
//


long 
DLLX TAddNetClassLayerRule(DbxContext* pContext,   // (i/o)
                           long        netClassId, // (i)
                     const char*       layerName,  // (i)
                           TAttribute* pAttr);     // (o)
//
// TAddNetClassLayerRule - (PCB/Sch) Add a rule to the net class specified netClassId.
// ---------------------             
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         id of net class that is to contain the rule
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TAddNetClassNet     (DbxContext* pContext,       // (i/o)
                          long      netClassId,       // (i)
                          TNet*           pTNet);     // (i/o)
//
// TAddNetClassNet - (PCB) Add a net to the given net class.
// ---------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         Net class Id number
//  pTNet               TNet*        Net to add
//
//  Returns             long         DBX completion status
//


long 
DLLX TAddNetLayerRule(DbxContext* pContext,   // (i/o)
                      long        netId,      // (i)
                const char*       layerName,  // (i)
                      TAttribute* pAttr);     // (o)
//
// TAddNetLayerRule - (PCB/Sch) Add a rule to the net specified by netId.
//
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         id of net that is to contain the rule
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TAddNetNode          (DbxContext* pContext,       // (i/o)
                           long        netId,          // (i)
                           TItem*      pTItem);        // (i/o)
//
// TAddNetNode - (PCB/SCH) Add a node to a specified net
// -----------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         net Id number
//  pItem               TItem*       Node to add 
//
//  Returns             long         DBX completion status
//


long  
DLLX  TAddRoomAttribute     (DbxContext* pContext, // (i) dbx context info
                             long        roomId,   // (i) room id
                             TAttribute* pTAttr);  // (i) room attribute to add
//
// TAddRoomAttribute - (PCB) Add an attribute to the given room.
// -----------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  roomId              long         Room Id 
//  pTAttr              TAttribute*  Room attribute to add
//
//  Returns             long         DBX completion status
//


long 
DLLX TCloseComponent  (DbxContext*   pContext);


long 
DLLX TCloseDesign(DbxContext* pContext, 
                  const char* pDesignName);       
//
// TCloseDesign - (PCB/Sch) Terminates communication with the application
// ------------             indicated by pContext.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation to close
//  pDesignName   char*        For future use (not used).  Input an 
//                             empty string.
//
//  returns       long         DBX completion status
//


long 
DLLX  TCloseLibrary(DbxContext* pContext,       //  (i/o) dbx context info
                    const char* pLibraryName);  //  (i) library name, currently ignored


long 
DLLX TCopyComponent   (DbxContext*   pContext, 
                       const char*   pSCompType,
                       const char*   pSLibName,
                       const char*   pDCompType,
                       const char*   pDLibName);

long 
DLLX TCopyPattern     (DbxContext*   pContext, 
                       const char*   pSPatName,
                       const char*   pSLibName,
                       const char*   pDPatName,
                       const char*   pDLibName);

long 
DLLX TCopySymbol      (DbxContext*   pContext, 
                       const char*   pSSymbolName,
                       const char*   pSLibName,
                       const char*   pDSymbolName,
                       const char*   pDLibName);


long 
DLLX TCreateClassToClass  (DbxContext* pContext,            // (i/o) dbx context info
                           TClassToClass* pTClassToClass);  // (i/o) class to class

//
// TCreateClassToClass - (PCB/SCH) Create a new class to class in the active design
// -------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pClassToClass       TClassToClass*   Class to class to add
//                                   Valid fields used for CreateClassToClass:
//                                      - netClassName
//
//  Returns       long         DBX completion status
//


long 
DLLX TCreateNet  (DbxContext* pContext,     // (i/o) dbx context info
                  TNet*       pTNet);       // (i/o) net to place

//
// TCreateNet - (PCB/SCH) Create a new net in the active design
// ----------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pNet                TNet*        Net to add
//                                   Valid fields used for CreateNet:
//                                      - netName
//
//  Returns       long         DBX completion status
//


long 
DLLX TCreateNetClass  (DbxContext* pContext,     // (i/o) dbx context info
                       TNetClass*  pTNetClass);  // (i/o) net class to place

//
// TCreateNetClass - (PCB/SCH) Create a new net class in the active design
// ----------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pNetClass           TNetClass*   Net to add
//                                   Valid fields used for CreateNetClass:
//                                      - netClassName
//
//  Returns       long         DBX completion status
//


//
//  Delete Functions - (PCB) delete an item from the active design
//
//
//    All functions have the following parameters
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  p<item>       <DbxItem>*   DBX item to be deleted
//
//
//  returns       long         DBX completion status
//                             and p<item> updated to include have dbId=0
//
long 
DLLX TDeleteArc (DbxContext* pContext,          // (i/o) dbx context info
                 TArc*       pTArc);            // (i/o) item to Delete

long 
DLLX TDeleteAttribute(DbxContext* pContext,     // (i/o) dbx context info
                      TAttribute* pTAttr);      // (i/o) item to Delete

long 
DLLX TDeleteBus      (DbxContext* pContext,     // (i/o) dbx context info
                      TBus*       pTBus);       // (i/o) item to Delete

long 
DLLX TDeleteClassToClass (DbxContext*     pContext,         // (i/o) dbx context info
                          TClassToClass*  pTClassToClass);  // (i/o) classtoclass to Delete

long 
DLLX TDeleteClassToClassAttribute  (DbxContext* pContext,        // (i/o)
                                    long        netClassId1,     // (i)
                                    long        netClassId2,     // (i)
                                    TAttribute* TAttribute);     // (i/o)
//
// TDeleteClassToClassAttribute - (PCB) Delete an attribute associated with a 
// ----------------------------         given class to class.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         net class Id number 1
//  netClassId2         long         net class Id number 2
//  pAttribute          TAttribute*  ClassToClass attribute to delete
//
//  Returns             long         DBX completion status
//


long 
DLLX TDeleteClassToClassLayerRule(DbxContext* pContext,     // (i/o)
                                  long        netclassId1,  // (i)
                                  long        netclassId2,  // (i)
                            const char*       layerName,    // (i)
                                  TAttribute* pAttr);       // (o)
//
// TDeleteClassToClassLayerRule - (PCB/Sch) Delete a rule in the class to class 
// ----------------------------             specified by the two net class ids.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         id #1 of net class containing the rule
//  netClassId2         long         id #2 of net class containing the rule
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TDeleteCompAttribute  (DbxContext* pContext,       // (i/o)
                                  char* pCompRefDes,    // (i)
                            TAttribute* TAttribute);    // (i/o)
long 
DLLX TDeleteComponent(DbxContext* pContext,     // (i/o) dbx context info
                    TComponent* pTComponent);   // (i/o) item to Delete

//
// TDeleteCompAttribute - (PCB) Delete an attribute associated with a 
// --------------------         given component.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pCompRefDes         char*        Input string containing the 
//                                   Component RefDes
//  pAttribute          TAttribute*  Component attribute to delete
//
//  Returns             long         DBX completion status
//


long
DLLX TDeleteDetail(DbxContext* pContext,    // (i/o) dbx context info
                   TDetail*    pTDetail);   // (i/o) item to Delete
 

long  
DLLX  TDeleteDesignAttribute     (DbxContext* pContext,     // (i) dbx context info
                                  TAttribute* pTAttr);      // (i/o) design attribute
//
// TDeleteDesignAttribute - Delete an attribute associated with the Design.
// ----------------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pTAttr              TAttribute*  Component attribute to delete
//
//  Returns             long         DBX completion status
//
                                  
                                  
long
DLLX TDeleteDiagram(DbxContext* pContext,   // (i/o) dbx context info
                     TDiagram*   pTDiagram);    // (i/o) item to Delete


long 
DLLX TDeleteField  (DbxContext* pContext,     // (i/o) dbx context info
                    TField*     pTField);     // (i/o) item to Delete


long  
DLLX  TDeleteIncludedRoomComponent (DbxContext* pContext,        // (i/o) dbx context info
                                    long        roomId,          // (i) room to delete component from
                                    TComponent* pTComponent);    // (i/o) the component to delete
//
// TDeleteIncludedRoomComponent - Delete a component from the specified room's included list.
// ----------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  roomId              long         Room to delete component from
//  pTComponent         TComponent*  Component to delete
//
//  Returns             long         DBX completion status
//
                                  

long 
DLLX TDeleteItem(DbxContext* pContext,     // (i/o) dbx context info
                 TItem*      pTItem);      // (i/o) item to Delete
 

long  
DLLX  TDeleteLayerAttribute     (DbxContext* pContext,     // (i) dbx context info
                                 long        layerId,      // (i) layer id
                                 TAttribute* pTAttr);      // (o) design attribute
//
// TDeleteLayerAttribute - (PCB) Delete an attribute associated with a 
// ---------------------         specified layer.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  layerId             long         layer Id number
//  pTAttr              TAttribute*  layer attribute to delete
//
//  Returns             long         DBX completion status
//


long 
DLLX TDeleteLine(DbxContext* pContext,     // (i/o) dbx context info
                 TLine*      pTLine);      // (i/o) item to Delete

long 
DLLX TDeleteMetaFile(DbxContext* pContext,    // (i/o) dbx context info
                     TMetaFile*  pTMetaFile); // (i/o) item to Delete
 
long 
DLLX TDeleteNet (DbxContext* pContext,     // (i/o) dbx context info
                 TNet*       pTNet);       // (i/o) net to Delete

long 
DLLX TDeleteNetAttribute  (DbxContext* pContext,       // (i/o)
                           long        netId,          // (i)
                           TAttribute* TAttribute);    // (i/o)
//
// TDeleteNetAttribute - (PCB) Delete an attribute associated with a 
// -------------------         given net.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         net Id number
//  pAttribute          TAttribute*  Net attribute to delete
//
//  Returns             long         DBX completion status
//


long 
DLLX TDeleteNetClass (DbxContext* pContext,// (i/o) dbx context info
                   TNetClass*  pTNetClass);// (i/o) net class to Delete

long 
DLLX TDeleteNetClassAttribute  (DbxContext* pContext,       // (i/o)
                                long        netClassId,     // (i)
                                TAttribute* TAttribute);    // (i/o)
//
// TDeleteNetClassAttribute - (PCB) Delete an attribute associated with a 
// ------------------------         given net class.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         net class Id number
//  pAttribute          TAttribute*  Net attribute to delete
//
//  Returns             long         DBX completion status
//


long 
DLLX TDeleteNetClassLayerRule(DbxContext* pContext,   // (i/o)
                              long        netClassId, // (i)
                        const char*       layerName,  // (i)
                              TAttribute* pAttr);     // (o)
//
// TDeleteNetClassLayerRule - (PCB/Sch) Delete a rule in the net class 
// ------------------------             specified by netClassId.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         id of net class to contain the rule
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TDeleteNetClassNet  (DbxContext* pContext,       // (i/o)
                          long        netClassId,     // (i)
                          TNet*       pTNet);         // (i/o)
//
// TDeleteNetClassAttribute - (PCB) Delete a net from the 
// ------------------------         given net class.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         Net class Id number
//  pTNet               TNet*        Net to delete
//
//  Returns             long         DBX completion status
//


long 
DLLX TDeleteNetLayerRule(DbxContext* pContext,   // (i/o)
                         long        netId,      // (i)
                   const char*       layerName,  // (i)
                         TAttribute* pAttr);     // (o)
//
// TDeleteNetLayerRule - (PCB/Sch) Delete a rule in the net specified by netId.
// -------------------             
//
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         id of net that contains the rule to modify
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TDeleteNetNode       (DbxContext* pContext,       // (i/o)
                           long        netId,          // (i)
                           TItem*      pTItem);        // (i/o)
//
// TDeleteNetNode - (PCB) Delete a node from the specified net
// --------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         net Id number
//  pPad                TPad*        Node to delete (a free or component pad)
//                                   (Note that this does not delete the pad,
//                                   it just removes the pad from the net)
//
//  Returns             long         DBX completion status
//

long 
DLLX TDeletePad (DbxContext* pContext,     // (i/o) dbx context info
                 TPad*       pTPad);       // (i/o) item to Delete

long 
DLLX TDeletePin (DbxContext* pContext,     // (i/o) dbx context info
                 TPin*       pTPin);       // (i/o) item to Delete

long 
DLLX TDeletePoint(DbxContext* pContext,    // (i/o) dbx context info
                  TPoint*     pTPoint);    // (i/o) item to Delete

long 
DLLX TDeletePort (DbxContext* pContext,    // (i/o) dbx context info
                  TPort*      pTPort);     // (i/o) item to Delete


long  
DLLX  TDeleteRoomAttribute  (DbxContext* pContext, // (i) dbx context info
                             long        roomId,   // (i) room id
                             TAttribute* pTAttr);  // (i/o) room attribute
//
// TDeleteRoomAttribute - (PCB) Delete an attribute from the specified room
// --------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  roomId              long         Room Id
//  pTAttr              TAttribute*  Attribute to delete
//
//  Returns             long         DBX completion status
//

long 
DLLX TDeleteSymbol (DbxContext* pContext,    // (i/o) dbx context info
                    TSymbol*    pTSymbol);   // (i/o) item to Delete

long
DLLX TDeleteTable(DbxContext* pContext,     // (i/o) dbx context info
                  TTable*     pTTable);     // (i/o) item to Delete

long 
DLLX TDeleteText(DbxContext* pContext,     // (i/o) dbx context info
                 TText*      pTText);      // (i/o) item to Delete

long 
DLLX TDeleteVia (DbxContext* pContext,     // (i/o) dbx context info
                 TVia*       pTVia);       // (i/o) item to Delete

long 
DLLX TDeleteWire(DbxContext* pContext,     // (i/o) dbx context info
                 TWire*      pTWire);      // (i/o) item to Delete

 
long
DLLX TDeselectPrintJob (DbxContext * pContext,      // (i/o) dbx context info
                        const char * pJobName);     // (i)   print job name.
//
//  TDeselectPrintJob - (PCB/SCH) Deselect the print job from output list.
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pJobName      char*        Name of PCB Print Job or SCH Sheet
//
//  returns       long         DBX completion status
//

//
// Flip Functions - (PCB/SCH) Flip the input dbx item about the input coordinate
//
//
//    All functions have the following parameters
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTCoord       TCoord*      Point about which to flip the item.
//                             if pTCoord values = (-1,-1) the default
//                             item origin will be used as the flip point
//  p<item>       <DbxItem>*   DBX item, or TItem to be flipped
//
//
//  returns       long         DBX completion status
//                             and p<item> updated to reflect new orientation
//
// Note: TFlipComponent only applies for PCB components, and fails for SCH components
//
long 
DLLX TFlipArc      (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i) flip point
                    TArc*       pTArc);       // (i/o) item to flip

long 
DLLX TFlipAttribute(DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TAttribute* pTAttr);      // (i/o) item to flip
                                                         
long 
DLLX TFlipBus      (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TBus*       pTBus);       // (i/o) item to flip

long 
DLLX TFlipComponent(DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TComponent* pTComponent); // (i/o) item to flip
                                                         
long 
DLLX TFlipField    (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TField*     pTField);     // (i/o) item to flip
                                                         
long 
DLLX TFlipItem     (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TItem*      pTItem);      // (i/o) item to flip
 
long 
DLLX TFlipLine     (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TLine*      pTLine);      // (i/o) item to flip
                                                         
long 
DLLX TFlipPad      (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TPad*       pTPad);       // (i/o) item to flip

long 
DLLX TFlipPin      (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TPin*       pTPin);       // (i/o) item to flip

long 
DLLX TFlipPoint    (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TPoint*     pTPoint);     // (i/o) item to flip

long 
DLLX TFlipPort     (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TPort*      pTPort);      // (i/o) item to flip

long 
DLLX TFlipSymbol   (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TSymbol*    pTSymbol);    // (i/o) item to flip

long
DLLX TFlipTable    (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i) flip point
                    TTable*     pTTable);     // (i/o) item to flip

long 
DLLX TFlipText     (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TText*      pTText);      // (i/o) item to flip

long 
DLLX TFlipVia      (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TVia*       pTVia);       // (i/o) item to flip
                                                         
long 
DLLX TFlipWire     (DbxContext* pContext,     // (i/o) dbx context info
                    TCoord*     pTCoord,      // (i)   flip point
                    TWire*      pTWire);      // (i/o) item to flip
                                                         

long 
DLLX TGetClassToClassById(DbxContext* pContext,         // (i/o)
                      long netClassId1,                 // (i)
                      long netClassId2,                 // (i)
                      TClassToClass* pClassToClass);    // (o)
//
// TGetClassToClassById - (PCB/Sch) Get class to class given net class ids.
// -----------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*     Input DBX conversation data
//  netClassId1         long            net class Id number #1
//  netClassId2         long            net class Id number #2
//  pClassToClass       TClassToClass*  class to class to fill in
//  Returns             long            DBX completion status
//


long 
DLLX TGetCompByRefDes(DbxContext* pContext, 
                      const char* pCompRefDes, 
                      TComponent* pComponent);
//
// TGetCompByRefDes - (PCB/Sch) Get Component Data by Reference Designator.
// ----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pCompRefDes   char*        Input string containing the Component
//                             RefDes
//  pComponent    TComponent*  Output Component item
//
//  returns       long         DBX completion status
//

long 
DLLX TGetCompByType  (DbxContext* pContext, 
                      const char* pCompType, 
                      TComponent* pComponent);
//
// TGetCompByType - (CMP) Get Component Data by Component name.
// ----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pCompType     char*        Input string containing the Component Name
//  pComponent    TComponent*  Output Component item
//
//  returns       long         DBX completion status
//


long 
DLLX TGetCompSymbolByPartNumber (DbxContext* pContext, 
                                 const char* pRefDes, 
                                 long        partNumber,
                                 TSymbol*    pTSymbol);
//
// TGetCompSymbolByRefDes - (Sch) Get data for a symbol by the Symbol part number.
// ----------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pRefDes       char*        Input string containing the 
//                             Component RefDes (e.g. U1)
//  partNumber    long         Symbol part number (1, 2, 3...)
//  pTSymbol      TSymbol*     Output component symbol
//
//
//  Returns       long         DBX completion status
//
                  
long 
DLLX TGetCompSymbolByRefDes (DbxContext* pContext, 
                             const char* pSymRefDes, 
                             TSymbol*    pTSymbol);
//
// TGetCompSymbolByRefDes - (Sch) Get data for a symbol by the Symbol RefDes.
// ----------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pSymRefDes    char*        Input string containing the 
//                             Symbol RefDes (e.g. U1:A)
//  pTSymbol      TSymbol*     Output component symbol
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetDesignInfo(DbxContext* pContext, 
                    TDesign* pDesignInfo);
//
// TGetDesignInfo - (PCB/Sch) Return Design Information for the Current Design.
// --------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pDesignInfo   TDesign*     Output Design Information
//
//
//  returns       long         DBX completion status
//
 

long 
DLLX TGetFirstBusNet  (DbxContext* pContext, 
                       const char* pBusName, 
                       TNet*       pTNet);

long 
DLLX TGetFirstClassToClass(DbxContext* pContext, 
                           TClassToClass* pTClassToClass);
//
// TGetFirstClassToClass - (PCB/Sch) Return data for the first classToclass in the design.
// ---------------------
//
//  parameter      Type/Description
//  ---------      ----------------
//
//  pContext       DbxContext*       Input DBX conversation data
//  pTClassToClass TClassToClass*    Output ClassToClass data
//
//
//  Returns        long         DBX completion status
//


long 
DLLX TGetFirstClassToClassAttribute(DbxContext* pContext,       // (i/o)
                                    long        netClassId1,    // (i)
                                    long        netClassId2,    // (i)
                                    TAttribute* TAttribute);    // (o)
//
// TGetFirstClassToClassAttribute - (PCB/Sch) Get First Attribute (Rule) associated
// ------------------------------             with a given classToclass.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         net class Id number #1
//  netClassId2         long         net class Id number #2
//  pAttribute          TAttribute*  Output net attribute
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstClassToClassLayerRule(DbxContext* pContext,       // (i/o)
                                    long        netClassId1,    // (i)
                                    long        netClassId2,    // (i)
                              const char*       layerName,      // (i)
                                    TAttribute* pAttr);         // (o)
//
// TGetFirstClassToClassLayerRule - (PCB/Sch) Get First layer rule associated
// ------------------------------             with a given ClassToClass name.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         id #1 of net class containing the rule
//  netClassId2         long         id #2 of net class containing the rule
//  layerName     const char*        layer name
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstClassToClassLayerRuleLayerName(DbxContext* pContext,       // (i/o)
                                             long        netClassId1,    // (i)
                                             long        netClassId2,    // (i)
                                             TLayer*     pLayer);        // (o)
//
// TGetFirstClassToClassLayerRuleLayerName - (PCB/Sch) Get First layer name associated
// ---------------------------------------             with a given ClassToClass rule.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         net class id #1
//  netClassId2         long         net class id #2
//  pLayer              TLayer*      Output layer name; only name is valid
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstCompGraphic(DbxContext* pContext,             // (i/o)
                          const char* pCompRefDes,          // (i)
                          TCompGraphic *pTCompGraphic);     // (o)
//
// TGetFirstCompGraphic - (PCB) Get first Graphic of a given Component.
// ----------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pCompRefDes         char*         Input string of Component RefDes
//  pTCompGraphic       TCompGraphic* Output Component Graphic
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextCompGraphic(DbxContext* pContext,         // (i/o)
                         TCompGraphic *pTCompGraphic); // (o)
//
// TGetNextCompGraphic - (PCB) Get next successive Component Graphic.
// ---------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pTCompGraphic       TCompGraphic* Output Component Graphic
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetCompGraphicByOrientation(DbxContext* pContext,
                                  const char* pCompRefDes,
                                  long orientation,
                                  TCompGraphic *pTCompGraphic);
//
// TGetCompGraphicByOrientation - (PCB) Get Graphic associated to given
// ------------------------------       Component orientation.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pCompRefDes         char*         Input string of Component RefDes
//  orientation         long          Input orientation indicator (#define)
//  pTCompGraphic       TCompGraphic* Output Component Graphic
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstCompGraphicPad(DbxContext* pContext,
                             const char* pCompRefDes,
                             const char* pCompGraphicName,
                             TPad *pCompPad);
//
// TGetFirstCompGraphicPad - (PCB) Get first Component Graphic Pad.
// -------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pCompRefDes         char*         Input string of Component RefDes
//  pCompGraphicName    char*         Input string of Component Graphic Name
//  pCompPad            TPad*         Output Pad
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextCompGraphicPad(DbxContext* pContext,
                            TPad *pCompPad);
//
// TGetNextCompGraphicPad - (PCB) Get next successive Component Graphic Pad.
// ------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pCompPad            TPad*         Output Pad
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstCompGraphicAttribute(DbxContext* pContext,         // (i/o)
                                   const char* pCompRefDes,      // (i)
                                   const char* pCompGraphicName, // (i)
                                   TAttribute* pTAttr);          // (o)
//
// TGetFirstCompGraphicAttribute - (PCB) Get first Component Graphic Attribute.
// -------------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pCompRefDes         char*         Input string of Component RefDes
//  pCompGraphicName    char*         Input string of Component Graphic Name
//  pCompPad            TAttribute*   Output Attribute
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextCompGraphicAttribute(DbxContext* pContext, // (i/o)
                                  TAttribute* pTAttr);  // (o)
//
// TGetNextCompGraphicAttribute - (PCB) Get next successive Component Graphic Attribute.
// ------------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pTAttr              TAttribute*   Output Attribute
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstCompGraphicItem(DbxContext* pContext,
                              const char* pCompRefDes,
                              const char* pCompGraphicName,
                              TItem* pCompItem);      
//
// TGetFirstCompGraphicItem - (PCB) Get first Component Graphic Item.
// --------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pCompRefDes         char*         Input string of Component RefDes
//  pCompGraphicName    char*         Input string of Component Graphic Name
//  pCompItem           TItem*        Output Item (exclusive of Pads / Attributes)
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextCompGraphicItem(DbxContext* pContext,
                             TItem* pCompItem);
//
// TGetNextCompGraphicItem - (PCB) Get next successive Component Graphic Item.
// -------------------------
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*   Input DBX conversation data
//  pCompItem           TItem*        Output Item (exclusive of Pads / Attributes)
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstCompAttribute(DbxContext* pContext,      // (i/o)
                            const char* pCompRefDes,   // (i)
                            TAttribute* TAttribute);   // (o)
//
// TGetFirstCompAttribute - (PCB/Sch) Get First Attribute Associated with a 
// ----------------------             given Component.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pCompRefDes         char*        Input string containing the 
//                                   Component RefDes
//  pAttribute          TAttribute*  Output component Attribute
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstCompItem(DbxContext* pContext, 
                       const char* pCompRefDes, 
                       TItem* pCompItem);      
//
// TGetFirstCompItem - (PCB) Get first pattern item defining a component.
// -----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pCompRefDes   char*        Input string containing the 
//                             Component RefDes
//  pCompItem     TItem*       Output component pattern item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstComponent (DbxContext* pContext, 
                         TComponent* pComponent);
//
// TGetFirstComponent - (PCB/Sch) Get data for first component.
// ------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pComponent    TComponent*  Output component item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstCompPad (DbxContext* pContext, 
                       const char* pCompRefDes, 
                       TPad *pCompPad);
//
// TGetFirstCompPad - (PCB) Get data for a components first pad.
// ----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pCompRefDes   char*        Input string containing the 
//                             Component RefDes
//  pCompPad      TPad*        Output component pad
//
//
//  Returns       long         DBX completion status
//

long 
DLLX TGetFirstCompPin    (DbxContext* pContext, 
                          const char* pCompRefDes, 
                          TPin*   pTPin);
//
// TGetFirstCompPin - (Sch) Get data for a component's first Pin.
// -----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pCompRefDes   char*        Input string containing the 
//                             Component RefDes (e.g. U1)
//  pTPin         TPin*        Output component pin
//
//
//  Returns       long         DBX completion status
//

long 
DLLX TGetFirstCompSymbol (DbxContext* pContext, 
                          const char* pCompRefDes, 
                          TSymbol*    pTSymbol);
//
// TGetFirstCompSymbol - (Sch) Get data for a component's first symbol.
// -------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pCompRefDes   char*        Input string containing the 
//                             Component RefDes (e.g. U1)
//  pTSymbol      TSymbol*     Output component symbol
//
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetFirstDesignAttribute (DbxContext*  pContext,  // (i) dbx context info
                                TAttribute*    pTAttr); // (o) dbx attribute
//
// TGetFirstDesignAttribute - (PCB/Sch) Get First global Attribute associated
// ------------------------             with the design.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pTAttr              TAttribute*  Output net attribute
//
//  Returns             long         DBX completion status
//


long  
DLLX  TGetFirstGrid (DbxContext* pContext,   // (i/o) dbx context info
                     TGrid*      pTGrid);    // (o) grid data
//
// TGetFirstGrid -  Get first Grid on GridList. 
// -------------    
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pTGrid              TGrid*       Grid data
//
//  Returns             long         DBX completion status
//


long 
DLLX  TGetFirstIncludedRoomComponent(DbxContext* pContext,     // (i/o) cntext 
                                     long        roomId,       // (i) room id
                                     TComponent* pTComponent); // (o) component data
//
// TGetFirstIncludedRoomComponent - (PCB) Get first Component on the specified room's 
// ------------------------------         Component Include list.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  roomId              long         Room Id
//  pTComponent         TComponent*  Component data
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstLayer (DbxContext* pContext, 
                     TLayer* pLayer);
//
// TGetFirstLayer - (PCB/Sch) Return data for the first layer in the design.
// --------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pLayer        TLayer*      Output layer data
//
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetFirstLayerAttribute (DbxContext*  pContext,  // (i) dbx context info
                               long         layerId,   // (i) layer id
                               TAttribute*  pTAttr);   // (i/o) TAttribute 
//
// TGetFirstLayerAttribute - (PCB/Sch) Get the first attribute of a layer.
// -----------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  layerId       long         Input Layer number
//  pTAttr        TAttribute*  Output layer attribute
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstLayerItem (DbxContext* pContext, 
                         long layerId, 
                         TItem* pLayerItem);
//
// TGetFirstLayerItem - (PCB/Sch) Get the first item on a layer.
// ------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  layerId       long         Input Layer number
//  pLayerItem    TItem*       Output layer item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstNet(DbxContext* pContext, 
                  TNet* pNet);
//
// TGetFirstNet - (PCB/Sch) Return data for the first net in the design.
// ------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pNet          TNet*        Output Net data
//
//
//  Returns       long         DBX completion status
//

long 
DLLX TGetFirstNetClass(DbxContext* pContext, 
                  TNetClass* pNetClass);
//
// TGetFirstNetClass - (PCB/Sch) Return data for the first net class in the design.
// -----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pNetClass     TNetClass*   Output NetClass data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstNetAttribute(DbxContext* pContext,       // (i/o)
                           long        netId,          // (i)
                           TAttribute* TAttribute);    // (o)
//
// TGetFirstNetAttribute - (PCB/Sch) Get First Attribute associated with a 
// ---------------------             given net.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         net Id number
//  pAttribute          TAttribute*  Output net attribute
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstNetClassAttribute(DbxContext* pContext,       // (i/o)
                                long        netClassId,     // (i)
                                TAttribute* TAttribute);    // (o)
//
// TGetFirstNetClassAttribute - (PCB/Sch) Get First Attribute associated with a 
// --------------------------             given net class.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         net class Id number
//  pAttribute          TAttribute*  Output net attribute
//
//  Returns             long         DBX completion status
//


long  
DLLX  TGetFirstNetClassNet (DbxContext* pContext,   // (i/o) dbx context info.
                            long        netClassId, // (i) which net class 
                            TNet*       pTNet);     // (o) net data
//
// TGetFirstNetClassNet - (PCB/Sch) Get first net in a given netclass.
// --------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  netClassId    long         Input NetClass number
//  pTNet         TNet*        Output net node item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstNetClassLayerRule(DbxContext* pContext,   // (i/o)
                                long        netClassId, // (i)
                          const char*       layerName,  // (i)
                                TAttribute* pAttr);     // (o)
//
// TGetFirstNetClassLayerRule - (PCB/Sch) Get First layer rule associated
// --------------------------             with a given net class name.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         id of net class containing the rule
//  layerName     const char*        layer name
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstNetClassLayerRuleLayerName(DbxContext* pContext,   // (i/o)
                                         long        netClassId, // (i)
                                         TLayer*     pLayer);    // (o)
//
// TGetFirstNetClassLayerRuleLayerName - (PCB/Sch) Get First layer name associated
// -----------------------------------             with a given netclass rule.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netclassId          long         netclass Id
//  pLayer              TLayer*      Output layer name; only name is valid
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstNetItem (DbxContext* pContext, 
                       long netId, 
                       TItem* pNetItem);
//
// TGetFirstNetItem - (PCB) Get first item in a net given a netID.
// ----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  netId         long         Input Net number
//  pNetItem      TItem*       Output net item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstNetLayerRule(DbxContext* pContext,   // (i/o)
                           long        netId,      // (i)
                     const char*       layerName,  // (i)
                           TAttribute* pAttr);     // (o)
//
// TGetFirstNetLayerRule - (PCB/Sch) Get First layer rule associated
// ---------------------             with a given net name.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         id of net containing the rule
//  layerName     const char*        name of layer containing the rule
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstNetLayerRuleLayerName(DbxContext* pContext,   // (i/o)
                                    long        netId,      // (i)
                                    TLayer*     pLayer);    // (o)
//
// TGetFirstNetLayerRuleLayerName - (PCB/Sch) Get First layer name associated
// ------------------------------             with a given net rule.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         net Id
//  pLayer              TLayer*      Output layer name; only name is valid
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetFirstNetNode(DbxContext* pContext,     // (i/o)
                      long        netId,        // (i)
                      TItem*      pNetNode);    // (o)
//
// TGetFirstNetNode - (PCB/Sch) Get first node in a net given netID.
// ----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  netId         long         Input Net number
//  pNetItem      TItem*       Output net node item
//
//
//  Returns       long         DBX completion status
//


long
DLLX TGetFirstPattern (DbxContext*  pContext,
                       TPattern*    pTPattern);
//
// TGetFirstPattern - (PCB) Get first pattern found in design.
// ----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPattern     TPattern*    Output pattern
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstPolyPadPoint(DbxContext* pContext, 
                           long        styleId,
                           long        layerNum, 
                           TPoint*     pPolyPoint);
//
// TGetFirstPolyPadPoint - (PCB) Get first point defining a pad's polygon.
// ---------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  styleId       long         Input pad's style ID number
//  layerNum      long         Input layer number
//  pPolyPoint    TPoint*      Output pad's first polygon point
//
//
//  Returns       long         DBX completion status
//


long  
DLLX TGetFirstPolyPoint (DbxContext* pContext,     // (i/o) context 
                         long        polyId,       // (i) polygon dbid
                         TPoint*     pPolyPoint);  // (o) point data
//
// TGetFirstPolyPoint - (PCB) Get first point defining a polygon.
// ------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  polyId        long         Input Polygon ID number
//  pPolyPoint    TPoint*      Output polygon point
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstPrintJob(DbxContext * pContext, 
                       TPrintJob  * pPrintJob );
//
// TGetFirstPrintJob - (PCB/SCH) Get first print job.
// ------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pPrintJob     TPrintJob*   Output print job.
//
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetFirstRoom (DbxContext* pContext,    // (i/o) dbx context info.
                     TRoom*      pTRoom);     // (o) room data
//
// TGetFirstRoom - (PCB) Get first room.
// -------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTRoom        TRoom*       Output room.
//
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetFirstRoomAttribute (DbxContext*  pContext,    // (i) dbx context info
                              long         roomId,      // (i) room id
                              TAttribute*  pTAttr);     // (o) attribute to return
//
// TGetFirstRoomAttr - (PCB) Get first room attribute.
// -----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  roomId        long         Room identifier
//  pTAttr        TAttribute*  Attribute data
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetFirstRoomPoint (DbxContext* pContext,   // (i/o) context 
                                   long roomId,   // (i) room dbid
                               TPoint* pTPoint);  // (o) point data
//
// TGetFirstRoomPoint - (PCB) Get first room point--the first of the defining points.
// ------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  roomId        long         Room dbId
//  pTPoint       TPoint*      Point data
//
//
//  Returns       long         DBX completion status
//
                               
                               
long 
DLLX TGetFirstSelectedItem (DbxContext* pContext, 
                            TItem* pSelectItem);
//
// TGetFirstSelectedItem - (PCB/Sch) Get the first item in the selection list
// ---------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pLayerItem    TItem*       Output selected item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetFirstSymAttribute(DbxContext* pContext,      // (i/o)
                            const char* pCompRefDes,   // (i)
                            TAttribute* TAttribute);   // (o)
//
// TGetFirstSymAttr         - (Sch) Get First Attribute Associated with a 
// ----------------------             given Symbol.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pCompRefDes         char*        Input string containing the 
//                                   Component RefDes:PartNumber
//  pAttribute          TAttribute*  Output component Attribute
//
//  Returns       long         DBX completion status
//


long
DLLX TGetFirstSymbol  (DbxContext*  pContext,
                       TSymbol*     pTSymbol);

long 
DLLX TGetFirstSymbolPin  (DbxContext* pContext, 
                          const char* pSymbolRefDes, 
                          TPin*       pTPin);
//
// TGetFirstSymbolPin - (Sch) Get data for a symbols's first Pin.
// ------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pSymbolRefDes char*        Input string containing the 
//                             Symbol RefDes (e.g. U1:A)
//  pTPin         TPin*        Output component pin
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetLayerById  (DbxContext* pContext, 
                     long layerId, 
                     TLayer* pLayer);                          
//
// TGetLayerByID - (PCB/Sch) Return layer data by layer number.
// -------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  layerId       long         Input layer number
//  pLayer        TLayer*      Output layer data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetLayerByName(DbxContext* pContext, 
                     const char* pLayerName, 
                     TLayer* pLayer);     
//
// TGetLayerByName - (PCB/Sch) Return layer data by layer name.
// ---------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  layerName     char*        Input string containing Layer name
//  pLayer        TLayer*      Output layer data
//
//
//  Returns       long         DBX completion status
//



long 
DLLX TGetNetById  (DbxContext* pContext, 
                   long netId, 
                   TNet* pNet);
//
// TGetNetByID - (PCB/Sch) Get net data by net ID.
// -----------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  NetId         long         Input net number
//  pNet          TNet*        Output net data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNetByName(DbxContext* pContext, 
                   const char* pNetName, 
                   TNet* pNet);
//
// TGetNetByName - (PCB/Sch) Return design net data by net name.
// -------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pNetName      char*        Input string containing net name
//  pNet          TNet*        Output net data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNetClassById (DbxContext* pContext, 
                            long netClassId, 
                       TNetClass* pNetClass);
//
// TGetNetClassById - (PCB/Sch) Get net data by net class ID.
// ----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  NetClassId    long         Input net class number
//  pNetClass     TNetClass*   Output net class data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextBusNet   (DbxContext* pContext, 
                       TNet*       pTNet);

long 
DLLX TGetNextClassToClass(DbxContext* pContext, 
                          TClassToClass* pTClassToClass);
//
// TGetNextClassToClass - (PCB/Sch) Return data for the next classToclass in the design.
// --------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*       Input DBX conversation data
//  pClassToClass TClassToClass*    Output ClassToClass data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextClassToClassAttribute(DbxContext* pContext,       // (i/o)
                                   TAttribute* TAttribute);    // (o)
//
// TGetNextClassToClassAttribute - (PCB/Sch) Get Next Attribute (Rule) associated
// -----------------------------             with a given classToclass.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Output net attribute
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextClassToClassLayerRule(DbxContext* pContext,   // (i/o)
                                   TAttribute* pAttr);     // (o)
//
// TGetNextClassToClassLayerRule - (PCB/Sch) Get Next layer rule associated
// -----------------------------             with a given ClassToClass name.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextClassToClassLayerRuleLayerName(DbxContext* pContext,   // (i/o)
                                            TLayer*     pLayer);    // (o)
//
// TGetNextClassToClassLayerRuleLayerName - (PCB/Sch) Get Next layer name associated
// --------------------------------------             with a given ClassToClass rule.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pLayer              TLayer*      Output layer name; only name is valid
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextCompAttribute (DbxContext* pContext,      // (i/o)
                            TAttribute* TAttribute);   // (o)
//
// TGetNextCompAttribute - (PCB/Sch) Get the next Attribute Associated with a 
// ---------------------             given Component.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Output component Attribute
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextComponent (DbxContext* pContext, 
                        TComponent* pComponent);
//
// TGetNextComponent - (PCB/Sch) Get next component.  Must be preceded by 
// -----------------             TGetFirstComponent.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pComponent    TComponent*  Output component item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextCompItem (DbxContext* pContext, 
                       TItem* pCompItem);                 
//
// TGetNextCompItem - (PCB) Get next item defining a component pattern. 
// ----------------         Must be preceded by TGetFirstCompItem.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pCompItem     TItem*       Output component item
//
//
//  Returns       long         DBX completion status
//

             


long 
DLLX TGetNextCompPad (DbxContext* pContext, 
                      TPad *pCompPad);                
//
// TGetNextCompPad - (PCB) Get data for next pad on the same component.  
// ---------------         Must be preceded by TGetFirstCompPad.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pCompPad      TPad*        Output component pad
//
//
//  Returns       long         DBX completion status
//

long 
DLLX TGetNextCompPin    (DbxContext* pContext, 
                         TPin*   pTPin);
//
// TGetNextCompPin - (Sch) Get data for a component's Next Pin.
// ---------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPin         TPin*        Output component pin
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextCompSymbol  (DbxContext* pContext, 
                          TSymbol*    pTSymbol);
//
// TGetFirstCompSymbol - (Sch) Get data for a component's next symbol.
// -------------------         Must be preceded by GetFirstCompSymbol().
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTSymbol      TSymbol*     Output component symbol
//
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetNextDesignAttribute (DbxContext*  pContext,  // (i) dbx context info
                               TAttribute*    pTAttr); // (o) dbx attribute
//
// TGetNextDesignAttribute - (PCB/Sch) Get Next global Attribute associated
// -----------------------             with the design.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pTAttr              TAttribute*  Output net attribute
//
//  Returns             long         DBX completion status
//



long  
DLLX  TGetNextGrid (DbxContext* pContext,  //  (i/o) dbx context info
                    TGrid*      pTGrid);   //  (o) Grid data 
//
// TGetNextGrid -  Get next Grid on GridList. 
// ------------    
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pTGrid              TGrid*       Grid data
//
//  Returns             long         DBX completion status
//


                    
long  
DLLX  TGetNextIncludedRoomComponent (DbxContext* pContext,      // (i/o) context
                                     TComponent* pTComponent);    // (o) component data
//
// TGetNextIncludedRoomComponent - (PCB) Get Next Component on the Rooms Included
// -----------------------------         Component list.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pTComponent         TComponent*  Output room component
//
//  Returns             long         DBX completion status
//



long 
DLLX TGetNextLayer (DbxContext* pContext, 
                    TLayer* pLayer);
//
// TGetNextLayer - (PCB/Sch) Return next layer data.  Must be preceded by 
// -------------             TGetFirstLayer.
//                 
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pLayer        TLayer*      Output layer item
//
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetNextLayerAttribute (DbxContext*  pContext,  // (i) dbx context info
                              TAttribute*    pTAttr); // (o) TAttribute
//
//
// TGetNextLayerAttribute - (PCB/Sch) Get the next attribute of a layer.
// ----------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTAttr        TAttribute*  Output layer attribute
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextLayerItem (DbxContext* pContext, 
                        TItem* pLayerItem);
//
//
// TGetNextLayerItem - (PCB/Sch) Get the next item on a layer.
// -----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pLayerItem    TItem*       Output layer item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextNet (DbxContext* pContext, 
                  TNet* pNet);
//
// TGetNextNet - (PCB/Sch) Return next net data.  Must be preceded by 
// -----------             GetFirstNet.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pNet          TNet*        Output Net data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextNetAttribute (DbxContext* pContext,       // (i/o)
                           TAttribute* TAttribute);    // (o)
//
// TGetNextNetAttribute - (PCB/Sch) Get the next Attribute associated with a 
// --------------------             given net.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Output component Attribute
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextNetClass (DbxContext* pContext, 
                       TNetClass* pNetClass);
//
// TGetNextNetClass - (PCB/Sch) Return next net class data.  Must be preceded by 
// ----------------             GetFirstNetClass.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pNetClass     TNetClass*   Output NetClass data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextNetClassAttribute (DbxContext* pContext,       // (i/o)
                                TAttribute* TAttribute);    // (o)
//
// TGetNextNetClassAttribute - (PCB/Sch) Get the next Attribute associated with a 
// -------------------------             given net class.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Output component Attribute
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextNetClassLayerRule(DbxContext* pContext,   // (i/o)
                               TAttribute* pAttr);     // (o)
//
// TGetNextNetClassLayerRule - (PCB/Sch) Get Next layer rule associated
// -------------------------             with a given net class name.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextNetClassLayerRuleLayerName(DbxContext* pContext,   // (i/o)
                                        TLayer*     pLayer);    // (o)
//
// TGetNextNetClassLayerRuleLayerName - (PCB/Sch) Get Next layer name associated
// ----------------------------------             with a given netclass rule.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pLayer              TLayer*      Output layer name; only name is valid
//
//  Returns             long         DBX completion status
//


long  
DLLX  TGetNextNetClassNet (DbxContext* pContext,   // (i/o) dbx context info.
                            TNet*       pTNet);     // (o) net data
//
// TGetNextNetClassNet - (PCB/Sch) Get next net in a given netclass.
// -------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTNet         TNet*        Output net node item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextNetItem (DbxContext* pContext, 
                      TItem* pNetItem);
//
// TGetNextNetItem - (PCB) Get the next item from same net.  Must be 
// ---------------         preceded by TGetFirstNetItem.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pNetItem      TItem*       Output net item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextNetLayerRule(DbxContext* pContext,   // (i/o)
                          TAttribute* pAttr);     // (o)
//
// TGetNextNetLayerRule - (PCB/Sch) Get Next layer rule associated
// --------------------             with a given net name.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextNetLayerRuleLayerName(DbxContext* pContext,   // (i/o)
                                   TLayer*     pLayer);    // (o)
//
// TGetNextNetLayerRuleLayerName - (PCB/Sch) Get Next layer name associated
// -----------------------------            with a given net rule.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pLayer              TLayer*      Output layer name; only name is valid
//
//  Returns             long         DBX completion status
//


long 
DLLX TGetNextNetNode(DbxContext* pContext, 
                     TItem* pNetNode);
//
// TGetNextNetNode - (PCB/Sch) Get next node from a net.  Must be 
// ---------------             preceded by TGetFirstNetNode.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pNetItem      TItem*       Output net node item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextPattern  (DbxContext*  pContext,
                       TPattern*    pTPattern);
//
// TGetNextPattern - (PCB) Get next pattern found in the design. Must be 
// ---------------         preceded by TGetFirstPattern.
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPattern     TPattern*    Output pattern
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextPolyPadPoint(DbxContext* pContext, 
                          TPoint*     pPolyPoint);
//
// TGetNextPolyPadPoint - (PCB) Get next point from a pad's polygon.  Must be 
// --------------------         preceded by TGetFirstPolyPadPoint.
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pPolyPoint    TPoint*      Output pad's polygon point
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextPolyPoint(DbxContext* pContext, 
                       TPoint*     pPolyPoint);
//
// TGetNextPolyPoint - (PCB) Get next point from a polygon.  Must be 
// -----------------         preceded by TGetFirstPolyPoint.
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pPolyPoint    TPoint*      Output polygon point
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextPrintJob(DbxContext * pContext, 
                      TPrintJob  * pPrintJob );
//
// TGetNextPrintJob - (PCB/SCH) Get next print job.  Must be
// ------------------           preceded by TGetFirstPrintJob.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pPrintJob     TPrintJob*   Output print job.
//
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetNextRoom (DbxContext* pContext,    // (i/o) dbx context info.
                    TRoom*      pTRoom);     // (o) room data
//
// TGetNextRoom - (PCB) Get next room in the selection list.
// ------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTRoom        TRoom*       Output room.
//
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetNextRoomAttribute (DbxContext*  pContext,    // (i) dbx context info
                             TAttribute*  pTAttr);     // (o) attribute to return
//
// TGetNextRoomAttr - (PCB) Get next room attribute from the list of attributes.
// -----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTAttr        TAttribute*  Attribute data
//
//  Returns       long         DBX completion status
//


long  
DLLX  TGetNextRoomPoint (DbxContext* pContext,   // (i/o) context 
                              TPoint* pTPoint);  // (o) point data
//
// TGetNextRoomPoint - (PCB) Get next room point in the selection list.
// -----------------         This is a defining point of the room.
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPoint       TPoint*      Point data
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextSelectedItem (DbxContext* pContext, 
                            TItem* pSelectItem);
//
// TGetNextSelectedItem - (PCB/Sch) Get the next item in the selection list
// --------------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pLayerItem    TItem*       Output selected item
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetNextSymAttribute (DbxContext* pContext,      // (i/o)
                            TAttribute* TAttribute);   // (o)
//
// TGetNextSymAttr            - (Sch) Get the next Attribute Associated with a 
// ---------------------             given Symbol.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pAttribute          TAttribute*  Output component Attribute
//
//  Returns       long         DBX completion status
//

                               
long
DLLX TGetNextSymbol   (DbxContext*  pContext,
                       TSymbol*     pTSymbol);

long 
DLLX TGetNextSymbolPin    (DbxContext* pContext, 
                         TPin*       pTPin);
//
// TGetNextSymbolPin - (Sch) Get data for a symbols's Next Pin.
// -----------------
//
//  parameter     Type/Description
//  ---------     ----------------
//
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPin         TPin*        Output symbol pin
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TGetPadShapeByLayer(DbxContext* pContext, 
                         long padStyleId,
                         long layerId, 
                         TPadViaShape* pPadShape);
//
// TGetPadShapeByLayer - (PCB) Get pad shape information for a pad 
// -------------------   style on a given layer.
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*   Input DBX conversation data
//  padStyleId    long          Input pad style ID number
//  layerId       long          Input layer number
//  pPadShape     TPadViaShape* Output pad shape data
//
//
//  Returns       long          DBX completion status
//


long 
DLLX TGetPadStyle (DbxContext* pContext, 
                   long padStyleId, 
                   TPadViaStyle* pPadStyle);
//
// TGetPadStyle  - (PCB) Return pad style data given a PadStyleID.
// ------------
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*   Input DBX conversation data
//  padStyleId    long          Input pad style ID number
//  pPadStyle     TPadViaStyle* Output pad style data
//
//
//  Returns       long          DBX completion status
//


long
DLLX TGetPatternByName(DbxContext*  pContext,
                       const char*  pPatternName,
                       TPattern*    pTPattern);


long
DLLX TGetSymbolByName (DbxContext*  pContext,
                       const char*  pSymbolName,
                       TSymbol*     pTSymbol);

long 
DLLX TGetTextStyle (DbxContext* pContext, 
                    long textStyleId, 
                    TTextStyle* pTextStyle);
//
// TGetTextStyle - (PCB) Return text style data given a TextStyleID.
// -------------
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*   Input DBX conversation data
//  textStyleId   long          Input text style ID number
//  pTextStyle    TTextStyle*   Output text style data
//
//
//  Returns       long          DBX completion status
//


long 
DLLX TGetViaShapeByLayer(DbxContext* pContext, 
                         long viaStyleId, 
                         long layerId, 
                         TPadViaShape* pViaShape);
//
// TGetViaShapeByLayer - (PCB) Get via shape information for a via 
// -------------------         style on a given layer.
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*   Input DBX conversation data
//  viaStyleId    long          Input via style ID number
//  layerId       long          Input layer number
//  pViaShape     TPadViaShape* Output via shape data
//
//
//  Returns       long          DBX completion status
//


long 
DLLX TGetViaStyle (DbxContext* pContext, 
                   long viaStyleId, 
                   TPadViaStyle* pViaStyle);
//
// TGetViaStyle - (PCB) Return via style data given a ViaStyleID.
// ------------
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*   Input DBX conversation data
//  viaStyleId    long          Input via style ID number
//  pViaStyle     TPadViaStyle* Output via style data
//
//
//  Returns       long          DBX completion status
//


//
//  Highlight Functions - (PCB/SCH) highlight the input DBX item
//
//
//    All functions have the following parameters
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  color         long         highlight color (1 or 2)
//  p<item>       <DbxItem>*   DBX item to be moved
//
//  returns       long         DBX completion status
//                             and p<item> updated to reflect highlight status
//
// Note: THighlightComponent only applies for PCB components, and fails for SCH components
//
long 
DLLX THighlightArc (DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TArc*       pTArc);       // (i/o) item to highlight

long 
DLLX THighlightAttribute(DbxContext* pContext,// (i/o) dbx context info
                         long        color,   // (i)   highlight color
                         TAttribute* pTAttr); // (i/o) item to highlight

long 
DLLX THighlightBus      (DbxContext* pContext,// (i/o) dbx context info
                         long        color,   // (i)   highlight color
                         TBus*       pTBus);  // (i/o) item to highlight

long 
DLLX THighlightComponent(DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TComponent* pTComponent); // (i/o) item to highlight

long 
DLLX THighlightDetail (DbxContext* pContext,      // (i/o) dbx context info
                       long        color,         // (i)   highlight color
                       TDetail*    pTDetail);     // (i/o) item to unhighlight

long 
DLLX THighlightDiagram (DbxContext* pContext,      // (i/o) dbx context info
                        long        color,         // (i)   highlight color
                        TDiagram*   pTDiagram);    // (i/o) item to unhighlight

long 
DLLX THighlightField  (DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TField*     pTField);     // (i/o) item to highlight

long 
DLLX THighlightItem(DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TItem*      pTItem);      // (i/o) item to highlight

long 
DLLX THighlightLine(DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TLine*      pTLine);      // (i/o) item to highlight

long 
DLLX THighlightMetaFile (DbxContext* pContext,      // (i/o) dbx context info
                         long        color,         // (i)   highlight color
                         TMetaFile*  pTMetaFile);   // (i/o) item to unhighlight

long 
DLLX THighlightNet (DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TNet*       pTNet);       // (i/o) net to highlight

long 
DLLX THighlightPad (DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TPad*       pTPad);       // (i/o) item to highlight

long 
DLLX THighlightPin (DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TPin*       pTPin);       // (i/o) item to highlight

long 
DLLX THighlightPoint(DbxContext* pContext,    // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TPoint*     pTPoint);     // (i/o) item to highlight

long 
DLLX THighlightPort (DbxContext* pContext,    // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TPort*      pTPort);      // (i/o) item to highlight

long  
DLLX  THighlightRoom  (DbxContext* pContext,  // (i/o) dbx context info
                       long        color,     // (i)   highlight color
                       TRoom*      pTRoom);   // (i/o) object to highlight

long 
DLLX THighlightSymbol (DbxContext* pContext,     // (i/o) dbx context info
                       long        color,        // (i)   highlight color
                       TSymbol*    pTSymbol);    // (i/o) item to highlight

long
DLLX THighlightTable(DbxContext* pContext,    // (i/o) dbx context info
                     long        color,       // (i)   highlight color
                     TTable*     pTTable);    // (i/o) item to highlight

long 
DLLX THighlightText(DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TText*      pTText);      // (i/o) item to highlight

long 
DLLX THighlightVia (DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TVia*       pTVia);       // (i/o) item to highlight

long 
DLLX THighlightWire(DbxContext* pContext,     // (i/o) dbx context info
                    long        color,        // (i)   highlight color
                    TWire*      pTWire);      // (i/o) item to highlight


long 
DLLX TModifyArc (DbxContext* pContext,          // (i/o) dbx context info
                 TArc*       pTArc);            // (i/o) item to modify
//
//  TModifyArc - (PCB/SCH) modify the input DBX arc
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTArc         TArc*        DBX item to be modified
//                             Valid fields to modify:
//                                  - width
//                                  - radius
//                                  - centerPt
//                                  - startAng
//                                  - sweepAng
//                                  - layerId
//                                  - isFixed   (PCB only)
//
//  returns       long         DBX completion status
//                             and pTArc updated to reflect changes
//


long 
DLLX TModifyAttribute(DbxContext* pContext,     // (i/o) dbx context info
                      TAttribute* pTAttr);      // (i/o) item to modify
//
//  TModifyAttribute - (PCB/SCH) modify the input DBX design attribute
//                           (Use TModifyCompAttribute for component attributes)
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTAttr        TAttribute*  DBX item to be modified
//                             Valid fields to modify:
//                                  - value
//                                  - refPoint
//                                  - textStyleId
//                                  - justPoint
//                                  - isVisible
//                                  - layerId
//
//  returns       long         DBX completion status
//                             and pAttr updated to reflect changes
//

long 
DLLX TModifyBus      (DbxContext* pContext,     // (i/o) dbx context info
                      TBus*       pTBus);       // (i/o) item to modify
//
//  TModifyBus - (SCH)      modify the input DBX schematic bus  
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTBus         TBus*        DBX item to be modified
//                             Valid fields to modify:
//                                  - startPt
//                                  - endPt
//                                  - busName
//                                  - isVisible
//                                  - isVisible
//
//  returns       long         DBX completion status
//                             and pTBus updated to reflect changes
//


long 
DLLX TModifyClassToClassAttribute  (DbxContext* pContext,       // (i/o)
                                    long        netClassId1,    // (i)
                                    long        netClassId2,    // (i)
                                    TAttribute* TAttribute);    // (i/o)
//
// TModifyClassToClassAttribute - (PCB) Modify an attribute associated to the
// ----------------------------         given class to class.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         net class Id number 1
//  netClassId2         long         net class Id number 2
//  pAttribute          TAttribute*  Attribute to modify
//                                   Valid fields to modify:
//                                      - value
//                                   
//  Returns             long         DBX completion status
//


long 
DLLX TModifyClassToClassLayerRule(DbxContext* pContext,     // (i/o)
                                  long        netclassId1,  // (i)
                                  long        netclassId2,  // (i)
                            const char*       layerName,    // (i)
                                  TAttribute* pAttr);       // (o)
//
// TModifyClassToClassLayerRule - (PCB/Sch) Modify a rule in the class to class 
// ----------------------------             specified by the two net class ids.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId1         long         id #1 of net class containing the rule
//  netClassId2         long         id #2 of net class containing the rule
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TModifyCompAttribute  (DbxContext* pContext,       // (i/o)
                                  char* pCompRefDes,    // (i)
                            TAttribute* TAttribute);    // (i/o)
//
// TModifyCompAttribute - (PCB) Modify a component attribute
// --------------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pCompRefDes         char*        Input string containing the 
//                                   Component RefDes
//  pAttribute          TAttribute*  Attribute to modify
//                             Valid fields to modify:
//                                  - value
//                                  - refPoint
//                                  - textStyleId
//                                  - justPoint
//                                  - isVisible
//                                  - layerId
//
//
//  Returns       long         DBX completion status
//


long 
DLLX TModifyComponent(DbxContext* pContext,     // (i/o) dbx context info
                      TComponent* pTComponent); // (i/o) item to modify
//
//  TModifyComponent - (PCB) modify the input DBX Component
//  ----------------
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTComponent   TComponent*  DBX item to be modified
//                             Valid fields to modify:
//                                  - refDes
//                                  - value
//                                  - refPoint (moves component location)
//                                  - isFixed  (allows the component to move) new for v14.00
//                                  - currentGraphicName
//                                  - isAutoSwapGraphic
//
//  returns       long         DBX completion status
//                             and pTComponent updated to reflect changes


long  
DLLX  TModifyDesignAttribute     (DbxContext* pContext,     // (i) dbx context info
                                  TAttribute* pTAttr);      // (i/o) design attribute
//
// TModifyDesignAttribute - Modify a Design attribute
// ----------------------   
//
//  parameter       Type/Description
//  ---------       ----------------
//
//  pContext        DbxContext*  Input DBX conversation data
//  pTAttr          TAttribute*  Attribute to modify
//                               Valid fields to modify:
//                                  - value 
//
//  Returns         long         DBX completion status
//


long
DLLX TModifyDesignInfo (DbxContext * pContext,      
                        TDesign    * pDesignInfo);  
//
//  TModifyDesignInfo - (PCB/SCH) modify the design info.
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pDesignInfo   TDesign*     DBX Design info to be modified
//                             Valid fields to modify:
//                                  - isModified
//
//  returns       long         DBX completion status
//                             and pDesignInfo updated to reflect changes

long 
DLLX TModifyField (DbxContext* pContext,     // (i/o) dbx context info
                   TField*     pTField);     // (i/o) item to modify
//
//  TModifyField - (SCH) modify the input DBX Field
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTField       TField*      DBX item to be modified
//                             Valid fields to modify:
//                                  - 
//                                  - 
//
//  returns       long         DBX completion status
//                             and pTField updated to reflect changes


long  
DLLX  TModifyLayerAttribute     (DbxContext* pContext,     // (i) dbx context info
                                 long        layerId,      // (i) layer id
                                 TAttribute* pTAttr);      // (o) design attribute
//
// TModifyLayerAttribute - (PCB) Modify an attribute associated to the
// ---------------------         specified layer.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  layerId             long         layer Id number
//  pTAttr              TAttribute*  Attribute to modify
//                                   Valid fields to modify:
//                                      - value
//                                   
//  Returns             long         DBX completion status
//


long 
DLLX TModifyItem (DbxContext* pContext,     // (i/o) dbx context info
                  TItem*      pTItem);      // (i/o) item to modify
//
//  TModifyItem - (PCB/SCH) modify the input DBX Item
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTItem        TItem*       DBX item to be modified
//                             Valid fields to modify:
//                                  - see the individual item description
//
//  returns       long         DBX completion status
//                             and pTItem updated to reflect changes


//
//  Move Functions - (PCB) Move the input dbx item by the specified (x,y)
//
//
//    All functions have the following parameters
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  dx            long         direction in the x direction to move (in db units)
//  dy            long         direction in the y direction to move (in db units)
//  p<item>       <DbxItem>*   DBX item to be moved
//
//
//  returns       long         DBX completion status
//                             and p<item> updated to reflect changes
//
                             

long 
DLLX TModifyLine (DbxContext* pContext,     // (i/o) dbx context info
                  TLine*      pTLine);      // (i/o) item to modify
//
//  TModifyLine - (PCB/SCH) modify the input DBX Line
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTLine        TLine*       DBX item to be modified
//                             Valid fields to modify:
//                                  - width
//                                  - startPt
//                                  - endPt
//                                  - layerId     (PCB only)
//                                  - line style  (SCH only)
//                                  - isFixed     (PCB only)
//
//  returns       long         DBX completion status
//                             and pTLine updated to reflect changes


long 
DLLX TModifyNet  (DbxContext* pContext,     // (i/o) dbx context info
                  TNet*       pTNet);       // (i/o) net to modify
//
//  TModifyNet - (PCB) modify the input DBX Net
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTNet         TNet*       DBX item to be modified
//                             Valid fields to modify:
//                                  - netName
//
//  returns       long         DBX completion status
//                             and pTNet updated to reflect changes


long 
DLLX TModifyNetAttribute  (DbxContext* pContext,       // (i/o)
                           long        netId,          // (i)
                           TAttribute* TAttribute);    // (i/o)
//
// TModifyNetAttribute - (PCB) Modify an attribute associated to the
// -------------------         given net.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         net Id number
//  pAttribute          TAttribute*  Attribute to modify
//                                   Valid fields to modify:
//                                      - value
//                                   
//  Returns             long         DBX completion status
//


long 
DLLX TModifyNetClass  (DbxContext* pContext,     // (i/o) dbx context info
                       TNetClass*  pTNetClass);  // (i/o) net class to modify
//
//  TModifyNetClass - (PCB) modify the input DBX NetClass
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTNetClass    TNetClass*   DBX item to be modified
//                             Valid fields to modify:
//                                  - netClassName
//
//  returns       long         DBX completion status
//                             and pTNetClass updated to reflect changes


long 
DLLX TModifyNetClassAttribute  (DbxContext* pContext,       // (i/o)
                                long        netId,          // (i)
                                TAttribute* TAttribute);    // (i/o)
//
// TModifyNetClassAttribute - (PCB) Modify an attribute associated to the
// ------------------------         given net class.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         net class Id number
//  pAttribute          TAttribute*  Attribute to modify
//                                   Valid fields to modify:
//                                      - value
//                                   
//  Returns             long         DBX completion status
//


long 
DLLX TModifyNetClassLayerRule(DbxContext* pContext,   // (i/o)
                              long        netClassId, // (i)
                        const char*       layerName,  // (i)
                              TAttribute* pAttr);     // (o)
//
// TModifyNetClassLayerRule - (PCB/Sch) Modify a rule in the net class 
// ------------------------             specified by netClassId.
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netClassId          long         id of net class to contain the rule
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//
//  Returns             long         DBX completion status
//


long 
DLLX TModifyNetLayerRule(DbxContext* pContext,   // (i/o)
                         long        netId,      // (i)
                   const char*       layerName,  // (i)
                         TAttribute* pAttr);     // (o)
//
// TModifyNetLayerRule - (PCB/Sch) Modify a rule in the net specified by netId.
// -------------------             
//
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  netId               long         id of net that contains the rule to modify
//  layerName     const char*        name of layer that the rule is on
//  pAttribute          TAttribute*  Output rule
//                      Valid fields to modify:
//                           - value
//                           - formula
//                           - comment
//                           - units
//
//  Returns             long         DBX completion status
//


long 
DLLX TModifyPad  (DbxContext* pContext,     // (i/o) dbx context info
                  TPad*       pTPad);       // (i/o) item to modify
//
//  TModifyPad - (PCB) modify the input DBX Pad
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPad         TPad*        DBX item to be modified
//                             Valid fields to modify:
//                                  - styleId
//                                  - location (valid for free pads only)
//                                  - padNum   (valid for free pads only)
//                                  - defaultPinDes
//                                  - isFixed  (PCB only)
//
//  returns       long         DBX completion status
//                             and pTPad updated to reflect changes


long 
DLLX TModifyPin  (DbxContext* pContext,     // (i/o) dbx context info
                  TPin*       pTPin);       // (i/o) item to modify
//
//  TModifyPin - (SCH) modify the input DBX Pin
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPin         TPin*        DBX item to be modified
//                             Valid fields to modify:
//                                  - Pin type
//                                  - pin designator
//                                  - pin equivalency
//                                  - defaultPinDes
//
//  returns       long         DBX completion status
//                             and pTPin updated to reflect changes


long 
DLLX TModifyPoint(DbxContext* pContext,     // (i/o) dbx context info
                  TPoint*     pTPoint);     // (i/o) item to modify
//
//  TModifyPoint - (PCB) modify the input DBX Point
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPoint       TPoint*      DBX item to be modified
//                             Valid fields to modify:
//                                  - x
//                                  - y
//                                  - placementSide   (PCB TestPoint only)
//                                  - snapToPadCenter (PCB TestPoint only)
//                                  - isFixed         (PCB TestPoint only)
//
//  returns       long         DBX completion status
//                             and pTPoint updated to reflect changes


long 
DLLX TModifyPort (DbxContext* pContext,     // (i/o) dbx context info
                  TPort*      pTPort);      // (i/o) item to modify
//
//  TModifyPort - (SCH) modify the input DBX Port
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPort        TPort*       DBX item to be modified
//                             Valid fields to modify:
//                                  - netname
//                                  - netid
//                                  - port type
//                                  - rotate angle
//                                  - reference point
//
//  returns       long         DBX completion status
//                             and pTPort updated to reflect changes


long
DLLX TModifyPrintJob (DbxContext * pContext,      // (i/o) dbx context info
                      TPrintJob  * pPrintJob);    // (i/o) print job.
//
//  TModifyPrintJob - (PCB/SCH) modify the print job info.
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pPrintJob     TPrintJob*   DBX PrintJob to be modified
//                             Valid fields to modify:
//                                  - isSelected
//                                  - isRotated
//
//  returns       long         DBX completion status
//                             and pPrintJob updated to reflect changes


long  
DLLX  TModifyRoom (DbxContext* pContext,  // (i/o) dbx context info
                   TRoom*      pTRoom);   // (i/o) room to modify
//
//  TModifyRoom - (PCB) modify the input Room
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTRoom        TRoom*       DBX item to be modified
//                             Valid fields to modify:
//                                  - room name
//                                  - fill pattern
//                                  - placement side
//                                  - is fixed
//
//  returns       long         DBX completion status
//                             and pTRoom updated to reflect changes


long  
DLLX  TModifyRoomAttribute  (DbxContext* pContext, // (i) dbx context info
                             long        roomId,   // (i) room id
                             TAttribute* pTAttr);  // (i) room attribute
//
// TModifyRoomAttribute - (PCB) Modify a room attribute
// --------------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  roomId              long         Id of Room containing attribute to modify
//  pAttr               TAttribute*  Attribute to modify
//                             Valid fields to modify:
//                                  - value
//
//  Returns       long         DBX completion status
//


long 
DLLX TModifySymbol(DbxContext* pContext,     // (i/o) dbx context info
                   TSymbol*    pTSymbol);    // (i/o) item to modify
//
//  TModifySymbol - (SCH) modify the input DBX Symbol
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTSymbol      TSymbol*     DBX item to be modified
//                             Valid fields to modify:
//                                  - refDes
//                                  - value
//                                  - refPoint (moves component location)
//
//  returns       long         DBX completion status
//                             and pTSymbol updated to reflect changes


long 
DLLX TModifySymbolAttribute  (DbxContext* pContext,       // (i/o)
                              char* symbRefDes,           // (i)     Symbol Ref. Des.
                              TAttribute* TAttribute);    // (i/o)
//
// TModifySymbolAttribute - (SCH) Modify a symbol attribute
// --------------------   
//
//  parameter           Type/Description
//  ---------           ----------------
//
//  pContext            DbxContext*  Input DBX conversation data
//  pSymName            char*        Input string containing the 
//                                   Symbol RefDes
//  pAttribute          TAttribute*  Attribute to modify
//                             Valid fields to modify:
//                                  - value
//                                  - refPoint
//                                  - textStyleId
//                                  - justPoint
//                                  - isVisible
//
//  Returns       long         DBX completion status
//


long
DLLX TModifyText (DbxContext* pContext,     // (i/o) dbx context info
                  TText*      pTText);      // (i/o) item to modify
//
//  TModifyText - (PCB/SCH) modify the input DBX Text
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTText        TText*       DBX item to be modified
//                             Valid fields to modify:
//                                  - text
//                                  - refPoint
//                                  - textStyleId
//                                  - justPoint
//                                  - isVisible
//                                  - layerId
//
//  returns       long         DBX completion status
//                             and pTText updated to reflect changes

long 
DLLX TModifyVia  (DbxContext* pContext,     // (i/o) dbx context info
                  TVia*       pTVia);       // (i/o) item to modify
//
//  TModifyVia - (PCB) modify the input DBX Via
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTVia         TVia*        DBX item to be modified
//                             Valid fields to modify:
//                                  - styleId
//                                  - location 
//                                  - isFixed
//
//  returns       long         DBX completion status
//                             and pTVia updated to reflect changes

long 
DLLX TModifyWire (DbxContext* pContext,     // (i/o) dbx context info
                  TWire*      pTWire);      // (i/o) item to modify
//
//  TModifyWire - (SCH) modify the input DBX Wire
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTWire        TWire*       DBX item to be modified
//                             Valid fields to modify:
//                                  - startPt
//                                  - endPt
//                                  - isVisible
//
//  returns       long         DBX completion status
//                             and pTWire updated to reflect changes
//

//
//  Move Functions - (PCB/SCH) highlight the input DBX item
//
//
//    All functions have the following parameters
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  dx            long         Delta x to move
//  dy            long         Delta y to move
//  p<item>       <DbxItem>*   DBX item to be moved
//
//  returns       long         DBX completion status
//                             and p<item> updated to reflect highlight status
//
// Note: TMoveComponent only applies for PCB components, and fails for SCH components
//

long 
DLLX TMoveArc      (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TArc*       pTArc);       // (i/o) item to move

long 
DLLX TMoveAttribute(DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TAttribute* pTAttr);      // (i/o) item to move

long 
DLLX TMoveBus      (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TBus*       pTBus);       // (i/o) item to move

long 
DLLX TMoveComponent(DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TComponent* pTComponent); // (i/o) item to move

long
DLLX TMoveDetail   (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TDetail*    pTDetail);    // (i/o) item to move

long
DLLX TMoveDiagram  (DbxContext* pContext,      // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TDiagram*   pTDiagram);   // (i/o) item to move

long 
DLLX TMoveField    (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TField*     pTField);     // (i/o) item to move

long 
DLLX TMoveItem     (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TItem*      pTItem);      // (i/o) item to move
 
long 
DLLX TMoveLine     (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TLine*      pTLine);      // (i/o) item to move

long 
DLLX TMovePad      (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TPad*       pTPad);       // (i/o) item to move

long 
DLLX TMovePin      (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TPin*       pTPin);       // (i/o) item to move

long 
DLLX TMovePoint    (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TPoint*     pTPoint);     // (i/o) item to move

long 
DLLX TMovePort     (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TPort*      pTPort);      // (i/o) item to move

long 
DLLX TMoveSymbol   (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TSymbol*    pTSymbol);      // (i/o) item to move

long
DLLX TMoveTable    (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TTable*     pTTable);     // (i/o) item to move

long 
DLLX TMoveText     (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TText*      pTText);      // (i/o) item to move

long 
DLLX TMoveVia      (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TVia*       pTVia);       // (i/o) item to move

long 
DLLX TMoveWire     (DbxContext* pContext,     // (i/o) dbx context info
                    long        dx,           // (i) delta x to move
                    long        dy,           // (i) delta y to move
                    TWire*      pTWire);      // (i/o) item to move
 
long
DLLX TMoveMetaFile (DbxContext*     pContext,    // (i/o) dbx context info
                    long         dx,          // (i) delta x to move
                    long         dy,          // (i) delta y to move
                    TMetaFile*   pTMetaFile); // (i/o) item to move


long 
DLLX TOpenDesign (long language,
                  long version, 
                  const char* pDesignName, 
                  DbxContext* pContext);
//
// TOpenDesign - (PCB/Sch) Establishes communication channel with 
// -----------             the specified ACCEL EDA application
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  language      long         Calling program language 
//                             (constant DBX_LANGUAGE)
//  version       long         DBX program version
//                             (constant DBX_VERSION)
//  pAppName      char*        Input application name ("pcb" or "sch")
//  pContext      DbxContext*  Output DBX converstation data
//
//
//  returns       long         DBX completion status
//

long 
DLLX TOpenComponent   (DbxContext*   pContext, 
                       const char*   pCompType);


long  
DLLX  TOpenLibrary(long language,            // (i) language used (C or VB)
                   long version,             // (i) dbx user version number
                   const char* pLibraryName, // (i) Library Name
                   DbxContext* pContext);    // (o) dbx context data, including hConv handle


long
DLLX TOutputPrintJobByName (DbxContext * pContext,  // (i/o) dbx context info
                            const char * pJobName); // (i)   print job name.
//
//  TOutputPrintJobByName - (PCB/SCH) Generate output of a print job by the job name.
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pJobName      char*        Name of PCB Print Job or SCH Sheet
//
//  returns       long         DBX completion status
//


long
DLLX TOutputSelectedPrintJobs (DbxContext * pContext);  // (i/o) dbx context info
//
//  TOutputSelectedPrintJobs - (PCB/SCH) Generate all the print jobs selected for output.
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//
//  returns       long         DBX completion status
//


long 
DLLX TPlaceArc (DbxContext* pContext,          // (i/o) dbx context info
                TArc*       pTArc);            // (i/o) item to place
//
//  TPlaceArc - (PCB) Place the input DBX arc
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTArc         TArc*        DBX item to be modified
//                             Valid fields for Place:
//                                  - width
//                                  - radius
//                                  - centerPt
//                                  - startAng
//                                  - sweepAng
//                                  - layerId
//
//  returns       long         DBX completion status
//                             and pTArc updated to reflect changes
//


long 
DLLX TPlaceAttribute(DbxContext* pContext,     // (i/o) dbx context info
                     TAttribute* pTAttr);      // (i/o) item to place
//
//  TPlaceAttribute - (PCB) Place the input DBX design attribute
//                           (Use TAddCompAttribute for component attributes)
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTAttr        TAttribute*  DBX item to be modified
//                             Valid fields for Place:
//                                  - value
//                                  - refPoint
//                                  - textStyleId
//                                  - justPoint
//                                  - isVisible
//                                  - layerId
//
//  returns       long         DBX completion status
//                             and pAttr updated to reflect changes
//

long 
DLLX TPlaceBus      (DbxContext* pContext,     // (i/o) dbx context info
                     TBus*       pTBus);       // (i/o) item to place
//
//  TPlaceAttribute - (SCH) Place the input DBX bus object 
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTBus         TBus*        DBX item to be modified
//                             Valid fields for Place:
//                                  - Starting point
//                                  - ending point
//                                  - bus name
//                                  - layerId
//
//  returns       long         DBX completion status
//                             and pTBus updated to reflect changes
//

long 
DLLX TPlaceComponent(DbxContext* pContext,     // (i/o) dbx context info
                     TComponent* pTComponent); // (i/o) item to place
//
//  TPlaceComponent - (PCB) Place the input DBX Component
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTComponent   TComponent*  DBX item to be modified
//                             Valid fields for Place:
//                                  - compType
//                                  - libraryName (Must be open. If none 
//                                    specified, search the open libraries)
//                                  - refDes
//                                  - value
//                                  - refPoint (component location)
//
//  returns       long         DBX completion status
//                             and pTComponent updated to reflect changes


long 
DLLX TPlaceField    (DbxContext* pContext,     // (i/o) dbx context info
                     TField* pTField);         // (i/o) item to place
//
//  TPlaceField - (SCH) Place the input DBX Field
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTField       TField*      DBX item to be placed
//                             Valid fields for Place:
//                                  - key type 
//                                  - location
//                                  - style
//                                  - justification
//                                  - visibility
//                                  - layerid
//
//  returns       long         DBX completion status
//                             and pTField updated to reflect changes


long 
DLLX TPlaceLine (DbxContext* pContext,     // (i/o) dbx context info
                 TLine*      pTLine);      // (i/o) item to place
//
//  TPlaceLine - (PCB) Place the input DBX Line
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTLine        TLine*       DBX item to be modified
//                             Valid fields for Place:
//                                  - width
//                                  - startPt
//                                  - endPt
//                                  - layerId
//
//  returns       long         DBX completion status
//                             and pTLine updated to reflect changes


long 
DLLX TPlacePad  (DbxContext* pContext,     // (i/o) dbx context info
                 TPad*       pTPad);       // (i/o) item to place
//
//  TPlacePad - (PCB) Place the input DBX Pad
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPad         TPad*        DBX item to be modified
//                             Valid fields for Place:
//                                  - styleId
//                                  - location 
//                                  - padNum   
//
//  returns       long         DBX completion status
//                             and pTPad updated to reflect changes

long 
DLLX TPlacePin  (DbxContext* pContext,     // (i/o) dbx context info
                 TPin*       pTPin);       // (i/o) item to place
//
//  TPlacePin - (SCH) Place the input DBX Pin
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPin         TPin*        DBX item to be modified
//                             Valid fields for Place:
//                                  - location
//                                  - style
//                                  - layer id
//                                  - pin number
//                                  - default pin des
//
//  returns       long         DBX completion status
//                             and pTPin updated to reflect changes



long 
DLLX TPlacePoint(DbxContext* pContext,     // (i/o) dbx context info
                 TPoint*     pTPoint);     // (i/o) item to place
//
//  TPlacePoint - (PCB) Place the input DBX Point
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPoint       TPoint*      DBX item to be modified
//                             Valid fields for Place:
//                                  - x
//                                  - y
//                                  - pointType
//                                  - location
//                                  - infoText (for Info Point)
//
//  returns       long         DBX completion status
//                             and pTPoint updated to reflect changes

long 
DLLX TPlacePort (DbxContext* pContext,     // (i/o) dbx context info
                 TPort*      pTPort);      // (i/o) item to place
//
//  TPlacePort - (SCH) Place the input DBX Port
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTPort        TPort*       DBX item to be modified
//                             Valid fields for Place:
//                                  - net name
//                                  - port type 
//                                  - pin count
//                                  - location
//                                  - pin length
//                                  - rotation
//
//  returns       long         DBX completion status
//                             and pTPort updated to reflect changes

long 
DLLX TPlaceSymbol (DbxContext* pContext,     // (i/o) dbx context info
                   TSymbol*    pTSymbol);    // (i/o) item to place
//
//  TPlaceSymbol - (SCH) Place the input DBX Symbol
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTSymbol      TSymbol*     DBX item to be modified
//                             Valid fields for Place:
//                                  - symbol name
//                                  - refdes
//                                  - number pins
//                                  - part number
//                                  - alternate type
//                                  - ref point 
//                                  - layer id
//                                  - library name
//
//  returns       long         DBX completion status
//                             and pTSymbol updated to reflect changes

long 
DLLX TPlaceText (DbxContext* pContext,     // (i/o) dbx context info
                 TText*      pTText);      // (i/o) item to place
//
//  TPlaceText - (PCB) Place the input DBX Text
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTText        TText*       DBX item to be modified
//                             Valid fields for Place:
//                                  - text
//                                  - refPoint
//                                  - textStyleId
//                                  - justPoint
//                                  - isVisible
//                                  - layerId
//
//  returns       long         DBX completion status
//                             and pTText updated to reflect changes


long 
DLLX TPlaceVia  (DbxContext* pContext,     // (i/o) dbx context info
                 TVia*       pTVia);       // (i/o) item to place
//
//  TPlaceVia - (PCB) Place the input DBX Via
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTVia         TVia*        DBX item to be modified
//                             Valid fields for Place:
//                                  - styleId
//                                  - location 
//
//  returns       long         DBX completion status
//                             and pTVia updated to reflect changes

long 
DLLX TPlaceWire (DbxContext* pContext,     // (i/o) dbx context info
                 TWire*      pTWire);      // (i/o) item to place
//
//  TPlaceVia - (SCH) Place the input DBX Wire
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pTWire        TWire*       DBX item to be modified
//                             Valid fields for Place:
//                                  - styleId
//                                  - starting point
//                                  - ending point
//
//  returns       long         DBX completion status
//                             and pTWire updated to reflect changes

//
//  Rotate Functions - (PCB/SCH) Rotate the input DBX Item
//
//    All functions have the following parameters
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  angle         long         rotation angle, in degrees * 10
//                             -3600 <= angle <= 3600
//  pTCoord       TCoord*      Point about which to rotate the item.
//                             if pTCoord values = (-1,-1) the default
//                             item origin will be used as the rotation point
//  p<item>       <DbxItem>*   DBX item, or TItem to be rotated
//
//
//  returns       long         DBX completion status
//                             and p<item> updated to reflect new orientation
//
// Note: TRotateComponent only applies for PCB components, and fails for SCH components
//
long 
DLLX TRotateArc    (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TArc*       pTArc);      // (i/o) item to flip

long 
DLLX TRotateAttribute(DbxContext* pContext,  // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TAttribute* pTAttr);     // (i/o) item to flip

long 
DLLX TRotateBus    (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TBus*       pTBus);      // (i/o) item to flip

long 
DLLX TRotateComponent(DbxContext* pContext,  // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TComponent* pTComponent);// (i/o) item to flip

long 
DLLX TRotateField  (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TField*     pTField);    // (i/o) item to flip

long 
DLLX TRotateItem   (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TItem*      pTItem);     // (i/o) item to flip
 
long 
DLLX TRotateLine   (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TLine*      pTLine);     // (i/o) item to flip

long 
DLLX TRotatePad    (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TPad*       pTPad);      // (i/o) item to flip

long 
DLLX TRotatePin    (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TPin*       pTPin);      // (i/o) item to flip

long 
DLLX TRotatePort   (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TPort*      pTPort);     // (i/o) item to flip

long 
DLLX TRotateSymbol (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TSymbol*    pTSymbol);   // (i/o) item to flip

long
DLLX TRotateTable  (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TTable*     pTTable);    // (i/o) item to flip

long 
DLLX TRotateText   (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TText*      pTText);     // (i/o) item to flip

long 
DLLX TRotateVia    (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TVia*       pTVia);      // (i/o) item to flip

long 
DLLX TRotateWire   (DbxContext* pContext,    // (i/o) dbx context info
                    long        angle,       // (i) rotation angle
                    TCoord*     pTCoord,     // (i) rotation point
                    TWire*      pTWire);     // (i/o) item to flip


long 
DLLX TSaveComponent   (DbxContext*   pContext);


long
DLLX TSaveDesign (DbxContext * pContext);           // (i/o) dbx context info
//
//  TSaveDesign - (PCB/SCH) Saves the current design to file.
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//
//  returns       long         DBX completion status
//


long
DLLX TSelectAllPrintJobs (DbxContext * pContext);   // (i/o) dbx context info
//
//  TSelectAllPrintJobs - (PCB/SCH) Selects all the print jobs for output.
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//
//  returns       long         DBX completion status
//


long
DLLX TSelectPrintJob (DbxContext * pContext,        // (i/o) dbx context info
                      const char * pJobName);       // (i)   print job name.
//
//  TSelectPrintJob - (PCB/SCH) Select the named print job for output.
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  pJobName      char*        Name of PCB Print Job or SCH Sheet
//
//  returns       long         DBX completion status
//


//
//  TUnFixAll - (PCB) Unfix all fixable objects in the design
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  returns       long         DBX completion status
//
long 
DLLX TUnFixAll(DbxContext* pContext);     // (i/o) dbx context info


//
//  UnHighlight Functions - (PCB/SCH) Unhighlight the input DBX item
//
//
//    All functions have the following parameters
//
//
//  Parameter     Type/Description
//  ---------     ----------------
//
//  pContext      DbxContext*  Input DBX conversation data
//  p<item>       <DbxItem>*   DBX item to be unhighlighted
//
//  returns       long         DBX completion status
//                             and p<item> updated to reflect highlight status
//
// Note: TUnHighlightComponent only applies for PCB components, and fails for SCH components
//
long 
DLLX TUnHighlightAll(DbxContext* pContext);     // (i/o) dbx context info

long 
DLLX TUnHighlightArc (DbxContext* pContext,   // (i/o) dbx context info
                      TArc*       pTArc);     // (i/o) item to unhighlight

long 
DLLX TUnHighlightAttribute (DbxContext* pContext, // (i/o) dbx context info
                            TAttribute* pTAttr);  // (i/o) item to unhighlight

long 
DLLX TUnHighlightBus       (DbxContext* pContext, // (i/o) dbx context info
                            TBus*       pTBus);   // (i/o) item to unhighlight

long 
DLLX TUnHighlightComponent(DbxContext* pContext,        // (i/o) dbx context info
                           TComponent* pTComponent);    // (i/o) item to unhighlight

long 
DLLX TUnHighlightDetail (DbxContext* pContext,      // (i/o) dbx context info
                         TDetail*    pTDetail);     // (i/o) item to unhighlight

long 
DLLX TUnHighlightDiagram (DbxContext* pContext,      // (i/o) dbx context info
                          TDiagram*   pTDiagram);    // (i/o) item to unhighlight

long 
DLLX TUnHighlightField (DbxContext* pContext,   // (i/o) dbx context info
                        TField*     pTField);   // (i/o) item to unhighlight

long 
DLLX TUnHighlightItem(DbxContext* pContext,     // (i/o) dbx context info
                      TItem*      pTItem);      // (i/o) item to unhighlight
 
long 
DLLX TUnHighlightLine(DbxContext* pContext,     // (i/o) dbx context info
                      TLine*      pTLine);      // (i/o) item to unhighlight

long 
DLLX TUnHighlightMetaFile (DbxContext* pContext,      // (i/o) dbx context info
                           TMetaFile*  pTMetaFile);   // (i/o) item to unhighlight

long 
DLLX TUnHighlightNet (DbxContext* pContext,     // (i/o) dbx context info
                      TNet*       pTNet);       // (i/o) net to unhighlight

long 
DLLX TUnHighlightPad (DbxContext* pContext,     // (i/o) dbx context info
                      TPad*       pTPad);       // (i/o) item to unhighlight

long 
DLLX TUnHighlightPin (DbxContext* pContext,     // (i/o) dbx context info
                      TPin*       pTPin);       // (i/o) item to unhighlight

long 
DLLX TUnHighlightPoint(DbxContext* pContext,    // (i/o) dbx context info
                       TPoint*     pTPoint);    // (i/o) item to unhighlight

long 
DLLX TUnHighlightPort (DbxContext* pContext,    // (i/o) dbx context info
                       TPort*      pTPort);     // (i/o) item to unhighlight

long  
DLLX TUnHighlightRoom (DbxContext* pContext,    // (i/o) dbx context info
                       TRoom*      pTRoom);     // (i/o) object to unhighlight

long 
DLLX TUnHighlightSymbol (DbxContext* pContext,  // (i/o) dbx context info
                         TSymbol*    pTSymbol); // (i/o) item to unhighlight

long
DLLX TUnHighlightTable(DbxContext* pContext,    // (i/o) dbx context info
                       TTable*     pTTable);    // (i/o) item to unhighlight

long 
DLLX TUnHighlightText(DbxContext* pContext,     // (i/o) dbx context info
                      TText*      pTText);      // (i/o) item to unhighlight

long 
DLLX TUnHighlightVia (DbxContext* pContext,     // (i/o) dbx context info
                      TVia*       pTVia);       // (i/o) item to unhighlight

long 
DLLX TUnHighlightWire(DbxContext* pContext,     // (i/o) dbx context info
                      TWire*      pTWire);      // (i/o) item to unhighlight


#endif // DBX32_H
