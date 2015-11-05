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

#include "vrParticle.h"
//==============================================================//
//																//
//==============================================================//
vrParticleSystem::vrParticleSystem()

{

vMinEmmiterPos = vrVector3( 3010, 105, 3002 );
vMaxEmmiterPos = vrVector3( 3015, 110, 3005 );

fMinLifeTime = 1000;
fMaxLifeTime = 2050;

vMinDeltaPos = vrVector3( 0.0f, 0.0f, 0.0f );
vMaxDeltaPos = vrVector3( 0.0f, 3.0f, 0.0f );

vMinColor = vrVector3( 1.0f, 1.0f, 0.0f );
vMaxColor = vrVector3( 1.0f, 1.0f, 0.0f );

vMinDeltaColor = vrVector3( -0.01f, -0.04f, 0.0f );
vMaxDeltaColor = vrVector3( -0.01f, -0.012f, 0.0f );
  
fMinSize = 1.0f;
fMaxSize = 3.50f;

fAlpha	= 1.0;
fMinDeltaAlpha	= 0.0005f;
fMaxDeltaAlpha	= 0.02f;

uiSrcBlend = GL_SRC_ALPHA;
uiDstBlend = GL_ONE;

rnd.Randomize();
vEmmiterPos = vrVector3( rnd.Rand( vMinEmmiterPos.x, vMaxEmmiterPos.x ), rnd.Rand( vMinEmmiterPos.y, vMaxEmmiterPos.y ), rnd.Rand( vMinEmmiterPos.z, vMaxEmmiterPos.z ));

}
//==============================================================//
//																//
//==============================================================//
BOOL	vrParticleSystem::Create( UINT uiNum )
{
//rnd.Randomize();

//выделяем память под частицы
	particle *p = new particle[ uiNum ];
	if ( !p ) return FALSE;

//задаем параметры частиц
	for ( int i=0; i<uiNum; i++ )
	{
	//	vEmmiterPos = vrVector3( rnd.Rand( vMinEmmiterPos.x, vMaxEmmiterPos.x ), rnd.Rand( vMinEmmiterPos.y, vMaxEmmiterPos.y ), rnd.Rand( vMinEmmiterPos.z, vMaxEmmiterPos.z ));
		ResetParticle( &p[i] );

	}
this->uiNum = uiNum;
this->particles_p = p;

return TRUE;
}
//==============================================================//
//																//
//==============================================================//
void vrParticleSystem::Update()
{
float tick = engine.GetTickCount();

	for ( int i=0; i< uiNum; i++ )
	{

		//если частица отжила свое, сбрасываем ее
		if ( particles_p[i].f_age >= particles_p[i].f_lifetime )  ResetParticle( &particles_p[i] );
		UpdateParticle( &particles_p[i], tick );



	}

}

//==============================================================//
//																//
//==============================================================//

void	vrParticleSystem::UpdateParticle( particle *p, float tick )
{

	p->f_age += tick;	//увеличиваем возраст


	tick/=100;
	p->v_pos += vrVector3( rnd.Rand( vMinDeltaPos.x, vMaxDeltaPos.x )*tick, rnd.Rand( vMinDeltaPos.y, vMaxDeltaPos.y )*tick, rnd.Rand( vMinDeltaPos.z, vMaxDeltaPos.z ) *tick);
	p->f_alpha -= rnd.Rand( fMinDeltaAlpha, fMaxDeltaAlpha ) * tick;

	p->v_color += vrVector3( rnd.Rand(vMinDeltaColor.x, vMaxDeltaColor.x), rnd.Rand(vMinDeltaColor.y, vMaxDeltaColor.y), rnd.Rand(vMinDeltaColor.z, vMaxDeltaColor.z) );



}
	

//==============================================================//
//																//
//==============================================================//
vrParticleSystem::~vrParticleSystem()
{
	if ( particles_p ) delete[] particles_p;
}
//==============================================================//
//																//
//==============================================================//
void vrParticleSystem::Render()
{

glPushAttrib( GL_ALL_ATTRIB_BITS   );

engine.glStoreMatrix( GL_MODELVIEW );
engine.glSetState( GL_TEXTURE_2D, false );
material->Set();

glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

glDisable( GL_LIGHTING );
//glDisable( GL_ALPHA_TEST );

glEnable( GL_BLEND );
glBlendFunc( uiSrcBlend, uiDstBlend ); //correct
//glDisable(GL_DEPTH_TEST);
glDepthMask( GL_FALSE );

//glBegin( GL_TRIANGLE_STRIP );

	for ( int i=0; i<uiNum; i++ )
	{

		glColor4f( particles_p[i].v_color.x, particles_p[i].v_color.y, particles_p[i].v_color.z, particles_p[i].f_alpha );

		RenderParticle( &particles_p[i] );


	}
//glEnd();

engine.glRestoreMatrix( GL_MODELVIEW );
glPopAttrib();

}
//==============================================================//
//																//
//==============================================================//
void vrParticleSystem::ResetParticle( particle *p )
{
if ( p )
{

	p->v_pos		= vrVector3( rnd.Rand( vMinEmmiterPos.x, vMaxEmmiterPos.x ), rnd.Rand( vMinEmmiterPos.y, vMaxEmmiterPos.y ), rnd.Rand( vMinEmmiterPos.z, vMaxEmmiterPos.z ));
	p->f_age		= 0.0f;
	p->f_lifetime	= rnd.Rand( fMinLifeTime, fMaxLifeTime );
	p->f_size		= rnd.Rand( fMinSize, fMaxSize );
	p->v_color		= vrVector3( rnd.Rand( vMinColor.x, vMaxColor.x), rnd.Rand( vMinColor.y, vMaxColor.y), rnd.Rand( vMinColor.z, vMaxColor.z ) );
	p->f_alpha		= fAlpha;



}

}

//==============================================================//
//																//
//==============================================================//
void vrParticleSystem::RenderParticle( particle *p )
{
if ( !p ) return;

//BILLBOARDING
float		mat[16];

glGetFloatv( GL_MODELVIEW_MATRIX, mat );		//get MODELVIEW matrix
vrVector3	v_right ( mat[0], mat[4], mat[8] );		//right
vrVector3	v_up ( mat[1], mat[5], mat[9] );		//up

vrVector3	A, B, C, D;

A = p->v_pos+ ( -v_right - v_up ) * p->f_size;
B = p->v_pos+ ( v_right - v_up ) * p->f_size;
C = p->v_pos+ ( v_right + v_up ) * p->f_size;
D = p->v_pos+ ( -v_right + v_up ) * p->f_size;

glBegin( GL_QUADS );
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( A.x, A.y, A.z );
			
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( B.x, B.y, B.z );

		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( C.x, C.y, C.z );

		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( D.x, D.y, D.z );

glEnd();
//
/*
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( p->v_pos.x-p->f_size, p->v_pos.y-p->f_size, p->v_pos.z );
			
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( p->v_pos.x+p->f_size, p->v_pos.y-p->f_size, p->v_pos.z );

		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( p->v_pos.x+p->f_size, p->v_pos.y+p->f_size, p->v_pos.z );

		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( p->v_pos.x-p->f_size, p->v_pos.y+p->f_size, p->v_pos.z );
*/

}

