#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

// Name: Xiangyi Lin

///////////////////////////////////////////////////////
/////////////       QUESTION 1 HELPER   ///////////////
///////////////////////////////////////////////////////

/**
 * a structure to implements the operator of priotity
 */
struct Compare 
{
    /**
     * check if the value in tuple is greater than another value in tuple
     * use in the priotity queue compare function
     * 
     * @param v1,v2, first integer in tuple is the value, 
     *               second integer in tuple is the row index of the value in matrix,
     *               third integer in tuple is the colunm index of the value in matrix 
     * @return true if the first value in tuple v1 is greater than first value in tuple v2, otherwise return false
     */
    bool operator() (tuple<int, int, int> v1, tuple<int, int, int> v2)
    {
        // return true if v1 order before v2
        if(get<0>(v1) > get<0>(v2))
          return true;
        else if(get<0>(v1) < get<0>(v2))
          return false;
        else if(get<0>(v1) == get<0>(v2) && get<1>(v1) > get<1>(v2))
          return true;
        else if(get<0>(v1) == get<0>(v2) && get<1>(v1) == get<1>(v2) && get<2>(v1) > get<2>(v2))
          return true;

        return false;
    }
};

/**
 * calculates upper bound at node X
 * 
 * @param A, (N x N) Matrix with c_ij representing the time taken by agent i to complete task j
 * @param X, location of c_ij that already picked, for example X[0]=1 means row 0 column 1 already pick.
 * @return tuple with minimum element location which the value in index i is the column and the i is row
 * @return tuple with integer number of upper bound
 */
tuple<vector<int>, int> upper_bound(vector<vector<int>> A, vector<int> X)
{
    vector<int> currLocation(A.size(), 0);
    set<int> rowExist, colExist;
    int up = 0;
    //calculate the current sum and save the row and column
    for(int i=0; i<X.size(); i++)
    {
        currLocation[i] = X[i];
        colExist.insert(X[i]);
        up += A[i][X[i]];
    }

    //create priority queue by rule Compare
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, Compare> minpq;

    //travel all element that not in the same row and column with require element in matrix and push the value to minpq
    for(int i=X.size(); i<A.size(); i++)
    {
        for(int j=0; j<A[0].size(); j++)
        {
            if(colExist.find(j)==colExist.end())
            //if the j is not find in the colExist
            {
                tuple<int, int, int> tempValue(make_tuple(A[i][j], i, j));
                minpq.push(tempValue);
            }
        }
    }

    int minFound = X.size();

    //find the A.size() minimum value
    while(minFound<A.size() && !minpq.empty())
    {
        if(rowExist.find(get<1>(minpq.top()))==rowExist.end() && colExist.find(get<2>(minpq.top()))==colExist.end())
        //make sure the minimum value is not in the same row and column with before
        {
            //add the value to the up and save the row and column
            up += get<0>(minpq.top());
            rowExist.insert(get<1>(minpq.top()));
            colExist.insert(get<2>(minpq.top()));
            currLocation[get<1>(minpq.top())] = get<2>(minpq.top());
            minFound ++;
        }
        minpq.pop();    //remove the top value
    }

    return make_tuple(currLocation, up);
}

/**
 * calculates lower bound at node X
 * 
 * @param A, (N x N) Matrix with c_ij representing the time taken by agent i to complete task j
 * @param X, location of c_ij that already picked, for example X[0]=1 means row 0 column 1 already pick.
 * @return integer number of lower bound
 */
int lower_bound(vector<vector<int>> A, vector<int> X)
{
    set<int> colExist;
    int lb = 0;
    //calculate the current sum and save the row and column
    for(int i=0; i<X.size(); i++)
    {
        colExist.insert(X[i]);
        lb += A[i][X[i]];
    }
    
    for(int i=X.size(); i<A.size(); i++)
    {
        //travel all row that do not pick require
        int min = -1;
        //travel all column
        for(int j=0; j<A[i].size(); j++)
        {
          if(colExist.find(j)==colExist.end() && min == -1)
            min = A[i][j];
          else if(colExist.find(j)==colExist.end() && A[i][j]<min)
          //if the column is not require and is less than current min, reset the min
          {
            min = A[i][j];
          }
        }
        lb += min;  //add the min in this row to the lb
    }

    return lb;
}

