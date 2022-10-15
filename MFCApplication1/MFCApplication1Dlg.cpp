
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
 
CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_pBmp(NULL)
{ 
	m_AlignH = StringAlignmentCenter;
	m_AlignV = StringAlignmentCenter;
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_EditText);
	DDX_Control(pDX, IDC_EDIT_FONTSIZE, m_EditFontSize);
	DDX_Control(pDX, IDC_CHECK_OUTLINE, m_CheckOutline);
	DDX_Control(pDX, IDC_CHECK_BOLD, m_CheckBold);
	DDX_Control(pDX, IDC_CHECK_ITALIC, m_CheckItalic);
	DDX_Control(pDX, IDC_CHECK_UNDERLINE, m_CheckUnderline);
	DDX_Control(pDX, IDC_CHECK_STRIKEOUT, m_CheckStrikeout);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON() 
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CMFCApplication1Dlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_MIDDLE, &CMFCApplication1Dlg::OnBnClickedButtonMiddle)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CMFCApplication1Dlg::OnBnClickedButtonRight)
	ON_EN_CHANGE(IDC_EDIT_TEXT, &CMFCApplication1Dlg::OnEnChangeEditText) 
	ON_EN_CHANGE(IDC_EDIT_FONTSIZE, &CMFCApplication1Dlg::OnEnChangeEditFontsize)
	ON_BN_CLICKED(IDC_BUTTON_TOP, &CMFCApplication1Dlg::OnBnClickedButtonTop)
	ON_BN_CLICKED(IDC_BUTTON_VMIDDLE, &CMFCApplication1Dlg::OnBnClickedButtonVmiddle)
	ON_BN_CLICKED(IDC_BUTTON_BOTTOM, &CMFCApplication1Dlg::OnBnClickedButtonBottom)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHECK_OUTLINE, &CMFCApplication1Dlg::OnBnClickedCheckOutline)
	ON_BN_CLICKED(IDC_CHECK_BOLD, &CMFCApplication1Dlg::OnBnClickedCheckBold)
	ON_BN_CLICKED(IDC_CHECK_ITALIC, &CMFCApplication1Dlg::OnBnClickedCheckItalic)
	ON_BN_CLICKED(IDC_CHECK_UNDERLINE, &CMFCApplication1Dlg::OnBnClickedCheckUnderline)
	ON_BN_CLICKED(IDC_CHECK_STRIKEOUT, &CMFCApplication1Dlg::OnBnClickedCheckStrikeout)
END_MESSAGE_MAP()
 
BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
 
	// TODO: Add extra initialization here
	ModifyStyle(0, WS_CLIPCHILDREN);

	m_EditText.SetWindowTextW(L"How are you...");
	m_EditFontSize.SetWindowTextW(L"40");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CMFCApplication1Dlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	CMyMemDC memdc(&dc, rect);
	memdc.FillSolidRect(&rect, RGB(239, 239, 239));

	if (m_pBmp)
	{
		Graphics graphics(memdc.m_hDC);
		graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
		graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
		graphics.SetSmoothingMode(SmoothingModeAntiAlias);
		graphics.DrawImage(m_pBmp, 20, 20);
	}
}
 
#define EPSILON  1e-4f

