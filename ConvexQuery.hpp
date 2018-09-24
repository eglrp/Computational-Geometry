#include "Convex.hpp"
struct Convex{//�贫����һ��͹�������ص㣬����ǿգ�pair<x,y>��С�ĵ���ڵ�һ����INFΪ���귶Χ 
	const double INF=1e9;
	int n;
	vector<P>A,up,dw;
	Convex(vector<P>_A):A(ConvexHull(_A)){//������һ���㼯���õ�����͹�� 
		int n=SZ(A),p=0;
		fr(i,n-1)if(A[p]<A[i])p=i;
		FR(i,0,p)dw.PB(A[i]);
		FR(i,p,n-1)up.PB(A[i]);
		up.PB(A[0]);
	}
	void update(P p,int id,int &v0,int &v1){
		if(det(A[v0]-p,A[id]-p)>0)v0=id;
		if(det(A[v1]-p,A[id]-p)<0)v1=id;
	}
	void fd(int l,int r,P p,int&v0,int&v1){
		if(l==r)return;
		update(p,l%n,v0,v1);
		int sl=sgn(det(A[l%n]-p,A[(l+1)%n]-p)),md,sm;
		for(;l+1<r;){
			md=l+r>>1;
			sm=sgn(det(A[md%n]-p,A[(md+1)%n]-p));
			if(sm==sl)l=md;else r=md;
		}
		update(p,r%n,v0,v1);
	}
	bool contain(P p){//�жϵ�p�Ƿ���͹����(�����߽�) 
		if(p.x<dw[0].x||p.x>dw.back().x)return 0;
		int id=lower_bound(dw.begin(),dw.end(),P(p.x,-INF))-dw.begin();
		if(dw[id].x==p.x){
			if(dw[id].y>p.y)return 0;
		}else if(det(dw[id-1]-p,dw[id]-p)<0)return 0;
		id=lower_bound(up.begin(),up.end(),P(p.x,INF),greater<P>())-up.begin();
		if(up[id].x==p.x){
			if(up[id].y<p.y)return 0;
		}else if(det(up[id-1]-p,up[id]-p)<0)return 0;
		return 1;
	}
	bool get_tangent(P p,int&v0,int&v1){//���p����͹���������е㣬�����͹���������򷵻ر�ţ����ߵĶ���е��η�һ�� 
		if(contain(p))return 0;
		v0=v1=0;
		int id=lower_bound(dw.begin(),dw.end(),p)-dw.begin(),VA=SZ(dw),VB=SZ(up);
		fd(0,id,p,v0,v1);fd(id,VA,p,v0,v1);
		id=lower_bound(up.begin(),up.end(),p,greater<P>())-up.begin();
		fd(VA-1,VA-1+id,p,v0,v1);
		fd(VA-1+id,VA-1+VB,p,v0,v1);
		return 1;
	}
	pair<double,int>get_tangent(vector<P>&q,P e){
		int l=0,r=SZ(q)-2,md;
		for(;l+1<r;){
			md=l+r>>1;
			if(sgn(det(q[md+1]-q[md],e))>0)r=md;else l=md;
		}
		return max(MP(e*q[r],r),MP(e*q[0],0));
	}
	int get_tangent(P e){//��͹���Ϻ�����e������ĵ㣬���ر�ţ����ߵĶ���е㷵������һ�� 
		pair<double,int>o=get_tangent(up,e);
		o.Y=(o.Y+SZ(dw)-1)%n;
		o=max(o,get_tangent(dw,e));
		return o.Y;	
	}
	int fd(P u,P v,int l,int r){
		int sl=sgn(det(v-u,A[l%n]-u)),md,sm;
		for(;l+1<r;){
			md=(l+r)>>1;sm=sgn(det(v-u,A[md%n]-u));
			if(sm==sl)l=md;else r=md;
		}
		return l%n;
	}
	bool intersection(P u,P v,int&v0,int&v1){//��͹����ֱ��uv�Ľ��㣬������ϸ��ཻ����0�����򷵻�(i,ne(i))�Ľ��� 
		int p0=get_tangent(u-v),p1=get_tangent(v-u);
		if(sgn(det(v-u,A[p0]-u))*sgn(det(v-u,A[p1]-u))<0){
			if(p0>p1)swap(p0,p1);
			v0=fd(u,v,p0,p1);
			v1=fd(u,v,p1,p0+n);
			return 1;
		}else return 0;
	}
};
