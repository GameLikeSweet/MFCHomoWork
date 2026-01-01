
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDestroy();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_MESSAGE(WM_SUBDLG_CLOSED, &CMFCApplication1Dlg::OnSubDlgClosed)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO3, &CMFCApplication1Dlg::OnRadioClicked)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECK1, IDC_CHECK3, &CMFCApplication1Dlg::OnCheckClicked)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCApplication1Dlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_LogList.SubclassDlgItem(IDC_LIST_LOG, this);

	// 리포트 형태 + 한 줄 선택 등

	CComboBox* m_cBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	m_cBox->AddString(_T("123"));

	m_LogList.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);

	m_LogList.SetExtendedStyle(
		m_LogList.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
	);

	m_LogList.InsertColumn(0, _T("Time"), LVCFMT_LEFT, 120);
	m_LogList.InsertColumn(1, _T("Control"), LVCFMT_LEFT, 120);
	m_LogList.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 300);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_CTest && ::IsWindow(m_CTest->GetSafeHwnd()))
	{
		m_CTest->ShowWindow(SW_SHOW);
		m_CTest->SetForegroundWindow();
		return;
	}

	// 기존 객체가 남아있다면 정리(안전하게)
	if (m_CTest)
	{
		if (::IsWindow(m_CTest->GetSafeHwnd())) m_CTest->DestroyWindow();
			

		delete m_CTest;
		m_CTest = nullptr;
	}

	m_CTest = new CSubDlg();

	// Create 성공 여부 체크 (실패하면 ShowWindow 해도 안 보임)
	if (!m_CTest->Create(IDD_CSubDlg, this))
	{
		delete m_CTest;
		m_CTest = nullptr;
		return;
	}

	m_CTest->ShowWindow(SW_SHOW);

}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSubDlg dlg(this);
	dlg.DoModal();
}

LRESULT CMFCApplication1Dlg::OnSubDlgClosed(WPARAM, LPARAM)
{
	// 창이 이미 내려갔을 수 있으니 포인터만 정리
	// (객체 delete는 OK에서 재생성할 때 하므로 여기서는 null 처리만 하는 방식도 가능)
	m_CTest = nullptr;
	return 0;
}


void CMFCApplication1Dlg::AddLog(const CString& who, const CString& value)
{
	CTime t = CTime::GetCurrentTime();
	CString ts = t.Format(_T("%H:%M:%S"));

	int row = m_LogList.GetItemCount();
	m_LogList.InsertItem(row, ts);
	m_LogList.SetItemText(row, 1, who);
	m_LogList.SetItemText(row, 2, value);

	// 마지막 줄 보이게
	m_LogList.EnsureVisible(row, FALSE);

	// 디버그 출력도 원하면
	// CString msg; msg.Format(_T("[%s] %s : %s\n"), ts, who, value);
	// OutputDebugString(msg);
}

void CMFCApplication1Dlg::OnRadioClicked(UINT nID)
{
	int checked = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3);

	CString msg;
	msg.Format(_T("Checked ID = %d (clicked=%u)"), checked, nID);

	AddLog(_T("RadioGroup"), msg);
}

void CMFCApplication1Dlg::OnCheckClicked(UINT nID)
{
	CButton* pBtn = (CButton*)GetDlgItem(nID);
	if (!pBtn) return;

	BOOL checked = (pBtn->GetCheck() == BST_CHECKED);

	CString who;
	who.Format(_T("Check(ID=%u)"), nID);

	AddLog(who, checked ? _T("ON") : _T("OFF"));
}

void CMFCApplication1Dlg::OnCbnSelchangeCombo1()
{
	CComboBox* p = (CComboBox*)GetDlgItem(IDC_COMBO1);
	if (!p) return;

	int sel = p->GetCurSel();

	CString text;
	if (sel >= 0)
		p->GetLBText(sel, text);
	else
		text = _T("(no selection)");

	AddLog(_T("Combo1"), text);
}
