#include "QModelView.h"
#include <GL/glu.h>
#include <QKeyEvent>
#include <QtCore/qmath.h>
#include <QMouseEvent>
#include <QWheelEvent>

QModelView::QModelView(QWidget *parent)
: QOpenGLWidget(parent)
{
	ui.setupUi(this);
	m_bMouseTracking = TRUE;
	m_ModelCount_Last = 0;

	m_bLButtonDown = false;
	m_LButton_x = 0.0;
	m_LButton_y = 0.0;
	m_RButton_x = 0.0;
	m_RButton_y = 0.0;

	// 旋转角度和轴分量
	m_angle = 0.0;
	m_rotate_xc = 0.0;
	m_rotate_yc = 0.0;
	m_rotate_zc = 0.0;

	// 旋转角度和轴分量
	m_box_angle = 0.0;
	m_box_rotate_xc = 0.0;
	m_box_rotate_yc = 0.0;
	m_box_rotate_zc = 0.0;

	m_bRButtonDown = false;

	// 平移分量、起点和终点
	m_pan_dx = 0.0;
	m_pan_dy = 0.0;
	m_pan_dz = 0.0;

	m_pan_sx = 0.0;
	m_pan_sy = 0.0;
	m_pan_sz = 0.0;

	m_pan_ex = 0.0;
	m_pan_ey = 0.0;
	m_pan_ez = 0.0;

	// 缩放
	m_scale_zdelta = 0;
	m_scale_dx = 0.0;
	m_scale_dy = 0.0;
	m_scale_dz = 0.0;

	//只显示STL
	m_ViewSTL = true;

	startTimer(15);
}

QModelView::~QModelView()
{
}

//下面的代码的作用是重新设置OpenGL场景的大小，而不管窗口的大小是否已经改变(假定您没有使用全屏模式)。
//甚至您无法改变窗口的大小时(例如您在全屏模式下)，它至少仍将运行一次--在程序开始时设置我们的透视图。
//OpenGL场景的尺寸将被设置成它显示时所在窗口的大小。
void QModelView::resizeGL(int w, int h)
{
	GLResize(w, h, MODEL_VIEW_AT);
}

void QModelView::initializeGL()
{
	Init();
	SetDefaultView();
}

//瞧，这是以前从未见过的最短的绘制程序，有很棒的视觉效果！
//我们调用RenderToTexture 函数。幸亏我们视口改变这个函数才着色被拉伸的弹簧。 对于我们的纹理拉伸的弹簧被着色，并且这些缓冲器被清除。
//我们之后绘制“真正的”弹簧 (你在屏幕上看到的3D实体) 通过调用 ProcessHelix( )。
//最后我们在弹簧前面绘制一些混合的方块。有织纹的方块将被拉伸以适应在真正的3D弹簧
//上面。
void QModelView::paintGL()
{
	Ready();
	SetBkground();
	RenderScene();
}

void QModelView::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && m_bLButtonDown)
	{
		CalRotateVars(m_LButton_x, m_LButton_y, event->pos().x(), event->pos().y(),
			m_angle, m_rotate_xc, m_rotate_yc, m_rotate_zc);
		m_LButton_x = event->pos().x();			// 更新变量
		m_LButton_y = event->pos().y();
		update();
	}
}

void QModelView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_LButton_x = event->pos().x();
		m_LButton_y = event->pos().y();
		m_bLButtonDown = true;
	}
}

void QModelView::mouseReleaseEvent(QMouseEvent *event)
{
	CalRotateVars(m_LButton_x, m_LButton_y, event->pos().x(), event->pos().y(),
		m_box_angle, m_box_rotate_xc, m_box_rotate_yc, m_box_rotate_zc);

	m_bLButtonDown = false;					// 鼠标左键松开
	m_LButton_x = 0.0;						// 鼠标左键按下坐标清零
	m_LButton_y = 0.0;

	m_box_angle = m_angle;
	m_box_rotate_xc = m_rotate_xc;
	m_box_rotate_yc = m_rotate_yc;
	m_box_rotate_zc = m_rotate_zc;

	m_angle = 0.0;
	m_rotate_xc = 0.0;
	m_rotate_yc = 0.0;
	m_rotate_zc = 0.0;
}

void QModelView::wheelEvent(QWheelEvent *event)
{
	const double MAX_SCALE_VALUE = 6;
	const double MIN_SCALE_VALUE = 0.1;
	double global_scale = .0;
	double s = exp((double)event->angleDelta().y() * -0.002);

	GetScale(global_scale);
	if (global_scale > MIN_SCALE_VALUE && s < 1 || global_scale < MAX_SCALE_VALUE && s > 1)
	{
		SetScale(s);
	}

	update();

}

