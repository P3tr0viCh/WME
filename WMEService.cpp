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
#include "WMEStringsGridHeader.h"

#include "WMEMain.h"

#include "WMEService.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
class TListVansColumns {
public:
	static const NUM = 0;
	static const VANNUM = 1;
	static const VANTYPE = 2;
	static const CARRYING = 3;
	static const TARE = 4;
	static const DATETIME = 5;

	TIntegerSet ReadOnly;

	TIntegerSet LeftAlign;

	TListVansColumns() {
		ReadOnly = TIntegerSet() << TARE << DATETIME;
		LeftAlign = TIntegerSet() << DATETIME << VANNUM << VANTYPE;
	}
};

static TListVansColumns VansColumns;

// ---------------------------------------------------------------------------
class TListVansColumnsLocal : public TListVansColumns {
public:
	static const COUNT = 6;

	static const VISIBLE_COUNT = COUNT;
};

static TListVansColumnsLocal VansColumnsLocal;

// ---------------------------------------------------------------------------
class TListVansColumnsServer : public TListVansColumns {
public:
	static const SCALE_NUM = 6;

	static const COUNT = 7;

	static const VISIBLE_COUNT = COUNT;

	TListVansColumnsServer() : TListVansColumns() {
		ReadOnly = ReadOnly << SCALE_NUM;
	}
};

static TListVansColumnsServer VansColumnsServer;

