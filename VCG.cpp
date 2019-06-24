#include <iostream>
#include <utility> 
#include <vector>
#include <cmath>
#include "memory.h"

using namespace std;
int zzz=3;	//bidder numbers
vector<int> info[3];	//bid,things	//bidder numbers			
int k=0;
int j=0;

void set(vector<vector<int> > &a,int *tag,int n,int num){

	if(n==zzz){				
		int i=0;
		int br=0;
		int thing[num];
		memset(thing,0,sizeof(thing));
		for(i=0;i<zzz;i++){
			if(tag[i]==1){
				vector<int>:: iterator iter = info[i].begin();
				iter++;
				for(j=0;iter!=info[i].end();iter++,j++){
					if(thing[*iter-1]==1) br=1;	//有交集 
				}
				
				vector<int>:: iterator it = info[i].begin();
				it++;
				for(j=0;it!=info[i].end();it++,j++){
					if(br==1) break;
					thing[*it-1]=1;
				}
			}
		}
		for(i=0;i<zzz;i++){												
			if(br==1) break;
			if(tag[i]==1){
				a[k][0]+=info[i][0];
				a[k].push_back(i+1);
			}
		}
		
		if(br==0) k++;
		return;
	}
	
	tag[n]=0;
	set(a,tag,n+1,num);
	tag[n]=1;
	set(a,tag,n+1,num);
}

int main() {
	int num,x;		//num thingnumbers   x bid
	int i,b,c,d;	//c wantthings	d wanthowmany	
	
	cout<<"enter the item numbers:";
	cin>>num;
	vector<vector<int> > a(pow(2.0,zzz),vector<int>(1));	//bid,bidder..				

	for(i=0;i<zzz;i++){											
		cout<<"enter the P"<<i+1<<"'s bid :";
		cin>>x;
		info[i].push_back(x);
		cout<<"how many things P"<<i+1<<" want :";
		cin>>d;
		cout<<"enter the things :";
		for(b=0;b<d;b++){
			cin>>c;
			info[i].push_back(c);
		}
	}
	
	int tag[zzz];		//combinations	000,001,010... 									
	set(a,tag,0,num);
	cout<<endl;

	/*for(i=1;i<k;++i){		Possible Results 
		vector<int>:: iterator iter = a[i].begin();
		for(x=0;iter!= a[i].end();iter++,x++){
			cout<<*iter<<" ";
		}
		cout<<endl;
	}*/
	
	int max=0,flag; //find max bid
	for(i=0;i<k;++i){
		if(a[i][0]>max){
			max=a[i][0];
			flag=i;
		}
	}
	
	cout<<"the winner are:"<<endl;
	vector<int>:: iterator ir = a[flag].begin();
	ir++;
	for(x=0;ir!= a[flag].end();ir++,x++){
		cout<<"P"<<*ir<<" and payoff is :";
		
		int mmax=0,ch;	//找扣掉自己後其他人的最大利益 
		for(i=0;i<k;++i){
			ch=0;
			vector<int>:: iterator t = a[i].begin();
			t++;
			for(x=0;t!=a[i].end();x++,t++){
				if(*t==*ir){
					ch=1;
					break;
				}
			}
			if(ch==0){
				if(a[i][0]>mmax){
					mmax=a[i][0];
				}
			}
		}
		
		int payoff=mmax-max+info[*ir-1][0]; 
		cout<<payoff<<endl;
	}
	
	return 0;
} 
