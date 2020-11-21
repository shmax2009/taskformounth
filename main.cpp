#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

enum Superposition {
    Null, Right /* '--- / ---' */, Left /* '--- \ ---' */
};

enum Color {
    Red, Blue
};

class Point {
public:
    int x;
    int y;

    friend istream &operator>>(istream &in, Point &point) {
        in >> point.x >> point.y;
        return in;
    };
};

struct Square {
    Point position;
    Superposition rotate;
    // color of upper triangle
    Color upperTriangle;
    // color of lower triangle
    Color lowerTriangle;
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

typedef vector<vector<Square>> Field;

Field initMatrix(int n, int m) {
    Field matrix;
    for (int y = 0; y < n; y++) {
        vector<Square> row;
        for (int x = 0; x < m; x++) {
            Square square;
            square.position.x = x;
            square.position.y = y;
            square.rotate = Null;
            row.push_back(square);
        }
        matrix.push_back(row);
    }

    return matrix;
}

double crossProduct(Point a, Point b) {
    return (double)(a.x) * b.y - (double)(a.y) * b.x;
}

Point makeVector(Point a, Point b) {
    return { b.x - a.x, b.y - a.y };
}

bool isPointInTriangle(Triangle triangle, Point point) {
    Point a = triangle.point1;
    Point b = triangle.point2;
    Point c = triangle.point3;

    Point ab = makeVector(a, b);
    Point bc = makeVector(b, c);
    Point ca = makeVector(c, a);

    Point ap = makeVector(a, point);
    Point bp = makeVector(b, point);
    Point cp = makeVector(c, point);

    double abp = crossProduct(ab, ap);
    double bcp = crossProduct(bc, bp);
    double cap = crossProduct(ca, cp);

    return (abp <= 0 && bcp <= 0 && cap <= 0) || (abp >= 0 && bcp >= 0 && cap >= 0);
}

void convertTriangleToSquare(Field &field, Triangle triangle) {
    for (int y = 0; y < field.size(); y++) {
        for (int x = 0; x < field[y].size(); x++) {
            Point LowLeftPoint;
            Point LowRightPoint;
            Point HeightLeftPoint;
            Point HeightRightPoint;

            // находится ли точка в треугольнике
            bool LowLeft;
            bool LowRight;
            bool HeightLeft;
            bool HeightRight;

            LowLeftPoint = {x, y};
            LowRightPoint = {x + 1, y};
            HeightLeftPoint = {x, y + 1};
            HeightRightPoint = {x + 1, y + 1};

            LowLeft = isPointInTriangle(triangle, LowLeftPoint);
            LowRight = isPointInTriangle(triangle, LowRightPoint);
            HeightLeft = isPointInTriangle(triangle, HeightLeftPoint);
            HeightRight = isPointInTriangle(triangle, HeightRightPoint);
            cout << x << " " << y << endl;
            cout << LowLeft << " " << LowRight << " " << HeightLeft << " " << HeightRight << endl;
            // если точек входит в треугольник <= 2, тогда выходим
            if (((int) LowLeft + (int) LowRight + (int) HeightLeft + (int) HeightRight) <= 2)
                continue;

            // иначе, то-есть >= 3 входят
            if (LowLeft and LowRight and HeightLeft and HeightRight) {
                field[x][y].rotate = Null;
                field[x][y].lowerTriangle = Red;
                field[x][y].upperTriangle = Red;
                continue;
            }
            if (!HeightLeft) {
                field[x][y].rotate = Right;
                field[x][y].lowerTriangle = Red;
                field[x][y].upperTriangle = Blue;
            }
            if (!HeightRight) {
                field[x][y].rotate = Left;
                field[x][y].lowerTriangle = Red;
                field[x][y].upperTriangle = Blue;
            }

            if (!LowLeft) {
                field[x][y].rotate = Right;
                field[x][y].lowerTriangle = Blue;
                field[x][y].upperTriangle = Red;
            }
            if (!LowRight) {
                field[x][y].rotate = Left;
                field[x][y].lowerTriangle = Blue;
                field[x][y].upperTriangle = Red;
            }


        }
    }
}

bool checkSquare(int a) {
    //TODO
}

int main() {
    int n, m;
    cin >> n >> m;
    Field field;
    field = initMatrix(n, m);
    int trianglesCount;
    cin >> trianglesCount;
    for (int i = 0; i < trianglesCount; i++) {
        Triangle triangle;
        cin >> triangle;
        convertTriangleToSquare(field, triangle);
    }

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            cout << x << " " << y << endl;
            if (field[x][y].rotate == Left) {
                cout << "left" << endl;
            } else if (field[x][y].rotate == Right) {
                cout << "right" << endl;

            }
            if (field[x][y].upperTriangle == Red) {
                cout << "Red" << endl;
            } else {
                cout << "Blue" << endl;
            }

            if (field[x][y].lowerTriangle == Red) {
                cout << "Red" << endl;
            } else {
                cout << "Blue" << endl;

            }

        }
    }

}
// 271 - M1, 500 - M2

//https://github.com/shmax2009/taskformounth