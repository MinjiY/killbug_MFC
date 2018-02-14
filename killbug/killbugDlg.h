
// killbugDlg.h : 헤더 파일
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

// CkillbugDlg 대화 상자
class CkillbugDlg : public CDialogEx
{
private:
	BugLife m_bug_list[MAX_BUG_COUNT];
	int m_bug_count = 0;
	int m_width, m_height;
	int m_score = 0;

// 생성입니다.
public:
	void MakeBugPos(POINT * a_pos, int a_side);
	void MakeBug(BugLife * ap_bug);
	CkillbugDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KILLBUG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
