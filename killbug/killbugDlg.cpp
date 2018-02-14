
// killbugDlg.cpp : 구현 파일


#include "stdafx.h"
#include "killbug.h"
#include "killbugDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CkillbugDlg 대화 상자



CkillbugDlg::CkillbugDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KILLBUG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CkillbugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CkillbugDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CkillbugDlg 메시지 처리기
BOOL CkillbugDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	srand((unsigned int)time(NULL));
	CRect r;
	GetClientRect(r);
	m_width = r.Width();
	m_height = r.Height();

	SetTimer(1, 100, NULL);
	SetTimer(2, 1000, NULL);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}




// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CkillbugDlg::OnPaint()
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
		CPaintDC dc(this);
		CPen line_pen;
		BugLife *p_pos = m_bug_list;

		for (int i = 0; i < m_bug_count; i++) {
			line_pen.CreatePen(PS_SOLID, 1, m_bug_list[i].color);

			CPen *p_old_pen = dc.SelectObject(&line_pen);

			dc.MoveTo(p_pos->s_pos);
			dc.LineTo(p_pos->e_pos);

			dc.Ellipse(p_pos->x_step - p_pos->size / 2,
				p_pos->y_step - p_pos->size / 2,
				p_pos->x_step + p_pos->size / 2,
				p_pos->y_step + p_pos->size / 2);
			
			dc.SelectObject(p_old_pen);

			line_pen.DeleteObject();
			p_pos++;
		}
		CString str;
		str.Format(L"score=%d", m_score);
		dc.TextOut(0, 0, str);

	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CkillbugDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CkillbugDlg::MakeBugPos(POINT * a_pos, int a_side)
{
	if (a_side == 0) {
		a_pos->x = rand() % (m_width - 100) + 50;
		a_pos->y = 0;
	}
	else if (a_side == 2) {
		a_pos->x = rand() % (m_width - 100) + 50;
		a_pos->y = m_height;
	}
	else if (a_side == 1) {
		a_pos->x = 0;
		a_pos->y = rand() % (m_height - 100) + 50;
	}
	else if (a_side == 3) {
		a_pos->x = m_width;
		a_pos->y = rand() % (m_height - 100) + 50;
	}
}




void CkillbugDlg::MakeBug(BugLife *ap_bug)
{
	int first_side = rand() % 4, second_side;


	MakeBugPos(&ap_bug->s_pos, first_side);


	do {
		second_side = rand() % 4;
	} while (first_side == second_side);

	MakeBugPos(&ap_bug->e_pos, second_side);

	if (ap_bug->e_pos.x == ap_bug->s_pos.x) ap_bug->e_pos.x += 30;

	ap_bug->color = RGB(rand() % 256, rand() % 256, rand() % 256);
	ap_bug->size = rand() % 40 + 20;	//20~60

	ap_bug->x_step = ap_bug->s_pos.x;
	ap_bug->y_step = 0;

	ap_bug->a = double(ap_bug->e_pos.y - ap_bug->s_pos.y) / (ap_bug->e_pos.x - ap_bug->s_pos.x);
	ap_bug->b = ap_bug->s_pos.y - ap_bug->a*ap_bug->s_pos.x;

}

void CkillbugDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (1 == nIDEvent)
	{
		BugLife *p_pos = m_bug_list;
		for (int i = 0; i < m_bug_count; i++)
		{
			if (p_pos->e_pos.x > p_pos->s_pos.x)
			{
				p_pos->x_step++;
				if (p_pos->x_step >= p_pos->e_pos.x)
				{
					m_score -= 5;
					MakeBug(m_bug_list + i);
				}
			}
			else {
				p_pos->x_step--;
				if (p_pos->x_step <= p_pos->e_pos.x)
				{
					m_score -= 5;
					MakeBug(m_bug_list + i);
				}
			}
			// y=ax+b
			p_pos->y_step = p_pos->a * p_pos->x_step + p_pos->b;
			p_pos++;
		}
		Invalidate();

	}
	else if (2 == nIDEvent)
	{
		if (m_bug_count < MAX_BUG_COUNT) {
			MakeBug(m_bug_list + m_bug_count);
			m_bug_count++;
		}
		else KillTimer(2);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CkillbugDlg::OnDestroy()
{
	KillTimer(1);
	KillTimer(2);

	CDialogEx::OnDestroy();

}


void CkillbugDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	BugLife *p_pos = m_bug_list;
	CRgn check_bug;
	int find_flag = 0;

	for (int i = 0; i < m_bug_count; i++)
	{
		check_bug.CreateEllipticRgn(p_pos->x_step - p_pos->size / 2,
			p_pos->y_step - p_pos->size / 2,
			p_pos->x_step + p_pos->size / 2,
			p_pos->y_step + p_pos->size / 2);

		if (check_bug.PtInRegion(point) != 0)
		{
			MakeBug(p_pos);
			m_score += 10;
			find_flag = 1;
			break;
		}
		check_bug.DeleteObject();
		p_pos++;

	}
	if (find_flag == 0) m_score -= 10;


	CDialogEx::OnLButtonDown(nFlags, point);
}
