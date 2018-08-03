
#include<stdio.h>
#include<GL/glut.h>

float x1=200.0,y1=200.0,x2=100.0,y2=300.0,x3=200.0,y3=400.0,x4=300.0,y4=300.0;
int flag=0;

void draw_pixel(int x,int y)
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}


void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
    float mx,x,temp;

    if((y2-y1)<0)
    {
        temp=x2;
        x2=x1;
        x1=temp;
        temp=y2;
        y2=y1;
        y1=temp;

    }
   if((y2-y1)!=0)
    {
        mx=(x2-x1)/(y2-y1);
    }

    else
        mx=x2-x1;

    x=x1;
    for(int i=y1;i<=y2;i++)
    {
        if(x<(float)le[i])
            le[i]=(int)x;
       if(x>(float)re[i])
            re[i]=(int)x;

        x+=mx;
    }
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
    int le[500],re[500];

    for(int i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }

    edgedetect(x1,y1,x2,y2,le,re);

    edgedetect(x2,y2,x3,y3,le,re);

    edgedetect(x3,y3,x4,y4,le,re);
    edgedetect(x4,y4,x1,y1,le,re);


    for(int i=0;i<500;i++)
    {
        if(le[i]<=re[i])
        {
            for(int j=(int)le[i];j<(int)re[i];j++)
            {
                draw_pixel(j,i);
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();
    if(flag==1)
        scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
    glFlush();

}
void init()
{
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}
void scanmenu(int id)
{
    if(id==1)
        flag=1;
    else if(id==2)
        flag=0;
    else
        exit(0);
    glutPostRedisplay();
}

void  main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("Clip");
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    init();
    glutDisplayFunc(display);
    glutCreateMenu(scanmenu);
    glutAddMenuEntry("Fill",1);
    glutAddMenuEntry("Clear",2);
    glutAddMenuEntry("Exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
