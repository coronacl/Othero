#include "stdafx.h"

//セルの初期化
CellManage::CellManage(int _ox,int _oy,int _width,int _height){
	ox=_ox; oy=_oy; width=_width; height=_height;
	state = eState::EMP;
	rotation = 0.0;

	flag_rotate = false;
	flag_last_choice = false;

	radius = width*0.4;
}

//===============================
//描画関連
//===============================
//セル描画のメイン関数
void CellManage::drawCell(){

	glPushMatrix();
		if (flag_rotate == true){
			glTranslated(ox + width / 2, oy + height / 2, 0);
			glRotated(rotation, 0, 1, 0);
			glTranslated(-ox - width / 2, -oy - height / 2, 0);
		}

		if (flag_last_choice == true){
			glColor3d(1.0, 1.0, 0.0);
		}

		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex3d(ox + 1, oy + 1, 0);

		glTexCoord2d(1.0, 1.0);
		glVertex3d(ox + width - 1, oy + 1, 0);

		glTexCoord2d(1.0, 0.0);
		glVertex3d(ox + width - 1, oy + height - 1, 0);

		glTexCoord2d(0.0, 0.0);
		glVertex3d(ox + 1, oy + height - 1, 0);
		glEnd();
	glPopMatrix();

	if (++rotation > 180){
		rotation = 0.0;
		stopRotation();
		flag_last_choice = false;
	}


	//switch (state){
	//case EMP:
	//	break;
	//case WHT:
	//	glColor3d(1.0,0.0,0.0);
	//	drawCircle();
	//	break;
	//case BLK:
	//	glColor3d(0.0,0.0,1.0);
	//	drawCircle();
	//	break;
	//default:
	//	break;
	//}



}
//セル内に円を描画
void CellManage::drawCircle(){
	

	const int radStep=30;
	glPushMatrix();
	glTranslated(0,0,10);
	glBegin(GL_POLYGON);
	for(int n=0;n<radStep;n++){
		double x = radius * cos(n*2.0*M_PI/radStep) + ox + width/2.0;
		double y = radius * sin(n*2.0*M_PI/radStep) + oy + height/2.0;
		glVertex2d(x,y);
	}
	//glutWireSphere(30.0, 16, 16);
	glEnd();
	glPopMatrix();
}

//===============================
//セルの状態
//===============================
//セル状態の変更（駒を置く）
void CellManage::putPiece(eState val){
	state = val;

}

//セルの状態を返却
eState CellManage::getState(){
	return state;
}
