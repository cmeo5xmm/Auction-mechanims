#include <iostream>
#include <utility> 
#include <vector>
#include <cmath>
#include "memory.h"

using namespace std;
int zzz=5;	//bidder numbers
vector<double> info[5];	//bid,things	//bidder numbers	
vector<double> sort[5];	//bidder,bid,wantwhat,b/s
int k=0;
int j=0;

int main() {
	int num,x;		//num thingnumbers   x bid
	int i,b,c,d;	//c wantthings	d wanthowmany	
	int tr;
	
	cout<<"enter the item numbers:";
	cin>>num;
	vector<int> winner;			

	for(i=0;i<zzz;i++){											
		cout<<"enter the P"<<i+1<<"'s bid :";
		cin>>x;
		cout<<"how many things P"<<i+1<<" want :";
		cin>>d;
		info[i].push_back(d);
		info[i].push_back(x);
		cout<<"enter the things :";
		for(b=0;b<d;b++){
			cin>>c;
			info[i].push_back(c);
		}
		info[i].push_back(info[i][1]/d); 
	}
	

	
	int check=0,temp=0;
	int thing[num];
	memset(thing,0,sizeof(thing));
	while(temp<zzz){
		int max=-1,flag; //find max bid
		for(i=0;i<zzz;++i){
			vector<double>:: iterator iter = info[i].end()-1;
			if(*iter>max){
				max=*iter;
				flag=i;
			}
		}
		

		int br=0;
		vector<double>:: iterator it = info[flag].begin()+1;
		it++;
		for(j=0;it!=info[flag].end()-1;it++,j++){
			tr = static_cast<int>(*it);
			if(thing[tr-1]==1) br=1;	//有交集 
		}
		
		vector<double>:: iterator itt = info[flag].begin()+1;
		itt++;
		for(j=0;itt!=info[flag].end()-1;itt++,j++){
			if(br==1) break;
			tr = static_cast<int>(*itt);
			thing[tr-1]=1;
		}
		if(br==0){
			winner.push_back(flag+1);
		}
		
		if(max!=0){
			sort[temp].assign(info[flag].begin()+2,info[flag].end()); 	//sort
			sort[temp].insert(sort[temp].begin(),flag+1);
			temp++;
			vector<double>:: iterator iter = info[flag].end()-1;
			*iter=0;
		}
		
	}

	/*  //print sort
	for(i=0;i<zzz;++i){		 
		vector<double>:: iterator iter = sort[i].begin();
		for(x=0;iter!= sort[i].end();iter++,x++){
			cout<<*iter<<" ";
		}
		cout<<endl;
	}
   */
	vector<int>:: iterator iter = winner.begin();
	double winnerprice;
	cout<<"the winner are:"<<endl;
	
	int things[num];	//check不是被前面的贏家阻擋 
	memset(things,0,sizeof(things));
	for(x=0;iter!= winner.end();iter++,x++){		//iter=winner
		cout<<"P"<<*iter<<" and payoff is :";
		
		memset(thing,0,sizeof(thing));
		vector<double>:: iterator itt = info[*iter-1].begin()+1;
		itt++;
		for(j=0;itt!=info[*iter-1].end()-1;itt++,j++){
			tr = static_cast<int>(*itt);
			thing[tr-1]=1;
		}
		
		for(i=0;i<zzz;++i){		//find winner price
			vector<double>:: iterator find = sort[i].begin();
			if(*find==*iter){
				vector<double>:: iterator wprice=sort[i].end()-1;
				winnerprice=*wprice;
			}
		}
		
		int al=0;
		int q=0;
		for(i=0;i<zzz;++i){		//find Vc
			q=0;
			vector<double>:: iterator it = sort[i].begin();
			vector<double>:: iterator itprice = sort[i].end()-1;
			if(*it!=*iter && *itprice<winnerprice){	//not winner
				it++;
				for(x=0;it!= sort[i].end()-1;it++,x++){		//check不是被前面的贏家阻擋 
					tr = static_cast<int>(*it);
					if(things[tr-1]==1){
						q=1;
						break;
					}
				}
				if(q==0){
					it = sort[i].begin();
					for(x=0;it!= sort[i].end()-1;it++,x++){
						tr = static_cast<int>(*it);
						if(thing[tr-1]==1){
							vector<double>:: iterator pay = sort[i].end()-1;
							vector<double>:: iterator howmany = info[*iter-1].begin();
							cout<<((*pay)*(*howmany));
							al=1;	//finded
							break;
						}
					}
				}
				
				if(al==1) break;
			}else if(i==zzz-1) cout<<0;
		}
		cout<<endl;
		
		vector<double>:: iterator ittt = info[*iter-1].begin()+1;
		ittt++;
		for(j=0;ittt!=info[*iter-1].end()-1;ittt++,j++){
			tr = static_cast<int>(*ittt);
			things[tr-1]=1;
		}

	}
	
	return 0;
} 
