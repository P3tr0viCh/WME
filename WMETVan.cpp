// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETVan.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TVan::TVan() {
	SetDefault();
}

// ---------------------------------------------------------------------------
void TVan::SetDefault() {
	FDateTime = NULL;
}

// ---------------------------------------------------------------------------
bool __fastcall TVan::Equals(TObject* Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TVan *Van = (TVan*) Obj;

	if (DateTime != Van->DateTime)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TVan::Assign(TVan* Source) {
	DateTime = Source->DateTime;
}

// ---------------------------------------------------------------------------
String __fastcall TVan::ToString() {
	String S;

	S = "TVan{";
	S += "FDateTime='" + DateTimeToStr(FDateTime) + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
