
// listControl_1Dlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// 학생 정보 구조체 
// name = 학생 이름, id = 국어 점수, interest = 영어 점수, comment = 수학 점수 
typedef struct Client
{
	char name[20];
	char trading[20];
	char id[20];
	char interest[20];
	char comment[50];
}INFO;

// ClistControl_1Dlg 대화 상자
class ClistControl_1Dlg : public CDialogEx
{
// 생성입니다.
public:
	ClistControl_1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LISTCONTROL_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//버튼
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDelete();	
	//클릭해서 에디트 컨트롤에 정보 담기
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	//파일 입출력
	afx_msg void OnBnClickedButtonFileIn();
	afx_msg void OnBnClickedButtonFileOut();
	afx_msg void OnBnClickedButtonBnFileIn();
	afx_msg void OnBnClickedButtonBnFileOut();
	//가상 리스트
	afx_msg void OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult);

	void addClient();
	void deleteClient(int arg_i);
	void addFile();
	void deleteAll();
	
	//리스트 컨트롤
	CListCtrl m_List;
	//이름 및 변수
	CString m_strName;
	CString m_strInterest;
	CString m_strComment;
	CString m_strId;
	CString m_strTrading;

	//m_nTotal = 입력된 총 학생 수
	int m_nTotal;
	
	//학생 정보 멤버 변수
	INFO* m_stClient;
	//피드백: INFO말고 좀 더 확실한 이름으로
	CButton m_chkBybit;
	CButton m_chkBitget;
	CButton m_chkYoutube;
	int m_rdBybit;
//	int m_rdBitget;
//	int m_rdYoutube;
};
