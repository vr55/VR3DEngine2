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
#include "vrMaterial.h"

//==============================================================//
//																//
//==============================================================//
vrMaterial2::vrMaterial2()
{

iNumLayers = 0;
sShader = NULL;
for ( int i=0; i<LAYERS_MAXTEXTURES; i++ ) tLayers[i] = NULL;

}
//==============================================================//
//																//
//==============================================================//
BOOL vrMaterial2::LoadShader( char* vertexFile, char* fragmentFile )
{

sShader = new glShader();
sShader = engine.SM.loadfromFile(vertexFile, fragmentFile );
if ( sShader == 0 ) 
{
	e_log.WriteOut("[ERROR] Unable to Load Shader from File %s or %s\n", vertexFile, fragmentFile );
	//e_log.WriteOut ("[ERROR] Shader Linker Says: %s\n", sShader->getLinkerLog() );
	return FALSE;
}
return TRUE;

}
//==============================================================//
//																//
//==============================================================//
void vrMaterial2::Begin()
{

//for ( int i=0; i<iNumLayers; i++ ) tLayers[i]->Bind();

if ( sShader )
{
	sShader->begin();
	
	sShader->setUniform1i("t0",0 );			//первый слой текстуры
	sShader->setUniform1i("t1",1 );			//второй слой текстуры
	sShader->setUniform1i("t2",2 );			
	sShader->setUniform1i("t3",3 );			

	sShader->setUniform1i("t1scale", 1 );

	glActiveTexture( GL_TEXTURE0 );
	glEnable( GL_TEXTURE_2D );
	if ( tLayers[0] ) tLayers[0]->Bind();
	
	glActiveTexture( GL_TEXTURE1 );
	glEnable( GL_TEXTURE_2D );
	if ( tLayers[1] ) tLayers[1]->Bind();

	glActiveTexture( GL_TEXTURE2 );
	glEnable( GL_TEXTURE_2D );
	if ( tLayers[2] ) tLayers[2]->Bind();

	glActiveTexture( GL_TEXTURE3 );
	glEnable( GL_TEXTURE_2D );
	if ( tLayers[3] ) tLayers[3]->Bind();

	//...и т.д.
}

if ( !sShader ) //если шейдер отсутствует, просто включаем текстурирование
{
//TODO::зделать мултитестурирование без шейдера
	glActiveTexture( GL_TEXTURE0 );
	glEnable( GL_TEXTURE_2D );
	if ( tLayers[0] ) { /*glColor3f( 1.0f, 1.0f, 1.0f );*/ tLayers[0]->Bind();}

	glActiveTexture( GL_TEXTURE1 );
	glDisable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, 0 );

	glActiveTexture( GL_TEXTURE2 );
	glDisable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, 0 );

	glActiveTexture( GL_TEXTURE3 );
	glDisable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, 0 );



}


}
//==============================================================//
//																//
//==============================================================//
void vrMaterial2::End()
{
if ( sShader ) sShader->end();

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, 0 );


//сбрасываем униформы
	if ( sShader ) 	sShader->setUniform1i("t1scale", 1 );


}
//==============================================================//
//																//
//==============================================================//
//==============================================================//
//																//
//==============================================================//
//==============================================================//
//																//
//==============================================================//
//==============================================================//
//																//
//==============================================================//

//				OLD				//
//------------------------------//
vrMaterial::vrMaterial()
{

	tDiffuse	= NULL;	
	tDetail		= NULL;
	tBump		= NULL;
	vrVector3	v( 1.0f, 1.0f, 1.0f );
	vDiffuseScale		= v;
	vDiffuseTranslate	= v;
	vDiffuseRotate		= v;

	vDetailScale		= v;
	vDetailTranslate	= v;
	vDetailRotate		= v;

	vAmbient			= v;
	vDiffuse			= v;
	vSpecular			= v;
	fBlend				= 1.0f;
	bAlphaTest			= FALSE;

	iDiffuseGenMode		= VR_TEXG_NONE;
	iDetailGenMode		= VR_TEXG_NONE;


}


//==============================================================//
//																//
//==============================================================//

