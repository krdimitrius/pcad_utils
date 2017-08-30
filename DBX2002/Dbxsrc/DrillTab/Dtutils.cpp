// drilldlg.cpp : implementation file
//

#include "dbxutils.h"
#include "dtutils.h"
//#include "math.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// String to db-unit parser/converter.
// Described in dtutils.h.
//
BOOL StringToDbUnits(char *pString, long *pScalar)
{
    int     i;
    int     ch[6] = {'m', 'M', 'i', 'I', 'c', 'C'};

    // Ensure some string has been sent
    if (!pString)
    {
        return FALSE;
    }
    if (!strlen(pString))
    {
        return FALSE;
    }
    if (!pScalar)
    {
        return FALSE;
    }

    // Convert string based on unit suffix
    *pScalar = 0L;
    for (i = 0; i < 6; i++)
    {
        char    *idx;
        if ((idx = strchr(pString, ch[i])))
        {
            *idx = '\0';
            double  dwidth;
            switch (i)
            {
                // String indicates mm or mil suffix
                case 0:
                case 1:
                    *pScalar = atol(pString);
                    if (idx[1] == 'm' || idx[1] == 'M')
                    {
                        *pScalar = mm_To_DB(*pScalar);
                    }
                    else
                    {
                        *pScalar = mil_To_DB(*pScalar);
                    }
                    break;
                // String indicates inch suffix
                case 2:
                case 3:
                    dwidth = atof(pString);
                    *pScalar = (long) (dwidth * 1.0e3);
                    *pScalar = mil_To_DB(*pScalar);
                    break;
                // String indicates cm suffix
                case 4:
                case 5:
                    dwidth = atof(pString);
                    *pScalar = (long) (dwidth * 1.0e1);
                    *pScalar = mm_To_DB(*pScalar);
                    break;
            }

            if (!*pScalar)
            {
                return FALSE;
            }
            break;
        }
    }

    //When no unit suffix specified, assume mils
    if (!*pScalar)
    {
        *pScalar = atol(pString);
        if (!*pScalar)
        {
            return FALSE;
        }
        *pScalar = mil_To_DB(*pScalar);
    }

    if (!*pScalar)
    {
        return FALSE;
    }

    return TRUE;
}

//
// String to db-unit to inch/mil converter.
// Described in dtutils.h.
//
BOOL DbUnitsToString(long dbvalue,
                     DRILLTAB_UNITS units,
                     int padto,
                     char* result,
                     unsigned int bufsize)
{
    char    buf[10];
    long    divisor = units == DTAPP_UNITS_IN ? 2540000L : 100000L;
    long    wholes = dbvalue / divisor;
    long    tenths = (dbvalue % divisor) / (divisor / 10L);
    long    hundrs = (dbvalue % (divisor / 10L)) / (divisor / 100L);
    long    mils   = units == DTAPP_UNITS_MM ? 0L :
                              (dbvalue % (divisor / 100L)) / (divisor / 1000L);
    long    tmils  = units == DTAPP_UNITS_MM ? 0L :
                              (dbvalue % (divisor / 1000L)) / (divisor / 10000L);

    if (!result || bufsize <= 0)
    {
        return FALSE;
    }

    *result = *buf = 0;

    // Always write whole units (even if zero)
    (void) ltoa(wholes, buf, 10);
    if (strlen(buf) >= bufsize)
    {
        return FALSE;
    }
    strcpy(result, buf);

    // Write decimal point and tenths
    if (padto >= 1 || tenths || hundrs || mils || tmils)
    {
        if (strlen(result) + 1 >= bufsize)
        {
            return FALSE;
        }
        (void) strcat(result, ".");
        ltoa(tenths, buf, 10);
        if (strlen(result) + strlen(buf) >= bufsize)
        {
            return FALSE;
        }
        (void) strcat(result, buf);
    }

    // Write hundredths
    if (padto >= 2 || hundrs || mils || tmils)
    {
        ltoa(hundrs, buf, 10);
        if (strlen(result) + strlen(buf) >= bufsize)
        {
            return FALSE;
        }
        (void) strcat(result, buf);
    }

    // Write thousandths (inch only)
    if (padto >= 3 || mils || tmils)
    {
        ltoa(mils, buf, 10);
        if (strlen(result) + strlen(buf) >= bufsize)
        {
            return FALSE;
        }
        (void) strcat(result, buf);
    }

    // Write tenthousandths (inch only)
    if (padto >= 4 || tmils)
    {
        ltoa(tmils, buf, 10);
        if (strlen(result) + strlen(buf) >= bufsize)
        {
            return FALSE;
        }
        (void) strcat(result, buf);
    }

    return TRUE;
}
