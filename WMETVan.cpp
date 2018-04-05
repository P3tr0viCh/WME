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
	FNum = 0;
	FDateTime = NULL;
}

// ---------------------------------------------------------------------------
bool __fastcall TVan::Equals(TObject* Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TVan *Van = (TVan*) Obj;

	if (Num != Van->Num || DateTime != Van->DateTime)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TVan::Assign(TVan* Source) {
	Num = Source->Num;
	DateTime = Source->DateTime;
}

// ---------------------------------------------------------------------------
String __fastcall TVan::ToString() {
	String S;

	S = "TVan{";
	S += "FNum=" + IntToStr(FNum);
	S += ",";
	S += "FDateTime='" + DateTimeToStr(FDateTime) + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
