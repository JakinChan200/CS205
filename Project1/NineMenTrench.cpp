#include <bits/stdc++.h>

using namespace std;


// vector<vector<int>> start = {{-1, -1, -1, 0, -1, 0, -1, 0, -1, -1},
//                             {0, 2, 3, 4, 5, 6, 7, 8, 9, 1}};

vector<vector<int>> start = {{-1, -1, -1, 0, -1, 8, -1, 0, -1, -1},
                            {1, 2, 3, 4, 5, 6, 7, 0, 9, 0}};
struct node{
    vector<vector<int>> state;
    int h = 0;
    bool isSolution = false;
    vector<string> path;
};

struct Compare{
    bool operator()(node &a, node &b){
        //return a.path.size() + a.h > b.path.size() + b.h;
        return a.h + a.path.size() != b.h + b.path.size() ? a.h + a.path.size() > b.h + b.path.size() : a.path.size() > b.path.size(); 
    }
};

void printState(vector<vector<int>> state){
    for(int i = 0; i < state.size(); i++){
        for(int k = 0; k < state[i].size(); k++){
            if(state[i][k] < 0){
                cout << "   ";
            }else{
                cout << "  " << state[i][k];
            }
        }
        cout << endl;
    }
    return;
}

bool isDupe(node &trial, set<vector<vector<int>>> &dupeStash){
    int dupeStashSize = dupeStash.size();
    dupeStash.insert(trial.state);
    return dupeStashSize == dupeStash.size();
}

bool checkCorrectness(node &trial, int algo){
    trial.h = 0;
    for(int i = 0; i < trial.state.size(); i++){
        for(int j = 0; j < trial.state[i].size(); j++){
            if(trial.state[i][j] != -1 && trial.state[i][j] != 0){

                if(i == 1 && j == trial.state[i][j]-1){
                    continue;
                }

                switch(algo){
                    case 3:
                        trial.h += (1-i) + abs(j-(trial.state[i][j]-1));
                        break;
                    case 2:
                        trial.h++;
                        break;
                    default:
                        return false;
                        break;
                }
            }
        }
    }
    if(trial.h == 0){
        trial.isSolution = true;
    }
    return trial.h == 0;
}

void movePerson(node &trial, int startPosX, int startPosY, int endPosX, int endPosY, string step){
    trial.state[endPosX][endPosY] = trial.state[startPosX][startPosY];
    trial.state[startPosX][startPosY] = 0;
    trial.path.push_back(step);
}

node algorithmn(node &startingState, int algo){

    int numNodesExpanded = 0;
    set<vector<vector<int>>> duplicates;
    node currentNode;

    priority_queue<node, vector<node>, Compare> tree;
    tree.push(startingState);
    if(checkCorrectness(startingState, algo)){return startingState;}


    while(!tree.empty()){
        currentNode = tree.top();
        tree.pop();
        numNodesExpanded++;

        // printState(currentNode.state);
        // cout << endl;
       // cout << duplicates.size();
        string step = "";

        //Checking the upper level
        for(int i = 0; i < currentNode.state[0].size(); i++){
            if(currentNode.state[0][i] == 0){
                if(currentNode.state[1][i] == 0){ continue;}
                node temp = currentNode;

                step = to_string(currentNode.state[1][i]) + " Up\n"; 
                movePerson(temp, 1, i, 0, i, step);
                if(!isDupe(temp, duplicates)){
                    if(checkCorrectness(temp, algo)){
                        return temp;
                    }else{
                        tree.push(temp);
                    }
                }
            }
        }

        //Checking the Lower Level
        for(int i = 0; i < currentNode.state[1].size(); i++){
            if(currentNode.state[1][i] == 0){
                if(i != 0){
                    if(currentNode.state[1][i-1] != 0){
                        node temp = currentNode;

                        step = to_string(currentNode.state[1][i-1]) + " Right\n"; 
                        movePerson(temp, 1, i-1, 1, i, step);
                        if(!isDupe(temp, duplicates)){
                            if(checkCorrectness(temp, algo)){
                                return temp;
                            }else{
                                tree.push(temp);
                            }
                        }
                    }
                }

                if(currentNode.state[0][i] > 0){
                    node temp = currentNode;

                    step = to_string(currentNode.state[0][i]) + " Down\n"; 
                    movePerson(temp, 0, i, 1, i, step);
                    if(!isDupe(temp, duplicates)){
                        if(checkCorrectness(temp, algo)){
                            return temp;
                        }else{
                            tree.push(temp);
                        }
                    }
                }

                if(i != currentNode.state[1].size()-1){
                    if(currentNode.state[1][i+1] != 0){
                        node temp = currentNode;

                        step = to_string(currentNode.state[1][i+1]) + " Left\n"; 
                        movePerson(temp, 1, i+1, 1, i, step);
                        if(!isDupe(temp, duplicates)){
                            if(checkCorrectness(temp, algo)){
                                return temp;
                            }else{
                                tree.push(temp);
                            }
                        }
                    }
                }
            }
        }

    }

    return currentNode;
}

int main(int argc, char** argv){
    int algo = 0;

    while(algo < 1 || algo > 3){
        cout << "1: for Uniform Cost Search\n2: for A* Misplaced Tile Heuristic \n3: for A* Manhattan Distance" << endl;
        cin >> algo;
    }

    node startingState;
    startingState.state = start;
    bool correct = checkCorrectness(startingState, algo);

    cout << "Correctness: " << correct << endl;
    cout << "h: " << startingState.h << endl;
    printState(startingState.state);

    node answer = algorithmn(startingState, algo);
    if(answer.isSolution){
        cout << "Solution Found!" << endl;
        for(int i = 0; i < answer.path.size(); i++){
            cout << answer.path[i];
        }
    }else{
        cout << "Solution Not Found!" << endl;
    }

    return 0;
}


/*
algo 1
uniform cost search

algo 2
A* with misplaced tile heuristic

algo 3
A* with manhattan distance

node = trial
state
*/