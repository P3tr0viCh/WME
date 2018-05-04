// ---------------------------------------------------------------------------

#ifndef WMETDBVansFieldsH
#define WMETDBVansFieldsH

#include <System.Classes.hpp>

#include <Data.DB.hpp>

#include "WMETDBTableFields.h"

enum TDBVansFieldName {
	fnVansTrnum, fnVansNum, fnVansWTime, fnVansDatetime, fnVansVanNum,
	fnVansVanType, fnVansVanTypeCode, fnVansCarrying, fnVansBrutto, fnVansTare,
	fnVansTareTrft, fnVansTareDyn, fnVansTareSta, fnVansTareIndex, fnVansNetto,
	fnVansOverload, fnVansCargoType, fnVansCargoTypeCode, fnVansAxisCount,
	fnVansOperator, fnVansOperatorTabNum, fnVansOperatorShiftNum,
	fnVansDepartStation, fnVansDepartStationCode, fnVansPurposeStation,
	fnVansPurposeStationCode, fnVansInvoiceNum, fnVansInvoiceSupplier,
	fnVansInvoiceSupplierCode, fnVansInvoiceRecipient,
	fnVansInvoiceRecipientCode
};

class TDBVansFields : public TDBTableFields<TDBVansFieldName> {
public:
	static const FIELDS_COUNT = 31;

	static const TDBVansFieldName FIELDS[FIELDS_COUNT];

	String GetFieldName(TDBVansFieldName Name);

	TFieldType GetFieldType(TDBVansFieldName Name);

	String GetFields();
	String GetValues(int Index);
};

// ---------------------------------------------------------------------------
#endif
