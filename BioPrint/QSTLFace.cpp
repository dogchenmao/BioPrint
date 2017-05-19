#include "QSTLFace.h"


QSTLFace::QSTLFace(const QSTLFace& srcFace)
{
	m_vector_normal = srcFace.m_vector_normal;

	m_points[0] = srcFace.m_points[0];
	m_points[1] = srcFace.m_points[1];
	m_points[2] = srcFace.m_points[2];

	m_edges[0] = srcFace.m_edges[0];
	m_edges[1] = srcFace.m_edges[1];
	m_edges[2] = srcFace.m_edges[2];
}

const QSTLFace& QSTLFace::operator=(const QSTLFace& srcFace)
{
	m_vector_normal = srcFace.m_vector_normal;

	m_points[0] = srcFace.m_points[0];
	m_points[1] = srcFace.m_points[1];
	m_points[2] = srcFace.m_points[2];

	m_edges[0] = srcFace.m_edges[0];
	m_edges[1] = srcFace.m_edges[1];
	m_edges[2] = srcFace.m_edges[2];

	return *this;
}
