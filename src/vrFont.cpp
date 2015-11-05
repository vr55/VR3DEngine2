#include "vrFont.h"

//==============================================================//
//																//
//==============================================================//
bool vrFont::Init( vrMaterial2 *m_p )
{
assert( m_p );
if ( m_p )
{
float cx, cy;

vrFontListID = glGenLists(256);

//m_p->Begin();
material_p = m_p;

for ( int i=0; i<256; i++ )
{
		cx = float(i%16)/16.0f;					// X Position Of Current Character
		cy = float(i/16)/16.0f;					// Y Position Of Current Character

		glNewList( vrFontListID + i,GL_COMPILE );				// Start Building A List


		glBegin( GL_QUADS );
				glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
				glTexCoord2f( cx,1 - cy - 0.0625f );	// Texture Coord (Bottom Left)
				glVertex2i( 0,0 );					// Vertex Coord (Bottom Left)

				glTexCoord2f( cx+0.0625f,1 - cy - 0.0625f );// Texture Coord (Bottom Right)
				glVertex2i(i_width,0);					// Vertex Coord (Bottom Right)

				glTexCoord2f( cx + 0.0625f,1 - cy );		// Texture Coord (Top Right)
				glVertex2i(i_width,i_width);					// Vertex Coord (Top Right)

				glTexCoord2f( cx,1 - cy );				// Texture Coord (Top Left)
				glVertex2i( 0, i_width );				// Vertex Coord (Top Left)

				glEnd();

				glTranslated( i_indent,0,0 );					// Move To The Right Of The Character
		glEndList();							// Done Building The Display List

}

return true;
}
return false;
}
//==============================================================//
//																//
//==============================================================//

vrFont::vrFont()

{

i_indent	= 10;
i_width		= 12;

material_p = NULL;
}


//==============================================================//
//																//
//==============================================================//
void vrFont::Print( int x, int y, const char *strString, ... )
{
glPushAttrib(GL_ALL_ATTRIB_BITS);

assert( material_p );

engine.glStoreMatrix( GL_TEXTURE );
if ( material_p ) material_p->Begin();

assert( strString );
if ( !strString ) return;

char	Text[255];

va_list	aPrint;

	va_start( aPrint, strString );
	    vsprintf( Text, strString, aPrint );	// Конвертитуем все что передали процедуре в строку
	va_end( aPrint );


glDisable( GL_DEPTH_TEST );
glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
glEnable( GL_BLEND );
glBlendFunc( GL_ONE, GL_ONE );

engine.glStoreMatrix( GL_PROJECTION );
glLoadIdentity();							// Reset The Projection Matrix
glOrtho( 0, engine.uiScreenWidth, 0, engine.uiScreenHeight, -1, 1 );							// Set Up An Ortho Screen

engine.glStoreMatrix( GL_MODELVIEW );
glLoadIdentity();							// Reset The Modelview Matrix

glTranslated( x,y,0 );						// Position The Text (0,0 - Bottom Left)

glListBase( vrFontListID - 32 );			// Choose The Font Set (0 or 1)

glCallLists( strlen(Text), GL_BYTE, Text);	// Write The Text To The Screen

engine.glRestoreMatrix( GL_TEXTURE );
engine.glRestoreMatrix( GL_MODELVIEW );
engine.glRestoreMatrix( GL_PROJECTION );

glEnable( GL_DEPTH_TEST );					// Enables Depth Testing

glPopAttrib();
if ( material_p ) material_p->End();




}



//==============================================================//
//																//
//==============================================================//
vrFont::~vrFont()
{
	glDeleteLists( vrFontListID, 256 );

}