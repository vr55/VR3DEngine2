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

//Last Edit 4.10.2k5

#include "vrTriObject.h"
#include "vrWorld.h"

//==============================================================//
//																//
//==============================================================//
vrTriObject2::vrTriObject2()
{

	iID				= -1;
	iNumSurfaces	= 0;
	surfaces		= NULL;
	skin_p			= NULL;
	bCompiled		= FALSE;
	ZeroMemory( &cName, sizeof( cName ) );


}
//==============================================================//
//																//
//==============================================================//
vrTriObject2::~vrTriObject2()
{
	for ( int i=0; i<iNumSurfaces; i++ )
	{

		if( surfaces[i].verts )		delete[] surfaces[i].verts;
		if( surfaces[i].faces )		delete[] surfaces[i].faces;
		if( surfaces[i].uv )		delete[] surfaces[i].uv;
		if( surfaces[i].normals )	delete[] surfaces[i].normals;
		if ( surfaces[i].triangles)	delete[] surfaces[i].triangles;


	}
	if ( surfaces )	delete[] surfaces;

	bCompiled = FALSE;


}
//==============================================================//
//																//
//==============================================================//
BOOL vrTriObject2::Load( LPSTR strFileName )/*Load ASCII*/
{

	char			buffer[255];
	char			dummy[255];
        char                    dummy1[255];

	int				i1, i2, i3, i4, i5, i6;
	float			f1, f2, f3;

e_log.WriteOut("[STATUS] Loading Object: %s \n", strFileName );

	FILE *f = fopen ( strFileName, "rt" );
	if ( f == NULL ) 
	{
#ifdef _DEBUG
		MessageBox(engine.hWindowHandle, "ERROR Loading Data File","ERROR", MB_ICONERROR);
#endif
		return FALSE;
	}
//читаем заголовок
	fgets( buffer, 255, f );
	if ( strcmp( "VR26 ASCII\n", buffer ) != 0 ) return FALSE;

//грузим объект

//ERROR!!!!для Builder'а такое не годится
	fscanf( f, "%s %s %s", dummy, buffer, dummy1 );


	strcpy( cName, buffer );			//имя объекта
	fscanf( f, "%s %i", dummy, &i1 );	//количество поверхностей
	iNumSurfaces = i1;

	//создаем поверхности

		surfaces = (surface*)malloc( i1 * sizeof( surface ) );
		if ( surfaces == NULL ) return FALSE;
		ZeroMemory( surfaces, i1 * sizeof( surface ) );

		for ( int j=0; j<iNumSurfaces; j++ )
		{
//получаем указатель на поверхность
			surface *s_ptr = &surfaces[j];
//имя поверхности
			fscanf( f, "%s %s", dummy, buffer );
			strcpy( s_ptr->name, buffer );

//пропускаем строку
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );

//количество вертексов
			fscanf( f, "%s %i", dummy, &i1 );
			s_ptr->numverts = i1;

//создаем массив вертексов
			vertex *v_array = (vertex*)malloc( i1 * sizeof(vertex) );
			if ( v_array == NULL ) return FALSE;
			s_ptr->verts = v_array;

			fgets( dummy, 255, f );

//читаем вершины
			for ( int i=0; i<s_ptr->numverts; i++ )
			{
				fscanf( f, "%f %f %f", &f1, &f2, &f3 );
				//координаты
				v_array[i].position.x = f1;
				v_array[i].position.y = f2;
				v_array[i].position.z = f3;
				//цвет
				//неиспользуется, ставим в нуль
				v_array[i].color.r = 0.0f;
				v_array[i].color.g = 0.0f;
				v_array[i].color.b = 0.0f;
				//нормаль к точке
				//будет вычислина в дальнейшем
				v_array[i].normal.x = 0.0f;
				v_array[i].normal.y = 0.0f;
				v_array[i].normal.z = 0.0f;


			}
//пропускаем строки
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );
//плоскости
			fscanf( f, "%s %i", dummy, &i1 );
