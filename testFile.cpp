#include <iostream>

using namespace std;

class Point {
public:
    int x;
    int y;

    friend istream &operator>>(istream &in, Point &point) {
        in >> point.x >> point.y;
        return in;
    };
};

class Triangle {
public:
    Point point1;
    Point point2;
    Point point3;

    friend istream &operator>>(istream &in, Triangle &triangle) {
        in >> triangle.point1 >> triangle.point2 >> triangle.point3;
        return in;

    };
};

bool res(Triangle triangle, Point point) {
    double xa = triangle.point1.x;
    double ya = triangle.point1.y;
    double xb = triangle.point2.x;
    double yb = triangle.point2.y;
    double xc = triangle.point3.x;
    double yc = triangle.point3.y;
    double yd = point.x;
    double xd = point.x;
    return (((((xd - xa) * (yb - ya) - (yd - ya) * (xb - xa)) * ((xc - xa) * (yb - ya) - (yc - ya) * (xb - xa)) >= 0) &&
            (((xd - xb) * (yc - yb) - (yd - yb) * (xc - xb)) * ((xa - xb) * (yc - yb) - (ya - yb) * (xc - xb)) >= 0) &&
            (((xd - xc) * (ya - yc) - (yd - yc) * (xa - xc)) * ((xb - xc) * (ya - yc) - (yb - yc) * (xa - xc)) >= 0)) ||
            ((((xd - xa) * (yb - ya) - (yd - ya) * (xb - xa)) * ((xc - xa) * (yb - ya) - (yc - ya) * (xb - xa)) <= 0) &&
            (((xd - xb) * (yc - yb) - (yd - yb) * (xc - xb)) * ((xa - xb) * (yc - yb) - (ya - yb) * (xc - xb)) <= 0) &&
            (((xd - xc) * (ya - yc) - (yd - yc) * (xa - xc)) * ((xb - xc) * (ya - yc) - (yb - yc) * (xa - xc)) <= 0)));
}

bool res1(Triangle triangle, Point point) {
    Point ab = makeVector(triangle.point1, triangle.point2);
    Point bc = makeVector(triangle.point2, triangle.point3);
    Point ca = makeVector(triangle.point3, triangle.point1);

    Point ap = makeVector(a, point);
    Point bp = makeVector(b, point);
    Point cp = makeVector(c, point);

    Point abp = crossProduct(ab, ap);
    Point bcp = crossProduct(bc, bp);
    Point cap = crossProduct(ca, cp);

    return (abp <= 0 && bcp <= 0 && cap <= 0) || (abp >= 0 && bcp >= 0 && cap >= 0);
}

Point crossProduct(Point a, Point b) {
    return a.x * b.y -  a.y * b.x;
}

Point makeVector(Point a, Point b) {
    return new Point(b.x - a.x, b.y - a.y);
}

int main() {
    Point point1;
    Point point2;
    Point point3;
    Point selfPoint;
    cin >> point1 >> point2 >> point3 >> selfPoint;
    cout << res1({point1, point2, point3}, selfPoint);
}