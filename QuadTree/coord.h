#include <vector>


using namespace std;

struct coord
{
    float x;
    float y;

    coord(){};

    coord(float X, float Y){
        x = X;
        y = Y;
    }
    
    vector<coord> generate(coord c1, coord c2){
        coord high(
                    c1.x > c2.x? c1.x : c2.x,
                    c1.y > c2.y? c1.y : c2.y
                );
        coord low(
                    c1.x > c2.x? c1.x : c2.x,
                    c1.y > c2.y? c1.y : c2.y
                );
        vector<coord> rpt;
        rpt.push_back(low);
        rpt.push_back(high);
        return rpt;
    }
};