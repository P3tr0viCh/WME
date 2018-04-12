// ---------------------------------------------------------------------------

#ifndef WMETDBTrainsFieldsH
#define WMETDBTrainsFieldsH

#include <System.Classes.hpp>

#include <Data.DB.hpp>

#include "WMETDBTableFields.h"

enum TDBTrainsFieldName {
	fnTrainsTrnum, fnTrainsWTime, fnTrainsDatetime, fnTrainsCarrying,
	fnTrainsBrutto, fnTrainsTare, fnTrainsNetto, fnTrainsOverload
};

enum TDBTrainsDatabaseOp {
	dboTrainsSaveTrain
};

class TDBTrainsFields
	: public TDBTableFields<TDBTrainsFieldName, TDBTrainsDatabaseOp> {
public:
	static const SAVE_TRAIN_FIELDS_COUNT = 8;

	static const TDBTrainsFieldName SAVE_TRAIN_FIELDS[SAVE_TRAIN_FIELDS_COUNT];

	String GetFieldName(TDBTrainsFieldName Name);

	TFieldType GetFieldType(TDBTrainsFieldName Name);

	String GetFields(TDBTrainsDatabaseOp DatabaseOp);
	String GetValues(TDBTrainsDatabaseOp DatabaseOp, int Index);
};

// ---------------------------------------------------------------------------
#endif