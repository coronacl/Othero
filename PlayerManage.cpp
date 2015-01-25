#include "stdafx.h"


PlayerManage::PlayerManage(BoardManage* _board,eState _state,bool _computer){
	board = _board;
	state = _state;
	comPlayer = _computer;
}


bool PlayerManage::putPiece(int x,int y){
	if(board!=NULL){return false;}
	return board->canPutPiece(x,y,state,true);
}


