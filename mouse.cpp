#include "mouse.h"
#include "drawElement.h"
#include <GL/glut.h>
extern bool view_first;
extern GLfloat view_width;
extern GLfloat view_height;
extern GLdouble eye_pos[3];
extern GLdouble center[3];
extern int coinAll[201];
extern int score;
void processHits(GLint hits, GLuint buffer[])
{
	printf("һ����%d�������¼\n",hits);
	unsigned int i;
	GLuint minZ, names, *ptr, *ptrNames=nullptr;
	ptr = (GLuint *)buffer;
	minZ = 0xffffffff;
	for (i = 0; i<hits; i++)    //����ÿһ�������¼
	{
		names = *ptr;      //������ֶ�ջ�е���������
		ptr ++;
		printf("min z:%g\n",(float)*ptr/0x7FFFFFFF);
		printf("name :%d\n",*(ptr+2));
		if (*ptr < minZ) {
			minZ = *ptr;
			ptrNames = ptr+2;
			
		}
		ptr += names+2;
	}
	coinAll[*ptrNames] = 0;
	score+=50;
	printf("\n");	
}

void mouse(int button, int state, int x, int y)
{
	GLuint selectBuf[BUFSIZE];				//�洢�����¼
	GLint hits;                             //�����¼�ĸ���
	GLint viewport[4];						//�ӿ�

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;
	
	glSelectBuffer(BUFSIZE, selectBuf);		//ָ���洢�����¼������
	glRenderMode(GL_SELECT);				//����ѡ��ģʽ
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glGetIntegerv(GL_VIEWPORT, viewport);  //����ӿ�
	GLfloat aspect = (GLfloat)viewport[2]/(GLfloat)viewport[3];
	//������ѡ������ѡ���������������(x,viewport[3]-y)����С��(1,1)
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 1, 1, viewport);
	//����ͶӰ����
	//if (view_first)
	//	gluLookAt(eye_pos[0], eye_pos[1], eye_pos[2], center[0], center[1], center[2], 0, 1, 0);//��һ�˳��ӽ�
	//else
	//	gluLookAt(0, 20.1, 0, 0, 0, 0, 0, 0, -1);  //�����ӽ�
	if (view_first){
		gluPerspective(60.f, (GLfloat)view_width / (GLfloat)view_height, 2.0f, 210.0f);
	    //glFrustum(-3, 3, -3, 3, 3,100);
		} else {
			glOrtho(0,210,0,210,0,60);
	}

	glMatrixMode(GL_MODELVIEW);
	glInitNames();           //��ʼ�����ֶ�ջ��ѹ���ʼԪ��
	glPushName(0);
	//��ѡ��ģʽ�»��Ƴ���
	drawCoins(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);		//
	glFlush();        //���ƽ���

	//��������¼
	hits = glRenderMode(GL_RENDER); //��ȡ��¼�µĵ���ĸ���
	if(hits>0)
		processHits(hits, selectBuf);           //��������¼selectBuf
	glutPostRedisplay();
}