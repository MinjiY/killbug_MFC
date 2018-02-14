
// killbugDlg.cpp : ���� ����


#include "stdafx.h"
#include "killbug.h"
#include "killbugDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CkillbugDlg ��ȭ ����



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


// CkillbugDlg �޽��� ó����
BOOL CkillbugDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	srand((unsigned int)time(NULL));
	CRect r;
	GetClientRect(r);
	m_width = r.Width();
	m_height = r.Height();

	SetTimer(1, 100, NULL);
	SetTimer(2, 1000, NULL);

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}




// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CkillbugDlg::OnPaint()
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
