#ifndef PATHFINDER_H
#define PATHFINDER_H


#include "maze.h"
class Pathfinder {
    Maze* maze_;
    std::vector<std::vector<int>> data_;
    std::pair<size_t, size_t> start_{0,0};
    std::pair<size_t, size_t> finish_{0,0};
public:
    Pathfinder();
    void Init (Maze* maze, std::pair<size_t, size_t> start, std::pair<size_t, size_t> finish) {
        maze_ = maze;
        data_.clear();
        data_.resize(maze_->rows_);
        for (size_t i = 0; i < data_.size(); ++i) {
            data_[i].resize(maze_->cols_, 0);
        }

            start_ = start;
            finish_ = finish;
            result_.clear();
    }
    void NextStep(size_t x, size_t y, int count);
    std::vector<std::pair<size_t, size_t>> result_;
    void Solve();

};

#endif // PATHFINDER_H
