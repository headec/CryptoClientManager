
// listControl_1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "listControl_1.h"
#include "listControl_1Dlg.h"
#include "afxdialogex.h"

#include <fstream>
#include <locale.h>
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4996)

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
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


// ClistControl_1Dlg 대화 상자


ClistControl_1Dlg::ClistControl_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClistControl_1Dlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strInterest(_T(""))
	, m_strComment(_T(""))
	, m_strId(_T(""))
	, m_nTotal(0)
	, m_stClient(nullptr)
	, m_rdBybit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);


	struct Client2
	{
		CString str;
		int a;
		int b;
		int c;
	};
	//구조체 string과 같은 클래스에 대하여
	/*Client2 k;
	k.str = _T("asdfasdfkljasdfdojisafdojisdfajioosfdoij");

	std::vector<BYTE> vec;

	_bstr_t tmp(_bstr_t(k.str));
	char* p =tmp;
	int len = strlen(p);

	auto nTotal = sizeof(int) * 4 + sizeof(char) * len;
	vec.insert(vec.end(), nTotal, 0);

	int idx = 0;
	memcpy(&vec[idx], &len, sizeof(int));
	idx += sizeof(int);

	memcpy(&vec[idx], p, len);
	idx += len;

	memcpy(&vec[idx], &k.a, sizeof(int) * 3);


	auto size1 = sizeof(k);
	auto size2 = sizeof(INFO);

	*/

}

void ClistControl_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_INTEREST, m_strInterest);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_strComment);
	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
	DDX_Radio(pDX, IDC_RADIO1, m_rdBybit);
}

BEGIN_MESSAGE_MAP(ClistControl_1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_ADD, &ClistControl_1Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &ClistControl_1Dlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &ClistControl_1Dlg::OnBnClickedButtonDelete)

	ON_NOTIFY(NM_CLICK, IDC_LIST1, &ClistControl_1Dlg::OnNMClickList1)

	ON_BN_CLICKED(IDC_BUTTON_FILE_IN, &ClistControl_1Dlg::OnBnClickedButtonFileIn)
	ON_BN_CLICKED(IDC_BUTTON_FILE_OUT, &ClistControl_1Dlg::OnBnClickedButtonFileOut)
	ON_BN_CLICKED(IDC_BUTTON_BN_FILE_IN, &ClistControl_1Dlg::OnBnClickedButtonBnFileIn)
	ON_BN_CLICKED(IDC_BUTTON_BN_FILE_OUT, &ClistControl_1Dlg::OnBnClickedButtonBnFileOut)

	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, &ClistControl_1Dlg::OnLvnGetdispinfoList1)
END_MESSAGE_MAP()


// ClistControl_1Dlg 메시지 처리기

BOOL ClistControl_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 리스트 컨트롤의 크기를 얻어온다.
	CRect rect;
	m_List.GetClientRect(&rect);

	//리스트 컨트롤 컬럼 추가
	m_List.InsertColumn(0, _T("이름"), LVCFMT_LEFT, rect.Width()/6);
	m_List.InsertColumn(1, _T("거래소"), LVCFMT_LEFT, rect.Width()/6);
	m_List.InsertColumn(2, _T("ID"), LVCFMT_LEFT, rect.Width()/6);
	m_List.InsertColumn(3, _T("수수료"), LVCFMT_LEFT, rect.Width()/6);
	m_List.InsertColumn(4, _T("코멘트"), LVCFMT_LEFT, rect.Width()/6*2+2);

	//Row 전체 하이라이트 및 커서 모양 바꾸기	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void ClistControl_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void ClistControl_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR ClistControl_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*** 학생 정보 추가 함수
