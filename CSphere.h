#pragma once
#include <iostream> //for debug
#define _USE_MATH_DEFINES 
#include <math.h>


template <int THorizontals, int TVerticals>
class CSphere
{

public:

  typedef CSphere<THorizontals, TVerticals> CThis;
	enum
	{
		m_Horizontals = THorizontals,
		m_Verticals = TVerticals,
	};

public:

	CSphere(float _Radius) : 
		m_X(0), 
		m_Y(0),
		m_Z(0), 
		m_Radius(_Radius), 
		m_HorizontalsAngleDegree(s_HalfCircleDegree / (THorizontals + 1)), 
		m_VerticalsAngleDegree(s_CircleDegree / TVerticals)
	{}

	~CSphere()
	{}
	
	void GetVertices()
	{
		float X, Y, Z, Radius, AnglePiHalfCircleDegree;
		float AngleHorizontal = s_QuarterCircleDegree + m_HorizontalsAngleDegree;
		for (int Horizontal = 0; Horizontal < THorizontals; ++ Horizontal) {
			AnglePiHalfCircleDegree = AngleHorizontal * (float) M_PI / s_HalfCircleDegree;
			X = (m_X + m_Radius * cos(AnglePiHalfCircleDegree));
			Y = (m_Y + m_Radius * sin(AnglePiHalfCircleDegree));
			X = RoundF(X, 6);
			Y = RoundF(Y, 6);
			Radius = X;
			float AngleVertical = 0.0f;
			for (int Vertical = 0; Vertical < TVerticals; ++ Vertical) {
				AnglePiHalfCircleDegree = AngleVertical * (float) M_PI / s_HalfCircleDegree;
				X = (m_X + Radius * cos(AnglePiHalfCircleDegree));
				Z = (m_Z + Radius * sin(AnglePiHalfCircleDegree));
				X = RoundF(X, 6);
				Z = RoundF(Z, 6);
				int Index = (Horizontal * TVerticals) + Vertical;
				m_VerticesArray[Index][0] = X;
				m_VerticesArray[Index][1] = Y;
				m_VerticesArray[Index][2] = Z;
				AngleVertical += m_VerticalsAngleDegree;
			}
			AngleHorizontal += m_HorizontalsAngleDegree;
		}
		m_VerticesArray[s_VerticesCount - 2][0] = 0;
		m_VerticesArray[s_VerticesCount - 2][1] = m_Radius;
		m_VerticesArray[s_VerticesCount - 2][2] = 0;
		m_VerticesArray[s_VerticesCount - 1][0] = 0;
		m_VerticesArray[s_VerticesCount - 1][1] = -m_Radius;
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
		for (int Horizontal = 0; Horizontal <= THorizontals; ++ Horizontal) {
			for (int Vertical = 0; Vertical < TVerticals; ++ Vertical) {
				int Index = (Horizontal * TVerticals) + Vertical;
				int NextInHorizontal = ((Vertical + 1) % TVerticals) + TVerticals * Horizontal;
				if (Horizontal == 0) {
					m_TrianglesArray[TriangleIndex][0] = Index;
					m_TrianglesArray[TriangleIndex][1] = NextInHorizontal;
					m_TrianglesArray[TriangleIndex][2] = NorthVertex;
				} else if (Horizontal == THorizontals) {
					Index = Index - TVerticals;
					NextInHorizontal = NextInHorizontal - TVerticals;
					m_TrianglesArray[TriangleIndex][0] = Index;
					m_TrianglesArray[TriangleIndex][1] = SouthVertex;
					m_TrianglesArray[TriangleIndex][2] = NextInHorizontal;
				} else {
					int LastIndex = Index - TVerticals;
					int NextInLastHorizontal = ((Vertical + 1) % TVerticals) + TVerticals * (Horizontal - 1);
					m_TrianglesArray[TriangleIndex][0] = LastIndex;
					m_TrianglesArray[TriangleIndex][1] = Index;
					m_TrianglesArray[TriangleIndex ++][2] = NextInHorizontal;
					m_TrianglesArray[TriangleIndex][0] = LastIndex;
					m_TrianglesArray[TriangleIndex][1] = NextInHorizontal;
					m_TrianglesArray[TriangleIndex][2] = NextInLastHorizontal;
				}
				++TriangleIndex;
			}
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
	float				m_Radius;
	float				m_HorizontalsAngleDegree;
	float				m_VerticalsAngleDegree;
	enum {
						s_VerticesCount					= THorizontals * TVerticals + 2,
						s_TrianglesCount				= THorizontals * TVerticals  * 2,
	};
	static const float	s_CircleDegree;
	static const float	s_HalfCircleDegree;
	static const float	s_QuarterCircleDegree;

public:
	
	float				m_VerticesArray[s_VerticesCount][3];
	int					m_TrianglesArray[s_TrianglesCount][3];

};

template <int THorizontals, int TVerticals> const float CSphere<THorizontals, TVerticals>::s_CircleDegree = 360.0f;
template <int THorizontals, int TVerticals> const float CSphere<THorizontals, TVerticals>::s_HalfCircleDegree = 180.0f;
template <int THorizontals, int TVerticals> const float CSphere<THorizontals, TVerticals>::s_QuarterCircleDegree = 90.0f;
