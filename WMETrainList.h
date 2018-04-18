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
	TToolBar *ToolBar;
	TToolButton *tbtnOpen;
	TToolButton *tbtnSeparator02;
	TToolButton *tbtnClose;
	TStringGrid *sgTrains;
	TPanel *PanelTop;
	TStringGrid *sgVans;
	TSplitter *Splitter;
	TStatusBar *StatusBar;

	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tbtnCloseClick(TObject *Sender);
	void __fastcall sgTrainsDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall sgVansDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall sgTrainsSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall tbtnOpenClick(TObject *Sender);
	void __fastcall sgTrainsDblClick(TObject *Sender);
	void __fastcall sgTrainsFixedCellClick(TObject *Sender, int ACol, int ARow);


private:
	TIntegerSet NUSet;
	TColor NUColor;

    int SelectedRow;

	TTrainList *TrainList;

	void CreateTrainsColumns();
	void CreateVansColumns();

	bool LoadTrains();
	bool LoadTrain(int Index);

	void UpdateTrains();
	void UpdateVans(int Index);

	int SetTrain(int Index, TTrain *Train);
	int SetVan(int Index, TVan *Van);

public:
	__fastcall TfrmTrainList(TComponent* Owner);

	static void Show();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmTrainList *frmTrainList;
// ---------------------------------------------------------------------------
#endif