// ---------------------------------------------------------------------------
__fastcall TfrmService::TfrmService(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmService::Show(TVanList * VanList) {
	bool Result = false;

	TfrmService * frmService = new TfrmService(Application);
	try {
		frmService->VanList = VanList;

		frmService->UpdateVanNums(stLocal);
		frmService->UpdateVanNums(stServer);

		frmService->UpdateReadOnlyVans();

		Result = frmService->ShowModal() == mrOk;
	}
	__finally {
		delete frmService;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	CreateVansColumns(stLocal);
	CreateVansColumns(stServer);

	sgVansLocal->DefaultRowHeight = Main->DefaultRowHeight;
	sgVansServer->DefaultRowHeight = Main->DefaultRowHeight;

	if (Main->User->IsAdmin) {
		sgVansLocal->Options = sgVansLocal->Options << goColSizing;
		sgVansServer->Options = sgVansServer->Options << goColSizing;
	}

	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	tbtnLocal->Down = true;
	SetSearchType(stLocal);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::FormDestroy(TObject *Sender) {
	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
TStringGrid * TfrmService::GetStringGrid(TSearchType SearchType) {
	switch (SearchType) {
	case stServer:
		return sgVansServer;
	case stLocal:
	default: ;
		return sgVansLocal;
	}
}

// ---------------------------------------------------------------------------
void TfrmService::CreateVansColumns(TSearchType SearchType) {
	TStringGrid * SG = GetStringGrid(SearchType);

	switch (SearchType) {
	case stServer:
		SG->ColCount = VansColumnsServer.VISIBLE_COUNT;

		StringGridSetHeader(SG, VansColumnsServer.SCALE_NUM,
			IDS_GRID_HEADER_SCALE_NUM, 80);

		break;
	case stLocal:
	default: ;
		SG->ColCount = VansColumnsLocal.VISIBLE_COUNT;
	}

	StringGridSetHeader(SG, VansColumns.NUM, IDS_GRID_HEADER_NUM, 50);

	StringGridSetHeader(SG, VansColumns.VANNUM, IDS_GRID_HEADER_VANNUM, 80);
	StringGridSetHeader(SG, VansColumns.VANTYPE, IDS_GRID_HEADER_VANTYPE, 120);

	StringGridSetHeader(SG, VansColumns.CARRYING, IDS_GRID_HEADER_CARRYING, 50);
	StringGridSetHeader(SG, VansColumns.TARE, IDS_GRID_HEADER_TARE, 60);

	StringGridSetHeader(SG, VansColumns.DATETIME,
		IDS_GRID_HEADER_DATETIME, 160);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::tbtnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::sgVansLocalDrawCell(TObject *Sender, int ACol,
	int ARow, TRect &Rect, TGridDrawState State) {
	StringGridDrawCell((TStringGrid*)Sender, ACol, ARow, Rect, State,
		BruttoVans.Contains(ARow - 1) ? NUSet : VansColumnsLocal.ReadOnly,
		VansColumnsLocal.LeftAlign, NUSet, Main->Settings->ColorReadOnly,
		NUColor, true, EmptyVanNums.Contains(ARow - 1));
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::sgVansServerDrawCell(TObject *Sender, int ACol,
	int ARow, TRect &Rect, TGridDrawState State) {
	StringGridDrawCell((TStringGrid*)Sender, ACol, ARow, Rect, State,
		BruttoVans.Contains(ARow - 1) ? NUSet : VansColumnsServer.ReadOnly,
		VansColumnsServer.LeftAlign, NUSet, Main->Settings->ColorReadOnly,
		NUColor, true, EmptyVanNums.Contains(ARow - 1));
}

// ---------------------------------------------------------------------------
void TfrmService::SetSearchType(TSearchType Value) {
	switch (Value) {
	case stServer:
		sgVansServer->Visible = true;
		sgVansLocal->Visible = false;

		break;
	case stLocal:
	default: ;
		sgVansLocal->Visible = true;
		sgVansServer->Visible = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::tbtnLocalClick(TObject *Sender) {
	SetSearchType(stLocal);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::tbtnServerClick(TObject *Sender) {
	SetSearchType(stServer);
}

// ---------------------------------------------------------------------------
int TfrmService::SetVan(TSearchType SearchType, int Index, TVan * Van) {
	TStringGrid * SG = GetStringGrid(SearchType);

	if (Index < 0) {
		if (!StringGridIsEmpty(SG)) {
			SG->RowCount++;
		}
		Index = SG->RowCount - 1;

		SG->Cells[VansColumns.NUM][Index] = IntToStr(Van->Num);

		SG->Cells[VansColumns.VANNUM][Index] = Van->VanNum;

		return Index;
	}

	if (Van->DateTime != DEFAULT_DATETIME) {
		SG->Cells[VansColumns.DATETIME][Index] = DateTimeToStr(Van->DateTime);
	}
	else {
		SG->Cells[VansColumns.DATETIME][Index] = "NOT FOUND";
	}

	SG->Cells[VansColumns.VANTYPE][Index] = Van->VanType->Name;

	SG->Cells[VansColumns.CARRYING][Index] = Van->Carrying != 0 ?
		IntToStr(Van->Carrying) : String("");

	SG->Cells[VansColumns.TARE][Index] = Van->Tare != 0 ?
		IntToStr(Van->Tare) : String("");

	switch (SearchType) {
	case stServer:
		// TODO:

		SG->Cells[VansColumnsServer.SCALE_NUM][Index] = IntToStr(42);

		break;
	}

	return Index;
}

// ---------------------------------------------------------------------------
void TfrmService::UpdateVanNums(TSearchType SearchType) {
	for (int i = 0; i < VanList->Count; i++) {
		SetVan(SearchType, -1, VanList->Items[i]);
	}
}

// ---------------------------------------------------------------------------
void TfrmService::UpdateReadOnlyVans() {
	for (int i = 0; i < VanList->Count; i++) {
		if (IsEmpty(VanList->Items[i]->VanNum)) {
			EmptyVanNums = EmptyVanNums << i;
		}

		if (VanList->Items[i]->WeightType == wtBrutto) {
			BruttoVans = BruttoVans << i;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::sgVansServerFixedCellClick(TObject *Sender,
	int ACol, int ARow) {
	StringGridSelectRowAfterFixedCellClick((TStringGrid*)Sender, ARow);
}

// ---------------------------------------------------------------------------
TVan * FindVanCharacteristics(String VanNum, bool FindTare) {
	TVan * Van;

	if (Odd(random(2))) {
		return NULL;
	}

	Van = new TVan();

	Van->VanType->Assign
		(Main->Settings->VanTypeList->Items[random
		(Main->Settings->VanTypeList->Count)]);

	Van->DateTime = rand();

	Van->Carrying = random(25);

	if (FindTare) {
		Van->TareSta = random(25);
		Van->TareIndex = tiStatic;
	}

	return Van;
}

// ---------------------------------------------------------------------------
void TfrmService::ClearVans(TSearchType SearchType) {
	TStringGrid * SG = GetStringGrid(SearchType);

	for (int i = 1; i < SG->RowCount; i++) {
		for (int j = 2; j < SG->ColCount; j++) {
			SG->Cells[j][i] = " ";
		}
	}
}

// ---------------------------------------------------------------------------
void TfrmService::SearchVans(TSearchType SearchType) {
	TStringGrid * SG = GetStringGrid(SearchType);

	ClearVans(SearchType);

	TVan * Van;

	for (int i = 0; i < VanList->Count; i++) {
		if (EmptyVanNums.Contains(i)) {
			continue;
		}

		Van = FindVanCharacteristics(VanList->Items[i]->VanNum,
			BruttoVans.Contains(i));

		if (Van == NULL) {
			Van = new TVan();
		}

		VanList->Items[i]->VanType->Assign(Van->VanType);
		VanList->Items[i]->Carrying = Van->Carrying;

		VanList->Items[i]->TareSta = Van->TareSta;
		VanList->Items[i]->TareDyn = Van->TareDyn;
		VanList->Items[i]->TareIndex = tiStatic;

		VanList->Items[i]->DateTime = Van->DateTime;

		SetVan(SearchType, i + 1, VanList->Items[i]);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::tbtnSearchClick(TObject *Sender) {
	TSearchType SearchType;

	if (tbtnLocal->Down) {
		SearchType = stLocal;
	}
	else {
		if (tbtnServer->Down) {
			SearchType = stServer;
		}
		else {
			return;
		}
	}

	SearchVans(SearchType);
}
// ---------------------------------------------------------------------------
