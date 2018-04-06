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
void TVan::SetCarrying(int Value) {
}

// ---------------------------------------------------------------------------
void TVan::SetBrutto(int Value) {
}

// ---------------------------------------------------------------------------
void TVan::SetTareTrft(int Value) {
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
		InvoiceConsign != Van->InvoiceConsign) {
		return false;
	}

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
	S += "Num=" + IntToStr(Num);
	S += ",";
	S += "DateTime='" + DateTimeToStr(DateTime) + "'";
	S += ",";
	S += "VanNum='" + VanNum + "'";
	S += ",";
	S += "VanType='" + VanType + "'";
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
	S += "CargoType='" + CargoType + "'";
	S += ",";
	S += "DepartStation='" + DepartStation + "'";
	S += ",";
	S += "PurposeStation='" + PurposeStation + "'";
	S += ",";
	S += "InvoiceNum='" + InvoiceNum + "'";
	S += ",";
	S += "InvoiceSupplier='" + InvoiceSupplier + "'";
	S += ",";
	S += "InvoiceConsign='" + InvoiceConsign + "'";
	S += "}";

	return S;
}

// ---------------------------------------------------------------------------
