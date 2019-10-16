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
    ASSERT_EQ(kdt.size(), 6);
    cout << "size is :" << kdt.size() << endl;
    cout << "size should be " << "6" << endl;
    cout << "Yunfan debug... after size" << endl;

}

TEST_F(SmallKDTFixture, TEST_NEAREST_POINT) {
    cout << "Yunfan debug... enter TEST_NEAREST_POINT" << endl;
    NaiveSearch naiveSearch;    
    naiveSearch.build(vec);
    Point queryPoint({2.0, 4.5});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    cout << "Yunfan debug... before findNearestNeighbor" << endl;
    Point* ret = kdt.findNearestNeighbor(queryPoint);
    cout << "Yunfan debug.. numDim in ret: " << ret->features << endl;
    closestPoint->setDistToQuery(queryPoint);
    cout << "The right answer is " << closestPoint->distToQuery << endl;
    cout << "Yunfan debug... before Assertion" << endl;
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
    ret->setDistToQuery(queryPoint);
    cout << "distance is : " << ret->distToQuery << endl;
    cout << "Yunfan debug... after Assertion" << endl;
};

class threeKDT : public ::testing::Test {
  protected:
    vector<Point> vec;
    KDT kdt;

  public:
    threeKDT() {
        vec.emplace_back(Point({1.0, 9.5, 10.0}));
        vec.emplace_back(Point({2.0, 9.0, 10.5}));
        vec.emplace_back(Point({3.0, 8.5, 11.0}));
        vec.emplace_back(Point({4.0, 7.0, 11.5}));
        vec.emplace_back(Point({5.0, 7.5, 12.0}));
        vec.emplace_back(Point({6.0, 6.0, 12.5}));
        vec.emplace_back(Point({7.0, 6.5, 13.0}));
        vec.emplace_back(Point({8.0, 5.0, 13.5}));
        vec.emplace_back(Point({9.0, 5.5, 14.0}));
        vec.emplace_back(Point({10.0, 4.0, 14.5}));
        vec.emplace_back(Point({11.0, 4.5, 15.0}));
        vec.emplace_back(Point({12.0, 3.0, 15.5}));
        vec.emplace_back(Point({13.0, 3.5, 16.0}));
        vec.emplace_back(Point({14.0, 2.0, 16.5}));
        vec.emplace_back(Point({15.0, 2.5, 17.0}));
        vec.emplace_back(Point({16.0, 1.0, 17.5}));
        vec.emplace_back(Point({17.0, 1.5, 18.0}));
        vec.emplace_back(Point({18.0, 0.5, 18.5}));
        //vec.emplace_back(Point({4.0, 7.0}));
        cout << "Yunfan debug... before Build" << endl;
        kdt.build(vec);
        cout << "Yunfan debug... after Build" << endl;
        kdt.print();
    }
};

TEST_F(threeKDT, TEST_SIZE) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.size(), 18);
    cout << "size is :" << kdt.size() << endl;
    cout << "size should be " << "18" << endl;
    cout << "Yunfan debug... after size" << endl;

}

TEST_F(threeKDT, TEST_NEAREST_POINT) {
    cout << "Yunfan debug... enter TEST_NEAREST_POINT" << endl;
    NaiveSearch naiveSearch;    
    naiveSearch.build(vec);
    Point queryPoint({2.0, 4.01, 6.0});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    cout << "Yunfan debug... before findNearestNeighbor" << endl;
    Point* ret = kdt.findNearestNeighbor(queryPoint);
    cout << "Yunfan debug.. numDim in ret: " << ret->features << endl;
    closestPoint->setDistToQuery(queryPoint);
    cout << "The right answer is " << closestPoint->distToQuery << endl;
    cout << "Yunfan debug... before Assertion" << endl;
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
    ret->setDistToQuery(queryPoint);
    cout << "distance is : " << ret->distToQuery << endl;
    cout << "Yunfan debug... after Assertion" << endl;
}