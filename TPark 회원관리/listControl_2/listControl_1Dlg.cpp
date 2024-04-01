
// listControl_1Dlg.cpp : ���� ����
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

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
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


// ClistControl_1Dlg ��ȭ ����


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
	//����ü string�� ���� Ŭ������ ���Ͽ�
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


// ClistControl_1Dlg �޽��� ó����

BOOL ClistControl_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// ����Ʈ ��Ʈ���� ũ�⸦ ���´�.
	CRect rect;
	m_List.GetClientRect(&rect);

	//����Ʈ ��Ʈ�� �÷� �߰�
	m_List.InsertColumn(0, _T("�̸�"), LVCFMT_LEFT, rect.Width()/6);
	m_List.InsertColumn(1, _T("�ŷ���"), LVCFMT_LEFT, rect.Width()/6);
	m_List.InsertColumn(2, _T("ID"), LVCFMT_LEFT, rect.Width()/6);
	m_List.InsertColumn(3, _T("������"), LVCFMT_LEFT, rect.Width()/6);
	m_List.InsertColumn(4, _T("�ڸ�Ʈ"), LVCFMT_LEFT, rect.Width()/6*2+2);

	//Row ��ü ���̶���Ʈ �� Ŀ�� ��� �ٲٱ�	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void ClistControl_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR ClistControl_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//*** �л� ���� �߰� �Լ�
void ClistControl_1Dlg::addClient()
{	
	//�л� ������ �� ���̶��
	if(!(m_stClient))
	{
		m_stClient = new INFO[m_nTotal+1];
	}
	//�� ���� �ƴ϶�� �л� ���� �߰�
	else 
	{	
		//�л��� ������ ���� ����� ��Ƶ� ����
		INFO* l_stTempA = new INFO[m_nTotal+1];

		//����
		for(int i = 0 ; i<m_nTotal; i++)
		{
			//�̸� �� ����
			strcpy(l_stTempA[i].name, m_stClient[i].name);
			strcpy(l_stTempA[i].id, m_stClient[i].id);
			strcpy(l_stTempA[i].interest, m_stClient[i].interest);
			strcpy(l_stTempA[i].comment, m_stClient[i].comment);
			strcpy(l_stTempA[i].trading, m_stClient[i].trading);
		}				
		//�Ⱦ��� �޸� ���� �� ����
		delete[] m_stClient;
		m_stClient = l_stTempA;
	}
	//���� �ڵ尡 ���� �۵��� �� �л� �� �߰�
	m_nTotal+=1;

	UpdateData(TRUE);

	int l_nItemNum = m_List.GetItemCount();
	//int l_nAvg = 0;
	//int l_nTotal = 0;
	CString l_strAvg = _T("");
	CString l_strTotal = _T("");

	//������ �� �Է� �ޱ�
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
	//�հ� , ���
	//l_nTotal = m_stClient[m_nTotal-1].id + m_stClient[m_nTotal-1].interest + m_stClient[m_nTotal-1].comment;
	//l_nAvg = l_nTotal/3;
	//l_strAvg.Format(_T("%d"),l_nAvg);
	//l_strTotal.Format(_T("%d"), l_nTotal);

	//����Ʈ ��Ʈ�ѿ� �Է��� ���� ����Ʈ ��Ʈ�ѿ� �߰��Ͽ��ٸ�
	//����Ʈ ��Ʈ���� �ʱ�ȭ �մϴ�.
	m_strName = _T("");
	m_strId = _T("");
	m_strInterest = _T("");
	m_strComment = _T("");
	m_strTrading = _T("");

	UpdateData(FALSE);
}

