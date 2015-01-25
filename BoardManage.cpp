#include "stdafx.h"

BoardManage::BoardManage(int _columns,int _rows,int _width,int _height){
	columns = _columns; rows = _rows;
	width = _width; height = _height;

	//board������
	board.resize(rows);
	for(int j=0;j<rows;j++){
		for(int i=0;i<columns;i++){
			int ox = i*width;
			int oy = j*height;
			board[j].push_back(CellManage(ox,oy,width,height));
		}
	}
	initBoard();

	last_choice.x = -1;
	last_choice.y = -1;




}

//�Ֆʂ̏�����
void BoardManage::initBoard(){

	for(int j=0;j<rows;j++){
		for(int i=0;i<columns;i++){
			board[j][i].putPiece(EMP);
		}
	}
	
	if(columns<2 || rows<2){return;}
	
	board[rows/2-1][columns/2-1].putPiece(WHT);
	board[rows/2  ][columns/2  ].putPiece(WHT);
	board[rows/2-1][columns/2  ].putPiece(BLK);
	board[rows/2  ][columns/2-1].putPiece(BLK);
}

//�Տ�ɒu���]�n�����邩����
bool BoardManage::hasOtherPutCell(eState state){

	bool find = false;
	for(int j=0;j<rows && !find;j++){
		for(int i=0;i<columns && !find;i++){
			if(canPutPiece(Pixel2d(i,j),state,false)){
				find = true;
			}
		}
	}
	return find;
}

//�Տ�̍��W�n����Z��ID��ԋp
Pixel2d BoardManage::isOnThisCell(int x,int y){
	for(int j=0;j<rows;j++){
		for(int i=0;i<columns;i++){
			if(board[j][i].isInArea(x,y)){
				return Pixel2d(i,j);
			}
		}
	}

	return Pixel2d(-1,-1);
}

//�Տ���W���w�肵�ċ��u������
bool BoardManage::canPutPiece(int x,int y,eState state,bool put){
	Pixel2d id = isOnThisCell(x,y);
	return canPutPiece(id,state,put);
}

//�w�肵�����W�̃Z����state�̋��u���邩�ǂ���
//put==true �̂Ƃ����ۂɋ��u��
bool BoardManage::canPutPiece(Pixel2d& id,eState state,bool put){

	//�̈�O�̎�false
	if(id.x<0 || id.x>=columns || id.y<0 || id.y>=rows){
		return false;
	}
	//�󔒃Z������Ȃ��Ƃ�false
	if(board[id.y][id.x].getState()!=EMP){
		return false;
	}

	bool canPut=false;
	for(int j=-1; j<=1; j++){
		for(int i=-1; i<=1; i++){
			if(i==0 && j==0){continue;}
			Pixel2d direction(i,j);
			Pixel2d findPiece;
			int reverseNum = checkPiece(id,findPiece,direction,state);
			if(reverseNum<=0){continue;}
			if(!put){return true;}
					 
			changeLinePieces(id,reverseNum,direction,state);
			//cpu�̒��肵�����o�^
			if (cpu_state == state){
				board[id.y][id.x].setLastChoice(true);
			}
			//else{
			//	board[id.y][id.x].setLastChoice(false);

			//}
			canPut=true;
		}
	}

	return canPut;
}

int BoardManage::checkPiece(Pixel2d& oID,Pixel2d& tgtID,Pixel2d& direction,eState orgState){
	int maxLength = MAX(columns,rows); 
	
	bool find = false;
	int reverseNum=0;
	for(int n=1; n<maxLength; n++){
		int i = oID.x + direction.x * n;
		int j = oID.y + direction.y * n;
		if(i<0 || i>=columns || j<0 || j>=rows){break;}
		//�󔒃Z����������
		if(board[j][i].getState()==EMP){break;}
		//�אڂ��鑼�F�̋������
		else if(board[j][i].getState()!=orgState){find = true; reverseNum++;}
		//�אڑ��F�̌�Ɏ��F�̋�������ꍇ�C��̈ʒu��ԋp
		else if(find){tgtID.set(i,j); return reverseNum;}
		//�����Ȃ莩�F���אڂ��Ă����ꍇ
		else{break;}
	}
	return 0;
}

void BoardManage::dispStateNumber(){
	num_BLK = 0;
	num_WHT = 0;
	for (int j = 0; j<rows; j++){
		for (int i = 0; i<columns; i++){
			if (board[j][i].getState() == eState::BLK){
				num_BLK++;
			}
			else if (board[j][i].getState() == eState::WHT){
				num_WHT++;
			}
		}
	}
	printf("Black number = %d  ", num_BLK);
	printf("White number = %d\n", num_WHT);
}

