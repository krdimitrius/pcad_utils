//
// rfdeslst.h : header file
//

#ifndef REFDESLIST_H
#define REFDESLIST_H

#include "Dbx32.h"
#include "rfdesitm.h"

/////////////////////////////////////////////////////////////////////////////
// RefDesItem entries for RefDesList linked list.
class RefDesList : public CObList
{
public:
    // Construction/destruction
    RefDesList(void);
    ~RefDesList();

    // return a pointer to the RefDesItem specified by index
    RefDesItem * GetAtIndex(int index);

    RefDesItem * Find(const char *prefix);

    void        SetStartIndices(int Value);

    void        ResetWorkIndices(void);
    
    void        UpdateStartIndices(void);

};

#endif // REFDESLIST_H