void ClistControl_1Dlg::addClient()
{	
	//학생 정보가 빈 값이라면
	if(!(m_stClient))
	{
		m_stClient = new INFO[m_nTotal+1];
	}
	//빈 값이 아니라면 학생 정보 추가
	else 
	{	
		//학생수 증가에 따른 예비로 담아둘 공간
		INFO* l_stTempA = new INFO[m_nTotal+1];

		//복사
		for(int i = 0 ; i<m_nTotal; i++)
		{
			//이름 및 점수
			strcpy(l_stTempA[i].name, m_stClient[i].name);
			strcpy(l_stTempA[i].id, m_stClient[i].id);
			strcpy(l_stTempA[i].interest, m_stClient[i].interest);
			strcpy(l_stTempA[i].comment, m_stClient[i].comment);
			strcpy(l_stTempA[i].trading, m_stClient[i].trading);
		}				
		//안쓰는 메모리 닫은 후 복사
		delete[] m_stClient;
		m_stClient = l_stTempA;
	}
	//위의 코드가 정상 작동된 후 학생 수 추가
	m_nTotal+=1;

	UpdateData(TRUE);

	int l_nItemNum = m_List.GetItemCount();
	//int l_nAvg = 0;
	//int l_nTotal = 0;
	CString l_strAvg = _T("");
	CString l_strTotal = _T("");

	//마지막 값 입력 받기
	strcpy(m_stClient[m_nTotal-1].name , (char*)_bstr_t(m_strName));
	strcpy(m_stClient[m_nTotal-1].id , (char*)_bstr_t(m_strId));
	strcpy(m_stClient[m_nTotal-1].interest , (char*)_bstr_t(m_strInterest));
	strcpy(m_stClient[m_nTotal-1].comment , (char*)_bstr_t(m_strComment));
	strcpy(m_stClient[m_nTotal-1].trading , (char*)_bstr_t(m_strTrading));	
	
	switch(m_rdBybit)
	{
		case 0:
			strcpy(m_stClient[m_nTotal-1].trading , (char*)_bstr_t(_T("Bybit")));
			break;
		case 1:
			strcpy(m_stClient[m_nTotal-1].trading , (char*)_bstr_t(_T("Bitget")));
			break;
		case 2:
			strcpy(m_stClient[m_nTotal-1].trading , (char*)_bstr_t(_T("YouTube")));
			break;
		default:
			break;
	}
	//합계 , 평균
	//l_nTotal = m_stClient[m_nTotal-1].id + m_stClient[m_nTotal-1].interest + m_stClient[m_nTotal-1].comment;
	//l_nAvg = l_nTotal/3;
	//l_strAvg.Format(_T("%d"),l_nAvg);
	//l_strTotal.Format(_T("%d"), l_nTotal);

	//에디트 컨트롤에 입력한 값을 리스트 컨트롤에 추가하였다면
	//에디트 컨트롤을 초기화 합니다.
	m_strName = _T("");
	m_strId = _T("");
	m_strInterest = _T("");
	m_strComment = _T("");
	m_strTrading = _T("");

	UpdateData(FALSE);
}

//*** 학생 정보 삭제 함수
void ClistControl_1Dlg::deleteClient(int arg_i)
{
	//삭제해야 하는 곳부터를 위한 수학적 논리를 위한 변수
	int l_n = 0;
	//학생수 증가에 따른 예비로 담아둘 공간
	INFO* l_stTempD = new INFO[m_nTotal-1];

	//복사
	for(int j = 0;j < m_nTotal; j++)
	{	
		//복사도중 해당 인덱스가 삭제해야 하는 곳에 다다르면 
		if(arg_i==j) 
		{
			l_n = 1;
			continue;
		}

		//논리에 따라 복사 시작. 예)array[i] = array[i+2]
		strcpy(l_stTempD[j - l_n].name , m_stClient[j].name);
		strcpy(l_stTempD[j - l_n].id , m_stClient[j].id);
		strcpy(l_stTempD[j - l_n].interest , m_stClient[j].interest);
		strcpy(l_stTempD[j - l_n].comment , m_stClient[j].comment);
		strcpy(l_stTempD[j - l_n].trading , m_stClient[j].trading);
	}

	//삭제 및 복사 완료
	delete[] m_stClient;
	m_stClient = l_stTempD;

	//리스트 컨트롤상에서도 삭제
	//m_List.DeleteItem(arg_i);

	UpdateData(TRUE);

	//에디트 컨트롤에 입력한 값을 리스트 컨트롤에 추가하였다면
	//에디트 컨트롤을 초기화 합니다.
	m_strName = _T("");
	m_strId = _T("");
	m_strInterest = _T("");
	m_strComment = _T("");
	m_strTrading = _T("");

	UpdateData(FALSE);

	//위의 코드가 정상 작동된 후 학생 수 감소
	m_nTotal -= 1;
}

//*** 모든 정보 삭제 함수
void ClistControl_1Dlg::deleteAll()
{
	if(m_nTotal>0)
	{
		if(m_stClient != NULL)
		{		
			delete[] m_stClient;	
			m_stClient = nullptr;

			m_nTotal = 0;
		}
	}
}