//�w�胉�C����̓_�̏�ԕύX
void BoardManage::changeLinePieces(Pixel2d& sID,int reverseNum,Pixel2d& direction,eState state){

	for(int n=0;n<=reverseNum;n++){
		int i = sID.x + direction.x*n;
		int j = sID.y + direction.y*n;
		if(i<0 || i>=columns || j<0 || j>=rows){continue;}

		board[j][i].putPiece(state);
		if (state == cpu_state){
				board[j][i].startRotation();
		}

		
	}

}

//�Ղ�`��
void BoardManage::drawBoard(){
	for (int j = 0; j < rows; j++){
		for (int i = 0; i < columns; i++)
		{
		


			glColor3d(1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			switch (board[j][i].getState()){
			case EMP:
				glDisable(GL_TEXTURE_2D);

				//glPushMatrix();
				//glTranslated(100.0,100.0,10.0);
				glColor3d(0.0, 0.5, 1.0);
				//glutWireSphere(20,50,50);
				//glColor3d(0.0 , 0.0 , 0.0);
				//glPopMatrix();

				//glBindTexture(GL_TEXTURE_2D, texture[2]);//(�e�N�X�`���̎���,�e�N�X�`���̖��O)
				break;
			case WHT:
				glBindTexture(GL_TEXTURE_2D, texture[0]);//(�e�N�X�`���̎���,�e�N�X�`���̖��O)
				break;
			case BLK:
				glBindTexture(GL_TEXTURE_2D, texture[1]);//(�e�N�X�`���̎���,�e�N�X�`���̖��O)
				break;
			default:
				break;
			}

			board[j][i].drawCell();
			glDisable(GL_TEXTURE_2D);

	
		}
	}
}

void BoardManage::getBoardData(vector<vector<eState>> &tmpBoard)
{
	tmpBoard.resize(rows);
	for (int j = 0; j<rows; j++){
		for (int i = 0; i<columns; i++){
			tmpBoard[j].push_back(eState::EMP);
		}
	}

	for (int j = 0; j<rows; j++){
		for (int i = 0; i<columns; i++){
			tmpBoard[j][i] = board[j][i].getState();
		}
	}
}

void BoardManage::setHandicap(int num_stone , eState state)
{
		printf("final choice %d , %d\n",last_choice.x,last_choice.y);
	switch (num_stone)
	{
	case 1:
		board[rows - 1][columns - 1].putPiece(state);
		break;
	case 2:
		board[0][0].putPiece(state);
		board[rows - 1][columns - 1].putPiece(state);
		break;

	case 3:
	default:
		break;
	}

}

//---------- �摜��ǂݍ���ŃR���o�[�g ----------------//
bool BoardManage::LoadGLTextures()
{

	image[0] = cvLoadImage("dog.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	if (image[0] == NULL)
	{
		printf("�t�@�C���ǂݍ��݂Ɏ��s���܂���\n");
		return false;
	}
	image[1] = cvLoadImage("cat.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	if (image[1] == NULL)
	{
		printf("�t�@�C���ǂݍ��݂Ɏ��s���܂���\n");
		return false;
	}
	image[2] = cvLoadImage("madoka.jpg", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	if (image[2] == NULL)
	{
		printf("�t�@�C���ǂݍ��݂Ɏ��s���܂���\n");
		return false;
	}

	//BGR����RGB�֕ύX
	cvCvtColor(image[0], image[0], CV_BGR2RGB);
	cvCvtColor(image[1], image[1], CV_BGR2RGB);
	cvCvtColor(image[2], image[2], CV_BGR2RGB);

	//�񎟌��z��̔��]
	//when 0 : x������Ŕ��]�i�㉺���])
	//when + : ��������Ŕ��]�i���E���]�j
	//when - ; ��������Ŕ��]�i�㉺���E���]�j
	cvFlip(image[0], NULL, 0);
	cvFlip(image[1], NULL, 0);
	cvFlip(image[2], NULL, 0);

	/******* �e�N�X�`���쐬 ****************/
	//�e�N�X�`���I�u�W�F�N�g�̍쐬
	glGenTextures(3, &texture[0]);//(�쐬����e�N�X�`���̐�,���̖��O)

	for (int i = 0; i < 3; i++){
		//�e�N�X�`���̗L����
		glBindTexture(GL_TEXTURE_2D, texture[i]);//(�e�N�X�`���̎���,�e�N�X�`���̖��O)
		//�g��k���̐ݒ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//�e�N�X�`���̍쐬�p�^�[��
		//(~,�F�̐�,�摜�̕�,�摜�̍���,�J���[���,�J���[�z��̌^,�J���[�z��)
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
						  image[i]->width, image[i]->height,
						  GL_RGB, GL_UNSIGNED_BYTE, image[i]->imageData);

	}
	//cvReleaseImage(&image1);


	return true;
};