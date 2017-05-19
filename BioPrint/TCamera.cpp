//*****************************************************************************
//
//  TCamera.cpp:  TCamera Implementation file
//
//*****************************************************************************
#include "TCamera.h"

TCamera::TCamera()
{

}
TCamera::~TCamera()
{

}

void TCamera::SetProjection()
{
	// switch to projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRenderMode(GL_RENDER);
	glOrtho(m_left, m_right, m_bottom, m_top, m_near, m_far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// 	glTranslated(0.0f,0.0f,-5.0f);

	// 	gluLookAt(m_eye.x(),m_eye.y(),m_eye.z(),m_ref.x(),m_ref.y(),m_ref.z(),
	// 		      m_upvec.x(), m_upvec.y(), m_upvec.z());

}

void TCamera::Init()
{
	m_eye.SetValue(0.0, 0.0, -5.0);
	m_ref.SetValue(0., 0., 0.);

	m_left = -1.0;
	m_right = 1.0;
	m_bottom = -1.0;
	m_top = 1.0;

	m_near = -2.0;
	m_far = 2.0;

	m_scale = 1.0;

	m_width = 0.0;
	m_height = 0.0;

	m_upvec.SetValue(0.0, 1.0, 0.0);
}

//  viewport window
void TCamera::SetWindow(double width, double height)
{
	m_width = width;
	m_height = height;
}

void TCamera::GetWindow(double& width, double& height)
{
	width = m_width;
	height = m_height;
}

// projection Body
void TCamera::SetProjectionBody(double left, double right, double bottom,
	double top, double znear, double zfar)
{
	m_left = left;
	m_right = right;
	m_bottom = bottom;
	m_top = top;
	m_near = znear;
	m_far = zfar;
}

void TCamera::GetProjectionBody(double &left, double &right, double &bottom,
	double &top, double &znear, double &zfar)
{
	left = m_left;
	right = m_right;
	bottom = m_bottom;
	top = m_top;
	znear = m_near;
	zfar = m_far;
}

// Scale
void TCamera::SetScale(double scale)
{
	m_scale *= scale;
	// 	m_near *= scale;
	// 	m_far *= scale;
	m_left *= scale;
	m_right *= scale;
	m_bottom *= scale;
	m_top *= scale;
	SetProjection();
}

void TCamera::GetScale(double &scale)
{
	scale = m_scale;
}
// viewpoint
void TCamera::set_eye(double eye_x, double eye_y, double eye_z)
{
	m_eye.SetValue(eye_x, eye_y, eye_z);
}

void TCamera::set_ref(double ref_x, double ref_y, double ref_z)
{
	m_ref.SetValue(ref_x, ref_y, ref_z);
}

void TCamera::set_vecUp(double up_dx, double up_dy, double up_dz)
{
	m_upvec.x(up_dx);
	m_upvec.y(up_dy);
	m_upvec.z(up_dz);
}


