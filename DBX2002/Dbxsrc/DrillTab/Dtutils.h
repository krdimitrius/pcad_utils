// dtutils.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// Drill Table utility function definitions

// Types of units
typedef enum {
    DTAPP_UNITS_IN = 0,
    DTAPP_UNITS_MM
} DRILLTAB_UNITS;


// StringToDbUnits is a poor-man's string to db-unit parser/converter.
// It is NOT sensitive to upper/lower case when interpreting unit suffix.
// If unit suffix is completely omitted, mil units are assumed.
// Examples:
//      6mm*    = 6 mm          = (6 * 10000) db
//      6m*     = 6 mils        = (6 * 2540) db
//      12.5i*  = 12.5 inches   = (12.5 * 2540000) db
//      12.5c*  = 12.5 cm       = (12.5 * 100000) db

BOOL StringToDbUnits(char *pString,
                     long *pScalar);


// DbUnitsToString converts db units to inch (Really, Inch! NOT mils!), or mm.
// It is used for display/verification purposes only.
// Inches are taken out to the fourth decimal place (if significant),
// Millimeters are taken to the first (if significant).

BOOL DbUnitsToString(long dbvalue,
                     DRILLTAB_UNITS units,
                     int padto,
                     char* result,
                     unsigned int bufsize);