void QModelView::RenderScene()
{
	glPushMatrix();
	const double* matrix = GetMatrix();
	glLoadIdentity();		//其等同于用单位矩阵调用glLoadMatrix。但是，在一些情况下，glLoadIdentity更加效率
	glTranslated(m_pan_dx, m_pan_dy, m_pan_dz);//glTranslated(0.0f,0.0f,-3.0f);//把物体沿(0,0,-1)方向平移
	glRotated(m_angle, m_rotate_xc, m_rotate_yc, m_rotate_zc);		//旋转
	glMultMatrixd(matrix);				//用当前矩阵与任意矩阵相乘
	RefreshMatrix();

#pragma region 画框
	DrawBox(200, 200, 100);
#pragma endregion 画框

	glPopMatrix();

}
void QModelView::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
	{
						   qApp->exit();
						   break;
	}
	}
	QOpenGLWidget::keyPressEvent(event);
}

void QModelView::timerEvent(QTimerEvent *event)
{
	QOpenGLWidget::timerEvent(event);
}

void QModelView::Init()
{
	m_Camera.Init();

	int pixelformat;
	PIXELFORMATDESCRIPTOR pfdWnd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Structure size.
		1,                             // Structure version number.
		PFD_DRAW_TO_WINDOW |           // Property flags.
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,                            // 24-bit color.
		0, 0, 0, 0, 0, 0,              // Not concerned with these.
		0, 0, 0, 0, 0, 0, 0,           // No alpha or accum buffer.
		32,                            // 32-bit depth buffer.
		0, 0,                          // No stencil or aux buffer.
		PFD_MAIN_PLANE,                // Main layer type.
		0,                             // Reserved.
		0, 0, 0                        // Unsupported.
	};

	GLSetupRC();

	glPointSize(2);
	glLineWidth(3);

	// The following commands should induce OpenGL to create round points and 
	// antialias points and lines.  (This is implementation dependent unfortunately).
	//RGBA mode antialias need cooperate with blend function.
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//设置混合函数

	glEnable(GL_TEXTURE_2D);						// 启用纹理映射
	glShadeModel(GL_SMOOTH);						// 启用阴影平滑
	glClearColor(0.85, 0.89, 0.89, 0.2);				// 背景
	glClearDepth(1.0f);								// 设置深度缓存
	glEnable(GL_DEPTH_TEST);						// 启用深度测试
	glDepthFunc(GL_LEQUAL);							// 所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// 真正精细的透视修正

}

