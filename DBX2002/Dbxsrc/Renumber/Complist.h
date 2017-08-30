//
// complist.h : header file
//

#ifndef COMPLIST_H
#define COMPLIST_H

#include "Dbx32.h"
#include "compitem.h"

enum FlippedOption { ALL_COMPS, TOP_BOTTOM, TOP_ONLY, BOTTOM_ONLY };

/////////////////////////////////////////////////////////////////////////////
// List of ComponentItems.
class ComponentList : public CObArray
{
// Construction
public:
    ComponentList(void){ ; }
    ~ComponentList();

    void    RemoveAll(void);

    void    DeleteNonDuplicates(ComponentList *pList);

    // reset the reNumbered flag for each item in the list
    void    ResetFlags(FlippedOption whichComps);

    // return the ComponentItem with the specified compId
    ComponentItem * FindItemById(long compId);
    
    BOOL FindItemPntr(ComponentItem *pCompItem);
    
};

#endif // COMPLIST_H
