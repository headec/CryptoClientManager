
// listControl_1Dlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// �л� ���� ����ü 
// name = �л� �̸�, id = ���� ����, interest = ���� ����, comment = ���� ���� 
typedef struct Client
{
	char name[20];
	char trading[20];
	char id[20];
	char interest[20];
	char comment[50];
}INFO;

// ClistControl_1Dlg ��ȭ ����
class ClistControl_1Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	ClistControl_1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LISTCONTROL_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//��ư
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDelete();	
	//Ŭ���ؼ� ����Ʈ ��Ʈ�ѿ� ���� ���
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//���� �����
	afx_msg void OnBnClickedButtonFileIn();
	afx_msg void OnBnClickedButtonFileOut();
	afx_msg void OnBnClickedButtonBnFileIn();
	afx_msg void OnBnClickedButtonBnFileOut();
	//���� ����Ʈ
	afx_msg void OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult);

	void addClient();
	void deleteClient(int arg_i);
	void addFile();
	void deleteAll();
	
	//����Ʈ ��Ʈ��
	CListCtrl m_List;
	//�̸� �� ����
	CString m_strName;
	CString m_strInterest;
	CString m_strComment;
	CString m_strId;
	CString m_strTrading;

	//m_nTotal = �Էµ� �� �л� ��
	int m_nTotal;
	
	//�л� ���� ��� ����
	INFO* m_stClient;
	//�ǵ��: INFO���� �� �� Ȯ���� �̸�����
	CButton m_chkBybit;
	CButton m_chkBitget;
	CButton m_chkYoutube;
	int m_rdBybit;
//	int m_rdBitget;
//	int m_rdYoutube;
};
