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


/*
	Description:
				Main structures and definitions



*/
#ifndef __VRCOMMONSTRUCT_H__
#define __VRCOMMONSTRUCT_H__

#include "vrMaterial.h"
#include <windows.h>  

#define PI (3.1415926535897932)
#define Deg2Rad(a) ((a)*PI/180)
#define Rad2Deg(a) ((a)*180/PI)


#define NAME_MAXCHARS		64

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

typedef struct {	//текстурные координаты

	float u;
	float v;

}st, *lp_st;

//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================

typedef struct {	//RGBA color

	float r;
	float g;
	float b;
	float a;

}rgba, *lp_rgba;
//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================
typedef struct { //вектор

	float x;
	float y;
	float z;
} vec3, *lp_vec3;

typedef struct{
	float x;
	float y;
} vec2, *lp_vec2; 

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

typedef struct { //вертекс

	rgba	color;			//цвет
	vec3	position;		//
	vec3	normal;			//нормаль

}vertex, *lp_vertex;

//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================
typedef struct { //face

	int		vert_index[3];	//индекс вершин
	int		uv_index[3];	//индекс текстурных координат

}face, *lp_face;

//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================
typedef struct { //треугольник

//индексы
	int		vert_index[3];	//индексы вертексов
	int		norm_index[3];	//индексы нормалей
	int		rgb_index[3];	//индексы цвета
	int		st_index[3];	//индексы текстуры


//данные 
	vertex	v[3];			//данные вертексов
	vec3	n[3];			//данные нормалей
	rgba	c[3];			//данные цвета
	st		t[3];			//данные текстуры

/*
для большей гибкости, треугольник может использовать
как индексы данных, так и сам выступать в роли носителя данных
*/
}tri, *lp_tri;

//-------------------------------------------------------------------------
typedef struct {	//ключ анимации

	int		frame;		//номер кадра
	vec3	d_pos;		//изменение позиции
	vec3	d_scl;
	vec3	d_rot;
	float	d_angle;

	bool	b_pos;
	bool	b_rot;
	bool	b_scl;


}animkey, *lp_animkey;


//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================

typedef struct {  //поверхность


	char	name[NAME_MAXCHARS];//имя поверхности
	int		numtriangles;		//количество треугольников
	tri		*triangles;			//треугольники

//всё нижеследующее загружается из файла, 
//затем треугольники строятся по этим данным
	int		numverts;			//количество вершин
	vertex	*verts;				//вершины
	
	int		numfaces;			//количество плоскостей
	face	*faces;				//плоскости

	int		numuv;				//количество текстурных координат
	st		*uv;				//текстурные координаты

	int		numnormals;			//количество нормалей
	vec3	*normals;			//нормали


	GLuint	dlist;				//дисплейный список OpenGL

//GAME EXTENSION
	vec3	pos;				//position
	vec3	wpos;				//world	position
	vec3	bpos;				//начальная позиция

	vec3	axis;				//оси вращения
	vec3	baxis;
	float	angle;				//угол поворота
	float	bangle;
	vec3	scl;				//local scale
	vec3	bscl;
	vec3	pivot;
	vec3	center;
	vec3	min;				//bbox
	vec3	max;
	char	mat_name[NAME_MAXCHARS];	//имя материала

	char	c_parent[64];

	int		numframes;			//количество фреймов анимации
	int		c_frame;			//текущий кадр анимации
	animkey	*frames;			//анимация


	vrMaterial2*	mat;		//указатель на материал

//	bool	isInHierarchy;

} surface, *lp_surface;

//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================

typedef struct { //скин

	vrMaterial2*	materials;		//указатель на материалы для каждой поверхности
	char			*names;			//имена поверхностей


} skin, *lp_skin;
//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================
typedef struct { //

	char		name[NAME_MAXCHARS];
	char		c_parent[64];
//	lp_dummy	parent;
	vec3		pos;
	vec3		axis;
	float		angle;
	vec3		scl;

//	bool		isInHierarchy;




} dummy, *lp_dummy;


#endif