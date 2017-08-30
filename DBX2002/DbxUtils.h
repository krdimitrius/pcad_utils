//////////////////////////////////////////////////////////////////////////////
//                                                                          
//    name:     DBXUTILS.H
//
//    abstract: These are the data structures and API used for dbx communication
//              between user C/VB programs and PCB.
//
//    author:   Steve Smith
//
//    $Header: /P-CAD 2002/AccelEDA/cmn/DbxUtils.h 1     3/07/02 3:30p M_lin $
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
//                         Copyright (c) 1993 - 1996
//                          ACCEL Technologies, Inc.                        
//                            6825 Flanders Drive                           
//                            San Diego, CA 92121                           
//                               (619) 554-1000                             
//                                                                          
////////////////////////////////////////////////////////////////////////////////

#ifndef DBXUTILS_H
#define DBXUTILS_H

#define DB_TO_MM   100000.0    // number of database units per mm       
#define DB_TO_MIL  2540.0      // number of database units per mil

extern  long DBX_Units;

double  Nearest      (double d);
double  FixPrecision (double & val, int precis = 1);

void   Long_To_String   (long   n, char * pOutStr, long outStrLen);
void   Double_To_String (double n, char * pOutStr, long outStrLen);
long   String_To_Long   (char * pInStr);
double String_To_Double (char * pInStr);

double DB_To_mil     (long   dbUnit);
void   DB_To_mil_Str (long   dbUnit, char* pOutStr, long outStrLen);

double DB_To_mm      (long   dbUnit);
void   DB_To_mm_Str  (long   dbUnit, char* pOutStr, long outStrLen);

long   mil_Str_To_DB (char * pMilStr);
long   mil_To_DB     (double mm);

long   mm_Str_To_DB  (char * pMmStr);
long   mm_To_DB      (double mm);

void Error_Message_Return (long error, char* pOutStr, long outStrLen);
void Unit_Convert (long dbUnit, char* pOutStr, long outStrLen);


#endif // DBXUTILS_H

