#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <graphics.h>
#include <winbgim.h>
using namespace std;
void print_pyr(vector<vector<int> > a,int n)
{
    int i=0;
    int l,r,h;
    for(i=0;i<n;i++)
    {
        l=a[i][0];
        r=a[i][1];
        h=a[i][2];
        //mid=(l+r)/2;
        rectangle(l+10,200-h,r+10,200);
        //line(mid,200-h,r,200);
     }
	 line(10,200,900,200);
}
void print_output(vector<pair<float,float> > s)
{
	vector<pair<float,float> >::iterator i=s.begin();
	float x1,x2,y1,x21,y21,y22;
	for(;i<s.end();)
	{
		x1=i->first;
		y1=i->second;
		i++;
		x2=i->first;
		x21=i->first;
		y21=y1;
		y22=i->second;	  
		//line(10,200,900,200);
		line(x1+10,400-y1,x2+10,400-y1);
		line(x21+10,400-y21,x21+10,400-y22);   

	}
	line(10,400,900,400);
}
vector <pair<float,float> > skyline(vector<vector<int> > a,int i,int n);
vector <pair<float,float> > mergesky(vector<pair<float,float> > left,vector<pair<float,float> > right);
vector<pair<float, float> > cleanH(vector<pair<float, float> > re);
vector<pair<float, float> > cleanP(vector<pair<float, float> > re);

int main(){
    int i,j,n;
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    cout<<"Enter number of building: ";
    cin>>n;
    vector<vector<int> > a;//={{1,5, 11}, {1,7, 6}, {3,9, 13},{3, 16,7}, {14, 25,3}, {16, 22,18},{14, 29,13}, {24, 28,4}};
    vector<int> temp;
    a.clear();
    cout<<"The random buildings are:"<<endl;
    for(i=0;i<n;i++){

            temp.clear();
            int x,y;
            x = (rand()%500)+1;
            y = x+(rand()%100)+1;
            if(x<y){
                temp.push_back(x);
                temp.push_back(y);
            }else{
                temp.push_back(y);
                temp.push_back(x);
            }
            temp.push_back(rand()%50+1);
            a.push_back(temp);
        cout<<a[i][0]<<" "<<a[i][1]<<" "<<a[i][2]<<endl;
    }
    print_pyr(a,n);
    vector<pair<float, float> > res = skyline(a,0,n-1);
    res = cleanH(res);
    res = cleanP(res);
    cout<<endl<<"The skyline for given buildings is:"<<endl;
    res.insert(res.begin(),make_pair(0,0));
	for(vector<pair<float, float> >::iterator i=res.begin();i<res.end();i++){
        cout<<'('<<i->first<<','<<i->second<<')';
    }
	print_output(res);
    getch();
    closegraph();
    return 0;
}
vector<pair<float, float> > cleanH(vector<pair<float, float> > re){
    for(vector<pair<float, float> >::iterator i=re.begin();i<re.end()-1;i++){
        vector<pair<float, float> >::iterator j=i+1;
        if(i->second == j->second){
            re.erase(j);
            i--;
        }
    }
    return re;
}
vector<pair<float, float> > cleanP(vector<pair<float, float> > re){
    for(vector<pair<float, float> >::iterator i=re.begin();i<re.end()-1;i++){
        vector<pair<float, float> >::iterator j=i+1;
        if(i->first == j->first){
            if(i->second>j->second)
                re.erase(j);
            else
                re.erase(i);
            i--;
        }
    }
    return re;
}
vector <pair<float,float> > skyline(vector<vector<int> > a,int i,int n){
    if(i==n){
        vector <pair<float, float> > res;
        res.clear();
        res.push_back(make_pair(a[i][0],a[i][2]));
        res.push_back(make_pair(a[i][1],0));
        return res;
    }
    float mid = (i+n)/2;
    vector <pair<float, float> > left = skyline(a,i,mid);
    vector <pair<float, float> > right = skyline(a,mid+1,n);
    vector <pair<float, float> > res = mergesky(left,right);

    return res;
}
vector <pair<float,float> > mergesky(vector <pair<float, float> > left,vector <pair<float, float> > right){
    vector <pair<float, float> > res ;
    float h1,h2;
    h1=h2=0;
    vector<pair<float, float> >::iterator i=left.begin();
    vector<pair<float, float> >::iterator j=right.begin();
    while(i<left.end() && j<right.end()){
        if(i->first<j->first){
            float x1 = i->first;
            h1 = i->second;
            float maxh = max(h1,h2);
            res.push_back(make_pair(x1,maxh));
            i++;
        }else{
            float x2 = j->first;
            h2 = j->second;
            float maxh = max(h1,h2);
            res.push_back(make_pair(x2,maxh));
            j++;
        }
    }
    while(i<left.end()){
        res.push_back(make_pair(i->first,i->second));
        i++;
    }
    while(j<right.end()){
        res.push_back(make_pair(j->first,j->second));
        j++;
    }
    return res;
}

