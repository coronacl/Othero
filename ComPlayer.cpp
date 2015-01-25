#include "stdafx.h"

ComPlayer::ComPlayer(BoardManage* _board,eState _state):PlayerManage(_board,_state,true)
{
	columns = board->getColumns();
	rows = board->getRows();
	setCom_state(state);

}


ComPlayer::~ComPlayer(void){
}

//=========================================
//引数	oID		候補手
//		tgtID	候補手によって挟むことができる自分の駒の位置
//		direction	oIDからtgtIDへの方向
//=========================================
int ComPlayer::checkPiece(Pixel2d& oID, Pixel2d& tgtID, Pixel2d& direction){
	int maxLength = MAX(columns, rows);

	bool find = false;
	int reverseNum = 0;
	for (int n = 1; n<maxLength; n++){
		int i = oID.x + direction.x * n;
		int j = oID.y + direction.y * n;
		if (i<0 || i >= columns || j<0 || j >= rows){ break; }
		//空白セルがあった
		if (board_data[j][i] == EMP){ break; }
		//隣接する他色の駒があった
		else if (board_data[j][i] != state){ find = true; reverseNum++; }
		//隣接他色の後に自色の駒があった場合，駒の位置を返却
		else if (find){ tgtID.set(i, j); return reverseNum; }
		//いきなり自色が隣接していた場合
		else{ break; }
	}
	return 0;
}

int ComPlayer::checkPiece(Pixel2d& oID, Pixel2d& tgtID, Pixel2d& direction, vector<vector<eState>>& dst_board,eState _state){
	int maxLength = MAX(columns, rows);

	bool find = false;
	int reverseNum = 0;
	for (int n = 1; n<maxLength; n++){
		int i = oID.x + direction.x * n;
		int j = oID.y + direction.y * n;
		if (i<0 || i >= columns || j<0 || j >= rows){ 
			break; }
		//空白セルがあった
		if (dst_board[j][i] == EMP){ 
			break; }
		//隣接する他色の駒があった
		else if (dst_board[j][i] != _state){ 
			find = true; 
			reverseNum++; }
		//隣接他色の後に自色の駒があった場合，駒の位置を返却
		else if (find){ 
			tgtID.set(i, j); 
			return reverseNum; }
		//いきなり自色が隣接していた場合
		else{ break; }
	}
	return 0;
}

//指定ライン上の点の状態変更
//void ComPlayer::changeLinePieces(Pixel2d& sID, int reverseNum, Pixel2d& direction){
//
//	for (int n = 0; n <= reverseNum; n++){
//		int i = sID.x + direction.x*n;
//		int j = sID.y + direction.y*n;
//		if (i<0 || i >= columns || j<0 || j >= rows){ continue; }
//		af_board_data[j][i] = state;
//	}
//}

void ComPlayer::changeLinePieces(Pixel2d& sID, int reverseNum, Pixel2d& direction, vector<vector<eState>>& dst_board, eState _state)
{

	for (int n = 0; n <= reverseNum; n++){
		int i = sID.x + direction.x*n;
		int j = sID.y + direction.y*n;
		if (i<0 || i >= columns || j<0 || j >= rows){ continue; }
		dst_board[j][i] = _state;
	}
}
void changeState(eState& com)
{
	if (com == eState::BLK){
		com = eState::WHT;
	}
	else if (com == eState::WHT){
		com = eState::BLK;
	}
}

//-------------------------------------------------------
//評価値を計算
//引数		src_board	入力盤面
//戻り値	evaluation	評価値
//--------------------------------------------------------
void ComPlayer::calEvaluationVal(vector<vector<eState>>& src_board, int& evaluation)
{
	evaluation = 0;
	eState tmp_state = cpu_state;
	int num_cpu , num_you;
	num_cpu = 0;
	num_you = 0;

	changeState(tmp_state);

	//角おいたら評価値変更
	if (src_board[0][0] == cpu_state){
		csvMin[1][0] = 20;
		csvMin[0][1] = 20;
		csvMin[1][1] = 20;
		csvMax[1][0] = 20;
		csvMax[0][1] = 20;
		csvMax[1][1] = 20;
	}
	if (src_board[0][7] == cpu_state){
		csvMin[1][7] = 20;
		csvMin[0][6] = 20;
		csvMin[1][6] = 20;
		csvMax[1][7] = 20;
		csvMax[0][6] = 20;
		csvMax[1][6] = 20;
	}
	if (src_board[7][0] == cpu_state){
		csvMin[7][1] = 20;
		csvMin[6][0] = 20;
		csvMin[6][1] = 20;
		csvMax[7][1] = 20;
		csvMax[6][0] = 20;
		csvMax[6][1] = 20;
	}
	if (src_board[7][7] == cpu_state){
		csvMin[6][7] = 20;
		csvMin[7][6] = 20;
		csvMin[6][6] = 20;
		csvMax[6][7] = 20;
		csvMax[7][6] = 20;
		csvMax[6][6] = 20;
	}

	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < columns; i++)
		{
			if (src_board[j][i] == cpu_state){
				if (game_counter < 30){
					evaluation = evaluation + csvMin[j][i];
				}
				else{
					evaluation = evaluation + csvMax[j][i];
				}
				num_cpu ++;
			}
			else if (src_board[j][i] == tmp_state){
				if (game_counter < 30){
					evaluation = evaluation - csvMin[j][i];
				}
				else{
					evaluation = evaluation - csvMax[j][i];
				}
				num_you ++;
			}
		}
	}
	//evaluation = evaluation + (int)((num_you - num_cpu) * 0.5);



}