//*** �л� ���� ���� �Լ�
void ClistControl_1Dlg::deleteClient(int arg_i)
{
	//�����ؾ� �ϴ� �����͸� ���� ������ ���� ���� ����
	int l_n = 0;
	//�л��� ������ ���� ����� ��Ƶ� ����
	INFO* l_stTempD = new INFO[m_nTotal-1];

	//����
	for(int j = 0;j < m_nTotal; j++)
	{	
		//���絵�� �ش� �ε����� �����ؾ� �ϴ� ���� �ٴٸ��� 
		if(arg_i==j) 
		{
			l_n = 1;
			continue;
		}

		//���� ���� ���� ����. ��)array[i] = array[i+2]
		strcpy(l_stTempD[j - l_n].name , m_stClient[j].name);
		strcpy(l_stTempD[j - l_n].id , m_stClient[j].id);
		strcpy(l_stTempD[j - l_n].interest , m_stClient[j].interest);
		strcpy(l_stTempD[j - l_n].comment , m_stClient[j].comment);
		strcpy(l_stTempD[j - l_n].trading , m_stClient[j].trading);
	}

	//���� �� ���� �Ϸ�
	delete[] m_stClient;
	m_stClient = l_stTempD;

	//����Ʈ ��Ʈ�ѻ󿡼��� ����
	//m_List.DeleteItem(arg_i);

	UpdateData(TRUE);

	//����Ʈ ��Ʈ�ѿ� �Է��� ���� ����Ʈ ��Ʈ�ѿ� �߰��Ͽ��ٸ�
	//����Ʈ ��Ʈ���� �ʱ�ȭ �մϴ�.
	m_strName = _T("");
	m_strId = _T("");
	m_strInterest = _T("");
	m_strComment = _T("");
	m_strTrading = _T("");

	UpdateData(FALSE);

	//���� �ڵ尡 ���� �۵��� �� �л� �� ����
	m_nTotal -= 1;
}

//*** ��� ���� ���� �Լ�
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

//*** ���Ͽ� �л� ���� �߰� �Լ�
void ClistControl_1Dlg::addFile()
{
	//�л� ������ �� ���̶��
	if(!(m_stClient))
	{
		m_stClient = new INFO[m_nTotal+1];
	}
	//�� ���� �ƴ϶�� �л� ���� �߰�
	else 
	{	
		//�л��� ������ ���� ����� ��Ƶ� ����
		INFO* l_stTempA = new INFO[m_nTotal+1];

		//����
		for(int i = 0 ; i<m_nTotal; i++)
		{
			//�̸� �� ����
			memcpy(l_stTempA, m_stClient, sizeof(INFO) * m_nTotal);
		}				
		//�Ⱦ��� �޸� ���� �� ����
		delete[] m_stClient;
		m_stClient = l_stTempA;
	}
	//���� �ڵ尡 ���� �۵��� �� �л� �� �߰�
	m_nTotal+=1;
}



//*** ����Ʈ ��Ʈ�� �߰� ��ư ���
void ClistControl_1Dlg::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);

	//�Է� ���� �� ���̶��
	if(m_strName.IsEmpty())
	{
		MessageBox(TEXT("�л� �̸��� �������ֽʽÿ�"));
	}
	//�Է� ���� �����Ѵٸ�
	else
	{	
		addClient();
	}

	UpdateData(FALSE);
	m_List.SetItemCountEx(m_nTotal,LVSICF_NOSCROLL);
}

