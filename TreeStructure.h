#pragma once

class Tree
{
private:
	Tree(void){};
public:
	Tree(int _max_depth);
	~Tree();

//メンバ変数
private:
	int max_depth;	//階層(rootを0とする)
	vector<vector<Node>> node;				//一つ目が深さ、二つ目がその深さでのインデックス
	int id_counter;				//順番木の番号
	vector<Pixel2d> sequence;

//メンバ関数
public:
	void disp();
	void dispNode(int _depth);

	//ある深さのノードを設定
	void setNode(vector<Pixel2d> child,int index_depth, int id_parent);


	//ある深さのノード数を返却
	int Tree::getNodeNum(int _depth);

	//あるidのノードを探索する
	void Tree::findChoiceById(int _id, Pixel2d& choice);


	void Tree::findDepthColById(int _id, Pixel2d& pos);


	//親ノードのIDを取得
	void Tree::findParentIDByPos(int _depth, int col, int& id);



	//ノードにたどり着くまでの手順を返す
	void getNodeRoute(const int _depth,const int col);

	int getNodeId(const int _depth,const int col);

	void getSequence(vector<Pixel2d>& _sequence);

	//ノードに評価値を代入
	void Tree::setEvaluationOfNode(int _depth, int _col, int val);

	//ノード情報を表示
	void Tree::dispNodeData(int _depth, int _col);

	//親ノードへの評価値の代入処理
	void Tree::calMinMaxNode(int _depth, int _max_depth);

	//ある深さの最大値を持つノードの手を取得
	Pixel2d Tree::getChoiceOfMax(int _depth);







	//使わない
	//void getNodeBoard(vector<vector<eState>>& _node_board, int d, int index);
	//void setNodeBoard(vector<vector<eState>>& _node_board, int d, int index);
};

