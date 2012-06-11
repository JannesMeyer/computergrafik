#include "Subdivision.h"
/*
// When we increase the level of detail we will have to re-create the points
// array inserting the new intermediate points into it.
//
//	Basically the subdivision works like this. each line,
//
//            A  *------------*  B
//
//	will be split into 2 new points, Q and R.
//
//                   Q    R
//            A  *---|----|---*  B
//
//	Q and R are given by the equations :
//
// 		Q = 3/4*A + 1/4*B
// 		R = 3/4*B + 1/4*A
//
void increaseDetail() {
	unsigned int i;
	std::vector<Point> newPoints;

	// keep the first point
	newPoints.push_back(line->points.front());
	for (i = 0; i < (line->points.size() - 1); ++i) {
	
		// get 2 original points
		const Point& p0 = line->points[i];
		const Point& p1 = line->points[i+1];
		Point Q;
		Point R;

		// average the 2 original points to create 2 new points
		Q.x = 0.75 * p0.x + 0.25 * p1.x;
		Q.y = 0.75 * p0.y + 0.25 * p1.y;
		Q.z = 0.75 * p0.z + 0.25 * p1.z;

		R.x = 0.25 * p0.x + 0.75 * p1.x;
		R.y = 0.25 * p0.y + 0.75 * p1.y;
		R.z = 0.25 * p0.z + 0.75 * p1.z;

		newPoints.push_back(Q);
		newPoints.push_back(R);
	}
	// keep the last point
	newPoints.push_back(line->points.back());

	// update the points array
	line->points = newPoints;
}

// When we decrease the level of detail, we can rather niftily get back
// to exactly what we had before. Since the original subdivision
// simply required a basic ratio of both points, we can simply
// reverse the ratios to get the previous point...
//
void decreaseDetail() {
	// make sure we dont loose any points!!
	if (line->points.size() <= 4) {
		return;
	}

	unsigned int i;
	std::vector<Point> newPoints;

	// keep the first point
	newPoints.push_back(line->points.front());

	// step over every 2 points
	for(i = 1; i < (line->points.size() - 1); i += 2) {

		// get last point found in reduced array
		const Point& pLast = newPoints.back();

		// get 2 original point
		const Point& p0 = line->points[i];
		Point Q;

		// calculate the original point
		Q.x = p0.x - 0.75 * pLast.x;
		Q.y = p0.y - 0.75 * pLast.y;
		Q.z = p0.z - 0.75 * pLast.z;

		Q.x *= 4.0;
		Q.y *= 4.0;
		Q.z *= 4.0;

		// add to new curve
		newPoints.push_back(Q);
	}

	// copy over points
	line->points = newPoints;
}
*/