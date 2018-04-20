// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMETVan.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TVan::TVan() {
	Init();
}

// ---------------------------------------------------------------------------
void TVan::Init() {
	FUser = new TUser();

	FVanType = new TVanCatalog();
	FCargoType = new TVanCatalog();

	FNum = 0;
	FDateTime = NULL;
	FTareIndex = 0;
}

// ---------------------------------------------------------------------------
__fastcall TVan::~TVan() {
	FCargoType->Free();
	FVanType->Free();
	FUser->Free();
}

// ---------------------------------------------------------------------------
void TVan::SetCarrying(int Value) {
	if (FCarrying == Value) {
		return;
	}

	FCarrying = Value;

	FOverload = FNetto - FCarrying;
}

// ---------------------------------------------------------------------------
void TVan::SetBrutto(int Value) {
	if (FBrutto == Value) {
		return;
	}

	FBrutto = Value;

	FNetto = FBrutto - FTare;

	FOverload = FNetto - FCarrying;
}

// ---------------------------------------------------------------------------
void TVan::SetTareTrft(int Value) {
	if (FTareTrft == Value) {
		return;
	}

	FTareTrft = Value;

	if (TareIndex != 0) {
		return;
	}

	FTare = FTareTrft;

	FNetto = FBrutto - FTare;

	FOverload = FNetto - FCarrying;
}

// ---------------------------------------------------------------------------
void TVan::SetTareDyn(int Value) {
}

// ---------------------------------------------------------------------------
void TVan::SetTareSta(int Value) {
}

// ---------------------------------------------------------------------------
void TVan::SetTareIndex(int Value) {
}

// ---------------------------------------------------------------------------
void TVan::SetUser(TUser *Value) {
	User->Assign(Value);
}

// ---------------------------------------------------------------------------
bool __fastcall TVan::Equals(TObject* Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TVan *Van = (TVan*) Obj;

	if (Num != Van->Num || DateTime != Van->DateTime || VanNum != Van->VanNum ||
		VanType != Van->VanType || Carrying != Van->Carrying ||
		Brutto != Van->Brutto || TareTrft != Van->TareTrft ||
		TareDyn != Van->TareDyn || TareSta != Van->TareSta ||
		TareIndex != Van->TareIndex || CargoType != Van->CargoType ||
		DepartStation != Van->DepartStation ||
		PurposeStation != Van->PurposeStation ||
		InvoiceNum != Van->InvoiceNum ||
		InvoiceSupplier != Van->InvoiceSupplier ||
		InvoiceRecipient != Van->InvoiceRecipient) {
		return false;
	}

	if (!User->Equals(Van->User)) {
		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TVan::Assign(TVan* Source) {
	Num = Source->Num;
	DateTime = Source->DateTime;

	VanNum = Source->VanNum;

	VanType->Assign(Source->VanType);

	Carrying = Source->Carrying;
	Brutto = Source->Brutto;
	TareTrft = Source->TareTrft;
	TareDyn = Source->TareDyn;
	TareSta = Source->TareSta;
	TareIndex = Source->TareIndex;

	CargoType->Assign(Source->CargoType);

	User->Assign(Source->User);

	DepartStation = Source->DepartStation;
	PurposeStation = Source->PurposeStation;
	InvoiceNum = Source->InvoiceNum;
	InvoiceSupplier = Source->InvoiceSupplier;
	InvoiceRecipient = Source->InvoiceRecipient;
}

// ---------------------------------------------------------------------------
String __fastcall TVan::ToString() {
	String S;

	S = "TVan{";
	S += "Num=" + IntToStr(Num);
	S += ",";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";
	S += "VanNum='" + VanNum + "'";
	S += ",";
	S += "VanType='" + VanType->Name + "'";
	S += ",";
	S += "VanTypeCode='" + IntToStr(VanType->Code) + "'";
	S += ",";
	S += "Carrying='" + IntToStr(Carrying) + "'";
	S += ",";
	S += "Brutto='" + IntToStr(Brutto) + "'";
	S += ",";
	S += "Tare='" + IntToStr(Tare) + "'";
	S += ",";
	S += "TareTrft='" + IntToStr(TareTrft) + "'";
	S += ",";
	S += "TareDyn='" + IntToStr(TareDyn) + "'";
	S += ",";
	S += "TareSta='" + IntToStr(TareSta) + "'";
	S += ",";
	S += "TareIndex='" + IntToStr(TareIndex) + "'";
	S += ",";
	S += "Netto='" + IntToStr(Netto) + "'";
	S += ",";
	S += "Overload='" + IntToStr(Overload) + "'";
	S += ",";
	S += "CargoType='" + CargoType->Name + "'";
	S += ",";
	S += "CargoTypeCode='" + IntToStr(CargoType->Code) + "'";
	S += ",";
	S += "User Name='" + User->Name + "'";
	S += ",";
	S += "DepartStation='" + DepartStation + "'";
	S += ",";
	S += "PurposeStation='" + PurposeStation + "'";
	S += ",";
	S += "InvoiceNum='" + InvoiceNum + "'";
	S += ",";
	S += "InvoiceSupplier='" + InvoiceSupplier + "'";
	S += ",";
	S += "InvoiceRecipient='" + InvoiceRecipient + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
