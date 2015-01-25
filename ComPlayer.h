#pragma once

//コンピュータプレーヤーを管理するクラス PlayerManageを継承し，基本的には次の手を検討するAIを司る
class ComPlayer : public PlayerManage{

private:ComPlayer(void);
public:ComPlayer(BoardManage* _board,eState _state);
public:~ComPlayer(void);

//=========================================
//AIのために必要な盤情報
//=========================================
private: 
	eState cpu_state;
		int columns,rows;
		 vector<vector<eState>> board_data;		//現在の盤面
		 vector<Pixel2d> next_choice;			//可能な次の一手
		 vector<Pixel2d> sequenceOfMove;		//指し手
		 vector<vector<eState>> bf_board_data;
		 vector<vector<eState>> af_board_data;
		 vector<int> next_evaluation;			//次の一手に対応する評価値
		 vector<vector<int>> csvMin;	//盤面の評価用数値データ
		 vector<vector<int>> csvMax;
		 int game_counter;
		 Tree* tree;

//=========================================
//次の手を考える思考ルーチン
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
//表示用関数&盤面情報取得
//=============================
		void disp();
//=============================
//ファイル読み込み
//=============================
public:
	void readCsv();
	void dispCsv();




};