#pragma once

#include "Clip.h"

class CClipboardSaveRestore
{
public:
	CClipboardSaveRestore(void);
	~CClipboardSaveRestore(void);

	bool Save();
	bool Restore();
	void Clear()	{ m_Clipboard.RemoveAll(); }
	bool RestoreTextOnly();

	CClipFormats m_Clipboard;
};
