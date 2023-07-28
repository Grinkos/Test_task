#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

struct Point {
    double x;
    double y;
};

struct Line {
    Point start;
    Point end;
};

bool InsidePolygon(const std::vector<Point>& poly, const Point& point) {
    int n = poly.size();
    int i, j, c = 0;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((poly[i].y > point.y) != (poly[j].y > point.y)) &&
            (point.x < (poly[j].x - poly[i].x) * (point.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x))
            c = !c;
    }
    return c;
}

bool LineInsidePolygon(const std::vector<Point>& poly, const Line& line) {
    return InsidePolygon(poly, line.start) && InsidePolygon(poly, line.end);
}

bool LinePartiallyInsidePolygon(const std::vector<Point>& poly, const Line& line) {
    return InsidePolygon(poly, line.start) != InsidePolygon(poly, line.end);
}


bool LineType1(const std::vector<Point>& poly, const Line& line) {
    return !InsidePolygon(poly, line.start) && !InsidePolygon(poly, line.end);
}

int main() {
    setlocale(LC_ALL, "ru");
    std::ifstream polysFile("polys.txt");
    std::ifstream linesFile("lines.txt");
    if (!polysFile || !linesFile) {
        std::cerr << "Ошибка: проверьте, создали ли вы файлы polys.txt и lines.txt\n";
        return 1;
    }


    std::string polyLine;
    std::vector<Point> polyPoints;
    while (std::getline(polysFile, polyLine)) {
        std::istringstream iss(polyLine);
        Point point;
        char comma;
        while (iss >> point.x >> comma >> point.y) {
            polyPoints.push_back(point);
        }
    }
    polysFile.close();

    std::ofstream resultsFile("results.txt");

    std::string lineString;
    while (std::getline(linesFile, lineString)) {
        std::istringstream iss(lineString);
        Line line;
        char comma;
        iss >> line.start.x >> comma >> line.start.y >> line.end.x >> comma >> line.end.y;

        if (LineInsidePolygon(polyPoints, line))
            resultsFile << "0\n";
        else if (LineType1(polyPoints, line))
            resultsFile << "1\n";
        else if (LinePartiallyInsidePolygon(polyPoints, line))
            resultsFile << "2\n";
        else
            resultsFile << "3\n";
    }
    linesFile.close();
    resultsFile.close();

    std::cout << "Программа завершила работу! Откройте файл results.txt, чтобы посмотреть результаты расчетов\n";
   
    return 0;
}
