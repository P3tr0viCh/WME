// ---------------------------------------------------------------------------

#ifndef WMEOptionsH
#define WMEOptionsH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>

#include "WMEOptionsUser.h"

#include "WMETSettings.h"

// ---------------------------------------------------------------------------
class TfrmOptions : public TForm {
__published:

	TPanel *PanelMain;
	TPageControl *PageControl;
	TTabSheet *tsDatabase;
	TLabel *lblDBConnection;
	TBevel *bvlDB;
	TLabeledEdit *eDBUser;
	TLabeledEdit *eDBPass;
	TButton *btnDBConnectionCheck;
	TLabeledEdit *eDBHost;
	TLabeledEdit *eDBPort;
	TButton *btnDBConnectionDefault;
	TButton *btnDBCreate;
	TButton *btnDBDelete;
	TTabSheet *tsUsers;
	TPanel *PanelButtons;
	TButton *btnOk;
	TButton *btnCancel;
	TStringGrid *sgUsers;
	TButton *btnUsersAdd;
	TButton *btnUsersChange;
	TButton *btnUsersDelete;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnDBConnectionCheckClick(TObject *Sender);
	void __fastcall btnDBConnectionDefaultClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall btnUsersAddClick(TObject *Sender);
	void __fastcall btnUsersChangeClick(TObject *Sender);
	void __fastcall btnUsersDeleteClick(TObject *Sender);
	void __fastcall sgUsersDblClick(TObject *Sender);
	void __fastcall sgUsersFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall btnDBCreateClick(TObject *Sender);
	void __fastcall btnDBDeleteClick(TObject *Sender);

private:
	TSettings *Settings;

	bool IsReadOnly;

	bool PerformSave;

	void CreateUsersColumns();

	void SetReadOnly(TComponent *Parent, bool ReadOnly);

	void UpdateForm();
	void UpdateSettings();

	TUser* GetUser(int Index);
	int SetUser(int Index, TUser *User);

	bool IsUserAdmin(int Index);

	TConnection* GetConnection();

	static const int DB_ACTION_CHECK = 100;
	static const int DB_ACTION_CREATE = 101;
	static const int DB_ACTION_DROP = 102;

	void DatabaseAction(int Action);

public:
	__fastcall TfrmOptions(TComponent* Owner);

	static bool Show(TSettings *Settings, bool ReadOnly);

	int AdminCount();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
// ---------------------------------------------------------------------------
#endif