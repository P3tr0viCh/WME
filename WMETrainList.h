// ---------------------------------------------------------------------------

#ifndef WMETrainListH
#define WMETrainListH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ToolWin.hpp>

// ---------------------------------------------------------------------------
class TfrmTrainList : public TForm {
__published:
	TPanel *PanelMain;
	TStringGrid *sgTrains;
	TPanel *PanelTop;
	TStringGrid *sgVans;
	TSplitter *Splitter;
	TStatusBar *StatusBar;
	TToolBar *ToolBar;
	TToolButton *tbtnPrevPage;
	TToolButton *tbtnNextPage;
	TToolButton *tbtnSeparator01;
	TToolButton *tbtnOpen;
	TToolButton *tbtnSeparator02;
	TToolButton *tbtnClose;

	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tbtnCloseClick(TObject *Sender);
	void __fastcall sgTrainsDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall sgVansDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall sgTrainsSelectCell(TObject *Sender, int ACol, int ARow,
		bool &CanSelect);
	void __fastcall tbtnOpenClick(TObject *Sender);
	void __fastcall sgTrainsDblClick(TObject *Sender);
	void __fastcall sgTrainsFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall tbtnPrevPageClick(TObject *Sender);
	void __fastcall tbtnNextPageClick(TObject *Sender);

private:
	TIntegerSet NUSet;
	TColor NUColor;

	int FPage;

	int SelectedRow;

	TTrainList * TrainList;

	void CreateTrainsColumns();
	void CreateVansColumns();

	bool LoadTrains();
	bool LoadTrain(int Index);

	void UpdateTrains();
	void UpdateVans(int Index);
	void UpdateTrain(int Index);

	int SetTrain(int Index, TTrain * Train);
	int SetVan(int Index, TVan * Van);

	void SetPage(int Value);

public:
	__fastcall TfrmTrainList(TComponent* Owner);

	static void Show();

	__property int Page = {read = FPage, write = SetPage};
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmTrainList *frmTrainList;
// ---------------------------------------------------------------------------
#endif
