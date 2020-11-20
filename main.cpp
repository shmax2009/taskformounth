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
    };
};
int length(Point point1, Point point2) {
    return sqrt(abs(point1.x - point2.x) * abs(point1.x - point2.x) + abs(point1.y - point2.y) * abs(point1.y - point2.y));
}

typedef vector<vector<Square>> Field;

vector<vector<Square>> initMatrix(int n, int m) {
    Field matrix;
    for (int x = 0; x < n; x++) {
        vector<Square> column;
        for (int y = 0; y < m; y++) {
            Square square;
            square.position.x = x;
            square.position.y = y;
            square.rotate = Null;
            column.push_back(square);
        }
        matrix.push_back(column);
    }

    return matrix;
}


void convertTriangleToSquare(Triangle triangle) {
    //TODO
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
    }
}
// 271 - M1, 500 - M2