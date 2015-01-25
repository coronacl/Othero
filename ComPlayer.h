#pragma once

//�R���s���[�^�v���[���[���Ǘ�����N���X PlayerManage���p�����C��{�I�ɂ͎��̎����������AI���i��
class ComPlayer : public PlayerManage{

private:ComPlayer(void);
public:ComPlayer(BoardManage* _board,eState _state);
public:~ComPlayer(void);

//=========================================
//AI�̂��߂ɕK�v�ȔՏ��
//=========================================
private: 
	eState cpu_state;
		int columns,rows;
		 vector<vector<eState>> board_data;		//���݂̔Ֆ�
		 vector<Pixel2d> next_choice;			//�\�Ȏ��̈��
		 vector<Pixel2d> sequenceOfMove;		//�w����
		 vector<vector<eState>> bf_board_data;
		 vector<vector<eState>> af_board_data;
		 vector<int> next_evaluation;			//���̈��ɑΉ�����]���l
		 vector<vector<int>> csvMin;	//�Ֆʂ̕]���p���l�f�[�^
		 vector<vector<int>> csvMax;
		 int game_counter;
		 Tree* tree;

//=========================================
//���̎���l����v�l���[�`��
//=========================================
private:int checkPiece(Pixel2d& oID, Pixel2d& tgtID, Pixel2d& direction);
		int checkPiece(Pixel2d& oID, Pixel2d& tgtID, Pixel2d& direction, vector<vector<eState>>& dst_board,eState _state);
		void changeLinePieces(Pixel2d& sID, int reverseNum, Pixel2d& direction);
		void changeLinePieces(Pixel2d& sID, int reverseNum, Pixel2d& direction, vector<vector<eState>>& dst_board,eState _state);
		void calEvaluationVal(vector<vector<eState>>& src_board, int& evaluation);
		bool canPutPiece(Pixel2d& id);
		bool canPutPiece(Pixel2d& id, vector<vector<eState>>& src_board,eState _state);
		bool canPutBoard(vector<vector<eState>> focus_board, vector<Pixel2d>* next_tmp, eState _state);
		void changeBoard(vector<Pixel2d> sequence, vector<vector<eState>>& dst_board);
		void changeBoard(vector<vector<eState>> src_board, Pixel2d choice, vector<vector<eState>>& dst_board);

public: Pixel2d getNextMove();
		void setGame_counter(int _game_counter){game_counter = _game_counter;};
		void setCom_state(eState _state){ cpu_state = _state; }

//=============================
//�\���p�֐�&�Ֆʏ��擾
//=============================
		void disp();
//=============================
//�t�@�C���ǂݍ���
//=============================
public:
	void readCsv();
	void dispCsv();




};