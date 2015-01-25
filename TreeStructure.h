#pragma once

class Tree
{
private:
	Tree(void){};
public:
	Tree(int _max_depth);
	~Tree();

//�����o�ϐ�
private:
	int max_depth;	//�K�w(root��0�Ƃ���)
	vector<vector<Node>> node;				//��ڂ��[���A��ڂ����̐[���ł̃C���f�b�N�X
	int id_counter;				//���Ԗ؂̔ԍ�
	vector<Pixel2d> sequence;

//�����o�֐�
public:
	void disp();
	void dispNode(int _depth);

	//����[���̃m�[�h��ݒ�
	void setNode(vector<Pixel2d> child,int index_depth, int id_parent);


	//����[���̃m�[�h����ԋp
	int Tree::getNodeNum(int _depth);

	//����id�̃m�[�h��T������
	void Tree::findChoiceById(int _id, Pixel2d& choice);


	void Tree::findDepthColById(int _id, Pixel2d& pos);


	//�e�m�[�h��ID���擾
	void Tree::findParentIDByPos(int _depth, int col, int& id);



	//�m�[�h�ɂ��ǂ蒅���܂ł̎菇��Ԃ�
	void getNodeRoute(const int _depth,const int col);

	int getNodeId(const int _depth,const int col);

	void getSequence(vector<Pixel2d>& _sequence);

	//�m�[�h�ɕ]���l����
	void Tree::setEvaluationOfNode(int _depth, int _col, int val);

	//�m�[�h����\��
	void Tree::dispNodeData(int _depth, int _col);

	//�e�m�[�h�ւ̕]���l�̑������
	void Tree::calMinMaxNode(int _depth, int _max_depth);

	//����[���̍ő�l�����m�[�h�̎���擾
	Pixel2d Tree::getChoiceOfMax(int _depth);







	//�g��Ȃ�
	//void getNodeBoard(vector<vector<eState>>& _node_board, int d, int index);
	//void setNodeBoard(vector<vector<eState>>& _node_board, int d, int index);
};

