#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;
template <typename Data>
/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        cout << "Yunfan debug... before build" << endl;
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
        cout << "Yunfan debug... after build" << endl;
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    cout << "Yunfan debug... before size" << endl;
    bst.insert(10);
    ASSERT_EQ(bst.size(), 6);
    ASSERT_EQ(bst.height(), 2);
    ASSERT_FALSE(bst.empty());
    vector<Data> rtn = bst.inorder();
    delete &rtn;
    BSTNode<Data>* first = bst.first();
    delete first;
    cout << "Yunfan debug... after size" << endl;
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    cout << "Yunfan debug... before SMALL_INSERT_DUPLICATES_TEST" << endl;
    ASSERT_FALSE(bst.insert(3));
    cout << "Yunfan debug... after SMALL_INSERT_DUPLICATES_TEST" << endl;
};
class BSTtest : public ::testing::Test {
  protected:
    BST<std::string> bst;

  public:
    BSTtest() {
        // initialization code here
        cout << "Yunfan debug... before build" << endl;
        vector<std::string> input{"a", "b", "c", "d", "e"};
        insertIntoBST(input, bst);
        cout << "Yunfan debug... after build" << endl;
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(BSTtest, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    cout << "Yunfan debug... before size" << endl;
    ASSERT_EQ(bst.size(), 5);
    cout << "Yunfan debug... after size" << endl;
    ASSERT_FALSE(bst.find("k"));
}

TEST_F(BSTtest, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    cout << "Yunfan debug... before SMALL_INSERT_DUPLICATES_TEST" << endl;
    ASSERT_FALSE(bst.insert("a"));
    cout << "Yunfan debug... after SMALL_INSERT_DUPLICATES_TEST" << endl;
    bst.deleteAll();
}

// TODO: add more BST tests here
