#pragma once
#include <iostream> //for debug
#define _USE_MATH_DEFINES 
#include <math.h>


class CQuader
{

public:
  
	CQuader(float _A) : 
		m_X(0), 
		m_Y(0),
		m_Z(0), 
		m_A(_A), 
		m_B(_A),
		m_C(_A)
	{}

	CQuader(float _A, float _B) : 
		m_X(0), 
		m_Y(0),
		m_Z(0), 
		m_A(_A), 
		m_B(_B),
		m_C(_B)
	{}

	CQuader(float _A, float _B, float _C) : 
		m_X(0), 
		m_Y(0),
		m_Z(0), 
		m_A(_A), 
		m_B(_B),
		m_C(_C)
	{}

	~CQuader()
	{}
	
	void GetVertices()
	{
		float HalfA = m_A / 2, HalfB = m_B / 2, HalfC = m_C / 2;
		
		m_VerticesArray[0][0] = HalfA;
		m_VerticesArray[0][1] = HalfB;
		m_VerticesArray[0][2] = HalfC;

		m_VerticesArray[1][0] = HalfA;
		m_VerticesArray[1][1] = HalfB;
		m_VerticesArray[1][2] = -HalfC;
		
		m_VerticesArray[2][0] = HalfA;
		m_VerticesArray[2][1] = -HalfB;
		m_VerticesArray[2][2] = HalfC;
		
		m_VerticesArray[3][0] = HalfA;
		m_VerticesArray[3][1] = -HalfB;
		m_VerticesArray[3][2] = -HalfC;

		m_VerticesArray[4][0] = -HalfA;
		m_VerticesArray[4][1] = HalfB;
		m_VerticesArray[4][2] = HalfC;

		m_VerticesArray[5][0] = -HalfA;
		m_VerticesArray[5][1] = HalfB;
		m_VerticesArray[5][2] = -HalfC;
		
		m_VerticesArray[6][0] = -HalfA;
		m_VerticesArray[6][1] = -HalfB;
		m_VerticesArray[6][2] = HalfC;
		
		m_VerticesArray[7][0] = -HalfA;
		m_VerticesArray[7][1] = -HalfB;
		m_VerticesArray[7][2] = -HalfC;
	}

	int GetVerticesCount()
	{
		return s_VerticesCount;
	}
	
	void GetTriangles()
	{
		m_TrianglesArray[0][0] = 2;
		m_TrianglesArray[0][1] = 6;
		m_TrianglesArray[0][2] = 0;
		m_TrianglesArray[1][0] = 0;
		m_TrianglesArray[1][1] = 6;
		m_TrianglesArray[1][2] = 4;

		m_TrianglesArray[2][0] = 6;
		m_TrianglesArray[2][1] = 7;
		m_TrianglesArray[2][2] = 4;
		m_TrianglesArray[3][0] = 4;
		m_TrianglesArray[3][1] = 7;
		m_TrianglesArray[3][2] = 5;
		
		m_TrianglesArray[4][0] = 7;
		m_TrianglesArray[4][1] = 3;
		m_TrianglesArray[4][2] = 5;
		m_TrianglesArray[5][0] = 5;
		m_TrianglesArray[5][1] = 3;
		m_TrianglesArray[5][2] = 1;
		
		m_TrianglesArray[6][0] = 3;
		m_TrianglesArray[6][1] = 2;
		m_TrianglesArray[6][2] = 1;
		m_TrianglesArray[7][0] = 1;
		m_TrianglesArray[7][1] = 2;
		m_TrianglesArray[7][2] = 0;
		
		m_TrianglesArray[8][0] = 0;
		m_TrianglesArray[8][1] = 4;
		m_TrianglesArray[8][2] = 1;
		m_TrianglesArray[9][0] = 1;
		m_TrianglesArray[9][1] = 4;
		m_TrianglesArray[9][2] = 5;

		m_TrianglesArray[10][0] = 2;
		m_TrianglesArray[10][1] = 3;
		m_TrianglesArray[10][2] = 6;
		m_TrianglesArray[11][0] = 6;
		m_TrianglesArray[11][1] = 3;
		m_TrianglesArray[11][2] = 7;
	}

	int GetTrianglesCount()
	{
		return s_TrianglesCount;
	}
	
private:

	float				m_X, m_Y, m_Z;
	float				m_A, m_B, m_C;
	enum {
						s_VerticesCount					= 8,
						s_TrianglesCount				= 12,
	};

public:
	
	float				m_VerticesArray[s_VerticesCount][3];
	int					m_TrianglesArray[s_TrianglesCount][3];

};
