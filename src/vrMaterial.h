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


#ifndef __VRMATERIAL_H__
#define __VRMATERIAL_H__

#include "vrInclude.h"

//#include "vrVector.h"
#include "vrBase.h"
//#include "vrCommonStruct.h"
#include "vrTexture.h"


#define			VR_TEXG_NONE			0
#define			VR_TEXG_SPHERE_MAP		1	
#define			VR_TEXG_REFLECTION_MAP	2
#define			VR_TEXG_EYE_LINEAR		3
#define			VR_TEXG_OBJECT_LINEAR	4
#define			VR_TEXG_NORMAL_MAP		5					


#define LAYERS_MAXTEXTURES	4			//������������ ���������� ���������� ����� � ���������	

//==============================================================//
//																//
//==============================================================//

class vrMaterial2
{

public:
	vrMaterial2();

	char		cName[64];			//��� ���������
	int			iNumLayers;						//���������� �����
	vrTexture	*tLayers[LAYERS_MAXTEXTURES];	//���������� ����. ���������� ������� �� GL_MAX
	glShader	*sShader;						//������


	BOOL	LoadShader( char* vertexFile, char* fragmentFile );
	void	Begin();
	void	End();


};
//==============================================================//
//																//
//==============================================================//


class vrMaterial
{


public: /*SUBROUTINES*/
		vrMaterial();
		void Set( void );
		void UnSet();




public: /*VARIABLES*/

		char		cName[32]; //��� ���������

//����
		vrVector3	vAmbient;
		vrVector3	vDiffuse;
		vrVector3	vSpecular;
		vrVector3	vEmission;
		float		fShininess;
		float		fBlend;			//����������� ������������
		BOOL		bAlphaTest;		//
//0 - VR_TEXG_NONE, 1 - VR_TEXG_SPHERE_MAP, 2 - VR_TEXG_REFLECTION_MAP, 3 - VR_TEXG_EYE_LINEAR, 4 - VR_TEXG_OBJECT_LINEAR
		//float		fLODBias;		//������� ����������� Mip-Map ���� 


		//��������

		vrTexture*	tDiffuse;		//��������� �� ����� ���������� ���������
		int			iDiffuseGenMode;
		vrVector3	vDiffuseScale;
		vrVector3	vDiffuseTranslate;
		vrVector3	vDiffuseRotate;

//DEATIL MAP
		vrTexture*	tDetail;
		int			iDetailGenMode;
		vrVector3	vDetailScale;
		vrVector3	vDetailTranslate;
		vrVector3	vDetailRotate;



//BUMP MAP;
		vrTexture*	tBump;

//environment map
//ENV MAP
//		vrTexture*	tEnv;


private: /*SUBROUTINES*/



private: /*VARIABLES*/

};


#endif