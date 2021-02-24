#include<iostream>
#include<algorithm>
#include<list>
#include<string>
using namespace std;

class point
{
    public:
        float x;
        float y;
        float RGB[3];
        string name;

        point(float xx, float yy, int r, int g, int b, string namee)
        {
            x = xx; y = yy; RGB[0] = r; RGB[1] = g, RGB[2] = b; name = namee;
        }

        point()
        {
            x,y,RGB[0],RGB[1],RGB[2] = 0; name = "a";
        }

        float calculateLuminity() const
        {
            return RGB[0] * 0.3 + RGB[1] * 0.59 + RGB[2] * 0.1;
        }

        friend ostream& operator<<(ostream& os, point inp)
        {
            return os << inp.name << " " << inp.x << " " << inp.y << " [" << inp.RGB[0] << ","  << inp.RGB[1] << "," << inp.RGB[2] << "]" << '\n';
        }
};

void write(list<point>& inp)
{
    for(auto x : inp)
    {
        cout << x << endl;
    }
}

void embellishName(list<point>& inp)
{
    inp.erase(remove_if(inp.begin(), inp.end(), [] (point& a) {return a.name.size() > 5; }), inp.end());
    write(inp);
}

void countQuarter(list<point>& inp)
{
    int I = 0; int II = 0; int III = 0; int IV = 0;
    for_each(inp.begin(), inp.end(), [&] (point& a) {
        if(a.x > 0)
            a.y > 0 ? I++ : IV++;
        else
            a.y > 0 ? II++ : III++;
    });
}

void sortLuminity(list<point>& inp)
{
    inp.sort([] (point a, point b) {return a.calculateLuminity() < b.calculateLuminity(); });
    write(inp);
}

void moveDark(list<point>& inp)
{
    list<point> copied(inp.size());
    copy_if(inp.begin(), inp.end(), copied.begin(), [] (point& a) {return a.calculateLuminity() < 64; });
    cout << "Number of dark points: " << copied.size() << '\n';
    write(copied);
}

int main()
{
    list<point> test;
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 100,200,40, "smietnik"));
    test.push_back(point(1, 1, 200, 100, 2, "p"));
    test.push_back(point(1, -1, 0, 0, 2, "ad"));
    test.push_back(point(-1, 1, 0, 100, 7, "awda"));
    test.push_back(point(-1,-1, 200,100,80, "awdwd"));

    embellishName(test);
    cout << endl << endl << endl;

    sortLuminity(test);
    cout << endl << endl << endl;

    countQuarter(test);
    cout << endl << endl << endl;

    moveDark(test);
    cout << endl << endl << endl;
}