void vrMaterial::Set( void )
{

glMatrixMode( GL_TEXTURE );
//glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, (const float*)&vAmbient ); //чего-та € здесь неуверен!!!
//glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, (const float*)&vDiffuse );
//glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, (const float*)&vSpecular );
//glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, (const float*)&vEmission );

//отключает текстурирование
engine.glActiveTexture( GL_TEXTURE0_ARB );
engine.glSetState( GL_TEXTURE_2D, false );

engine.glActiveTexture( GL_TEXTURE1_ARB );
engine.glSetState( GL_TEXTURE_2D, false );


if ( tDiffuse ) //tDiffuse->Bind();
{

	engine.glActiveTexture( GL_TEXTURE0_ARB );
	engine.glSetState( GL_TEXTURE_2D, true );

	engine.glSetState( GL_TEXTURE_GEN_S, false );//выключаем автоматическую генерацию текстурных координат
	engine.glSetState( GL_TEXTURE_GEN_T, false );

	engine.glSetState( GL_BLEND, false );

	tDiffuse->Bind();

	glLoadIdentity();
	glTranslatef( vDiffuseTranslate.x, vDiffuseTranslate.y, vDiffuseTranslate.z );
	glScalef( vDiffuseScale.x, vDiffuseScale.y, vDiffuseScale.z );

if ( tDetail )//если есть детальна€ текстура, включаем режим смешивани€
{
	glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT );
	glTexEnvf ( GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE );
}
else glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

//ѕрозрачность
	if ( fBlend != 1.0f )
	{
		engine.glSetState( GL_BLEND, true );
	//	glBlendFunc( GL_DST_COLOR, GL_SRC_ALPHA );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		glColor4f( 1.0, 1.0, 1.0, fBlend );
	}
if ( bAlphaTest )	{ glEnable( GL_ALPHA_TEST ); glAlphaFunc( GL_GREATER, 0.5f );}

else				glDisable( GL_ALPHA_TEST );




	
//јвтоматическа€ генераци€ текстурных координат
	if ( iDiffuseGenMode != VR_TEXG_NONE )
	{
//		glEnable( GL_TEXTURE_GEN_S );	//включаем автоматическую генерацию текстурных координат
//		glEnable( GL_TEXTURE_GEN_T );

		engine.glSetState( GL_TEXTURE_GEN_S, true );
		engine.glSetState( GL_TEXTURE_GEN_T, true );

		switch( (int)iDiffuseGenMode )
		{
		case VR_TEXG_OBJECT_LINEAR:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
			break;
			}
		case VR_TEXG_EYE_LINEAR:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );			
			break;
			}
		case VR_TEXG_REFLECTION_MAP:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV );			
			break;
			}
		case VR_TEXG_SPHERE_MAP:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );			
			break;
			}
		case VR_TEXG_NORMAL_MAP:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT );			
			break;
			}

		}



	}

}


if ( tDetail )
{

	engine.glActiveTexture( GL_TEXTURE1_ARB );
	engine.glSetState( GL_TEXTURE_2D, true );

	glDisable( GL_TEXTURE_GEN_S );	//включаем автоматическую генерацию текстурных координат
	glDisable( GL_TEXTURE_GEN_T );



	tDetail->Bind();
	glLoadIdentity();
	glTranslatef( vDetailTranslate.x, vDetailTranslate.y, vDetailTranslate.z );
	glScalef( vDetailScale.x, vDetailScale.y, vDetailScale.z );


	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT );
	glTexEnvi( GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2 );
	glTexEnvf( GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, 2 );


	if ( iDetailGenMode != VR_TEXG_NONE )
	{
		glEnable( GL_TEXTURE_GEN_S );	//включаем автоматическую генерацию текстурных координат
		glEnable( GL_TEXTURE_GEN_T );


		switch( (int)iDetailGenMode )
		{
		case VR_TEXG_OBJECT_LINEAR:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
			break;
			}
		case VR_TEXG_EYE_LINEAR:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR );			
			break;
			}
		case VR_TEXG_REFLECTION_MAP:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV );			
			break;
			}
		case VR_TEXG_SPHERE_MAP:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );			
			break;
			}
		case VR_TEXG_NORMAL_MAP:
			{
			glTexGenf( GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT );
			glTexGenf( GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT );			
			break;
			}

		}



	}


}
//glMatrixMode( mode );
//glPopMatrix();

}


//==============================================================//
//																//
//==============================================================//

void vrMaterial::UnSet()
{

if ( tDiffuse ) tDiffuse->UnBind();
if ( tDetail ) tDetail->UnBind();

}