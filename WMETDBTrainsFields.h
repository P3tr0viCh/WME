// ---------------------------------------------------------------------------

#ifndef WMETDBTrainsFieldsH
#define WMETDBTrainsFieldsH

#include <System.Classes.hpp>

#include <Data.DB.hpp>

#include "WMETDBTableFields.h"

enum TDBTrainsFieldName {
	fnTrainsTrnum, fnTrainsWTime, fnTrainsDatetime, fnTrainsCarrying,
	fnTrainsBrutto, fnTrainsTare, fnTrainsNetto, fnTrainsOverload,
	fnTrainsVanCount, fnTrainsOperator, fnTrainsOperatorTabNum,
	fnTrainsOperatorShiftNum
};

class TDBTrainsFields : public TDBTableFields<TDBTrainsFieldName> {
public:
	static const FIELDS_COUNT = 12;

	static const TDBTrainsFieldName FIELDS[FIELDS_COUNT];

	String GetFieldName(TDBTrainsFieldName Name);

	TFieldType GetFieldType(TDBTrainsFieldName Name);

	String GetFields();
	String GetValues(int Index);
};

// ---------------------------------------------------------------------------
#endif
