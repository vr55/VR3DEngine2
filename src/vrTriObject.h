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


#ifndef __VRTRIOBJECT_H__
#define __VRTRIOBJECT_H__

#include "vrInclude.h"
#include "vrTriMesh.h"
#include "vrCommonStruct.h"
#include "vrGameObject.h"


//Last Edit 10.11.2k5

//==============================================================//
//																//
//==============================================================//
class vrTriObject2
{
public:/*constructor/destructor*/

	vrTriObject2();
	~vrTriObject2();

public: /*subroutines*/

	BOOL	Load( LPSTR strFileName );		//������ ������ �� �����
	BOOL	LoadSkin( LPSTR strfileName );	
	void	Render();						//������ ������
	BOOL	Compile();						//������� ���������� ������
	void	CreateBBox();

	//void	Free();


public:/*variables*/
	char		cName[ NAME_MAXCHARS ];		//��� �������
	int			iID;						//�������������
	int			iNumSurfaces;				//���������� ������������
	lp_surface	surfaces;					//�����������

	vrVector3	center;						//����� ����
	float		width;
	float		height;

	BOOL		bCompiled;					//���� ����������???


	skin*		skin_p;						//���� - ��������� �� ������ ���������� ��� ������ �����������
											//���������� ��������� ����� iNumSurfaces

private:/*subroutines*/


private:
	GLuint	uiRenderList;


};




//					OLD					//
//---------------------------------------
//==============================================================//
//																//
//==============================================================//

class vrTriObject
{

public: /*SUBROUTINES*/
		vrTriObject();								//�����������
		~vrTriObject();								//����������

		bool Load( LPSTR strFileName );				//��������� ������ �� �����
//		void Render( ObjectWrapper *o );			//������ ������ ���������� �� ������ ��������
		int	 MeshCount();							//���������� ���������� ����� � �������

		vrTriMesh*  GetMesh( );						//���������� ��������� �� ���



public: /*VARIABLES*/

		char		cName[32];						//��� �������
		unsigned int uiID;							//�������������


private: /*SUBROUTINES*/

		bool		AddMesh( vrTriMesh *fromMesh );	//��������� ��� � ������ �� ������


private: /*VARIABLES*/

		vrTriMesh					*mesh_p;					//���
		vrErrorLog					eLog;						//���


};



//==============================================================//
//																//
//==============================================================//
#endif