#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool removable(vector<int> neighbor, vector<int> cover);
int max_removable(vector<vector<int> > neighbors, vector<int> cover);
vector<int> procedure_1(vector<vector<int> > neighbors, vector<int> cover);
vector<int> procedure_2(vector<vector<int> > neighbors, vector<int> cover, int k);
int cover_size(vector<int> cover);
ifstream infile ("2371.txt");



bool removable(vector<int> neighbor, vector<int> cover)
{
 bool check=true;
 for(int i=0; i<neighbor.size(); i++)
 if(cover[neighbor[i]]==0)
 {
  check=false;
  break;
 }
 return check;
}

int max_removable(vector<vector<int> > neighbors, vector<int> cover)
{
 int r=-1, max=-1;
 for(int i=0; i<cover.size(); i++)
 {
  if(cover[i]==1 && removable(neighbors[i],cover)==true)
  {
   vector<int> temp_cover=cover;
   temp_cover[i]=0;
   int sum=0;
   for(int j=0; j<temp_cover.size(); j++)
   if(temp_cover[j]==1 && removable(neighbors[j], temp_cover)==true)
   sum++;
   if(sum>max)
   {
    max=sum;
    r=i;
   }
  }
 }
 return r;
}

vector<int> procedure_1(vector<vector<int> > neighbors, vector<int> cover)
{
 vector<int> temp_cover=cover;
 int r=0;
 while(r!=-1)
 {
  r= max_removable(neighbors,temp_cover);
  if(r!=-1) temp_cover[r]=0;
 }
 return temp_cover;
}

vector<int> procedure_2(vector<vector<int> > neighbors, vector<int> cover, int k)
{
 int count=0;
 vector<int> temp_cover=cover;
 int i=0;
 for(int i=0; i<temp_cover.size(); i++)
 {
  if(temp_cover[i]==1)
  {
   int sum=0, index;
   for(int j=0; j<neighbors[i].size(); j++)
   if(temp_cover[neighbors[i][j]]==0) {index=j; sum++;}
   if(sum==1 && cover[neighbors[i][index]]==0)
   {
    temp_cover[neighbors[i][index]]=1;
    temp_cover[i]=0;
    temp_cover=procedure_1(neighbors,temp_cover);
    count++;
   }
   if(count>k) break;
  }
 }
 return temp_cover;
}

int cover_size(vector<int> cover)
{
 int count=0;
 for(int i=0; i<cover.size(); i++)
 if(cover[i]==1) count++;
 return count;
}

int main()
{
 //Read Graph
 cout<<"Vertex Coloring Algorithm."<<endl;
 int C, N, n, i, j, k, K, p, q, r, s, min, edge, counter=0;
 infile>>N;
 vector< vector<int> > Graph;
 for(i=0; i<N; i++)
 {
  vector<int> row;
  for(j=0; j<N; j++)
  {
   infile>>edge;
   row.push_back(edge);
  }
  Graph.push_back(row);
 }
 //COLORING to INDEPENDENT SET conversion
 cout<<"Graph has N = "<<N<<" vertices."<<endl;
 cout<<"Find a vertex coloring using at most C colors. Enter C = ";
 cin>>C;
  //Complete garph on C verteices
  vector<vector<int> > KC;
  vector<int> row1;
  for(int i=0; i<C; i++) row1.push_back(1);
  for(int i=0; i<C; i++) KC.push_back(row1);
  for(int i=0; i<C; i++) KC[i][i]=0;
  unsigned int t, t_;
 
  t = clock();
  //Cartesian product of Graph and KC
  vector<vector<int> > graph;
  vector<int> rowind;
  for(int i=0; i<C*N; i++) rowind.push_back(0);
  for(int i=0; i<C*N; i++) graph.push_back(rowind);
  for(int i=0; i<C*N; i++)
  for(int j=0; j<C*N; j++)
  {
   int i_G=i/C, i_KC=i%C, j_G=j/C, j_KC=j%C;
   if((i_G==j_G) && (KC[i_KC][j_KC]==1)) graph[i][j]=1;
   if((Graph[i_G][j_G]==1) && (i_KC==j_KC)) graph[i][j]=1;
  }
  //Assign parameters for finding independent sets in the graph
  n=N*C; K=n/C; k=n-K;
 //Find Neighbors
 vector<vector<int> > neighbors;
 for(i=0; i<graph.size(); i++)
 {
  vector<int> neighbor;
  for(j=0; j<graph[i].size(); j++)
  if(graph[i][j]==1) neighbor.push_back(j);
  neighbors.push_back(neighbor);
 }

 //Find Independent Sets
 bool found=false;
 cout<<"Finding Vertex Colorings..."<<endl;
 min=n+1;
 vector<vector<int> > covers;
 vector<int> allcover;
 for(i=0; i<graph.size(); i++)
 allcover.push_back(1);
 for(i=0; i<allcover.size(); i++)
 {
  if(found) break;
  vector<int> cover=allcover;
  cover[i]=0;
  cover=procedure_1(neighbors,cover);
  s=cover_size(cover);
  if(s<min) min=s;

  for(j=0; j<n-k; j++)
  cover=procedure_2(neighbors,cover,j);
  s=cover_size(cover);

  covers.push_back(cover);
  if(s<=k){ found=true; break; }
 }
 t_ = clock();
//Pairwise Intersections
 for(p=0; p<covers.size(); p++)
 {
  if(found) break;
  for(q=p+1; q<covers.size(); q++)
  {
   if(found) break;
   vector<int> cover=allcover;
   for(r=0; r<cover.size(); r++)
   if(covers[p][r]==0 && covers[q][r]==0) cover[r]=0;
   cover=procedure_1(neighbors,cover);
   s=cover_size(cover);
   if(s<min) min=s;
   if(s<=k)
   {
    found=true;
    break;
   }
   for(j=0; j<k; j++)
   cover=procedure_2(neighbors,cover,j);
   s=cover_size(cover);
   if(s<min) min=s;
   cout<<"Vertex Coloring Size: "<<n-s<<endl;
   if(s<=k){ found=true; break; }
   }
 }
  
 
  double time = (double(t_ - t)/CLOCKS_PER_SEC);
  
 if(found){
   cout<<"Found  complete Vertex Coloring using at most "<<C<<" colors."<<endl;
   cout << "Execution Time: " << time << endl;
 }
 else cout<<"Could not find complete Vertex Coloring using at most "<<C<<" colors."<<endl
 <<"Maximum partial Vertex Coloring found for "<<n-min<<" vertices."<<endl;
 return 0;
}
//codigo con algunas modificaciones de The Vertex Coloring Algorithm - Ashay Dharwadker

