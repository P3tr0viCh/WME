// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETDBVansFields.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

const TDBVansFieldName TDBVansFields::FIELDS[TDBVansFields::FIELDS_COUNT] = {
	fnVansTrnum, fnVansNum, fnVansWTime, fnVansDatetime, fnVansWeightType,
	fnVansVanNum, fnVansVanType, fnVansVanTypeCode, fnVansCarrying,
	fnVansBrutto, fnVansTare, fnVansTareTrft, fnVansTareDyn, fnVansTareSta,
	fnVansTareIndex, fnVansNetto, fnVansOverload, fnVansCargoType,
	fnVansCargoTypeCode, fnVansAxisCount, fnVansOperator, fnVansOperatorTabNum,
	fnVansOperatorShiftNum, fnVansDepartStation, fnVansDepartStationCode,
	fnVansPurposeStation, fnVansPurposeStationCode, fnVansInvoiceNum,
	fnVansInvoiceSupplier, fnVansInvoiceSupplierCode, fnVansInvoiceRecipient,
	fnVansInvoiceRecipientCode};

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

	case fnVansWeightType:
		return "weighttype";

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
	case fnVansTareTrft:
		return "tare_t";
	case fnVansTareDyn:
		return "tare_d";
	case fnVansTareSta:
		return "tare_s";
	case fnVansTareIndex:
		return "tareindex";
	case fnVansNetto:
		return "netto";
	case fnVansOverload:
		return "overload";

	case fnVansCargoType:
		return "cargotype";
	case fnVansCargoTypeCode:
		return "cargotype_code";

	case fnVansAxisCount:
		return "naxis";

	case fnVansOperator:
		return "operator_name";
	case fnVansOperatorTabNum:
		return "operator_tabn";
	case fnVansOperatorShiftNum:
		return "operator_shift";

	case fnVansDepartStation:
		return "depart_station";
	case fnVansDepartStationCode:
		return "depart_station_code";
	case fnVansPurposeStation:
		return "purpose_station";
	case fnVansPurposeStationCode:
		return "purpose_station_code";
	case fnVansInvoiceNum:
		return "invoice_num";
	case fnVansInvoiceSupplier:
		return "invoice_supplier";
	case fnVansInvoiceSupplierCode:
		return "invoice_supplier_code";
	case fnVansInvoiceRecipient:
		return "invoice_recipient";
	case fnVansInvoiceRecipientCode:
		return "invoice_recipient_code";
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

	case fnVansWeightType:
		return ftInteger;

	case fnVansVanNum:
	case fnVansVanType:
		return ftString;

	case fnVansCarrying:
	case fnVansBrutto:
	case fnVansTare:
	case fnVansTareTrft:
	case fnVansTareDyn:
	case fnVansTareSta:
	case fnVansTareIndex:
	case fnVansNetto:
	case fnVansOverload:
		return ftInteger;

	case fnVansCargoType:
	case fnVansDepartStation:
	case fnVansPurposeStation:
	case fnVansInvoiceNum:
	case fnVansInvoiceSupplier:
	case fnVansInvoiceRecipient:
		return ftString;

	case fnVansAxisCount:
		return ftInteger;

	case fnVansOperator:
	case fnVansOperatorTabNum:
	case fnVansOperatorShiftNum:
		return ftString;

	case fnVansVanTypeCode:
	case fnVansCargoTypeCode:
	case fnVansDepartStationCode:
	case fnVansPurposeStationCode:
	case fnVansInvoiceSupplierCode:
	case fnVansInvoiceRecipientCode:
		return ftInteger;

	default:
		throw Exception("TDBVansFields: unknown Name");
	}
}

// ---------------------------------------------------------------------------
String TDBVansFields::GetFields() {
	return ConcatFields(FIELDS, FIELDS_COUNT);
}

// ---------------------------------------------------------------------------
String TDBVansFields::GetValues(int Index) {
	return ConcatValues(FIELDS, FIELDS_COUNT, Index);
}

// ---------------------------------------------------------------------------