bool ComPlayer::canPutPiece(Pixel2d& id, vector<vector<eState>>& src_board,eState _state){

	//領域外の時false
	if (id.x<0 || id.x >= columns || id.y<0 || id.y >= rows){
		return false;
	}
	//空白セルじゃないときfalse
	if (board_data[id.y][id.x] != EMP){
		return false;
	}

	bool canPut = false;
	for (int j = -1; j <= 1; j++){
		for (int i = -1; i <= 1; i++){
			if (i == 0 && j == 0){ continue; }
			Pixel2d direction(i, j);
			Pixel2d findPiece;
			int reverseNum = checkPiece(id, findPiece, direction,src_board,_state);
			if (reverseNum <= 0){ continue; }
			//changeLinePieces(id,reverseNum,direction);
			canPut = true;
		}
	}

	return canPut;
}

//=============================
//引数	src_board	着手前の盤面
//		sequence		手順
//		dst_board	着手後の盤面
//=============================
void ComPlayer::changeBoard(vector<Pixel2d> sequence, vector<vector<eState>>& dst_board)
{
	eState tmp_state = cpu_state;
	for (int count = 0; count < (int)sequence.size(); ++count){
		if (count % 2 == 0){
		}
		else{
			changeState(tmp_state);
		}
		for (int j = -1; j <= 1; j++){
			for (int i = -1; i <= 1; i++){
				if (i == 0 && j == 0){ continue; }
				Pixel2d direction(j, i);
				Pixel2d findPiece;
		
				int reverseNum = checkPiece(sequence[count], findPiece, direction, dst_board, tmp_state);
				if (reverseNum <= 0){ continue; }
				changeLinePieces(sequence[count], reverseNum, direction, dst_board,tmp_state);

			}
		}
	}
}


//与えられた盤面の候補手を求める。
//候補手がない場合は、false
bool ComPlayer::canPutBoard(vector<vector<eState>> focus_board, vector<Pixel2d>* next_tmp,eState _state){

	bool canPut = false;
	for (int j = 0; j<rows; j++){
		for (int i = 0; i<columns; i++){
			if (canPutPiece(Pixel2d(i, j),focus_board,_state)){
				canPut = true;
				next_tmp->push_back(Pixel2d(i, j));
				//return Pixel2d(i,j);			
			}
		}
	}
	return(canPut);
}

