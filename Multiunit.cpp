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
	int num,x;		//num types of goods   
	int i,b,c,d;	//c wantthings	d wanthowmany	
	int tr;
	int want[zzz];
	vector<int> winner;	
	vector<int> stemp;
		
	cout<<"how many types of goods ?"<<endl;
	cin>>num;
	int thing[num];		
	int thingg[num];
	int thinggg[num];
	
	cout<<"enter the number of each good :"<<endl;
	for(i=0;i<num;i++){
		cin>>x;
		thing[i]=x;
	}
			

	for(i=0;i<zzz;i++){											
		d=0;
		cout<<"enter the P"<<i+1<<"'s bid :"<<endl;
		cin>>x;
		info[i].push_back(x);
		cout<<"enter how many number does P"<<i+1<<" want for each good :"<<endl;
		for(b=0;b<num;b++){
			cin>>c;
			info[i].push_back(c);
			d+=c;
		}
		info[i].push_back(info[i][0]/d); 
		want[i]=d;
	}
	

	memcpy(thingg,thing,sizeof(thing));
	memcpy(thinggg,thing,sizeof(thing));
	int check=0,temp=0;
	
	while(temp<zzz){	//sort
		int flag; //find max bid
		double max=-1;
		for(i=0;i<zzz;++i){
			vector<double>:: iterator iter = info[i].end()-1;
			if(info[i]>max){
				max=*iter;
				flag=i;
			}
		}	
		sort[temp].assign(info[flag].begin()+1,info[flag].end()); 	//sort
		sort[temp].insert(sort[temp].begin(),flag+1);
		temp++;
		vector<double>:: iterator iter = info[flag].end()-1;
		*iter=0;
		
	}
	
	int br=0,bl=0;
	for(temp=0;temp<zzz;temp++){	//find winner
		br=0;
		vector<double>:: iterator iter = sort[temp].begin()+1;
		for(j=0;iter!=sort[temp].end()-1;iter++,j++){
			tr = static_cast<int>(*iter);
			if(thing[j]-tr<0) {
				br=1;	//not winner
				break;	
			}
		}
		if(br==0){
			iter = sort[temp].begin();
			stemp.push_back(temp);
			winner.push_back(*iter);
			iter++;
			for(j=0;iter!=sort[temp].end()-1;iter++,j++){
				tr = static_cast<int>(*iter);
				thing[j]=thing[j]-tr;
			}
		}
		
	}
	
	memcpy(thing,thingg,sizeof(thingg));
	cout<<"the winner are:"<<endl;
	vector<int>:: iterator iter = winner.begin();	//iter=winner
	vector<int>:: iterator ite = stemp.begin();
	
	for(x=0;iter!= winner.end();iter++,ite++,x++){
		cout<<"P"<<*iter<<" and payoff is :";
		br=0;
		bl=0;
		memcpy(thinggg,thingg,sizeof(thingg));
		vector<double>:: iterator itt = sort[*ite].begin()+1;
		for(j=0;itt!=sort[*ite].end()-1;itt++,j++){
			tr = static_cast<int>(*itt);
			thingg[j]=thingg[j]-tr;
		}

		for(j=(*ite)+1;j<zzz;j++){
			vector<double>:: iterator it = sort[j].begin()+1;
			for(x=0;it!=sort[j].end()-1;it++,x++){
				tr = static_cast<int>(*it);
				if(thing[x]-tr<0) {	//not blocked by this winner
					bl=1;	
					break;	
				}
			}
			
			if(bl==0){
				it = sort[j].begin()+1;
				for(x=0;it!=sort[j].end()-1;it++,x++){	//檢查是不是被其他WINNER擋 
					tr = static_cast<int>(*it);
					if(thinggg[x]-tr <0){
						br=2;
						break;
					}
				}
				if(br!=2){
					it = sort[j].begin()+1;
					for(x=0;it!=sort[j].end()-1;it++,x++){
						tr = static_cast<int>(*it);
						thinggg[x]=thinggg[x]-tr;
					}
					it = sort[j].begin()+1;
					for(x=0;it!=sort[j].end()-1;it++,x++){
						tr = static_cast<int>(*it);
						if(thingg[x]-tr<0) {	//blocked by this winner
							br=1;	
							break;	
						}
					}
					if(br==1){
						c=want[*iter-1];
						it = sort[j].end()-1;
						cout<<(*it)*(c)<<endl;
						break;
					}
				}
			}
		}
		if(br==0 || br==2) cout<<0<<endl;
		
		itt = sort[*ite].begin()+1;
		for(j=0;itt!=sort[*ite].end()-1;itt++,j++){
			tr = static_cast<int>(*itt);
			thing[j]=thing[j]-tr;
		}
	}	

	return 0;
} 

