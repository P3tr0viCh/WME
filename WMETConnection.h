// ---------------------------------------------------------------------------

#ifndef WMETConnectionH
#define WMETConnectionH

#include <System.Classes.hpp>

// ---------------------------------------------------------------------------
class TConnection : public TObject {
private:
	String FHost;
	String FPort;

	String FDatabase;

	String FUser;
	String FPassword;

public:
	__fastcall TConnection();

	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TConnection* Source);
	String __fastcall ToString();

	void SetDefault();

	String GetConnectionString(bool WithDB = true);

	__property String Host = {read = FHost, write = FHost};
	__property String Port = {read = FPort, write = FPort};

	__property String Database = {read = FDatabase, write = FDatabase};

	__property String User = {read = FUser, write = FUser};
	__property String Password = {read = FPassword, write = FPassword};
};

// ---------------------------------------------------------------------------
#endif
