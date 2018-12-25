
// DIPdemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPdemo.h"
#include "DIPdemoDlg.h"
#include "afxdialogex.h"
#include "ImageMat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDIPdemoDlg 对话框




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


// CDIPdemoDlg 消息处理程序

BOOL CDIPdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	MVSTATUS_CODES r;
	r = MVInitLib();
	if (r != MVST_SUCCESS)
	{
		MessageBox("函数库初始化失败！","提示",MB_ICONWARNING);
		return TRUE;
	}

	r = MVUpdateCameraList();
	if (r != MVST_SUCCESS)
	{
		MessageBox("查找连接计算机的相机失败！", "提示", MB_ICONWARNING);
		return TRUE;
	}
	GetDlgItem(IDC_OpenCam)->EnableWindow(true);
	GetDlgItem(IDC_StartGrab)->EnableWindow(false);
	GetDlgItem(IDC_CloseCam)->EnableWindow(false);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDIPdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDIPdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDIPdemoDlg::OnBnClickedOpencam()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCams = 0;

	MVGetNumOfCameras(&nCams);

	if( nCams == 0 )
	{
		MessageBox("没有找到相机,请确认连接和相机IP设置","提示",MB_ICONWARNING);
		return ;
	}
	MVSTATUS_CODES r = MVOpenCamByIndex(0, &m_hCam);
	if (m_hCam == NULL)
	{
		if (r == MVST_ACCESS_DENIED)
			MessageBox("无法打开相机，可能正被别的软件控制", "提示",MB_ICONWARNING);
		else
			MessageBox("无法打开相机","提示",MB_ICONWARNING);
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
