//
// compitem.cpp : implementation file
//

#include <assert.h>
#include <string.h>

#include "stdafx.h"
#include "compitem.h"

/////////////////////////////////////////////////////////////////////////////
// ComponentItem
           
ComponentItem::ComponentItem(TComponent *pComp)
{
    pComponent = new TComponent;
    assert(pComponent);
    memcpy(pComponent, pComp, sizeof(TComponent));
    
    char *ptr;
    short len;
    ptr = strpbrk(pComp->refDes, "0123456789");
    len = ptr - pComp->refDes;
    strncpy(refDesPref, pComp->refDes, len);
    refDesPref[len] = '\0';
    strcpy(refDesSuff, ptr);
    reNumbered = FALSE;
}

ComponentItem::~ComponentItem()
{
    if (pComponent)
    {
        delete pComponent; 
        pComponent = 0;
    }
}

long ComponentItem::GetRefPointValue(CoordName nName)
{
    if (nName == COORD_X_VALUE)
        return pComponent->refPoint.x;
    else
        return pComponent->refPoint.y;
}

void ComponentItem::SetRefDes(char *pRefDes)
{
    assert(pRefDes);
    assert(strlen(pRefDes) > 0  &&  strlen(pRefDes) < DBX_MAX_NAME_LEN);
    strcpy(pComponent->refDes, pRefDes); 
}
