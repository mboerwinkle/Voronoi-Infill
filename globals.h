#define MAXX 100000//in micrometers (10cm)
#define MAXY 100000
#define MAXZ 100000
#define POINTS 200

typedef int scalar;
typedef scalar point3d[3];
typedef scalar point2d[2];
typedef struct center{
	point2d loc;
	point3d *parents[3];
}center;


extern point3d *pointList;
extern center *centers;

extern void genPoints();
