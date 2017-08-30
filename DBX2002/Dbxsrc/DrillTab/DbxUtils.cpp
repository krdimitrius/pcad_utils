//////////////////////////////////////////////////////////////////////////////
//                                                                          
//    name:     DBXUTILS.C
//
//    abstract: These are the data structures and API used for dbx communication
//              between user C/VB programs and PCB.  This file was created by
//              moving the actual functions from file DBXUTILS.H.
//
//    author:   Phil Mayou
//              Ported from 12.1 to Win32 by Nick Choate
//              
//
//    $Header: /P-CAD 2002/AccelEDA/cmn/DbxUtils.cpp 1     3/07/02 3:30p M_lin $
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
//                          Copyright (c) 1991-1996
//                          ACCEL Technologies, Inc.                        
//                            6825 Flanders Drive                           
//                            San Diego, CA 92121                           
//                               (619) 554-1000                             
//                                                                          
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dbxutils.h"
#include "Dbx32.h"


long DBX_Units = DBX_UNIT_MIL;


double Nearest(double d)
{
    double int_part;

    if   (d >= 0) d += 0.5;
    else          d -= 0.5;

    modf (d, &int_part);
    return int_part;
}

double FixPrecision(double & val, int precis)
{
    val = val          * (double)precis;
    val = Nearest(val) / (double)precis;
    return val;
}

void Long_To_String (long n, char* pOutStr, long outStrLen)
{
    if (pOutStr && outStrLen > 0)
    {
        char buf [50];
        
        sprintf(buf, "%ld", n);
        
        strncpy (pOutStr, buf, (size_t)outStrLen);
        pOutStr[outStrLen-1] = 0;
    }
}

void Double_To_String (double n, char* pOutStr, long outStrLen)
{
    if (pOutStr && outStrLen > 0)
    {
        char buf [50];

        sprintf(buf, "%lf", n);

        strncpy (pOutStr, buf, (size_t)outStrLen);
        pOutStr[outStrLen-1] = 0;
    }
}

long String_To_Long (char* pInStr)
{
    long val = 0;

    if (pInStr)
    {
        sscanf (pInStr, "%ld", &val);
    }

    return val;
}

double String_To_Double (char* pInStr)
{
    double val = 0;

    if (pInStr)
    {
        sscanf (pInStr, "%lf", &val);
    }

    return val;
}

double DB_To_mil (long dbUnit)
{
    return (double)dbUnit / DB_TO_MIL;
}

void DB_To_mil_Str (long dbUnit, char* pOutStr, long outStrLen)
{
    double mil;
    mil = DB_To_mil(dbUnit);
    Double_To_String(mil, pOutStr, outStrLen);
} 
    
double DB_To_mm (long dbUnit)
{
    return (double)dbUnit / DB_TO_MM;
}

void DB_To_mm_Str (long dbUnit, char* pOutStr, long outStrLen)
{
    double mm;
    mm = DB_To_mm(dbUnit);
    Double_To_String(mm, pOutStr, outStrLen);
}

long mil_Str_To_DB (char* pMilStr)
{
    double mil;
    
    mil = String_To_Double (pMilStr);

    return mil_To_DB(mil);
}

long mil_To_DB (double mil)
{
    return (long)( Nearest(mil * DB_TO_MIL) );
}

long mm_Str_To_DB (char* pMmStr)
{
    double mm;
    
    mm = String_To_Double (pMmStr);

    return mm_To_DB(mm);
}

long mm_To_DB (double mm)
{
    return (long)( Nearest(mm * DB_TO_MM) );
}