//создаем массив плоскостей
			s_ptr->faces = (face*)malloc( i1 * sizeof( face ) );
			if( s_ptr->faces == NULL ) return NULL;
			ZeroMemory( s_ptr->faces, i1 * sizeof( face ) );

			s_ptr->numfaces = i1;

//читаем фейсы
			fgets( dummy, 255, f );

			for ( i=0; i<s_ptr->numfaces; i++ )
			{
//WARNING!!!
//небольшая лажа
//нумерация фейсов начинается с 1, а элементов массива с 0, поэтому делаем -1
				fscanf( f, "%i %i %i %i %i %i", &i1, &i2, &i3, &i4, &i5, &i6 );
				s_ptr->faces[i].vert_index[0] = i1 - 1;
				s_ptr->faces[i].vert_index[1] = i2 - 1;
				s_ptr->faces[i].vert_index[2] = i3 - 1;

				s_ptr->faces[i].uv_index[0] = i4 - 1;
				s_ptr->faces[i].uv_index[1] = i5 - 1;
				s_ptr->faces[i].uv_index[2] = i6 - 1;



			}
//пропускаем строки
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );

//текстурные координаты
			fscanf( f, "%s %i", dummy, &i1 );
//выделяем память под текстурные координаты
			s_ptr->uv = (st*)malloc( i1 * sizeof( st ) );
			if ( s_ptr->uv == NULL ) return FALSE;
			ZeroMemory( s_ptr->uv,  i1 * sizeof( st ) );

			s_ptr->numuv = i1;

//читаем текстурные координаты
			fgets( dummy, 255, f );

			for ( i=0; i<s_ptr->numuv; i++ )
			{
				
				fscanf( f, "%f %f", &f1, &f2 );
				s_ptr->uv[i].u = f1;
				s_ptr->uv[i].v = f2;

			}


//пропускаем строки
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );

//нормали к плоскостям
			fscanf( f, "%s %i", dummy, &i1 );
//выделяем память
			s_ptr->normals = (vec3*)malloc( i1 * sizeof( vec3 ) );
			if( s_ptr->normals == NULL ) return FALSE;
			ZeroMemory( s_ptr->normals, i1 * sizeof( vec3 ) );

			s_ptr->numnormals = i1;

//читаем нормали
			fgets( dummy, 255, f );

			for (  i=0; i<s_ptr->numnormals; i++ )
			{
				fscanf( f, "%f %f %f", &f1, &f2, &f3 );
				s_ptr->normals[i].x = f1;
				s_ptr->normals[i].y = f2;
				s_ptr->normals[i].z = f3;


			}

			fgets( dummy, 255, f );
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );
			fgets( dummy, 255, f );

}
	fclose( f );


	CreateBBox();
//	Compile();

return TRUE;
}
//==============================================================//
//																//
//==============================================================//
BOOL vrTriObject2::LoadSkin( LPSTR strFileName )
{
char	buffer[512];
char	dummy[255];
int		j = 0;

FILE *f = fopen(strFileName, "rt" );
if ( f == NULL ) return FALSE;

while ( strstr( buffer, "<skin>\n") == NULL ) fgets( (char*)buffer, 255, f );

//нашли начало тега
//данные объекта уже должны быть загружены,
//поэтому количество плоскостей можно взять оттуда

//создаем skin
skin_p = new skin;

//создаем массив имен 
skin_p->names = new char[ iNumSurfaces ];//BUGS BUGS!!!!!!!
//создаем массив указателей на материалы. [материалы должны быть уже загружены]
skin_p->materials = new vrMaterial2[iNumSurfaces];

for ( int i=0; i<iNumSurfaces; i++ ) skin_p->names[i] = NULL;
//for ( i=0; i<iNumSurfaces; i++ ) skin_p->materials[i] = NULL;

while ( !feof(f) )
{
	if ( j >= iNumSurfaces ) break;	//если слоев в скине больше чем в объекте то выходим из цикла
	while( strstr( buffer, "surface" ) == NULL ) fscanf(f, "%s %s", buffer, dummy );

	skin_p->names[j] = (char)malloc( strlen(dummy) *sizeof(char));
	strcpy( &skin_p->names[j], dummy );

	while( strstr( buffer, "material" ) == NULL ) fscanf(f, "%s %s", buffer, dummy );
	vrMaterial2 *m = world.r_mgr->GetMaterial( dummy );
	if ( m ) skin_p->materials[j] = *m; //else skin_p->materials[j] = NULL;
j++;

}
fclose(f);
return TRUE;

}

