// ---------------------------------------------------------------------------

#ifndef WMETDBTableFieldsH
#define WMETDBTableFieldsH

#include <System.Classes.hpp>

#include <Data.DB.hpp>

template<typename T, typename D>
class TDBTableFields : public TObject {
protected:
	String ConcatFields(const T Fields[], int Count) {
		String S = GetFieldName(Fields[0]);
		for (int i = 1; i < Count; i++) {
			S = S + "," + GetFieldName(Fields[i]);
		}
		return S;
	}
	String ConcatValues(const T Fields[], int Count, int Index) {
		String S = GetParamValue(Fields[0], Index);
		for (int i = 1; i < Count; i++) {
			S = S + "," + GetParamValue(Fields[i], Index);
		}
		return S;
	}

public:
	// field_name
	virtual String GetFieldName(T Name) = 0;

	// field_name0
	String GetParamName(T Name, int Index = -1) {
		return GetFieldName(Name) + (Index < 0 ? String("") : IntToStr(Index));
	};

	// :field_name0
	String GetParamValue(T Name, int Index = -1) {
		return ":" + GetParamName(Name, Index);
	};

	virtual TFieldType GetFieldType(T Name) = 0;

	// field_name1, field_name2, ...
	virtual String GetFields(D DatabaseOp) = 0;
	// :field_name10, :field_name20, ...
	virtual String GetValues(D DatabaseOp, int Index = -1) = 0;
};

// ---------------------------------------------------------------------------
#endif
