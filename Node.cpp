#include "stdafx.h"

Node::Node(Pixel2d _choice)
{
	choice = _choice;
	//flag_root = 0;
	//flag_leaf = 0;
}
Node::Node(Pixel2d _choice, int _id, int _rank , int _parent_id)
{
	choice = _choice;
	id = _id;
	rank = _rank;
	parent_id = _parent_id;

}



Node::~Node()
{

}

void Node::disp()
{
	cout << " id=" << id;
	cout << "{" << "Pa=" << parent_id;
	cout << "(" << choice.x << "," << choice.y << ")" ;
	cout << "f=" << (int)val_evaluation << "}";
}

void Node::getParent_id(int &id)
{
	id = parent_id;
}

void Node::getChoice(Pixel2d& tmp_choice)
{
	tmp_choice = choice;
}



