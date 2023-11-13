//
//  maze.h
//  maze
//
//  Created by mcbk on 10.11.2023.
//

#ifndef maze_hpp
#define maze_hpp

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
class Maze {
    static constexpr int k_line_w = 2;
    static constexpr int k_width = 500;
    static constexpr int k_length = 500;
    std::vector<std::vector<bool>> side_border_;
    std::vector<std::vector<bool>> bottom_border_;
    std::vector<int> seed_;
    int counter_;
    int rows_;
    int cols_;
    int vert_length_;
    int hor_length_;
    void PrepareSeed(int row);
    void AddSideBorder(int row);
    void AddBottomBorder(int row);
    void Merge(int i, int val);
public:
    Maze(int rows, int cols) : rows_{rows}, cols_{cols} {
        side_border_.resize(rows);
        bottom_border_.resize(rows);
        for (int i = 0; i < rows; ++i) {
            side_border_[i].resize(cols);
            bottom_border_[i].resize(cols);
        }
        seed_.resize(cols);
        for (counter_ = 0; counter_ < cols; ++ counter_)
            seed_[counter_] = counter_;
        vert_length_ = (k_width - 2 * k_line_w * rows) / rows;
        hor_length_ = (k_length - 2 * k_line_w * cols) / cols;
        std::cout << vert_length_ << ' ' << hor_length_ << '\n';
    }
    void Print();
    bool CoinFlip();
    void Generate();
};
#endif /* maze_h */
