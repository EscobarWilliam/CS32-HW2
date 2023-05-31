//
//  mazestack.cpp
//  HW_2
//
//  Created by William  Escobar on 4/29/23.
//


#include <stack>
#include <iostream>
#include <cassert>
//Declare Prototype
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

//Define Coord Class
class Coord
{
    public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {} //initializes row and column positions
    int r() const { return m_r; } //return current row position
    int c() const { return m_c; } //return current column position

    private:
    //member variables that hold the position
    int m_r;
    int m_c;
};

//------------------------------------------------------------------------
//     bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
//
// Returns true if there is a path from (sr, sc) to (er, ec) through maze
// Otherwise it returns false is not path exists
//------------------------------------------------------------------------
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    //create a stack of coordinatest which will allow us to move through maze
    std::stack<Coord> coordStack;
    Coord start(sr, sc); //create the starting coordinate
    Coord end(er, ec); //create the ending coordinate

    coordStack.push(start);
    maze[sr][sc] = '#'; //'#' represents that we've already discoverd the position

    //while the stack isn't empty continue to search for a path through
    while(!coordStack.empty())
    {
        //retrieve the current location in maze
        Coord curr = coordStack.top();
        coordStack.pop();

        //if current position is the end then path exists
        if(curr.r() == end.r() && curr.c() == end.c())
            return true;

        //look to the SOUTH--------------------------------
        if(maze[curr.r()+1][curr.c()] == '.')
        {
            maze[curr.r()+1][curr.c()] = '#';//mark as discovered
            coordStack.push( Coord(curr.r()+1, curr.c()) ); //push this position onto stack
        }
        //look to the EAST--------------------------------
        if(maze[curr.r()][curr.c()+1] == '.')
        {
            maze[curr.r()][curr.c()+1] = '#';//mark as discovered
            coordStack.push( Coord(curr.r(), curr.c()+1) ); //push this position onto stack
        }
        //look to the NORTH--------------------------------
        if(maze[curr.r()-1][curr.c()] == '.')
        {
            maze[curr.r()-1][curr.c()] = '#';//mark as discovered
            coordStack.push( Coord(curr.r()-1, curr.c()) ); //push this position onto stack
        }
        //look to the WEST--------------------------------
        if(maze[curr.r()][curr.c()-1] == '.')//we don't need to check if its a '#' because if it is '.' its undiscovered
        {
            maze[curr.r()][curr.c()-1] = '#';//mark as discovered
            coordStack.push( Coord(curr.r(), curr.c()-1) ); //push this position onto stack
        }

    }

    return false;
}

int main()
{
    //For the homework assignment, we don't have to generate the mazes.
    //It is assumed the client would enter a maze which is valid.
    //i.e. the walls only contian 'X' and the other elements are '.' or 'X'
    char maze[10][10] = {
            { 'X','X','X','X','X','X','X','X','X','X'},
            { 'X','.','.','.','.','.','.','.','.','X'},
            { 'X','X','.','X','.','X','X','X','X','X'},
            { 'X','.','.','X','.','X','.','.','.','X'},
            { 'X','.','.','X','.','.','.','X','.','X'},
            { 'X','X','X','X','.','X','X','X','.','X'},
            { 'X','.','.','X','.','.','.','X','X','X'},
            { 'X','.','.','X','X','.','X','X','.','X'},
            { 'X','.','.','.','X','.','.','.','.','X'},
            { 'X','X','X','X','X','X','X','X','X','X'}
        };
        assert(pathExists(maze, 6,4, 1,1)); //start position (6,4) and end position (1,1), solution exists

    char maze1[10][10] = {
            { 'X','X','X','X','X','X','X','X','X','X'},
            { 'X','.','X','.','.','X','.','.','.','X'},
            { 'X','.','X','X','.','X','.','X','X','X'},
            { 'X','.','.','.','.','X','.','X','.','X'},
            { 'X','X','.','X','.','X','.','.','.','X'},
            { 'X','X','X','.','.','X','.','X','.','X'},
            { 'X','.','.','.','X','.','.','.','X','X'},
            { 'X','.','X','X','.','.','X','.','X','X'},
            { 'X','.','.','.','.','X','.','.','.','X'},
            { 'X','X','X','X','X','X','X','X','X','X'}
        };
        assert(pathExists(maze1, 8, 6, 1, 1)); //start position (8,6) and end position (1,1), solution exists

    char maze2[10][10] = {
            { 'X','X','X','X','X','X','X','X','X','X'},
            { 'X','.','X','.','.','X','.','.','.','X'},
            { 'X','X','X','X','.','X','.','X','X','X'},
            { 'X','.','.','.','.','X','.','X','.','X'},
            { 'X','X','.','X','.','X','.','.','.','X'},
            { 'X','X','X','.','.','X','.','X','.','X'},
            { 'X','.','.','.','X','.','.','.','X','X'},
            { 'X','.','X','X','.','.','X','.','X','X'},
            { 'X','.','.','.','.','X','.','.','.','X'},
            { 'X','X','X','X','X','X','X','X','X','X'}

        };
        assert(!pathExists(maze2, 8, 6, 1, 1)); //start position (8,6) and end position (1,1), no solution

    char maze3[10][10] = {
            { 'X','X','X','X','X','X','X','X','X','X'},
            { 'X','X','.','.','.','.','.','X','X','X'},
            { 'X','.','.','X','X','.','.','.','.','X'},
            { 'X','.','.','.','X','.','.','.','X','X'},
            { 'X','.','X','.','X','X','X','.','.','X'},
            { 'X','X','X','X','.','.','X','.','.','X'},
            { 'X','X','.','.','.','.','X','.','.','X'},
            { 'X','.','.','.','.','.','.','.','X','X'},
            { 'X','.','.','X','X','X','X','X','X','X'},
            { 'X','X','X','X','X','X','X','X','X','X'}

        };
        assert(pathExists(maze3, 4, 3, 7, 1)); //start position (4,3) and end position (7,1), solution exists

    char maze4[10][10] = {
            { 'X','X','X','X','X','X','X','X','X','X'},
            { 'X','X','.','.','.','.','.','X','X','X'},
            { 'X','.','.','X','X','.','.','.','.','X'},
            { 'X','.','.','.','X','.','.','.','X','X'},
            { 'X','.','X','.','X','X','X','.','.','X'},
            { 'X','X','X','X','.','.','X','.','.','X'},
            { 'X','X','.','.','.','.','X','.','.','X'},
            { 'X','.','X','.','.','.','.','.','X','X'},
            { 'X','.','.','X','X','X','X','X','X','X'},
            { 'X','X','X','X','X','X','X','X','X','X'}
        };
        assert(!pathExists(maze4, 4, 3, 7, 1));//start position (4,3) and end position (7,1), no solution
        std::cerr << "Passed all tests!" << std::endl;
    return 0;
}

