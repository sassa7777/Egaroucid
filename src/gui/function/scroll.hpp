/*
    Egaroucid Project

    @file scroll.hpp
        Scroll Utility
    @date 2021-2024
    @author Takuto Yamana
    @license GPL-3.0 license
*/

#pragma once
#include "const/gui_common.hpp"

class Scroll_manager{
private:
    Rect rect;
    Rect frame_rect;
    int sx;
    int sy;
    int width;
    int height;
    int rect_min_height;
    int n_elem;
    int n_elem_per_window;
    int rect_height;
    int max_strt_idx;
    double strt_idx_double;
    uint64_t up_strt;
    uint64_t down_strt;
    uint64_t pup_strt;
    uint64_t pdown_strt;
    bool dragged;
    int dragged_y_offset;


public:
    void init(int x, int y, int w, int h, int rect_mh, int ne, int n_epw){
        sx = x;
        sy = y;
        width = w;
        height = h;
        rect_min_height = rect_mh;
        n_elem = ne;
        n_elem_per_window = n_epw;
        rect_height = std::max(rect_min_height, (int)round((double)n_elem_per_window / (double)n_elem * (double)height));
        max_strt_idx = std::max(n_elem - n_elem_per_window, 0);
        strt_idx_double = 0.0;
        up_strt = BUTTON_NOT_PUSHED;
        down_strt = BUTTON_NOT_PUSHED;
        pup_strt = BUTTON_NOT_PUSHED;
        pdown_strt = BUTTON_NOT_PUSHED;
        dragged = false;
        rect.x = sx;
        rect.w = width;
        rect.h = rect_height;
        frame_rect.x = sx;
        frame_rect.y = sy;
        frame_rect.w = width;
        frame_rect.h = height;
    }

    void draw(){
        int strt_idx_int = round(strt_idx_double);
        double percent = (double)strt_idx_int / (double)max_strt_idx;
        int rect_y = sy + round(percent * (double)(height - rect_height));
        frame_rect.drawFrame(1.0, Palette::White);
        rect.y = rect_y;
        rect.draw(Palette::White);
        if (dragged){
            Cursor::RequestStyle(CursorStyle::ResizeUpDown);
        }
    }

    void update(){
        strt_idx_double = std::max(0.0, std::min((double)(n_elem - n_elem_per_window), strt_idx_double + Mouse::Wheel()));
        if (!KeyUp.pressed()){
            up_strt = BUTTON_NOT_PUSHED;
        }
        if (!KeyDown.pressed()){
            down_strt = BUTTON_NOT_PUSHED;
        }
        if (!KeyPageUp.pressed()){
            pup_strt = BUTTON_NOT_PUSHED;
        }
        if (!KeyPageDown.pressed()){
            pdown_strt = BUTTON_NOT_PUSHED;
        }
        if (KeyUp.down() || (up_strt != BUTTON_NOT_PUSHED && tim() - up_strt >= BUTTON_LONG_PRESS_THRESHOLD)){
            strt_idx_double = std::max(0.0, strt_idx_double - 1.0);
            if (KeyUp.down()){
                up_strt = tim();
            }
        }
        if (KeyDown.down() || (down_strt != BUTTON_NOT_PUSHED && tim() - down_strt >= BUTTON_LONG_PRESS_THRESHOLD)){
            strt_idx_double = std::max(0.0, std::min((double)(n_elem - n_elem_per_window), strt_idx_double + 1.0));
            if (KeyDown.down()){
                down_strt = tim();
            }
        }
        if (KeyPageUp.down() || (pup_strt != BUTTON_NOT_PUSHED && tim() - pup_strt >= BUTTON_LONG_PRESS_THRESHOLD)){
            strt_idx_double = std::max(0.0, strt_idx_double - n_elem_per_window);
            if (KeyPageUp.down()){
                pup_strt = tim();
            }
        }
        if (KeyPageDown.down() || (pdown_strt != BUTTON_NOT_PUSHED && tim() - pdown_strt >= BUTTON_LONG_PRESS_THRESHOLD)){
            strt_idx_double = std::max(0.0, std::min((double)(n_elem - n_elem_per_window), strt_idx_double + n_elem_per_window));
            if (KeyPageDown.down()){
                pdown_strt = tim();
            }
        }
        if (rect.leftClicked()){
            dragged = true;
            dragged_y_offset = Cursor::Pos().y - rect.y;
            std::cerr << dragged_y_offset << std::endl;
        } else if (!MouseL.pressed()){
            dragged = false;
        }
        if (dragged){
            double n_percent = std::max(0.0, std::min(1.0, (double)(Cursor::Pos().y - dragged_y_offset - sy) / (height - rect_height)));
            strt_idx_double = n_percent * (double)max_strt_idx;
        }
        if (frame_rect.leftClicked()){
            double n_percent = std::max(0.0, std::min(1.0, (double)(Cursor::Pos().y - rect.h / 2 - sy) / (height - rect_height)));
            strt_idx_double = n_percent * (double)max_strt_idx;
        }
    }

    int get_strt_idx_int() const{
        return (int)strt_idx_double;
    }

    bool is_dragged() const{
        return dragged;
    }
};