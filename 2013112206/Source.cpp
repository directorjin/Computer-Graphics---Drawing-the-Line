#include <stdlib.h>
#include <gl/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>
using std::vector;
using std::cin;
using std::cout;
using std::string;


	vector<int> fx;
	vector<int> fy;
	vector<int> fx1;
	vector<int> fy1;
	vector<int> R;
	vector<int> G;
	vector<int> B;

	int q = 0;
int Width = 800, Height = 600;
int count = 0;
int c = 0;
int ix;
int iy;
int k = 0;
int s = 0;

void MouseFunc(int button, int state, int x, int y)
{
	
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && count==1) //마지막 점 연결
	{
		fx.push_back(x);
		fy.push_back(y);
		count=2;
		c++;
		glutPostRedisplay();
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //처음 점 선택
	{
		fx.push_back(x);
		fy.push_back(y);
		count=1;
		c++;

	}

}
	
	
void MouseMove(int x,int y)
{
		ix = x;
		iy = y;
		glutPostRedisplay();
}

void SetUpViewTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.0);
}

void SetupViewVolume()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -100.0, 100.0);
}

void Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetUpViewTransform();

	SetupViewVolume();

	glMatrixMode(GL_MODELVIEW);

	// darw
	if (count == 2)
	{
		int r = (char)rand() % 256;
		R.push_back(r);
		int g = (char)rand() % 256;
		G.push_back(g);
		int b = (char)rand() % 256;
		B.push_back(b);
		k++;
		glColor3ub(R[k-1], G[k-1], B[k-1]);
		glBegin(GL_LINES);
		glVertex3f(fx[c - 2], Height - fy[c - 2], 0.0);
		glVertex3f(fx[c - 1], Height - fy[c - 1], 0.0);
		glEnd();
		
		fx1.push_back(fx[c-2]);
		fy1.push_back(fy[c-2]);
		fx1.push_back(fx[c-1]);
		fy1.push_back(fy[c-1]);
		count = 0;

	}
	else if (count == 1)
	{
		glColor3ub(192, 192, 192);
		srand((unsigned)time(NULL));
		glBegin(GL_LINES);
		glVertex3f(fx[c - 1], Height - fy[c - 1], 0.0);
		glVertex3f(ix, Height - iy, 0.0);
		glEnd();
		

	}

	if (k > 0)
	{
		for (int i = 0; i < k; i++)
		{

			glColor3ub(R[i], G[i], B[i]);
			glBegin(GL_LINES);
			glVertex3f(fx1[s], Height - fy1[s], 0.0);
			glVertex3f(fx1[s+1], Height - fy1[s+1], 0.0);
			glEnd();
			s++;
			s++;
		}
		s = 0;
	}

	
	
	

	

	glutSwapBuffers();

	}

/*
void Reshape(int w ,int h)
{
	glViewport(0, 0, w, h);
	GLfloat WidthFactor = (GLfloat)w / (GLfloat)800;
	GLfloat HeightFactor = (GLfloat)h / (GLfloat)600;
	glOrtho(0, 800, 0, 600, -100.0, 100.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	


}
*/

int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	srand((unsigned)time(NULL));
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("문제");

	glutDisplayFunc(Render);
	/*
	glutReshapeFunc(Reshape);
	*/
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MouseFunc);



	glutMainLoop();

	return 0;
}