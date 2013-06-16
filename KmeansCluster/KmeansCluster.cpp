#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <cmath>
#include <set>
#include <list>
#include <vector>

using namespace std;
struct Group;

struct Point
{
    double x;
    double y;
    int groupNumber;
    Point(const double& _x, const double& _y):x(_x), y(_y)
    {}
};

struct Group
{
    Point newPoint;
    Point oldPoint;
    int count;
    Group():newPoint(0, 0), oldPoint(0, 0), count(0)
    {}
};


void updateCenterPoint(list<Point>& ps, Group* Grps, int pc);
void showHotPoint(list<Point>& ps, int pc);
void divPoints(list<Point>&, Group*, int);
double getDistance(const Point& a, const Point& b);

void loadPoints(const string& filepath , list<Point>& ps)
{
    ifstream in(filepath.c_str());
    if (!in.is_open())
    {
        cerr << "打开文件失败" << endl;
        return;
    }
    double x, y;
    while (in >> x && in >> y)
    {
        ps.push_back(Point(x, y));
    }
    in.close();
}

/**
 * @brief KmeansCluster K-means聚类算法
 * @param ps 坐标集(point list)
 * @param pc 热点数(point count)
 */
void KmeansCluster(list<Point>& ps, const int& pc)
{
    if (ps.size() < static_cast<unsigned>(pc))
    {
        cerr << "点的数量低于热点数量" << endl;
        return;
    }

    int step;         //首次取点的步长
    Group Grps[pc];
    step = ps.size()/pc;
    list<Point>::iterator it;

    for(int i = 0; i < pc; i++)
    {
        it = ps.begin();
        std::advance(it, (step*(i+1)-1));
        Grps[i].newPoint = *it;
    }

    for (int i = 0; i < 4; ++i)
    {
        divPoints(ps, Grps, pc);
        updateCenterPoint(ps, Grps, pc);
    }
    showHotPoint(ps, pc);
}


void divPoints(list<Point>& ps, Group* Grps, int pc)
{
    double dis, minDis;
    int minNum;
    int i;
    list<Point>::iterator it = ps.begin();

    for(i = 0; i < pc; i++)
    {
        Grps[i].count = 0;
    }
    for(; it != ps.end(); ++it)
    {
        minDis = getDistance(Grps[0].newPoint, *it);
        minNum = 0;
        for(i = 1; i < pc; ++i)
        {
            dis = getDistance(Grps[i].newPoint, *it);
            if(dis < minDis)
            {
                minDis = dis;
                minNum = i;
            }
        }
        it->groupNumber = minNum;
        Grps[minNum].count++;
    }
}


/**
 * @brief updateCenterPoint 更新中心点。
 * @param rhs
 */
void updateCenterPoint(list<Point>& ps, Group* Grps, int pc)
{
    list<Point>::iterator it = ps.begin();
    vector<double>xCount(pc);
    vector<double>yCount(pc);
    for(; it != ps.end(); ++it)
    {
        xCount[it->groupNumber] += it->x;
        yCount[it->groupNumber] += it->y;
    }
    for(int i = 0; i < pc; i++)
    {
        Grps[i].oldPoint = Grps->newPoint;
        Grps[i].newPoint = Point(xCount[i]/Grps[i].count,
                                 yCount[i]/Grps[i].count);
    }
}


double getDistance(const Point &a, const Point &b)
{
    return sqrt(pow((a.x - b.x), 2.0) + pow((a.y- b.y), 2.0));
}

void showHotPoint(list<Point>& ps, int pc)
{
    vector<list<Point> >hotpoints(pc);
    list<Point>::iterator it = ps.begin();
    for(; it != ps.end(); ++it)
    {
        hotpoints.at(it->groupNumber).push_back(*it);
    }
    for(unsigned i = 0; i < hotpoints.size(); ++i)
    {
        it = hotpoints.at(i).begin();
        for(; it != hotpoints.at(i).end(); ++it)
        {
            cout << "(" << it->x << ", " << it->y << ") ";
        }
        cout << endl << "-------------------" << endl;
    }
}

int main()
{
    list<Point> s;
    loadPoints("/home/mint/test", s);
    KmeansCluster(s, 10);
    return 0;
}
