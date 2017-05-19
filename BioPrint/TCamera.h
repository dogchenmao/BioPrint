//*****************************************************************************
//  Camera.h 
//  Camera class
//*****************************************************************************
// Author:  Liu Mingzeng    2009/11/29   DLUT  SAE Department
//
//*****************************************************************************

#ifndef _TCAMERA_HEADER_
#define _TCAMERA_HEADER_

#include "GeomBase.h"
#include "TVector3D.h"
#include <qopengl.h>
class TCamera
{
protected:
	//  eye coordinate
	TPoint3D  m_eye;
	TPoint3D  m_ref;
	TVector3D m_upvec;

	// view volume
	double m_left, m_right, m_bottom, m_top;
	double m_near, m_far;

	double m_scale;
	double m_width, m_height;

public:
	TCamera();
	~TCamera();

public:
	// initializing
	void Init();

	void SetProjection();

	// set viewport acoording to window
	void SetWindow(double width, double height);
	void GetWindow(double &width, double &height);

	// set eye coordinate
	void set_eye(double eye_x, double eye_y, double eye_z);
	void set_ref(double ref_x, double ref_y, double ref_z);
	void set_vecUp(double up_dx, double up_dy, double up_dz);

	// set viewing volume
	void SetProjectionBody(double left, double right, double bottom,
		double top, double near, double Far);
	void GetProjectionBody(double& left, double& ritht, double& bottom,
		double& top, double& near, double& Far);

	void SetScale(double scale);
	void GetScale(double &scale);
};


#endif