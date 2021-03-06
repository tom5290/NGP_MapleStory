#include "StdAfx.h"
#include "SwingEffect.h"

CSwingEffect::CSwingEffect(void)
{
}

CSwingEffect::~CSwingEffect(void)
{
}

void CSwingEffect::Initialize(void)
{
	m_tInfo.size.cx = 299.f;
	m_tInfo.size.cy = 99.f;

	m_dwFrameOldTime = GetTickCount();
	m_dwFrameCurTime = 0;

	if(DIR_LEFT == m_eDir )
	{
		m_pImgName = L"SwingEffect_LEFT";
	}
	else
	{
		m_pImgName = L"SwingEffect_RIGHT";
	}

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iScene = 0;
	m_tFrame.dwFrameSpd = 150;

	m_eRenderType = RENDER_OBJ;

}

int CSwingEffect::Update(void)
{
	if(DIR_LEFT == m_eDir )	
		m_pImgName = L"SwingEffect_LEFT";
	else
		m_pImgName = L"SwingEffect_RIGHT";

	m_dwFrameCurTime = GetTickCount();

	if(m_dwFrameOldTime + m_tFrame.dwFrameSpd < m_dwFrameCurTime)
	{
		++(m_tFrame.iFrameStart);
		m_dwFrameOldTime = m_dwFrameCurTime;
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		return 1;

	UpdateCollRect();

	CObj::UpdateRect();

	return 0;
}

void CSwingEffect::Render(HDC hDc)
{
	CMyBmp* pBit = CBitmapMgr::GetInstance()->FindImage(m_pImgName);

	if(NULL == pBit)  return;


	TransparentBlt(hDc,
		static_cast<int>(m_tRect.left + g_fScrollX),
		static_cast<int>(m_tRect.top + g_fScrollY), 
		static_cast<int>(m_tInfo.size.cx),
		static_cast<int>(m_tInfo.size.cy),
		pBit->GetMemDC(),
		static_cast<int>(m_tFrame.iFrameStart * m_tInfo.size.cx),
		static_cast<int>(m_tFrame.iScene * m_tInfo.size.cy),
		static_cast<int>(m_tInfo.size.cx),
		static_cast<int>(m_tInfo.size.cy),
		RGB(0, 255, 0));
	// ??Ʈ?ڽ?
	if(GetAsyncKeyState('2'))
	{
		Rectangle(hDc, 
			static_cast<int>(m_tCollRect.left + g_fScrollX),
			static_cast<int>(m_tCollRect.top + g_fScrollY), 
			static_cast<int>(m_tCollRect.right + g_fScrollX),
			static_cast<int>(m_tCollRect.bottom + g_fScrollY));
	}

}

void CSwingEffect::Release(void)
{

}

void CSwingEffect::FrameMove()
{

}

void CSwingEffect::UpdateCollRect()
{
	
	if(DIR_RIGHT == m_eDir)
	{
		m_tCollRect.left = m_tRect.left;
		m_tCollRect.top = m_tRect.top;
		m_tCollRect.bottom = m_tRect.bottom;
		m_tCollRect.right = static_cast<LONG>(m_tInfo.pt.x);
	}
	else
	{
		m_tCollRect.right = m_tRect.right;
		m_tCollRect.top = m_tRect.top;
		m_tCollRect.bottom = m_tRect.bottom;
		m_tCollRect.left = static_cast<LONG>(m_tInfo.pt.x);
	}
}
