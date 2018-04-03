// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEDebug.h"

#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMEMain.h"

#include "WMETrain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
struct {
	static const NUM = 0;
	static const DATETIME = 1;
	static const VANNUM = 2;
	static const VANTYPE = 3;
	static const CARRYING = 4;
	static const BRUTTO = 5;
	static const TARE = 6;
	static const TARE_T = 7;
	static const TARE_D = 8;
	static const TARE_S = 9;
	static const TARE_INDEX = 10;
	static const NETTO = 11;
	static const OVERLOAD = 12;
	static const CARGOTYPE = 13;
	static const DEPART_STATION = 14;
	static const PURPOSE_STATION = 15;
	static const INVOICE_NUM = 16;
	static const INVOICE_SUPPLIER = 17;
	static const INVOICE_CONSIGN = 18;

	static const VISIBLE_COUNT = 19;

	static const COUNT = 19;
} VansColumns;

// ---------------------------------------------------------------------------
struct {
	static const VANCOUNT = 0;
	static const DATETIME = 1;
	static const CARRYING = 2;
	static const BRUTTO = 3;
	static const TARE = 4;
	static const NETTO = 5;
	static const OVERLOAD = 6;

	static const VISIBLE_COUNT = 7;

	static const COUNT = 7;
} TrainColumns;

