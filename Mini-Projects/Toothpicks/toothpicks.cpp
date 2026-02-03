/* 
* Toothpick representation: (endpoint, endpoint, orientation)
* Tracking next endpoint to add: stack
* 
* add new endpoint:
*   Loop
*       pop next endpoint off the stack
*   Loop while endpoint is not in list of existing endpoints
*   Find endpoints for new toothpick
*   Store endpoints in list for rendering
*   Push endpoints onto stack
*/

#include <vector>
#include <cstdint>

struct Segment {
    int32_t x1, y1;
    int32_t x2, y2;
};

struct Point {
    int32_t x, y;
};

struct EndPoint {
    Point end;
    Point parent;
};

class Pattern{
    public:
        Pattern();
        Segment add_segment();
        void render_pattern();

    private:
        std::vector<EndPoint> end_points;
        std::vector<Point> occupied_points;

        bool is_occupied(Point potential_point);
};

Pattern::Pattern() {
    segments.push_back({0, 1, 0, -1});

    end_points.push_back({{0, -1}, {0, 0}});
    end_points.push_back({{0, 1}, {0, 0}});
}

Segment Pattern::add_segment() {
    do {
        EndPoint point = end_points.back();
        end_points.pop_back();
    } while (is_occupied(point.end));


}

bool Pattern::is_occupled(Point potential_point) {
    for (Point occupied_point : occupied_points) {
        if (potential_point.x == occupied_point.x && potential_point.y == occupied_point.y) {
            return True;
        }
    }
    return False;
}



