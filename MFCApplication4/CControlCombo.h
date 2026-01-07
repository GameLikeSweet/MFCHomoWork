#pragma once
#include <afxwin.h>
#include <map>
#include <functional>

#define WM_APPLYRADIO (WM_APP + 101)


struct SSaveData {
	bool c1 = false;
	bool c2 = false;
	bool c3 = false;
	int radio = 0;
};

class CControlCombo
{
public:

private:
	CWnd* m_pParent;
public:
	CControlCombo(CWnd* pParent = nullptr);

	void SetParent(CWnd* pParent) { m_pParent = pParent; }
	std::map<CString, SSaveData> m_SaveMap;
	void DeleteCombo(CComboBox* pCombo);
	void SaveCombo(CComboBox* pCombo);
	int CheckComboList(CComboBox* pCombo, CString s);
	SSaveData GetSaveData();
	void ApplyCombo(SSaveData s);
};