/**
 * calculates Smallest Number Hueristic of a Matrix
 * 
 * @param vector<vector<int>> A: (N x N) Matrix with c_ij representing the time taken by agent i to complete task j
 * @return tuple with minimum element location which the value in index i is the column and the i is row
 * @return tuple with integer number of smallest number hueristic of Matrix A
 */
tuple<vector<int>, int> SNH(vector<vector<int>> A)
{
    //create priority queue by rule Compare
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, Compare> minpq;

    //travel all element in matrix and push the value to minpq
    for(int i=0; i<A.size(); i++)
    {
        for(int j=0; j<A[i].size(); j++)
        {
            tuple<int, int, int> tempValue(make_tuple(A[i][j], i, j));
            minpq.push(tempValue);
        }
    }

    vector<int> location(A.size(), 0);
    set<int> rowExist, colExist;
    //find the minimum value in the top and save each value
    int snh = get<0>(minpq.top());
    rowExist.insert(get<1>(minpq.top()));
    colExist.insert(get<2>(minpq.top()));
    location[get<1>(minpq.top())] = get<2>(minpq.top());
    minpq.pop();
    int minFound = 1;

    //find the A.size() minimum value
    while(minFound<A.size())
    {
        if(rowExist.find(get<1>(minpq.top()))==rowExist.end() && colExist.find(get<2>(minpq.top()))==colExist.end())
        //make sure the minimum value is not in the same row and column with before
        {
            //add the value to the snh and save the row and column
            snh += get<0>(minpq.top());
            rowExist.insert(get<1>(minpq.top()));
            colExist.insert(get<2>(minpq.top()));
            location[get<1>(minpq.top())] = get<2>(minpq.top());
            minFound ++;
        }
        minpq.pop();    //remove the top value
    }

    return make_tuple(location, snh);
}

/**
 * a structure to implements the operator of priotity for temp branch
 */
struct CompareTempBranch
{
    /**
     * check if the size of vector in tuple is grater than another
     * if is equal, check if the integer lower bound is greater than another
     * use in the priotity queue compare function
     * 
     * @param v1,v2, first vector in tuple is the require location in this node
     *               second integer in tuple is the lower bound value for this node
     * @return true if the size of vector in tuple is grater than another, and return true if they are equal and lower bound is
     *              greater than another. otherwise, return false
     */
    bool operator() (tuple<vector<int>, int> v1, tuple<vector<int>, int> v2)
    {
        // return true if v1 order before v2
        if(get<0>(v1).size() > get<0>(v2).size())
          return true;
        else if(get<0>(v1).size() < get<0>(v2).size())
          return false;
        else if(get<1>(v1) >= get<1>(v2))
          return true;

        return false;
    }
};

/**
 * a structure to implements the operator of priotity for branch
 */
struct CompareBranch
{
    /**
     * check if the size of vector in tuple is grater than another
     * if is equal, check if the integer lower bound is greater than another
     * use in the priotity queue compare function
     * 
     * @param v1,v2, first vector in tuple is the require location in this node
     *               second integer in tuple is the lower bound value for this node
     * @return true if the size of vector in tuple is grater than another, and return true if they are equal and lower bound is
     *              greater than another. otherwise, return false
     */
    bool operator() (tuple<vector<int>, int, int> v1, tuple<vector<int>, int, int> v2)
    {
        // return true if v1 order before v2
        // if(get<0>(v1).size() > get<0>(v2).size())
        //   return true;
        // else if(get<0>(v1).size() < get<0>(v2).size())
        //   return false;
        // else if(get<2>(v1) > get<2>(v2))
        //   return true;
        // else if(get<2>(v1) < get<2>(v2))
        //   return false;
        // else if(get<0>(v1).size()-2>=0 && get<0>(v2).size()-2>=0 && get<0>(v1)[get<0>(v1).size()-2] == get<0>(v2)[get<0>(v2).size()-2])
        //   return get<1>(v1) >= get<1>(v2);

        if(get<2>(v1) > get<2>(v2))
          return true;
        else if(get<2>(v1) < get<2>(v2))
          return false;
        else if(get<0>(v1).size() > get<0>(v2).size())
          return true;
        else if(get<0>(v1).size() < get<0>(v2).size())
          return false;
        else
          return get<1>(v1) >= get<1>(v2);

        return false;
    }
};

