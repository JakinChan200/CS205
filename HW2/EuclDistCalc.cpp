#include <bits/stdc++.h>

using namespace std;

vector<vector<double>> rgbValues = {{65, 105, 225},
                                    {0, 255, 0},
                                    {255, 165, 0},
                                    {233, 150, 122},
                                    {153, 50, 204}};

vector<string> colors = {"RoyalBlue", "Lime", "Orange", "DarkSalmon", "DarkOrchid"};

int main(int argc, char* argv[]){
    for(int i = 0; i < rgbValues.size(); i++){
        for(int j = i+1; j < rgbValues.size(); j++){
            cout << "Distance between " << colors[i] << " and " << colors[j] << " is " << sqrt(pow(rgbValues[i][0] - rgbValues[j][0], 2) + pow(rgbValues[i][1] - rgbValues[j][1], 2) + pow(rgbValues[i][2] - rgbValues[j][2], 2)) << endl;
        }
    }
    return 0;
}