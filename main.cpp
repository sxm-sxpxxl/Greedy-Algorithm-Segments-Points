#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#define DEBUG

/*
 * По данным n отрезкам необходимо найти множество точек минимального размера,
 * для которого каждый из отрезков содержит хотя бы одну из точек.
 *
 * В первой строке дано число 1 ≤ n ≤ 100 отрезков.
 * Каждая из последующих n строк содержит по два числа 0 ≤ l ≤ r ≤ 10^9, задающих начало и конец отрезка.
 * Выведите оптимальное число m точек и сами m точек.
 * Если таких множеств точек несколько, выведите любое из них.
 */

using Segment = std::pair<int, int>;

struct segment_less : public std::binary_function<Segment, Segment, bool> {
    bool operator()(const Segment & seg_first, const Segment & seg_second) const {
        return seg_first.first < seg_second.first;
    }
};

int main() {
    int segments_count;

#ifndef DEBUG
    std::cin >> segments_count;

    std::vector<Segment> vec_segments(static_cast<unsigned int>(segments_count));
    for (auto & segment : vec_segments) {
        std::cin >> segment.first >> segment.second;
    }

#else

    std::ifstream file("..\\input.txt");
    file >> segments_count;
    std::vector<Segment> vec_segments(static_cast<unsigned int>(segments_count));
    for (auto & segment : vec_segments) {
        file >> segment.first >> segment.second;
    }

    file.close();
#endif

    std::sort(vec_segments.begin(), vec_segments.end(), segment_less());

    std::vector<int> vec_points;
    int min_point = vec_segments.front().second;
    for (size_t i = 1; i < vec_segments.size(); ) {
        if (vec_segments[i].first <= min_point) {
            if (vec_segments[i].second < min_point) min_point = vec_segments[i].second;
            i++;
        }
        else {
            vec_points.push_back(min_point);
            min_point = vec_segments[i].second;
            i++;
        }
    }
    vec_points.push_back(min_point);

    std::cout << vec_points.size() << std::endl;
    for (auto point : vec_points) {
        std::cout << point << " ";
    }

    return 0;
}