
// listControl_1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// ClistControl_1App:
// �� Ŭ������ ������ ���ؼ��� listControl_1.cpp�� �����Ͻʽÿ�.
//

class ClistControl_1App : public CWinApp
{
public:
	ClistControl_1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern ClistControl_1App theApp;