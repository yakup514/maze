//
//  maze.h
//  maze
//
//  Created by mcbk on 10.11.2023.
//

#ifndef maze_h
#define maze_h

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
class Maze {

    std::vector<int> seed_;
    int counter_;
    void PrepareSeed(int row);
    void AddSideBorder(int row);
    void AddBottomBorder(int row);
    void Merge(int i, int val);
    void InitMaze(int rows, int cols);
    bool CoinFlip();
public:
    Maze(){};
    static constexpr int k_width = 500;
    static constexpr int k_height = 500;
    std::vector<std::vector<bool>> side_border_;
    std::vector<std::vector<bool>> bottom_border_;
    int rows_ = 0;
    int cols_ = 0;
    int vert_length_;
    int hor_length_;
    void SaveMaze(std::string path);
    void LoadMaze(std::string path);
    void Generate(int rows, int cols);
};
#endif /* maze_h */
