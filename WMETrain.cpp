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

#include "WMETDBSaveTrain.h"

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
	static const INVOICE_RECIPIENT = 18;

	static const VISIBLE_COUNT = 19;

	static const COUNT = 19;

	TVansColumns() {
		ReadOnly =
			TIntegerSet() << NUM << VANTYPE << TARE << TARE_D << TARE_S <<
			TARE_INDEX << NETTO << OVERLOAD;
		LeftAlign = TIntegerSet() << NUM << DATETIME << VANNUM << VANTYPE <<
			CARGOTYPE << DEPART_STATION << PURPOSE_STATION << INVOICE_NUM <<
			INVOICE_SUPPLIER << INVOICE_RECIPIENT;
	}

	TIntegerSet ReadOnly;

	TIntegerSet LeftAlign;
};

static TVansColumns VansColumns;

// ---------------------------------------------------------------------------
class TTrainColumns {
public:
	static const VANCOUNT = 0;
	static const DATETIME = 1;
	static const CARRYING = 2;
	static const BRUTTO = 3;
	static const TARE = 4;
	static const NETTO = 5;
	static const OVERLOAD = 6;

	static const VISIBLE_COUNT = 7;

	static const COUNT = 7;

	TTrainColumns() {
		LeftAlign = TIntegerSet() << DATETIME;
	}

	TIntegerSet LeftAlign;
};

static TTrainColumns TrainColumns;

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

	Changed = false;

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

	UpdateButtons();
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
	StringGridSetHeader(sgVans, VansColumns.DEPART_STATION,
		"Станция отправления", 180);
	StringGridSetHeader(sgVans, VansColumns.PURPOSE_STATION,
		"Станция назначения", 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_NUM,
		"Номер накладной", 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_SUPPLIER,
		"Грузоотправитель", 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_RECIPIENT,
		"Грузополучатель", 180);
}

