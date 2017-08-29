#include "rb_tree_test.h"

using namespace std;

RBTreeTest::RBTreeTest() {

}

RBTreeTest::~RBTreeTest() {

}

void RBTreeTest::InsertData (int key) {
	rb->InsertData (key);
}

void RBTreeTest::InsertDataRB1 (int key) {
	rb1->InsertData (key);
}

void RBTreeTest::InsertDataRB2 (int key) {
	rb2->InsertData (key);
}

void RBTreeTest::GetInorderWithColor (RedBlackTree* rb, RedBlackTreeNode *root) {
	if (root == rb->nil || root->key == NULL) {
		return;
	}
	GetInorderWithColor (rb, root->left);
  	int value = ((struct RedBlackKey *)(root->key))->key;
	inorder_with_color.push_back (make_pair(value, root->red));
	GetInorderWithColor (rb, root->right);
}

void RBTreeTest::InsertionTest() {
	rb = new RedBlackTree ();
	InsertData (6);
	InsertData (5);
	InsertData (4);
	InsertData (3);
	InsertData (2);
	InsertData (1);
	GetInorderWithColor (rb, rb->GetRoot()->left);
	CPPUNIT_ASSERT (inorder_with_color.size() == 6);
	CPPUNIT_ASSERT (inorder_with_color[0].first == 1 && inorder_with_color[0].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[1].first == 2 && inorder_with_color[1].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[2].first == 3 && inorder_with_color[2].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[3].first == 4 && inorder_with_color[3].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[4].first == 5 && inorder_with_color[4].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[5].first == 6 && inorder_with_color[5].second == 0);
	inorder_with_color.clear();
} 

void RBTreeTest::JoinTest () {
	rb1 = new RedBlackTree();
	rb2 = new RedBlackTree();
	InsertDataRB1 (3);
	InsertDataRB1 (2);
	InsertDataRB1 (1);
	InsertDataRB2 (6);
	InsertDataRB2 (5);
	InsertDataRB2 (4);
	InsertDataRB2 (9);
	InsertDataRB2 (8);
	InsertDataRB2 (7);
	GetInorderWithColor (rb1, rb1->GetRoot()->left);
	CPPUNIT_ASSERT (inorder_with_color.size() == 3);
	CPPUNIT_ASSERT (inorder_with_color[0].first == 1 && inorder_with_color[0].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[1].first == 2 && inorder_with_color[1].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[2].first == 3 && inorder_with_color[2].second == 1);
	
	inorder_with_color.clear();
	GetInorderWithColor (rb2, rb2->GetRoot()->left);
	CPPUNIT_ASSERT (inorder_with_color.size() == 6);
	CPPUNIT_ASSERT (inorder_with_color[0].first == 4 && inorder_with_color[0].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[1].first == 5 && inorder_with_color[1].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[2].first == 6 && inorder_with_color[2].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[3].first == 7 && inorder_with_color[3].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[4].first == 8 && inorder_with_color[4].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[5].first == 9 && inorder_with_color[5].second == 0);
	RedBlackTree* red_black_tree = GetMergedRBTree (rb1, rb2, false);
	inorder_with_color.clear();
	GetInorderWithColor (red_black_tree, red_black_tree->GetRoot ()->left);
	CPPUNIT_ASSERT (inorder_with_color.size() == 9);
	CPPUNIT_ASSERT (inorder_with_color[0].first == 1 && inorder_with_color[0].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[1].first == 2 && inorder_with_color[1].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[2].first == 3 && inorder_with_color[2].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[3].first == 4 && inorder_with_color[3].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[4].first == 5 && inorder_with_color[4].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[5].first == 6 && inorder_with_color[5].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[6].first == 7 && inorder_with_color[0].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[7].first == 8 && inorder_with_color[1].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[8].first == 9 && inorder_with_color[2].second == 0);
}

