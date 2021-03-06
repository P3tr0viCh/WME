// ---------------------------------------------------------------------------

#ifndef WMETrainH
#define WMETrainH

// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "WMETVan.h"
#include "WMETTrain.h"
#include "WMETVanCatalog.h"
#include "WMETVanType.h"

// ---------------------------------------------------------------------------
class TfrmTrain : public TForm {
__published:
	TStatusBar *StatusBar;
	TPanel *PanelMain;
	TToolBar *ToolBar;
	TToolButton *tbtnClose;
	TStringGrid *sgVans;
	TPanel *PanelTop;
	TStringGrid *sgTrain;
	TToolButton *tbtnDelete;
	TToolButton *tbtnAdd;
	TToolButton *tbtnSeparator01;
	TPanel *PanelBottom;
	TToolButton *tbtnSave;
	TToolButton *tbtnSeparator03;
	TComboBox *ComboBox;
	TToolButton *tbtnService;
	TToolButton *tbtnSeparator02;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall tbtnCloseClick(TObject *Sender);
	void __fastcall tbtnAddClick(TObject *Sender);
	void __fastcall tbtnDeleteClick(TObject *Sender);
	void __fastcall sgVansSelectCell(TObject *Sender, int ACol, int ARow,
		bool &CanSelect);
	void __fastcall sgVansSetEditText(TObject *Sender, int ACol, int ARow,
		const UnicodeString Value);
	void __fastcall sgVansKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift);
	void __fastcall tbtnSaveClick(TObject *Sender);
	void __fastcall sgVansGetEditMask(TObject *Sender, int ACol, int ARow,
		UnicodeString &Value);
	void __fastcall sgVansGetEditText(TObject *Sender, int ACol, int ARow,
		UnicodeString &Value);
	void __fastcall sgVansExit(TObject *Sender);
	void __fastcall sgVansDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall sgTrainDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall sgVansDblClick(TObject *Sender);
	void __fastcall ComboBoxExit(TObject *Sender);
	void __fastcall ComboBoxEnter(TObject *Sender);
	void __fastcall ComboBoxKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift);
	void __fastcall ComboBoxKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ToolBarMouseActivate(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y, int HitTest,
		TMouseActivate &MouseActivate);
	void __fastcall tbtnServiceClick(TObject *Sender);
	void __fastcall sgVansFixedCellClick(TObject *Sender, int ACol, int ARow);

private:
	bool FChanged;

	TTrain * Train;

	String CellValue;

	TVanCatalogList * WeightTypeList;

	TVanCatalogList * TareIndexList;

	void SetChanged(bool Value);

	void CreateVansColumns();
	void CreateTrainColumns();

	void UpdateTrainCell(int ACol, float Value);

	void CalcFields(int ARow = -1);
	void UpdateTrain();

	void UpdateValue(int ACol, int ARow);
	void UpdateValues(int ARow = -1);

	void UpdateButtons();

	void CheckValue(int ACol, int ARow, int MaxLength);
	bool CheckValues(int ARow = -1);
	bool CheckVanNums();
	bool CheckVanList();

	int GetVanCatalogCode(int CatalogIdent, String Name);

	TVanType * GetVanType(String Name);

	TVanList * GetVanList();
	TTrain * GetTrain(int TrainNum);

	bool SaveVans();

	int SetVan(int Index, TVan * Van);

	void UpdateVans(TTrain * Train);

	void UpdateVanComboBox(TVanCatalogList * VanCatalogList);
	bool ShowVanComboBox(int Col);

public:
	__fastcall TfrmTrain(TComponent * Owner);

	static bool Show(TTrain * Train);

	__property bool Changed = {read = FChanged, write = SetChanged};
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmTrain *frmTrain;
// ---------------------------------------------------------------------------
#endif
