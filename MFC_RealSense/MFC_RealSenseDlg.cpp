
// MFC_RealSenseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_RealSense.h"
#include "MFC_RealSenseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_RealSenseDlg �Ի���



CMFC_RealSenseDlg::CMFC_RealSenseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_REALSENSE_DIALOG, pParent)
	, mBarrierHeightThresh(30)
	, mSideThresh(600)
	, mDistanceThresh(2000)
	, mDownSampleType(0)
	, mDownSampleRate(4)
	, isShowCube(FALSE)
	, isShowPlane(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
}

void CMFC_RealSenseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, mBtnStart);
	DDX_Text(pDX, IDC_EDIT1, mBarrierHeightThresh);
	DDX_Text(pDX, IDC_EDIT2, mSideThresh);
	DDX_Text(pDX, IDC_EDIT3, mDistanceThresh);
	DDX_Radio(pDX, IDC_RADIO1, mDownSampleType);
	DDX_Check(pDX, IDC_CHECKBOX, isShowCube);
	DDX_Check(pDX, IDC_CHECKBOX2, isShowPlane);
	DDX_Control(pDX, IDCANCEL, IsSaveheight);
}

BEGIN_MESSAGE_MAP(CMFC_RealSenseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC_RealSenseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFC_RealSenseDlg::OnBnClickedCancel)
	
	ON_BN_CLICKED(IDC_RADIO1, &CMFC_RealSenseDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFC_RealSenseDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CMFC_RealSenseDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_CHECKBOX, &CMFC_RealSenseDlg::OnBnClickedCheckbox)
	ON_BN_CLICKED(IDC_CHECKBOX2, &CMFC_RealSenseDlg::OnBnClickedCheckbox2)
END_MESSAGE_MAP()


// CMFC_RealSenseDlg ��Ϣ�������

BOOL CMFC_RealSenseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFC_RealSenseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_RealSenseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFC_RealSenseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_RealSenseDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	algo.mDistanceThresh = mDistanceThresh / 1000.0f;
	algo.mSideThresh = mSideThresh / 1000.0f;
	algo.mBarrierHeightThresh = mBarrierHeightThresh / 1000.0f;
	algo.mDownSampleRate = mDownSampleRate;
	algo.showBox = isShowCube;
	algo.showPlane = isShowPlane;
	if (!algoCtrl)
	{	
		algoCtrl = !algoCtrl;
		mBtnStart.SetWindowText(_T("ֹͣ���"));
		AfxBeginThread((AFX_THREADPROC)threadProc, (LPVOID)this);  //�����߳�
	}
	else
	{		
		algoCtrl = !algoCtrl;
		mBtnStart.SetWindowText(_T("��ʼ���"));
	}	
}

void threadProc(LPVOID IpParamater)
{
	CMFC_RealSenseDlg *p = (CMFC_RealSenseDlg*)IpParamater;
	p->funcProc();
}


void CMFC_RealSenseDlg::funcProc()
{
	algo.startDetectFromFile();
	mBtnStart.SetWindowText(_T("��ʼ���"));
}


void CMFC_RealSenseDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (algoCtrl)
	{
		algoCtrl = !algoCtrl;
		mBtnStart.SetWindowText(_T("��ʼ���"));
		Sleep(500);
	}	
	CDialogEx::OnCancel();
}

void CMFC_RealSenseDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	switch (mDownSampleType)
	{
	case 0:
		mDownSampleRate = 4;
		break;
	case 1:
		mDownSampleRate = 2;
		break;
	case 2:
		mDownSampleRate = 1;
		break;
	default:
		break;
	}
}


void CMFC_RealSenseDlg::OnBnClickedCheckbox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
}


void CMFC_RealSenseDlg::OnBnClickedCheckbox2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
}
