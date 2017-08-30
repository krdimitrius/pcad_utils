//
// rfdeslst.cpp : implementation file
//

#include <assert.h>

#include "stdafx.h"
#include "rfdeslst.h"

/////////////////////////////////////////////////////////////////////////////
// RefDesList implementation file

// constructor
RefDesList::RefDesList(void)
{
    ;
}

// destructor
RefDesList::~RefDesList()
{
    POSITION pos = GetHeadPosition();
    while(pos)
    {
        RefDesItem   *p_item = (RefDesItem *) GetNext( pos );
        if (p_item)
            delete p_item;
    }
}

RefDesItem * RefDesList::GetAtIndex(int index)
{
    POSITION pos;
    if ((pos = FindIndex(index)) != NULL )
    {
        RefDesItem *p_item = (RefDesItem *) GetAt(pos);
        assert(p_item);
        return p_item;
    }
    return NULL;
}

RefDesItem * RefDesList::Find(const char *prefix)
{
    POSITION pos = GetHeadPosition();
    while(pos)
    {
        RefDesItem *p_item = (RefDesItem *) GetNext(pos);
        assert(p_item);
        if (strcmp(p_item->GetRefDesPref(), prefix) == 0)
            return p_item;
    }
    return NULL;
}

void RefDesList::SetStartIndices(int Value)
{
    POSITION pos = GetHeadPosition();
    while(pos)
    {
        RefDesItem *p_item = (RefDesItem *) GetNext(pos);
        assert(p_item);
        p_item->SetStartIndex(Value);
    }
}

void RefDesList::ResetWorkIndices(void)
{
    POSITION pos = GetHeadPosition();
    while(pos)
    {
        RefDesItem *p_item = (RefDesItem *) GetNext(pos);
        assert(p_item);
        p_item->ResetWorkIndex();
    }
}

void RefDesList::UpdateStartIndices(void)
{
    POSITION pos = GetHeadPosition();
    while(pos)
    {
        RefDesItem *p_item = (RefDesItem *) GetNext(pos);
        assert(p_item);
        p_item->SetStartIndex(p_item->GetWorkIndex());
    }
}