void QModelView::GLSetupRC()
{
	// clear bkground
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glClearDepth(2.0);
	glLoadIdentity();
	glEnable(GL_COLOR_MATERIAL);

	// Lighting components
	GLfloat  ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat  diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat  specular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat	 lightPos[] = { 0.0f, 50.0f, 150.0f, 0.0f };
	// Lighting components
	GLfloat  ambientLight2[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat  diffuseLight2[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat  specular2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat	 lightPos2[] = { 0.0f, 50.0f, 150.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);//两面照亮
	/*glEnable(GL_LIGHT0);*/
	//glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);//启用颜色追踪  

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, 100);
}

void QModelView::GLResize(int w, int h, double pos)
{
	// 	wglMakeCurrent(m_hDC,m_hRC);
	m_Camera.SetWindow(w, h);
	double cx, cy;
	cx = w;
	cy = h;

	double model = ((cx < cy ? cx : cy));
	cx /= model;
	cy /= model;

	//显示尺寸
	double _PrintSize = 100.0;
	cx *= _PrintSize;
	cy *= _PrintSize;

	double _left, _right, _bottom, _top, _nears, _Fars;
	double scale;
	GetScale(scale);
	_left = -cx;
	_right = cx;
	_bottom = -cy;
	_top = cy;

	//模型默认位置 
	double StandAt = pos;			// 0 ~ 2;
	StandAt = (1 - StandAt) * cy;
	_bottom = _bottom + StandAt;
	_top = _top + StandAt;

	_nears = -(cx + cy)*scale;
	_Fars = (cx + cy)*scale;
	SetProjectionBody(_left*scale*0.8, _right*scale*0.8, _bottom*scale*0.8, _top*scale*0.8, _nears, _Fars);
	glViewport(0, 0, w, h);//X，Y————以像素为单位，指定了视口的左下角位置。 　　width，height————表示这个视口矩形的宽度和高度，根据窗口的实时变化重绘窗口。
}

void QModelView::Ready()
{
	// 	wglMakeCurrent(m_hDC,m_hRC);
	SetProjection();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
}

void QModelView::SetBkground()
{
	glDisable(GL_LIGHTING);
	double left, right, bottom, top, zfar, znear;
	GetProjectionBody(left, right, bottom, top, znear, zfar);

	GLfloat Coord[8][2];
	{
		Coord[0][0] = left;
		Coord[0][1] = top;
		Coord[1][0] = right;
		Coord[1][1] = top;
		Coord[2][0] = left;
		Coord[2][1] = 0.150*top;
		Coord[3][0] = right;
		Coord[3][1] = 0.150*top;
		Coord[4][0] = left;
		Coord[4][1] = 0.550*top;
		Coord[5][0] = right;
		Coord[5][1] = 0.550*top;
		Coord[6][0] = left;
		Coord[6][1] = bottom;
		Coord[7][0] = right;
		Coord[7][1] = bottom;
	}


	GLfloat BKColor1[4] = { .9, .92, .92, .7 };
	GLfloat BKColor2[4] = { .9, .92, .92, .7 };
	GLfloat BKColor3[4] = { .6, .6, .6, .7 };
	GLfloat BKColor4[4] = { .6, .6, .6, .7 };
											  
	glPushMatrix();
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	double z = zfar * 0.99;

	glBegin(GL_QUAD_STRIP);
	glColor4f(BKColor1[0], BKColor1[1], BKColor1[2], BKColor1[3]);
	glVertex3f(Coord[0][0], Coord[0][1], -z);
	glColor4f(BKColor1[0], BKColor1[1], BKColor1[2], BKColor1[3]);
	glVertex3f(Coord[1][0], Coord[1][1], -z);

	glColor4f(BKColor2[0], BKColor2[1], BKColor2[2], BKColor2[3]);
	glVertex3f(Coord[2][0], Coord[2][1], -z);
	glColor4f(BKColor2[0], BKColor2[1], BKColor2[2], BKColor2[3]);
	glVertex3f(Coord[3][0], Coord[3][1], -z);

	//glColor4f(BKColor3[0],BKColor3[1],BKColor3[2],BKColor3[3]);
	//glVertex3f(Coord[4][0],Coord[4][1],-z);
	//glColor4f(BKColor3[0],BKColor3[1],BKColor3[2],BKColor3[3]);
	//glVertex3f(Coord[5][0],Coord[5][1],-z);

	glColor4f(BKColor4[0], BKColor4[1], BKColor4[2], BKColor4[3]);
	glVertex3f(Coord[6][0], Coord[6][1], -z);
	glColor4f(BKColor4[0], BKColor4[1], BKColor4[2], BKColor4[3]);
	glVertex3f(Coord[7][0], Coord[7][1], -z);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void QModelView::DrawBox(double box_x, double box_y, double box_z)
{
	glDisable(GL_LIGHTING);
	double xMin, xMax, yMin, yMax, zMin, zMax;

	double gridlen = 10.0;
	int nMinGrids = 5;
	double gridlen_Min = gridlen / nMinGrids;
	int xGrids = box_x / gridlen	/* + (box_x % gridlen == 0 ? 0 : 1)*/;
	int yGrids = box_y / gridlen		/* + (box_y % gridlen == 0 ? 0 : 1)*/;

	double zOffset = 0.0f;  //线不被底面遮挡
	double handOffset = 1.0f; //画坐标轴距离

	//平台尺寸
	xMin = -box_x / 2.0;
	xMax = -xMin;
	yMin = -box_y / 2.0;
	yMax = -yMin;
	zMin = 0;
	zMax = box_z;

	double global_scale = 1.0f;
	GetScale(global_scale);
	if (false)
	{
		//平台尺寸
		xMin *= global_scale;
		xMax *= global_scale;
		yMin *= global_scale;
		yMax *= global_scale;
		zMin *= global_scale;
		zMax *= global_scale;
		gridlen *= global_scale;
		zOffset *= global_scale;
		handOffset *= global_scale;
	}
	//平台渐变坐标
	GLfloat Coord[6][2];
	{
		Coord[0][0] = xMin;
		Coord[0][1] = yMax;
		Coord[1][0] = xMax;
		Coord[1][1] = yMax;
		Coord[2][0] = xMin;
		Coord[2][1] = 0.50*yMax;
		Coord[3][0] = xMax;
		Coord[3][1] = 0.50*yMax;
		Coord[4][0] = xMin;
		Coord[4][1] = yMin;
		Coord[5][0] = xMax;
		Coord[5][1] = yMin;
	}

	//描边坐标
	float fBoxOut = 1.0;
	GLfloat Coord_Box_Top[4][2];
	{
		Coord_Box_Top[0][0] = xMin - fBoxOut;
		Coord_Box_Top[0][1] = yMax + fBoxOut;

		Coord_Box_Top[1][0] = xMax + fBoxOut;
		Coord_Box_Top[1][1] = yMax + fBoxOut;

		Coord_Box_Top[2][0] = xMin - fBoxOut;
		Coord_Box_Top[2][1] = yMax;

		Coord_Box_Top[3][0] = xMax + fBoxOut;
		Coord_Box_Top[3][1] = yMax;

	}

	GLfloat Coord_Box_Bottom[4][2];
	{
		Coord_Box_Bottom[0][0] = xMin - fBoxOut;
		Coord_Box_Bottom[0][1] = yMin;

		Coord_Box_Bottom[1][0] = xMax + fBoxOut;
		Coord_Box_Bottom[1][1] = yMin;

		Coord_Box_Bottom[2][0] = xMin - fBoxOut;
		Coord_Box_Bottom[2][1] = yMin - fBoxOut;

		Coord_Box_Bottom[3][0] = xMax + fBoxOut;
		Coord_Box_Bottom[3][1] = yMin - fBoxOut;
	}

	GLfloat Coord_Box_Left[4][2];
	{
		Coord_Box_Left[0][0] = xMin - fBoxOut;
		Coord_Box_Left[0][1] = yMax;

		Coord_Box_Left[1][0] = xMin;
		Coord_Box_Left[1][1] = yMax;

		Coord_Box_Left[2][0] = xMin - fBoxOut;
		Coord_Box_Left[2][1] = yMin;

		Coord_Box_Left[3][0] = xMin;
		Coord_Box_Left[3][1] = yMin;
	}

	GLfloat Coord_Box_Right[4][2];
	{
		Coord_Box_Right[0][0] = xMax;
		Coord_Box_Right[0][1] = yMax;

		Coord_Box_Right[1][0] = xMax + fBoxOut;
		Coord_Box_Right[1][1] = yMax;

		Coord_Box_Right[2][0] = xMax;
		Coord_Box_Right[2][1] = yMin;

		Coord_Box_Right[3][0] = xMax + fBoxOut;
		Coord_Box_Right[3][1] = yMin;
	}

	GLfloat Coord_Box_Vetex[4][2];
	{
		//Coord_Box_Vetex[0][0] = 0;
		//Coord_Box_Vetex[0][1] = yMin;

		Coord_Box_Vetex[1][0] = 0 - fBoxOut / 2;
		Coord_Box_Vetex[1][1] = yMin - fBoxOut;

		Coord_Box_Vetex[2][0] = 0 + fBoxOut / 2;
		Coord_Box_Vetex[2][1] = yMin - fBoxOut;

		Coord_Box_Vetex[3][0] = 0;
		Coord_Box_Vetex[3][1] = yMin - fBoxOut * 1.7;
	}

	GLfloat Coord_Box_Tex[4][2];
	{
		Coord_Box_Tex[0][0] = 0 - fBoxOut / 2;
		Coord_Box_Tex[0][1] = yMin - fBoxOut;

		Coord_Box_Tex[1][0] = 0 + fBoxOut / 2;
		Coord_Box_Tex[1][1] = yMin - fBoxOut;

		Coord_Box_Tex[2][0] = 0 + fBoxOut / 2;
		Coord_Box_Tex[2][1] = yMin;

		Coord_Box_Tex[3][0] = 0 - fBoxOut / 2;
		Coord_Box_Tex[3][1] = yMin;
	}


	//平台颜色													   
	//GLfloat BKColor1[4] = {.15, .1, .1, .8};
	//GLfloat BKColor2[4] = {.3, .3, .3, .9};
	//GLfloat BKColor3[4] = {.1, .1, .1, .8};
	//GLfloat BKColor4[4] = {.1, .1, .1, .9};
	GLfloat BKColor1[4] = { 0.95, 1.0, 1.0, 0.98 };
	GLfloat BKColor2[4] = { 0.95, 1.0, 1.0, 0.98 };
	GLfloat BKColor3[4] = { 0.95, 1.0, 1.0, 0.78 };
	GLfloat BKColor4[4] = { 0.95, 1.0, 1.0, 0.78 };

	glLineWidth(1);
#pragma region 绘制框架
	////底部
	//glBegin(GL_LINE_STRIP);
	//glColor3f(0,0,0);
	//glVertex3f(xMin,yMax,zMin + zOffset);
	//glVertex3f(xMax,yMax,zMin + zOffset);
	//glVertex3f(xMax,yMin,zMin + zOffset);
	//glVertex3f(xMin,yMin,zMin + zOffset);
	//glVertex3f(xMin,yMax,zMin + zOffset);
	//glEnd();
	//顶部
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_LINES);
	glVertex3f(xMin, yMax, zMax);
	glVertex3f(xMax, yMax, zMax);
	glVertex3f(xMax, yMax, zMax);
	glVertex3f(xMax, yMin, zMax);
	glVertex3f(xMin, yMax, zMax);
	glVertex3f(xMin, yMin, zMax);
	glEnd();
	//四边
	glBegin(GL_LINES);
	glVertex3f(xMin, yMax, zMin);
	glVertex3f(xMin, yMax, zMax);
	glVertex3f(xMax, yMax, zMax);
	glVertex3f(xMax, yMax, zMin);
	glVertex3f(xMin, yMin, zMin);
	glVertex3f(xMin, yMin, zMax);
	glVertex3f(xMax, yMin, zMax);
	glVertex3f(xMax, yMin, zMin);
	glEnd();
#pragma endregion 绘制框架


#pragma region 绘制平面
	double z = .001;
	glBegin(GL_QUAD_STRIP);

	glColor4f(BKColor1[0], BKColor1[1], BKColor1[2], BKColor1[3]);
	glVertex3f(Coord[0][0], Coord[0][1], -z);
	glColor4f(BKColor1[0], BKColor1[1], BKColor1[2], BKColor1[3]);
	glVertex3f(Coord[1][0], Coord[1][1], -z);

	glColor4f(BKColor2[0], BKColor2[1], BKColor2[2], BKColor2[3]);
	glVertex3f(Coord[2][0], Coord[2][1], -z);
	glColor4f(BKColor2[0], BKColor2[1], BKColor2[2], BKColor2[3]);
	glVertex3f(Coord[3][0], Coord[3][1], -z);

	glColor4f(BKColor3[0], BKColor3[1], BKColor3[2], BKColor3[3]);
	glVertex3f(Coord[4][0], Coord[4][1], -z);
	glColor4f(BKColor3[0], BKColor3[1], BKColor3[2], BKColor3[3]);
	glVertex3f(Coord[5][0], Coord[5][1], -z);

	//



	//


	glEnd();

	//描边
	glColor4f(0, 0, 0, 0.3);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <4; i++)
	{
		glVertex3f(Coord_Box_Bottom[i][0], Coord_Box_Bottom[i][1], -z);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <4; i++)
	{
		glVertex3f(Coord_Box_Top[i][0], Coord_Box_Top[i][1], -z);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <4; i++)
	{
		glVertex3f(Coord_Box_Left[i][0], Coord_Box_Left[i][1], -z);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <4; i++)
	{
		glVertex3f(Coord_Box_Right[i][0], Coord_Box_Right[i][1], -z);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 1; i < 4; i++)
	{
		glVertex3f(Coord_Box_Vetex[i][0], Coord_Box_Vetex[i][1], -z);
	}
	glEnd();
	if (m_isTexturesLoaded)
	{
		//纹理贴图
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, texture[0]);				// 选择纹理
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(Coord_Box_Tex[0][0], Coord_Box_Tex[0][1], 0.01);	// 纹理和四边形的左下
		glTexCoord2f(1.0f, 0.0f); glVertex3f(Coord_Box_Tex[1][0], Coord_Box_Tex[1][1], 0.01);	// 纹理和四边形的右下
		glTexCoord2f(1.0f, 1.0f); glVertex3f(Coord_Box_Tex[2][0], Coord_Box_Tex[2][1], 0.01);	// 纹理和四边形的右上
		glTexCoord2f(0.0f, 1.0f); glVertex3f(Coord_Box_Tex[3][0], Coord_Box_Tex[3][1], 0.01);	// 纹理和四边形的左上
		glEnd();
	}
