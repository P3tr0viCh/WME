// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEDebug.h"

#include "WMEAdd.h"
#include "WMEStrings.h"
#include "WMEStringsGridHeader.h"

#include "WMETDBLoadTrains.h"
#include "WMETDBLoadTrain.h"

#include "WMEMain.h"

#include "WMETrain.h"

#include "WMETrainList.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
class TListTrainsColumns {
public:
	static const NUM = 0;
	static const DATETIME = 1;
	static const CARRYING = 2;
	static const BRUTTO = 3;
	static const TARE = 4;
	static const NETTO = 5;
	static const OVERLOAD = 6;
	static const VANCOUNT = 7;
	static const OPERATOR = 8;

	static const VISIBLE_COUNT = 9;

	static const COUNT = 9;

	TListTrainsColumns() {
		LeftAlign = TIntegerSet() << DATETIME << OPERATOR;
	}

	TIntegerSet LeftAlign;
};

static TListTrainsColumns TrainsColumns;

// ---------------------------------------------------------------------------
class TListVansColumns {
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

	TListVansColumns() {
		LeftAlign =
			TIntegerSet() << DATETIME << VANNUM << VANTYPE << CARGOTYPE <<
			DEPART_STATION << PURPOSE_STATION << INVOICE_NUM <<
			INVOICE_SUPPLIER << INVOICE_RECIPIENT;
	}

	TIntegerSet ReadOnly;

	TIntegerSet LeftAlign;
};

static TListVansColumns VansColumns;

