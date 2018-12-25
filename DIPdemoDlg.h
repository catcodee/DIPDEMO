
// DIPdemoDlg.h : ͷ�ļ�
//

#pragma once

#include<MVGigE.h>
#include<MVImage.h>
#include<iostream>
#include<string.h>
#include<stdio.h>

// CDIPdemoDlg �Ի���
class CDIPdemoDlg : public CDialogEx
{
// ����
public:
	//��������������
	HANDLE m_hCam;
	//����ͼ�������
	MVImage m_image;
	//�������ظ�ʽ����
	MV_PixelFormatEnums m_PixelFormat;
	//�ɼ���ʶ
	bool m_bRun;
	//ͨ���ص�������ȡͼ��������Ϣ
	int OnStreamCB( MV_IMAGE_INFO * pInfo);
	//��ͼ
	void DrawImage();

	CDIPdemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DIPDEMO_DIALOG };
	void OnClose();
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

