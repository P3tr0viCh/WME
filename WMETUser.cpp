// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMEAdd.h"

#include "WMETUser.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool __fastcall TUser::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TUser * User = (TUser*) Obj;

	if (Name != User->Name || Pass != User->Pass ||
		TabNum != User->TabNum || ShiftNum != User->ShiftNum ||
		IsAdmin != User->IsAdmin)
		return false;

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TUser::Assign(TUser * Source) {
	Name = Source->Name;
	Pass = Source->Pass;
	TabNum = Source->TabNum;
	ShiftNum = Source->ShiftNum;
	IsAdmin = Source->IsAdmin;
}

// ---------------------------------------------------------------------------
