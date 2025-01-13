#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};


bool cmpx(const Point &a, const Point &b);
bool cmpy(const Point &a, const Point &b);
double dis(const Point &a, const Point &b);
double merge(vector<Point> &strip, double d);
double solve(vector<Point> &points, int left, int right);


int main() {
    int N;
    while (cin >> N && N != 0) {
        vector<Point> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        sort(points.begin(), points.end(), cmpx);
        double result = solve(points, 0, points.size());
        printf("%.2f\n", result / 2);
    }
    return 0;
}



bool cmpx(const Point &a, const Point &b) {
    return a.x < b.x;
}


bool cmpy(const Point &a, const Point &b) {
    return a.y < b.y;
}


double dis(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


double merge(vector<Point> &strip, double d) {
    double minDist = d;
    int size = strip.size();
    
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = min(minDist, dis(strip[i], strip[j]));
        }
    }
    
    return minDist;
}


double solve(vector<Point> &points, int left, int right) {
    if (right - left <= 3) {
        double minDist = 2e9;
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                minDist = min(minDist, dis(points[i], points[j]));
            }
        }
        return minDist;
    }

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    double dl = solve(points, left, mid);
    double dr = solve(points, mid, right);

    double d = min(dl, dr);

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), cmpy);

    return min(d, merge(strip, d));
}