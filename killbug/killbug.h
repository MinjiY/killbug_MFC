
// killbug.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CkillbugApp:
// �� Ŭ������ ������ ���ؼ��� killbug.cpp�� �����Ͻʽÿ�.
//

class CkillbugApp : public CWinApp
{
public:
	CkillbugApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CkillbugApp theApp;