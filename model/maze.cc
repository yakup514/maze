//
//  maze.cc
//  maze
//
//  Created by mcbk on 10.11.2023.
//

#include "maze.h"
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>
#include <QWidget>
void Maze::PrepareSeed(int row) {
    if (row == 0)
        return;
    for (int i = 0; i < cols_; ++i) {
        if (bottom_border_[row - 1][i])
            seed_[i] = counter_++;
    }
}
void Maze::AddSideBorder(int row) {
    PrepareSeed(row);
//    std::cout << "after PrepareSeed:\n";
//    for (auto v : seed_)
//        std::cout << v << ' ';
//    std::cout << '\n';
    
        
       
        for (int i = 0; i < cols_ - 1; ++i) {
            if (CoinFlip() || seed_[i] == seed_[i + 1]) {
                side_border_[row][i] = 1;
            } else {
                Merge(i, seed_[i]);
            }
        }
    if (row == rows_ - 1) {
        for (int i = 0; i < cols_ - 1; ++i) {
            if (seed_[i] != seed_[i + 1]) {
                side_border_[row][i] = 0;
                Merge(i, seed_[i]);
            }
        }
    }
//    std::cout << "after AddSideBorder:\n";
//    for (auto v : seed_)
//        std::cout << v << ' ';
//    std::cout << '\n';
    side_border_[row][cols_ - 1] = 1;
}

void Maze::Merge(int i, int val) {
    int mut_val = seed_[i + 1];
    for (int j = 0; j < cols_; ++j) {
        if(seed_[j] == mut_val) {
            seed_[j] = val;
        }
    }
}
void Maze::AddBottomBorder(int row) {
//    for (auto v : seed_)
//        std::cout << v << ' ';
//    std::cout << '\n';
    if (row == rows_ - 1 ) {
        for (int i = 0; i < cols_; ++i)
            bottom_border_[row][i] = 1;
    } else {
        bool have_pass = false;
        for (int i = 0; i < cols_ - 1; ++i) {
            if(!(seed_[i] != seed_[i + 1] && !have_pass)) {
                if (CoinFlip())
                    bottom_border_[row][i] = 1;
                else
                    have_pass = true;
            }
            if(seed_[i] != seed_[i + 1]) {
                have_pass = false;
            }
        }
        if (have_pass)
            bottom_border_[row][cols_ - 1] = CoinFlip();
    }
}

std::mt19937 engine;
bool Maze::CoinFlip() {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1ms);
    unsigned seed = unsigned (std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count());
        engine.seed(seed);
    std::random_device device;
    std::uniform_int_distribution<unsigned> distribution(0, 10000);
    return distribution(engine) % 2;
}

void Maze::SaveMaze(std::string path){
    std::ofstream out;
    out.open(path);
    if (out.is_open()) {
        out << rows_ << ' ' << cols_ << '\n';
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                out << side_border_[i][j];
                j == cols_ - 1 ? out << '\n' : out << ' ';
            }
        }
        out << '\n';
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                out << bottom_border_[i][j];
                j == cols_ - 1 ? out << '\n' : out << ' ';
            }
        }
        out.close();
    }
}

void Maze::LoadMaze(std::string path) {
    std::ifstream in(path);
        if (in.is_open()) {
            in >> rows_ >> cols_;
            InitMaze(rows_, cols_);
            bool tmp;
            int i = 0, j = 0;
            while(in >> tmp) {
                 qDebug() << tmp << ' ';
                side_border_[i][j++] = tmp;
                if (j == cols_) {
                    j = 0;
                    ++i;
                }
                if (i == rows_)
                    break;
            }
            i = 0, j = 0;
            while(in >> tmp) {
                bottom_border_[i][j++] = tmp;
                if (j == cols_) {
                    j = 0;
                    ++i;

                }
                if (i == rows_)
                    break;
            }

        }
        in.close();
}

void Maze::Generate(int rows, int cols) {
    InitMaze(rows, cols);
    for (int i = 0; i < rows_; ++i) {
        AddSideBorder(i);
        AddBottomBorder(i);
    }
}

void Maze::InitMaze(int rows, int cols) {
    if (rows < 2 || cols < 2 || rows > 50 || cols > 50) {
        rows = 2;
        cols = 2;
    }
    cols_= cols;
    rows_ = rows;
    side_border_.clear();
    bottom_border_.clear();
    seed_.clear();
    side_border_.resize(rows);
    bottom_border_.resize(rows);
    for (int i = 0; i < rows; ++i) {
        side_border_[i].resize(cols);
        bottom_border_[i].resize(cols);
    }
    seed_.resize(cols);
    for (counter_ = 0; counter_ < cols; ++ counter_)
        seed_[counter_] = counter_;
    vert_length_ = (k_width ) / rows;
    hor_length_ = (k_height ) / cols;
}