// ---------------------------------------------------------------------------
__fastcall TfrmTrainList::TfrmTrainList(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void TfrmTrainList::Show() {
	TfrmTrainList * frmTrainList = new TfrmTrainList(Application);
	try {
		// if (frmTrainList->LoadTrains()) {
		//
		// if (!frmTrainList->TrainList->IsEmpty()) {
		// if (frmTrainList->LoadTrain(0)) {
		// frmTrainList->SelectedRow = 1;
		// }
		// }
		//
		// frmTrainList->ShowModal();
		// }
		frmTrainList->Page = 0;

		frmTrainList->ShowModal();
	}
	__finally {
		delete frmTrainList;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	FPage = -1;

	SelectedRow = -1;

	TrainList = new TTrainList();

	CreateTrainsColumns();
	CreateVansColumns();

	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormBounds(this);

		sgTrains->Height = FileIni->ReadInteger(Name, "TrainsHeight",
			sgTrains->Height);
	}
	__finally {
		delete FileIni;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::FormDestroy(TObject *Sender) {
	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormBounds(this);

		FileIni->WriteInteger(Name, "TrainsHeight", sgTrains->Height);
	}
	__finally {
		delete FileIni;
	}

	TrainList->Free();

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
void TfrmTrainList::CreateTrainsColumns() {
	sgTrains->ColCount = TrainsColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgTrains, TrainsColumns.NUM, IDS_GRID_HEADER_NUM, 50);
	StringGridSetHeader(sgTrains, TrainsColumns.DATETIME,
		IDS_GRID_HEADER_DATETIME, 160);
	StringGridSetHeader(sgTrains, TrainsColumns.CARRYING,
		IDS_GRID_HEADER_CARRYING, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.BRUTTO,
		IDS_GRID_HEADER_BRUTTO, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.TARE, IDS_GRID_HEADER_TARE, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.NETTO,
		IDS_GRID_HEADER_NETTO, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.OVERLOAD,
		IDS_GRID_HEADER_OVERLOAD, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.VANCOUNT,
		IDS_GRID_HEADER_VANCOUNT, 120);
	StringGridSetHeader(sgTrains, TrainsColumns.OPERATOR,
		IDS_GRID_HEADER_OPERATOR, 120);
}

// ---------------------------------------------------------------------------
void TfrmTrainList::CreateVansColumns() {
	sgVans->ColCount = VansColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgVans, VansColumns.NUM, IDS_GRID_HEADER_NUM, 50);
	StringGridSetHeader(sgVans, VansColumns.DATETIME,
		IDS_GRID_HEADER_DATETIME, 160);
	StringGridSetHeader(sgVans, VansColumns.VANNUM, IDS_GRID_HEADER_VANNUM, 80);
	StringGridSetHeader(sgVans, VansColumns.VANTYPE,
		IDS_GRID_HEADER_VANTYPE, 120);
	StringGridSetHeader(sgVans, VansColumns.CARRYING,
		IDS_GRID_HEADER_CARRYING, 50);
	StringGridSetHeader(sgVans, VansColumns.BRUTTO, IDS_GRID_HEADER_BRUTTO, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE, IDS_GRID_HEADER_TARE, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_T, IDS_GRID_HEADER_TARE_T, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_D, IDS_GRID_HEADER_TARE_D, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_S, IDS_GRID_HEADER_TARE_S, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_INDEX,
		IDS_GRID_HEADER_TARE_INDEX, 60);
	StringGridSetHeader(sgVans, VansColumns.NETTO, IDS_GRID_HEADER_NETTO, 60);
	StringGridSetHeader(sgVans, VansColumns.OVERLOAD,
		IDS_GRID_HEADER_OVERLOAD, 80);
	StringGridSetHeader(sgVans, VansColumns.CARGOTYPE,
		IDS_GRID_HEADER_CARGOTYPE, 120);
	StringGridSetHeader(sgVans, VansColumns.DEPART_STATION,
		IDS_GRID_HEADER_DEPART_STATION, 180);
	StringGridSetHeader(sgVans, VansColumns.PURPOSE_STATION,
		IDS_GRID_HEADER_PURPOSE_STATION, 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_NUM,
		IDS_GRID_HEADER_INVOICE_NUM, 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_SUPPLIER,
		IDS_GRID_HEADER_INVOICE_SUPPLIER, 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_RECIPIENT,
		IDS_GRID_HEADER_INVOICE_RECIPIENT, 180);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::tbtnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::sgTrainsDrawCell(TObject *Sender, int ACol,
	int ARow, TRect &Rect, TGridDrawState State) {
	StringGridDrawCell(sgTrains, ACol, ARow, Rect, State, NUSet,
		TrainsColumns.LeftAlign, NUSet, NUColor, NUColor, true);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::sgVansDrawCell(TObject *Sender, int ACol,
	int ARow, TRect &Rect, TGridDrawState State) {
	StringGridDrawCell(sgVans, ACol, ARow, Rect, State, NUSet,
		VansColumns.LeftAlign, NUSet, NUColor, NUColor, true);
}

// ---------------------------------------------------------------------------
bool TfrmTrainList::LoadTrains() {
	bool Result;

	ShowWaitCursor();

	TrainList->Clear();

	TDBLoadTrains * DBLoadTrains = new TDBLoadTrains(Main->Settings->Connection,
		Page, Main->Settings->LoadTrainCount);
	try {
		Result = DBLoadTrains->Execute();

		TrainList->Assign(DBLoadTrains->TrainList);
	}
	__finally {
		DBLoadTrains->Free();

		RestoreCursor();
	}

	if (Result) {
		UpdateTrains();
	}
	else {
		MsgBoxErr(IDS_ERROR_TRAINS_LOAD);
	}

	return Result;
}

// ---------------------------------------------------------------------------
bool TfrmTrainList::LoadTrain(int Index) {
	bool Result;

	TTrain * Train = TrainList->Items[Index];

	Result = Train->VanCount == Train->VanList->Count;

	if (!Result) {
		ShowWaitCursor();

		TDBLoadTrain * DBLoadTrain =
			new TDBLoadTrain(Main->Settings->Connection, Train->TrainNum);
		try {
			Result = DBLoadTrain->Execute();

			Train->VanList->Assign(DBLoadTrain->VanList);
		}
		__finally {
			DBLoadTrain->Free();

			RestoreCursor();
		}
	}

	if (Result) {
		UpdateVans(Index);
	}
	else {
		MsgBoxErr(IDS_ERROR_TRAIN_LOAD);
	}

	return Result;
}

// ---------------------------------------------------------------------------
void TfrmTrainList::SetPage(int Value) {
	FPage = Value;

	StringGridClear(sgTrains);
	StringGridClear(sgVans);

	tbtnPrevPage->Enabled = Page > 0;

	if (LoadTrains()) {
		tbtnNextPage->Enabled =
			TrainList->Count == Main->Settings->LoadTrainCount;

		if (!TrainList->IsEmpty()) {
			if (LoadTrain(0)) {
				SelectedRow = 1;

				return;
			}
		}
		else {
			return;
		}
	}

	tbtnPrevPage->Enabled = false;
	tbtnNextPage->Enabled = false;
}

// ---------------------------------------------------------------------------
void TfrmTrainList::UpdateTrains() {
	StringGridClear(sgTrains);

	SelectedRow = -1;

	for (int i = 0; i < TrainList->Count; i++) {
		SetTrain(-1, TrainList->Items[i]);
	}
}

// ---------------------------------------------------------------------------
void TfrmTrainList::UpdateVans(int Index) {
	StringGridClear(sgVans);

	for (int i = 0; i < TrainList->Items[Index]->VanList->Count; i++) {
		SetVan(-1, TrainList->Items[Index]->VanList->Items[i]);
	}
}

// ---------------------------------------------------------------------------
void TfrmTrainList::UpdateTrain(int Index) {
	SetTrain(Index + 1, TrainList->Items[Index]);
	UpdateVans(Index);
}

// ---------------------------------------------------------------------------
int TfrmTrainList::SetTrain(int Index, TTrain * Train) {
	if (Index < 0) {
		if (!StringGridIsEmpty(sgTrains)) {
			sgTrains->RowCount++;
		}
		Index = sgTrains->RowCount - 1;
	}

	sgTrains->Cells[TrainsColumns.NUM][Index] =
		IntToStr(Index + Main->Settings->LoadTrainCount * Page);

	sgTrains->Cells[TrainsColumns.DATETIME][Index] =
		DateTimeToStr(Train->DateTime);

	sgTrains->Cells[TrainsColumns.CARRYING][Index] = IntToStr(Train->Carrying);
	sgTrains->Cells[TrainsColumns.BRUTTO][Index] = IntToStr(Train->Brutto);
	sgTrains->Cells[TrainsColumns.TARE][Index] = IntToStr(Train->Tare);
	sgTrains->Cells[TrainsColumns.NETTO][Index] = IntToStr(Train->Netto);
	sgTrains->Cells[TrainsColumns.OVERLOAD][Index] = IntToStr(Train->Overload);

	sgTrains->Cells[TrainsColumns.VANCOUNT][Index] = IntToStr(Train->VanCount);

	sgTrains->Cells[TrainsColumns.OPERATOR][Index] = Train->User->Name;

	return Index;
}

// ---------------------------------------------------------------------------
int TfrmTrainList::SetVan(int Index, TVan * Van) {
	if (Index < 0) {
		if (!StringGridIsEmpty(sgVans)) {
			sgVans->RowCount++;
		}
		Index = sgVans->RowCount - 1;
	}

	sgVans->Cells[VansColumns.NUM][Index] = IntToStr(Van->Num);
	sgVans->Cells[VansColumns.DATETIME][Index] = DateTimeToStr(Van->DateTime);

	sgVans->Cells[VansColumns.VANNUM][Index] = Van->VanNum;

	sgVans->Cells[VansColumns.VANTYPE][Index] = Van->VanType->Name;

	sgVans->Cells[VansColumns.CARRYING][Index] = IntToStr(Van->Carrying);
	sgVans->Cells[VansColumns.BRUTTO][Index] = IntToStr(Van->Brutto);
	sgVans->Cells[VansColumns.TARE][Index] = IntToStr(Van->Tare);
	sgVans->Cells[VansColumns.TARE_T][Index] = IntToStr(Van->TareTrft);
	sgVans->Cells[VansColumns.TARE_S][Index] = IntToStr(Van->TareSta);
	sgVans->Cells[VansColumns.TARE_D][Index] = IntToStr(Van->TareDyn);

	sgVans->Cells[VansColumns.TARE_INDEX][Index] = Van->TareIndexAsText;

	sgVans->Cells[VansColumns.NETTO][Index] = IntToStr(Van->Netto);
	sgVans->Cells[VansColumns.OVERLOAD][Index] = IntToStr(Van->Overload);

	sgVans->Cells[VansColumns.CARGOTYPE][Index] = Van->CargoType->Name;
	sgVans->Cells[VansColumns.DEPART_STATION][Index] = Van->DepartStation->Name;
	sgVans->Cells[VansColumns.PURPOSE_STATION][Index] =
		Van->PurposeStation->Name;

	sgVans->Cells[VansColumns.INVOICE_NUM][Index] =
		Van->InvoiceNum;

	sgVans->Cells[VansColumns.INVOICE_SUPPLIER][Index] =
		Van->InvoiceSupplier->Name;
	sgVans->Cells[VansColumns.INVOICE_RECIPIENT][Index] =
		Van->InvoiceRecipient->Name;

	return Index;
}

// ---------------------------------------------------------------------------l.----
void __fastcall TfrmTrainList::sgTrainsSelectCell(TObject *Sender, int ACol,
	int ARow, bool &CanSelect) {
	if (StringGridIsEmpty(sgTrains)) {
		return;
	}

	if (SelectedRow == ARow) {
		return;
	}

	SelectedRow = ARow;

	LoadTrain(ARow - 1);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::sgTrainsDblClick(TObject *Sender) {
	tbtnOpen->Click();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::tbtnOpenClick(TObject *Sender) {
	if (SelectedRow < 0) {
		return;
	}

	if (StringGridIsEmpty(sgTrains)) {
		return;
	}

	int Index = SelectedRow - 1;

	if (TfrmTrain::Show(TrainList->Items[Index])) {
		UpdateTrain(Index);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::sgTrainsFixedCellClick(TObject *Sender, int ACol,
	int ARow) {
	if (ARow < 1) {
		return;
	}

	if (StringGridIsEmpty((TStringGrid*)Sender)) {
		return;
	}

	((TStringGrid*)Sender)->Row = ARow;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::tbtnPrevPageClick(TObject *Sender) {
	Page -= 1;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::tbtnNextPageClick(TObject *Sender) {
	Page += 1;
}
// ---------------------------------------------------------------------------
