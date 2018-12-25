
// DIPdemoDlg.h : 头文件
//

#pragma once

#include<MVGigE.h>
#include<MVImage.h>
#include<iostream>
#include<string.h>
#include<stdio.h>

// CDIPdemoDlg 对话框
class CDIPdemoDlg : public CDialogEx
{
// 构造
public:
	//定义相机句柄对象
	HANDLE m_hCam;
	//定义图像处理对象
	MVImage m_image;
	//定义像素格式对象
	MV_PixelFormatEnums m_PixelFormat;
	//采集标识
	bool m_bRun;
	//通过回调函数获取图像数据信息
	int OnStreamCB( MV_IMAGE_INFO * pInfo);
	//画图
	void DrawImage();

	CDIPdemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIPDEMO_DIALOG };
	void OnClose();
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOpencam();
	afx_msg void OnBnClickedStartgrab();
	afx_msg void OnBnClickedClosecam();
	afx_msg void OnBnClickedSave();
	afx_msg void OnStnClickedOut();
	afx_msg void OnBnClickedDebug();
};

