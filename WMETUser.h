// ---------------------------------------------------------------------------

#ifndef WMETUserH
#define WMETUserH

#include <System.Classes.hpp>

// ---------------------------------------------------------------------------
class TUser : public TObject {
private:
	String FName;
	String FPass;
	String FTabNum;
	String FShiftNum;

	bool FAdmin;

public:
	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TUser* Source);

	__property String Name = {read = FName, write = FName};
	__property String Pass = {read = FPass, write = FPass};
	__property String TabNum = {read = FTabNum, write = FTabNum};
	__property String ShiftNum = {read = FShiftNum, write = FShiftNum};

	__property bool IsAdmin = {read = FAdmin, write = FAdmin};
};

// ---------------------------------------------------------------------------
#endif
