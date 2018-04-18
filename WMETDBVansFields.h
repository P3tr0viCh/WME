// ---------------------------------------------------------------------------

#ifndef WMETDBVansFieldsH
#define WMETDBVansFieldsH

#include <System.Classes.hpp>

#include <Data.DB.hpp>

#include "WMETDBTableFields.h"

enum TDBVansFieldName {
	fnVansTrnum, fnVansNum, fnVansWTime, fnVansDatetime, fnVansVanNum,
	fnVansVanType, fnVansCarrying, fnVansBrutto, fnVansTare, fnVansNetto,
	fnVansOverload, fnVansOperator, fnVansOperatorTabNum, fnVansOperatorShiftNum
};

enum TDBVansDatabaseOp {
	dboVansSaveTrain, dboVansLoadTrain
};

class TDBVansFields : public TDBTableFields<TDBVansFieldName, TDBVansDatabaseOp>
{
public:
	static const SAVE_TRAIN_FIELDS_COUNT = 14;
	static const LOAD_TRAIN_FIELDS_COUNT = 14;

	static const TDBVansFieldName SAVE_TRAIN_FIELDS[SAVE_TRAIN_FIELDS_COUNT];
	static const TDBVansFieldName LOAD_TRAIN_FIELDS[LOAD_TRAIN_FIELDS_COUNT];

	String GetFieldName(TDBVansFieldName Name);

	TFieldType GetFieldType(TDBVansFieldName Name);

	String GetFields(TDBVansDatabaseOp DatabaseOp);
	String GetValues(TDBVansDatabaseOp DatabaseOp, int Index);
};

// ---------------------------------------------------------------------------
#endif
