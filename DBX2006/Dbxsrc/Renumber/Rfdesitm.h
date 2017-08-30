//
// rfdesitm.h : header file                                                                                          7
//

#ifndef REFDESITEM_H
#define REFDESITEM_H

#include "Dbx32.h"

#define RENUM_MAX_REFDES_PREF_LEN    10

/////////////////////////////////////////////////////////////////////////////
// RefDesItem entries for RefDes linked list.
class RefDesItem : public CObject
{
// Construction
private:
    char    *m_RefDesPref;
    int     nStartIndex;
    int     nWorkIndex;
    
public:
    RefDesItem(const char *RefDesPref, int index = 1);
    ~RefDesItem(void);

    char *      GetRefDesPref(void) { return m_RefDesPref; }

    int         GetStartIndex(void) { return nStartIndex; }

    int         GetWorkIndex(void) { return nWorkIndex; }

    void        SetRefDesPref(char *pRefDesPref) { m_RefDesPref = pRefDesPref; }

    void        SetStartIndex(int index) { nStartIndex = index; }

    void        IncrementWorkIndex(void) { nWorkIndex++; }
    
    void        ResetWorkIndex(void) { nWorkIndex = nStartIndex; }
};

#endif // REFDESITEM_H
