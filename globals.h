//these MAX values are exclusive.
#define MAXX 100000//in micrometers (10cm)
#define MAXY 100000
#define MAXZ 100000
#define POINTS 200

typedef int* bitarray;
typedef int scalar;
typedef scalar point3d[3];
typedef scalar point2d[2];
typedef struct vertex{
	point2d loc;
	point3d *parents[3];
}vertex;

//list of all starting points
extern point3d *pointList;
//array of arrays of vertices on each layer
extern vertex **vertexList;
//array of length of each array of vertexList
extern int *vertexCount;
//array of bitarrays of which points are present on each layer
extern bitarray *pointsPresent;

//allocates memory ot pointList, and generates safe point locations
extern void genPoints();
//calculates all the vertices (centers is the term I used to use)
extern void calcCenter();
//generates a zeroed bitarray
extern bitarray genBitarray(int size);
//sets index bit to value
extern void setBit(bitarray in, int index, int value);
//returns value of index bit
extern int getBit(bitarray in, int index);
//generates the center
extern int setVertex(int layer, int ind1, int ind2, int ind3, vertex* target);
//checks to see if vertex is valid (AKA has no other points closer than it's parents)
extern int isGoodVertex(int layer, vertex test);
//calculates the intersection of two 2d lines. returns 1 if points are parallel.
extern int lineIntersect2d(point2d a1, point2d a2, point2d b1, point2d b2, int* x, int* y);
//returns the closest equidistant point on the given plane (layer) to the two points. Also known as the weighted midpoint function that is given two 3d points instead of two weighted 2d points.
extern void planeIntersect(int layer, point3d one, point3d two, point2d ret);
