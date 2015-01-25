#include "stdafx.h"

Tree::Tree(int _max_depth)
{
	max_depth = _max_depth;


	//最大深さ分だけ、ノードのを確保
	node.resize(_max_depth+1);

	id_counter = 1;

	//node[0].push_back(Pixel2d(-1,-1));
	//node[0][0].setId(0);

}

Tree::~Tree()
{
	for (int j = 0; j<=max_depth; j++){
		node[j].clear();
	}
	node.clear();
	sequence.clear();
}

void Tree::disp()
{
	//盤面情報の表示
	//cout << endl << "盤面情報(AI's root)"  << endl;
	//for (int j = 0; j<8; j++){
	//	cout << endl;
	//	for (int i = 0; i<8; i++){
	//		cout << root_board[j][i];
	//	}
	//}
	//cout << endl;

	//各ノードの情報を表示
	cout << endl;
	for (int j = 0; j<=max_depth; j++){
		cout << "深さ=" << j << endl <<"候補手";
		for (int i = 0; i<(int)node[j].size(); i++){
			node[j][i].disp();
		}
		cout << endl;
	}


}

//====================================================
//引数	choice		ある特定の深さにおける候補手
//		index_depth	候補手の深さ
//====================================================
void Tree::setNode(vector<Pixel2d> choice,int index_depth , int id_parent)
{
	//cout << "Depth=" << index_depth << endl;
	for(int c=0;c<(int)choice.size();c++){
		node[index_depth].push_back(Node(choice[c], id_counter, index_depth, id_parent));
		id_counter++;
		//node[index_depth][c].disp();
	}

}

//====================================================
//ある深さにおけるノードの持つ候補手を表示する
//引数	_depth	ある深さ
//====================================================
void Tree::dispNode(int _depth)
{
	for  (int i = 0;  i< (int)node[_depth].size(); i++)
	{
		node[_depth][i].disp();
	}

}

//ある深さのノードの個数を返却
int Tree::getNodeNum(int _depth)
{
	//ノードの深さは0からスタート
	int num;
	num = (int)node[_depth].size();
	return(num);


}

//あるidのノードを探索する
//戻り値	choice	ノードの差し手
void Tree::findChoiceById(int _id, Pixel2d& choice)
{

	for (int j = 0; j <= max_depth; ++j)
	{
		for (int i = 0; i < getNodeNum(j); ++i)
		{
			if (_id == node[j][i].getId())
			{
				node[j][i].getChoice(choice);

			}
		}
	}

}

void Tree::findDepthColById(int _id, Pixel2d& pos)
{

	for (int j = 0; j <= max_depth; ++j)
	{
		for (int i = 0; i < (int)getNodeNum(j); ++i)
		{
			if (_id == node[j][i].getId())
			{
				pos.set(i,j);

			}
		}
	}
	

}



//ノードまでの指し手を渡す
//_depthは０から
void Tree::getNodeRoute(const int _depth, const int col)
{
	//手順の領域確保(深さは0から始まるため+1)
	sequence.resize(_depth + 1);

	//指定ノードの手を登録(sequenceの最後)
	Pixel2d tmp_choice;
	node[_depth][col].getChoice(tmp_choice);
	sequence[_depth].set(tmp_choice.x, tmp_choice.y);

	//指定ノードの親ID取得
	int tmp_id;
	node[_depth][col].getParent_id(tmp_id);

	Pixel2d tmp_position;
	findDepthColById(tmp_id, tmp_position);

	for (int d = _depth-1; d >= 0; d--)//depthの親から始まるためdepth-1
	{
		node[tmp_position.y][tmp_position.x].getChoice(tmp_choice);
		sequence[d].set(tmp_choice.x, tmp_choice.y);

		//親ノードのIDを取得
		node[tmp_position.y][tmp_position.x].getParent_id(tmp_id);
		//ルートノード到達
		if (tmp_id == -1){ break; }
		//親ノードの位置を取得
		findDepthColById(tmp_id,tmp_position);
	}

}

int Tree::getNodeId(const int _depth, const int col)
{
	int tmp =node[_depth][col].getId();
	return(tmp);
}

void Tree::getSequence(vector<Pixel2d>& _sequence)
{
	_sequence.resize((int)sequence.size());
	for (int i = 0; i < (int)sequence.size(); i++)
	{
		_sequence[i].set(sequence[i].x,sequence[i].y);
	}
	sequence.clear();
}

//戻り値	id	親ノードのID
void Tree::findParentIDByPos(int _depth, int col,int& id)
{

	node[_depth][col].getParent_id(id);

	
}

void Tree::setEvaluationOfNode(int _depth , int _col , int val)
{
	node[_depth][_col].setVal_evaluation(val);
	
}

void Tree::dispNodeData(int _depth, int _col)
{
	node[_depth][_col].disp();
}

void Tree::calMinMaxNode(int _depth , int _max_depth)
{
	vector<int> list_parent_val;
	int num_node = getNodeNum(_depth);

	//各ノードの評価値格納用
	vector<int> list_val;

	int parent_id_bf=0,parent_id_af=0;
	int tmp;

	for (int i = 0; i < num_node; i++)
	{
		if (i  == num_node-1){
			node[_depth][i].getParent_id(parent_id_bf);
			parent_id_af = -10;
		}
		else{
			node[_depth][i].getParent_id(parent_id_bf);
			node[_depth][i+1].getParent_id(parent_id_af);
		}

		node[_depth][i].getVal_evaluation(tmp);
		list_val.push_back(tmp);

		if (parent_id_bf != parent_id_af){
			//最大値・最小値探索
			vector<int>::iterator iter;
			if (_depth % 2 == 0){
				 iter = max_element(list_val.begin(), list_val.end());
			}
			else{
				iter = min_element(list_val.begin(), list_val.end());
			}
			
			size_t index = distance(list_val.begin(), iter);

			tmp = list_val[index];
			list_parent_val.push_back(tmp);

			//cout << tmp << endl;

			list_val.clear();
		}
	}

	for (int i = 0; i < (int)list_parent_val.size(); i++){
		node[_depth-1][i].setVal_evaluation(list_parent_val[i]);
	}
	
}
Pixel2d Tree::getChoiceOfMax(int _depth)
{
	int num_node = getNodeNum(_depth);

	vector<int> list_node;
	int tmp;

	for (int i = 0; i < num_node; i++)
	{
		node[_depth][i].getVal_evaluation(tmp);
		list_node.push_back(tmp);
	}

	vector<int>::iterator iter = max_element(list_node.begin(), list_node.end());
	size_t index = distance(list_node.begin(), iter);

	Pixel2d choice;
	node[_depth][index].getChoice(choice);

	//////==========
	//getNodeRoute(max_depth-1,0);
	//
	//for (int i = 0; i < (int)sequence.size(); i++)
	//{
	//	cout << "(" << sequence[i].x <<"," << sequence[i].y << ")" << endl;
	//}
	//sequence.clear();
	//////=========




	return(choice);

}




