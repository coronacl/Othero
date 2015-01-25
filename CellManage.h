#pragma once

//ひとつのセルを管理するクラス
//描画，現在の状態の返却等
class CellManage{

private: CellManage(void){}

//セルの初期化
public:  CellManage(int _ox,int _oy,int _width,int _height);

public:	~CellManage(void){}

//===============================
//セルの基本情報
//===============================
private:
	int width,height;//セルのサイズ
	int ox,oy;//セルの描画位置（左上座標）
	eState state;//セルの状態
	double radius;//セル内に描画する円の半径（駒サイズ）
	double rotation;
	bool flag_rotate;
	bool flag_last_choice;


//===============================
//描画関連
//===============================
//セル描画のメイン関数
public:	void drawCell();
//セル内に円を描画
private:void drawCircle();

//===============================
//セルの状態
//===============================
//セル状態の変更（駒を置く）
public:	void putPiece(eState val);
//セルの状態を返却
public: eState getState();
//セルの回転制御
		void startRotation(){
			flag_rotate = true;
		}
		void stopRotation(){
			flag_rotate = false;
		}
//===============================
//CPUの最後の手
//===============================
		void setLastChoice(bool _flag){
				flag_last_choice = _flag;
		}

//===============================
//セルの当たり判定 (速度重視のためインライン)
//===============================
public: bool isInArea(int x,int y){
			if(x<ox || y<oy){return false;}
			if(x>=ox+width || y>=oy+height){return false;}
			return true;
		}
		
};


