#include "Circle.hpp"
P Inv(P a,C b){//��a����Բb�ķ��� 
	D d=b.r*b.r/(a-b.c).norm();
	return b.c+(a-b.c).unit()*d;
}
C Inv(L a,C b){//�󲻹�o��ֱ��a����Բb�ķ��� 
	return C(b.c,Inv(ProjectToLine(b.c,a),b));
}
C Inv(C a,C b){//�󲻹�o��Բa����Բb�ķ���
	P p1=a.c+(b.c-a.c).unit()*a.r,p2=a.c*2-p1;
	return C(Inv(p1,b),Inv(p2,b));
}
L Inv2(C a,C b){//���o��Բa����Բb�ķ���
	P c;
	if(!sgn(a.c.x-b.c.x))c=P(a.r,0);else c=P(0,a.r);
	return L(Inv(a.c+c,b),Inv(a.c-c,b));
}
