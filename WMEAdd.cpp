// ---------------------------------------------------------------------------

#pragma hdrstop

#include <System.SysUtils.hpp>
#include <System.DateUtils.hpp>

#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMEAdd.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
bool StringGridIsEmpty(TStringGrid *Grid) {
	return IsEmpty(Grid->Cells[0][1]);
}

// ---------------------------------------------------------------------------
void StringGridClear(TStringGrid *Grid) {
	for (int i = 1; i < Grid->RowCount; i++) {
		Grid->Rows[i]->Clear();
	}
	Grid->RowCount = 2;
}

// ---------------------------------------------------------------------------
void StringGridSelectCell(TStringGrid *Grid, int ACol, int ARow) {
	Grid->Col = ACol;
	Grid->Row = ARow;
}

// ---------------------------------------------------------------------------
void StringGridUpdateOrderNum(TStringGrid *Grid) {
	for (int ARow = 1, Count = Grid->RowCount; ARow < Count; ARow++) {
		Grid->Cells[0][ARow] = IntToStr(ARow);
	}
}

// ---------------------------------------------------------------------------
void StringGridDeleteRow(TStringGrid *Grid, int ARow, int AColCount) {
	int Count = Grid->RowCount;

	if (Count - Grid->FixedRows <= 1) {
		Grid->Rows[ARow]->Clear();
		return;
	}

	if (AColCount < 0) {
		for (ARow; ARow < Count; ARow++) {
			Grid->Rows[ARow] = Grid->Rows[ARow + 1];
		}
	}
	else {
		for (ARow; ARow < Count; ARow++) {
			for (int ACol = 0; ACol < AColCount; ACol++) {
				Grid->Cells[ACol][ARow] = Grid->Cells[ACol][ARow + 1];
			}
		}
	}

	Grid->Rows[Count]->Clear();

	Grid->RowCount--;
}

// ---------------------------------------------------------------------------
void StringGridSetHeader(TStringGrid *Grid, int ACol, String ColName,
	int ColWidth) {
	Grid->Cells[ACol][0] = ColName;
	Grid->ColWidths[ACol] = ColWidth;
}

// ---------------------------------------------------------------------------
void StringGridSetHeader(TStringGrid *Grid, int ACol, NativeUInt ColNameIdent,
	int ColWidth) {
	StringGridSetHeader(Grid, ACol, LoadStr(ColNameIdent), ColWidth);
}

// ---------------------------------------------------------------------------
void StringGridDrawCell(TStringGrid *Grid, int ACol, int ARow, TRect Rect,
	TGridDrawState State, TIntegerSet ColsReadOnly, TIntegerSet ColsLeftAlign,
	TIntegerSet ColsCustomColor, TColor ReadOnlyColor, TColor CustomColor,
	bool DrawFocusedOnInactive) {
	Grid->Canvas->Font = Grid->Font;

	if (State.Contains(gdFixed)) {
		Grid->Canvas->Brush->Color = Grid->FixedColor;
	}
	else {
		if (State.Contains(gdSelected)) {
			if (State.Contains(gdFocused)) {
				Grid->Canvas->Brush->Color = clMedGray;
			}
			else {
				Grid->Canvas->Brush->Color = DrawFocusedOnInactive ? clSilver :
					clWindow;
			}
		}
		else {
			if (ColsCustomColor.Contains(ACol)) {
				Grid->Canvas->Brush->Color = CustomColor;
			}
			else {
				if (ColsReadOnly.Contains(ACol)) {
					Grid->Canvas->Brush->Color = ReadOnlyColor;
				}
				else {
					Grid->Canvas->Brush->Color = Grid->Color;
				}
			}
		}
	}

	Grid->Canvas->FillRect(Rect);

	if (State.Contains(gdFixed)) {
		InflateRect(Rect, -2, 0);
		OffsetRect(Rect, -1, 0);

		DrawText(Grid->Canvas->Handle, Grid->Cells[ACol][ARow].c_str(),
			Grid->Cells[ACol][ARow].Length(), (RECT*)&Rect,
			DT_CENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	}
	else {
		InflateRect(Rect, -2, 0);
		OffsetRect(Rect, 0, 2);

		if (!State.Contains(gdSelected)) {
			if (ColsCustomColor.Contains(ACol)) {
				// Grid->Canvas->Font->Color =
				// GetColorByBack(Grid->Canvas->Brush->Color);
			}
		}

		if (ColsLeftAlign.Contains(ACol)) {
			DrawText(Grid->Canvas->Handle, Grid->Cells[ACol][ARow].c_str(),
				Grid->Cells[ACol][ARow].Length(), (RECT*)&Rect,
				DT_SINGLELINE | DT_END_ELLIPSIS);
		}
		else {
			DrawText(Grid->Canvas->Handle, Grid->Cells[ACol][ARow].c_str(),
				Grid->Cells[ACol][ARow].Length(), (RECT*)&Rect,
				DT_SINGLELINE | DT_END_ELLIPSIS | DT_CENTER);
		}
	}
}

// ---------------------------------------------------------------------------
void StringGridMouseToCell(TStringGrid *Grid, int &ACol, int &ARow) {
	TPoint P = Mouse->CursorPos;
	P = Grid->ScreenToClient(P);

	Grid->MouseToCell(P.X, P.Y, ACol, ARow);
}

// ---------------------------------------------------------------------------
String LoadSQL(NativeUInt Ident) {
	String Result;

	TStrings *Strings = new TStringList;

	TResourceStream *Stream = new TResourceStream((int)HInstance,
		LoadStr(Ident), RT_RCDATA);

	try {
		Strings->LoadFromStream(Stream);

		Result = Strings->Text;
	}
	__finally {
		Stream->Free();
		Strings->Free();
	}

	return Result;
}

// ---------------------------------------------------------------------------
String DateTimeToSQLStr(TDateTime ADateTime) {
	return FormatDateTime("yyyyMMddhhnnss", ADateTime);
}

// ---------------------------------------------------------------------------
int DateTimeToWTime(TDateTime ADateTime) {
	// TODO: Magic Number
	return int(DateTimeToUnix(IncHour(ADateTime, -3)));
}

// ---------------------------------------------------------------------------
