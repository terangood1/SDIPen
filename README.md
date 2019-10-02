# SDIPen
SDIPen Manual
1. Visual Stdio 실행 MFC - 단일문서 - MFC Standard
2. MyDoc.h에서 CObArray m_oa; 멤버변수 추가
3. 클래스뷰에서 SDIPen(솔루션이름)에 우클릭->추가->클래스 클래스 이름 CLine 기본 클래스 CObject -> 확인
4. 클래스뷰에서 CLine.h에 들어가
```c++
class CLine :
	public CObject
{
	DECLARE_SERIAL(CLine)
	CPoint m_From, m_To;
	int m_Size;
	COLORREF m_Col;
public:
	CLine() {}
	CLine(CPoint From, CPoint To,
		int Size, COLORREF Col) {
		m_From = From;
		m_To = To;
		m_Size = Size;
		m_Col = Col;
	}
	void Draw(CDC* pDC) {
		CPen pen(PS_SOLID, m_Size, m_Col);
		pDC->SelectObject(&pen);
		pDC->MoveTo(m_From);
		pDC->LineTo(m_To);
	}
	virtual void Serialize(CArchive& ar);
}; //작성


 5. CLine.cpp에 들어가
#include "pch.h"
#include "CLine.h"

IMPLEMENT_SERIAL(CLine, CObject, 1)
void CLine::Serialize(CArchive& ar)
{
	//CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_From << m_To << m_Size << m_Col;
	}
	else
	{	// loading code
		ar >> m_From >> m_To >> m_Size >> m_Col;
	}
} //작성

5. 클래스뷰에서 CSDIPen(솔루션이름)View 클릭 -> 속성 -> 네번째 탭(메시지) -> WM_MOUSEMOVE를 선택하고 OnMouseMove 활성화
6. SDIPen(솔루션이름)View.cpp에 #include "CLine.h" 헤더파일 추가
7. SDIPen(솔루션이름)View.h에 
CSDIPenDoc* GetDocument() const;
	CPoint pnt;
	int size;
	COLORREF col; // 멤버추가
8. CSDIPenView()에 
size = 32;
col = RGB(0,255,0); // 작성 기본크기와 색상
9. OnMouseMove(UNIT nFlags, CPoint point)에
if (nFlags == MK_LBUTTON) {
		CLine* p = new CLine(pnt, point, size, col);
		GetDocument()->m_oa.Add(p);
		Invalidate(false);
	}
	pnt = point;
	CView::OnMouseMove(nFlags, point); // 작성
  10. 리소스뷰에서 Menu -> IDR_MAINFRAME 더블클릭 도움말 옆에 Menu 입력
  Menu -> col , size 작성 - > size -> 1, 16 , 32 입력
  11 col 우클릭 이벤트 처리기 추가 -> CAboutDlg를 CSDIPen(솔루션이름)View로 변경 -> 확인
  CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		col = dlg.GetColor();
	} // 작성
  12. 1, 16, 32 (size)를 11번과같이 각각 이벤트 처리기 추가 ->
  1은 size = 1; 16은 size = 16; 32는 size = 32; //작성