//*** 파일용 학생 정보 추가 함수
void ClistControl_1Dlg::addFile()
{
	//학생 정보가 빈 값이라면
	if(!(m_stClient))
	{
		m_stClient = new INFO[m_nTotal+1];
	}
	//빈 값이 아니라면 학생 정보 추가
	else 
	{	
		//학생수 증가에 따른 예비로 담아둘 공간
		INFO* l_stTempA = new INFO[m_nTotal+1];

		//복사
		for(int i = 0 ; i<m_nTotal; i++)
		{
			//이름 및 점수
			memcpy(l_stTempA, m_stClient, sizeof(INFO) * m_nTotal);
		}				
		//안쓰는 메모리 닫은 후 복사
		delete[] m_stClient;
		m_stClient = l_stTempA;
	}
	//위의 코드가 정상 작동된 후 학생 수 추가
	m_nTotal+=1;
}



//*** 리스트 컨트롤 추가 버튼 기능
void ClistControl_1Dlg::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);

	//입력 값이 빈 값이라면
	if(m_strName.IsEmpty())
	{
		MessageBox(TEXT("학생 이름을 기입해주십시오"));
	}
	//입력 값이 존재한다면
	else
	{	
		addClient();
	}

	UpdateData(FALSE);
	m_List.SetItemCountEx(m_nTotal,LVSICF_NOSCROLL);
}

//*** 리스트 컨트롤 수정 버튼 기능
void ClistControl_1Dlg::OnBnClickedButtonEdit()
{	
	//입력 값이 빈 값이라면
	if(m_nTotal < 1)
	{
		MessageBox(TEXT("학생 정보를 추가해주십시오"));
	}
	else
	{
		//리스트 컨트롤의 현재 항목 수를 얻어옵니다.
		int l_nCount = m_List.GetItemCount(); 

		UpdateData(TRUE);

		//모든 항목을 조사하여
		for(int i =  0; i < l_nCount; i++)   
		{
			//클릭된 항목이 있다면, 클릭된 항목 인덱스 = i
			if(m_List.GetItemState(i, LVIS_SELECTED) != 0)
			{	
				//입력 값이 빈 값이라면
				if(m_strName.IsEmpty())
				{
					MessageBox(TEXT("학생 정보 기입해주십시오"));
				}
				else
				{
					//int l_nAvg = 0;
					//int l_nTotal = 0;
					//CString l_strAvg = _T("");
					//CString l_strTotal = _T("");

					//입력 값 받기
					strcpy(m_stClient[i].name , (char*)_bstr_t(m_strName));
					strcpy(m_stClient[i].id , (char*)_bstr_t(m_strId));
					strcpy(m_stClient[i].interest , (char*)_bstr_t(m_strInterest));
					strcpy(m_stClient[i].comment , (char*)_bstr_t(m_strComment));
					strcpy(m_stClient[i].trading , (char*)_bstr_t(m_strTrading));

					//합계 평균
					//l_nTotal = m_stClient[i].id + m_stClient[i].interest + m_stClient[i].comment;
					//l_nAvg = l_nTotal/3;
					//l_strAvg.Format(_T("%d"),l_nAvg);
					//l_strTotal.Format(_T("%d"),l_nTotal);

					//리스트 컨트롤상에서 삭제
					m_List.DeleteItem(i);

					//에디트 컨트롤에 입력한 값을 리스트 컨트롤에 추가하였다면
					//에디트 컨트롤을 초기화 합니다.
					m_strName = _T("");
					m_strId = _T("");
					m_strInterest = _T("");
					m_strComment = _T("");
					m_strTrading = _T("");

					break;
				}
			}
		}
		UpdateData(FALSE);
	}	
	m_List.SetItemCountEx(m_nTotal, LVSICF_NOSCROLL);
}

//*** 리스트 컨트롤 삭제 버튼 기능
void ClistControl_1Dlg::OnBnClickedButtonDelete()
{
	//입력 값이 빈 값이라면
	if(m_nTotal < 1)
	{
		MessageBox(TEXT("학생 정보를 추가해주십시오"));
	}
	//리스트 컨트롤의 현재 항목 수를 얻어옵니다.
	int l_nCount = m_List.GetItemCount(); 

	//모든 항목을 조사하여
	for(int i = l_nCount-1 ; i >= 0; i--)
	{
		//클릭된 항목이 있다면, 클릭된 항목 인덱스 = i
		if(m_List.GetItemState(i, LVIS_SELECTED) != 0)
		{	
			//삭제
			deleteClient(i);
		}
	}
	m_List.SetItemCountEx(m_nTotal,LVSICF_NOSCROLL);
}