// ---------------------------------------------------------------------------
__fastcall TfrmTrain::TfrmTrain(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmTrain::Show() {
	bool Result = false;

	TfrmTrain *frmTrain = new TfrmTrain(Application);
	try {
		Result = frmTrain->ShowModal() == mrOk;
	}
	__finally {
		delete frmTrain;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	CreateVansColumns();
	CreateTrainColumns();

	if (Main->User->IsAdmin) {
		sgVans->Options = sgVans->Options << goColSizing;
		sgTrain->Options = sgTrain->Options << goColSizing;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::FormDestroy(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
void TfrmTrain::CreateVansColumns() {
	sgVans->ColCount = VansColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgVans, VansColumns.NUM, "№", 50);
	StringGridSetHeader(sgVans, VansColumns.DATETIME, "Дата и время", 160);
	StringGridSetHeader(sgVans, VansColumns.VANNUM, "№ вагона", 80);
	StringGridSetHeader(sgVans, VansColumns.VANTYPE, "Род вагона", 120);
	StringGridSetHeader(sgVans, VansColumns.CARRYING, "ГП", 50);
	StringGridSetHeader(sgVans, VansColumns.BRUTTO, "Брутто", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE, "Тара", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_T, "Тара Т", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_D, "Тара Д", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_S, "Тара С", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_INDEX, "Тара", 60);
	StringGridSetHeader(sgVans, VansColumns.NETTO, "Нетто", 60);
	StringGridSetHeader(sgVans, VansColumns.OVERLOAD, "Перегруз", 80);
	StringGridSetHeader(sgVans, VansColumns.CARGOTYPE, "Род груза", 120);
}

// ---------------------------------------------------------------------------
void TfrmTrain::CreateTrainColumns() {
	sgTrain->ColCount = TrainColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgTrain, TrainColumns.VANCOUNT, "Кол-во вагонов", 120);
	StringGridSetHeader(sgTrain, TrainColumns.DATETIME, "Дата и время", 160);
	StringGridSetHeader(sgTrain, TrainColumns.CARRYING, "ГП", 70);
	StringGridSetHeader(sgTrain, TrainColumns.BRUTTO, "Брутто", 70);
	StringGridSetHeader(sgTrain, TrainColumns.TARE, "Тара", 70);
	StringGridSetHeader(sgTrain, TrainColumns.NETTO, "Нетто", 70);
	StringGridSetHeader(sgTrain, TrainColumns.OVERLOAD, "Перегруз", 90);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnCloseClick(TObject * Sender) {
	Close();

//	Application->Terminate();
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateTrain() {
	if (StringGridIsEmpty(sgVans)) {
		sgTrain->Rows[1]->Clear();

		return;
	}

	sgTrain->Cells[TrainColumns.VANCOUNT][1] = IntToStr(sgVans->RowCount - 1);

	if (IsEmpty(sgTrain->Cells[TrainColumns.DATETIME][1])) {
		sgTrain->Cells[TrainColumns.DATETIME][1] = DateTimeToStr(Now());
	}

	float Carrying = 0;
	float Brutto = 0;
	float Tare = 0;
	float Netto = 0;
	float Overload = 0;

	for (int i = 1; i < sgVans->RowCount; i++) {
		Carrying += StrToFloatDef(sgVans->Cells[VansColumns.CARRYING][i], 0);
		Brutto += StrToFloatDef(sgVans->Cells[VansColumns.BRUTTO][i], 0);
		Tare += StrToFloatDef(sgVans->Cells[VansColumns.TARE][i], 0);
		Netto += StrToFloatDef(sgVans->Cells[VansColumns.NETTO][i], 0);
		Overload += StrToFloatDef(sgVans->Cells[VansColumns.OVERLOAD][i], 0);
	}

	// TODO
	sgTrain->Cells[TrainColumns.CARRYING][1] = Carrying > 0 ?
		FloatToStr(Carrying) : String("");
	sgTrain->Cells[TrainColumns.BRUTTO][1] = Brutto > 0 ? FloatToStr(Brutto) :
		String("");
	sgTrain->Cells[TrainColumns.TARE][1] = Tare > 0 ? FloatToStr(Tare) :
		String("");
	sgTrain->Cells[TrainColumns.NETTO][1] = Netto > 0 ? FloatToStr(Netto) :
		String("");
	sgTrain->Cells[TrainColumns.OVERLOAD][1] = FloatToStr(Overload);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnAddClick(TObject *Sender) {
	if (!StringGridIsEmpty(sgVans)) {
		sgVans->RowCount++;
	}

	sgVans->Row = sgVans->RowCount - 1;

	sgVans->Cells[VansColumns.DATETIME][sgVans->Row] = DateTimeToStr(Now());

	StringGridUpdateOrderNum(sgVans);

	UpdateTrain();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnDeleteClick(TObject *Sender) {
	StringGridDeleteRow(sgVans, sgVans->Row, VansColumns.COUNT);

	if (!StringGridIsEmpty(sgVans)) {
		StringGridUpdateOrderNum(sgVans);
	}

	UpdateTrain();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansSelectCell(TObject *Sender, int ACol, int ARow,
	bool &CanSelect) {
	if (StringGridIsEmpty(sgVans)) {
		sgVans->Options = sgVans->Options >> goEditing;
		return;
	}

	switch (ACol) {
	case VansColumns.DATETIME:
	case VansColumns.VANNUM:
	case VansColumns.CARRYING:
	case VansColumns.BRUTTO:
	case VansColumns.TARE:
		sgVans->Options = sgVans->Options << goEditing;
		break;
	default:
		sgVans->Options = sgVans->Options >> goEditing;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansSetEditText(TObject *Sender, int ACol,
	int ARow, const UnicodeString Value) {
	switch (ACol) {
	case VansColumns.CARRYING:
	case VansColumns.BRUTTO:
	case VansColumns.TARE:
		float Carrying =
			StrToFloatDef(sgVans->Cells[VansColumns.CARRYING][ARow], 0);
		float Brutto =
			StrToFloatDef(sgVans->Cells[VansColumns.BRUTTO][ARow], 0);
		float Tare = StrToFloatDef(sgVans->Cells[VansColumns.TARE][ARow], 0);

		float Netto = 0;
		float Overload = 0;

		if (Brutto > 0 && Tare > 0) {
			Netto = Brutto - Tare;
		}
		if (Carrying > 0 && Netto > 0) {
			Overload = Netto - Carrying;
		}

		sgVans->Cells[VansColumns.NETTO][ARow] = Netto > 0 ? FloatToStr(Netto) :
			String("");
		sgVans->Cells[VansColumns.OVERLOAD][ARow] = FloatToStr(Overload);
	}

	switch (ACol) {
	case VansColumns.CARRYING:
	case VansColumns.BRUTTO:
	case VansColumns.TARE:
	case VansColumns.NETTO:
	case VansColumns.OVERLOAD:
		UpdateTrain();
	}
}
// ---------------------------------------------------------------------------
