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
extern int *vertexCount;
//array of bitarrays of which points are present on each layer
extern bitarray *pointsPresent;

//allocates memory ot pointList, and generates safe point locations
extern void genPoints();
//calculates all the centers
extern void calcCenter();
//generates a zeroed bitarray
extern bitarray genBitarray(int size);
//sets index bit to value
extern void setBit(bitarray in, int index, int value);
//returns value of index bit
extern int getBit(bitarray in, int index);
//generates the center
extern void setVertex(int layer, int ind1, int ind2, int ind3, vertex* target);
//checks to see if vertex is valid (AKA has no other points closer than it's parents)
extern int isGoodVertex(int layer, vertex test);
