#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

#define N 100010
typedef long long ll;

struct Node{
	ll l;
	ll r;
	ll sum;
	ll add;
	Node(){
		sum=0;
		add=0;
	}
}a[N*4];

void build(int u,int le,int ri){
	a[u].l=le;
	a[u].r=ri;
	a[u].sum=0;
	if(le==ri) return;
	int mid=(le+ri)>>1;
	build(u<<1,le,mid);
	build(u<<1|1,mid+1,ri);
}

void spread(int u){
	if(a[u].add){
		a[u<<1].add+=a[u].add;
		a[u<<1|1].add+=a[u].add;
		a[u<<1].sum+=(a[u<<1].r-a[u<<1].l+1)*a[u].add;
		a[u<<1|1].sum+=(a[u<<1|1].r-a[u<<1|1].l+1)*a[u].add;
		a[u].add=0;
	}
}


ll query(int u,int le,int ri){
	if(le<=a[u].l&&ri>=a[u].r){
		return a[u].sum;
	}
	spread(u);
	int mid=(a[u].l+a[u].r)>>1;
	if(mid>=ri) return query(u<<1,le,ri);
	else if(mid+1<=le) return query(u<<1|1,le,ri);
	else return query(u<<1,le,mid)+query(u<<1|1,mid+1,ri);
}

void modify(int u,int le,int ri,int k){
	if(le<=a[u].l&&ri>=a[u].r){
		a[u].sum+=k;
		a[u].add+=k;
		return;
	}
	spread(u);
	int mid=(a[u].l+a[u].r)>>1;
	if(mid>=ri) modify(u<<1,le,ri,k);
	else if(mid+1<=le) modify(u<<1|1,le,ri,k);
	else{
		modify(u<<1,le,mid,k);
		modify(u<<1|1,mid+1,ri,k);
	}
	a[u].sum=a[u<<1].sum+a[u<<1|1].sum;
}



int main()
{
	int n,m,k,a,b;
	//cin>>n>>m;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i=1;i<=m;++i){
		//cin>>k>>a>>b;
		scanf("%d%d%d",&k,&a,&b);
		//cout<<k<<" "<<a<<" "<<b<<endl;
		if(k){//²éÑ¯ 
		ll ans=query(1,min(a,b),max(a,b));
			printf("%lld\n",ans);
		}
		else{
			modify(1,a,a,b);
		}
	}
	return 0;

}
