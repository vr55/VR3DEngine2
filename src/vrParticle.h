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
#include "vrBase.h"
#include "vrMaterial.h"
#include "vrRandom.h"
//==============================================================//
//																//
//==============================================================//

//==============================================================//
//																//
//==============================================================//

typedef struct tagParticle
{
	vrVector3		v_pos;		//�������
	float			f_size;		//������

	vrVector3		v_color;	//����
	float			f_alpha;




	float			f_age;		// ������� ������� � �������������
	float			f_lifetime;	//����� �����

	

}particle, *particle_p;


//==============================================================//
//																//
//==============================================================//
//typedef std::vector<vrParticle*> PARTICLELIST;


//==============================================================//
//																//
//==============================================================//

class vrParticleSystem
{

public:
				vrParticleSystem();
				~vrParticleSystem();
		void	Render();					//������������ �������
		void	Update();					//��������� �������
		BOOL	Create( UINT uiNum );		//������� ������� � uiNum ���������


		vrMaterial		*material;			//�������� public

		UINT			uiSrcBlend;
		UINT			uiDstBlend;

private:


		vrVector3		vMinEmmiterPos;		//�������
		vrVector3		vMaxEmmiterPos;
		vrVector3		vEmmiterPos;

		float			fMinLifeTime;		//����� ����� � �������������
		float			fMaxLifeTime;

		vrVector3		vMinDeltaPos;		//��������� �������
		vrVector3		vMaxDeltaPos;

		float			fMinSize;			//������
		float			fMaxSize;


		vrVector3		vMinColor;			//����
		vrVector3		vMaxColor;
		vrVector3		vMinDeltaColor;		//��������� �����
		vrVector3		vMaxDeltaColor;

		float			fAlpha;
		float			fMinDeltaAlpha;
		float			fMaxDeltaAlpha;


		void			RenderParticle( particle *p );
		void			ResetParticle( particle *p );
		void			UpdateParticle( particle *p, float tick );

		vrRandom		rnd;


		particle		*particles_p;		//������� 
		UINT			uiNum;				//���������� ������
		
};