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
__fastcall TTrain::TTrain(TVanList *AVanList) {
	Init();

	VanList = AVanList;
}

// ---------------------------------------------------------------------------
__fastcall TTrain::~TTrain() {
	FVanList->Free();
}

// ---------------------------------------------------------------------------
void TTrain::Init() {
	FVanList = new TVanList();

	FTrainNum = 0;
	FUnixTime = 0;
	FDateTime = NULL;
}

// ---------------------------------------------------------------------------
void TTrain::SetCarrying(int Value) {
	if (FCarrying == Value) {
		return;
	}

	FCarrying = Value;

	FOverload = FNetto - FCarrying;
}

// ---------------------------------------------------------------------------
void TTrain::SetBrutto(int Value) {
	if (FBrutto == Value) {
		return;
	}

	FBrutto = Value;

	FNetto = FBrutto - FTare;

	FOverload = FNetto - FCarrying;
}

// ---------------------------------------------------------------------------
void TTrain::SetTare(int Value) {
	if (FTare == Value) {
		return;
	}

	FTare = Value;

	FNetto = FBrutto - FTare;

	FOverload = FNetto - FCarrying;
}

// ---------------------------------------------------------------------------
void TTrain::SetVanList(TVanList *AVanList) {
	VanList->Assign(AVanList);
	CalcFields();
}

// ---------------------------------------------------------------------------
void TTrain::CalcFields() {
	if (VanList->IsEmpty()) {
		Carrying = 0;
		Brutto = 0;
		Tare = 0;

		return;
	}

	DateTime = VanList->Items[0]->DateTime;

	int ACarrying = 0;
	int ABrutto = 0;
	int ATare = 0;

	for (int i = 0; i < VanList->Count; i++) {
		ACarrying += VanList->Items[i]->Carrying;
		ABrutto += VanList->Items[i]->Brutto;
		ATare += VanList->Items[i]->Tare;
	}

	Carrying = ACarrying;
	Brutto = ABrutto;
	Tare = ATare;
}

// ---------------------------------------------------------------------------
bool __fastcall TTrain::Equals(TObject* Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TTrain *Train = (TTrain*) Obj;

	if (TrainNum != Train->TrainNum || DateTime != Train->DateTime ||
		Carrying != Train->Carrying || Brutto != Train->Brutto ||
		Tare != Train->Tare) {
		return false;
	}

	if (!VanList->Equals(Train->VanList)) {
		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TTrain::Assign(TTrain* Source) {
	TrainNum = Source->TrainNum;
	DateTime = Source->DateTime;

	VanList = Source->VanList;
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
	S += "VanList Items Count='" + IntToStr(VanList->Count) + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
