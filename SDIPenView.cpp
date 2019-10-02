
// SDIPenView.cpp: CSDIPenView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDIPen.h"
#endif

#include "SDIPenDoc.h"
#include "SDIPenView.h"
#include "CLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIPenView

IMPLEMENT_DYNCREATE(CSDIPenView, CView)

BEGIN_MESSAGE_MAP(CSDIPenView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENU_COL, &CSDIPenView::OnMenuCol)
	ON_COMMAND(ID_SIZE_1, &CSDIPenView::OnSize1)
	ON_COMMAND(ID_SIZE_16, &CSDIPenView::OnSize16)
	ON_COMMAND(ID_SIZE_32, &CSDIPenView::OnSize32)
END_MESSAGE_MAP()

// CSDIPenView 생성/소멸

CSDIPenView::CSDIPenView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	size = 32;
	col = RGB(0, 255, 0);

}

CSDIPenView::~CSDIPenView()
{
}

BOOL CSDIPenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDIPenView 그리기

void CSDIPenView::OnDraw(CDC* pDC)
{
	CSDIPenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int n = pDoc->m_oa.GetSize();
	CLine* p;
	for (int i = 0; i < n; i++) {
		p = (CLine*)pDoc->m_oa[i];
		p->Draw(pDC);
	}
}


// CSDIPenView 인쇄

BOOL CSDIPenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDIPenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDIPenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSDIPenView 진단

#ifdef _DEBUG
void CSDIPenView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIPenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIPenDoc* CSDIPenView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIPenDoc)));
	return (CSDIPenDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIPenView 메시지 처리기


void CSDIPenView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON) {
		CLine* p = new CLine(pnt, point, size, col);
		GetDocument()->m_oa.Add(p);
		Invalidate(false);
	}
	pnt = point;
	CView::OnMouseMove(nFlags, point);

	
}


void CSDIPenView::OnMenuCol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		col = dlg.GetColor();
	}

}


void CSDIPenView::OnSize1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	size = 1;
}


void CSDIPenView::OnSize16()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	size = 16;
}


void CSDIPenView::OnSize32()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	size = 32;

}
