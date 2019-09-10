// draw3D.cpp : ����Ӧ�ó������ڵ㡣
//

#include <windows.h>
#include "stdafx.h"
#include "draw3D.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

#define MAX_LOADSTRING 100

using namespace std;

double i=0;
double j=0;//ȫ�ֱ��������ڿ����ӽ� 
class mVector{//������
protected:
	double x,y,z;
public:
	mVector(){
		x=0;
		y=0;
		z=0;
	}
	void setDirection(double px,double py,double pz){
		x=px;
		y=py;
		z=pz;
	}
	bool operator!()const{//������������
		if(x==0&&y==0&&z==0)return true;
		return false;
	}
	bool isValid(){
		if(x==0&&y==0&&z==0)return false;
		return true;
	}
	mVector(double px,double py,double pz){
		setDirection(px,py,pz);
	}
	mVector(const mVector& x1){
		setDirection(x1.getX(),x1.getY(),x1.getZ());
	}
	void setDirection(const mVector& x1){
		setDirection(x1.getX(),x1.getY(),x1.getZ());
	}
	double getX()const{
		return x;
	}
	double getY()const{
		return y;
	}
	double getZ()const{
		return z;
	}
	friend bool operator==(const mVector&,const mVector&);
	friend mVector operator+(const mVector&,const mVector&);
	friend mVector operator-(const mVector&,const mVector&);
	friend double operator*(const mVector&,const mVector&);//�������
	friend mVector operator*(const double,const mVector&);//������������
	friend mVector operator^(const mVector&,const mVector&);//�������
	friend mVector operator%(const mVector&,const mVector&);//��������
	friend double findCos(const mVector&,const mVector&);//�����������нǵ�����ֵ
};
bool operator==(const mVector& x1,const mVector& x2){
	if(!x1||!x2)return false;
	if(x1.getX()==x2.getX()&&x1.getY()==x2.getY()&&x1.getZ()==x2.getZ())return true;
	return false;
}
mVector operator+(const mVector& x1,const mVector& x2){
	mVector result(x1.getX()+x2.getX(),x1.getY()+x2.getY(),x1.getZ()+x2.getZ());
	return result;
}
mVector operator-(const mVector& x1,const mVector& x2){
	mVector result(x1.getX()-x2.getX(),x1.getY()-x2.getY(),x1.getZ()-x2.getZ());
	return result;
}
double operator*(const mVector& x1,const mVector& x2){
	return x1.getX()*x2.getX()+x1.getY()*x2.getY()+x1.getZ()*x2.getZ();
}
mVector operator*(const double lambda,const mVector& x){
	mVector result(lambda*x.getX(),lambda*x.getY(),lambda*x.getZ());
	return result;
}
mVector operator^(const mVector& x1,const mVector& x2){
	mVector result(x1.getY()*x2.getZ()-x1.getZ()*x2.getY(),x1.getZ()*x2.getX()-x1.getX()*x2.getZ(),x1.getX()*x2.getY()-x1.getY()*x2.getX());
	return result;
}
mVector operator%(const mVector& x1,const mVector& x2){
	double theta=(x1*x2)/(x2*x2);
	mVector result(x1.getX()-theta*x2.getX(),x1.getY()-theta*x2.getY(),x1.getZ()-theta*x2.getZ());
	return result;
}
double findCos(const mVector& x1,const mVector& x2){
	double theta=(x1*x2)/(sqrt((x1*x1)*(x2*x2)));
	return theta;
}
class direction:public mVector{//��λ������������
private:
public:
	direction(){
		x=0;
		y=0;
		z=0;
	}
	void setDirection(double px,double py,double pz){
		double r=px*px+py*py+pz*pz;
		if(r==0){
			x=0;
			y=0;
			z=0;
		}
		else{//���������������ڵ�λ��
			r=sqrt(r);
			x=px/r;
			y=py/r;
			z=pz/r;
		}
	}
	direction(double px,double py,double pz){
		setDirection(px,py,pz);
	}
	direction(const direction& x1){
		setDirection(x1.getX(),x1.getY(),x1.getZ());
	}
	void setDirection(const direction& x1){
		setDirection(x1.getX(),x1.getY(),x1.getZ());
	}
	friend bool operator==(const direction&,const direction&);
	friend direction operator+(const direction&,const direction&);
	friend direction operator-(const direction&,const direction&);
	friend double operator*(const direction&,const direction&);
	friend direction operator^(const direction&,const direction&);
	friend direction operator%(const direction&,const direction&);
};
bool operator==(const direction& x1,const direction& x2){
	if(!x1||!x2)return false;
	if(x1.getX()==x2.getX()&&x1.getY()==x2.getY()&&x1.getZ()==x2.getZ())return true;
	return false;
}
direction operator+(const direction& x1,const direction& x2){
	direction result(x1.getX()+x2.getX(),x1.getY()+x2.getY(),x1.getZ()+x2.getZ());
	return result;
}
direction operator-(const direction& x1,const direction& x2){
	direction result(x1.getX()-x2.getX(),x1.getY()-x2.getY(),x1.getZ()-x2.getZ());
	return result;
}
double operator*(const direction& x1,const direction& x2){
	return x1.getX()*x2.getX()+x1.getY()*x2.getY()+x1.getZ()*x2.getZ();
}
direction operator^(const direction& x1,const direction& x2){
	direction result(x1.getY()*x2.getZ()-x1.getZ()*x2.getY(),x1.getZ()*x2.getX()-x1.getX()*x2.getZ(),x1.getX()*x2.getY()-x1.getY()*x2.getX());
	return result;
}
direction operator%(const direction& x1,const direction& x2){
	double theta=x1*x2;
	direction result(x1.getX()-theta*x2.getX(),x1.getY()-theta*x2.getY(),x1.getZ()-theta*x2.getZ());
	return result;
}
class coordination{//����ϵ��
private:
	direction x,y,z;//x,y,z�᷽��
public:
	coordination(){
		x.setDirection(1,0,0);
		y.setDirection(0,1,0);
		z.setDirection(0,0,1);
	}
	void orthogonalize(){
		y=y%x;
		z=x^y;
	}
	coordination(const direction& px,const direction& py,const direction& pz,bool ortho=false){
		if(!px||!py||!pz){
			x.setDirection(1,0,0);
			y.setDirection(0,1,0);
			z.setDirection(0,0,1);
		}
		else{
			x.setDirection(px);
			y.setDirection(py);
			z.setDirection(pz);
		}
		if(ortho)orthogonalize();
	}
	direction getX()const{
		return x;
	}
	direction getY()const{
		return y;
	}
	direction getZ()const{
		return z;
	}
	bool isDefault(){
		if(x.getX()==1&&x.getY()==0&&x.getZ()==0&&y.getX()==0&&y.getY()==1&&y.getZ()==0&&z.getX()==0&&z.getY()==0&&z.getZ()==1)return true;
		return false;
	}
	bool isOrthogonal(){
		if(x*y==0&&x*z==0&&y*z==0)return true;
		return false;
	}
	void setOrthogonal(const direction& x1,const direction& x2){//����ϵ������
		x=x1;
		y=x2%x1;
		z=x^y;
	}
	coordination(const coordination& Coord,bool ortho=false){
		x.setDirection(Coord.getX());
		y.setDirection(Coord.getY());
		z.setDirection(Coord.getZ());
		if(ortho)orthogonalize();
	}
	void setCoordination(const direction& x1,const direction& x2,const direction& x3,bool ortho=false){
		x.setDirection(x1);
		y.setDirection(x2);
		z.setDirection(x3);
		if(ortho)orthogonalize();
	}
	void setCoordination(const coordination& c,bool ortho=false){
		x.setDirection(c.getX());
		y.setDirection(c.getY());
		z.setDirection(c.getZ());
		if(ortho)orthogonalize();
	}
};
struct canvas{
	int width,height;
};
struct pixel{//������
	int x,y;
	pixel(){
		x=-1;
		y=-1;
	}
	pixel(int px,int py){
		x=px;
		y=py;
	}
	pixel(const pixel& p){
		x=p.x;
		y=p.y;
	}
	friend pixel operator-(const pixel&,const pixel&); 
};
pixel operator-(const pixel& p1,const pixel& p2){
	pixel result(p1.x-p2.x,p1.y-p2.y);
	return result;
}
struct location3D{//����������ά����ϵ�г�����λ��
	double x,y,z;
	location3D(){
		x=0;
		y=0;
		z=0;
	}
	location3D(double px,double py,double pz){
		x=px;
		y=py;
		z=pz;
	}
	location3D(const location3D& l){
		x=l.x;
		y=l.y;
		z=l.z;
	}
};
location3D operator+(const location3D& p,const mVector& v){//������������õ���
	location3D result(p.x+v.getX(),p.y+v.getY(),p.z+v.getZ());
	return result;
}
mVector operator-(const location3D& p1,const location3D& p2){//���������õ�����
	mVector result(p1.x-p2.x,p1.y-p2.y,p1.z-p2.z);
	return result;
}
struct color{//ɫ����
	int red,green,blue;
	color(){
		red=0;
		green=0;
		blue=0;
	}
	color(int r,int g,int b){
		if(r>255){
			red=255;
		}
		else if(r<0){
			red=0;
		}
		else{
			red=r; 
		}
		if(g>255){
			green=255;
		}
		else if(g<0){
			green=0;
		}
		else{
			green=g;
		}
		if(b>255){
			blue=255;
		}
		else if(b<0){
			blue=0;
		}
		else{
			blue=b;
		}
	}
	color(const color&c){
		if(c.red>255){
			red=255;
		}
		else if(c.red<0){
			red=0;
		}
		else{
			red=c.red;
		}
		if(c.green>255){
			green=255;
		}
		else if(c.green<0){
			green=0;
		}
		else{
			green=c.green;
		}
		if(c.blue>255){
			blue=255;
		}
		else if(c.blue<0){
			blue=0;
		}
		else{
			blue=c.blue;
		}
	}
	void set(int r,int g,int b){
		if(r>255){
			red=255;
		}
		else if(r<0){
			red=0;
		}
		else{
			red=r; 
		}
		if(g>255){
			green=255;
		}
		else if(g<0){
			green=0;
		}
		else{
			green=g;
		}
		if(b>255){
			blue=255;
		}
		else if(b<0){
			blue=0;
		}
		else{
			blue=b;
		}
	}
	friend color operator+(const color&,const color&);//����ɫ�ʵ���
	friend color operator-(const color&,const color&);
	friend color operator*(const double,const color&);
};
color operator+(const color& c1,const color& c2){
	color result(c1.red+c2.red,c1.green+c2.green,c1.blue+c2.blue);
	return result;
}
color operator-(const color& c1,const color& c2){
	color result(c1.red-c2.red,c1.green-c2.green,c1.blue-c2.blue);
	return result;
}
color operator*(const double d,const color& c){
	color result(d*c.red,d*c.green,d*c.blue);
	return result;
}
struct light{//������
	color lColor;//���ɫ��
	direction lDirection;//��ķ���
	double lightIntensity;//���ǿ��
	location3D lightLocation;//��Դλ��
	light(){//���ܳ��֡��ڹ⡱���е����
		lColor.red=0;
		lColor.green=0;
		lColor.blue=0;
		lDirection.setDirection(0,0,0);
		lightIntensity=0;
		lightLocation.x=0;
		lightLocation.y=0;
		lightLocation.z=0;
	}
	light(const color& c,const direction& dir,const double i,const location3D l){
		lColor=c;
		lDirection=dir;
		lightIntensity=i;
		lightLocation=l;
	}
	light(const light& l){
		lColor=l.lColor;
		lDirection=l.lDirection;
		lightIntensity=l.lightIntensity;
		lightLocation=l.lightLocation;
	}
};
class scene3D{//����ϵͳ,͸��ϵͳ,��,����,��Ⱦ,��ɫ,����ά��������Ϊ����,�����������ȷ����ͼ˳����Զ���������
//������: ����������ϵͳ, ����, 2D��ͼ, �������棺��ӿؼ�����Ӧ����¼���ʵ��3D����Ĵ������޸�, �ļ�ϵͳ���½������ļ���, �ѹ⻬�����Զ�����������񻯵�΢����
//�����䣺���������Ŀռ��ϵ����������Ч������ײ�������ȣ�
private:
	//��λϵͳ
	location3D origin;//�������Ĵ���ԭ������
	coordination vectors;//����ϵ����
	//͸��ϵͳ
	double scale;//���굥λ1�����������
	double zoom;//��Ļ��ÿǰ��1��λ����������Сϵ��
	canvas window;//���洰��ߴ磨δʵ�֣�
	//��ϵͳ
	light lt;//���滷����Դ��Ϣ������Դ��
	double calcShrinkage(double CoordY){//��zoomֵ����������С�ĳ̶�
		return zoom*(-1)*CoordY+1;
	}
public:
	scene3D(location3D orig,coordination coord,double s,double z,int hCanvas,int wCanvas,light l){
		origin.x=orig.x;
		origin.y=orig.y;
		origin.z=orig.z;
		vectors.setCoordination(coord);
		scale=s;
		zoom=z;
		window.height=hCanvas;
		window.width=wCanvas;
		lt=l;
	}
	pixel projection(location3D p){//����ά��ת��Ϊ��Ļ��
		mVector rCoord(p.x-origin.x,p.y-origin.y,p.z-origin.z);
		mVector p1(vectors.getX().getX(),vectors.getY().getX(),vectors.getZ().getX());//��ά��������Ļ����ϵ�µ�x����
		mVector p2(vectors.getX().getY(),vectors.getY().getY(),vectors.getZ().getY());//��ά��������Ļ����ϵ�µ�y����
		mVector p3(vectors.getX().getZ(),vectors.getY().getZ(),vectors.getZ().getZ());//��ά��������Ļ����ϵ�µ�z����
		mVector rScreen(p1*rCoord,p2*rCoord,p3*rCoord);//������ά������Ļ����ϵ�µ�x,y,z����
		pixel proj;
		double shrinkage=calcShrinkage(rScreen.getY());//������Ļ����ϵ�µ�y�����������ϵ��
		if(shrinkage<=0){//Զ��������������
			proj.x=-1;
			proj.y=-1;
			return proj;
		}
		proj.x=window.width/2+(int)(rScreen.getX()*scale*shrinkage);//�Ӵ����������������ƶ����ҵ�ӳ������ص�
		proj.y=window.height/2-(int)(rScreen.getZ()*scale*shrinkage);
		return proj;
	}
	const light& lightInfo(){
		return lt;
	}
	void setOrigin(double x1,double y1,double z1){
		origin.x=x1;
		origin.y=y1;
		origin.z=z1;
	} 
	location3D getOrigin(){
		return origin;
	}
	void setCoordination(const direction& d1,const direction& d2,const direction& d3,bool ortho=false){
		vectors.setCoordination(d1,d2,d3,ortho);
	}
	direction getCoordination1(){
		return vectors.getX();
	}
	direction getCoordination2(){
		return vectors.getY();
	}
	direction getCoordination3(){
		return vectors.getZ();
	}
	canvas getCanvas(){
		return window;
	}
};
class object3D{//3D������
protected:
public:
};
class surface:public object3D{//3D��������
protected:
public:
	virtual void draw(scene3D&,HDC,bool)=0;
};
class triangle3D:public surface{//3D����������
private:
	location3D vertex1,vertex2,vertex3;//�����ζ������ά����
	mVector d1,d2,d3;//d1,d2Ϊ����������d3Ϊ������
	color surfaceColor;//�����ɫ
protected:
public:
	triangle3D(){
	}
	triangle3D(const location3D& v1,const location3D& v2,const location3D& v3,const color& c){//©�����û��豣֤�����ĵ㲻����ͬ�������ĵ�Ӧ���������������ʱ�뷽�����
		vertex1=v1;
		vertex2=v2;
		vertex3=v3;
		d1.setDirection(vertex2.x-vertex1.x,vertex2.y-vertex1.y,vertex2.z-vertex1.z);//���㷽������
		d2.setDirection(vertex3.x-vertex2.x,vertex3.y-vertex2.y,vertex3.z-vertex2.z);
		d3=d1^d2;//���ݷ���������������ϵ�������Ϊʲô���캯���Ĳ������������ʱ�뷽�������
		surfaceColor=c;
	}
	void set(const location3D& v1,const location3D& v2,const location3D& v3,const color& c){
		vertex1=v1;
		vertex2=v2;
		vertex3=v3;
		d1.setDirection(vertex2.x-vertex1.x,vertex2.y-vertex1.y,vertex2.z-vertex1.z);
		d2.setDirection(vertex3.x-vertex2.x,vertex3.y-vertex2.y,vertex3.z-vertex2.z);
		d3=d1^d2;
		surfaceColor=c;
	}
	void draw(scene3D& scene,HDC hdc,bool ifRender=true){
		if(scene.getCoordination1().getY()*d3.getX()+scene.getCoordination2().getY()*d3.getY()+scene.getCoordination3().getY()*d3.getZ()>0)return;
		//����͸��ϵͳ��һ�������ǣ�Զ������������x�᷽���ϵ�������һЩ����ά����ϵ��Ӧ�����ڱεı��棬��͸��ϵͳ�·���Ӧ����������
		HBRUSH Brush=CreateSolidBrush(RGB(surfaceColor.red,surfaceColor.green,surfaceColor.blue));
		HPEN Pen=CreatePen(PS_SOLID,1,RGB(surfaceColor.red,surfaceColor.green,surfaceColor.blue)); 
		SelectObject(hdc,Brush);
		SelectObject(hdc,Pen);
		pixel p1=scene.projection(vertex1);//������ά�����Ӧ����Ļ����ֵ
		pixel p2=scene.projection(vertex2);
		pixel p3=scene.projection(vertex3);
		POINT pt[3]={{p1.x,p1.y},{p2.x,p2.y},{p3.x,p3.y}};
		Polygon(hdc,pt,3);//���߻���ͼ��
		DeleteObject(Pen);
		DeleteObject(Brush);
		if(ifRender){//��Ⱦ��Ч��
			render(scene,hdc);
		}
	}
	void render(scene3D& scene,HDC hdc){
		//double deltaS=0.05;//��Ⱦ��㲽�����Զ����ڹ��ܣ���������͸��ϵͳ����Զ���ļ��㲻׼ȷ������޷�ʵ�����õĹ���
		//double deltaT=0.05;
		//pixel pSave;
		//bool enter=true;
		//���ڲ���ֵ�̶����ϴ�����ֻ�õ�����΢��Ⱦ����С����ȴ�õ��˹��ص���Ⱦ
		//������㷽��ʹ����Ⱦ���ķֲ����Բ�����
		for(double s=0.0;s<=1;s+=0.05){//������͸��ϵͳ�ļ����У�Զ��ֱ������õ����ߣ�������Polygon������ֻͶӰ���㣬Ȼ������ֱ�ߣ��������㷽�������ͶӰ���õ���ͼ�β���һ��
			for(double t=0.0;t<=1;t+=0.05){
				location3D v=vertex2+s*((-t)*d1+(1-t)*d2);
				pixel p=scene.projection(v);
				/*if(enter){
					pSave=p;
					enter=false;
				}
				else{
					pixel deltaP=p-pSave;
					if(abs(deltaP.x)>=2&&abs(deltaP.y)>=2){
						deltaS*=0.4;
						deltaT*=0.4;
					}
					else if(abs(deltaP.x)<1&&abs(deltaP.y)<1){
						deltaS*=2;
						deltaT*=2;
					}
					pSave=p;
				}//�����Ե���*/
				double paraAngle=findCos(scene.lightInfo().lDirection,d3);//�����Դ������ƽ�淨����ļнǵ�����ֵ
				color c;
				if(paraAngle<=0){//������Ĺ���ɫ�ʽ���У�������ǹ�ǿ����Դ����ľ��룬��Դ��ƽ�淨��ļн�
					c=surfaceColor-scene.lightInfo().lightIntensity*abs(paraAngle)*(1/((v-scene.lightInfo().lightLocation)*(v-scene.lightInfo().lightLocation))*scene.lightInfo().lColor);
				}
				else{
					c=surfaceColor+scene.lightInfo().lightIntensity*paraAngle*(1/((v-scene.lightInfo().lightLocation)*(v-scene.lightInfo().lightLocation))*scene.lightInfo().lColor);
				}
				SetPixelV(hdc,p.x,p.y,RGB(c.red,c.green,c.blue));//�����Ⱦ��
			}
		}
	}	 
};
class rect3D:public surface{//3D������
private:
	location3D vertex1,vertex2,vertex3,vertex4;
	mVector d1,d2,d3;
	color surfaceColor;
public:
	rect3D(const location3D& v1,const location3D& v2,const location3D& v3,const color& c){
		vertex1=v1; 
		vertex2=v2;
		vertex3=v3;
		d1.setDirection(vertex2.x-vertex1.x,vertex2.y-vertex1.y,vertex2.z-vertex1.z);
		d2.setDirection(vertex3.x-vertex2.x,vertex3.y-vertex2.y,vertex3.z-vertex2.z);
		d3=d1^d2;
		vertex4=v1+d2;//��֤���һ��������ǰ�������㹲��
		surfaceColor=c;
	}
	void draw(scene3D& scene,HDC hdc,bool ifRender=true){
		if(scene.getCoordination1().getY()*d3.getX()+scene.getCoordination2().getY()*d3.getY()+scene.getCoordination3().getY()*d3.getZ()>0)return;
		HBRUSH Brush=CreateSolidBrush(RGB(surfaceColor.red,surfaceColor.green,surfaceColor.blue));
		HPEN Pen=CreatePen(PS_SOLID,1,RGB(surfaceColor.red,surfaceColor.green,surfaceColor.blue));
		SelectObject(hdc,Brush);
		SelectObject(hdc,Pen);
		pixel p1=scene.projection(vertex1);
		pixel p2=scene.projection(vertex2);
		pixel p3=scene.projection(vertex3);
		pixel p4=scene.projection(vertex4);
		POINT pt[4]={{p1.x,p1.y},{p2.x,p2.y},{p3.x,p3.y},{p4.x,p4.y}};
		Polygon(hdc,pt,4);
		DeleteObject(Pen); 
		DeleteObject(Brush);
		if(ifRender){
			render(scene,hdc);
		}
	}
	void render(scene3D& scene,HDC hdc){//��֧�ֶ��Դ��ֻ�о����Դ�����������ȾЧ�����ԣ��������
	//û��ʵ����ӰЧ�����������岻���ڹ⣬��Ҳ�Եò���Ȼ����ʵ
		for(double s=0.0;s<=1;s+=0.05){
			for(double t=0.0;t<=1;t+=0.01){
				location3D v=vertex2+s*d2+(-t)*d1;
				pixel p=scene.projection(v);
				double paraAngle=findCos(scene.lightInfo().lDirection,d3);
				color c;
				if(paraAngle<=0){//��ǿ�����ƺ�����
					c=surfaceColor-scene.lightInfo().lightIntensity*abs(paraAngle)*(1/((v-scene.lightInfo().lightLocation)*(v-scene.lightInfo().lightLocation))*scene.lightInfo().lColor);
				}
				else{
					c=surfaceColor+scene.lightInfo().lightIntensity*paraAngle*(1/((v-scene.lightInfo().lightLocation)*(v-scene.lightInfo().lightLocation))*scene.lightInfo().lColor);
				}
				SetPixelV(hdc,p.x,p.y,RGB(c.red,c.green,c.blue));
			}
		}
	}
};
class trapezium3D:public surface{//3D������
private:
	location3D vertex1,vertex2,vertex3,vertex4;
	mVector d1,d2,d3;
	color surfaceColor;
public:
	trapezium3D(const location3D& v1,const location3D& v2,const location3D& v3,const location3D& v4,const color& c){
		vertex1=v1; 
		vertex2=v2;
		vertex3=v3;
		d1.setDirection(vertex2.x-vertex1.x,vertex2.y-vertex1.y,vertex2.z-vertex1.z);
		d2.setDirection(vertex3.x-vertex2.x,vertex3.y-vertex2.y,vertex3.z-vertex2.z);
		d3=d1^d2;
		mVector extra=(v4-v3)%d3;
		vertex4=v3+extra;//��������һ�������λ�ã�Ϊ��֤��ǰ�������㹲�棩
		surfaceColor=c;
	}
	void draw(scene3D& scene,HDC hdc,bool ifRender=true){
		if(scene.getCoordination1().getY()*d3.getX()+scene.getCoordination2().getY()*d3.getY()+scene.getCoordination3().getY()*d3.getZ()>0)return;
		HBRUSH Brush=CreateSolidBrush(RGB(surfaceColor.red,surfaceColor.green,surfaceColor.blue));
		HPEN Pen=CreatePen(PS_SOLID,1,RGB(surfaceColor.red,surfaceColor.green,surfaceColor.blue));
		SelectObject(hdc,Brush);
		SelectObject(hdc,Pen);
		pixel p1=scene.projection(vertex1);
		pixel p2=scene.projection(vertex2);
		pixel p3=scene.projection(vertex3);
		pixel p4=scene.projection(vertex4);
		POINT pt[4]={{p1.x,p1.y},{p2.x,p2.y},{p3.x,p3.y},{p4.x,p4.y}};
		Polygon(hdc,pt,4);
		DeleteObject(Pen); 
		DeleteObject(Brush);
		if(ifRender){
			render(scene,hdc);
		}
	}
	void render(scene3D& scene,HDC hdc){
		for(double s=0.0;s<=1;s+=0.05){
			for(double t=0.0;t<=1;t+=0.01){
				location3D v1=vertex2+s*((-t)*d1+(1-t)*d2);//��Ⱦ����������
				pixel p1=scene.projection(v1);
				double paraAngle=findCos(scene.lightInfo().lDirection,d3);
				color c1;
				if(paraAngle<=0){
					c1=surfaceColor-scene.lightInfo().lightIntensity*abs(paraAngle)*(1/((v1-scene.lightInfo().lightLocation)*(v1-scene.lightInfo().lightLocation))*scene.lightInfo().lColor);
				}
				else{
					c1=surfaceColor+scene.lightInfo().lightIntensity*paraAngle*(1/((v1-scene.lightInfo().lightLocation)*(v1-scene.lightInfo().lightLocation))*scene.lightInfo().lColor);
				}
				SetPixelV(hdc,p1.x,p1.y,RGB(c1.red,c1.green,c1.blue));
				mVector md1,md2;
				md1=vertex4-vertex3;
				md2=vertex1-vertex4;
				location3D v2=vertex4+s*((-t)*md1+(1-t)*md2);
				pixel p2=scene.projection(v2);
				color c2;
				if(paraAngle<=0){
					c2=surfaceColor-scene.lightInfo().lightIntensity*abs(paraAngle)*(1/((v2-scene.lightInfo().lightLocation)*(v2-scene.lightInfo().lightLocation))*scene.lightInfo().lColor);
				}
				else{
					c2=surfaceColor+scene.lightInfo().lightIntensity*paraAngle*(1/((v2-scene.lightInfo().lightLocation)*(v2-scene.lightInfo().lightLocation))*scene.lightInfo().lColor);
				}
				SetPixelV(hdc,p2.x,p2.y,RGB(c2.red,c2.green,c2.blue));
			}
		}
	}
};
class entity3D{//�����࣬���ڰ�3D����������һ���Ϊ����
protected:
	struct entityNode{//�ڽ�����
		surface *facet;
		entityNode *next;
	};
	entityNode *head,*tail;
public:
	entity3D(){
		head=new entityNode;
		tail=head;
	}
	~entity3D(){
		tail=head;
		while(tail!=NULL){
			head=head->next;
			delete tail;
			tail=head;
		}
	}
	void add(surface& s){//��3D������ӵ�������
		tail->next=new entityNode;
		tail=tail->next;
		tail->facet=&s;
		tail->next=NULL;
	}
	void draw(scene3D& scene,HDC hdc,bool ifRender=true){//������������е�3D����
		entityNode* ptr=head->next;
		while(ptr!=NULL){
			ptr->facet->draw(scene,hdc,ifRender);
			ptr=ptr->next;
		}
	}
};
class distanceManager{//Ӧ�����ϵ�scene3D���У�����ͬ���嵽�۲��ߵľ���
private:
	struct dNode{//�ڽ�����ڵ㹹�ɵ�����
		entity3D *obj;
		bool settled;
		location3D approx_coord;
		double approx_dist;
		dNode* next;
	};
	dNode *head,*tail;
public:
	distanceManager(){
		head=new dNode;
		tail=head;
	}
	~distanceManager(){
		tail=head;
		while(tail!=NULL){
			head=head->next;
			delete tail;
			tail=head;
		}
	}
	void add(entity3D& e,double coordX,double coordY,double coordZ){//������壬����ÿ������Ĵ�������
		tail->next=new dNode;
		tail=tail->next;
		tail->obj=&e;
		tail->settled=false;
		tail->approx_coord.x=coordX;
		tail->approx_coord.y=coordY;
		tail->approx_coord.z=coordZ;
		tail->approx_dist=-1;
		tail->next=NULL;
	}
	void reset(){//��������������������
		dNode* ptr=head->next;
		while(ptr!=NULL){
			ptr->settled=false;
			ptr=ptr->next;
		}
	}
	void draw(scene3D& scene,HDC hdc,bool ifRender=true){//����ÿ�����嵽�۲��ߵľ��룬��Զ�������л���
		dNode* ptr=head->next;
		while(ptr!=NULL){
			mVector r=ptr->approx_coord-scene.getOrigin();
			mVector v(scene.getCoordination1().getY(),scene.getCoordination2().getY(),scene.getCoordination3().getY());
			ptr->approx_dist=r*v;//�������
			ptr=ptr->next;
		}
		int count;
		dNode* ptrFarSave;
		double distSave;
		do{
			count=0;//��settled=false�Ľڵ���м���
			ptrFarSave=NULL;
			ptr=head->next;
			while(ptr!=NULL){
				if(ptr->settled==true){
					ptr=ptr->next;
					continue;
				}
				else{
					++count;
					if(ptrFarSave==NULL){
						ptrFarSave=ptr;
						distSave=ptr->approx_dist;
					}
					else if(ptr->approx_dist>distSave){//�ҵ�������Զ������
						ptrFarSave=ptr;
						distSave=ptr->approx_dist;
					}
					ptr=ptr->next;
				}
			}
			ptrFarSave->obj->draw(scene,hdc,ifRender);//��Զ�����������л��ƣ���settled�����Ϊtrue��settled=false�Ľڵ��������1
			ptrFarSave->settled=true;
			--count;
		}
		while(count>0);
	} 
};
class meshMountain:public entity3D{//���γ��Խ�3ά�����Զ�����һϵ�������α���
	//����ɽ���࣬�̳���3D������
private:
	double surfaceFunc(double x,double y){//�������溯�����ο���ά��̬�ֲ�����
		return exp((-1)*x*x+(-1)*y*y);
	}
	location3D pointTable[11][11];//�����Ԫ����
	triangle3D triangleTable[10][10][2];//�ʷ������ξ���
	color colorTable[10][10];//����ɫ�ʾ���
	color c;
public:
	double positionX,positionY,height;//����ɽ���XY�����Լ��߶�
	meshMountain(double px,double py,double h,color c1):entity3D(){
		positionX=px;
		positionY=py;
		height=h;
		c.set(c1.red,c1.green,c1.blue);
		int i=0;
		int j=0;
		for(double x=-2.0;x<=2.0;x+=0.4){//���������Ԫ
			for(double y=-2.0;y<=2.0;y+=0.4){
				pointTable[i][j].x=x+px;
				pointTable[i][j].y=y+py;
				pointTable[i][j].z=h*surfaceFunc(x,y);
				++j;
			}
			++i;
			j=0;
		}
		srand((int)time(0));
		for(int i=0;i<10;i++){//��������ɫ�ʾ���
			for(int j=0;j<10;j++){
				int r1=rand()%40;
				int r2=rand()%40;
				int r3=rand()%40;
				colorTable[i][j].set(c.red+r1-20,c.green+r2-20,c.blue+r3-20);//ÿ��ɫ�����ɫ�ڹ涨��ɫ�������������
				triangleTable[i][j][0].set(pointTable[i][j],pointTable[i+1][j],pointTable[i+1][j+1],colorTable[i][j]);//ÿ������������ʱ���ʷ�Ϊ����3D������
				triangleTable[i][j][1].set(pointTable[i+1][j+1],pointTable[i][j+1],pointTable[i][j],colorTable[i][j]);
			}
		}
		for(int i=0;i<10;i++){//��3D��������ӵ�������
			for(int j=0;j<10;j++){
				add(triangleTable[i][j][0]);
				add(triangleTable[i][j][1]);
			}
		}
	}
};
meshMountain mMountain(5,2,6,color(50,120,40));

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW3D, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW3D));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW3D));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DRAW3D);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH Brush;
	HPEN Pen;
	location3D o(0,0,0);
	direction d1(0.707,-0.707,0);
	direction d2(0.707,0.707,0);
	direction d3=d1^d2;
	coordination c(d1,d2,d3);
	//color ltColor(255,220,0);//color orange
	//color ltColor(255,0,255);
	color ltColor(255,150,0);
	direction ltdir(1,1,-1);
	double ltint=16;
	location3D ltspot(-4,-4,4);
	light lt(ltColor,ltdir,ltint,ltspot);
	scene3D s(o,c,100,0.1,768,1366,lt);//��������
	POINT ground[4]={{0,s.getCanvas().height/2},{0,s.getCanvas().height},{s.getCanvas().width,s.getCanvas().height},{s.getCanvas().width,s.getCanvas().height/2}};
	POINT sky[4]={{0,0},{0,s.getCanvas().height/2},{s.getCanvas().width,s.getCanvas().height/2},{s.getCanvas().width,0}};//���Ʊ�������أ�����Ӧ���������ӽǵ������Ʒ�Χ
	location3D v1(1.5,-2,1.2);//�����
	location3D v2(1.5,-1.2,1.2);
	location3D v3(1.0,-2,0.8);
	location3D v4(2.0,-2,0.8);
	location3D v5(1.0,-1.2,0.8);
	location3D v6(2.0,-1.2,0.8);
	location3D v7(1.0,-2,0);
	location3D v8(2.0,-2,0);
	location3D v9(2.0,-1.2,0);
	location3D v10(1.0,-1.2,0);
	location3D v11(-0.8,-4.0,0); 
	location3D v12(-0.9,-4.0,0);
	location3D v13(-0.97,-4.07,0);
	location3D v14(-0.97,-4.17,0);
	location3D v15(-0.9,-4.24,0);
	location3D v16(-0.8,-4.24,0);
	location3D v17(-0.73,-4.17,0);
	location3D v18(-0.73,-4.07,0);
	location3D v19(-0.8,-4.0,1);
	location3D v20(-0.9,-4.0,1);
	location3D v21(-0.97,-4.07,1);
	location3D v22(-0.97,-4.17,1);
	location3D v23(-0.9,-4.24,1);
	location3D v24(-0.8,-4.24,1);
	location3D v25(-0.73,-4.17,1);
	location3D v26(-0.73,-4.07,1);
	location3D v27(-0.684,-3.72,1.8);
	location3D v28(-1.016,-3.72,1.8);
	location3D v29(-1.25,-3.954,1.8);
	location3D v30(-1.25,-4.286,1.8);
	location3D v31(-1.016,-4.52,1.8);
	location3D v32(-0.684,-4.52,1.8);
	location3D v33(-0.45,-4.286,1.8);
	location3D v34(-0.45,-3.954,1.8);
	location3D v35(-0.85,-4.12,2.7);
	location3D v36(-5,4,0);
	location3D v37(2,2,0);
	location3D v38(4,6,0);
	location3D v39(2,8,0);
	location3D v40(-3,5,0);
	location3D v41(-0.5,6,7);
	location3D v42(2.5,-4,0);
	location3D v43(4.5,-4,0);
	location3D v44(4.5,-2,0);
	location3D v45(2.5,-2,0);
	location3D v46(3.0,-3.5,2);
	location3D v47(4.0,-3.5,2);
	location3D v48(4.0,-2.5,2);
	location3D v49(3.0,-2.5,2);
	color c1(110,15,15);//������ɫ
	color c2(190,200,210);
	color c3(225,255,0);
	color c4(45,30,0);
	color c5(0,150,40);
	color c6(0,65,10);
	color c7(90,125,75);
	triangle3D t1(v4,v1,v3,c2);//�ɵ㹹��3D��
	triangle3D t2(v5,v2,v6,c2);
	rect3D r1(v3,v1,v2,c1);
	rect3D r2(v6,v2,v1,c1);
	rect3D r3(v4,v3,v7,c3);
	rect3D r4(v7,v3,v5,c3);
	rect3D r5(v5,v6,v9,c3);
	rect3D r6(v9,v6,v4,c3);
	rect3D r7(v11,v19,v26,c4);
	rect3D r8(v12,v20,v19,c4);
	rect3D r9(v13,v21,v20,c4);
	rect3D r10(v14,v22,v21,c4);
	rect3D r11(v15,v23,v22,c4);
	rect3D r12(v16,v24,v23,c4);
	rect3D r13(v17,v25,v24,c4);
	rect3D r14(v18,v26,v25,c4);
	trapezium3D tr1(v19,v20,v28,v27,c5);
	trapezium3D tr2(v20,v21,v29,v28,c5);
	trapezium3D tr3(v21,v22,v30,v29,c5);
	trapezium3D tr4(v22,v23,v31,v30,c5);
	trapezium3D tr5(v23,v24,v32,v31,c5);
	trapezium3D tr6(v24,v25,v33,v32,c5);
	trapezium3D tr7(v25,v26,v34,v33,c5);
	trapezium3D tr8(v26,v19,v27,v34,c5);
	triangle3D t3(v27,v28,v35,c5);
	triangle3D t4(v28,v29,v35,c5);
	triangle3D t5(v29,v30,v35,c5);
	triangle3D t6(v30,v31,v35,c5);
	triangle3D t7(v31,v32,v35,c5);
	triangle3D t8(v32,v33,v35,c5);
	triangle3D t9(v33,v34,v35,c5);
	triangle3D t10(v34,v27,v35,c5);
	triangle3D t11(v36,v37,v41,c6);
	triangle3D t12(v37,v38,v41,c6);
	triangle3D t13(v38,v39,v41,c6);
	triangle3D t14(v39,v40,v41,c6);
	triangle3D t15(v40,v36,v41,c6);
	trapezium3D tr9(v42,v43,v47,v46,c7);
	trapezium3D tr10(v43,v44,v48,v47,c7);
	trapezium3D tr11(v44,v45,v49,v48,c7);
	trapezium3D tr12(v45,v42,v46,v49,c7);
	trapezium3D tr13(v46,v47,v48,v49,c7);
	entity3D house;//��3D�����Ϊ����
	entity3D tree;
	entity3D mountain;
	entity3D castle;
	house.add(t1);
	house.add(t2);
	house.add(r1);
	house.add(r2);
	house.add(r3);
	house.add(r4);
	house.add(r5);
	house.add(r6);
	tree.add(r7);
	tree.add(r8);
	tree.add(r9);
	tree.add(r10);
	tree.add(r11);
	tree.add(r12);
	tree.add(r13);
	tree.add(r14);
	tree.add(tr1);
	tree.add(tr2);
	tree.add(tr3);
	tree.add(tr4);
	tree.add(tr5);
	tree.add(tr6);
	tree.add(tr7);
	tree.add(tr8);
	tree.add(t3);
	tree.add(t4);
	tree.add(t5);
	tree.add(t6);
	tree.add(t7);
	tree.add(t8);
	tree.add(t9);
	tree.add(t10);
	mountain.add(t11);
	mountain.add(t12);
	mountain.add(t13);
	mountain.add(t14);
	mountain.add(t15);
	castle.add(tr13);
	castle.add(tr9);
	castle.add(tr10);
	castle.add(tr11);
	castle.add(tr12);//ʵ����һ�������и���Ļ���˳��Ҳ�����Ӱ��
	distanceManager entityManager;//��������ӵ������������
	entityManager.add(mountain,0,5,0);
	entityManager.add(tree,-0.9,-4.0,1);
	entityManager.add(house,1.5,-1.6,0.8);
	entityManager.add(castle,3.5,-3,1);
	entityManager.add(mMountain,mMountain.positionX,mMountain.positionY,mMountain.height/3);
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,3000,NULL);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,true);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		RECT r;
		GetClientRect(hWnd,&r);
		SetMapMode(hdc,MM_TEXT);
		SetWindowExtEx(hdc,1366,768,NULL);
		SetViewportExtEx(hdc,r.right,r.bottom,NULL);
		FillRect(hdc,&r,(HBRUSH)GetStockObject(BLACK_BRUSH));
		Brush=CreateSolidBrush(RGB(0,225,0));
		Pen=CreatePen(PS_SOLID,1,RGB(0,225,0));
		SelectObject(hdc,Brush);//�������
		SelectObject(hdc,Pen);
		Polygon(hdc,ground,4);
		DeleteObject(Pen); 
		DeleteObject(Brush);
		Brush=CreateSolidBrush(RGB(0,0,190));
		Pen=CreatePen(PS_SOLID,1,RGB(0,0,190));
		SelectObject(hdc,Brush);
		SelectObject(hdc,Pen);
		Polygon(hdc,sky,4);
		DeleteObject(Pen); 
		DeleteObject(Brush);
		d1.setDirection(cos(i),sin(i),0);//��������ϵ
		d2.setDirection(-sin(i),cos(i),0);
		d3.setDirection(d1^d2);
		s.setCoordination(d1,d2,d3,true);
		//s.setOrigin(j,1.4*j,0);//���z����Ϊ0���൱�ڽ����ر���й۲죬3D͸��Ч������
		s.setOrigin(j,1.4*j,1);//ģ���˵��ӽ�
		entityManager.reset();
		entityManager.draw(s,hdc);
		if(i<6){
			i+=0.1;
		} 
		else if(j<5){
			j+=0.1;
		}
		else{
			KillTimer(hWnd,1);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
