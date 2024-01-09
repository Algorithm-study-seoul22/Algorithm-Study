#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Town {
private:
    int quantity;
    vector<int> houses;
public:
    Town(int number_of_houses): quantity(number_of_houses), houses(vector<int>(number_of_houses)) {}
    void read_input() {
        for(int &house: houses) {
            cin >> house;
        }
        sort(houses.begin(), houses.end());
    }
    int install_router(int target) {
        int left = 1;
        int right = (houses[quantity - 1] - houses[0]) / (target - 1);
        while(left <= right) {
            int mid = (left + right) >> 1;
            int previous_house = houses[0];
            int installed = 1;
            int maximum_available = houses[quantity - 1] - (target - 1 - installed) * mid;
            for(const int house: houses) {
                if(house - previous_house < mid) {continue;}
                if(maximum_available < house) {
                    right = mid - 1;
                    break;
                }
                previous_house = house;
                ++installed;
                maximum_available += mid;
                if(target <= installed) {
                    left = mid + 1;
                    break;
                }
            }
        }
        return right;
    }
};

int main() {
    // initiate fast io
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int houses, routers;
    cin >> houses >> routers;
    Town town{houses};
    town.read_input();
    cout << town.install_router(routers);
    return 0;
}