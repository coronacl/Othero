#include "stdafx.h"


GameManage::GameManage(int width, int height, int columns, int rows){
	boardWidth = width; 
	boardHeight = height;
	cellColumns = columns; 
	cellRows = rows;
	int cellWidth = (int)(boardWidth / cellColumns + 0.5);
	int cellHeight = (int)(boardHeight / cellRows + 0.5);

	board = new BoardManage(cellColumns, cellRows, cellWidth, cellHeight);

	if (board->LoadGLTextures() == false){
		printf("ファイル読み込みに失敗しました\n");
	}

	scaleH = scaleW = 1.0;
	turnNumber = 0;
	game_counter = 0;

	//2つのプレーヤーを追加
	players.push_back(new PlayerManage(board, eState::BLK, false));
	players.push_back(new ComPlayer(board, eState::WHT));

	board->setCpuState(eState::WHT);

}

GameManage::GameManage(int width,int height,int columns,int rows , int go_stone)
{
	boardWidth = width; 
	boardHeight = height;
	cellColumns = columns; 
	cellRows = rows;
	int cellWidth = (int)(boardWidth / cellColumns + 0.5);
	int cellHeight = (int)(boardHeight / cellRows + 0.5);

	board = new BoardManage(cellColumns, cellRows, cellWidth, cellHeight);
	if (board->LoadGLTextures() == false){
		printf("ファイル読み込みに失敗しました\n");
	}

	scaleH = scaleW = 1.0;
	turnNumber = 0;
	game_counter = 0;

	//2つのプレーヤーを追加
	players.push_back(new ComPlayer(board, eState::BLK));
	players.push_back(new PlayerManage(board, eState::WHT, false));

	board->setCpuState(eState::BLK);

	
}

GameManage::~GameManage(void){
	for(int n=0;n<(int)players.size();n++){
		delete players[n];
	}
	delete board;
}

bool GameManage::turnChange(){
	turnNumber++;
	turnNumber%=players.size();
	return board->hasOtherPutCell(players[turnNumber]->thisState());
}

void GameManage::startCPU(){
	turnOfComputer();

}

//ターン処理 isCellID=trueのときx,yはセルIDを,falseのときクリックした盤上座標を示す
void GameManage::turnEvent(int x,int y,bool isCellID){
	//置けなかったとき終了
	if(isCellID && !board->canPutPiece(Pixel2d(x,y),players[turnNumber]->thisState(),true)){return;}
	else if(!isCellID && !board->canPutPiece(x,y,players[turnNumber]->thisState(),true)){return;}
	
	//ターンを変え，置けるか調べる．全員分調べて誰もおけなかったらゲーム終了
	bool canContinue = false;
	for(int n=0;n<(int)players.size();n++){
		if(turnChange()){
			canContinue=true;
			break;}
	}
	if(!canContinue){
		gameEnd();
	}
	//次のターンがコンピュータだった場合の処理
	turnOfComputer();
}



void GameManage::turnOfComputer(){
	if(!players[turnNumber]->isComputer()){return;}


	game_counter ++;

	ComPlayer* com = (ComPlayer*)players[turnNumber];
	com->disp();//盤面情報の表示と取得

	if (game_counter == 1){
		com->readCsv();
	}

	com->setGame_counter(game_counter);

	Pixel2d move = com->getNextMove();
	turnEvent(move.x,move.y,true);


}


//ゲームの終了処理
void GameManage::gameEnd(){
	board->dispStateNumber();

}

void GameManage::mouseClick(int x,int y){
	turnEvent((int)(x/scaleW),(int)(y/scaleH),false);
}

void GameManage::drawBoard(){
	board->drawBoard();
}

void GameManage::dispResult(){
	board->dispStateNumber();
}

void GameManage::makeHandicap(int val , eState state)
{
	board->setHandicap(val, state);
}
