// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETDBTrainsFields.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

const TDBTrainsFieldName TDBTrainsFields::FIELDS[TDBTrainsFields::FIELDS_COUNT]
	= {fnTrainsTrnum, fnTrainsWTime, fnTrainsDatetime, fnTrainsWeightType,
	fnTrainsCarrying, fnTrainsBrutto, fnTrainsTare, fnTrainsNetto,
	fnTrainsOverload, fnTrainsVanCount, fnTrainsOperator,
	fnTrainsOperatorTabNum, fnTrainsOperatorShiftNum};

// ---------------------------------------------------------------------------
String TDBTrainsFields::GetFieldName(TDBTrainsFieldName Name) {
	switch (Name) {
	case fnTrainsTrnum:
		return "trnum";

	case fnTrainsWTime:
		return "wtime";

	case fnTrainsDatetime:
		return "bdatetime";

	case fnTrainsWeightType:
		return "weighttype";

	case fnTrainsCarrying:
		return "carrying";
	case fnTrainsBrutto:
		return "brutto";
	case fnTrainsTare:
		return "tare";
	case fnTrainsNetto:
		return "netto";
	case fnTrainsOverload:
		return "overload";

	case fnTrainsVanCount:
		return "nvans";

	case fnTrainsOperator:
		return "operator_name";
	case fnTrainsOperatorTabNum:
		return "operator_tabn";
	case fnTrainsOperatorShiftNum:
		return "operator_shift";
	default:
		throw Exception("TDBVansFields: unknown Name");
	}
}

// ---------------------------------------------------------------------------
TFieldType TDBTrainsFields::GetFieldType(TDBTrainsFieldName Name) {
	switch (Name) {
	case fnTrainsTrnum:
		return ftInteger;

	case fnTrainsWTime:
		return ftInteger;

	case fnTrainsDatetime:
		return ftString;

	case fnTrainsWeightType:
		return ftInteger;

	case fnTrainsCarrying:
	case fnTrainsBrutto:
	case fnTrainsTare:
	case fnTrainsNetto:
	case fnTrainsOverload:
		return ftInteger;

	case fnTrainsVanCount:
		return ftInteger;

	case fnTrainsOperator:
	case fnTrainsOperatorTabNum:
	case fnTrainsOperatorShiftNum:
		return ftString;
	default:
		throw Exception("TDBVansFields: unknown Name");
	}
}

// ---------------------------------------------------------------------------
String TDBTrainsFields::GetFields() {
	return ConcatFields(FIELDS, FIELDS_COUNT);
}

// ---------------------------------------------------------------------------
String TDBTrainsFields::GetValues(int Index) {
	return ConcatValues(FIELDS, FIELDS_COUNT, Index);
}

// ---------------------------------------------------------------------------
