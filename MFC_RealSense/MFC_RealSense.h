
// MFC_RealSense.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_RealSenseApp: 
// �йش����ʵ�֣������ MFC_RealSense.cpp
//

class CMFC_RealSenseApp : public CWinApp
{
public:
	CMFC_RealSenseApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMFC_RealSenseApp theApp;