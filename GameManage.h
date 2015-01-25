#pragma once
class GameManage{

private:GameManage(void){}
public:GameManage(int width,int height,int columns,int rows);
public:GameManage(int width,int height,int columns,int rows , int go_stone);
public:~GameManage(void);

//==========================
//ゲームを構成する各要素のインスタンス
//==========================
private: BoardManage* board;
private: vector<PlayerManage*> players;


//=============================
//盤のサイズとマス数
//=============================
private: int boardWidth,boardHeight;//ボードの基準サイズ
private: int cellColumns,cellRows;//セル数
private: double scaleW,scaleH;//縦横それぞれのスケール
		int game_counter;//今何手目か



//==================================
//ゲームのターン管理
//==================================
//ターンの変更 変更後，置く余地があるか調べ返却
private:bool turnChange();
//ターン処理 isCellID=trueのときx,yはセルIDを、falseのときクリックした盤上座標を示す
private:void turnEvent(int x,int y,bool isCellID);
//コンピュータのターン開始時に呼び出される
public:void startCPU();
private:void turnOfComputer();
//ゲーム終了時に呼び出される関数
private:void gameEnd();
private:int turnNumber;//現在のターンのプレイヤー番号
//=============================
//外部から呼び出されるイベント関数
//=============================
//ゲーム盤の描画
public:void drawBoard();
//ボードサイズの変更
public:void resizeBoard(double sW,double sH){scaleW=sW; scaleH=sH;}
//マウスクリックイベント
public:void mouseClick(int x,int y);
//結果の表示
public:void dispResult();
	   void makeHandicap(int val,eState state);

};