//次の一手を返却
Pixel2d ComPlayer::getNextMove(){
	//=============================
	//改良版AI
	//=============================
	bool canPut = false;
	//候補手の取得
	canPut = canPutBoard(board_data, &next_choice,cpu_state);

	//パスの場合の処理
	if (canPut == false){
		//board->dispStateNumber();
		return(Pixel2d(-1,-1));
	}

	//以下、depthに応じて評価値の探索
	int depth;
	static bool flag_counter = true;
	if (game_counter > 30 && flag_counter){
		puts("change");
		flag_counter = false;
	}
	if (game_counter < 40){
		depth = 2;//0,1,2,...
	}
	else{
		depth = 4;//0,1,2,...
	}
	
	tree = new Tree(depth);

	af_board_data = board_data;

	//深さに応じて、候補手を登録
	for (int d = 0; d <= depth; ++d){

		eState tmp_state = cpu_state;
		if (d % 2 == 0){ 
		}
		else{
			changeState(tmp_state);
		}

		if (d == 0){
			tree->setNode(next_choice, d, -1);
			next_choice.clear();
		}
		else
		{
			for (int i = 0; i < (tree->getNodeNum(d-1)); i++){
				//親ノードまでの各手を登録
				tree->getNodeRoute(d-1,i);
				tree->getSequence(sequenceOfMove);

				//候補手の登録
				changeBoard( sequenceOfMove  , af_board_data);
				canPutBoard(af_board_data, &next_choice,tmp_state);

				//深さdのノードの登録
				int parent_id = tree->getNodeId(d-1, i);
				tree->setNode(next_choice, d, parent_id);

				//解放処理と盤面の初期化
				next_choice.clear();
				sequenceOfMove.clear();
				af_board_data = board_data;
			}
		}
	}	

	
	//ルートノードの評価値を計算
	int cal;//評価値
	for (int count = 0; count < tree->getNodeNum(depth); ++count)
	{
		cal = 0;
		af_board_data = board_data;

		tree->getNodeRoute(depth, count);
		tree->getSequence(sequenceOfMove);

		changeBoard(sequenceOfMove, af_board_data);

		calEvaluationVal(af_board_data, cal);
		tree->setEvaluationOfNode(depth, count, cal);

		sequenceOfMove.clear();
	}

	//minMaxの評価値を各ノードに伝達
	for (int d = depth; 1 <= d; --d){
		tree->calMinMaxNode(d,1000);
	}

	Pixel2d answer = tree->getChoiceOfMax(0);

	//tree->disp();

	tree->~Tree();


	return(answer);
}

void ComPlayer::readCsv(){

	csvMin.resize(rows);
	for (int j=0; j < rows; j++){
		csvMin[j].resize(columns);
	}

	FILE *fp;
	errno_t error;
	if ((error = fopen_s(&fp, "cell_value_min.csv", "r")) != 0){
		cout << "ファイルが開けません" << endl;
	}

	for (int i = 0; i < rows; i++)
	{
		fscanf_s(fp,"%d,%d,%d,%d,%d,%d,%d,%d,\n", &csvMin[i][0],&csvMin[i][1],&csvMin[i][2],&csvMin[i][3],&csvMin[i][4],&csvMin[i][5],&csvMin[i][6],&csvMin[i][7]);
		//puts("");
		//printf("%d,%d,%d,%d,%d,%d,%d,%d\n", csvMin[i][0],csvMin[i][1],csvMin[i][2],csvMin[i][3],csvMin[i][4],csvMin[i][5],csvMin[i][6],csvMin[i][7]);
	}
	fclose(fp);

	csvMax.resize(rows);
	for (int j=0; j < rows; j++){
		csvMax[j].resize(columns);
	}

	FILE *fp2;
	if ((error = fopen_s(&fp2, "cell_value_max.csv", "r")) != 0){
		cout << "ファイルが開けません" << endl;
	}
	for (int i = 0; i < rows; i++)
	{
		fscanf_s(fp2,"%d,%d,%d,%d,%d,%d,%d,%d,\n", &csvMax[i][0],&csvMax[i][1],&csvMax[i][2],&csvMax[i][3],&csvMax[i][4],&csvMax[i][5],&csvMax[i][6],&csvMax[i][7]);
		//puts("");
		//printf("%d,%d,%d,%d,%d,%d,%d,%d\n", csvMin[i][0],csvMin[i][1],csvMin[i][2],csvMin[i][3],csvMin[i][4],csvMin[i][5],csvMin[i][6],csvMin[i][7]);
	}
	fclose(fp2);

}

void ComPlayer::disp(){
	//盤面情報の取得
	board->getBoardData(board_data);

	//盤面情報の表示
	//cout << "盤面情報"  << endl;
	//for (int j = 0; j<rows; j++){
	//	cout << endl;
	//	for (int i = 0; i<columns; i++){
	//		cout << board_data[j][i];
	//	}
	//}
	//cout << endl;

}

//void ComPlayer::dispCsv(){
//	printf("csvのデータ\n");
//	for (int i = 0; i < rows; i++)
//	{
//		//printf("%d,%d,%d,%d,%d,%d,%d,%d\n", csvMin[i][0],csvMin[i][1],csvMin[i][2],csvMin[i][3],csvMin[i][4],csvMin[i][5],csvMin[i][6],csvMin[i][7]);
//		printf("%d,%d,%d,%d,%d,%d,%d,%d\n", csvMax[i][0],csvMax[i][1],csvMax[i][2],csvMax[i][3],csvMax[i][4],csvMax[i][5],csvMax[i][6],csvMax[i][7]);
//	}
//}
//

