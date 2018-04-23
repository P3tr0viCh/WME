// ---------------------------------------------------------------------------

#ifndef WMETSettingsH
#define WMETSettingsH

#include <System.Classes.hpp>

#include <ObjList.h>

#include "WMETUser.h"
#include "WMETConnectionInfo.h"
#include "WMETVanCatalog.h"
#include "WMETVanType.h"

#define CFG_DIR_NAME "cfg"
#define CFG_EXT ".cfg"

// ---------------------------------------------------------------------------
class TSettings : public TObject {
private:
	String FConfigDir;

	TColor FColorReadOnly;

	TConnectionInfo * FConnection;

	TUserList * FUserList;

	TVanTypeList * FVanTypeList;
	TVanCatalogList * FCargoTypeList;

	String GetConfigDir();
	bool CheckConfigDir();
	String GetConfigFileName(String ConfigName);

	String EncryptPass(String S);
	String DecryptPass(String S);

	void DeleteConfigFile(String ConfigFileName);

	void LoadVanCatalog(String ConfigFileName, String SCount, String SSection,
		TVanCatalogList * VanCatalogList);
	void SaveVanCatalog(String ConfigFileName, String SCount, String SSection,
		TVanCatalogList * VanCatalogList);

	void LoadDatabase(String ConfigFileName);
	void LoadUsers(String ConfigFileName);
	void LoadVanTypes(String ConfigFileName);
	void LoadCargoTypes(String ConfigFileName);

	void SaveDatabase(String ConfigFileName);
	void SaveUsers(String ConfigFileName);
	void SaveVanTypes(String ConfigFileName);
	void SaveCargoTypes(String ConfigFileName);

public:
	__fastcall TSettings();
	__fastcall ~TSettings();

	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TSettings * Source);
	String __fastcall ToString();

	bool Load();
	bool Save();

	__property TColor ColorReadOnly = {read = FColorReadOnly};

	__property TConnectionInfo * Connection = {read = FConnection};
	__property TUserList * UserList = {read = FUserList};

	__property TVanTypeList * VanTypeList = {read = FVanTypeList};
	__property TVanCatalogList * CargoTypeList = {read = FCargoTypeList};
};

// ---------------------------------------------------------------------------
#endif
