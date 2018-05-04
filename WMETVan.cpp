// ---------------------------------------------------------------------------

#pragma hdrstop

#include "WMEStringsGridHeader.h"

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

	FVanType = new TVanType();

	FCargoType = new TVanCatalog();
	FDepartStation = new TVanCatalog();
	FPurposeStation = new TVanCatalog();
	FInvoiceRecipient = new TVanCatalog();
	FInvoiceSupplier = new TVanCatalog();

	FNum = 0;

	FDateTime = NULL;

	FTareIndex = VAN_TARE_INDEX_S;
}

// ---------------------------------------------------------------------------
__fastcall TVan::~TVan() {
	FInvoiceSupplier->Free();
	FInvoiceRecipient->Free();
	FPurposeStation->Free();
	FDepartStation->Free();
	FCargoType->Free();

	FVanType->Free();
	FUser->Free();
}

// ---------------------------------------------------------------------------
void TVan::UpdateValues() {
	if (FBrutto > 0 && FTare > 0) {
		FNetto = FBrutto - FTare;
	}
	else {
		FNetto = 0;
	}

	if (FCarrying > 0 && FNetto > 0) {
		FOverload = FNetto - FCarrying;
	}
	else {
		FOverload = 0;
	}
}

// ---------------------------------------------------------------------------
void TVan::SetCarrying(int Value) {
	if (FCarrying == Value) {
		return;
	}

	FCarrying = Value;

	UpdateValues();
}

// ---------------------------------------------------------------------------
void TVan::SetBrutto(int Value) {
	if (FBrutto == Value) {
		return;
	}

	FBrutto = Value;

	UpdateValues();
}

// ---------------------------------------------------------------------------
void TVan::SetTareTrft(int Value) {
	if (FTareTrft == Value) {
		return;
	}

	FTareTrft = Value;

	if (TareIndex != VAN_TARE_INDEX_T) {
		return;
	}

	FTare = FTareTrft;

	UpdateValues();
}

// ---------------------------------------------------------------------------
void TVan::SetTareDyn(int Value) {
	if (FTareDyn == Value) {
		return;
	}

	FTareDyn = Value;

	if (TareIndex != VAN_TARE_INDEX_D) {
		return;
	}

	FTare = FTareDyn;

	UpdateValues();
}

// ---------------------------------------------------------------------------
void TVan::SetTareSta(int Value) {
	if (FTareSta == Value) {
		return;
	}

	FTareSta = Value;

	if (TareIndex != VAN_TARE_INDEX_S) {
		return;
	}

	FTare = FTareSta;

	UpdateValues();
}

// ---------------------------------------------------------------------------
void TVan::SetTareIndex(int Value) {
	if (FTareIndex == Value) {
		return;
	}

	FTareIndex = Value;

	switch (TareIndex) {
	case VAN_TARE_INDEX_D:
		FTare = FTareDyn;
		FTareIndexAsText = LoadStr(IDS_GRID_HEADER_TARE_D);
		break;
	case VAN_TARE_INDEX_S:
		FTare = FTareSta;
		FTareIndexAsText = LoadStr(IDS_GRID_HEADER_TARE_S);
		break;
	case VAN_TARE_INDEX_T:
	default:
		FTare = FTareTrft;
		FTareIndexAsText = LoadStr(IDS_GRID_HEADER_TARE_T);
	}

	UpdateValues();
}

// ---------------------------------------------------------------------------
void TVan::SetUser(TUser * Value) {
	User->Assign(Value);
}

// ---------------------------------------------------------------------------
bool __fastcall TVan::Equals(TObject * Obj) {
	if (this == Obj)
		return true;
	if (Obj == NULL || ClassType() != Obj->ClassType())
		return false;

	TVan * Van = (TVan*) Obj;

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
void __fastcall TVan::Assign(TVan * Source) {
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

	DepartStation->Assign(Source->DepartStation);
	PurposeStation->Assign(Source->PurposeStation);

	InvoiceNum = Source->InvoiceNum;

	InvoiceSupplier->Assign(Source->InvoiceSupplier);
	InvoiceRecipient->Assign(Source->InvoiceRecipient);
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
	S += "CargoType='" + CargoType->ToString() + "'";
	S += ",";
	S += "User Name='" + User->Name + "'";
	S += ",";
	S += "DepartStation='" + DepartStation->ToString() + "'";
	S += ",";
	S += "PurposeStation='" + PurposeStation->ToString() + "'";
	S += ",";
	S += "InvoiceNum='" + InvoiceNum + "'";
	S += ",";
	S += "InvoiceSupplier='" + InvoiceSupplier->ToString() + "'";
	S += ",";
	S += "InvoiceRecipient='" + InvoiceRecipient->ToString() + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
