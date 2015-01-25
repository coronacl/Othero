#include "stdafx.h"
const int windWidth  =512;
const int windHeight =512;
int columns;
int rows;

GameManage* gameManager=NULL;

void timer(int t)
{
        glutPostRedisplay();
        glutTimerFunc(t,timer,10); //タイマー関数
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

	// 画面をクリア（ピクセルデータとＺバッファの両方をクリア）
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	gameManager->drawBoard();

	// バックバッファに描画した画面をフロントバッファに表示
	glutSwapBuffers();
}

void resize( int w, int h ){
	// ウィンドウ内の描画を行う範囲を設定（ここではウィンドウ全体に描画）
	glViewport(0, 0, w, h);
	// カメラ座標系→スクリーン座標系への変換行列を設定
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
	case '\033':  /* '\033' は ESC の ASCII コード */
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

	// 背景色を設定
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	// ウィンドウ内の描画を行う範囲を設定（ここではウィンドウ全体に描画）
	glViewport(0, 0, windWidth, windHeight);

	// カメラ座標系→スクリーン座標系への変換行列を設定
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(0 ,windWidth , 0, windHeight,-100.0,100.0);//(left,right,bottom,top,near,far)

	glMatrixMode(GL_MODELVIEW); //行列モード切替
	glLoadIdentity();
	//引数(eyeX,eyeY,eyeZ , centerX,centreY,centerZ(注視点) , upX,upY,upZ)
	//gluLookAt(10,10,50, 0,0, 0.0, 0.0, 1.0, 0.0);




}
void mouse( int button, int state, int mx, int my ){

	//左ボタンのドラッグ判定
	if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ){
		gameManager->mouseClick(mx,my);
	}
	glutPostRedisplay();
}


void main( int argc, char **argv){

	/*============================*/ 
	/*		OpenGL呼び出し		  */
	/*============================*/
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA|GLUT_DEPTH );

	glutInitWindowSize( windWidth, windHeight );
	glutCreateWindow("Othello Test");

	glEnable(GL_DEPTH_TEST);//ZバッファON

	//コールバック関数
	glutDisplayFunc( display );
	glutReshapeFunc( resize );
	glutMouseFunc( mouse );
	//glutKeyboardFunc(keyboard);
	//glutSpecialFunc(move);
	glutTimerFunc(0,timer,17);
	initEnvironment();

	glutCreateMenu(menu);   //コールバック登録
	glutAddMenuEntry("first:YOU second:CPU", 1); //項目と与える引数の設定 
	glutAddMenuEntry("first:CPU second:YOU", 2);
	glutAddMenuEntry("Change Board 10*10", 3);
	glutAddMenuEntry("Change Board 12*12", 4);
	glutAddMenuEntry("give a handicap for Black", 5);
	glutAddMenuEntry("give a handicap for White", 6);
	glutAddMenuEntry("Result", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON); //マウスの右ボタンでポップアップ


	//ループ開始
	glutMainLoop();

}