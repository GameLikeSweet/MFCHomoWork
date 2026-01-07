#include "stdafx.h"
#include <afxwin.h>
#include <Windows.h>
#include "CControlCombo.h"
#include "Resource.h"




CControlCombo::CControlCombo(CWnd* pParent)
	: m_pParent(pParent)
{
}


void CControlCombo::DeleteCombo(CComboBox* Combo)
{
	//CComboBox* Combo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CString s;
	int x = Combo->GetCurSel();
	if (x < 0) return;
	Combo->GetLBText(x, s);
	s.Trim();
	if (x == 0) return;
	Combo->DeleteString(x);
	m_SaveMap.erase(s);
}



void CControlCombo::SaveCombo(CComboBox* pCombo)
{
	CString wText;
	pCombo->GetWindowTextW(wText);
	wText.Trim();

	if (wText == _T("")) return;
	int nTarget = CheckComboList(pCombo, wText);

	if (nTarget == -1)
	{
		nTarget = pCombo->AddString(wText);
	}
	else
	{
		pCombo->SetCurSel(nTarget);
	}

	m_SaveMap[wText] = GetSaveData();
}

int CControlCombo::CheckComboList(CComboBox* pCombo , CString s)
{
	int nTry = pCombo->GetCount();
	int selTarget = -1;
	CString t;
	for (int i = 0; i < nTry; i++)
	{
		pCombo->GetLBText(i, t);
		if (t == s)
		{
			selTarget = i;
			break;
		}
	}
	return selTarget;
}

SSaveData CControlCombo::GetSaveData()
{
	SSaveData _save;
	_save.c1 = m_pParent->IsDlgButtonChecked(IDC_CHECK1);
	_save.c2 = m_pParent->IsDlgButtonChecked(IDC_CHECK2);
	_save.c3 = m_pParent->IsDlgButtonChecked(IDC_CHECK3);
	_save.radio = m_pParent->GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3);
	return _save;
}

void CControlCombo::ApplyCombo(SSaveData s)
{
	CWnd* target1 = m_pParent->GetDlgItem(IDC_CHECK1);
	CWnd* target2 = m_pParent->GetDlgItem(IDC_CHECK2);
	CWnd* target3 = m_pParent->GetDlgItem(IDC_CHECK3);

	m_pParent->CheckDlgButton(IDC_CHECK1, s.c1);
	m_pParent->CheckDlgButton(IDC_CHECK2, s.c2);
	m_pParent->CheckDlgButton(IDC_CHECK3, s.c3);

	if (s.radio == 0)
	{
		// 라디오 전부 해제
		if (target1) m_pParent->SendMessage(WM_APPLYRADIO, (WPARAM)IDC_RADIO1, (LPARAM)target1->GetSafeHwnd());
		if (target2) m_pParent->SendMessage(WM_APPLYRADIO, (WPARAM)IDC_RADIO1, (LPARAM)target2->GetSafeHwnd());
		if (target3) m_pParent->SendMessage(WM_APPLYRADIO, (WPARAM)IDC_RADIO1, (LPARAM)target3->GetSafeHwnd());

		m_pParent->CheckDlgButton(IDC_RADIO1, BST_UNCHECKED);
		m_pParent->CheckDlgButton(IDC_RADIO2, BST_UNCHECKED);
		m_pParent->CheckDlgButton(IDC_RADIO3, BST_UNCHECKED);
	}
	else
	{
		m_pParent->CheckRadioButton(IDC_RADIO1, IDC_RADIO3, s.radio);

		if (target1) m_pParent->SendMessage(WM_APPLYRADIO, (WPARAM)s.radio, (LPARAM)target1->GetSafeHwnd());
		if (target2) m_pParent->SendMessage(WM_APPLYRADIO, (WPARAM)s.radio, (LPARAM)target2->GetSafeHwnd());
		if (target3) m_pParent->SendMessage(WM_APPLYRADIO, (WPARAM)s.radio, (LPARAM)target3->GetSafeHwnd());
	}
}