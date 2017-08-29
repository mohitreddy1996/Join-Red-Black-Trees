#ifndef RB_TREE_TEST_H
#define RB_TREE_TEST_H

#include "cppunit/TestFixture.h"
#include "cppunit/TestSuite.h"
#include "cppunit/TestResult.h"
#include "cppunit/TestCaller.h"
#include "cppunit/TestAssert.h"
#include "cppunit/ui/text/TestRunner.h"
#include "rbtree.h"

using namespace std;

class RBTreeTest : public CppUnit::TestFixture {
 public:
    vector<pair<int, int> > inorder_with_color;
    RedBlackTree *rb, *rb1, *rb2;
    void InsertData (int key);
    void InsertDataRB1 (int key);
    void InsertDataRB2 (int key);
    void GetInorderWithColor (RedBlackTree* rb, RedBlackTreeNode *root);
    RBTreeTest();
    ~RBTreeTest();
    void InsertionTest();
    void JoinTest();
    void JoinTest2();
    void JoinTest3();
    CppUnit::TestSuite *Suite();
};


#endif //RB_TREE_TEST_H