// ---------------------------------------------------------------------------

#ifndef WMETDBTableFieldsH
#define WMETDBTableFieldsH

#include <System.Classes.hpp>

#include <Data.DB.hpp>

template<typename T, typename D>
class TDBTableFields : public TObject {
public:
	// field_name
	virtual String GetFieldName(T Name) = 0;

	// field_name0
	String GetParamName(T Name, int Index) {
		return GetFieldName(Name) + IntToStr(Index);
	};

	// :field_name0
	String GetParamValue(T Name, int Index) {
		return ":" + GetParamName(Name, Index);
	};

	virtual TFieldType GetFieldType(T Name) = 0;

	// field_name1, field_name2, ...
	virtual String GetFields(D DatabaseOp) = 0;
	// :field_name10, :field_name20, ...
	virtual String GetValues(D DatabaseOp, int Index) = 0;
};

// ---------------------------------------------------------------------------
#endif
