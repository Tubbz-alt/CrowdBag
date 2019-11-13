/**
 * @file Utils.h
 * @author Teofilo Dutra
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include "definitions.h"
#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

#include <sys/time.h>
#include <unistd.h>

static struct timeval start;
static struct timeval end;

static void tic()
{
	gettimeofday(&start, 0);
};

static void toc()
{
	gettimeofday(&end, 0);
	
	double starttime = start.tv_sec+start.tv_usec/1000000.0;
	double endtime = end.tv_sec+end.tv_usec/1000000.0;
	double time = endtime-starttime;
	
	std::cout<< time<< std::endl;
};

/**
 * This class has many useful methods.
 */
class Utils
{
private:
    Utils() {};
    ~Utils() {};
    
    static mFloat m_meter;
public:
    
    template<class T>
    inline static T min(T a, T b)
	{
	    return (a<=b)?a:b;
	}
    
    template<class T>
    inline static T max(T a, T b)
	{
	    return (a>=b)?a:b;
	}
    
    template<class T>
	inline static T clip (T x,  T min,  T max)
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
	
	template<class T>
    inline static T interpolate (mFloat alpha, T& x0, T& x1)
    {
        return x0 + ((x1 - x0) * alpha);
    }
    
    inline static void truncate(vec3& v, mFloat f)
    {
        mFloat n = glm::length(v);
        if (n>f)
            v = glm::normalize(v) * f;
    }
    
    inline static float signedAngle(vec2 a, vec2 b)
    {
        vec2 Au = glm::normalize(a);
        vec2 Bu = glm::normalize(b);
        
        return atan2( Au.x*Bu.y - Bu.x*Au.y, Au.x*Bu.x + Au.y*Bu.y );
    }
    
    static void printVector3D(const vec3& v);
    
    static void setMeter(mFloat meter);
    
    static mFloat getMeter();
    
    static char* readShaderSource(const char* shaderFile);
    
    static GLuint InitShader(const char* vShaderFile, const char* fShaderFile);
};

#endif