//*** ����Ʈ ��Ʈ�� ���� ��ư ���
void ClistControl_1Dlg::OnBnClickedButtonEdit()
{	
	//�Է� ���� �� ���̶��
	if(m_nTotal < 1)
	{
		MessageBox(TEXT("�л� ������ �߰����ֽʽÿ�"));
	}
	else
	{
		//����Ʈ ��Ʈ���� ���� �׸� ���� ���ɴϴ�.
		int l_nCount = m_List.GetItemCount(); 

		UpdateData(TRUE);

		//��� �׸��� �����Ͽ�
		for(int i =  0; i < l_nCount; i++)   
		{
			//Ŭ���� �׸��� �ִٸ�, Ŭ���� �׸� �ε��� = i
			if(m_List.GetItemState(i, LVIS_SELECTED) != 0)
			{	
				//�Է� ���� �� ���̶��
				if(m_strName.IsEmpty())
				{
					MessageBox(TEXT("�л� ���� �������ֽʽÿ�"));
				}
				else
				{
					//int l_nAvg = 0;
					//int l_nTotal = 0;
					//CString l_strAvg = _T("");
					//CString l_strTotal = _T("");

					//�Է� �� �ޱ�
					strcpy(m_stClient[i].name , (char*)_bstr_t(m_strName));
					strcpy(m_stClient[i].id , (char*)_bstr_t(m_strId));
					strcpy(m_stClient[i].interest , (char*)_bstr_t(m_strInterest));
					strcpy(m_stClient[i].comment , (char*)_bstr_t(m_strComment));
					strcpy(m_stClient[i].trading , (char*)_bstr_t(m_strTrading));

					//�հ� ���
					//l_nTotal = m_stClient[i].id + m_stClient[i].interest + m_stClient[i].comment;
					//l_nAvg = l_nTotal/3;
					//l_strAvg.Format(_T("%d"),l_nAvg);
					//l_strTotal.Format(_T("%d"),l_nTotal);

					//����Ʈ ��Ʈ�ѻ󿡼� ����
					m_List.DeleteItem(i);

					//����Ʈ ��Ʈ�ѿ� �Է��� ���� ����Ʈ ��Ʈ�ѿ� �߰��Ͽ��ٸ�
					//����Ʈ ��Ʈ���� �ʱ�ȭ �մϴ�.
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

//*** ����Ʈ ��Ʈ�� ���� ��ư ���
void ClistControl_1Dlg::OnBnClickedButtonDelete()
{
	//�Է� ���� �� ���̶��
	if(m_nTotal < 1)
	{
		MessageBox(TEXT("�л� ������ �߰����ֽʽÿ�"));
	}
	//����Ʈ ��Ʈ���� ���� �׸� ���� ���ɴϴ�.
	int l_nCount = m_List.GetItemCount(); 

	//��� �׸��� �����Ͽ�
	for(int i = l_nCount-1 ; i >= 0; i--)
	{
		//Ŭ���� �׸��� �ִٸ�, Ŭ���� �׸� �ε��� = i
		if(m_List.GetItemState(i, LVIS_SELECTED) != 0)
		{	
			//����
			deleteClient(i);
		}
	}
	m_List.SetItemCountEx(m_nTotal,LVSICF_NOSCROLL);
}

//�ǵ��: Ŭ�� ���� ItemChange �� �ؾ� Ű����� ���Ʒ� �� ���� ����...
//*** ����Ʈ ��Ʈ�ѷ� �ؽ�Ʈ �ű��
void ClistControl_1Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//Lock�߰�
	*pResult = 1;

	//����Ʈ ��Ʈ���� ���� �׸� ���� ���ɴϴ�.
	int l_nCount = m_List.GetItemCount(); 

	//��� �׸��� �����Ͽ�
	for(int i =  0; i < l_nCount; i++)
	{
		//Ŭ���� �׸��� �ִٸ�, Ŭ���� �׸� �ε��� = i
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


//*** �ؽ�Ʈ ���� �б�
void ClistControl_1Dlg::OnBnClickedButtonFileIn()
{
	//�ʱ�ȭ
	deleteAll();
	//�ѱ� �������� ���� locale ����
	char* pLocale = setlocale(LC_ALL, "idean");
	//����
	CStdioFile l_fileIn;
	CString l_strToken;
	TCHAR szBuffer[] = _T("�ؽ�Ʈ ����(*.*)|*.txt||");           // ������� ���� 
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szBuffer);
	int iRet = fDlg.DoModal();
	auto m_strFilePath = fDlg.GetPathName();
	if(iRet==IDOK)
	{
		// ���� ��ο��� "test.txt" ������ ����.
		// CStdioFile::modeRead -> ������ �б� ���� ����. ( ������ ���ٸ� �����Ѵ�. )
		if(l_fileIn.Open(m_strFilePath, CStdioFile::modeRead))
		{
			CString l_strDisplay, str;
			// ���Ͽ� ���̻� �ؽ�Ʈ ������ ���������� ���پ� �ݺ��ؼ� �о str ������ �����Ѵ�.
			while(l_fileIn.ReadString(str))
			{
				// �о���� ������ �ؽ�Ʈ�� l_strDisplay ������ �߰��Ѵ�.
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
					//�ǵ��: else if , else �߰�...
				}
				l_strDisplay = _T("");
			}
		}
		m_List.SetItemCountEx(m_nTotal,LVSICF_NOSCROLL);
		l_fileIn.Close();
		setlocale(LC_ALL, pLocale);
	}
}

//*** �ؽ�Ʈ ���� ����
void ClistControl_1Dlg::OnBnClickedButtonFileOut()
{
	//����
	CStdioFile l_fileOut;
	CString l_strDisplay;

	////����Ʈ ��Ʈ���� ���� �׸� ���� ���ɴϴ�.
	int l_nCount = m_List.GetItemCount(); 
	TCHAR szBuffer[] = _T("�ؽ�Ʈ ����(*.*)|*.txt||");           // ������� ���� 
	CFileDialog fDlg(FALSE, _T("*.txt"), NULL, OFN_HIDEREADONLY, szBuffer);
	int iRet = fDlg.DoModal();
	auto m_strFilePath = fDlg.GetPathName();
	if(iRet==IDOK)
	{
		if(l_fileOut.Open(m_strFilePath, CStdioFile::modeCreate | CStdioFile::modeWrite ))
		{
			//��� �׸��� �����Ͽ�
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

//*** ���̳ʸ� ���� �б�
void ClistControl_1Dlg::OnBnClickedButtonBnFileIn()
{	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//�ʱ�ȭ
	deleteAll();
	//����
	CFile l_binIn;
	int nTotal = 0;
	TCHAR szBuffer[] = _T("dat ����(*.*)|*.dat||");           // ������� ���� 
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

//*** ���̳ʸ� ���� ����
void ClistControl_1Dlg::OnBnClickedButtonBnFileOut()
{
	//����
	CFile l_binOut;
	TCHAR szBuffer[] = _T("dat ����(*.*)|*.dat||");           // ������� ���� 
	CFileDialog fDlg(FALSE, _T("*.dat"), NULL, OFN_HIDEREADONLY, szBuffer);
	int iRet = fDlg.DoModal();
	auto m_strFilePath = fDlg.GetPathName();
	if(iRet==IDOK)
	{
		/*CFile ���*/
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

//*** ���÷��� ����
void ClistControl_1Dlg::OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	LVITEM* pItem = &(pDispInfo)->item;

	int nTotal = 0;
	int nAvg = 0;
	//�ο쿡 �����Ǵ� �� �������� ����
	int nRow = pItem->iItem;
	//�÷��� �����Ǵ� �� �������� ����
	int nCol = pItem->iSubItem;

	CString strid;
	CString strinterest;
	CString strcomment;
	CString strTotal;
	CString strAvg;
	//�ǵ��: �ʱ�ȭ

	if (nRow<0 || nRow >= m_nTotal)
	{
		return;
	}	

	//��ȿ�� �ؽ�Ʈ ���۸� ���� �� ���� ���
	if (pItem->mask & LVIF_TEXT)
	{
		switch (nCol)
		{
		case 0:
			//LVITEM�� ����
			//icchTextMax = Maximum number of characters 
			// pszText : ������ �ؽ�Ʈ�� ����ϴ� ��Ʈ���� �ּ�
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
		//�ǵ��: Switch ���� if, else if, else ��...
	}
	*pResult = 0;
}

/*
�ǵ�� ���: 
memcpy ����Ҹ� �� ���̸� ����ϰ� switch���� if, else if, else��
������ Ȯ���ϰ� l_ ���Ÿ� Ȯ���� ���. ���������� �ʱ�ȭ���� Ȯ���ϰ�.
����ü �̸��� �� �� ���������.
*/