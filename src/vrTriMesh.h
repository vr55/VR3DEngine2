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

#include "vrInclude.h"
#include "vrCommonStruct.h"

#include "vrTriFace.h"
#include "vrMaterial.h"

//==============================================================//
//																//
//==============================================================//
//Last Edit 12.09.2k5
//


//		OUTOFDATED
//		Ё“ќ“ ‘ј…Ћ ”—“ј–≈Ћ » ЅќЋ№Ў≈ Ќ≈»—ѕќЋ№«”≈“—я

class vrTriMesh2
{
public:

		char		cName[NAME_MAXCHARS];	//им€ меша
		int			iNumSurfaces;			//количество поверхностей
		lp_surface	surfaces;				//поверхности

		int			iID;					//идентификатор

		//на каждую поверхность должен быть свой материал




private:



};
//==============================================================//
//																//
//==============================================================//



class vrTriMesh
{

friend class vrTriObject;

public:/*SUBROUTINES*/
					vrTriMesh();
					~vrTriMesh();
		void		Render( );
		void		CreateBV();				//CreateBoundingVolumes



public:/*VARIABLES*/
		char	cName[32];		//им€

		int		iNumVerts;		//количество точек
		int		iNumFaces;		//количество плоскостей
		int		iNumTVerts;		//количество текстурных координат
		int		iNumNormals;	//количество нормалей
		//количество нормалей равно количеству плоскостей TODO: дл€ плоского освещени€.
																//нужно сделать нормали к каждой точке

		unsigned int	uiID;	//идентификатор, изначально равен -1

private:
		void		RenderBV();
	//	void		SetMaterial( MeshParams param );

private:
		vrTriFace	*faces;		//плоскости
		vrVector3	*verts;		//точки
		vrVector3	*normals;	//нормали
		vrVector3	*tverts;	//текстурные координаты
		vrVector3	AABB[2];	//Bounding Box//чтобы задать BBox нам достаточно знать 2 точки:
								//координаты левого нижнего ближнего угла и проавого верхнего дальнего угла
		vrSphere	BSphere;	//Bounding Sphere


		vrMaterial	material;	//материал
//TODO
//¬ообще по-хорошему материал должен быть назначен дл€ каждой плоскости в отдельности(дл€ каждой точки в плоскости)
//но смена материала при отрисовке в реальном времени вызывает жуткие тормоза
// так что пока материал назначаем всему мешу целиком
};