///////////////////////////////////////////////////////
//////////////       QUESTION 1 HERE   ////////////////
///////////////////////////////////////////////////////
tuple<vector<vector<int>>, vector<int>, int> myBranchBound(vector<vector<int>> C)
{
  /*
    TODO:
    
    Implement Assignment Branch and Bound function under here.
    Some Helper functions that might help you modularize the code:
        - int upper_bound(vector<vector<int>> A, vector<int> X) : calculates upper bound at node X
        - int lower_bound(vector<vector<int>> A, vector<int> X) : calculates lower bound at node X
        - int SNH(vector<vector<int>> A) : calculates Smallest Number Hueristic of a Matrix
        - int rowMin(vector<vector<int>> A) : calculates Row-Min strategy Lower bound of a Matrix
        - vector<int> minElement(vector<vector<int>> A) : calculates minimum element in a matrix with its position
        - vector<vector<int>> calcMatrixMinor(vector<vector<int>> A, int i, int j) : calculates minor of a Matrix at a given location
    Note: These functions are recommended however we won't be grading your implementations of the
          above stated functions

    Input:
    vector<vector<int>> C: (N x N) with c_ij representing the time taken by agent i to complete task j - vector<vector<int>>

    Input constraints: 2<N<10

    return:
    tuple <vector<vector<int>>, vector<int>, int> mySol: A tuple with the following elements in the exact order:
        0:  vector<vector<int>> X:  Optimal Assignment of Jobs -  vector<vector<int>>
        1:  vector<int> ub_list: List of upper bounds when they were updated(0th index should be the first upper bound calculated by SNH) - vector<int>
        2:  int node_count: Number of nodes evaluated by your branch and bound algorithm - int
    
  */
  
  vector<int> ub;
  //find the first upper bound using SNH
  tuple<vector<int>, int> snh = SNH(C);
  ub.push_back(get<1>(snh));
  vector<int> currMinLocation = get<0>(snh);
  cout << "1"<<endl;
  int node_count = 0;
  //create a queue to save the branch value, the first value in tuple is the require location in this node and the second value 
  // is the lower bound value for this node, the third integer is the minimum lower bound of branch for one node
  priority_queue<tuple<vector<int>, int, int>, vector<tuple<vector<int>, int, int>>, CompareBranch> branch;

  queue<tuple<vector<int>, int>> temp1;
  int minTemp = -1;

  //travel the first level of branch tree and push to the queue branch
  for(int i=0; i<C[0].size(); i++)
  {
    //get the curr require location
    vector<int> location;
    location.push_back(i);
    int currLB = lower_bound(C, location);  //call the lower_bound function to get the number of currLB
    
    if(currLB < ub.back())
    //if the currLB is less than the last upper bound, calculate the curr upper bound
    {
      if(minTemp == -1 || currLB < minTemp)
        minTemp = currLB;

      temp1.push(make_tuple(location, currLB));
      tuple<vector<int>, int> currUB = upper_bound(C, location);  //call upper_bound function to find the currUB
      
      if(get<1>(currUB) < ub.back())
      //if the curr upper bound is less than the last upper bound, add the currUB to the list of ub and change the minimum location
      {
        ub.push_back(get<1>(currUB));
        currMinLocation = get<0>(currUB);
      }
    }
    node_count ++;  //add the count of node
  }

  while(!temp1.empty())
  {
    branch.push(make_tuple(get<0>(temp1.front()), get<1>(temp1.front()), minTemp));
    temp1.pop();
  }
  cout << "2 " << temp1.size() <<endl;

  while(!branch.empty())
  //travel when the branch queue is not empty
  {
    if(get<1>(branch.top()) < ub.back() && get<0>(branch.top()).size() < C.size()-1)  //if the lower bound is the top is less than the last upper bound
    {
      set<int> colExist;
      //get the location in top node
      vector<int> currLocation = get<0>(branch.top());
      for(int i=0; i<currLocation.size(); i++)
      {
        colExist.insert(currLocation[i]);
      }

      // priority_queue<tuple<vector<int>, int>, vector<tuple<vector<int>, int>>, CompareTempBranch> temp;
      int minTempLB = -1;

      for(int i=0; i<C[0].size(); i++)
      {
        if(colExist.find(i)==colExist.end())
        //if the column do not be used before
        {
          vector<int> location = currLocation;
          location.push_back(i);  //add a new location
          int currLB = lower_bound(C, location);
          
          if(currLB < ub.back())
          //if the currLB is less than the last upper bound, calculate the curr upper bound
          {
            if(minTempLB == -1 || currLB < minTempLB)
              minTempLB = currLB;

            temp1.push(make_tuple(location, currLB));
            tuple<vector<int>, int> currUB = upper_bound(C, location);  //call upper_bound function to find the currUB
            
            if(get<1>(currUB) < ub.back())
            //if the curr upper bound is less than the last upper bound, add the currUB to the list of ub
            {
              ub.push_back(get<1>(currUB));
              currMinLocation = get<0>(currUB);
            }
          }
          
          node_count ++;  //add the number to the count of node
        }
      }

      while(!temp1.empty())
      {
        branch.push(make_tuple(get<0>(temp1.front()), get<1>(temp1.front()), minTempLB));
        temp1.pop();
      }
    }
    cout << " 3: "<< branch.size();
    branch.pop(); //remove the top node
  }

  //draw the location of matrix
  vector<int> col(C[0].size(), 0);
  vector<vector<int>> matrix(C.size(), col);
  for(int i=0; i<currMinLocation.size(); i++)
  {
    matrix[i][currMinLocation[i]] = 1;
  }

  return make_tuple(matrix, ub, node_count);
}

