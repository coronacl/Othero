#pragma once

//�Ղ̊Ǘ��N���X �u���邩�ǂ����̔���C�e�Z���ւ̏�ԕύX�w����
class BoardManage{
private: BoardManage(void){};
public: BoardManage(int _columns,int _rows,int _width,int _height);//���}�X���C�c�}�X���C�}�X�̉����C�}�X�̏c��
public: ~BoardManage(void){};

//==============================
//�ՖʃC���X�^���X�@�e�Z����ID=(row,column)
//==============================
private:vector<vector<CellManage>> board;
private: int columns,rows;
private: int width,height;
private: int num_BLK, num_WHT;
		 GLuint texture[3];		//�e�N�X�`��ID
		 eState cpu_state;
		Pixel2d last_choice;


//=============================
//�`��摜
//=============================
private: IplImage* image[3];			//�摜���


//=============================
//�A�N�Z�b�Z
//=============================
public: int getColumns(){ return columns; };
public: int getRows(){ return rows; };
		void setCpuState(eState _cpu_state){
			cpu_state = _cpu_state;
		}


		 
//==============================
//�Ֆʂ̏�����
//==============================
public:void initBoard();

//==============================
//�Տ�ɒu���]�n�����邩����
//==============================
public:bool hasOtherPutCell(eState state);

//==============================
//�Տ�̍��W�n����Z��ID�ɕύX
//==============================
private: Pixel2d isOnThisCell(int x,int y);

//==============================
//�e�픻�菈��
//==============================
//�w�肵�����W�̃Z����state�̋��u���邩�ǂ��� �Z��ID�͓����Ŏ擾
//put==true �̂Ƃ����ۂɋ��u��
public:  bool canPutPiece(Pixel2d& id,eState state,bool put);
//�Տ���W�����ɋ��u������
public:  bool canPutPiece(int x,int y,eState state,bool put);

//�P������ɔ��]�\���`�F�b�N�@���]�\�ȋ�̐���ԋp
public: int checkPiece(Pixel2d& oID,Pixel2d& tgtID,Pixel2d& direction,eState orgState);
//==============================
//�e�Z���̏�Ԃ̌����擾
//==============================
public: void dispStateNumber();

//=============================
//�w�肵��ID����CreverseNum���̃Z��������ύX
//=============================
private: void changeLinePieces(Pixel2d& sID,int reverseNum,Pixel2d& direction,eState state);

//=============================
//�{�[�h�̂̕`��
//=============================
public: void drawBoard();

//=============================
//�Ֆʏ��̎擾
//=============================
public: void getBoardData(vector<vector<eState>> &tmpBoard);

//=============================
//�n���f��^����
//=============================
public: void setHandicap(int num_stone, eState state);

//=============================
//�摜�f�[�^�̓ǂݍ���
//=============================
		bool LoadGLTextures();

};