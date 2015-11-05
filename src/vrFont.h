#ifndef __VRFONT_H__
#define __VRFONT_H__

#include "vrInclude.h"
#include "vrMaterial.h"
#include "vrBase.h"



class vrFont
{

public:

	vrFont();
	bool		Init( vrMaterial2 *m_p );
	~vrFont();
	void		Print( int x, int y, const char *strString, ... );

	int			i_width;
	int			i_indent;


private:

	vrMaterial2	*material_p;

	UINT		vrFontListID;




};

















#endif