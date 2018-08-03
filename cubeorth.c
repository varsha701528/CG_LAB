#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

float ver[][3]={{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};
float theta[]={0,0,0};
int axis=2;
float view[]={0,0,5};
void polygon(int a,int b,int c,int d)
{
	//glColor3f(1,0,0);
	glBegin(GL_POLYGON);
glColor3f(.5,0,0.6);
	glVertex3fv(ver[a]);
glColor3f(1,0.2,0.2);
	glVertex3fv(ver[b]);
glColor3f(1,0.5,0.5);
	glVertex3fv(ver[c]);
glColor3f(1,1,0);
	glVertex3fv(ver[d]);
	glEnd();
}

void color_cube()
{
	glColor3f(1.0,1.0,0.0);
	polygon(0,3,2,1);

	glColor3f(1.0,0.7,0.0);
	polygon(2,3,7,6);

	glColor3f(1.0,1.0,1.0);
	polygon(0,4,7,3);

	glColor3f(1.0,0.0,1.0);
	polygon(1,2,6,5);

	glColor3f(0.4,0.6,0.8);
	polygon(4,5,6,7);

	glColor3f(0.8,0.2,0.1);
	polygon(0,1,5,4);


}

void init()
{
	//glOrtho(-2,2,-2,2,-10,10);
        glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2,2,-2,2,2,10);
	glMatrixMode(GL_MODELVIEW);

	//glLoadIdentity();
}

void display()
{	glClearColor(0,0,0,1);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(view[0],view[1],view[2],0,0,0,0,1,0);
	glRotatef(theta[0],1,0,0);
	glRotatef(theta[1],0,1,0);
	glRotatef(theta[2],0,0,1);
	color_cube();

	glFlush();
	glutSwapBuffers();

}

void spin_cube()
{
	theta[axis]+=0.01;
	if(theta[axis]>360)
	{
		theta[axis]-=360;
	}
	glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		axis=0;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
			axis=2;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
			axis=1;
}
void keyboard(char key,int x,int y)
{
    if(key=='x')
        view[0]-=1;
    if(key=='X')
        view[0]+=1;

    if(key=='y')
        view[1]-=1;
    if(key=='Y')
        view[1]+=1;
    if(key=='z')
        view[2]-=1;
    if(key=='Z')
        view[2]+=1;

}
/*void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,-10,10);
	glMatrixMode(GL_MODELVIEW);
}
*/
void main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(500,500);
	glutCreateWindow("Spin Cube");
	init();
	glutIdleFunc(spin_cube);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	//glutReshapeFunc(reshape);
	glutDisplayFunc(display);
        glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
