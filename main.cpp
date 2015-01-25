#include "stdafx.h"
const int windWidth  =512;
const int windHeight =512;
int columns;
int rows;

GameManage* gameManager=NULL;

void timer(int t)
{
        glutPostRedisplay();
        glutTimerFunc(t,timer,10); //�^�C�}�[�֐�
}

void menu(int val){
	switch (val) {
	case 1:
		columns = 8;
		rows = 8;
		gameManager = new GameManage(windWidth,windHeight,columns,rows);
		break;
	case 2:
		columns = 8;
		rows = 8;
		gameManager = new GameManage(windWidth,windHeight,columns,rows,1);
		gameManager->startCPU();
		break;
	case 3 :
		columns = 10;
		rows = 10;
		gameManager = new GameManage(windWidth,windHeight,columns,rows);
		break;
	case 4 :
		columns = 12;
		rows = 12;
		gameManager = new GameManage(windWidth,windHeight,columns,rows);
		break;
	case 5:
		gameManager->makeHandicap(2,eState::BLK);
		break;
	case 6:
		gameManager->makeHandicap(2,eState::WHT);
		break;
	case 7:
		gameManager->dispResult();
	
		break;
	default:
		break;
	}
}

void display( void ){

	// ��ʂ��N���A�i�s�N�Z���f�[�^�Ƃy�o�b�t�@�̗������N���A�j
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	gameManager->drawBoard();

	// �o�b�N�o�b�t�@�ɕ`�悵����ʂ��t�����g�o�b�t�@�ɕ\��
	glutSwapBuffers();
}

void resize( int w, int h ){
	// �E�B���h�E���̕`����s���͈͂�ݒ�i�����ł̓E�B���h�E�S�̂ɕ`��j
	glViewport(0, 0, w, h);
	// �J�������W�n���X�N���[�����W�n�ւ̕ϊ��s���ݒ�
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	if (w > h){
		glOrtho(0, windWidth * w/h, windHeight, 0, -100.0, 100.0);//left,right,bottom.top,znear,zfar
		gameManager->resizeBoard((double)w / windWidth* h / w, (double)h / windHeight);
	}
	else{
		glOrtho(0, windWidth, windHeight * h/w, 0, -100.0, 100.0);
		gameManager->resizeBoard((double)w / windWidth, (double)h / windHeight * w / h);
	}
	
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y){

	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  /* '\033' �� ESC �� ASCII �R�[�h */
		exit(0);
	default:
		break;
	}

	glutPostRedisplay();
}


void move(int key, int  x, int y){

	switch (key){
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;
	}
	glutPostRedisplay();
}


void initEnvironment( void ){

	glEnable( GL_DEPTH_TEST );

	// �w�i�F��ݒ�
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	// �E�B���h�E���̕`����s���͈͂�ݒ�i�����ł̓E�B���h�E�S�̂ɕ`��j
	glViewport(0, 0, windWidth, windHeight);

	// �J�������W�n���X�N���[�����W�n�ւ̕ϊ��s���ݒ�
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(0 ,windWidth , 0, windHeight,-100.0,100.0);//(left,right,bottom,top,near,far)

	glMatrixMode(GL_MODELVIEW); //�s�񃂁[�h�ؑ�
	glLoadIdentity();
	//����(eyeX,eyeY,eyeZ , centerX,centreY,centerZ(�����_) , upX,upY,upZ)
	//gluLookAt(10,10,50, 0,0, 0.0, 0.0, 1.0, 0.0);




}
void mouse( int button, int state, int mx, int my ){

	//���{�^���̃h���b�O����
	if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ){
		gameManager->mouseClick(mx,my);
	}
	glutPostRedisplay();
}


void main( int argc, char **argv){

	/*============================*/ 
	/*		OpenGL�Ăяo��		  */
	/*============================*/
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA|GLUT_DEPTH );

	glutInitWindowSize( windWidth, windHeight );
	glutCreateWindow("Othello Test");

	glEnable(GL_DEPTH_TEST);//Z�o�b�t�@ON

	//�R�[���o�b�N�֐�
	glutDisplayFunc( display );
	glutReshapeFunc( resize );
	glutMouseFunc( mouse );
	//glutKeyboardFunc(keyboard);
	//glutSpecialFunc(move);
	glutTimerFunc(0,timer,17);
	initEnvironment();

	glutCreateMenu(menu);   //�R�[���o�b�N�o�^
	glutAddMenuEntry("first:YOU second:CPU", 1); //���ڂƗ^��������̐ݒ� 
	glutAddMenuEntry("first:CPU second:YOU", 2);
	glutAddMenuEntry("Change Board 10*10", 3);
	glutAddMenuEntry("Change Board 12*12", 4);
	glutAddMenuEntry("give a handicap for Black", 5);
	glutAddMenuEntry("give a handicap for White", 6);
	glutAddMenuEntry("Result", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON); //�}�E�X�̉E�{�^���Ń|�b�v�A�b�v


	//���[�v�J�n
	glutMainLoop();

}