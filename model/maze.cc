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
                seed_[i + 1] = seed_[i];
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
    for (int j = i; j < cols_; ++j) {
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
void Maze::Print() {
    std::cout << '\n';
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout <<side_border_[i][j];
            j == cols_ - 1 ? std::cout << '\n' : std::cout << ' ';
        }
    }
    std::cout << '\n';
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout <<bottom_border_[i][j];
            j == cols_ - 1 ? std::cout << '\n' : std::cout << ' ';
        }
    }
    std::cout << '\n';
    for (int j = 0; j < cols_; ++j)
        std::cout << "__";
    std::cout << '\n';
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (bottom_border_[i][j] && side_border_[i][j]) {
                std::cout<< "_⏌";
            } else if (bottom_border_[i][j] && !side_border_[i][j]){
                std::cout << "__";
            } else if (!bottom_border_[i][j] && side_border_[i][j]){
                std::cout << " |";
            }  else {
                std::cout << "  ";
            }
           
            if(j == cols_ - 1)
                std::cout << '\n';
        }
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

void Maze::Generate() {
    for (int i = 0; i < rows_; ++i) {
        AddSideBorder(i);
        AddBottomBorder(i);
    }
}
