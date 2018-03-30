// ---------------------------------------------------------------------------

#ifndef WMETSettingsH
#define WMETSettingsH

#include <System.Classes.hpp>

#include <ObjList.h>

#include "WMETUser.h"
#include "WMETConnection.h"

#define CFG_DIR_NAME "cfg"
#define CFG_EXT ".cfg"

// ---------------------------------------------------------------------------
class TSettings : public TObject {
private:
	String FConfigDir;

	TConnection *FConnection;

	TObjList<TUser> *FUserList;

	String GetConfigDir();
	bool CheckConfigDir();
	String GetConfigFileName(String ConfigName);

	String EncryptPass(String S);
	String DecryptPass(String S);

public:
	__fastcall TSettings();
	__fastcall ~TSettings();

	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TSettings* Source);
	String __fastcall ToString();

	bool Load();
	bool Save();

	__property TConnection *Connection = {read = FConnection};
	__property TObjList<TUser> *UserList = {read = FUserList};
};

// ---------------------------------------------------------------------------
#endif
