#pragma once

//�ЂƂ̃Z�����Ǘ�����N���X
//�`��C���݂̏�Ԃ̕ԋp��
class CellManage{

private: CellManage(void){}

//�Z���̏�����
public:  CellManage(int _ox,int _oy,int _width,int _height);

public:	~CellManage(void){}

//===============================
//�Z���̊�{���
//===============================
private:
	int width,height;//�Z���̃T�C�Y
	int ox,oy;//�Z���̕`��ʒu�i������W�j
	eState state;//�Z���̏��
	double radius;//�Z�����ɕ`�悷��~�̔��a�i��T�C�Y�j
	double rotation;
	bool flag_rotate;
	bool flag_last_choice;


//===============================
//�`��֘A
//===============================
//�Z���`��̃��C���֐�
public:	void drawCell();
//�Z�����ɉ~��`��
private:void drawCircle();

//===============================
//�Z���̏��
//===============================
//�Z����Ԃ̕ύX�i���u���j
public:	void putPiece(eState val);
//�Z���̏�Ԃ�ԋp
public: eState getState();
//�Z���̉�]����
		void startRotation(){
			flag_rotate = true;
		}
		void stopRotation(){
			flag_rotate = false;
		}
//===============================
//CPU�̍Ō�̎�
//===============================
		void setLastChoice(bool _flag){
				flag_last_choice = _flag;
		}

//===============================
//�Z���̓����蔻�� (���x�d���̂��߃C�����C��)
//===============================
public: bool isInArea(int x,int y){
			if(x<ox || y<oy){return false;}
			if(x>=ox+width || y>=oy+height){return false;}
			return true;
		}
		
};


