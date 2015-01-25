#pragma once
class PlayerManage{
protected:PlayerManage(){}
public:PlayerManage(BoardManage* _board,eState _state,bool _computer);
public:~PlayerManage(void){}

//==============================
//プレイヤー管理用変数
//==============================
//ボードのアドレス
protected:BoardManage* board;
protected:bool comPlayer;//プレイヤーがPCかどうかのフラグ
//プレイヤーがコンピュータかどうか
public:bool isComputer(){return comPlayer;} 
//プレーヤーの状態
protected:eState state;
public:eState thisState(){return state;}
//===================================
//プレーヤーが盤座標を指定して駒を置く
//===================================
public:bool putPiece(int x,int y);
};

