// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETDBTrainsFields.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

const TDBTrainsFieldName TDBTrainsFields::SAVE_TRAIN_FIELDS
	[TDBTrainsFields::SAVE_TRAIN_FIELDS_COUNT] = {
	fnTrainsTrnum, fnTrainsWTime, fnTrainsDatetime, fnTrainsCarrying,
	fnTrainsBrutto, fnTrainsTare, fnTrainsNetto, fnTrainsOverload,
	fnTrainsNumVans};

// ---------------------------------------------------------------------------
String TDBTrainsFields::GetFieldName(TDBTrainsFieldName Name) {
	switch (Name) {
	case fnTrainsTrnum:
		return "trnum";
	case fnTrainsWTime:
		return "wtime";
	case fnTrainsDatetime:
		return "bdatetime";
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
	case fnTrainsNumVans:
		return "nvans";
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
	case fnTrainsCarrying:
	case fnTrainsBrutto:
	case fnTrainsTare:
	case fnTrainsNetto:
	case fnTrainsOverload:
	case fnTrainsNumVans:
		return ftInteger;
	default:
		throw Exception("TDBVansFields: unknown Name");
	}
}

// ---------------------------------------------------------------------------
String TDBTrainsFields::GetFields(TDBTrainsDatabaseOp DatabaseOp) {
	String S;

	switch (DatabaseOp) {
	case dboTrainsSaveTrain:
		S = GetFieldName(SAVE_TRAIN_FIELDS[0]);
		for (int i = 1; i < SAVE_TRAIN_FIELDS_COUNT; i++) {
			S = S + "," + GetFieldName(SAVE_TRAIN_FIELDS[i]);
		}
		break;
	default:
		throw Exception("TDBTrainsFields: unknown DatabaseOp");
	}

	return S;
}

// ---------------------------------------------------------------------------
String TDBTrainsFields::GetValues(TDBTrainsDatabaseOp DatabaseOp, int Index) {
	String S;

	switch (DatabaseOp) {
	case dboTrainsSaveTrain:
		S = GetParamValue(SAVE_TRAIN_FIELDS[0], Index);
		for (int i = 1; i < SAVE_TRAIN_FIELDS_COUNT; i++) {
			S = S + "," + GetParamValue(SAVE_TRAIN_FIELDS[i], Index);
		}
		break;
	default:
		throw Exception("TDBTrainsFields: unknown DatabaseOp");
	}

	return S;
}

// ---------------------------------------------------------------------------