//==============================================================//
//																//
//==============================================================//
//DONE::функция Compile должна создавать дисплейный список[DONE]

BOOL vrTriObject2::Compile()
{

lp_surface	s;

for ( int i=0; i<iNumSurfaces; i++ )
{
	if (surfaces) s = &surfaces[i];
	if ( !s ) return FALSE;

	s->dlist = glGenLists(1);	//создаем дисплейный список

glNewList( s->dlist, GL_COMPILE );//Begin List
//------------------------
	glEnable( GL_TEXTURE_2D );
	skin_p->materials[i].Begin();
	glBegin( GL_TRIANGLES );

		for( int j=0; j<s->numfaces; j++ )
		{
			int a = s->faces[j].vert_index[0];
			int b = s->faces[j].vert_index[1];
			int c = s->faces[j].vert_index[2];

			int	at = s->faces[j].uv_index[0];
			int bt = s->faces[j].uv_index[1];
			int	ct = s->faces[j].uv_index[2];

			glMultiTexCoord2fv( GL_TEXTURE0, &s->uv[at].u );
			glVertex3fv( &s->verts[a].position.x );

			glMultiTexCoord2fv( GL_TEXTURE0, &s->uv[bt].u );
			glVertex3fv( &s->verts[b].position.x );

			glMultiTexCoord2fv( GL_TEXTURE0, &s->uv[ct].u );
			glVertex3fv( &s->verts[c].position.x );



		}

	glEnd();
	skin_p->materials[i].End();
//------------------------
glEndList();//End List


}




bCompiled = TRUE;
return TRUE;
}

//==============================================================//
//																//
//==============================================================//

void vrTriObject2::CreateBBox()
{
vrVector3 temp;
int count = 0;

vrVector3 min, max;

for ( int i=0; i<iNumSurfaces; i++ )
{
	lp_surface s = &surfaces[i];

	for( int j=0; j<s->numverts; j++ )
		{
//			int a = s->faces[j].vert_index[0];
//			int b = s->faces[j].vert_index[1];
//			int c = s->faces[j].vert_index[2];

			if ( s->verts[j].position.x > max.x ) max.x = s->verts[j].position.x;
			if ( s->verts[j].position.y > max.y ) max.y = s->verts[j].position.y;
			if ( s->verts[j].position.z > max.z ) max.z = s->verts[j].position.z;

			if ( s->verts[j].position.x < min.x ) min.x = s->verts[j].position.x;
			if ( s->verts[j].position.y < min.y ) min.y = s->verts[j].position.y;
			if ( s->verts[j].position.z < min.z ) min.z = s->verts[j].position.z;



			temp += vrVector3( (float)s->verts[j].position.x,  (float)s->verts[j].position.y, (float)s->verts[j].position.z );
			count ++;

	}


}

width = sqrt((max.x - min.x)*(max.x - min.x));
height = sqrt(( max.y - min.y )*( max.y - min.y ));
this->center = temp/count;


}
//==============================================================//
//																//
//==============================================================//
void vrTriObject2::Render()
{

for ( int i=0; i<iNumSurfaces; i++ )
{
	lp_surface s = &surfaces[i];

if ( bCompiled ) glCallList( s->dlist );//используем дисплейный список, если доступно
else
{

	glEnable( GL_TEXTURE_2D );
	skin_p->materials[i].Begin();
	glBegin( GL_TRIANGLES );

		for( int j=0; j<s->numfaces; j++ )
		{
			int a = s->faces[j].vert_index[0];
			int b = s->faces[j].vert_index[1];
			int c = s->faces[j].vert_index[2];

			int	at = s->faces[j].uv_index[0];
			int bt = s->faces[j].uv_index[1];
			int	ct = s->faces[j].uv_index[2];

			glMultiTexCoord2fv( GL_TEXTURE0, &s->uv[at].u );
			glNormal3fv( &s->normals[a].x );
			glVertex3fv( &s->verts[a].position.x );

			glMultiTexCoord2fv( GL_TEXTURE0, &s->uv[bt].u );
			glNormal3fv( &s->normals[b].x );
			glVertex3fv( &s->verts[b].position.x );

			glMultiTexCoord2fv( GL_TEXTURE0, &s->uv[ct].u );
			glNormal3fv( &s->normals[c].x );
			glVertex3fv( &s->verts[c].position.x );
		}

	glEnd();
	skin_p->materials[i].End();
}


}


}
//==============================================================//
//																//
//==============================================================//
//						OLD CODE
//==============================================================//
//																//
//==============================================================//

