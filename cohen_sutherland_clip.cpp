#include<stdio.h>
#include<GL/glut.h>

#define false 0
#define true 1
const int top=4,bottom=1,left=2,right=8;
float xmin=50,xmax=100,ymin=50,ymax=100,x,y;
int accept , done;
int out,out1,out2;

int outcode(float x,float y)
{
    int code=0;
    if(x>xmax)
        code|=right;
    else if(x<xmin)
        code|=left;
    if(y>ymax)
        code|=top;
    else if(y<ymin)
        code|=bottom;
    return code;
}

void cohen(float x1,float y1,float x2,float y2)
{
    int accept=false;
    int done=false;
    out1=outcode(x1,y1);
    out2=outcode(x2,y2);

    do
    {
        if(!(out1|out2))
        {
            done=true;
            accept=true;
        }
        else if(out1&out2)
        {
            done=true;
        }
        else
        {
            out=out1 ? out1:out2;

            if(out&top)
            {
                y=ymax;
                x=x1+(ymax-y1)*(x2-x1)/(y2-y1);


            }
            else if(out&bottom)
            {
                y=ymin;
                x=x1+(ymin-y1)*(x2-x1)/(y2-y1);
            }
            else if(out&left)
            {
                x=xmin;
                y=y1+(xmin-x1)*(y2-y1)/(x2-x1);
            }

            else
            {
                x=xmax;
                y=y1+(xmax-x1)*(y2-y1)/(x2-x1);
            }


            if(out==out1)
            {
                x1=x;
                y1=y;
                 out1=outcode(x1,y1);
            }
            else
            {
                x2=x;
                y2=y;
                 out2=outcode(x2,y2);
            }
        }
    }while(!done);

    if(accept)
    {
        glPushMatrix();
        glTranslated(100,100,0);
        glColor3f(1.0,0.0,1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(50,50);
        glVertex2f(50,100);
        glVertex2f(100,100);
        glVertex2f(100,50);
        glEnd();
        glColor3f(0.9,0.1,0.0);
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glEnd();

        glPopMatrix();
        glFlush();

    }
}

void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(50,50);
        glVertex2f(50,100);
        glVertex2f(100,100);
        glVertex2f(100,50);
        glEnd();
        glColor3f(0.9,0.1,0.0);
        glBegin(GL_LINES);
        glVertex2f(60,40);
        glVertex2f(100,120);
        glEnd();
        cohen(60,40,100,120);
        glFlush();

}
void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,300,0,300);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("clip");

    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(0,0);
    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
