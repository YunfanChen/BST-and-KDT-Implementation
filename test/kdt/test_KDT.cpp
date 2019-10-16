#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "KDT.hpp"
#include "NaiveSearch.hpp"
#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/**
 * A simple test fixture from which multiple tests can
 * be written. The structure of the KDT built from this
 * may vary. See test_BST.cpp for more information on
 * test fixtures.
 */
class SmallKDTFixture : public ::testing::Test {
  protected:
    vector<Point> vec;
    KDT kdt;

  public:
    SmallKDTFixture() {
        vec.emplace_back(Point({7.0, 2.0}));
        vec.emplace_back(Point({5.0, 4.0}));
        vec.emplace_back(Point({9.0, 6.0}));
        vec.emplace_back(Point({2.0, 3.0}));
        vec.emplace_back(Point({4.0, 7.0}));
        vec.emplace_back(Point({8.0, 1.0}));
        //vec.emplace_back(Point({4.0, 7.0}));
        cout << "Yunfan debug... before Build" << endl;
        kdt.build(vec);
        cout << "Yunfan debug... after Build" << endl;
        kdt.print();
    }
};

TEST_F(SmallKDTFixture, TEST_SIZE) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.size(), 5);
    cout << "Yunfan debug... after size" << endl;
}

TEST_F(SmallKDTFixture, TEST_NEAREST_POINT) {
    cout << "Yunfan debug... enter TEST_NEAREST_POINT" << endl;
    NaiveSearch naiveSearch;    
    naiveSearch.build(vec);
    Point queryPoint({5.81, 3.21});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    cout << "Yunfan debug... before findNearestNeighbor" << endl;
    Point* ret = kdt.findNearestNeighbor(queryPoint);
    cout << "Yunfan debug.. numDim in ret: " << ret->features << endl;
    cout << "Yunfan debug... before Assertion" << endl;
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
    ret->setDistToQuery(queryPoint);
    cout << "distance is : " << ret->distToQuery << endl;
    cout << "Yunfan debug... after Assertion" << endl;
}