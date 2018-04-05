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
class TVansColumns {
public:
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

	TVansColumns() {
		ReadOnly =
			TIntegerSet() << NUM << VANTYPE << TARE << TARE_D << TARE_S <<
			TARE_INDEX << NETTO << OVERLOAD;
		LeftAlign = TIntegerSet() << NUM << DATETIME << VANNUM << VANTYPE <<
			CARGOTYPE << DEPART_STATION << PURPOSE_STATION << INVOICE_NUM <<
			INVOICE_SUPPLIER << INVOICE_CONSIGN;
	}

	TIntegerSet ReadOnly;

	TIntegerSet LeftAlign;
};

static TVansColumns VansColumns;

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

	FVanList = new TObjList<TVan>();

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

	FVanList->Free();

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
void TfrmTrain::CreateVansColumns() {
	sgVans->ColCount = VansColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgVans, VansColumns.NUM, "�", 50);
	StringGridSetHeader(sgVans, VansColumns.DATETIME, "���� � �����", 160);
	StringGridSetHeader(sgVans, VansColumns.VANNUM, "� ������", 80);
	StringGridSetHeader(sgVans, VansColumns.VANTYPE, "��� ������", 120);
	StringGridSetHeader(sgVans, VansColumns.CARRYING, "��", 50);
	StringGridSetHeader(sgVans, VansColumns.BRUTTO, "������", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE, "����", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_T, "���� �", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_D, "���� �", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_S, "���� �", 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_INDEX, "����", 60);
	StringGridSetHeader(sgVans, VansColumns.NETTO, "�����", 60);
	StringGridSetHeader(sgVans, VansColumns.OVERLOAD, "��������", 80);
	StringGridSetHeader(sgVans, VansColumns.CARGOTYPE, "��� �����", 120);
}

// ---------------------------------------------------------------------------
void TfrmTrain::CreateTrainColumns() {
	sgTrain->ColCount = TrainColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgTrain, TrainColumns.VANCOUNT, "���-�� �������", 120);
	StringGridSetHeader(sgTrain, TrainColumns.DATETIME, "���� � �����", 160);
	StringGridSetHeader(sgTrain, TrainColumns.CARRYING, "��", 70);
	StringGridSetHeader(sgTrain, TrainColumns.BRUTTO, "������", 70);
	StringGridSetHeader(sgTrain, TrainColumns.TARE, "����", 70);
	StringGridSetHeader(sgTrain, TrainColumns.NETTO, "�����", 70);
	StringGridSetHeader(sgTrain, TrainColumns.OVERLOAD, "��������", 90);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnCloseClick(TObject * Sender) {
	Close();

	Application->Terminate();
}

// ---------------------------------------------------------------------------
void TfrmTrain::CalcFields(int ARow) {
	if (ARow == -1) {
		for (int i = 1; i < sgVans->RowCount; i++) {
			CalcFields(i);
		}
		return;
	}

	float Carrying =
		StrToFloatDef(sgVans->Cells[VansColumns.CARRYING][ARow], 0);
	float Brutto = StrToFloatDef(sgVans->Cells[VansColumns.BRUTTO][ARow], 0);

	int TareIndex = 0;
	int TareCol;

	switch (TareIndex) {
	case 0:
	default:
		TareCol = VansColumns.TARE_T;
	}

	float Tare = StrToFloatDef(sgVans->Cells[TareCol][ARow], 0);

	sgVans->Cells[VansColumns.TARE][ARow] = FloatToStr(Tare);

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

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateTrainCell(int ACol, float Value) {
	sgTrain->Cells[ACol][1] = FloatToStr(Value);
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

	UpdateTrainCell(TrainColumns.CARRYING, Carrying);
	UpdateTrainCell(TrainColumns.BRUTTO, Brutto);
	UpdateTrainCell(TrainColumns.TARE, Tare);
	UpdateTrainCell(TrainColumns.NETTO, Netto);
	UpdateTrainCell(TrainColumns.OVERLOAD, Overload);
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

	if (VansColumns.ReadOnly.Contains(ACol)) {
		sgVans->Options = sgVans->Options >> goEditing;
	}
	else {
		sgVans->Options = sgVans->Options << goEditing;
	}

	CalcFields();
	UpdateTrain();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansSetEditText(TObject *Sender, int ACol,
	int ARow, const UnicodeString Value) {
	//
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	if (Shift.Empty() && Key == VK_ESCAPE) {
		if (sgVans->EditorMode) {
			sgVans->EditorMode = false;

			sgVans->Cells[sgVans->Col][sgVans->Row] = CellValue;

			return;
		}
	}

	if (Shift == (TShiftState() << ssAlt)) {
		switch (Key) {
		case VK_UP:
			if (sgVans->Row > 1) {
				sgVans->Cells[sgVans->Col][sgVans->Row - 1] =
					sgVans->Cells[sgVans->Col][sgVans->Row];
			};
			break;
		case VK_DOWN:
			if (sgVans->Row < sgVans->RowCount - 1) {
				sgVans->Cells[sgVans->Col][sgVans->Row + 1] =
					sgVans->Cells[sgVans->Col][sgVans->Row];
			};
			break;
		}

		return;
	}

	if (Key == VK_RETURN) {
		CalcFields();
		UpdateTrain();
	}
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateVanList() {
	VanList->Clear();

	TVan *Van;

	for (int i = 1; i < sgVans->RowCount; i++) {
		Van = new TVan();

		Van->Num = i;
		Van->DateTime = sgVans->Cells[VansColumns.DATETIME][i];

		VanList->Add(Van);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnSaveClick(TObject *Sender) {
	UpdateVanList();

	MsgBox(FVanList->ToString());
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansGetEditMask(TObject *Sender, int ACol,
	int ARow, UnicodeString &Value) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	switch (ACol) {
	case VansColumns.DATETIME:
		Value = "00/00/0000 00:00:00";
		break;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansGetEditText(TObject *Sender, int ACol,
	int ARow, UnicodeString &Value) {
	CellValue = Value;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansExit(TObject *Sender) {
	CalcFields();
	UpdateTrain();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansDrawCell(TObject *Sender, int ACol, int ARow,
	TRect &Rect, TGridDrawState State) {
	StringGridDrawCell(sgVans, ACol, ARow, Rect, State, VansColumns.ReadOnly,
		VansColumns.LeftAlign, NUSet, Main->Settings->ColorReadOnly, NUColor, true);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgTrainDrawCell(TObject *Sender, int ACol, int ARow,
	TRect &Rect, TGridDrawState State) {
	StringGridDrawCell(sgTrain, ACol, ARow, Rect, State, NUSet,
		VansColumns.LeftAlign, NUSet, NUColor, NUColor, false);
}
// ---------------------------------------------------------------------------
