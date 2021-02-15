//////////////////////////////////////////////////////////////////////////////
//                                                                          
//    name:     MyDbxUtils.H
//
//    $Header: MyDbxUtils.h, 1, 09/01/14 2:09:03 AM, Dmitry Krysin$
//                                                                          
////////////////////////////////////////////////////////////////////////////////

#include "dbx32.h"

#ifndef MYDBXUTILS_H
#define MYDBXUTILS_H

// ����������
extern DbxContext tContext; //  Global DBX Conversation Data
extern long tStatus;        //  Global Return status variable
// ���� ��������
static const char *attrValue = "Value"; // ������� Value
static const char *attrRefDes = "refDes"; // ������� RefDes2
static const char *attrRefDes_1 = "REFDES"; // ������� RefDes2
static const char *attrRefDes2 = "refDes2"; // ������� RefDes2
static const char *attrRefDes2_1 = "REFDES2"; // ������� RefDes2
static const char *attrDesCommonType = "DesCommon";
static const char *attrDesCommonType_1 = "DESCOMMON";
static const char *attrDesTUType = "DesTU";
static const char *attrDesFirmType = "DesFirm";
static const char *attrDesRemType = "DesRem";
static const char *attrNoChannelType = "NoChannel";
static const char *attrNoChannelGroupType = "NoChannelGroup";	// ����� ������ �������
static const char *attrNoChannelGroupType1 = "NOCHANNELGROUP";	// ����� ������ �������
static const char *attrNoChannelInGroupType = "NoChannelInGroup"; // ����� ������ � ������
static const char *attrNoChannelInGroupType1 = "NOCHANNELINGROUP"; // ����� ������ � ������
static const char *attrDesChannel = "DesChannel"; // �������� ������
static const char *attrNotList = "NotList";	// PE, SP, ALL - ������� �� ���������
static const char *attrDesMark = "DesMark"; // ������� �������������� ����������
static const char *attrFUNCBLOCK = "FUNCBLOCK";
static const char *attrFIT = "FIT";

static const char *textSchExtension = ".sch";
static const char *textPcbExtension = ".pcb";
static const char *textMerge1Component = ", ";
static const char *textMergeManyComponents = "-";

static const char *acceptNumber = "0123456789"; //�����
static const char *acceptLastChannelComponets = "_"; // ������� �������� �� ������ �������

// �������� � �������� ����
extern bool openDesignPcb(void);
extern bool closeDesignPcb(void);
extern bool openDesignSch(void);
extern bool closeDesignSch(void);

// ��� ������ ��������� ��������� ���� � ������
extern char * myStrpbrkLatin(char * pstr);
// ��� ������ ��������� ���� � ������
extern char * myStrpbrkDigit(char * pstr);
// ����������� �������� curAttr �� ������� refAttr � ���������� curRefDes �� ��������� [offsetX,offsetY]
extern long modifyCompAttrByRefAttr(TAttribute *refAttr,TAttribute *curAttr, char * curRefDes, long offsetX, long offsetY);

#endif // MYDBXUTILS_H

