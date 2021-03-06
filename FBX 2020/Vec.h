#ifndef VEC_H_
#define VEC_H_

struct Vec2
{
	/** Constructor */
	Vec2()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] x ¡
	* @param[in] y c
	*/
	Vec2(float x, float y)
	{
		X = x;
		Y = y;
	}

	/**
	* @brief Constructor
	* @param[in] Vec2 Rs[pVec2f[^
	*/
	Vec2(const Vec2& size)
	{
		this->X = size.X;
		this->Y = size.Y;
	}

	float X;	//!< Xl
	float Y;	//!< Yl
};


#endif