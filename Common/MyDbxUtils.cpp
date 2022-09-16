//////////////////////////////////////////////////////////////////////////////
//                                                                          
//    name:     MyDbxUtils.c
//
//    $Header: MyDbxUtils.c, 1, 09/01/14 2:09:03 AM, Dmitry Krysin$
//                                                                          
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbx32.h"

// ����������
DbxContext tContext; //  Global DBX Conversation Data
long tStatus;        //  Global Return status variable


// �������� ����
bool openDesignPcb(void)
{
	if(TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "pcb",&tContext) == DBX_OK)
		return true;
	return false;
}

// �������� ����
bool closeDesignPcb(void)
{
	TCloseDesign(&tContext,"");
	return true;
}

// �������� ����
bool openDesignSch(void)
{
	if(TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "sch",&tContext) == DBX_OK)
		return true;
	return false;
}

// �������� ����
bool closeDesignSch(void)
{
	TCloseDesign(&tContext,"");
	return true;
}

// ���� ��������� � ������ ����� ��������� ����
char * myStrpbrkLatin(char * pstr)
{
	if(pstr == NULL)
		return NULL;
	return strpbrk(pstr,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
}

// ���� ��������� � ������ ����� ����
char * myStrpbrkDigit(char * pstr)
{
	if(pstr == NULL)
		return NULL;
	return strpbrk(pstr,"0123456789");
}

// ����������� �������� curAttr �� ������� refAttr � ���������� curRefDes �� ��������� [offsetX,offsetY]
long modifyCompAttrByRefAttr(TAttribute *refAttr,TAttribute *curAttr, char * curRefDes, long offsetX, long offsetY)
{
	if(refAttr->typeLength > 0)
	{
		curAttr->refPoint.x = refAttr->refPoint.x + offsetX;
		curAttr->refPoint.y = refAttr->refPoint.y + offsetY;
		curAttr->textStyleId = refAttr->textStyleId;
		curAttr->justPoint = refAttr->justPoint;
		curAttr->isVisible = refAttr->isVisible;
		curAttr->layerId = refAttr->layerId;
		if(curAttr->compId == 0)
		{	// ������� ������� � ��������� �� ����������
			curAttr->rotationAng = refAttr->rotationAng;
			curAttr->isFlipped = refAttr->isFlipped;
			return DBX_BAD_INPUT;
		}
		else
		{	// ������� ������� � ��������� ����������
			if( (curAttr->rotationAng == refAttr->rotationAng) &&
				(curAttr->isFlipped == refAttr->isFlipped) )
			{
				return TModifyCompAttribute(&tContext,curRefDes,curAttr);
			}
			else
			{
				// ��� ��������� �������� �������� ������ ����� ��������/���������� ��������
				curAttr->rotationAng = refAttr->rotationAng;
				curAttr->isFlipped = refAttr->isFlipped;
				TDeleteCompAttribute(&tContext,curRefDes,curAttr);
				return TAddCompAttribute(&tContext,curRefDes,curAttr);
			}
		}
	}
	else
		return DBX_BAD_INPUT;
}