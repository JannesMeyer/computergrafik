////////////////////////////////////////////////////////////////////
// FILE:        vec3.h
//
// AUTHOR:      Martin Bertram
//
// DESCRIPTION:	a vector class to represent 3-D points and vectors
////////////////////////////////////////////////////////////////////

#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// constants ///////////////////////////////////////////////////////

#define	VEC_DIM	3
#define VEC_INF 1.0e9
#define VEC_EPS 1.0e-9

#define Null3 Vec3( 0.0, 0.0, 0.0)
#define XVec3 Vec3( 1.0, 0.0, 0.0)
#define YVec3 Vec3( 0.0, 1.0, 0.0)
#define ZVec3 Vec3( 0.0, 0.0, 1.0)


// 3D points and vectors /////////////////////////////////////////////
class Vec3{ public:
	double	p[VEC_DIM];

	Vec3(){
	}

	Vec3( double *x){
		for( int i=0; i<VEC_DIM; i++) p[i] = x[i];
	}

	Vec3( FILE *fp){
		for( int i=0; i<VEC_DIM; i++) fscanf( fp, "%lf,", &p[i]);
	}

	Vec3( const Vec3 &a){
		p[0] = a.p[0];
		p[1] = a.p[1];
		p[2] = a.p[2];
	}

	Vec3( double x, double y, double z){
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}

	// scalar-vector arithmetics //////////////////////////////
	Vec3	&operator=( Vec3 a){
		for( int i=0; i<VEC_DIM; i++) p[i] = a.p[i];
		return *this;
	}

	Vec3	&operator+=( Vec3 a){
		for( int i=0; i<VEC_DIM; i++) p[i] += a.p[i];
		return *this;
	}

	Vec3	&operator-=( Vec3 a){
		for( int i=0; i<VEC_DIM; i++) p[i] -= a.p[i];
		return *this;
	}

	Vec3	&operator*=( double sc){
		for( int i=0; i<VEC_DIM; i++) p[i] *= sc;
		return *this;
	}

	Vec3	&operator/=( double sc){
		for( int i=0; i<VEC_DIM; i++) p[i] /= sc;
		return *this;
	}

	friend Vec3 operator-( Vec3 a){
		Vec3 c = Vec3();
		for( int i=0; i<VEC_DIM; i++) c.p[i] = -a.p[i];
		return c;
	}

	friend Vec3 operator+( Vec3 a, Vec3 b){
		Vec3 c = Vec3();
		for( int i=0; i<VEC_DIM; i++) c.p[i] = a.p[i] + b.p[i];
		return c;
	}

	friend Vec3 operator-( Vec3 a, Vec3 b){
		Vec3 c = Vec3();
		for( int i=0; i<VEC_DIM; i++) c.p[i] = a.p[i] - b.p[i];
		return c;
	}

	friend Vec3 operator*( double sc, Vec3 a){
		Vec3 c = Vec3();
		for( int i=0; i<VEC_DIM; i++) c.p[i] = a.p[i] * sc;
		return c;
	}

	friend Vec3 operator*( Vec3 a, double sc){
		Vec3 c = Vec3();
		for( int i=0; i<VEC_DIM; i++) c.p[i] = a.p[i] * sc;
		return c;
	}

	friend Vec3 operator/( Vec3 a, double sc){
		Vec3 c = Vec3();
		for( int i=0; i<VEC_DIM; i++) c.p[i] = a.p[i] / sc;
		return c;
	}

	// dot product ////////////////////////////////////////////////
	friend double operator*( Vec3 a, Vec3 b){
		double r = 0;
		for( int i=0; i<VEC_DIM; i++) r += a.p[i] * b.p[i];
		return r;
	}

	// cross product //////////////////////////////////////////////
	friend Vec3 operator%( Vec3 a, Vec3 b){
		double	x, y, z;
		x = a.p[1] * b.p[2] - a.p[2] * b.p[1];
		y = a.p[2] * b.p[0] - a.p[0] * b.p[2];
		z = a.p[0] * b.p[1] - a.p[1] * b.p[0];
		return Vec3( x, y, z);
	}

	double Length(){
		double r = 0;
		for( int i=0; i<VEC_DIM; i++) r += p[i] * p[i];
		return sqrt( r);
	}

	double Length2(){
		double r = 0;
		for( int i=0; i<VEC_DIM; i++) r += p[i] * p[i];
		return r;
	}

	void Normalize(){
		double l = 1.0 / Length();
		for( int i=0; i<VEC_DIM; i++) p[i] *= l;
	}

        double LengthXY(){
                return sqrt( p[0]*p[0] + p[1]*p[1]);
        }

        double LengthXY2(){
                return p[0]*p[0] + p[1]*p[1];
        }

        double DotXY( Vec3 a){
                return p[0]*a.p[0] + p[1]*a.p[1];
        }

        double CrossXY( Vec3 a){
                return p[0]*a.p[1] - p[1]*a.p[0];
        }

        void MinMaxExpand( Vec3 *min, Vec3 *max){
                for( int i=0; i<VEC_DIM; i++){
                        if( p[i] < min->p[i]) min->p[i] = p[i];
                        if( p[i] > max->p[i]) max->p[i] = p[i];
                }
        }

	void Print( char *c = NULL){
		if( c == NULL) c = "Vec3";
		printf("%s = (", c);
		for( int i=0; i<VEC_DIM; i++) printf(" %12.9lf", p[i]);
		printf(")\n");
	}

	void FScan( FILE *fp){
		for( int i=0; i<VEC_DIM; i++) fscanf( fp, "%lf", &p[i]);
	}

	void FPrint( FILE *fp){
		for( int i=0; i<VEC_DIM; i++) fprintf( fp, " %12.9lf", p[i]);
	}



};


#endif
// EOF
