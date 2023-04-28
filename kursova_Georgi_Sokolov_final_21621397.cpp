/* 8 зад. */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*
I. Да се състави клас CColor с защитени член променливи интензивностите на
основните цветове-цяло неотрицателно число от 0 до 15
Обозачения на член променливите интензивности:
Червен: red
зелен: green
син: blue
Класът да има експлицитен конструктор по зададени интензивности:
CColor(int, int, int)
Копиращ конструктор:
CColor(CColor& )
Подразбиращ се конструктор:
CColor()
Функции:
1. Образуване на съставен цвят:
int RGB(int red, int green, int blue)
с помощта на която да може да се получава съставен цвят по интензивностите на
червения, зеления и синия цвят
2. Установяване на цвят по зададени интензивности-setColor :
void SetColors( int red, int green, int blue)
3. Получаване на интензивностите на цветовете-GetColor :
void GetColor( int& redRef, int& greenRef, int& blueRef)
4. Оператори за сравнение на два цвята == и < :
operator==
operator<
5. Оператор за извеждане на данните в поток (файл или конзола).
operator<<
*/
class CColor{
	protected:
	int red,green,blue;
	bool ColorCheck(int r, int g, int b){
		return (r>=0&&r<=15)&&(g>=0&&g<=15)&&(b>=0&&b<=15);
	}
	public:
	CColor(){
		red = 0;
		green = 0;
		blue = 0;
	}
	CColor(int r, int g, int b){
		SetColors(r,g,b);
	}
	CColor(const CColor& toCopy){
		toCopy.GetColor(this->red,this->green,this->blue);
	}
	void SetColors(int r, int g, int b){
		if(ColorCheck(r,g,b)){
			red=r;
			green=g;
			blue=b;
		}
		else {
			red=0;
			green=0;
			blue=0;
		}
	}
	void GetColor(int& redRef, int& greenRef, int& blueRef) const {
		redRef = red;
		greenRef = green;
		blueRef = blue;
	}
	void GetColor(int& redRef, int& greenRef, int& blueRef, int rgb){
		int toExtract = rgb;
		redRef = toExtract%16;
		toExtract>>=4;
		greenRef = toExtract%16;
		toExtract>>=4;
		blueRef = toExtract;
	}
	int RGB(int r, int g, int b) const {
		return (r+g*16+b*16*16);
	}
	int RGB() const {
		return RGB(red, green, blue);
	}
	bool operator==(const CColor& color){
		int rgb1,rgb2;
		rgb1 = this->RGB();
		rgb2 = color.RGB();
		return rgb1==rgb2;
	}
	bool operator<(const CColor& color){
		int rgb1,rgb2;
		rgb1 = this->RGB();
		rgb2 = color.RGB();
		return rgb1<rgb2;
	}
	friend ostream& operator<<(ostream& toStream, const CColor& color);
};
ostream& operator<<(ostream& toStream, const CColor& color){
	int r,g,b;
	color.GetColor(r,g,b);
	toStream<<" red:"<<r<<" green:"<<g<<" blue:"<<b<<endl;
	return toStream;
}

/*
II. Да се създаде производен клас цветна точка CColorPoint, основан на CColor с
член променливи координати:
координата по iX1
координата по iY1
6. Да се съставят подразбиращ се конструктор :
CColorPoint()
7. Да се състави конструктор по зададени координати и цвят
CColorPoint(int x,int y,int Color)
8. Да се състави оператор за извеждане в поток (файл или конзола). :
operator<<
*/
class CColorPoint: public CColor{
	private:
	int iX1, iY1;
	public:
	void SetXY(int x, int y){
		iX1=x;
		iY1=y;
	}
	void GetXY(int& xRef, int& yRef) const {
		xRef = iX1;
		yRef = iY1;
	}
	CColorPoint():CColor(){
		iX1 = iY1 = 0;
	}
	CColorPoint(const int x, const int y, const int rgb){
		int r,g,b;
		this->GetColor(r,g,b,rgb);
		this->SetColors(r,g,b);
		this->SetXY(x,y);
	}
	friend ostream& operator<<(ostream& toStream, CColorPoint& cpoint);
};
ostream& operator<<(ostream& toStream, CColorPoint& cpoint){
		int x,y;
		cpoint.GetXY(x,y);
		CColor *c = &cpoint;
		toStream<<"x:"<<x<<" y:"<<y;
		toStream<< *c;
		return toStream;
	}

/*
III. Да се създаде вектор от цветни точки, основан на CColorPoint, с който да може
да се изобрази многоъгълник:
· Да се създаде вектора.
· Да се изведат точките.
*/
int main(){
	cout<<"Ще се сравнят 3 цвята за проверка\nна работата на операторите за сравнение.\n";
	CColor c1, c2(0,0,0), c3(1,1,1);
	cout<<"c1==c2 : "<<(c1==c2?"true":"false")<<endl;
	cout<<"c1==c3 : "<<(c1==c3?"true":"false")<<endl;
	cout<<"c1<c2 : "<<(c1<c2?"true":"false")<<endl;
	cout<<"c1<c3 : "<<(c1<c3?"true":"false")<<endl;
	cout<<"c3<c1 : "<<(c3<c1?"true":"false")<<endl<<endl;
	
	cout<<"Ще се създаде фигура по зададен брой точки.\n";
	int N;
	do {
		cout<<"Enter number of points between 1 and 15:\n";
		cin>>N;
	} while(N<1||N>15);
	
	vector <CColorPoint> vc;
	for(int i = 0; i<N; i++)
		vc.push_back(CColorPoint(i,(i*i),(i+i*16+i*16*16)));

	ofstream output;
	output.open("output.txt", ios::out | ios::trunc);
	vector <CColorPoint>::iterator i;
	for(i=vc.begin();i!=vc.end();i++)
		output<<*i;
	output.close();

	cout<<"Ще се изведе фигурата:\n";
	ifstream toTerminal("output.txt");
	string line;
	while(getline(toTerminal,line))
		cout<<line<<endl;
	toTerminal.close();

	return 0;
}