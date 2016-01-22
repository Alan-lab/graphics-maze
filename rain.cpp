#include<stdlib.h>
#include<GL\glut.h>
#include<time.h>
#include<math.h>
#define PI 3.1415
class particle
{
private:
 GLfloat x;//λ��x����
 GLfloat y;//y����
 GLfloat z;//z����
 GLfloat v[3];//�����ٶ�
 GLfloat rotate[3];//������ת����
 GLfloat angle;//��ת�ĽǶ�
 GLfloat color[3];//�������ʾ����ɫ
 GLuint display_list;//һ������ǵ���ʾ�б�����
public:
 GLuint createDL()//����һ���������ʾ�б�
 {
  GLuint DL;
  DL = glGenLists(1);
  glNewList(DL,GL_COMPILE); 
  drawFive();//��һ�������
  glEndList();
  return DL;
 }
 void init()//�����ʼ��λ���Լ��������Ϣ
 {
  display_list = createDL();
  angle = 0;
  y = rand() % 40;
  x = rand() % 181 - 90;
  z = rand() % 181 - 90;
  v[0] = (float)(rand() % 8) / (float)10 - 0.4;
  v[1] = (float)(rand() % 8) / (float)10 - 0.4;
  v[2] = (float)(rand() % 8) / (float)10 - 0.4;
  rotate[0] = (float)(rand() % 7) / (float)7 + 5;
  rotate[1] = (float)(rand() % 7) / (float)7 + 5;
  rotate[2] = (float)(rand() % 7) / (float)7 + 5;
  color[0] = (float)(rand() % 5) / (float)5 + 0.2;
  color[1] = (float)(rand() % 5) / (float)5 + 0.2;
  color[2] = (float)(rand() % 5) / (float)5 + 0.2;
 }
 void drawFive()//�������
 {
  GLfloat out_length = sqrt(1.0 / (2 - 2 * cos(72 * PI / 180))),
  bx = out_length * cos(18 * PI / 180),
  by = out_length * sin(18 * PI / 180),
  cx = out_length * sin(36 * PI / 180),
  cy = -out_length * cos(36 * PI / 180);
  GLfloat fx = cx * (by - out_length) / (cy - out_length), fy = by,
  in_length = sqrt(fx * fx + fy * fy),
  gx = in_length * cos(18 * PI / 180),
  gy = -in_length * sin(18 * PI / 180);
  GLfloat point_a[2] = {0, out_length},
  point_b[2] = {bx, by},
  point_c[2] = {cx, cy},
  point_d[2] = {-cx, cy},
  point_e[2] = {-bx, by},
  point_f[2] = {fx, fy},
  point_g[2] = {gx, gy},
  point_h[2] = {0, -in_length},
  point_i[2] = {-gx, gy},
  point_j[2] = {-fx, fy};
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(point_a[0], point_a[1]);
  glVertex2f(point_f[0], point_f[1]);
  glVertex2f(point_b[0], point_b[1]);
  glVertex2f(point_g[0], point_g[1]);
  glVertex2f(point_c[0], point_c[1]);
  glVertex2f(point_h[0], point_h[1]);
  glVertex2f(point_d[0], point_d[1]);
  glVertex2f(point_i[0], point_i[1]);
  glVertex2f(point_e[0], point_e[1]);
  glVertex2f(point_j[0], point_j[1]);
  glVertex2f(point_a[0], point_a[1]);
  glEnd();
 }
 void draw()//�ڣ�x, y, z����ʾ�����
 {
  GLfloat diffuse[] = {color[0], color[1], color[2]};
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotatef(angle, rotate[0], rotate[1], rotate[2]);
  glCallList(display_list);
  glPopMatrix();
 }
 void move(float slowdown)//�ı�����λ�ü��Ƕȵ���Ϣ
 {
  x += v[0] / slowdown;
  y += v[1] / slowdown;
  z += v[2] / slowdown;
  angle += 10 / slowdown;
  if(!(x >= -90 && x <= 90))
   die();
  else if(!(z >= -90 && z <= 90))
   die();
  else if(!(y >= 0 && y <= 50))
   die();
 }
 void die()//��������,��ʧ�����³�ʼ��
 {//���Լ���������
  init();
 }
};