void RBTreeTest::JoinTest2 () {
	rb1 = new RedBlackTree();
	rb2 = new RedBlackTree();

	InsertDataRB1(1);
	InsertDataRB2(3);
	RedBlackTree* red_black_tree = GetMergedRBTree (rb1, rb2, false);
	GetInorderWithColor (red_black_tree, red_black_tree->GetRoot ()->left);
	CPPUNIT_ASSERT (inorder_with_color.size() == 2);
	CPPUNIT_ASSERT (inorder_with_color[0].first == 1 && inorder_with_color[0].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[1].first == 3 && inorder_with_color[1].second == 0);
}

void RBTreeTest::JoinTest3 () {
	rb1 = new RedBlackTree();
	rb2 = new RedBlackTree();
	InsertDataRB1 (9);
	InsertDataRB1 (8);
	InsertDataRB1 (7);
	InsertDataRB2 (6);
	InsertDataRB2 (5);
	InsertDataRB2 (4);
	InsertDataRB2 (1);
	InsertDataRB2 (2);
	InsertDataRB2 (3);
	GetInorderWithColor (rb1, rb1->GetRoot()->left);
	CPPUNIT_ASSERT (inorder_with_color.size() == 3);
	CPPUNIT_ASSERT (inorder_with_color[0].first == 7 && inorder_with_color[0].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[1].first == 8 && inorder_with_color[1].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[2].first == 9 && inorder_with_color[2].second == 1);
	
	inorder_with_color.clear();
	GetInorderWithColor (rb2, rb2->GetRoot()->left);
	CPPUNIT_ASSERT (inorder_with_color.size() == 6);
	CPPUNIT_ASSERT (inorder_with_color[0].first == 1 && inorder_with_color[0].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[1].first == 2 && inorder_with_color[1].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[2].first == 3 && inorder_with_color[2].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[3].first == 4 && inorder_with_color[3].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[4].first == 5 && inorder_with_color[4].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[5].first == 6 && inorder_with_color[5].second == 0);
	RedBlackTree* red_black_tree = GetMergedRBTree (rb1, rb2, true);
	inorder_with_color.clear();
	GetInorderWithColor (red_black_tree, red_black_tree->GetRoot ()->left);
	CPPUNIT_ASSERT (inorder_with_color.size() == 9);
	CPPUNIT_ASSERT (inorder_with_color[0].first == 1 && inorder_with_color[0].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[1].first == 2 && inorder_with_color[1].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[2].first == 3 && inorder_with_color[2].second == 1);
	CPPUNIT_ASSERT (inorder_with_color[3].first == 4 && inorder_with_color[3].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[4].first == 5 && inorder_with_color[4].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[5].first == 6 && inorder_with_color[5].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[6].first == 7 && inorder_with_color[0].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[7].first == 8 && inorder_with_color[1].second == 0);
	CPPUNIT_ASSERT (inorder_with_color[8].first == 9 && inorder_with_color[2].second == 1);
}

CppUnit::TestSuite* RBTreeTest::Suite() {
	CppUnit::TestSuite *suite_of_tests = new CppUnit::TestSuite;
	suite_of_tests->addTest(new CppUnit::TestCaller<RBTreeTest>("test_add", &RBTreeTest::InsertionTest));
	suite_of_tests->addTest(new CppUnit::TestCaller<RBTreeTest>("test_rb_join1", &RBTreeTest::JoinTest));
	suite_of_tests->addTest(new CppUnit::TestCaller<RBTreeTest>("test_rb_join2", &RBTreeTest::JoinTest2));
	suite_of_tests->addTest(new CppUnit::TestCaller<RBTreeTest>("test_rb_join3", &RBTreeTest::JoinTest3));
	return suite_of_tests;
}

int main () {
	RBTreeTest *rb_tree_test = new RBTreeTest();
	CppUnit::TextUi::TestRunner runner;
	runner.addTest (rb_tree_test->Suite());
	runner.run ();
	return 0;
}