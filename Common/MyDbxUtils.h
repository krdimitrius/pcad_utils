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

// Глобальное
extern DbxContext tContext; //  Global DBX Conversation Data
extern long tStatus;        //  Global Return status variable
// Наши атрибуты
static const char *attrValue = "Value"; // атрибут Value
static const char *attrRefDes = "refDes"; // атрибут RefDes2
static const char *attrRefDes_1 = "REFDES"; // атрибут RefDes2
static const char *attrRefDes2 = "refDes2"; // атрибут RefDes2
static const char *attrRefDes2_1 = "REFDES2"; // атрибут RefDes2
static const char *attrDesCommonType = "DesCommon";
static const char *attrDesCommonType_1 = "DESCOMMON";
static const char *attrDesTUType = "DesTU";
static const char *attrDesFirmType = "DesFirm";
static const char *attrDesRemType = "DesRem";
static const char *attrNoChannelType = "NoChannel";
static const char *attrNoChannelGroupType = "NoChannelGroup";	// номер группы каналов
static const char *attrNoChannelGroupType1 = "NOCHANNELGROUP";	// номер группы каналов
static const char *attrNoChannelInGroupType = "NoChannelInGroup"; // номер канала в группе
static const char *attrNoChannelInGroupType1 = "NOCHANNELINGROUP"; // номер канала в группе
static const char *attrDesChannel = "DesChannel"; // описание канала
static const char *attrNotList = "NotList";	// PE, SP, ALL - элемент не заносится
static const char *attrDesMark = "DesMark"; // атрибут маркированного компонента
static const char *attrFUNCBLOCK = "FUNCBLOCK";
static const char *attrFIT = "FIT";

static const char *textSchExtension = ".sch";
static const char *textPcbExtension = ".pcb";
static const char *textMerge1Component = ", ";
static const char *textMergeManyComponents = "-";

static const char *acceptNumber = "0123456789"; //номер
static const char *acceptLastChannelComponets = "_"; // признак элемента во вторых каналах

// открытие и закрытие базы
extern bool openDesignPcb(void);
extern bool closeDesignPcb(void);
extern bool openDesignSch(void);
extern bool closeDesignSch(void);

// ищу первое вхождение латинских букв в строку
extern char * myStrpbrkLatin(char * pstr);
// ищу первое вхождение цифр в строку
extern char * myStrpbrkDigit(char * pstr);
// перемещение атрибута curAttr по образцу refAttr у компонента curRefDes со смещением [offsetX,offsetY]
extern long modifyCompAttrByRefAttr(TAttribute *refAttr,TAttribute *curAttr, char * curRefDes, long offsetX, long offsetY);

#endif // MYDBXUTILS_H

