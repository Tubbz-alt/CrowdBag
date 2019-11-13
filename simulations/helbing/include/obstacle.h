#ifndef OBSTACLE_H
#define OBSTACLE_H

#ifdef USE_SDL
    #ifdef _MSC_VER
     #include <SDL.h>
     #include <SDL_OpenGL.h>
    #else
     #include <SDL/SDL.h>
     #include <SDL/SDL_OpenGL.h>
    #endif
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
#include "vec2f.h"
namespace helbing {

#define MAX_OBS 2048

void initObs();
void initObsFromFile(char * filename, bool useKDtree = true);
bool isVisible(vec2f src, vec2f tgt, float rad);
bool isVisibleSlow(vec2f src, vec2f tgt);
bool isVisibleKD(vec2f src, vec2f tgt);

struct lineObstacle{
    vec2f a,b;

    float time_to_collision(vec2f p, vec2f v, bool collision = false) { //Code from Jur van den Berg
        // returns the time to collision of ray p + tv to segment ab
        float inf = collision ? -9e9 : 9e9;

        vec2f ba, ap;
        ba.x = b.x-a.x;
        ba.y = b.y-a.y;

        float D = det(v, ba);
        if (D == 0) {  // ray and line are collinear
            return inf;
        }

        float invD = 1.f/D;
        ap.x = a.x-p.x;
        ap.y = a.y-p.y;
        float t = det(ap, ba) * invD;
        if (t > 0){
            ap.negate();
            float s = det(ap, v) * -invD;
            if (s > 0 && s < 1) {
                return t;
            }
        }
        return inf;
    }

    static float time_to_collision(vec2f p, vec2f v, vec2f a, vec2f b, bool collision = false) { //Code from Jur van den Berg
        // returns the time to collision of ray p + tv to segment ab
        float inf = collision ? -9e9 : 9e9;

        vec2f ba, ap;
        ba.x = b.x-a.x;
        ba.y = b.y-a.y;

        float D = det(v, ba);
        if (D == 0) {  // ray and line are collinear
            return inf;
        }

        float invD = 1.f/D;
        ap.x = a.x-p.x;
        ap.y = a.y-p.y;
        float t = det(ap, ba) * invD;
        if (t > 0){
            ap.negate();
            float s = det(ap, v) * -invD;
            if (s > 0 && s < 1) {
                return t;
            }
        }
        return inf;
    }

    static float time_to_collision(vec2f apos, vec2f veli, vec2f bpos, double rad, bool colliding){
        double a = (veli.x)*(veli.x) + (veli.y)*(veli.y);
        double b = 2*( (veli.x)*(apos.x - bpos.x)+(veli.y)*(apos.y - bpos.y));
        double c = bpos.x*bpos.x+bpos.y*bpos.y+apos.x*apos.x+apos.y*apos.y-2*(bpos.x*apos.x + bpos.y*apos.y)-(rad)*(rad);
        double disc = b*b - 4*a*c;
        double t = 9e9;
        if (disc > 0){
            if(!colliding){
                double ttemp = (-b - sqrt(disc))/(2*a);
                if (ttemp >= 0) t = ttemp;
            }
            else{
                t = (-b + sqrt(disc))/(2*a);
            }
        }
        return t;
    }

    float best(float a,float b,bool intersecting){
        if (intersecting)
            return a > b ? a : b;
        else
            return a < b ? a : b;
    }

    float distanceToVO(vec2f pos, vec2f vel, float r, bool intersecting){ //Velocity Obstacle
		float t;
		t = time_to_collision(pos, vel, a, r, intersecting);
		t = best(t,time_to_collision(pos, vel, b, r, intersecting),intersecting);
		vec2f perp = vec2f(b.y-a.y,a.x-b.x);
		normalize(perp);
		t = best(t,time_to_collision(pos, vel, a+perp*r, b+perp*r, intersecting),intersecting);
		t = best(t,time_to_collision(pos, vel, a-perp*r, b-perp*r, intersecting),intersecting);
		return t;
	}

    void init(float ax, float ay, float bx, float by){
        a.x = ax;
        a.y = ay;
        b.x = bx;
        b.y = by;
    }

    bool collide(vec2f start, vec2f end){
        vec2f tmp;
        tmp.x = end.x-start.x;
        tmp.y = end.y-start.y;
        float t = time_to_collision(start, tmp);
		if (t < 1)
			return true;
		else
			return false;
    }

    #ifdef USE_SDL
    void draw(){
        glColor3f(.1,.1,1);
        glBegin(GL_QUADS);
            glVertex3f(a.x,a.y,0);
            glVertex3f(a.x,a.y,10);
			glVertex3f(b.x,b.y,10);
			glVertex3f(b.x,b.y,0);
        glEnd();

        glLineWidth(1);
		glBegin(GL_LINES);
			glVertex3f(a.x,a.y,10);
			glVertex3f(b.x,b.y,10);
		glEnd();
		glLineWidth(1);
    }
    #endif
};

extern lineObstacle obstacles[MAX_OBS];
extern unsigned numObstacles;

}


#endif
