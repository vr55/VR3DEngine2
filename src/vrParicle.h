/*
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free
	Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#pragma once
#include <vector>

#include "vrVector.h"
//==============================================================//
//																//
//==============================================================//
typedef std::vector<vrParticle*> PARTICLELIST;


//==============================================================//
//																//
//==============================================================//

class vrParticleSystem
{

public:
				vrParticleSystem();
//				~vrParticleSystem();
//		void	Render();
//		void	Update();
//		void	AddParticle( UINT uiNum );

private:
		PARTICLELIST	*particles_p;

};
//==============================================================//
//																//
//==============================================================//




class vrParticle
{
public:

	void	Render();
	void	Update();
	void	Reset();




private:
	vrVector3		vPos;			//������� ������� �������
	vrVector3		vStartPos;		//��������� �������
	vrVector3		vDeltaPosMin;	//����������� � ������������ ��������� �������
	vrVector3		vDeltaPosMax;	//���� �������, �� ���������� �������� �� ������� ����������


	float			fSize;			//������� ������
	float			fStartSize;		//��������� ������
	float			fDeltaSizeMin;	//��������� �������
	float			fDeltaSizeMax;

	float			fAlpha;			//������� ������������
	float			fStartAlpha;	//��������� ������������
	float			fDeltaAlphaMin;	//��������� ������������
	float			fDeltaAlphaMax;

	vrVector3		vColor;			//������� ����
	vrVector3		vStartColor;	//��������� ����
	vrVector3		vDeltaColorMin;
	vrVector3		vDeltaColorMax;



	float			fLifeTime;	//����� �����
	float			fAge;		//������� ������




};

//==============================================================//
//																//
//==============================================================//