vrTriObject::vrTriObject()
{

uiID		= -1;

mesh_p		= NULL;

/*
scale.x = scale.y = scale.z = 1.0f;
rotation.x = rotation.y = rotation.z = 1.0f;
position.x = position.y = position.z = 1.0f;
*/

eLog.Create( LOG_FILE_PATH );


}


//==============================================================//
//																//
//==============================================================//

vrTriObject::~vrTriObject()
{


if ( mesh_p ) delete[] mesh_p;
}


//==============================================================//
//																//
//==============================================================//

bool vrTriObject::Load( LPSTR strFileName )
{

HANDLE		h;
VROHeader2	header;
VROMesh		meshheader;
DWORD		read;
int			chunkcount = 0;
char		chunkid[4];


eLog.WriteOut( "Loading Objects From File %s",  strFileName );

//открываем файл
h = CreateFile( strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0 );

if ( h == INVALID_HANDLE_VALUE ) 
{

	eLog.WriteOut( "\tERROR!!! NOT FOUND\n" );
	return false;

}
//читаем заголовок

if ( !ReadFile( h, &header, sizeof( header ), &read, NULL ) ) return false;

//проверяем корректность файла
//if ( strncmp( header.magic, "VRO2", 4 ) != 0 ) 
if ( strncmp( header.magic, "VR26", 4 ) != 0 ) //версия 2.6
{

	eLog.WriteOut( "\tIncorect Data File %s\n",  strFileName );
	eLog.WriteOut( "\tERROR\n" );
	return false;

}

//имя объекта
//ExtractFilenameFromPath( (char*)header.name );
//strncpy( this->cName, header.name , 32 );
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^-ну это вообще полная фигня!!!
//имя объекта задается менеджером ресурсов


chunkcount = header.numofchunk;			//количество секций в файле

DWORD *chunkoffset = new DWORD[ chunkcount ];

//читаем массив смещений к секциям
if ( !ReadFile( h, chunkoffset, chunkcount * sizeof( DWORD ), &read, NULL ) ) return false;

eLog.WriteOut( "\n\t%i Sections in File\n", chunkcount );

//проходим по всем секциям
for ( int i=0; i<chunkcount; i++ )
{

	//ставим указатель	
	if ( SetFilePointer( h, chunkoffset[i], NULL, FILE_BEGIN ) == 0xFFFFFFFF ) continue;

	//читаем идентификатор секции
	if ( !ReadFile( h, &chunkid, sizeof( chunkid ), &read, NULL ) ) return false;

	if ( strncmp( chunkid, "VROM", 4) == 0 )		//если чанк mesh
	{

		eLog.WriteOut( "\tLoading Section 'MESH'...\n" );

		//читаем заголовок чанка
		SetFilePointer( h, chunkoffset[i], NULL, FILE_BEGIN );
		ReadFile( h, &meshheader, sizeof( meshheader ), &read, NULL );
		if ( read != sizeof( meshheader ) ) return false;

		//создаем новый меш
		vrTriMesh *mesh = new vrTriMesh;

		strncpy( mesh->cName, meshheader.name, 32 );
		mesh->iNumVerts		= meshheader.iNumVerts;
		mesh->iNumFaces		= meshheader.iNumFaces;
		mesh->iNumTVerts	= meshheader.iNumTVerts;
		mesh->iNumNormals	= meshheader.iNumNormals;


		eLog.WriteOut( "\t\tName: %s\n",		mesh->cName );
		eLog.WriteOut( "\t\tVerteces: %i\n",	mesh->iNumVerts );
		eLog.WriteOut( "\t\tFaces: %i\n",		mesh->iNumFaces );
		eLog.WriteOut( "\t\tTVerteces: %i\n",	mesh->iNumTVerts );
		eLog.WriteOut( "\t\tNormals: %i\n",		mesh->iNumNormals );


		//создаем новый массив плоскостей и читаем данные плоскостей из файла
		vrTriFace *faces = new vrTriFace[ mesh->iNumFaces ];
		if ( ReadFile( h, faces, mesh->iNumFaces * sizeof( vrTriFace ), &read, NULL ) ) mesh->faces = faces;

		//создаем новый массив нормалей и читаем данные нормалей из файла
		vrVector3 *normals = new vrVector3[ mesh->iNumNormals ];
		if ( ReadFile ( h, normals, mesh->iNumNormals * sizeof( vrVector3 ), &read, NULL ) ) mesh->normals = normals;


		//создаем новый массив точек и читаем данные точек из файла
		vrVector3 *verts = new vrVector3[ mesh->iNumVerts ];
		if ( ReadFile( h, verts, mesh->iNumVerts * sizeof( vrVector3 ), &read, NULL ) ) mesh->verts = verts;

		//создаем новый массив нормалей и читаем данные нормалей из файла
//		vrVector3 *normals = new vrVector3[ mesh->iNumFaces ];
//		if ( ReadFile( h, normals, mesh->iNumFaces * sizeof( vrVector3 ), &read, NULL ) ) mesh->normals = normals;

		//создаем новый массив текстурных координат и читаем данные текстурных координат из файла
		vrVector3 *tverts = new vrVector3[ mesh->iNumTVerts ];
		if ( ReadFile( h, tverts, mesh->iNumTVerts * sizeof( vrVector3 ), &read, NULL ) ) mesh->tverts = tverts;

		if (!this->AddMesh( mesh ))
		{
			eLog.WriteOut( "\tERROR\n" );
			return false;
		}

		mesh->CreateBV();
		eLog.WriteOut( "\tSection Loaded\n" );

	}

}

eLog.WriteOut( "File Loaded\n\n" );


return true;
}