#pragma endregion 绘制平面

#pragma region 绘制指针
	//	//X轴
	//	glBegin(GL_LINES);
	//	glColor3f(0.23,0.25,0.85);
	//	glVertex3f(xMin-handOffset,yMin-handOffset,zMin - handOffset);
	//	glVertex3f(xMin + 10 * handOffset,yMin - handOffset,zMin - handOffset);
	//
	//	glVertex3f(xMin + 10 * handOffset,yMin - handOffset,zMin - handOffset);
	//	glVertex3f(xMin + 9 * handOffset,yMin - handOffset,zMin);
	//
	//	glVertex3f(xMin + 10 * handOffset,yMin - handOffset,zMin - handOffset);
	//	glVertex3f(xMin + 9 * handOffset,yMin - handOffset,zMin - 2 * handOffset);
	//	//字
	//	glVertex3f(xMin + 11 * handOffset,yMin - handOffset,zMin);
	//	glVertex3f(xMin + 12 * handOffset,yMin - handOffset,zMin - 2 * handOffset);
	//
	//	glVertex3f(xMin + 11 * handOffset,yMin - handOffset,zMin - 2 * handOffset);
	//	glVertex3f(xMin + 12 * handOffset,yMin - handOffset,zMin);
	//
	//	glEnd();
	//	//Y轴
	//	glBegin(GL_LINES);
	//	glColor3f(0.23,0.25,0.85);
	//	glVertex3f(xMin - handOffset,yMin-handOffset,zMin - handOffset);
	//	glVertex3f(xMin - handOffset,yMin + 10 * handOffset,zMin - handOffset);
	//			    
	//	glVertex3f(xMin - handOffset,yMin + 10 * handOffset,zMin - handOffset);
	//	glVertex3f(xMin - handOffset,yMin + 9 * handOffset,zMin);
	//			   
	//	glVertex3f(xMin - handOffset,yMin + 10 * handOffset,zMin - handOffset);
	//	glVertex3f(xMin - handOffset,yMin + 9 * handOffset,zMin - 2 * handOffset);
	//	//字
	//	glVertex3f(xMin - handOffset,yMin + 11.5 * handOffset,zMin);
	//	glVertex3f(xMin - handOffset,yMin + 11 * handOffset,zMin - handOffset);
	//
	//	glVertex3f(xMin - handOffset,yMin + 10.5 * handOffset,zMin);
	//	glVertex3f(xMin - handOffset,yMin + 11 * handOffset,zMin - handOffset);
	//
	//	glVertex3f(xMin - handOffset,yMin + 11 * handOffset,zMin - handOffset);
	//	glVertex3f(xMin - handOffset,yMin + 11 * handOffset,zMin - 2 * handOffset);
	//
	//	glEnd();
	//	//Z轴
	//	glBegin(GL_LINES);
	//	glColor3f(0.23,0.25,0.85);
	//	glVertex3f(xMin - handOffset,yMin-handOffset,zMin - handOffset);
	//	glVertex3f(xMin - handOffset,yMin - handOffset,zMin + 10 * handOffset);
	//
	//	glVertex3f(xMin - handOffset,yMin - handOffset,zMin + 10 * handOffset);
	//	glVertex3f(xMin - 2 * handOffset,yMin - handOffset,zMin + 9 * handOffset);
	//
	//	glVertex3f(xMin - handOffset,yMin - handOffset,zMin + 10 * handOffset);
	//	glVertex3f(xMin,yMin - handOffset,zMin + 9 * handOffset);
	//	//字
	//	glVertex3f(xMin - 2 * handOffset,yMin - handOffset,zMin + 12.5 * handOffset);
	//	glVertex3f(xMin,yMin - handOffset,zMin + 12.5 * handOffset);
	//
	//	glVertex3f(xMin,yMin - handOffset,zMin + 12.5 * handOffset);
	//	glVertex3f(xMin - 2 * handOffset,yMin - handOffset,zMin + 10.5 * handOffset);
	//
	//	glVertex3f(xMin - 2 * handOffset,yMin - handOffset,zMin + 10.5 * handOffset);
	//	glVertex3f(xMin,yMin - handOffset,zMin + 10.5 * handOffset);
	//	glEnd();