//피드백: 클릭 말고 ItemChange 로 해야 키보드로 위아래 할 때도 가능...
//*** 에디트 컨트롤로 텍스트 옮기기
void ClistControl_1Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//Lock추가
	*pResult = 1;

	//리스트 컨트롤의 현재 항목 수를 얻어옵니다.
	int l_nCount = m_List.GetItemCount(); 

	//모든 항목을 조사하여
	for(int i =  0; i < l_nCount; i++)
	{
		//클릭된 항목이 있다면, 클릭된 항목 인덱스 = i
		if(m_List.GetItemState(i, LVIS_SELECTED) != 0) 
		{	
			SetDlgItemText(IDC_NAME , m_List.GetItemText(i,0));
			SetDlgItemText(IDC_EDIT_ID , m_List.GetItemText(i,1));
			SetDlgItemText(IDC_EDIT_INTEREST , m_List.GetItemText(i,2));
			SetDlgItemText(IDC_EDIT_COMMENT , m_List.GetItemText(i,3));
			break;
		}
	}
	CString str[100];
	int index=0;
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		return;
	}
	else
	{
		while(pos)
		{	
			int nItem = m_List.GetNextSelectedItem(pos);
			auto strItem = m_List.GetItemText(nItem,0);
			str[index]=strItem;
			index++;
		}
	}

}


//*** 텍스트 파일 읽기
void ClistControl_1Dlg::OnBnClickedButtonFileIn()
{
	//초기화
	deleteAll();
	//한글 깨짐으로 인한 locale 설정
	char* pLocale = setlocale(LC_ALL, "idean");
	//변수
	CStdioFile l_fileIn;
	CString l_strToken;
	TCHAR szBuffer[] = _T("텍스트 파일(*.*)|*.txt||");           // 경로저장 버퍼 
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szBuffer);
	int iRet = fDlg.DoModal();
	auto m_strFilePath = fDlg.GetPathName();
	if(iRet==IDOK)
	{
		// 현재 경로에서 "test.txt" 파일을 연다.
		// CStdioFile::modeRead -> 파일을 읽기 모드로 연다. ( 파일이 없다면 실패한다. )
		if(l_fileIn.Open(m_strFilePath, CStdioFile::modeRead))
		{
			CString l_strDisplay, str;
			// 파일에 더이상 텍스트 내용이 없을때까지 한줄씩 반복해서 읽어서 str 변수에 저장한다.
			while(l_fileIn.ReadString(str))
			{
				// 읽어들인 한줄의 텍스트를 l_strDisplay 변수에 추가한다.
				l_strDisplay +=str;
				addFile();
				for(int k = 0 ; k < 6 ; k++)
				{
					AfxExtractSubString(l_strToken, l_strDisplay, k, '\t');
					if(k == 0)
					{
						strcpy(m_stClient[m_nTotal - 1].name , _bstr_t(l_strToken));
					}
					if(k == 1)
					{
						strcpy(m_stClient[m_nTotal - 1].trading , _bstr_t(l_strToken));
					}
					if(k == 2)
					{
						strcpy(m_stClient[m_nTotal - 1].id , _bstr_t(l_strToken));
					}
					if(k == 3)
					{
						strcpy(m_stClient[m_nTotal - 1].interest , _bstr_t(l_strToken));
					}
					if(k == 4)
					{
						strcpy(m_stClient[m_nTotal - 1].comment , _bstr_t(l_strToken));
					}
					//피드백: else if , else 추가...
				}
				l_strDisplay = _T("");
			}
		}
		m_List.SetItemCountEx(m_nTotal,LVSICF_NOSCROLL);
		l_fileIn.Close();
		setlocale(LC_ALL, pLocale);
	}
}

//*** 텍스트 파일 쓰기
void ClistControl_1Dlg::OnBnClickedButtonFileOut()
{
	//변수
	CStdioFile l_fileOut;
	CString l_strDisplay;

	////리스트 컨트롤의 현재 항목 수를 얻어옵니다.
	int l_nCount = m_List.GetItemCount(); 
	TCHAR szBuffer[] = _T("텍스트 파일(*.*)|*.txt||");           // 경로저장 버퍼 
	CFileDialog fDlg(FALSE, _T("*.txt"), NULL, OFN_HIDEREADONLY, szBuffer);
	int iRet = fDlg.DoModal();
	auto m_strFilePath = fDlg.GetPathName();
	if(iRet==IDOK)
	{
		if(l_fileOut.Open(m_strFilePath, CStdioFile::modeCreate | CStdioFile::modeWrite ))
		{
			//모든 항목을 조사하여
			for(int i =  0; i < l_nCount; i++)
			{
				for(int j = 0 ; j < 6 ; j++)
				{
					l_strDisplay += m_List.GetItemText(i,j);
					if(j<5)
					{
						l_strDisplay += _T("\t");
					}
				}
				if(i < l_nCount-1)
				{
					l_strDisplay += _T("\n");
				}
			}
		}
		l_fileOut.WriteString( l_strDisplay );
		l_fileOut.Close();
	}
}