void CMFCApplication1Dlg::Apply()
{  
	wchar_t text[512] = {};
	m_EditText.GetWindowText(text, sizeof(text));
	wcscat_s(text, L"\n");

	char fontsize[20] = {};
	GetWindowTextA(m_EditFontSize.m_hWnd, fontsize, sizeof(fontsize));
	float fFontSize = float(atoi(fontsize));

	BOOL bOutline = m_CheckOutline.GetCheck();
	float outline_size = 6.f;

	StringFormat format;
	format.SetTrimming(Gdiplus::StringTrimmingNone);
	format.SetFormatFlags(StringFormatFlagsNoFitBlackBox | StringFormatFlagsMeasureTrailingSpaces);
	format.SetAlignment(m_AlignH);
	format.SetLineAlignment(m_AlignV);
  
	int nFontStyle = Gdiplus::FontStyleRegular;
	if (m_CheckBold.GetCheck())	nFontStyle |= Gdiplus::FontStyleBold;
	if (m_CheckItalic.GetCheck()) nFontStyle |= Gdiplus::FontStyleItalic;
	if (m_CheckUnderline.GetCheck()) nFontStyle |= Gdiplus::FontStyleUnderline;
	if (m_CheckStrikeout.GetCheck()) nFontStyle |= Gdiplus::FontStyleStrikeout;

	Gdiplus::Font font(L"Arial", fFontSize, nFontStyle);

	FontFamily family;
	font.GetFamily(&family);

	RectF bounding_box;
	RectF bounding_box_tmp;
	{
		HDC hdc = ::GetDC(m_hWnd);

		Graphics graphics(hdc);
		graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
		graphics.SetSmoothingMode(SmoothingModeAntiAlias);

		graphics.MeasureString(text, -1, &font, PointF(0.0f, 0.0f), &format, &bounding_box_tmp);
	
		bounding_box_tmp.X = bounding_box_tmp.Y = 0.f;
		bounding_box = bounding_box_tmp;
		if (bOutline)
		{ 
			bounding_box.Width += outline_size;
			bounding_box.Height += outline_size;
		}
		 
		{ // handle text region because of we pushed "\n"

			RectF before;
			RectF after;
			graphics.MeasureString(L"W", 2, &font, PointF(0.0f, 0.0f), &format, &before); 
			graphics.MeasureString(L"W\n", 3, &font, PointF(0.0f, 0.0f), &format, &after);
			 
			float offset_cx = after.Width - before.Width;
			if (offset_cx >= 1.0f) offset_cx -= 1.0f;

			bounding_box.Width -= offset_cx; 
			switch (m_AlignH)
			{
			case Gdiplus::StringAlignmentNear:
				bounding_box.X = 0;
				break;
			case Gdiplus::StringAlignmentCenter:
				bounding_box.X = (offset_cx / 2);
				break;
			case Gdiplus::StringAlignmentFar:
				bounding_box.X = offset_cx;
				break;
			default:
				break;
			}
		}

		::ReleaseDC(m_hWnd, hdc);
	}

	LONG cx = LONG(bounding_box.Width + EPSILON);
	LONG cy = LONG(bounding_box.Height + EPSILON);
	cx += (cx % 2);
	cy += (cy % 2);

	if (m_pBmp)
	{
		::delete m_pBmp;
		m_pBmp = NULL;
	}
	m_pBmp = ::new Gdiplus::Bitmap(cx, cy, PixelFormat32bppARGB);

	Graphics graphics(m_pBmp);
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.Clear(Gdiplus::Color(255,0,0,0));

	Gdiplus::Color clrTextGDIP(0XFFFFFFFF);
	Gdiplus::SolidBrush brushText(clrTextGDIP);
	 
#if 1
	bounding_box = bounding_box_tmp;
	if (bOutline)
		bounding_box.Offset(outline_size / 2, outline_size / 2);

	float emSize = graphics.GetDpiX() * font.GetSize() / float(72);

	GraphicsPath path;
	path.AddString(text, -1, &family, font.GetStyle(), emSize, bounding_box, &format);

	if (bOutline)
	{
		Pen pen(Color(0XFFFF0000), outline_size);
		graphics.DrawPath(&pen, &path);
	}

	graphics.FillPath(&brushText, &path);
#else
	graphics.DrawString(text, -1, &font, bounding_box, &format, &brushText);
#endif

	Invalidate(TRUE);
}

void CMFCApplication1Dlg::OnBnClickedButtonLeft()
{
	m_AlignH = StringAlignmentNear;
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedButtonMiddle()
{
	m_AlignH = StringAlignmentCenter;
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedButtonRight()
{
	m_AlignH = StringAlignmentFar;
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedButtonVmiddle()
{
	m_AlignV = StringAlignmentCenter;
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedButtonBottom()
{
	m_AlignV = StringAlignmentFar;
	Apply();
}

void CMFCApplication1Dlg::OnEnChangeEditText()
{ 
	// TODO:  Add your control notification handler code here
	Apply();
}

void CMFCApplication1Dlg::OnEnChangeEditFontsize()
{ 
	// TODO:  Add your control notification handler code here
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedButtonTop()
{
	m_AlignV = StringAlignmentNear;
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedCheckOutline()
{
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedCheckBold()
{
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedCheckItalic()
{
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedCheckUnderline()
{
	Apply();
}

void CMFCApplication1Dlg::OnBnClickedCheckStrikeout()
{
	Apply();
}