#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Coordinate {
    int x;
    int y;
    bool operator<(const Coordinate &rhs) const {
        if(y > rhs.y) {return true;}
        return x > rhs.x;
    }
    Coordinate operator+(const Coordinate &rhs) const {
        return Coordinate{x + rhs.x, y + rhs.y};
    }
    Coordinate& operator+=(const Coordinate &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Coordinate operator*(const int multiple) const {
        return Coordinate{x * multiple, y * multiple};
    }
    Coordinate& operator*=(const int multiple) {
        x *= multiple;
        y *= multiple;
        return *this;
    }
    bool operator==(const Coordinate& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

class Fungus {
private:
    Coordinate coordinate_;
    int size_;
    Coordinate velocity_;
    int turn_;
public:
    Fungus(Coordinate coordinate, int size, Coordinate velocity, int turn=0): coordinate_(coordinate), size_(size), velocity_(velocity), turn_(turn) {}
    void move(int width, int height, int this_turn) {
        if(this_turn != turn_) {return;}
        ++turn_;
        coordinate_ += velocity_;
        if(coordinate_.x < 0) {
            if(coordinate_.x <= -height) {coordinate_.x += (height << 1) - 2;}
            else {coordinate_.x = -coordinate_.x; velocity_ *= -1;}
        }
        else if(height <= coordinate_.x) {
            if(((height << 1) - 2) < coordinate_.x) {coordinate_.x -= (height << 1) - 2;}
            else {coordinate_.x = (height << 1) - coordinate_.x - 2; velocity_ *= -1;}
        }
        if(coordinate_.y < 0) {
            if(coordinate_.y <= -width) {coordinate_.y += (width << 1) - 2;}
            else {coordinate_.y = -coordinate_.y; velocity_ *= -1;}
        }
        else if(width <= coordinate_.y) {
            if(((width << 1) - 2) < coordinate_.y) {coordinate_.y -= (width << 1) - 2;}
            else {coordinate_.y = (width << 1) - coordinate_.y - 2; velocity_ *= -1;}
        }
    }
    int getColumn() {return coordinate_.y;}
    int getSize() {return size_;}
    Coordinate getCoordinate() {return coordinate_;}
    bool operator<(const Fungus& rhs) const {return coordinate_ < rhs.coordinate_;}
};

class Field {
private:
    int width_;
    int height_;
    vector<priority_queue<Fungus>> fungi_;
    int sample_column_;
public:
    Field(int height, int width): width_(width), height_(height), fungi_(vector<priority_queue<Fungus>>(width, priority_queue<Fungus>())), sample_column_(0) {}
    void read(int fungi_count) {
        const Coordinate direction[5] = {
            { 0, 0}, {-1, 0}, { 1, 0}, { 0, 1}, { 0,-1}
        };
        int modular_speed[5] = {
            0, (height_ - 1) << 1, (height_ - 1) << 1, (width_ - 1) << 1, (width_ - 1) << 1
        };
        for(int it = 0; it < fungi_count; ++it) {
            int x, y, s, d, b;
            cin >> x >> y >> s >> d >> b;
            fungi_[y - 1].push(Fungus{{x - 1, y - 1}, b, direction[d] * (s % modular_speed[d])});
        }
    }
    int sample() {
        int sampled_size{};
        for(int sample_it = 0; sample_it < width_; ++sample_it) {
            if(!fungi_[sample_it].empty()) {
                Fungus fungus = fungi_[sample_it].top();
                sampled_size += fungus.getSize();
                fungi_[sample_it].pop();
            }
            int column_it{0};
            for(priority_queue<Fungus>& fungi_column : fungi_) {
                priority_queue<Fungus> fungi_moved{};
                while(!fungi_column.empty()) {
                    Fungus fungus = fungi_column.top();
                    fungi_column.pop();
                    fungus.move(width_, height_, sample_it);
                    if(column_it == fungus.getColumn()) {
                        fungi_moved.push(fungus);
                        continue;
                    }
                    fungi_[fungus.getColumn()].push(fungus);
                }
                fungi_column.swap(fungi_moved);
                ++column_it;
            }
            for(priority_queue<Fungus>& fungi_column : fungi_) {
                if(fungi_column.size() <= 1) {continue;}
                Fungus fungus_lhs = fungi_column.top();
                fungi_column.pop();
                priority_queue<Fungus> fungi_merged{};
                while(!fungi_column.empty()) {
                    Fungus fungus_rhs = fungi_column.top();
                    fungi_column.pop();
                    if(fungus_lhs.getCoordinate() == fungus_rhs.getCoordinate()) {
                        if(fungus_lhs.getSize() > fungus_rhs.getSize()) {continue;}
                        fungus_lhs = fungus_rhs;
                        continue;
                    }
                    fungi_merged.push(fungus_lhs);
                    fungus_lhs = fungus_rhs;
                }
                fungi_merged.push(fungus_lhs);
                fungi_column.swap(fungi_merged);
            }
        }
        return sampled_size;
    }
};

int main() {
    // initiate fast io
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    Field field{n, m};
    field.read(k);
    cout << field.sample();
    return 0;
}