
// Furkan's Bit CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Furkan's Bit Calculator.h"
#include "Furkan's Bit CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CFurkansBitCalculatorDlg dialog



CFurkansBitCalculatorDlg::CFurkansBitCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFurkansBitCalculatorDlg::IDD, pParent)
	, radio(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFurkansBitCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, editBoxOperand1);
	DDX_Control(pDX, IDC_EDIT1, editBoxOperand2);
	DDX_Control(pDX, IDC_CHECK1, checkShift);
	DDX_Control(pDX, IDC_COMBO1, comboBox);
	DDX_Control(pDX, IDC_EDIT3, editBoxShift);
	DDX_Control(pDX, IDC_BUTTON1, buttonCompute);
	DDX_Control(pDX, IDC_LIST1, listBoxResult);
	DDX_Radio(pDX, IDC_RADIO1, radio);
}

BEGIN_MESSAGE_MAP(CFurkansBitCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &CFurkansBitCalculatorDlg::OnBnClickedCheck1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFurkansBitCalculatorDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CFurkansBitCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CFurkansBitCalculatorDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CFurkansBitCalculatorDlg message handlers

BOOL CFurkansBitCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	comboBox.SetCurSel(0);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFurkansBitCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFurkansBitCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFurkansBitCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}







void CFurkansBitCalculatorDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	if (checkShift.GetCheck())
	{
		// Enable the combo box for left or right object 
		// and edit box for number of bits, so that the user can interact with it
		comboBox.EnableWindow(TRUE);
		editBoxShift.EnableWindow(TRUE);
	}
	else
	{
		// Disable the combo box for left or right object 
		// and edit box for number of bits
		comboBox.EnableWindow(FALSE);
		editBoxShift.EnableWindow(FALSE);
	}
}


void CFurkansBitCalculatorDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}

int maxSize = 0;
void CFurkansBitCalculatorDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	//initialize strings to store operands and result
	CString result, operand1_string, operand2_string;
	editBoxOperand1.GetWindowTextW(operand1_string);
	editBoxOperand2.GetWindowTextW(operand2_string);

	//for horizontal scroll
	CDC *pDC = GetDC();
	CSize cz;

	//convert operands from string to unsigned integer
	unsigned int operand1_uint =  _tcstoul(operand1_string,nullptr,10);
	unsigned int operand2_uint =  _tcstoul(operand2_string,nullptr,10);
	
	//bool to check whether the number of bits to shift entered or not
	bool is_shift_entered = true;

	//if one of at least one operand is not entered
	if(operand1_string.GetLength() == 0 || operand2_string.GetLength() == 0)
	{
		result = "At least one operand was not entered";

		//display it on the result box
		listBoxResult.AddString(result);

		//to horizontal scroll
		cz = pDC->GetTextExtent(result);
		if(cz.cx > maxSize)
		{
			maxSize = cz.cx; 
		}
		listBoxResult.SetHorizontalExtent(maxSize);
	}

	//if two operands entered
	else
	{
		//if user wants to shift
		if(checkShift.GetCheck())
		{
			CString shift_direction, shift;

			//get the number of bits to shift
			editBoxShift.GetWindowTextW(shift);

			//convert to unsigned it
			unsigned int shift_units = _tcstoul(shift,nullptr,10);

			//get the direction of the shift
			comboBox.GetWindowTextW(shift_direction);

			//if user did not enter the shift bits
			if(shift.GetLength() == 0)
			{
				result = "Specify how many bits you want to shift";

				//display message on the result box
				listBoxResult.AddString(result);

				//update the boolean 
				is_shift_entered=false;

				//for horizontal shift
				cz = pDC->GetTextExtent(result);
				if(cz.cx > maxSize)
				{
					maxSize = cz.cx; 
				}
				listBoxResult.SetHorizontalExtent(maxSize);
			}

			else
			{
				if(shift_direction == "Left")
				{
					//shift to the left
					operand1_uint = operand1_uint<<shift_units;
					operand2_uint = operand2_uint<<shift_units;

					//update the string versions of the operands
					operand1_string.Format(_T("%u"), operand1_uint);
					operand2_string.Format(_T("%u"), operand2_uint);
				}

				else if(shift_direction == "Right")
				{
					//shift to right
					operand1_uint = operand1_uint>>shift_units;
					operand2_uint = operand2_uint>>shift_units;

					//update the string versions of the operands
					operand1_string.Format(_T("%u"), operand1_uint);
					operand2_string.Format(_T("%u"), operand2_uint);
				}
			}
		}

		//in order to get the latest choice for the radio button
		UpdateData(true);

		//if shift bits entered
		if(is_shift_entered)
		{
			if(radio == 0)
			//AND
			{
				result.Format(_T("%u"), operand1_uint & operand2_uint);
				//display the result
				listBoxResult.AddString(operand1_string+" AND "+operand2_string+" = " +result);

				//for horizontal scroll
				cz = pDC->GetTextExtent(operand1_string+" AND "+operand2_string+" = " +result);
				if(cz.cx > maxSize)
				{
					maxSize = cz.cx; 
				}
				listBoxResult.SetHorizontalExtent(maxSize);
			}

			else if(radio == 1)
			//OR
			{
				result.Format(_T("%u"), operand1_uint | operand2_uint);
				//display the result
				listBoxResult.AddString(operand1_string+" OR "+operand2_string+" = " +result);

				//for horizontal scroll
				cz = pDC->GetTextExtent(operand1_string+" OR "+operand2_string+" = " +result);
				if(cz.cx > maxSize)
				{
					maxSize = cz.cx; 
				}
				listBoxResult.SetHorizontalExtent(maxSize);
			}

			else if(radio == 2)
			//XOR
			{
				result.Format(_T("%u"), operand1_uint ^ operand2_uint);
				//display the result
				listBoxResult.AddString(operand1_string+" XOR "+operand2_string+" = " +result);

				//for horizontal scroll
				cz = pDC->GetTextExtent(operand1_string+" XOR "+operand2_string+" = " +result);
				if(cz.cx > maxSize)
				{
					maxSize = cz.cx; 
				}
				listBoxResult.SetHorizontalExtent(maxSize);
			}
		}
	}
}


void CFurkansBitCalculatorDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}
