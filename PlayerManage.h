#pragma once
class PlayerManage{
protected:PlayerManage(){}
public:PlayerManage(BoardManage* _board,eState _state,bool _computer);
public:~PlayerManage(void){}

//==============================
//�v���C���[�Ǘ��p�ϐ�
//==============================
//�{�[�h�̃A�h���X
protected:BoardManage* board;
protected:bool comPlayer;//�v���C���[��PC���ǂ����̃t���O
//�v���C���[���R���s���[�^���ǂ���
public:bool isComputer(){return comPlayer;} 
//�v���[���[�̏��
protected:eState state;
public:eState thisState(){return state;}
//===================================
//�v���[���[���Ս��W���w�肵�ċ��u��
//===================================
public:bool putPiece(int x,int y);
};

