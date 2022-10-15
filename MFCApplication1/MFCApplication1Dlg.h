
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxwin.h"
 
class CMFCApplication1Dlg : public CDialogEx
{
protected:
	CEdit m_EditText;
	CEdit m_EditFontSize;
	CButton m_CheckOutline;
	CButton m_CheckBold;
	CButton m_CheckItalic;
	CButton m_CheckUnderline;
	CButton m_CheckStrikeout;

	Gdiplus::Bitmap* m_pBmp;
	StringAlignment m_AlignH;
	StringAlignment m_AlignV;
	 
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor
	 
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	void Apply();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public: 
	virtual BOOL OnInitDialog(); 
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonMiddle();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnEnChangeEditText();
	afx_msg void OnEnChangeEditFontsize();
	afx_msg void OnBnClickedButtonTop();
	afx_msg void OnBnClickedButtonVmiddle();
	afx_msg void OnBnClickedButtonBottom();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);  
	afx_msg void OnBnClickedCheckOutline();
	afx_msg void OnBnClickedCheckBold();
	afx_msg void OnBnClickedCheckItalic();
	afx_msg void OnBnClickedCheckUnderline();
	afx_msg void OnBnClickedCheckStrikeout();
};