#pragma once

class Node
{
private:
	Node(void){};
public:
	Node(Pixel2d _choice);
	Node(Pixel2d _choice,int _id,int _parent_id,int _rank);
	~Node();

private:
	int id;
	Pixel2d choice;
	int rank;	//ê[Ç≥
	int parent_id;	
	int val_evaluation;	//ï]âøíl

public:
	void disp();
	void getChoice(Pixel2d& tmp_choice);
	void setParent_id(int _parent_id){parent_id = _parent_id;}
	int getId(){ return(id); }
	void getParent_id(int &id);
	void setId(int _id){id = _id;}
	void setVal_evaluation(int& _val){ val_evaluation = _val; }
	void getVal_evaluation(int& _val){ _val = val_evaluation; }
};
