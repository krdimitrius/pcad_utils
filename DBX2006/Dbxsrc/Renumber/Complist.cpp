// compitem.cpp : implementation file
//

#include <assert.h>
#include <memory.h>

#include "stdafx.h"
#include "compitem.h"
#include "complist.h"

/////////////////////////////////////////////////////////////////////////////
// ComponentList implementation file
           
ComponentList::~ComponentList()
{
    ComponentItem   *p_item;
    for(int indx = 0;  indx < GetSize();  indx++)
    {
        p_item = (ComponentItem *)GetAt(indx);
        if (p_item)
        {
            delete p_item;
            p_item = 0;
        }
    }
    CObArray::RemoveAll();
}

void ComponentList::RemoveAll(void)
{
    ComponentItem   *p_item;
    for(int indx = 0;  indx < GetSize();  indx++)
    {
        p_item = (ComponentItem *)GetAt(indx);
        if (p_item)
            delete p_item;
    }
    CObArray::RemoveAll();
}

void ComponentList::ResetFlags(FlippedOption whichComps)
{
    for(int indx = 0;  indx < GetSize();  indx++)
    {
        switch(whichComps)
        {
            case ALL_COMPS:
            case TOP_BOTTOM:
            {
                ComponentItem   *p_item = (ComponentItem *) GetAt(indx);
                p_item->SetRenumberFlag(FALSE);
                break;
            }
            case TOP_ONLY:
            {
                ComponentItem   *p_item = (ComponentItem *) GetAt(indx);
                if (!p_item->IsFlipped())
                    p_item->SetRenumberFlag(FALSE);
                break;
            }
            case BOTTOM_ONLY:
            {
                ComponentItem   *p_item = (ComponentItem *) GetAt(indx);
                if (p_item->IsFlipped())
                    p_item->SetRenumberFlag(FALSE);
                break;
            }
        }
    }
}

ComponentItem * ComponentList::FindItemById(long compId)
{
    for(int indx = 0;  indx < GetSize();  indx++)
    {
        ComponentItem   *p_item = (ComponentItem *) GetAt(indx);
        assert(p_item);
        if (p_item->GetCompId() == compId)
            return p_item;
    }
    return NULL;
}

BOOL ComponentList::FindItemPntr(ComponentItem *pCompItem)
{
    for(int indx = 0;  indx < GetSize();  indx++)
    {
        ComponentItem   *p_item = (ComponentItem *) GetAt(indx);
        assert(p_item);
        if (p_item == pCompItem)
            return TRUE;
    }
    return FALSE;
}

