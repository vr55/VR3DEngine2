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
	vrVector3		v_pos;		//позиция
	float			f_size;		//размер

	vrVector3		v_color;	//цвет
	float			f_alpha;




	float			f_age;		// текущий возраст в миллисекундах
	float			f_lifetime;	//время жизни

	

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
		void	Render();					//отрисовываем систему
		void	Update();					//обновляем систему
		BOOL	Create( UINT uiNum );		//создаем систему с uiNum частицами


		vrMaterial		*material;			//временно public

		UINT			uiSrcBlend;
		UINT			uiDstBlend;

private:


		vrVector3		vMinEmmiterPos;		//еммитер
		vrVector3		vMaxEmmiterPos;
		vrVector3		vEmmiterPos;

		float			fMinLifeTime;		//время жизни в миллисекундах
		float			fMaxLifeTime;

		vrVector3		vMinDeltaPos;		//изменение позиции
		vrVector3		vMaxDeltaPos;

		float			fMinSize;			//размер
		float			fMaxSize;


		vrVector3		vMinColor;			//цвет
		vrVector3		vMaxColor;
		vrVector3		vMinDeltaColor;		//изменение цвета
		vrVector3		vMaxDeltaColor;

		float			fAlpha;
		float			fMinDeltaAlpha;
		float			fMaxDeltaAlpha;


		void			RenderParticle( particle *p );
		void			ResetParticle( particle *p );
		void			UpdateParticle( particle *p, float tick );

		vrRandom		rnd;


		particle		*particles_p;		//частицы 
		UINT			uiNum;				//количество частиц
		
};