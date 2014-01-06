#include "stdafx.h"

#include <windows.h>

#include <GL/glu.h>

#include <GL/gl.h>

#include <GL/glut.h>

void background(void)

{

//���ñ�����ɫΪ��ɫ

glClearColor(0.0,0.0,0.0,0.0);

}

 

void myDisplay(void)

{

//buffer����Ϊ��ɫ��д

glClear(GL_COLOR_BUFFER_BIT);

//��ʼ��������

glBegin(GL_TRIANGLES);

//����Ϊ�⻬����ģʽ

glShadeModel(GL_SMOOTH);

//���õ�һ������Ϊ��ɫ

glColor3f(1.0,0.0,0.0);

//���õ�һ�����������Ϊ��-1.0��-1.0��

glVertex2f(-1.0,-1.0);

//���õڶ�������Ϊ��ɫ

glColor3f(0.0,1.0,0.0);

//���õڶ������������Ϊ��0.0��-1.0��

glVertex2f(0.0,-1.0);

//���õ���������Ϊ��ɫ

glColor3f(0.0,0.0,1.0);

//���õ��������������Ϊ��-0.5��1.0��

glVertex2f(-0.5,1.0);

//�����ν���

glEnd();

//ǿ��OpenGL����������ʱ��������

glFlush();

}

 

void myReshape(GLsizei w,GLsizei h)

{

glViewport(0,0,w,h);

//�����ӿ�

 

glMatrixMode(GL_PROJECTION);

//ָ����ǰ����ΪGL_PROJECTION

glLoadIdentity();

//����ǰ�����û�Ϊ��λ��

 

if(w <= h)

gluOrtho2D(-1.0,1.5,-1.5,1.5*(GLfloat)h/(GLfloat)w);

//�����ά����ͶӰ����

else

gluOrtho2D(-1.0,1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5);

glMatrixMode(GL_MODELVIEW);

//ָ����ǰ����ΪGL_MODELVIEW

}

int main(int argc, char* argv[])

{

// ��ʼ��

glutInit(&argc,argv);

glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

glutInitWindowSize(400,400);

glutInitWindowPosition(200,200);

 

//��������

glutCreateWindow("Triangle");

 

//��������ʾ

background();

glutReshapeFunc(myReshape);

glutDisplayFunc(myDisplay);

 

glutMainLoop();

return(0);

}
