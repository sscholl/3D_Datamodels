#pragma once
#include <iostream> //for debug
#define _USE_MATH_DEFINES 
#include <math.h>


template <int TVerticals>
class CCylinder
{

public:

  typedef CCylinder<TVerticals> CThis;
	enum
	{
		m_Verticals = TVerticals,
	};

public:

	CCylinder(float _Radius, float _Height) : 
		m_X(0), 
		m_Y(0),
		m_Z(0), 
		m_Radius(_Radius), 
		m_Height(_Height), 
		m_VerticalsAngleDegree(s_CircleDegree / TVerticals)
	{}

	~CCylinder()
	{}
	
	void GetVertices()
	{
		float X, Z, AnglePiHalfCircleDegree;
		float AngleVertical = 0.0f;
		float HalfHeight = m_Height / 2;
		for (int Vertical = 0; Vertical < TVerticals; ++ Vertical) {
			AnglePiHalfCircleDegree = AngleVertical * (float) M_PI / s_HalfCircleDegree;
			X = (m_X + m_Radius * cos(AnglePiHalfCircleDegree));
			Z = (m_Z + m_Radius * sin(AnglePiHalfCircleDegree));
			X = RoundF(X, 6);
			Z = RoundF(Z, 6);
			int IndexNorthCircle = Vertical;
			m_VerticesArray[Vertical][0] = X;
			m_VerticesArray[Vertical][1] = HalfHeight;
			m_VerticesArray[Vertical][2] = Z;
			int IndexSouthCircle = Vertical + TVerticals;
			m_VerticesArray[IndexSouthCircle][0] = X;
			m_VerticesArray[IndexSouthCircle][1] = -HalfHeight;
			m_VerticesArray[IndexSouthCircle][2] = Z;
			AngleVertical += m_VerticalsAngleDegree;
		}
		m_VerticesArray[s_VerticesCount - 2][0] = 0;
		m_VerticesArray[s_VerticesCount - 2][1] = HalfHeight;
		m_VerticesArray[s_VerticesCount - 2][2] = 0;
		m_VerticesArray[s_VerticesCount - 1][0] = 0;
		m_VerticesArray[s_VerticesCount - 1][1] = -HalfHeight;
		m_VerticesArray[s_VerticesCount - 1][2] = 0;
	}

	int GetVerticesCount()
	{
		return s_VerticesCount;
	}
	
	void GetTriangles()
	{
		int NorthVertex = s_VerticesCount - 2;
		int SouthVertex = s_VerticesCount - 1;
		int TriangleIndex = 0;
		for (int Vertical = 0; Vertical < TVerticals; ++ Vertical) {
			int NorthCircleVertex = Vertical;
			int NextInNorthCircle = (Vertical + 1) % TVerticals;
			m_TrianglesArray[TriangleIndex][0] = NorthCircleVertex;
			m_TrianglesArray[TriangleIndex][1] = NextInNorthCircle;
			m_TrianglesArray[TriangleIndex ++][2] = NorthVertex;
						
			int SouthCircleVertex = NorthCircleVertex + TVerticals;
			int NextInSouthCircle = NextInNorthCircle + TVerticals;
			m_TrianglesArray[TriangleIndex][0] = SouthCircleVertex;
			m_TrianglesArray[TriangleIndex][1] = SouthVertex;
			m_TrianglesArray[TriangleIndex ++][2] = NextInSouthCircle;

			m_TrianglesArray[TriangleIndex][0] = NorthCircleVertex;
			m_TrianglesArray[TriangleIndex][1] = SouthCircleVertex;
			m_TrianglesArray[TriangleIndex ++][2] = NextInNorthCircle;
			m_TrianglesArray[TriangleIndex][0] = SouthCircleVertex;
			m_TrianglesArray[TriangleIndex][1] = NextInSouthCircle;
			m_TrianglesArray[TriangleIndex ++][2] = NextInNorthCircle;
		}
	}

	int GetTrianglesCount()
	{
		return s_TrianglesCount;
	}

private:

	float RoundF(float Zahl, int Stellen) 
	{ 
		float v[] = { 1, 10, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8 };  // mgl. verlängern 
		return (float) floor(Zahl * v[Stellen] + 0.5) / v[Stellen]; 
	}
	
private:

	float				m_X, m_Y, m_Z;
	float				m_Radius, m_Height;
	float				m_VerticalsAngleDegree;
	enum {
						s_VerticesCount				= TVerticals * 2 + 2,
						s_TrianglesCount			= TVerticals  * 4,
	};
	static const float	s_CircleDegree;
	static const float	s_HalfCircleDegree;
	static const float	s_QuarterCircleDegree;

public:
	
	float				m_VerticesArray[s_VerticesCount][3];
	int					m_TrianglesArray[s_TrianglesCount][3];

};

template <int TVerticals> const float CCylinder<TVerticals>::s_CircleDegree = 360.0f;
template <int TVerticals> const float CCylinder<TVerticals>::s_HalfCircleDegree = 180.0f;
template <int TVerticals> const float CCylinder<TVerticals>::s_QuarterCircleDegree = 90.0f;
