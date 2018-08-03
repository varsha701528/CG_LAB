#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

float triangle[3][3]={{150,250,350},{200,400,200},{1,1,1}};
float rot_mat[3][3]={{0},{0},{0}};
float result[3][3]={{0},{0},{0}};

float m=0,n=0,h=0,k=0,theta;

void multiply()
{
    int i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            result[i][j]=0;

            for(k=0;k<3;k++)
            {
                result[i][j]=result[i][j]+rot_mat[i][k]*triangle[k][j];
            }
        }
    }
}
void rotate(float m,float n)
{
    rot_mat[0][0]=cos(theta);
    rot_mat[0][1]=-sin(theta);
    rot_mat[0][2]=m;
    rot_mat[1][0]=sin(theta);
    rot_mat[1][1]=cos(theta);
    rot_mat[1][2]=n;
    rot_mat[2][0]=0;
    rot_mat[2][1]=0;
    rot_mat[2][2]=1;

    multiply();
}

void draw_triangle()
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(triangle[0][0],triangle[1][0]);
    glVertex2f(triangle[0][1],triangle[1][1]);
    glVertex2f(triangle[0][2],triangle[1][2]);
    glEnd();
}

void draw_rotated_triangle()
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(result[0][0],result[1][0]);
    glVertex2f(result[0][1],result[1][1]);
    glVertex2f(result[0][2],result[1][2]);
    glEnd();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(0,1,1);
    draw_triangle();


    rotate(0,0);glColor3f(1,1,0);
    draw_rotated_triangle();




    m=-h*(cos(theta)-1)+k*sin(theta);
    n=-k*(cos(theta)-1)-h*sin(theta);
    rotate(m,n);glColor3f(1,0,0);
    draw_rotated_triangle();

glFlush();

}
void main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    printf("Enter h and k and theta\n");
    scanf("%f%f%f",&h,&k,&theta);
    theta=(theta)*(3.14)/180;
    glutCreateWindow("rot");
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(0,0);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