#pragma endregion 绘制指针

#pragma region 绘制格子
	glLineWidth(0.5f);
	glBegin(GL_LINES);
	glColor4f(0.3, 0.3, 0.3, 0.3);

	float Grid_Y_Max = yMax ;
	float Grid_X_Max = yMax ;
	glVertex3f(-Grid_X_Max, 0, zMin + zOffset);
	glVertex3f(Grid_X_Max, 0, zMin + zOffset);
	float fNextOffset = gridlen;
	while (fNextOffset < Grid_Y_Max)
	{
		glVertex3f(-Grid_X_Max, -fNextOffset, zMin + zOffset);
		glVertex3f(Grid_X_Max, -fNextOffset, zMin + zOffset);
		glVertex3f(-Grid_X_Max, fNextOffset, zMin + zOffset);
		glVertex3f(Grid_X_Max, fNextOffset, zMin + zOffset);
		fNextOffset += gridlen;
	}

	glVertex3f(0, -Grid_Y_Max, zMin + zOffset);
	glVertex3f(0, Grid_Y_Max, zMin + zOffset);
	fNextOffset = gridlen;
	while (fNextOffset < Grid_X_Max)
	{
		glVertex3f(-fNextOffset, -Grid_Y_Max, zMin + zOffset);
		glVertex3f(-fNextOffset, Grid_Y_Max, zMin + zOffset);
		glVertex3f(fNextOffset, -Grid_Y_Max, zMin + zOffset);
		glVertex3f(fNextOffset, Grid_Y_Max, zMin + zOffset);
		fNextOffset += gridlen;
	}
	glEnd();

	glLineWidth(0.5f);
	glBegin(GL_LINES);
	glColor4f(0, 0, 0, 0.1);

	glVertex3f(xMin, 0, zMin + zOffset);
	glVertex3f(xMax, 0, zMin + zOffset);
	fNextOffset = gridlen_Min;
	while (fNextOffset < yMax)
	{
		glVertex3f(xMin, -fNextOffset, zMin + zOffset);
		glVertex3f(xMax, -fNextOffset, zMin + zOffset);
		glVertex3f(xMin, fNextOffset, zMin + zOffset);
		glVertex3f(xMax, fNextOffset, zMin + zOffset);
		fNextOffset += gridlen_Min;
	}

	glVertex3f(0, yMin, zMin + zOffset);
	glVertex3f(0, yMax, zMin + zOffset);
	fNextOffset = gridlen_Min;
	while (fNextOffset < xMax)
	{
		glVertex3f(-fNextOffset, yMin, zMin + zOffset);
		glVertex3f(-fNextOffset, yMax, zMin + zOffset);
		glVertex3f(fNextOffset, yMin, zMin + zOffset);
		glVertex3f(fNextOffset, yMax, zMin + zOffset);
		fNextOffset += gridlen_Min;
	}
	glEnd();

