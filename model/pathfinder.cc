#include "pathfinder.h"
Pathfinder::Pathfinder()
{

}

void Pathfinder::NextStep (size_t x, size_t y, int count) {
    data_[y][x] = count;
    if (x == finish_.first && y == finish_.second)
        return;
    if (y > 0 && !maze_->bottom_border_[y - 1][x] && data_[y - 1][x] == 0)
        NextStep(x, y - 1, count + 1);
    if (y < maze_->rows_ - 1 && !maze_->bottom_border_[y][x] && data_[y + 1][x] == 0)
        NextStep(x, y + 1, count + 1);
    if (x > 0 && !maze_->side_border_[y][x - 1] && data_[y][x - 1] == 0)
        NextStep(x - 1, y, count + 1);
    if (x < maze_->cols_ - 1 && !maze_->side_border_[y][x] && data_[y][x + 1] == 0)
        NextStep(x + 1, y, count + 1);
}


void Pathfinder::Solve() {

    NextStep(start_.first, start_.second, 1);
    std::pair<size_t, size_t> tmp = finish_;
    result_.clear();
    while (tmp != start_) {
        result_.push_back(tmp);
        int next = data_[tmp.second][tmp.first] - 1;
        if (tmp.first < maze_->cols_ - 1 && next == data_[tmp.second][tmp.first + 1] && !maze_->side_border_[tmp.second][tmp.first])
            tmp = {tmp.first + 1, tmp.second};
        else if (tmp.first > 0 && next == data_[tmp.second][tmp.first - 1]&& !maze_->side_border_[tmp.second][tmp.first - 1])
            tmp = {tmp.first - 1, tmp.second};
        else if (tmp.second < maze_->rows_ - 1 && next == data_[tmp.second + 1][tmp.first] && !maze_->bottom_border_[tmp.second][tmp.first])
            tmp = {tmp.first , tmp.second + 1};
        else if (tmp.second > 0 && next == data_[tmp.second - 1][tmp.first]&& !maze_->bottom_border_[tmp.second - 1][tmp.first])
            tmp = {tmp.first, tmp.second - 1};
    }
    result_.push_back(tmp);

}
