/**
  * @file   SDL_Const.cpp
  * @author 0And1Story
  * @date   2023-09-22
  * @brief  
  */
#include "SDL_Const.h"

const SDL_Rect& operator*=(SDL_Rect& rect_, const int& scale_) {
    rect_.x *= scale_;
    rect_.y *= scale_;
    rect_.w *= scale_;
    rect_.h *= scale_;
    return rect_;
}

const SDL_Rect& operator*=(SDL_Rect& rect_, const double& scale_) {
    rect_.x = (int)(rect_.x * scale_);
    rect_.y = (int)(rect_.y * scale_);
    rect_.w = (int)(rect_.w * scale_);
    rect_.h = (int)(rect_.h * scale_);
    return rect_;
}

SDL_Rect operator*(const SDL_Rect& rect_, const int& scale_) {
    return SDL_Rect {
            rect_.x * scale_,
            rect_.y * scale_,
            rect_.w * scale_,
            rect_.h * scale_
    };
}

SDL_Rect operator*(const SDL_Rect& rect_, const double& scale_) {
    return SDL_Rect {
            (int)(rect_.x * scale_),
            (int)(rect_.y * scale_),
            (int)(rect_.w * scale_),
            (int)(rect_.h * scale_)
    };
}

SDL_Rect operator/(const SDL_Rect& rect_, const int& scale_) {
    return SDL_Rect {
            (int)(rect_.x / scale_),
            (int)(rect_.y / scale_),
            (int)(rect_.w / scale_),
            (int)(rect_.h / scale_)
    };
}

SDL_Rect operator/(const SDL_Rect& rect_, const double& scale_) {
    return SDL_Rect {
            (int)(rect_.x / scale_),
            (int)(rect_.y / scale_),
            (int)(rect_.w / scale_),
            (int)(rect_.h / scale_)
    };
}


const SDL_Point& operator*=(SDL_Point& position_, const int& scale_) {
    position_.x *= scale_;
    position_.y *= scale_;
    return position_;
}

const SDL_Point& operator*=(SDL_Point& position_, const double& scale_) {
    position_.x = (int)(position_.x * scale_);
    position_.y = (int)(position_.y * scale_);
    return position_;
}

SDL_Point operator*(const SDL_Point& position_, const int& scale_) {
    return SDL_Point {
            position_.x * scale_,
            position_.y * scale_
    };
}

SDL_Point operator*(const SDL_Point& position_, const double& scale_) {
    return SDL_Point {
            (int)(position_.x * scale_),
            (int)(position_.y * scale_)
    };
}

SDL_Point operator/(const SDL_Point& position_, const int& scale_) {
    return SDL_Point {
            (int)(position_.x / scale_),
            (int)(position_.y / scale_)
    };
}

SDL_Point operator/(const SDL_Point& position_, const double& scale_) {
    return SDL_Point {
            (int)(position_.x / scale_),
            (int)(position_.y / scale_)
    };
}

const SDL_Point& operator+=(SDL_Point& position_A, const SDL_Point& position_B) {
    position_A.x += position_B.x;
    position_A.y += position_B.y;
    return position_A;
}

const SDL_Point& operator-=(SDL_Point& position_A, const SDL_Point& position_B) {
    position_A.x -= position_B.x;
    position_A.y -= position_B.y;
    return position_A;
}

SDL_Point operator+(const SDL_Point& position_A, const SDL_Point& position_B) {
    return SDL_Point { position_A.x + position_B.x, position_A.y + position_B.y };
}

SDL_Point operator-(const SDL_Point& position_A, const SDL_Point& position_B) {
    return SDL_Point { position_A.x - position_B.x, position_A.y - position_B.y };
}

SDL_Color GetColorFromHex(Uint32 color_hex) {
    return SDL_Color {
            (Uint8)(color_hex >> 24),
            (Uint8)((color_hex >> 16) & 0xFF),
            (Uint8)((color_hex >> 8) & 0xFF),
            (Uint8)(color_hex & 0xFF),
    };
}
