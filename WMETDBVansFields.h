// ---------------------------------------------------------------------------

#ifndef WMETDBVansFieldsH
#define WMETDBVansFieldsH

#include <System.Classes.hpp>

#include <Data.DB.hpp>

#include "WMETDBTableFields.h"

enum TDBVansFieldName {
	fnVansTrnum, fnVansNum, fnVansWTime, fnVansDatetime, fnVansVannum,
	fnVansBrutto
};

enum TDBVansDatabaseOp {
	dboVansSaveTrain
};

class TDBVansFields : public TDBTableFields<TDBVansFieldName, TDBVansDatabaseOp>
{
public:
	static const SAVE_TRAIN_FIELDS_COUNT = 6;

	static const TDBVansFieldName SAVE_TRAIN_FIELDS[SAVE_TRAIN_FIELDS_COUNT];

	String GetFieldName(TDBVansFieldName Name);

	TFieldType GetFieldType(TDBVansFieldName Name);

	String GetFields(TDBVansDatabaseOp DatabaseOp);
	String GetValues(TDBVansDatabaseOp DatabaseOp, int Index);
};

// ---------------------------------------------------------------------------
#endif
