#include "vrTextureManager.h"


//==============================================================//
//																//
//==============================================================//

bool vrTextureManager::Create( )
{


tl = new TEXTURELIST();
//iCount = 0;


return true;
}


//==============================================================//
//			�����������											//
//==============================================================//

vrTextureManager::vrTextureManager()
{


}


//==============================================================//
//																//
//==============================================================//
vrTextureManager::~vrTextureManager()

{

TEXTURELIST::iterator j,i=tl->begin(), e = tl->end();

vrTexture *texture;

	while( i!=e )
	{

		texture = *i;
	
		if ( texture != NULL ) delete[] texture;

		i++;
	}


}


//==============================================================//
//		��������� ��������										//
//==============================================================//
bool vrTextureManager::Add( vrTexture *texture )
{

if ( !texture ) return false;

tl->insert( tl->end(), texture );

//texture->uiID = iCount;
//iCount++;
return true;
}


//==============================================================//
//																//
//==============================================================//
bool vrTextureManager::Add( LPSTR strFileName )
{

//...............................................................//
//#ifdef _VR_DEBUG
	//assert( strFileName );
//#endif
//...............................................................//

//TODO �������� ���������, ������-�� ��������� ���������� ������� ����� � ������ strFileName
vrTexture			*texture = new vrTexture;

if ( !texture->LoadFromFile( strFileName ) ) return false;


tl->insert( tl->end(), texture );

//texture->uiID = iCount;
//iCount++;
return true;


}
//==============================================================//
//	���������� ��������� �� �������� �� � �����				//
//==============================================================//

vrTexture* vrTextureManager::Get( LPSTR strTextureName )
{

ToUpperCase( strTextureName );

TEXTURELIST::iterator j,i=tl->begin(), e = tl->end();

vrTexture *texture;

while( i!=e )
	{

		texture = *i;
		if ( strncmp( texture->cName, strTextureName , 32 ) == 0 ) return texture;
		i++;
	}
return NULL;

}




//==============================================================//
//	������� �������� �� ������									//
//==============================================================//
void	vrTextureManager::Remove( LPSTR strTextureName )
{

ToUpperCase( strTextureName );

TEXTURELIST::iterator j,i=tl->begin(), e = tl->end();

vrTexture *texture;

while( i!=e )
	{

		texture = *i;
		if ( strncmp( texture->cName, strTextureName, 32 ) == 0 )
		{
			delete[] texture;
			tl->erase( i );
		}
		i++;
	}

//iCount--;
return;
}


//==============================================================//
//																//
//==============================================================//

void	vrTextureManager::Remove( unsigned int uiID )
{

TEXTURELIST::iterator i=tl->begin(), e = tl->end();


vrTexture *texture;

	while( i!=e )
	{

		texture = *i;
	
		if ( texture->uiID == uiID ) 
		{
			delete[] texture;
			tl->erase( i );
			return;
		}

		i++;

	}


//iCount--;
return;

}

//==============================================================//
//																//
//==============================================================//

vrTexture* vrTextureManager::Get( unsigned int uiID )
{


TEXTURELIST::iterator i=tl->begin(), e = tl->end();

vrTexture *texture;

while( i!=e )
	{

		texture = *i;
		if ( texture->uiID == uiID ) 
		{
			return texture;
		}

		
		i++;
	}


return NULL;

}

//==============================================================//
//																//
//==============================================================//
vrTexture* vrTextureManager::GetLast( )
{
	if ( !tl->empty() ) return tl->back();
	return NULL;
}


//==============================================================//
//																//
//==============================================================//

void vrTextureManager::Clear()
{
TEXTURELIST::iterator i=tl->begin(), e = tl->end();

vrTexture *texture;

	while( i!=e )
	{

		texture = *i;
		delete[] texture;
		tl->erase( i );
		i++;
	}

//iCount = 0;
}


//==============================================================//
//																//
//==============================================================//

int vrTextureManager::UploadAll()
{

TEXTURELIST::iterator i=tl->begin(), e = tl->end();

vrTexture *texture;
int count=0;
	while( i!=e )
	{

		texture = *i;
		//bUseTextureCompression � bUseMipMapping - ���������� ���������
		//���������������� �� ��� �������� �����, ���� ����� ������� �� ����������
		//��� ����� ������

		texture->bCompress	= engine.bUseTextureCompression;
		texture->bMipmap	= engine.bUseMipMapping;

		if ( texture->Upload() ) count++;
		i++;
	}

return count;

}

//==============================================================//
//																//
//==============================================================//

int vrTextureManager::Count()
{


return tl->size();


}