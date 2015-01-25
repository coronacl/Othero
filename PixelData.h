class Pixel2d{
public:
	int x,y;
	Pixel2d(){x=y=0;}
	Pixel2d(int _x,int _y){x=_x;y=_y;}
	~Pixel2d(){}
	void set(int _x,int _y){x=_x;y=_y;}
};