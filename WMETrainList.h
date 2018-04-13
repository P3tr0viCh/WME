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

private:
	TIntegerSet NUSet;
	TColor NUColor;

	void CreateTrainsColumns();
	void CreateVansColumns();

public:
	__fastcall TfrmTrainList(TComponent* Owner);

	static void Show();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmTrainList *frmTrainList;
// ---------------------------------------------------------------------------
#endif
