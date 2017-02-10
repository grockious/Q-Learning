#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//*** External functions ***//
//*** Function#1 ***//
int** neigh (int ind_m, int ind_n, int *current_state){
    vector<int> neigh_temp_1={current_state[0]};
    vector<int> neigh_temp_2={current_state[1]};
    if (current_state[0]!=1){
        neigh_temp_1.push_back(current_state[0]-1);
        neigh_temp_2.push_back(current_state[1]);
    }
    if (current_state[1]!=1){
        neigh_temp_1.push_back(current_state[0]);
        neigh_temp_2.push_back(current_state[1]-1);
    }
    if (current_state[0]+1<=ind_m){
        neigh_temp_1.push_back(current_state[0]+1);
        neigh_temp_2.push_back(current_state[1]);
    }
    if (current_state[1]+1<=ind_n){
        neigh_temp_1.push_back(current_state[0]);
        neigh_temp_2.push_back(current_state[1]+1);
    }
    int** N= new int*[2];
    N[0] = new int[neigh_temp_1.size()];
    N[1] = new int[neigh_temp_1.size()];
    copy(neigh_temp_1.begin(), neigh_temp_1.end(), N[0]);
    copy(neigh_temp_2.begin(), neigh_temp_2.end(), N[1]);
    return N;
}
//*** End of function#1 ***//
//*** End of external functions ***//

int main() {
    
    //*** Initialization ***//
    int m=40;
    int n=40;
    srand (time(NULL));
    
    float r[m][n];
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            r[i][j]=-100;
        }
    }
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            r[i][j]=100;
        }
    }
    
    float Q[m][n];
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            Q[i][j]=0;
        }
    }
    
    float discount_factor=0.8;
    float alpha=0.99;
    //*** End of initialization ***//
    
    //*** Main function ***//
    for (int run_num=1;run_num<2001;run_num++){
        int current_state[2]={39,39};
        auto current_path = new int[2001][2][2001];
        current_path[run_num][0][0]=current_state[0];
        current_path[run_num][1][0]=current_state[1];
        for (int it_num=1;it_num<2001;it_num++){
            int** neighbors;
            int neighbors_size;
            neighbors=neigh(m-1,n-1,current_state);
            neighbors_size=sizeof(neighbors[0])/sizeof(neighbors[0][0])+1;
            vector<int> available_Qs;
            for (int i=0;i<neighbors_size;i++){
                available_Qs.push_back(Q[neighbors[0][i]][neighbors[1][i]]);
            }
            vector<pair<int,int>> Qs_and_index(available_Qs.size());
            for (int i=0;i<available_Qs.size();++i){
                Qs_and_index[i]=make_pair(available_Qs[i],i);
            }
            random_shuffle(Qs_and_index.begin(),Qs_and_index.end());
            sort (Qs_and_index.begin(),Qs_and_index.end(),[](const pair<int,int>& l,
            const pair<int,int>& r){return l.first>r.first;});
            int row_with_max_Q=Qs_and_index[0].second;
            Q[current_state[0]][current_state[1]]=
            (1-alpha)*Q[current_state[0]][current_state[1]]+
            alpha*(r[current_state[0]][current_state[1]]+
            discount_factor*Qs_and_index[0].first);
            current_state[0]=neighbors[0][row_with_max_Q];
            current_state[1]=neighbors[1][row_with_max_Q];
            current_path[run_num][0][it_num]=current_state[0];
            current_path[run_num][1][it_num]=current_state[1];
        }
    }
    //*** End of main function ***//
}
