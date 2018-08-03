#include<stdio.h>
#include<GL/glut.h>

float ver[4][3]={{0,0,1},{-1,-1,-1},{1,-1,-1},{0,1,-1}};

int m;

void triangle(float *a,float *b,float *c)
{
    glBegin(GL_TRIANGLES);
    //glColor3f(1.0,1.0,0.0);
    glVertex3fv(a);
    //glColor3f(0.0,1.0,0.0);
    glVertex3fv(b);
    // glColor3f(0.0,1.0,1.0);
    glVertex3fv(c);

glEnd();
}

void divide_triangle(float *a,float *b,float *c,int m)
{
    float v1[3],v2[3],v3[3];
    if(m>0)
    {
        for(int i=0;i<3;i++)
        {
            v1[i]=(a[i]+b[i])/2;

        }
        for(int i=0;i<3;i++)
        {
            v2[i]=(c[i]+b[i])/2;

        }
        for(int i=0;i<3;i++)
        {
            v3[i]=(a[i]+c[i])/2;

        }



        divide_triangle(a,v1,v3,m-1);
        divide_triangle(b,v1,v2,m-1);
        divide_triangle(c,v2,v3,m-1);
    }
    else
        triangle(a,b,c);
}

void tetrahedron(int m)
{
    divide_triangle(ver[0],ver[1],ver[2],m);
    glColor3f(1.0,1.0,0.0);
    divide_triangle(ver[1],ver[0],ver[3],m);
    glColor3f(0.0,1.0,0.0);
    divide_triangle(ver[0],ver[2],ver[3],m);
    glColor3f(1.0,0.0,1.0);
    divide_triangle(ver[1],ver[2],ver[3],m);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glClearColor(0,0,0,1);
    glLoadIdentity();
gluLookAt(0,0,2,0,0,0,0,1,0);
    tetrahedron(m);
    glFlush();
    //glutSwapBuffers();
}
void init()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,-10,10);
    glMatrixMode(GL_MODELVIEW);

}
void main(int argc,char **argv)
{
    glutInit(&argc,argv);
    printf("enter m\n");
    scanf("%d",&m);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);

    glutCreateWindow("gasket");
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);init();
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