//==============================================================//
//																//
//==============================================================//


bool vrTriObject::AddMesh( vrTriMesh *fromMesh )
{

if ( !fromMesh ) return false;


/*	this->uiID = ml->size();
	ml->insert( ml->end(), fromMesh );
*/
	this->mesh_p = fromMesh;

	ToUpperCase( fromMesh->cName );

	return true;


}

//==============================================================//
//																//
//==============================================================//
vrTriMesh* vrTriObject::GetMesh()
{

if ( mesh_p ) return mesh_p;

return NULL;

}

//==============================================================//
//																//
//==============================================================//
/*
void vrTriObject::Render( ObjectWrapper *o )
{

int				index = 0;


//engine.glSetState( GL_TEXTURE_2D, true );

//glLoadIdentity();
engine.glStoreMatrix( GL_TEXTURE );
if ( o->material ) o->material->Set();


engine.glStoreMatrix( GL_MODELVIEW );
//glLoadIdentity();

glTranslatef( o->vTranslate.x, o->vTranslate.y, o->vTranslate.z );
glScalef( o->vScale.x, o->vScale.y, o->vScale.z );
glRotatef( o->vRotate.x, 1, 0, 0 );
glRotatef( o->vRotate.y, 0, 1, 0 );
glRotatef( o->vRotate.z, 0, 0, 1 );



if ( mesh_p != NULL ) mesh_p->Render( );


engine.glRestoreMatrix( GL_TEXTURE );
engine.glRestoreMatrix( GL_MODELVIEW );


}
*/

//==============================================================//
//																//
//==============================================================//

int vrTriObject::MeshCount()
{

	return 1;

}