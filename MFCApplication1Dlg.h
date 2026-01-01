
// MFCApplication1Dlg.h: 헤더 파일
//

#pragma once
#include"CSubDlg.h"

// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CListCtrl m_LogList;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();

	void AddLog(const CString& who, const CString& value);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnRadioClicked(UINT nID);
	afx_msg void OnCheckClicked(UINT nID);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CSubDlg* m_CTest;
	afx_msg void OnBnClickedCancel();
	afx_msg LRESULT OnSubDlgClosed(WPARAM, LPARAM);

};
