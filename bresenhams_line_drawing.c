#include<stdio.h>
#include<GL/glut.h>
int x1,x2,y1,y2;

void draw_pixel(int x,int y)
{
    glColor3f(1.0,0.88,0.45);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void draw_line(int x1,int y1,int x2,int y2)
{
    int dx,dy,x,y,e,inc1,inc2,incx,incy;
    x=x1;
    y=y1;
    dx=x2-x1;
    dy=y2-y1;

    incx=1;incy=1;
    if(dx<0)
    {
        incx=-1;
        dx=-dx;

    }
    if(dy<0)
    {
        incy=-1;
        dy=-dy;

    }

    if(dx>dy)
    {
        draw_pixel(x,y);
        e=2*dy-dx;
        inc1=2*(dy-dx);
        inc2=2*dy;

        for(int i=0;i<dx;i++)
        {
            if(e>=0)
            {
                y+=incy;
                e+=inc1;
            }
            else
                e+=inc2;
            x+=incx;
            draw_pixel(x,y);
        }
    }

    else

    {
        draw_pixel(x,y);
        e=2*dx-dy;
        inc1=2*(dx-dy);
        inc2=2*dx;

        for(int i=0;i<dy;i++)
        {
            if(e>=0)
            {
                x+=incx;
                e+=inc1;
            }
            else
                e+=inc2;
            y+=incy;
            draw_pixel(x,y);
        }
    }
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,300,0,300);
    glMatrixMode(GL_MODELVIEW);
}
void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_line(150,100,200,70);

    glFlush();
}
void main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("line");
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
