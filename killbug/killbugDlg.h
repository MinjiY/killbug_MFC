
// killbugDlg.h : ��� ����
//

#pragma once

#define MAX_BUG_COUNT 20

struct BugLife
{
	POINT s_pos;
	POINT e_pos;

	double a;
	double b;

	int x_step;
	int y_step;
	int size;
	COLORREF color;
};

// CkillbugDlg ��ȭ ����
class CkillbugDlg : public CDialogEx
{
private:
	BugLife m_bug_list[MAX_BUG_COUNT];
	int m_bug_count = 0;
	int m_width, m_height;
	int m_score = 0;

// �����Դϴ�.
public:
	void MakeBugPos(POINT * a_pos, int a_side);
	void MakeBug(BugLife * ap_bug);
	CkillbugDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KILLBUG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
