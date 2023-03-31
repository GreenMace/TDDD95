#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <set>
#include <iomanip>

int findSide(std::pair<double, double> p1, std::pair<double, double> p2, std::pair<double, double> p) {
    int val = (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0) {
        return 1;
    }

    if (val < 0) {
        return -1;
    }

    return 0;   
}

double lineDist(std::pair<double, double> p1, std::pair<double, double> p2, std::pair<double, double> p) {
    return abs((p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first));
}

void quickHull(std::set<std::pair<double, double>> &hull, std::vector<std::pair<double, double>> &points, 
                std::pair<double, double> p1, std::pair<double, double> p2, int side) {
    int ind = -1;
    double max_dist = 0;
    for (int i = 0; i < points.size(); ++i) {
        double temp = lineDist(p1, p2, points[i]);
        if (findSide(p1, p2, points[i]) == side && temp > max_dist) {
            ind = i;
            max_dist = temp;
        }
    }

    if (ind == -1) {
        hull.insert(p1);
        hull.insert(p2);
        return;
    }

    quickHull(hull, points, points[ind], p1, -findSide(points[ind], p1, p2));
    quickHull(hull, points, points[ind], p2, -findSide(points[ind], p2, p1));
}

std::set<std::pair<double, double>> calcHull(std::vector<std::pair<double, double>> &points) {
    if (points.size() < 3) {
        return {};
    }

    int minX  = 0, maxX = 0;
    for (int i = 1; i < points.size(); ++i) {
        if (points[i].first < points[minX].first) {
            minX = i;
        }
        
        if (points[i].first > points[maxX].first) {
            maxX = i;
        }
    }

    std::set<std::pair<double, double>> hull;
    quickHull(hull, points, points[minX], points[maxX], 1);
    quickHull(hull, points, points[minX], points[maxX], -1);
    
    return hull;
}

double calcAngle(std::pair<double, double> origo, std::pair<double, double> p1, std::pair<double, double> p2) {
    p1 = {p1.first - origo.first, p1.second - origo.second};
    p2 = {p2.first - origo.first, p2.second - origo.second};

    return atan2(p1.first*p2.second - p1.second*p2.first, p1.first*p2.first + p1.second * p2.second);
}

std::vector<std::pair<double, double>> sortHull(std::set<std::pair<double, double>> points) {
    double meanX = 0, meanY = 0;
    for (auto p : points) {
        meanX += p.first;
        meanY += p.second;
    }

    meanX /= points.size();
    meanY /= points.size();
    
    std::vector<std::pair<double, double>> hull = {*(points.begin())};
    points.erase(points.begin());

    while(!points.empty()) {
        double angle = -1;
        std::pair<double, double> closest;
        for (auto p : points) {
            double v = calcAngle({meanX, meanY}, hull.back(), p);
            if (v > 0 && (angle == -1 || v < angle)) {
                closest = p;
                angle = v;
            }
        }
        hull.push_back(closest);
        points.erase(closest);
    }
    
    return hull;
    
}

double polyArea2D(std::vector<std::pair<double, double>> hull) {
    double area = 0.0;

    for (int i = 0; i < hull.size(); ++i) {
       int j = (i + 1)%hull.size();
       area += 0.5 * (hull[i].first*hull[j].second -  hull[j].first*hull[i].second);
    }

    return (area);
}

int main(int argc, char const *argv[]) {
    int N, n;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        std::cin >> n;

        std::vector<std::pair<double, double>> points;
        double boardArea = 0;
        double x, y, w, h, v;
        for (int j = 0; j < n; ++j) {
            std::cin >> x >> y >> w >> h >> v;
            boardArea += w * h;

            v *= M_PI / 180;

            points.push_back({x + cos(v)*w/2 + sin(v)*h/2, y + cos(v)*h/2 - sin(v)*w/2}); //Top right
            points.push_back({x + cos(v)*w/2 - sin(v)*h/2, y - cos(v)*h/2 - sin(v)*w/2}); //Bottom right
            points.push_back({x - cos(v)*w/2 + sin(v)*h/2, y + cos(v)*h/2 + sin(v)*w/2}); //Top left
            points.push_back({x - cos(v)*w/2 - sin(v)*h/2, y - cos(v)*h/2 + sin(v)*w/2}); //Bottom left
        }

        double totalArea = 0;
        std::set<std::pair<double, double>> hull = calcHull(points);
        std::vector<std::pair<double, double>> sortedHull = sortHull(hull);

        std::cout << std::fixed;
        std::cout << std::setprecision(1);
        std::cout << boardArea / polyArea2D(sortedHull) * 100 << " %\n";
    }
    
    return 0;
}
