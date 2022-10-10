
// Furkan's Bit CalculatorDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CFurkansBitCalculatorDlg dialog
class CFurkansBitCalculatorDlg : public CDialogEx
{
// Construction
public:
	CFurkansBitCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FURKANSBITCALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnCbnSelchangeCombo1();
	CEdit editBoxOperand1;
	CEdit editBoxOperand2;
	CButton checkShift;
	CComboBox comboBox;
	CEdit editBoxShift;
	CButton buttonCompute;
	CListBox listBoxResult;
	afx_msg void OnBnClickedButton1();

	int radio;
	afx_msg void OnBnClickedRadio1();
};