// ---------------------------------------------------------------------------
void TfrmTrain::CreateTrainColumns() {
	sgTrain->ColCount = TrainColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgTrain, TrainColumns.VANCOUNT, "Кол-во вагонов", 120);
	StringGridSetHeader(sgTrain, TrainColumns.DATETIME, "Дата и время", 160);
	StringGridSetHeader(sgTrain, TrainColumns.CARRYING, "ГП", 90);
	StringGridSetHeader(sgTrain, TrainColumns.BRUTTO, "Брутто", 90);
	StringGridSetHeader(sgTrain, TrainColumns.TARE, "Тара", 90);
	StringGridSetHeader(sgTrain, TrainColumns.NETTO, "Нетто", 90);
	StringGridSetHeader(sgTrain, TrainColumns.OVERLOAD, "Перегруз", 90);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnCloseClick(TObject * Sender) {
	Close();
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

	sgVans->Cells[VansColumns.NETTO][ARow] = FloatToStr(Netto);
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
	Changed = true;

	if (!StringGridIsEmpty(sgVans)) {
		sgVans->RowCount++;
	}

	sgVans->Row = sgVans->RowCount - 1;

	sgVans->Cells[VansColumns.DATETIME][sgVans->Row] = DateTimeToStr(Now());

	StringGridUpdateOrderNum(sgVans);

	UpdateTrain();

	UpdateButtons();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnDeleteClick(TObject *Sender) {
	Changed = true;

	StringGridDeleteRow(sgVans, sgVans->Row, VansColumns.COUNT);

	if (!StringGridIsEmpty(sgVans)) {
		StringGridUpdateOrderNum(sgVans);
	}

	UpdateTrain();

	UpdateButtons();
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
	Changed = true;
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
void TfrmTrain::UpdateValue(int ACol, int ARow) {
	if (IsEmpty(sgVans->Cells[ACol][ARow])) {
		sgVans->Cells[ACol][ARow] = "0";
	}
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateValues(int ARow) {
	if (ARow == -1) {
		for (int i = 1; i < sgVans->RowCount; i++) {
			UpdateValues(i);
		}
		return;
	}

	UpdateValue(VansColumns.CARRYING, ARow);
	UpdateValue(VansColumns.BRUTTO, ARow);
	UpdateValue(VansColumns.TARE_T, ARow);
	UpdateValue(VansColumns.TARE_D, ARow);
	UpdateValue(VansColumns.TARE_S, ARow);

	CalcFields(ARow);
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateButtons() {
	tbtnDelete->Enabled = !StringGridIsEmpty(sgVans);
	tbtnSave->Enabled = tbtnDelete->Enabled;

	if (!tbtnDelete->Enabled) {
		sgVans->Options = sgVans->Options >> goEditing;
	}

	sgVans->EditorMode = false;
}

// ---------------------------------------------------------------------------
String TfrmTrain::CheckStrValue(String Value) {
	int P = Value.Pos(sLineBreak);
	if (P > 0) {
		Value = Value.SubString(0, P - 1);
	}

	return Trim(Value);
}

// ---------------------------------------------------------------------------
void TfrmTrain::CheckStrValue(int ACol, int ARow) {
	sgVans->Cells[ACol][ARow] = CheckStrValue(sgVans->Cells[ACol][ARow]);
}

// ---------------------------------------------------------------------------
bool TfrmTrain::CheckDateTimeValue(String Value) {
	try {
		StrToDateTime(Value);
	}
	catch (...) {
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool TfrmTrain::CheckIntValue(String Value) {
	try {
		StrToInt(Value);
	}
	catch (...) {
		return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
bool TfrmTrain::CheckValues(int ARow) {
	if (ARow == -1) {
		bool Result = true;

		for (int i = 1; i < sgVans->RowCount; i++) {
			if (!CheckValues(i)) {
				Result = false;
			}
		}

		return Result;
	}

	CheckStrValue(VansColumns.VANNUM, ARow);
	CheckStrValue(VansColumns.VANTYPE, ARow);
	CheckStrValue(VansColumns.CARGOTYPE, ARow);
	CheckStrValue(VansColumns.DEPART_STATION, ARow);
	CheckStrValue(VansColumns.PURPOSE_STATION, ARow);
	CheckStrValue(VansColumns.INVOICE_NUM, ARow);
	CheckStrValue(VansColumns.INVOICE_SUPPLIER, ARow);
	CheckStrValue(VansColumns.INVOICE_RECIPIENT, ARow);

	if (!CheckDateTimeValue(sgVans->Cells[VansColumns.DATETIME][ARow])) {
		StringGridSelectCell(sgVans, VansColumns.DATETIME, ARow);
		return false;
	}

	if (!CheckIntValue(sgVans->Cells[VansColumns.CARRYING][ARow])) {
		StringGridSelectCell(sgVans, VansColumns.CARRYING, ARow);
		return false;
	}
	if (!CheckIntValue(sgVans->Cells[VansColumns.BRUTTO][ARow])) {
		StringGridSelectCell(sgVans, VansColumns.BRUTTO, ARow);
		return false;
	}
	if (!CheckIntValue(sgVans->Cells[VansColumns.TARE_T][ARow])) {
		StringGridSelectCell(sgVans, VansColumns.TARE_T, ARow);
		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
TVanList *TfrmTrain::GetVanList() {
	TVanList *VanList = new TVanList();

	TVan *Van;

	for (int i = 1; i < sgVans->RowCount; i++) {
		Van = new TVan();

		Van->Num = i;

		Van->DateTime = sgVans->Cells[VansColumns.DATETIME][i];

		Van->VanNum = sgVans->Cells[VansColumns.VANNUM][i];
		Van->VanType = sgVans->Cells[VansColumns.VANTYPE][i];

		Van->Carrying = StrToInt(sgVans->Cells[VansColumns.CARRYING][i]);
		Van->Brutto = StrToInt(sgVans->Cells[VansColumns.BRUTTO][i]);

		Van->TareTrft = StrToInt(sgVans->Cells[VansColumns.TARE_T][i]);
		Van->TareDyn = StrToInt(sgVans->Cells[VansColumns.TARE_D][i]);
		Van->TareSta = StrToInt(sgVans->Cells[VansColumns.TARE_S][i]);
		Van->TareIndex = 0; // sgVans->Cells[VansColumns.TARE_INDEX][i];

		Van->CargoType = sgVans->Cells[VansColumns.CARGOTYPE][i];
		Van->DepartStation = sgVans->Cells[VansColumns.DEPART_STATION][i];
		Van->PurposeStation = sgVans->Cells[VansColumns.PURPOSE_STATION][i];
		Van->InvoiceNum = sgVans->Cells[VansColumns.INVOICE_NUM][i];
		Van->InvoiceSupplier = sgVans->Cells[VansColumns.INVOICE_SUPPLIER][i];
		Van->InvoiceRecipient = sgVans->Cells[VansColumns.INVOICE_RECIPIENT][i];

		VanList->Add(Van);
	}

	return VanList;
}

// ---------------------------------------------------------------------------
TTrain *TfrmTrain::GetTrain() {
	TTrain *Train = new TTrain(GetVanList());

	Train->TrainNum = DateTimeToWTime(Now());
	Train->UnixTime = DateTimeToWTime(Train->DateTime);

	return Train;
}

// ---------------------------------------------------------------------------
bool TfrmTrain::SaveVans() {
	if (StringGridIsEmpty(sgVans)) {
		MsgBoxErr("NOTHING SAVE");
		return false;
	}

	UpdateValues();

	if (!CheckValues()) {
		MsgBoxErr("BAD VALUES");
		return false;
	}

	bool Result;

	TDBSaveTrain *DBSaveTrain = new TDBSaveTrain(Main->Settings->Connection,
		GetTrain());
	try {
		Result = DBSaveTrain->Execute();
	}
	__finally {
		DBSaveTrain->Free();
	}

	if (!Result) {
		MsgBoxErr("SAVE ERROR");
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnSaveClick(TObject * Sender) {
	if (SaveVans()) {
		Changed = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansGetEditMask(TObject * Sender, int ACol,
	int ARow, UnicodeString & Value) {
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
void __fastcall TfrmTrain::sgVansGetEditText(TObject * Sender, int ACol,
	int ARow, UnicodeString & Value) {
	CellValue = Value;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansExit(TObject * Sender) {
	CalcFields();
	UpdateTrain();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansDrawCell(TObject * Sender, int ACol, int ARow,
	TRect & Rect, TGridDrawState State) {
	StringGridDrawCell(sgVans, ACol, ARow, Rect, State, VansColumns.ReadOnly,
		VansColumns.LeftAlign, NUSet, Main->Settings->ColorReadOnly,
		NUColor, true);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgTrainDrawCell(TObject * Sender, int ACol, int ARow,
	TRect & Rect, TGridDrawState State) {
	StringGridDrawCell(sgTrain, ACol, ARow, Rect, State, NUSet,
		TrainColumns.LeftAlign, NUSet, NUColor, NUColor, false);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::FormCloseQuery(TObject *Sender, bool &CanClose) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	if (!Changed) {
		return;
	}

	switch (MsgBox(LoadStr(IDS_QUESTION_TRAIN_CHANGED),
		MB_ICONQUESTION | MB_YESNOCANCEL)) {
	case ID_YES:
		CanClose = SaveVans();
		break;
	case ID_CANCEL:
		CanClose = false;
		break;
	default:
		CanClose = true;
		ModalResult = mrCancel;
	}
}
// ---------------------------------------------------------------------------
