#pragma once
class GameManage{

private:GameManage(void){}
public:GameManage(int width,int height,int columns,int rows);
public:GameManage(int width,int height,int columns,int rows , int go_stone);
public:~GameManage(void);

//==========================
//�Q�[�����\������e�v�f�̃C���X�^���X
//==========================
private: BoardManage* board;
private: vector<PlayerManage*> players;


//=============================
//�Ղ̃T�C�Y�ƃ}�X��
//=============================
private: int boardWidth,boardHeight;//�{�[�h�̊�T�C�Y
private: int cellColumns,cellRows;//�Z����
private: double scaleW,scaleH;//�c�����ꂼ��̃X�P�[��
		int game_counter;//������ڂ�



//==================================
//�Q�[���̃^�[���Ǘ�
//==================================
//�^�[���̕ύX �ύX��C�u���]�n�����邩���וԋp
private:bool turnChange();
//�^�[������ isCellID=true�̂Ƃ�x,y�̓Z��ID���Afalse�̂Ƃ��N���b�N�����Տ���W������
private:void turnEvent(int x,int y,bool isCellID);
//�R���s���[�^�̃^�[���J�n���ɌĂяo�����
public:void startCPU();
private:void turnOfComputer();
//�Q�[���I�����ɌĂяo�����֐�
private:void gameEnd();
private:int turnNumber;//���݂̃^�[���̃v���C���[�ԍ�
//=============================
//�O������Ăяo�����C�x���g�֐�
//=============================
//�Q�[���Ղ̕`��
public:void drawBoard();
//�{�[�h�T�C�Y�̕ύX
public:void resizeBoard(double sW,double sH){scaleW=sW; scaleH=sH;}
//�}�E�X�N���b�N�C�x���g
public:void mouseClick(int x,int y);
//���ʂ̕\��
public:void dispResult();
	   void makeHandicap(int val,eState state);

};

