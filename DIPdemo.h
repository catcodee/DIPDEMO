
// DIPdemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once


#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDIPdemoApp:
// �йش����ʵ�֣������ DIPdemo.cpp
//

class CDIPdemoApp : public CWinApp
{
public:
	CDIPdemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDIPdemoApp theApp;