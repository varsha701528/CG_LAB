#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define PI 3.14
float theta;

struct points
{
    float x,y,z;
};

void bino(int n,int *c)

{
    int j,k;
    for(k=0;k<=n;k++)
    {
        c[k]=1;
        for(j=n;j>=k+1;j--)
            c[k]*=j;
        for(j=n-k;j>=2;j--)
            c[k]/=j;
    }
}

void compute(float u,points *bezpt,int npts,points *pt,int *c)
{
    int n=npts-1,k;
    float blend;

    bezpt->x=bezpt->y=bezpt->z=0.0;
    for(k=0;k<npts;k++)
    {
        blend=c[k]*pow(u,k)*pow(1-u,n-k);

        bezpt->x+=pt[k].x*blend;
        bezpt->y+=pt[k].y*blend;
        bezpt->z+=pt[k].z*blend;

    }
}

void bezier(points *pt,int npts,int bcurvept)
{
    points bz;
    int k,*c;
    float u;
    c=new int[npts];
    bino(npts-1,c);
    glBegin(GL_LINE_STRIP);
    for(k=0;k<bcurvept;k++)
    {
        u=(float)k/(float)bcurvept;
        compute(u,&bz,npts,pt,c);
        glVertex2f(bz.x,bz.y);
    }
    glEnd();
    delete []c;
}

void display()
{
    int npts=4,bcurvept=20;

    points pt[4]={{20,100,0},{30,110,0},{50,90,0},{60,100,0}};

    pt[1].x+=5*sin(theta*PI/180);
    pt[1].y+=5*sin(theta*PI/180);

    pt[2].x+=5*sin((theta+30)*PI/180);
    pt[2].y+=5*sin((theta+30)*PI/180);

    pt[3].x+=5*sin(theta*PI/180);
    pt[3].y+=5*sin((theta-30)*PI/180);

    theta+=0.1;
    glColor3f(1.0,1.0,1.0);

    glPointSize(5);
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5);

    glColor3f(1.0,0.5,0.1);
    for(int i=0;i<8;i++)
    {
        glTranslated(0,-0.8,0);
        bezier(pt,npts,bcurvept);
    }

    glColor3f(1.0,1.0,1.0);
    for(int i=0;i<8;i++)
    {
        glTranslated(0,-0.8,0);
        bezier(pt,npts,bcurvept);
    }

    glColor3f(0.1,1.0,0.1);
    for(int i=0;i<8;i++)
    {
        glTranslated(0,-0.8,0);
        bezier(pt,npts,bcurvept);
    }

    glPopMatrix();


    glLineWidth(5);

    glBegin(GL_LINES);
        glColor3f(0.7,0.5,0.3);
    glVertex2f(20,40);
    glVertex2f(20,100);
    glEnd();

    glFlush();
    glutPostRedisplay();
    //glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,100,0,120);
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("hi");

    glutInitWindowPosition(50,50);
    glutInitWindowSize(700,700);
        init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

