// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMEAdd.h"

#include "WMETVanCatalog.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TVanCatalog::TVanCatalog() {
	FCode = VAN_CATALOG_CODE_NONE;
	FName = "";
}

// ---------------------------------------------------------------------------
__fastcall TVanCatalog::TVanCatalog(int Code, String Name) {
	FCode = Code;
	FName = Name;
}

// ---------------------------------------------------------------------------
__fastcall TVanCatalog::TVanCatalog(int Code, NativeUInt Ident) {
	FCode = Code;
	FName = LoadStr(Ident);
}

// ---------------------------------------------------------------------------
bool __fastcall TVanCatalog::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TVanCatalog * VanCatalog = (TVanCatalog*) Obj;

	if (Code != VanCatalog->Code || Name != VanCatalog->Name)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TVanCatalog::Assign(TVanCatalog * Source) {
	Code = Source->Code;
	Name = Source->Name;
}

// ---------------------------------------------------------------------------
String __fastcall TVanCatalog::ToString() {
	String S;

	S = "TVanCatalog{";
	S += "Code='" + IntToStr(Code) + "'";
	S += ",";
	S += "Name='" + Name + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
