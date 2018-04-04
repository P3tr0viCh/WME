// ---------------------------------------------------------------------------

#ifndef WMETVanH
#define WMETVanH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

// ---------------------------------------------------------------------------
class TVan : public TObject {
private:
	TDateTime FDateTime;

public:
	__fastcall TVan();

	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TVan* Source);
	String __fastcall ToString();

	void SetDefault();

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};
};

// ---------------------------------------------------------------------------
#endif
