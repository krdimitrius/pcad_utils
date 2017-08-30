//
// rfdesitm.cpp : implementation file
//

#include <assert.h>

#include "stdafx.h"
#include "rfdesitm.h"

/////////////////////////////////////////////////////////////////////////////
// RefDesItem implementation file
           
RefDesItem::RefDesItem(const char *RefDesPref, int index)
{
    assert(RefDesPref);
    m_RefDesPref = new char [RENUM_MAX_REFDES_PREF_LEN];
    strcpy(m_RefDesPref, RefDesPref);
    nStartIndex = index;
    nWorkIndex = index;
}

RefDesItem::~RefDesItem(void)
{
    delete m_RefDesPref;
}

/*
RefDesItem * RefDesItem::GetAtIndex(int index)
{
    POSITION pos;
    if ((pos = FindIndex(index)) != NULL )
    {
        ComponentItem *p_item = (ComponentItem *) GetAt(pos);
        assert(p_item);
        return p_item;
    }
    return NULL;
}
*/