void Error_Message_Return (long error, char* pOutStr, long outStrLen)
{
    char buf[50];

    *buf = 0;

    if (pOutStr && outStrLen > 0)
    {
        switch (error)
        {
            case DBX_CONNECTION_ERROR:         strcpy (buf, "Connection Error");         break;
            case DBX_DISCONNECT_ERROR:         strcpy (buf, "Disconnect Error");         break;
            case DBX_BAD_SERVER_DATA:          strcpy (buf, "Bad Server Data");          break;
            case DBX_SERVER_ERROR:             strcpy (buf, "Server Error");             break;
            case DBX_FATAL_ERROR:              strcpy (buf, "Fatal DBX Error");          break;
            case DBX_VERSION_INCOMPATIBLE:     strcpy (buf, "Version Incompatible");     break;
            case DBX_CLIENT_ERROR:             strcpy (buf, "Client Error");             break;
            case DBX_SECURITY_ERROR:           strcpy (buf, "Security Error");           break;
            case DBX_FLIP_ERROR:               strcpy (buf, "Flip Error");               break;
            case DBX_ROTATE_ERROR:             strcpy (buf, "Rotate Error");             break;
            case DBX_MOVE_ERROR:               strcpy (buf, "Move Error");               break;
            case DBX_HIGHLIGHT_ERROR:          strcpy (buf, "Highlight Error");          break;
            case DBX_DELETE_ERROR:             strcpy (buf, "Delete Error");             break;
            case DBX_MODIFY_ERROR:             strcpy (buf, "Modify Error");             break;
            case DBX_CREATE_ERROR:             strcpy (buf, "Create Error");             break;
            case DBX_DATABASE_ERROR:           strcpy (buf, "Database Error");           break;
            case DBX_OK:                       strcpy (buf, "Status: OK");               break;
            case DBX_INVALID_CONV_HANDLE:      strcpy (buf, "Invalid Conv Handle");      break;
            case DBX_SERVER_TERMINATED:        strcpy (buf, "Server Terminated");        break;
            case DBX_LOW_MEMORY:               strcpy (buf, "Low Memory");               break;
            case DBX_ALREADY_CONNECTED:        strcpy (buf, "Already Connected");        break;
            case DBX_NO_CONNECTION:            strcpy (buf, "No Connection");            break;
            case DBX_SERVER_BUSY:              strcpy (buf, "Server Busy");              break;
            case DBX_ILLEGAL_OP:               strcpy (buf, "Illegal Operation");        break;
            case DBX_BAD_INPUT:                strcpy (buf, "Bad Input");                break;
            case DBX_ARRAY_TOO_SMALL:          strcpy (buf, "Array Too Small");          break;
            case DBX_INVALID_ITEM_ID:          strcpy (buf, "Invalid Item ID");          break;
            case DBX_ITEM_NOT_FOUND:           strcpy (buf, "Item Not Found");           break;
            case DBX_ITEM_NOT_SUPPORTED:       strcpy (buf, "Item Not Supported");       break;
            case DBX_ILLEGAL_ITEM:             strcpy (buf, "Illegal Item");             break;
            case DBX_SHAPE_NOT_DEFINED:        strcpy (buf, "Shape Not Defined");        break;
            case DBX_GETFIRST_NOT_CALLED:      strcpy (buf, "GetFirst Not Called");      break;
            case DBX_GETCOMP_NOT_CALLED:       strcpy (buf, "GetComp Not Called");       break; 
            case DBX_GETNET_NOT_CALLED:        strcpy (buf, "GetNet Not Called");        break; 
            case DBX_NO_MORE_LAYERS:           strcpy (buf, "No More Layers");           break;
            case DBX_NO_MORE_NETS:             strcpy (buf, "No More Nets");             break;
            case DBX_NO_MORE_ITEMS:            strcpy (buf, "No More Items");            break;
            case DBX_NO_MORE_NETCLASSES:       strcpy (buf, "No More Net Classes");      break;
            case DBX_NO_MORE_CLASSTOCLASSES:   strcpy (buf, "No More Class To Class Rules"); break;
            case DBX_NO_MORE_ROOMS:            strcpy (buf, "No More Rooms");            break;
            case DBX_NO_MORE_ROOMPOINTS:       strcpy (buf, "No More Room Points");      break;
            case DBX_NO_MORE_COMPONENTS:       strcpy (buf, "No More Components");       break;
            case DBX_INVALID_ANGLE:            strcpy (buf, "Invalid Angle");            break;
            case DBX_INVALID_HIGHLIGHT_COLOR:  strcpy (buf, "Invalid Highlight Color");  break;
            case DBX_INVALID_ITEM_TYPE:        strcpy (buf, "Invalid Item Type");        break;
            case DBX_INVALID_JUSTIFICATION:    strcpy (buf, "Invalid Justification");    break;
            case DBX_INVALID_LAYER:            strcpy (buf, "Invalid Layer");            break;
            case DBX_INVALID_LOCATION:         strcpy (buf, "Invalid Location");         break;
            case DBX_INVALID_NET_ID:           strcpy (buf, "Invalid Net Id");           break;
            case DBX_INVALID_NETNAME:          strcpy (buf, "Invalid Net Name");         break;
            case DBX_INVALID_PADSTYLE:         strcpy (buf, "Invalid Padstyle");         break;
            case DBX_INVALID_PIN_NUMBER:       strcpy (buf, "Invalid Pin Number");       break;
            case DBX_INVALID_RADIUS:           strcpy (buf, "Invalid Radius");           break;
            case DBX_INVALID_REFDES:           strcpy (buf, "Invalid Refdes");           break;
            case DBX_INVALID_ROTATION_ANGLE:   strcpy (buf, "Invalid Rotation Angle");   break;
            case DBX_INVALID_TEXTSTYLE:        strcpy (buf, "Invalid TextStyle");        break;
            case DBX_INVALID_WIDTH:            strcpy (buf, "Invalid Width");            break;
            case DBX_INVALID_LAYERNAME:        strcpy (buf, "Invalid Layer Name");       break;
            case DBX_INVALID_COMPNAME:         strcpy (buf, "Invalid Component Name");   break;
            case DBX_NOT_SAME_NUM_PARTS:       strcpy (buf, "Mismatched Part Numbers");  break;
            case DBX_NOT_SAME_NUM_PINS:        strcpy (buf, "Mismatched Pin Numbers");   break;
            case DBX_NOT_SAME_COMP_TYPE:       strcpy (buf, "Mismatched Component Type"); break;
            case DBX_NOT_SAME_HETERO:          strcpy (buf, "Mismatched Hetero");        break;
            case DBX_INVALID_LINESTYLE:        strcpy (buf, "Invalid Line Style");       break;
            case DBX_INVALID_PINLENGTH:        strcpy (buf, "Invalid Pin Length");       break;
            case DBX_INVALID_PINSTYLE:         strcpy (buf, "Invalid Pin Style");        break;
            case DBX_INVALID_ALTTYPE:          strcpy (buf, "Invalid Alt Type");         break;
            case DBX_INVALID_NETCLASSNAME:     strcpy (buf, "Invalid Net Class Name");   break;
            case DBX_INVALID_CLASSTOCLASSID:   strcpy (buf, "Invalid Class To Class Id"); break;
            case DBX_INVALID_NETCLASS_ID:      strcpy (buf, "Invalid Net Class Id");     break;
            case DBX_INVALID_LAYER_ID:         strcpy (buf, "Invalid Layer Id");         break;
            case DBX_INVALID_ROOMNAME:         strcpy (buf, "Invalid Room Name");        break;
            case DBX_INVALID_ATTRIBUTE_VALUE:  strcpy (buf, "Invalid Attribute Value");  break;
            case DBX_INVALID_ATTRIBUTE_NAME:   strcpy (buf, "Invalid Attribute Name");   break;
            case DBX_DUPLICATE_ATTRIBUTE:      strcpy (buf, "Duplicate Attribute");      break;
            case DBX_DUPLICATE_NETNAME:        strcpy (buf, "Duplicate Net Name");       break;
            case DBX_DUPLICATE_NETCLASSNAME:   strcpy (buf, "Duplicate Net Class Name"); break;
            case DBX_DUPLICATE_CLASSTOCLASSNAME:   strcpy (buf, "Duplicate Class To Class Name");  break;
            case DBX_DUPLICATE_REFDES:         strcpy (buf, "Duplicate Refdes");         break;
            case DBX_COMPONENT_NOT_FOUND:      strcpy (buf, "Component Not Found");      break;
            case DBX_LAYER_NOT_FOUND:          strcpy (buf, "Layer Not Found");          break;
            case DBX_NET_NOT_FOUND:            strcpy (buf, "Net Not Found");            break;
            case DBX_NET_NOT_EMPTY:            strcpy (buf, "Net Not Empty");            break;
            case DBX_NET_EXISTS:               strcpy (buf, "Net Exists");               break;
            case DBX_NET_CONFLICT:             strcpy (buf, "Net Conflict");             break;
            case DBX_NETCLASS_NOT_FOUND:       strcpy (buf, "Net Class Not Found");      break;
            case DBX_NETCLASS_NOT_EMPTY:       strcpy (buf, "Net Class Not Empty");      break;     
            case DBX_NETCLASS_EXISTS:          strcpy (buf, "Net Class Exists");         break;
            case DBX_CLASSTOCLASS_NOT_FOUND:   strcpy (buf, "Class To Class Not Found"); break;
            case DBX_ROOM_NOT_FOUND:           strcpy (buf, "Room Not Found");           break;
            case DBX_POINT_NOT_FOUND:          strcpy (buf, "Point Not Found");          break; 
            case DBX_COMP_CACHE_CONFLICT:      strcpy (buf, "Component Cache Conflict"); break;
            case DBX_LIBRARY_NOT_OPEN:         strcpy (buf, "Library Not Open");         break;
            case DBX_ITEM_OUTSIDE_WORKSPACE:   strcpy (buf, "Item Outside Workspace");   break;
            case DBX_NO_ATTACHED_PATTERN:      strcpy (buf, "No Attached Pattern");      break;
            case DBX_TOO_FEW_PINS:             strcpy (buf, "Too Few Pins");             break;
            case DBX_PINDES_NOT_FOUND:         strcpy (buf, "Pindes Not Found");         break;
            case DBX_NAME_TOO_LONG:            strcpy (buf, "Name Too Long");            break;
            case DBX_PRINT_JOB_NOT_FOUND:      strcpy (buf, "Print Job Not Found");      break;
            case DBX_NO_PRINT_JOBS_SELECTED:   strcpy (buf, "No Print Jobs Selected");   break;
            case DBX_FILE_OPEN_FAILURE:        strcpy (buf, "Unable to open file");      break;
            case DBX_INVALID_LIBRARY_NAME:     strcpy (buf, "Invalid Library Name");     break;
            case DBX_LIBRARY_CANT_OPEN:        strcpy (buf, "Unable to open Library");   break;
            case DBX_COMP_ALREADY_OPEN:        strcpy (buf, "Component Already Open");   break;
            case DBX_OPENCOMP_NOT_CALLED:      strcpy (buf, "OpenComponent Not Called"); break;
            case DBX_SAVECOMP_FAILED:          strcpy (buf, "SaveComponent Failed");     break;
            case DBX_LIBRARY_READ_ONLY:        strcpy (buf, "Library is READ only");     break;
            case DBX_SAVESYMBOL_FAILED:        strcpy (buf, "Save Symbol Failed");       break;
            case DBX_SAVEPATTERN_FAILED:       strcpy (buf, "Save Pattern Failed");      break;
            case DBX_INTERNAL_PARAMETER_ERROR: strcpy (buf, "Internal Parameter Error"); break;
            default: 
            {
                strcpy(buf, "Status: ");
                sprintf(buf + strlen ("Status: "), "%ld", error);
            }
        }

        strncpy (pOutStr, buf, (size_t)outStrLen);
        pOutStr[outStrLen-1] = 0;
    }
}


void Unit_Convert (long dbUnit, char* pOutStr, long outStrLen)
{
    if (DBX_Units == DBX_UNIT_DB)
    {
        Long_To_String (dbUnit, pOutStr, outStrLen);
    }
    else if (DBX_Units == DBX_UNIT_MIL)
    {
        DB_To_mil_Str (dbUnit, pOutStr, outStrLen);
    }
    else if (DBX_Units == DBX_UNIT_MM)
    {
        DB_To_mm_Str (dbUnit, pOutStr, outStrLen);
    }
}
