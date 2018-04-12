// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETDBVansFields.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

const TDBVansFieldName TDBVansFields::SAVE_TRAIN_FIELDS
	[TDBVansFields::SAVE_TRAIN_FIELDS_COUNT] = {
	fnVansTrnum, fnVansNum, fnVansWTime, fnVansDatetime, fnVansVannum,
	fnVansBrutto};

// ---------------------------------------------------------------------------
String TDBVansFields::GetFieldName(TDBVansFieldName Name) {
	switch (Name) {
	case fnVansTrnum:
		return "trnum";
	case fnVansNum:
		return "num";
	case fnVansWTime:
		return "wtime";
	case fnVansDatetime:
		return "bdatetime";
	case fnVansVannum:
		return "vannum";
	case fnVansBrutto:
		return "brutto";
	default:
		throw Exception("TDBVansFields: unknown Name");
	}
}

// ---------------------------------------------------------------------------
TFieldType TDBVansFields::GetFieldType(TDBVansFieldName Name) {
	switch (Name) {
	case fnVansTrnum:
		return ftInteger;
	case fnVansNum:
		return ftInteger;
	case fnVansWTime:
		return ftInteger;
	case fnVansDatetime:
		return ftString;
	case fnVansVannum:
		return ftString;
	case fnVansBrutto:
		return ftInteger;
	default:
		throw Exception("TDBVansFields: unknown Name");
	}
}

// ---------------------------------------------------------------------------
String TDBVansFields::GetFields(TDBVansDatabaseOp DatabaseOp) {
	String S;

	switch (DatabaseOp) {
	case dboVansSaveTrain:
		S = GetFieldName(SAVE_TRAIN_FIELDS[0]);
		for (int i = 1; i < SAVE_TRAIN_FIELDS_COUNT; i++) {
			S = S + "," + GetFieldName(SAVE_TRAIN_FIELDS[i]);
		}
		break;
	default:
		throw Exception("TDBVansFields: unknown DatabaseOp");
	}

	return S;
}

// ---------------------------------------------------------------------------
String TDBVansFields::GetValues(TDBVansDatabaseOp DatabaseOp, int Index) {
	String S;

	switch (DatabaseOp) {
	case dboVansSaveTrain:
		S = GetParamValue(SAVE_TRAIN_FIELDS[0], Index);
		for (int i = 1; i < SAVE_TRAIN_FIELDS_COUNT; i++) {
			S = S + "," + GetParamValue(SAVE_TRAIN_FIELDS[i], Index);
		}
		break;
	default:
		throw Exception("TDBVansFields: unknown DatabaseOp");
	}

	return S;
}

// ---------------------------------------------------------------------------
