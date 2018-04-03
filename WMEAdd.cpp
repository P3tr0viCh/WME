// ---------------------------------------------------------------------------

#pragma hdrstop

#include <System.SysUtils.hpp>

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
void StringGridSetHeader(TStringGrid *Grid, int Col, String ColName,
	int ColWidth) {
	Grid->Cells[Col][0] = ColName;
	Grid->ColWidths[Col] = ColWidth;
}

// ---------------------------------------------------------------------------
