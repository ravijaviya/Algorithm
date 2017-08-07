#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
std::vector<unsigned int> set1;
std::vector<std::vector<unsigned int> > disjoint_set;
std::vector<unsigned int> dist;
std::vector<std::vector<unsigned int> > euclaDistance;
using namespace std;

int findCoordinates(int n,int coordinates[][2])
{
    int i=0;
    //srand((int) time(0));
    while(i < n) {
		 coordinates[i][0] = (rand()%500) + 1;
		 coordinates[i][1] = (rand()%500) + 1;
		 i++;
    }
    return coordinates[n][2];
}

bool compFunction(vector<unsigned int>& comp1,vector<unsigned int>& comp2)
{
    return(comp1[2]<comp2[2]);
}

void findEuclaDistance(int n,int coordinates[][2])
{
    unsigned int i,j,tempDist;
    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
    {
        //std::vector<int> dist;
        dist.clear();
        if(i!=j){
            tempDist=pow((coordinates[i][0]-coordinates[j][0]),2)+pow((coordinates[i][1]-coordinates[j][1]),2);
            tempDist=sqrt(tempDist);
            dist.push_back(i);
            dist.push_back(j);
            dist.push_back(tempDist);
            euclaDistance.push_back(dist);
        }
    }
     std::sort (euclaDistance.begin(), euclaDistance.end(), compFunction);

}
int union_find(int n,int mst[]){
    int i,j,x,y;

    for(i=0;i<n;i++)
    {
        set1.clear();
        set1.push_back(i);
        disjoint_set.push_back(set1);
        mst[i]=-1;
        //cout<<disjoint_set[i][0];
    }
    cout<<endl;
    j=n;
    for(i=0;i<euclaDistance.size();i++)
    {
        for(j=0;j<disjoint_set.size();j++){
            for(int k=0;k<disjoint_set[j].size();k++){
                //cout<<*tempx<<" "<<*tempy<<endl;
                if (disjoint_set[j][k]==euclaDistance[i][0]){
                    x = j;
                }
                if (disjoint_set[j][k]==euclaDistance[i][1]){
                    y = j;
                }
            }
        }
        //x= std::find(disjoint_set.begin(), disjoint_set.end(), euclaDistance[i][0]) disjoint_set.begin());
       // y= std::find(disjoint_set.begin(), disjoint_set.end(), euclaDistance[i][1]));
                   //cout<<euclaDistance[i][1]<<" "<<euclaDistance[i][0]<<endl;
                     //          cout<<x<<" "<<y<<endl;
        if(x!=y){
            disjoint_set[x].insert(disjoint_set[x].end(),disjoint_set[y].begin(),disjoint_set[y].end());
            disjoint_set.erase(disjoint_set.begin()+y);
            //cout<<euclaDistance[i][1]<<" "<<euclaDistance[i][0]<<endl;
            if(mst[euclaDistance[i][1]]== -1){
                mst[euclaDistance[i][1]]=euclaDistance[i][0];
                //cout<<mst[euclaDistance[i][1]]<<"\t"<<mst[euclaDistance[i][0]]<<endl;
            }
            else{
                mst[euclaDistance[i][0]]=euclaDistance[i][1];
                //cout<<mst[euclaDistance[i][1]]<<"\t"<<mst[euclaDistance[i][0]]<<endl;
            }
        }
        else if(x==y && disjoint_set.size()==1)
            break;
        else
            continue;
    }
    return mst[n];
}

void print_mst(int n,int mst[]){
    for(int i=0;i<n;i++){
        cout<<i<<"\t"<<mst[i]<<endl;
    }
}
int main()
{
    int n;
    //int mst[n];
    //int coordinates[n][2];
    cout<<"Please enter the number of vertices:";
    cin>>n;
    int mst[n];
    int coordinates[n][2];
    findCoordinates(n,coordinates);
    findEuclaDistance(n,coordinates);
    //for(int i=0;i<n;i++){
        //cout<<mst[i]<<"\t";
        //cout<<coordinates[i][0]<<" "<<coordinates[i][1]<<endl;
    //
    //cout<<endl;
    //cout<<"RAVI"<<endl;
    /*for (int i = 0; i < (n*(n-1)/2); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout <<euclaDistance[i][j]<<"\t";
        }
        cout<<endl;
    }*/
    union_find(n, mst);
    print_mst(n, mst);
    return 0;
}