#pragma endregion 绘制格子


	glEnable(GL_LIGHTING);
}

//*****************************************************************************
//  camera operation
//*****************************************************************************
void QModelView::SetScale(double scale)
{
	m_Camera.SetScale(scale);
}

void QModelView::GetScale(double& scale)
{
	m_Camera.GetScale(scale);
}

void QModelView::SetProjection()
{
	m_Camera.SetProjection();
}

void QModelView::SetWindow(double width, double height)
{
	m_Camera.SetWindow(width, height);
}

void QModelView::GetWindow(double& width, double& height)
{
	m_Camera.GetWindow(width, height);
}

void QModelView::SetProjectionBody(double left, double right, double bottom,
	double top, double znear, double zfar)
{
	m_Camera.SetProjectionBody(left, right, bottom, top, znear, zfar);
}

void QModelView::GetProjectionBody(double& left, double& right, double& bottom,
	double& top, double& znear, double& zfar)
{
	m_Camera.GetProjectionBody(left, right, bottom, top, znear, zfar);
}

//*****************************************************************************
// transformation
//*****************************************************************************
const double* QModelView::GetMatrix()
{
	if (!_is_init)
		RefreshMatrix();
	return _matrix;
}

const double* QModelView::GetInverseMatrix()
{
	if (!_is_init)
		RefreshMatrix();
	return _inverse_matrix;
}

