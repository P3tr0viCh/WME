// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETDBTrainsFields.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

const TDBTrainsFieldName TDBTrainsFields::SAVE_TRAIN_FIELDS
	[TDBTrainsFields::SAVE_TRAIN_FIELDS_COUNT] = {
	fnTrainsTrnum, fnTrainsWTime, fnTrainsDatetime, fnTrainsCarrying,
	fnTrainsBrutto, fnTrainsTare, fnTrainsNetto, fnTrainsOverload,
	fnTrainsVanCount};

const TDBTrainsFieldName TDBTrainsFields::LOAD_TRAINS_FIELDS
	[TDBTrainsFields::LOAD_TRAINS_FIELDS_COUNT] = {
	fnTrainsTrnum, fnTrainsWTime, fnTrainsDatetime, fnTrainsCarrying,
	fnTrainsBrutto, fnTrainsTare, fnTrainsNetto, fnTrainsOverload,
	fnTrainsVanCount};

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
	case fnTrainsVanCount:
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
	case fnTrainsVanCount:
		return ftInteger;
	default:
		throw Exception("TDBVansFields: unknown Name");
	}
}

// ---------------------------------------------------------------------------
String TDBTrainsFields::GetFields(TDBTrainsDatabaseOp DatabaseOp) {
	switch (DatabaseOp) {
	case dboTrainsSaveTrain:
		return ConcatFields(SAVE_TRAIN_FIELDS, SAVE_TRAIN_FIELDS_COUNT);
	case dboTrainsLoadTrains:
		return ConcatFields(LOAD_TRAINS_FIELDS, LOAD_TRAINS_FIELDS_COUNT);
	default:
		throw Exception("TDBTrainsFields: unknown DatabaseOp");
	}
}

// ---------------------------------------------------------------------------
String TDBTrainsFields::GetValues(TDBTrainsDatabaseOp DatabaseOp, int Index) {
	switch (DatabaseOp) {
	case dboTrainsSaveTrain:
		return ConcatValues(SAVE_TRAIN_FIELDS, SAVE_TRAIN_FIELDS_COUNT, Index);
	case dboTrainsLoadTrains:
		return ConcatValues(LOAD_TRAINS_FIELDS, LOAD_TRAINS_FIELDS_COUNT,
			Index);
	default:
		throw Exception("TDBTrainsFields: unknown DatabaseOp");
	}
}

// ---------------------------------------------------------------------------