//*** 바이너리 파일 읽기
void ClistControl_1Dlg::OnBnClickedButtonBnFileIn()
{	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//초기화
	deleteAll();
	//변수
	CFile l_binIn;
	int nTotal = 0;
	TCHAR szBuffer[] = _T("dat 파일(*.*)|*.dat||");           // 경로저장 버퍼 
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szBuffer);
	int iRet = fDlg.DoModal();
	auto m_strFilePath = fDlg.GetPathName();
	if(iRet==IDOK)
	{
		if(l_binIn.Open(m_strFilePath,  CFile::modeRead )) 
		{
			l_binIn.Read(&m_nTotal, sizeof(int));
			if(m_nTotal>0)
			{
				m_stClient = new INFO[m_nTotal];
				l_binIn.Read(m_stClient, m_nTotal * sizeof(INFO));
			}
		}
		m_List.SetItemCountEx(m_nTotal,LVSICF_NOSCROLL);
		l_binIn.Close();
	}
}

//*** 바이너리 파일 쓰기
void ClistControl_1Dlg::OnBnClickedButtonBnFileOut()
{
	//변수
	CFile l_binOut;
	TCHAR szBuffer[] = _T("dat 파일(*.*)|*.dat||");           // 경로저장 버퍼 
	CFileDialog fDlg(FALSE, _T("*.dat"), NULL, OFN_HIDEREADONLY, szBuffer);
	int iRet = fDlg.DoModal();
	auto m_strFilePath = fDlg.GetPathName();
	if(iRet==IDOK)
	{
		/*CFile 사용*/
		if(l_binOut.Open(m_strFilePath,  CFile::modeCreate | CFile::modeWrite ))
		{
			l_binOut.Write(&m_nTotal, sizeof(int));
			if(m_stClient)
			{
				l_binOut.Write(m_stClient, sizeof(INFO) * m_nTotal);
			}
		}
		l_binOut.Close();
	}
}

//*** 디스플레이 정보
void ClistControl_1Dlg::OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	LVITEM* pItem = &(pDispInfo)->item;

	int nTotal = 0;
	int nAvg = 0;
	//로우에 연관되는 부 아이템의 색인
	int nRow = pItem->iItem;
	//컬럼에 연관되는 부 아이템의 색인
	int nCol = pItem->iSubItem;

	CString strid;
	CString strinterest;
	CString strcomment;
	CString strTotal;
	CString strAvg;
	//피드백: 초기화

	if (nRow<0 || nRow >= m_nTotal)
	{
		return;
	}	

	//유효한 텍스트 버퍼를 받을 수 있을 경우
	if (pItem->mask & LVIF_TEXT)
	{
		switch (nCol)
		{
		case 0:
			//LVITEM로 복사
			//icchTextMax = Maximum number of characters 
			// pszText : 아이템 텍스트를 명시하는 스트링의 주소
			lstrcpyn(pItem->pszText, _bstr_t(m_stClient[nRow].name), pItem->cchTextMax);
			break;
		case 1:
			lstrcpyn(pItem->pszText, _bstr_t(m_stClient[nRow].trading), pItem->cchTextMax);
			break;
		case 2:
			lstrcpyn(pItem->pszText, _bstr_t(m_stClient[nRow].id), pItem->cchTextMax);
			break;
		case 3:
			lstrcpyn(pItem->pszText, _bstr_t(m_stClient[nRow].interest), pItem->cchTextMax);
			break;
		case 4:
			lstrcpyn(pItem->pszText, _bstr_t(m_stClient[nRow].comment), pItem->cchTextMax);
			//case 4:
			//	nTotal = (m_stClient[nRow].id + m_stClient[nRow].interest + m_stClient[nRow].comment);
			//	strTotal.Format(_T("%d") , nTotal);
			//	lstrcpyn(pItem->pszText, strTotal , pItem->cchTextMax);
			//	break;
			//case 5:
			//	nAvg = (m_stClient[nRow].id + m_stClient[nRow].interest + m_stClient[nRow].comment)/3;
			//	strAvg.Format(_T("%d") , nAvg);
			//	lstrcpyn(pItem->pszText, strAvg , pItem->cchTextMax);
			//	break;
		default:

			break;
		}
		//피드백: Switch 보단 if, else if, else 로...
	}
	*pResult = 0;
}

/*
피드백 요약: 
memcpy 사용할만 한 곳이면 사용하고 switch보단 if, else if, else로
변수도 확실하게 l_ 쓸거면 확실히 사용. 선언했으면 초기화까지 확실하게.
구조체 이름도 좀 더 명시적으로.
*/