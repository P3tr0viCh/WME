// ---------------------------------------------------------------------------

#ifndef WMETDBTrainsFieldsH
#define WMETDBTrainsFieldsH

#include <System.Classes.hpp>

#include <Data.DB.hpp>

#include "WMETDBTableFields.h"

enum TDBTrainsFieldName {
	fnTrainsTrnum, fnTrainsWTime, fnTrainsDatetime, fnTrainsCarrying,
	fnTrainsBrutto, fnTrainsTare, fnTrainsNetto, fnTrainsOverload,
	fnTrainsVanCount
};

enum TDBTrainsDatabaseOp {
	dboTrainsSaveTrain,
	dboTrainsLoadTrains
};

class TDBTrainsFields
	: public TDBTableFields<TDBTrainsFieldName, TDBTrainsDatabaseOp> {
public:
	static const SAVE_TRAIN_FIELDS_COUNT = 9;
	static const LOAD_TRAINS_FIELDS_COUNT = 9;

	static const TDBTrainsFieldName SAVE_TRAIN_FIELDS[SAVE_TRAIN_FIELDS_COUNT];
	static const TDBTrainsFieldName LOAD_TRAINS_FIELDS[LOAD_TRAINS_FIELDS_COUNT];

	String GetFieldName(TDBTrainsFieldName Name);

	TFieldType GetFieldType(TDBTrainsFieldName Name);

	String GetFields(TDBTrainsDatabaseOp DatabaseOp);
	String GetValues(TDBTrainsDatabaseOp DatabaseOp, int Index);
};

// ---------------------------------------------------------------------------
#endif
