#include "submission.cpp"

void printResult(vector<vector<int>> m, int num)
{
    cout<<"test " << num<<": "<<endl;
    tuple<vector<vector<int>>, vector<int>, int> result = myBranchBound(m);
    for(int i=0; i<get<0>(result).size(); i++)
    {
        for(int j=0; j<get<0>(result)[0].size(); j++)
            cout << get<0>(result)[i][j] << ",";

        cout << endl;
    }
    cout << endl;
    for(int i=0; i<get<1>(result).size(); i++)
    {
        cout << get<1>(result)[i] << ",";
    }

    cout << endl;
    cout << get<2>(result) <<endl;

    cout << endl;
};

int main()
{
    cout << "Question 1: " << endl;
    vector<vector<int>> curr = {
        {1,2,3},
        {4,13,12},
        {2,41,21}
        };
    printResult(curr, 1);
    cout << endl;

    curr = {
        {12, 1234},
        {4,10000},
        };
    printResult(curr, 2);
    cout << endl;

curr = {
        {6,4,2,5},
        {2,1,5,4},
        {4,2,1,3},
        {5,3,3,2}
        };
    printResult(curr, 3);
    cout << endl;

    curr = {
        {1, 2, 3, 4, 5},
        {10, 9, 8, 7, 6},
        {15, 14, 13, 12, 11},
        {20, 19, 18, 17, 16},
        {25, 24, 23, 22, 21}
        };
    printResult(curr, 4);
    cout << endl;

    curr = {
        {1, 2, 12, 3, 4, 5},
        {10, 9, 8, 23, 7, 6},
        {15, 14, 13, 12, 32, 11},
        {20, 19, 18, 17, 13, 16},
        {25, 24, 23, 22, 21, 2},
        {25, 24, 2, 21, 4, 22}
        };
    printResult(curr, 5);
    cout << endl;

    curr = {
        {1, 2, 12, 3, 4, 32, 21},
        {10, 9, 8, 23, 7, 6, 23},
        {15, 14, 13, 12, 32, 12, 11},
        {20, 19, 18, 17, 13, 16, 43},
        {25, 24, 23, 12, 22, 21, 2},
        {25, 24, 2, 21, 2, 4, 22},
        {15, 14, 14, 12, 32, 42, 11}
        };
    printResult(curr, 6);
    cout << endl;

    curr = {
        {1, 42, 21, 12, 33, 4, 32, 21},
        {10, 29, 33, 18, 23, 7, 6, 23},
        {15, 33, 14, 13, 12, 32, 12, 11},
        {43, 20, 19, 18, 17, 13, 16, 43},
        {22, 5, 24, 23, 12, 22, 21, 2},
        {25, 24, 2, 70, 21, 2, 4, 22},
        {15, 14, 23, 14, 12, 32, 42, 11},
        {43, 28, 29, 68, 37, 43, 26, 43}
        };
    printResult(curr, 7);
    cout << endl;

    curr = {
        {41, 42, 21, 12, 34, 33, 24, 32, 21},
        {10, 29, 33, 18, 23, 72, 64, 45, 23},
        {15, 33, 14, 13, 12, 32, 43, 12, 11},
        {43, 20, 19, 18, 17, 13, 34, 126, 43},
        {22, 5, 24, 23, 23, 12, 22, 21, 2},
        {25, 24, 22, 34, 70, 21, 23, 42, 22},
        {15, 67, 104, 23, 14, 12, 32, 42, 11},
        {43, 28, 34, 29, 68, 37, 43, 26, 43},
        {43, 120, 19, 18, 17, 123, 34, 126, 43},
        };
    printResult(curr, 8);
    cout << endl;
    
    cout << endl;
    // cout << "Question 2: " <<endl;
    // int v[] = {3,4,5,8,10};
    // int w[] = {2,3,4,5,9};
    // cout << endl;
    // vector<int> Z = myBitmask(5, 11, v, w);
    // for(int i=0; i<Z.size(); i++)
    // {
    //     cout << Z[i] << ",";
    // }
    // cout << endl;

    system("pause");
    return 0;
}