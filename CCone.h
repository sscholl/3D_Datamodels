#pragma once
#include <iostream> //for debug
#define _USE_MATH_DEFINES 
#include <math.h>


template <int TVerticals>
class CCone
{

public:

  typedef CCone<TVerticals> CThis;
	enum
	{
		m_Verticals = TVerticals,
	};

public:

	CCone(float _Radius, float _Height) : 
		m_X(0), 
		m_Y(0),
		m_Z(0), 
		m_Radius(_Radius), 
		m_Height(_Height), 
		m_VerticalsAngleDegree(s_CircleDegree / TVerticals)
	{}

	~CCone()
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
			int CircleVertex = Vertical;
			int NextInCircle = (Vertical + 1) % TVerticals;
			m_TrianglesArray[TriangleIndex][0] = CircleVertex;
			m_TrianglesArray[TriangleIndex][1] = NextInCircle;
			m_TrianglesArray[TriangleIndex ++][2] = NorthVertex;

			m_TrianglesArray[TriangleIndex][0] = CircleVertex;
			m_TrianglesArray[TriangleIndex][1] = SouthVertex;
			m_TrianglesArray[TriangleIndex ++][2] = NextInCircle;
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
						s_VerticesCount				= TVerticals + 2,
						s_TrianglesCount			= TVerticals  * 2,
	};
	static const float	s_CircleDegree;
	static const float	s_HalfCircleDegree;
	static const float	s_QuarterCircleDegree;

public:
	
	float				m_VerticesArray[s_VerticesCount][3];
	int					m_TrianglesArray[s_TrianglesCount][3];

};

template <int TVerticals> const float CCone<TVerticals>::s_CircleDegree = 360.0f;
template <int TVerticals> const float CCone<TVerticals>::s_HalfCircleDegree = 180.0f;
template <int TVerticals> const float CCone<TVerticals>::s_QuarterCircleDegree = 90.0f;