void QModelView::TransformPosition(const int &x, const int &y, double &px, double &py, double &pz)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	double _left, _right, _bottom, _top, _nears, _fars;
	GetProjectionBody(_left, _right, _bottom, _top, _nears, _fars);

	px = (double)(x - viewport[0]) / (double)(viewport[2]);
	py = (double)(y - viewport[1]) / (double)(viewport[3]);

	px = _left + px*(_right - _left);
	py = _top + py*(_bottom - _top);
	pz = _nears;
}

void QModelView::RefreshMatrix()
{
	glGetDoublev(GL_MODELVIEW_MATRIX, (double*)_matrix);
	invertMatrix(_matrix, (double*)_inverse_matrix);

	for (int i = 0; i < 16; i++)
	{
		if (_isnan(_matrix[i]) || _isnan(_inverse_matrix[i]))
		{
			_is_init = false;
			return;
		}
	}

	_is_init = true;
}

void QModelView::invertMatrix(const GLdouble *m, GLdouble *out)
{
	/* NB. OpenGL Matrices are COLUMN major. */
#define MAT(m,r,c) (m)[(c)*4+(r)]

	/* Here's some shorthand converting standard (row,column) to index. */
#define m11 MAT(m,0,0)
#define m12 MAT(m,0,1)
#define m13 MAT(m,0,2)
#define m14 MAT(m,0,3)
#define m21 MAT(m,1,0)
#define m22 MAT(m,1,1)
#define m23 MAT(m,1,2)
#define m24 MAT(m,1,3)
#define m31 MAT(m,2,0)
#define m32 MAT(m,2,1)
#define m33 MAT(m,2,2)
#define m34 MAT(m,2,3)
#define m41 MAT(m,3,0)
#define m42 MAT(m,3,1)
#define m43 MAT(m,3,2)
#define m44 MAT(m,3,3)

	GLdouble det;
	GLdouble d12, d13, d23, d24, d34, d41;
	GLdouble tmp[16]; /* Allow out == in. */

	/* Inverse = adjoint / det. (See linear algebra texts.)*/

	/* pre-compute 2x2 dets for last two rows when computing */
	/* cofactors of first two rows. */
	d12 = (m31*m42 - m41*m32);
	d13 = (m31*m43 - m41*m33);
	d23 = (m32*m43 - m42*m33);
	d24 = (m32*m44 - m42*m34);
	d34 = (m33*m44 - m43*m34);
	d41 = (m34*m41 - m44*m31);

	tmp[0] = (m22 * d34 - m23 * d24 + m24 * d23);
	tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
	tmp[2] = (m21 * d24 + m22 * d41 + m24 * d12);
	tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);

	/* Compute determinant as early as possible using these cofactors. */
	det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];

	/* Run singularity test. */
	if (_isnan(det))
	{
		/* printf("invert_matrix: Warning: Singular matrix.\n"); */
		/*    memcpy(out,_identity,16*sizeof(double)); */
	}
	else {
		GLdouble invDet = 1.0 / det;
		/* Compute rest of inverse. */
		tmp[0] *= invDet;
		tmp[1] *= invDet;
		tmp[2] *= invDet;
		tmp[3] *= invDet;

		tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
		tmp[5] = (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
		tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
		tmp[7] = (m11 * d23 - m12 * d13 + m13 * d12) * invDet;

		/* Pre-compute 2x2 dets for first two rows when computing */
		/* cofactors of last two rows. */
		d12 = m11*m22 - m21*m12;
		d13 = m11*m23 - m21*m13;
		d23 = m12*m23 - m22*m13;
		d24 = m12*m24 - m22*m14;
		d34 = m13*m24 - m23*m14;
		d41 = m14*m21 - m24*m11;

		tmp[8] = (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
		tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
		tmp[10] = (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
		tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
		tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
		tmp[13] = (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
		tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
		tmp[15] = (m31 * d23 - m32 * d13 + m33 * d12) * invDet;

		memcpy(out, tmp, 16 * sizeof(GLdouble));
	}

#undef m11
#undef m12
#undef m13
#undef m14
#undef m21
#undef m22
#undef m23
#undef m24
#undef m31
#undef m32
#undef m33
#undef m34
#undef m41
#undef m42
#undef m43
#undef m44
#undef MAT
}

//*****************************************************************************
//*****************************************************************************
// 计算旋转角度和旋转轴
// 虚拟单位球方法
void QModelView::CalRotateVars(double star_x, double star_y, double end_x, double end_y,
	double& angle, double& r_vx, double& r_vy, double& r_vz)
{
	const double PI = 3.14159265;
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// 对鼠标获取的点进行归一化处理下（线性变换）
	double sx = star_x * (2.0 / (viewport[2] + 1)) - 1.0;
	double sy = -1.0 *(star_y * (2.0 / (viewport[3] + 1)) - 1.0);

	double ex = end_x * (2.0 / (viewport[2] + 1)) - 1.0;
	double ey = -1.0 * (end_y * (2.0 / (viewport[3] + 1)) - 1.0);

	double s_vx, s_vy, s_vz, e_vx, e_vy, e_vz;
	map2Sphere(sx, sy, s_vx, s_vy, s_vz);
	map2Sphere(ex, ey, e_vx, e_vy, e_vz);

	TVector3D s_vec(s_vx, s_vy, s_vz);
	TVector3D e_vec(e_vx, e_vy, e_vz);

	if (!s_vec.IsZero())
		s_vec.Normalize();
	if (!e_vec.IsZero())
		e_vec.Normalize();

	TVector3D r_vec = s_vec^e_vec;

	if (!r_vec.IsZero())
		r_vec.Normalize();

	double _angle = acos(s_vec * e_vec);

	angle = 2.0 *_angle * 180.0 / PI;
	r_vx = r_vec.x();
	r_vy = r_vec.y();
	r_vz = r_vec.z();
}

void QModelView::map2Sphere(double px, double py, double& vx, double& vy, double& vz)
{
	double radius = 1.0;
	if ((px * px + py * py) > 1.0)
	{
		vx = px;
		vy = py;
		vz = 0.0;
	}
	// (px * px + py * py) <= 1.0
	else
	{
		vx = px;
		vy = py;
		vz = sqrt(radius * radius - px*px - py * py);
	}
}


void QModelView::SetViewDirection(int nDirection)
{

}
// 设置模型默认视角
void QModelView::SetDefaultView(void)
{
	double global_scale;

	GetScale(global_scale);
	SetScale(2.5 / global_scale);
	RefreshMatrix();

	glPushMatrix();
	const double* matrix = GetMatrix();
	glLoadIdentity();		//其等同于用单位矩阵调用glLoadMatrix。但是，在一些情况下，glLoadIdentity更加效率
	glRotated(270.0, 1, 0, 0);		//旋转
	glMultMatrixd(matrix);				//用当前矩阵与任意矩阵相乘
	RefreshMatrix();
	glPopMatrix();

	glPushMatrix();
	matrix = GetMatrix();
	glLoadIdentity();		//其等同于用单位矩阵调用glLoadMatrix。但是，在一些情况下，glLoadIdentity更加效率
	glRotated(20, 1.25, -0.75, 0.0);    //旋转
	glMultMatrixd(matrix);				//用当前矩阵与任意矩阵相乘
	RefreshMatrix();
	glPopMatrix();

	QRect rc;

	rc = contentsRect();

	GLResize(rc.x(), rc.y(), MODEL_VIEW_AT);

}
