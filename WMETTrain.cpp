// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETTrain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TTrain::TTrain() {
	Init();
}

// ---------------------------------------------------------------------------
__fastcall TTrain::TTrain(TVanList * AVanList) {
	Init();

	VanList = AVanList;
}

// ---------------------------------------------------------------------------
__fastcall TTrain::~TTrain() {
	FVanList->Free();
	FUser->Free();
}

// ---------------------------------------------------------------------------
void TTrain::Init() {
	FUser = new TUser();

	FVanList = new TVanList();

	FTrainNum = TRAINNUM_NONE;

	FUnixTime = 0;
	FDateTime = NULL;
}

// ---------------------------------------------------------------------------
void TTrain::SetUser(TUser * Value) {
	User->Assign(Value);
}

// ---------------------------------------------------------------------------
void TTrain::SetVanList(TVanList * AVanList) {
	VanList->Assign(AVanList);
}

// ---------------------------------------------------------------------------
bool __fastcall TTrain::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TTrain * Train = (TTrain*) Obj;

	if (TrainNum != Train->TrainNum || UnixTime != Train->UnixTime ||
		DateTime != Train->DateTime || Carrying != Train->Carrying ||
		Brutto != Train->Brutto || Tare != Train->Tare ||
		Netto != Train->Netto || Overload != Train->Overload ||
		VanCount != Train->VanCount) {
		return false;
	}

	if (!User->Equals(Train->User)) {
		return false;
	}

	if (!VanList->Equals(Train->VanList)) {
		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TTrain::Assign(TTrain * Source) {
	TrainNum = Source->TrainNum;

	UnixTime = Source->UnixTime;
	DateTime = Source->DateTime;

	Carrying = Source->Carrying;
	Brutto = Source->Brutto;
	Tare = Source->Tare;
	Netto = Source->Netto;
	Overload = Source->Overload;

	VanCount = Source->VanCount;

	User->Assign(Source->User);

	VanList->Assign(Source->VanList);
}

// ---------------------------------------------------------------------------
String __fastcall TTrain::ToString() {
	String S;

	S = "TTrain{";
	S += "TrainNum='" + IntToStr(TrainNum) + "'";
	S += ",";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";
	S += "Carrying='" + IntToStr(Carrying) + "'";
	S += ",";
	S += "Brutto='" + IntToStr(Brutto) + "'";
	S += ",";
	S += "Tare='" + IntToStr(Tare) + "'";
	S += ",";
	S += "Netto='" + IntToStr(Netto) + "'";
	S += ",";
	S += "Overload='" + IntToStr(Overload) + "'";
	S += ",";
	S += "VanCount='" + IntToStr(VanCount) + "'";
	S += ",";
	S += "User Name='" + User->Name + "'";
	S += ",";
	S += "VanList Items Count='" + IntToStr(VanList->Count) + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
