#pragma once

//盤の管理クラス 置けるかどうかの判定，各セルへの状態変更指示等
class BoardManage{
private: BoardManage(void){};
public: BoardManage(int _columns,int _rows,int _width,int _height);//横マス数，縦マス数，マスの横幅，マスの縦幅
public: ~BoardManage(void){};

//==============================
//盤面インスタンス　各セルのID=(row,column)
//==============================
private:vector<vector<CellManage>> board;
private: int columns,rows;
private: int width,height;
private: int num_BLK, num_WHT;
		 GLuint texture[3];		//テクスチャID
		 eState cpu_state;
		Pixel2d last_choice;


//=============================
//描画画像
//=============================
private: IplImage* image[3];			//画像情報


//=============================
//アクセッセ
//=============================
public: int getColumns(){ return columns; };
public: int getRows(){ return rows; };
		void setCpuState(eState _cpu_state){
			cpu_state = _cpu_state;
		}


		 
//==============================
//盤面の初期化
//==============================
public:void initBoard();

//==============================
//盤上に置く余地があるか判定
//==============================
public:bool hasOtherPutCell(eState state);

//==============================
//盤上の座標系からセルIDに変更
//==============================
private: Pixel2d isOnThisCell(int x,int y);

//==============================
//各種判定処理
//==============================
//指定した座標のセルにstateの駒を置けるかどうか セルIDは内部で取得
//put==true のとき実際に駒を置く
public:  bool canPutPiece(Pixel2d& id,eState state,bool put);
//盤上座標を元に駒を置く処理
public:  bool canPutPiece(int x,int y,eState state,bool put);

//単一方向に反転可能かチェック　反転可能な駒の数を返却
public: int checkPiece(Pixel2d& oID,Pixel2d& tgtID,Pixel2d& direction,eState orgState);
//==============================
//各セルの状態の個数を取得
//==============================
public: void dispStateNumber();

//=============================
//指定したIDから，reverseNum分のセル属性を変更
//=============================
private: void changeLinePieces(Pixel2d& sID,int reverseNum,Pixel2d& direction,eState state);

//=============================
//ボードのの描画
//=============================
public: void drawBoard();

//=============================
//盤面情報の取得
//=============================
public: void getBoardData(vector<vector<eState>> &tmpBoard);

//=============================
//ハンデを与える
//=============================
public: void setHandicap(int num_stone, eState state);

//=============================
//画像データの読み込み
//=============================
		bool LoadGLTextures();

};