// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETDBVansFields.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

const TDBVansFieldName TDBVansFields::SAVE_TRAIN_FIELDS
	[TDBVansFields::SAVE_TRAIN_FIELDS_COUNT] = {
	fnVansTrnum, fnVansNum, fnVansWTime, fnVansDatetime, fnVansVannum,
	fnVansCarrying, fnVansBrutto, fnVansTare, fnVansNetto, fnVansOverload,
	fnVansOperator, fnVansOperatorTabNum, fnVansOperatorShiftNum};

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

	case fnVansCarrying:
		return "carrying";
	case fnVansBrutto:
		return "brutto";
	case fnVansTare:
		return "tare";
	case fnVansNetto:
		return "netto";
	case fnVansOverload:
		return "overload";

	case fnVansOperator:
		return "operator_name";
	case fnVansOperatorTabNum:
		return "operator_tabn";
	case fnVansOperatorShiftNum:
		return "operator_shift";
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

	case fnVansCarrying:
	case fnVansBrutto:
	case fnVansTare:
	case fnVansNetto:
	case fnVansOverload:
		return ftInteger;

	case fnVansOperator:
	case fnVansOperatorTabNum:
	case fnVansOperatorShiftNum:
		return ftString;
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
