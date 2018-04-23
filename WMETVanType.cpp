// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMEAdd.h"

#include "WMETVanType.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TVanType::TVanType() {
	FAxisCount = VAN_TYPE_AXIS_NONE;
}

// ---------------------------------------------------------------------------
__fastcall TVanType::TVanType(int Code, String Name, int AxisCount)
	: TVanCatalog(Code, Name) {
	FAxisCount = AxisCount;
}

// ---------------------------------------------------------------------------
bool __fastcall TVanType::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TVanType *VanCatalog = (TVanType*) Obj;

	if (Code != VanCatalog->Code || Name != VanCatalog->Name)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TVanType::Assign(TVanType * Source) {
	Code = Source->Code;
	Name = Source->Name;
	AxisCount = Source->AxisCount;
}

// ---------------------------------------------------------------------------
String __fastcall TVanType::ToString() {
	String S;

	S = "TVanType{";
	S += "Code='" + IntToStr(Code) + "'";
	S += ",";
	S += "Name='" + Name + "'";
	S += ",";
	S += "AxisCount='" + IntToStr(AxisCount) + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
