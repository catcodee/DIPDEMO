
// DIPdemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DIPdemo.h"
#include "DIPdemoDlg.h"
#include "afxdialogex.h"
#include "ImageMat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDIPdemoDlg �Ի���




CDIPdemoDlg::CDIPdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDIPdemoDlg::IDD, pParent)
	,m_bRun(FALSE)
	,m_hCam(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDIPdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDIPdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON2, &CDIPdemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_OpenCam, &CDIPdemoDlg::OnBnClickedOpencam)
	ON_BN_CLICKED(IDC_StartGrab, &CDIPdemoDlg::OnBnClickedStartgrab)
	ON_BN_CLICKED(IDC_CloseCam, &CDIPdemoDlg::OnBnClickedClosecam)

	
	ON_BN_CLICKED(IDC_DEBUG, &CDIPdemoDlg::OnBnClickedDebug)
END_MESSAGE_MAP()


// CDIPdemoDlg ��Ϣ�������

BOOL CDIPdemoDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	MVSTATUS_CODES r;
	r = MVInitLib();
	if (r != MVST_SUCCESS)
	{
		MessageBox("�������ʼ��ʧ�ܣ�","��ʾ",MB_ICONWARNING);
		return TRUE;
	}

	r = MVUpdateCameraList();
	if (r != MVST_SUCCESS)
	{
		MessageBox("�������Ӽ���������ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
		return TRUE;
	}
	GetDlgItem(IDC_OpenCam)->EnableWindow(true);
	GetDlgItem(IDC_StartGrab)->EnableWindow(false);
	GetDlgItem(IDC_CloseCam)->EnableWindow(false);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDIPdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDIPdemoDlg::OnPaint()
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
HCURSOR CDIPdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDIPdemoDlg::OnBnClickedOpencam()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCams = 0;

	MVGetNumOfCameras(&nCams);

	if( nCams == 0 )
	{
		MessageBox("û���ҵ����,��ȷ�����Ӻ����IP����","��ʾ",MB_ICONWARNING);
		return ;
	}
	MVSTATUS_CODES r = MVOpenCamByIndex(0, &m_hCam);
	if (m_hCam == NULL)
	{
		if (r == MVST_ACCESS_DENIED)
			MessageBox("�޷��������������������������", "��ʾ",MB_ICONWARNING);
		else
			MessageBox("�޷������","��ʾ",MB_ICONWARNING);
		return;
	}
	int w,h;

	MVGetWidth(m_hCam,&w);
	MVGetHeight(m_hCam,&h);
	MVGetPixelFormat(m_hCam,&m_PixelFormat);
	m_image.CreateByPixelFormat(w,h,m_PixelFormat);

	GetDlgItem(IDC_OpenCam)->EnableWindow(false);
	GetDlgItem(IDC_StartGrab)->EnableWindow(true);
	GetDlgItem(IDC_CloseCam)->EnableWindow(false);

}

int __stdcall StreamCB(MV_IMAGE_INFO * pInfo, ULONG_PTR nUserVal)
{
	CDIPdemoDlg *pDlg = (CDIPdemoDlg *)nUserVal;
	return ( pDlg->OnStreamCB(pInfo) );
}
void CDIPdemoDlg::OnBnClickedStartgrab()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TriggerModeEnums enumMode;
	MVGetTriggerMode(m_hCam, &enumMode);
	if (enumMode != TriggerMode_Off)
	{
		MVSetTriggerMode(m_hCam, TriggerMode_Off);
		Sleep(100);
	}
	MVStartGrab(m_hCam,StreamCB,(long)this);
	m_bRun = true;

	GetDlgItem(IDC_OpenCam)->EnableWindow(false);
	GetDlgItem(IDC_StartGrab)->EnableWindow(false);
	GetDlgItem(IDC_CloseCam)->EnableWindow(true);

}

void CDIPdemoDlg::DrawImage()
{
	
	CRect rct;
	GetDlgItem(pic)->GetClientRect(&rct);
	int dstW = rct.Width();
	int dstH = rct.Height();
	CDC *pDC = GetDlgItem(pic)->GetDC();
	{
		pDC->SetStretchBltMode(COLORONCOLOR);
		m_image.Draw(pDC->GetSafeHdc(),0,0,dstW,dstH);
	}
	ReleaseDC(pDC);
}

int CDIPdemoDlg::OnStreamCB( MV_IMAGE_INFO *pInfo)
{
	MVInfo2Image(m_hCam,pInfo,&m_image);
	DrawImage();
	return 0;
}


void CDIPdemoDlg::OnBnClickedClosecam()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MVStopGrab(m_hCam);

	HBITMAP m1;
	BITMAP m2;
	

	m1 = m_image.GetHBitmap();
	ImageMat i_mat(m2);
	int rej = GetObject(m1,sizeof(m2),&m2);

	char str[100];
	memset(str,0,100);
	
	sprintf(str,"%l",m2.bmHeight);
	GetDlgItem(IDC_OUT)->SetWindowText(str);

	MVCloseCam(m_hCam);
	m_bRun = false;
	GetDlgItem(IDC_OpenCam)->EnableWindow(true);
	GetDlgItem(IDC_StartGrab)->EnableWindow(false);
	GetDlgItem(IDC_CloseCam)->EnableWindow(false);

}

void CDIPdemoDlg::OnClose()
{
	if(m_bRun != false)
	{
		MVStopGrab(m_hCam);
	}
	MVTerminateLib();
	CDialog::OnClose();
}


void CDIPdemoDlg::OnBnClickedDebug()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char str[100] = {0};
	char filename[100] = "E:/CPP/test.bmp";
	m_image.Load(filename);
	HBITMAP handles = m_image.GetHBitmap();
	BITMAP bm ;
	GetObject(handles,sizeof(bm),&bm);
	ImageMat mat(bm);

	
	//IMAGEDATA p = mat.GetPixelColor(0,1);
	mat.BmpSave("E:/CPP/output.bmp",0);

	//ImageMat mat1(filename);
	sprintf(str,"%d",bm.bmHeight);
	GetDlgItem(IDC_OUT)->SetWindowText(str);
}