/////////////////////////////////////////////////////////
//////////////       QUESTION 2 HERE   //////////////////
/////////////////////////////////////////////////////////
vector<vector<int>> myDynamicProgramming(int n, int c, int V[], int W[])
{
  /*
    TODO:

    Implement Knapsack Dynamic Programming function under here and return the 2-D matrix generated to solve this question.

    Input:
    int n: Number of items - int
    int c: Capacity of the Knapsack - int
    int V[]: Array of Values of each item - int[] (1-D int array)
    int W[]: Array of Weights of each item - int[] (1-D int array)

    return:
    vector<vector<int>> DP: Dynamic Programming two-dimensional matrix generated while calculating - vector<vector<int>>
  */
  vector<vector<int>> DP;
  vector<int> firstDp(c+1, 0);  //create the first line of DP with c+1 of 0
  DP.push_back(firstDp);

  if(c==0 || n==0)
    return DP;
  
  for(int i=1; i<=n; i++)
  //create other n line of DP
  {
    vector<int> currLineDp;
    currLineDp.push_back(0);  //add the first 0 to the line
    for(int j=1; j<=c; j++)
    {
      if(j-W[i-1]>=0)
      //if the curr capacity minus new weight is greater than or equal to 0, find the maximum value between
      // DP[i-1][j-W[i-1]] + V[i-1] and DP[i-1][j], add the maximum value to the line
      {
        int temp = DP[i-1][j-W[i-1]] + V[i-1];
        currLineDp.push_back(max(DP[i-1][j], temp));
      }
      else    //add the value in DP[i-1][j] to the line
      {
        currLineDp.push_back(DP[i-1][j]);
      }
    }
    DP.push_back(currLineDp);   //push the whole line to the DP
  }

  return DP;
}

vector<int> myBitmask(int n, int c, int V[], int W[])
{
  /*
    TODO:

    Return the bitmask for the Knapsack Dynamic Programming problem given the 2-D matrix which you can generate 
    by calling myDynamicProgramming(n, c, V, W).

    Input:
    int n: Number of items - int
    int c: Capacity of the Knapsack - int
    int V[]: Array of Values of each item - int[] (1-D int array)
    int W[]: Array of Weights of each item - int[] (1-D int array)

    return:
    vector<int> Z: Optimal choice of items for the given constraints - vector<int>
  */

  vector<vector<int>> DP = myDynamicProgramming(n, c, V, W);    //call myDynamicProgramming to find the DP matrix
  vector<int> Z(n, 0);  //initial each value not pick

  if(c == 0 || n == 0)
  {
    return Z;
  }

  //initial the value to find the last value in the matrix
  int currRow = n;
  int currCol = c;
  //int currItem = n-1;

  cout << DP[currRow][currCol]<<endl;
  while(currRow > 0)
  {
    if(currRow-1 >=0 && DP[currRow][currCol] == DP[currRow-1][currCol])
    //if the value in curr is equal to the value up 1 of the curr, the currItem is 0 (which means not pick) and move to the up
    {
      //currItem --;
      currRow --;
    }
    else if(currRow-1 >= 0)
    //otherwise, the currItem is 1 (which means picked) and move to DP[currRow-1][currCol-W[currRow]]
    {
      Z[currRow-1] = 1;
      currRow --;
      currCol -= W[currRow];
    }
  }

  return Z;
}
