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

typedef struct {	//���������� ����������

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
typedef struct { //������

	float x;
	float y;
	float z;
} vec3, *lp_vec3;

typedef struct{
	float x;
	float y;
} vec2, *lp_vec2; 

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

typedef struct { //�������

	rgba	color;			//����
	vec3	position;		//
	vec3	normal;			//�������

}vertex, *lp_vertex;

//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================
typedef struct { //face

	int		vert_index[3];	//������ ������
	int		uv_index[3];	//������ ���������� ���������

}face, *lp_face;

//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================
typedef struct { //�����������

//�������
	int		vert_index[3];	//������� ���������
	int		norm_index[3];	//������� ��������
	int		rgb_index[3];	//������� �����
	int		st_index[3];	//������� ��������


//������ 
	vertex	v[3];			//������ ���������
	vec3	n[3];			//������ ��������
	rgba	c[3];			//������ �����
	st		t[3];			//������ ��������

/*
��� ������� ��������, ����������� ����� ������������
��� ������� ������, ��� � ��� ��������� � ���� �������� ������
*/
}tri, *lp_tri;

//-------------------------------------------------------------------------
typedef struct {	//���� ��������

	int		frame;		//����� �����
	vec3	d_pos;		//��������� �������
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

typedef struct {  //�����������


	char	name[NAME_MAXCHARS];//��� �����������
	int		numtriangles;		//���������� �������������
	tri		*triangles;			//������������

//�� ������������� ����������� �� �����, 
//����� ������������ �������� �� ���� ������
	int		numverts;			//���������� ������
	vertex	*verts;				//�������
	
	int		numfaces;			//���������� ����������
	face	*faces;				//���������

	int		numuv;				//���������� ���������� ���������
	st		*uv;				//���������� ����������

	int		numnormals;			//���������� ��������
	vec3	*normals;			//�������


	GLuint	dlist;				//���������� ������ OpenGL

//GAME EXTENSION
	vec3	pos;				//position
	vec3	wpos;				//world	position
	vec3	bpos;				//��������� �������

	vec3	axis;				//��� ��������
	vec3	baxis;
	float	angle;				//���� ��������
	float	bangle;
	vec3	scl;				//local scale
	vec3	bscl;
	vec3	pivot;
	vec3	center;
	vec3	min;				//bbox
	vec3	max;
	char	mat_name[NAME_MAXCHARS];	//��� ���������

	char	c_parent[64];

	int		numframes;			//���������� ������� ��������
	int		c_frame;			//������� ���� ��������
	animkey	*frames;			//��������


	vrMaterial2*	mat;		//��������� �� ��������

//	bool	isInHierarchy;

} surface, *lp_surface;

//-------------------------------------------------------------------------
//_________________________________________________________________________
//=========================================================================

typedef struct { //����

	vrMaterial2*	materials;		//��������� �� ��������� ��� ������ �����������
	char			*names;			//����� ������������


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