extern int maxx, maxy, maxz, points, step, distpoints;
typedef int* bitarray;
typedef long int scalar;
typedef scalar point3d[3];
typedef scalar point2d[2];
//vertices and nodes are mostly the same, it's just that vertices contain the info of their parents, while nodes contain the info of their sibling nodes. Nodes are used because they are better for path generation
//temporary. Eventually, calcCenter will generate nodes exclusively, and use vertices as intermediaries
typedef struct vertex{
	point2d loc;
	point3d *parents[3];
}vertex;
typedef struct line2d{
	point2d end[2];
	int parents[2];
}line2d;
typedef struct node{
	point2d loc;
	int sibCount;
	int* sibs;
}node;
//list of all boundary points (for cropping)
extern point2d *bP;
//point inside of bounds
extern point2d insideBounds;
//count of boundary points
extern long int bPcount;
//list of all starting points
extern point3d *pointList;
//array of arrays of vertices on each layer
extern vertex **vertexList;
//array of length of each array of vertexList
extern int *vertexCount;
//array of arrays of lines on each layer
extern line2d **lineList;
//array of length of each array of lineList
extern int *lineCount;
//array of arrays of nodes on each layer
extern node **nodeList;
//array of length of each array of nodeList
extern int *nodeCount;
//array of bitarrays of which points are present on each layer
extern bitarray *pointsPresent;

//allocates memory ot pointList, and generates safe point locations
extern void genPoints();
//calculates all the vertices (centers is the term I used to use)
extern void calcCenter();
//calculates all the lines between points(whether or not they are valid is addressed in cropLines
extern void calcLines();
//crops lines to generate valid power diagrams on a layer
extern void cropLines(int layer);
//calculates nodes based on the lines
extern void genNodes();
//generates a zeroed bitarray
extern bitarray genBitarray(int size);
//sets index bit to value
extern void setBit(bitarray in, int index, int value);
//returns value of index bit
extern int getBit(bitarray in, int index);
//ORs two identically sized bitarrays and returns the resultant bitarray
extern bitarray ORBitarray(bitarray one, bitarray two, int size);
//returns the string representation of bitarray
extern char* printBitarray(bitarray in, int size);
//generates the center
extern int setVertex(int layer, int ind1, int ind2, int ind3, vertex* target);
//calculates the intersection of two 2d lines. returns 1 if points are parallel.
extern int lineIntersect2d(point2d a1, point2d a2, point2d b1, point2d b2, scalar* x, scalar* y);
//gets the closest equidistant point on the given plane (layer) to the two points. Also known as the weighted midpoint function that is given two 3d points instead of two weighted 2d points.
//returns 1 if two points are on top of each other (error)
extern int planeIntersect(int layer, point3d one, point3d two, point2d ret);
//2d distance
extern scalar distance2d(point2d a, point2d b);
//2d distance squared (to avoid the nasty squareroot)
extern scalar distance2dsq(point2d a, point2d b);
//3d distance squared (to avoid the nasty squareroot)
extern scalar distance3dsq(point3d a, point3d b);
//displays the voronoi diagram. This description intentionally left ambiguous
extern void display();
//prints the specified layer as ascii art
extern void layer_to_ascii(int layer);
//prints the specified layer in an SDL window
extern void layer_to_SDL(int layer);
//prints a progress bar to terminal
extern void progressBar(int count, int max);
extern void openSDLwindow();
extern void closeSDLwindow();
//returns number of shared parents of two vertices
//extern int getSharedParentCount(vertex a, vertex b);
//crops all nodes to the inside of the boundary points
extern void cropNodes();
//returns the sibs index of the sib equal to targ, or -1
extern int findNodePointer(int targ, node *orig);
//generates the path of the head to take
extern void genPath();
//generates the path of the head to take for a single layer
extern void genPathLayer(int layer);
//finds the intersection of two linesegments
extern int lineSegIntersect2d(point2d a1, point2d a2, point2d b1, point2d b2, point2d* sect/*for inter'sect*/);
extern void midpoint2d(point2d A, point2d B, point2d* ret);
//sorts point2d list inter (size "size") in order of increasing distance from "start"
extern void sortPointList(point2d start, point2d* inter, int size);
extern int lineSharesParent(line2d *A, line2d *B);
extern void combineNodes(int layer);
