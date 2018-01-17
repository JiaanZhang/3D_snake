#include <string>
#include <vector>
#include <array>
using namespace std;

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

class body
{
public:
    body();
	body(float x, float y, float z);
	void changeY(float amount);
	void changeX(float amount);
	void changeZ(float amount);
    void reZ(float amount);
    void reX(float amount);
    void reY(float amount);
	float getY();
	float getX();
	float getZ();
	void draw();
    void get_food(int num);
    void dele_food();
    void draw_food();



private:
	float x, y, z;
    GLUquadricObj *sphere = NULL;
    GLuint mysphereID;
    int food_plane;
};


class Snake
{
public:
	Snake();
	void move( int mode);
	void draw();
	//float* position();
	std::array<float, 3> position();
    std::array<float, 3> vposition(int index);
	void col_food();
    void stop_move();
    bool get_move();
    int snake_size();
private:
	std::vector<body> body_list;
	bool food_col = false;
	int size = 12;
    bool stop = false;
};



