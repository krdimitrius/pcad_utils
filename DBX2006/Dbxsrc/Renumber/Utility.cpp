// utility.cpp : implementation file
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stdafx.h"
#include "utility.h"

void FormatLBStr(CString& PrefStr, const CString& StartIndex)
{
    int ndx = PrefStr.ReverseFind('\t') + 1;
    if (ndx == 0)
    {
        PrefStr += "\t";
    }
    else
    {
        PrefStr.GetBufferSetLength(ndx);
    }
        
    int ilen = StartIndex.GetLength();
    CString spaces = "               ";
    PrefStr += spaces.GetBufferSetLength(10 - ilen) + StartIndex;        
}

