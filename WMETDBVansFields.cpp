// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETDBVansFields.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

const TDBVansFieldName TDBVansFields::SAVE_TRAIN_FIELDS
	[TDBVansFields::SAVE_TRAIN_FIELDS_COUNT] = {
	fnVansTrnum, fnVansNum, fnVansWTime, fnVansDatetime, fnVansVanNum,
	fnVansVanType, fnVansVanTypeCode, fnVansCarrying, fnVansBrutto, fnVansTare,
	fnVansNetto, fnVansOverload, fnVansCargoType, fnVansCargoTypeCode,
	fnVansOperator, fnVansOperatorTabNum, fnVansOperatorShiftNum};

const TDBVansFieldName TDBVansFields::LOAD_TRAIN_FIELDS
	[TDBVansFields::LOAD_TRAIN_FIELDS_COUNT] = {
	fnVansTrnum, fnVansNum, fnVansWTime, fnVansDatetime, fnVansVanNum,
	fnVansVanType, fnVansVanTypeCode, fnVansCarrying, fnVansBrutto, fnVansTare,
	fnVansNetto, fnVansOverload, fnVansCargoType, fnVansCargoTypeCode,
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

	case fnVansVanNum:
		return "vannum";

	case fnVansVanType:
		return "vantype";
	case fnVansVanTypeCode:
		return "vantype_code";

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

	case fnVansCargoType:
		return "cargotype";
	case fnVansCargoTypeCode:
		return "cargotype_code";

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

	case fnVansVanNum:
	case fnVansVanType:
		return ftString;

	case fnVansCarrying:
	case fnVansBrutto:
	case fnVansTare:
	case fnVansNetto:
	case fnVansOverload:
		return ftInteger;

	case fnVansCargoType:
		return ftString;

	case fnVansOperator:
	case fnVansOperatorTabNum:
	case fnVansOperatorShiftNum:
		return ftString;

	case fnVansVanTypeCode:
	case fnVansCargoTypeCode:
		return ftInteger;

	default:
		throw Exception("TDBVansFields: unknown Name");
	}
}

// ---------------------------------------------------------------------------
String TDBVansFields::GetFields(TDBVansDatabaseOp DatabaseOp) {
	switch (DatabaseOp) {
	case dboVansSaveTrain:
		return ConcatFields(SAVE_TRAIN_FIELDS, SAVE_TRAIN_FIELDS_COUNT);
	case dboVansLoadTrain:
		return ConcatFields(LOAD_TRAIN_FIELDS, LOAD_TRAIN_FIELDS_COUNT);
	default:
		throw Exception("TDBVansFields: unknown DatabaseOp");
	}
}

// ---------------------------------------------------------------------------
String TDBVansFields::GetValues(TDBVansDatabaseOp DatabaseOp, int Index) {
	switch (DatabaseOp) {
	case dboVansSaveTrain:
		return ConcatValues(SAVE_TRAIN_FIELDS, SAVE_TRAIN_FIELDS_COUNT, Index);
	case dboVansLoadTrain:
		return ConcatValues(LOAD_TRAIN_FIELDS, LOAD_TRAIN_FIELDS_COUNT, Index);
	default:
		throw Exception("TDBVansFields: unknown DatabaseOp");
	}
}

// ---------------------------------------------------------------------------
