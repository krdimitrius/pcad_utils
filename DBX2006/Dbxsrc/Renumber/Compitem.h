//
// compitem.h : header file                                                                                          7
//
#ifndef COMPITEM_H
#define COMPITEM_H

#include "Dbx32.h"

#define MAX_REFDES_PREFIX_LEN   10
#define MAX_REFDES_SUFFIX_LEN   10

enum CoordName { COORD_X_VALUE, COORD_Y_VALUE };

/////////////////////////////////////////////////////////////////////////////
// ComponentItem entries for selected components linked list.
class ComponentItem : public CObject
{
// Construction
private:
    TComponent      *pComponent;
    
    char    refDesPref[MAX_REFDES_PREFIX_LEN];
    char    refDesSuff[MAX_REFDES_SUFFIX_LEN];
    BOOL    reNumbered;
    
public:
    ComponentItem( TComponent *pComp );
    ~ComponentItem();

    TComponent  *GetComponent(void) { return pComponent; }

    char        *GetRefDes(void) { return pComponent->refDes; }

    char        *GetCompType(void) { return pComponent->compType; }
    
    void        SetRefDes(char *pRefDes);

    char        *GetRefDesPref(void) { return refDesPref; }

    void        SetRenumberFlag(BOOL bValue) { reNumbered = bValue; }

    BOOL        GetRenumberFlag(void) { return reNumbered; }

    long        GetRefPointValue(CoordName nName);

    TCoord      *GetRefPoint(void) { return &pComponent->refPoint; }

    void        SetCompId(long lCompId) { pComponent->compId = lCompId; }

    long        GetCompId(void) { return pComponent->compId; }

    BOOL        IsFlipped(void) { return (pComponent->isFlipped == 0) ? FALSE : TRUE; }
};

#endif // COMPITEM_H
