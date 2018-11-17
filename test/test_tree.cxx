#include <iostream>
#include <memory>
#include <gtest/gtest.h>

#include <tree.h>

using namespace cubesnake;

TEST(tree, integers)
{
    auto root = std::make_shared<TreeNode<int>>(
            std::move(std::make_unique<int>(0)));
    EXPECT_EQ(root->ReadData(), 0);
    EXPECT_EQ(root->IsRoot(), true);
    EXPECT_EQ(root.use_count(), 1);

    auto node1 = std::make_shared<TreeNode<int>>(root,
            std::move(std::make_unique<int>(1)));
    EXPECT_EQ(node1->ReadData(), 1);
    EXPECT_EQ(node1->IsRoot(), false);
    EXPECT_EQ(node1->GetFather(), root);
    EXPECT_EQ(node1.use_count(), 1);
    EXPECT_EQ(root.use_count(), 2);

    auto node2 = std::make_shared<TreeNode<int>>(node1,
            std::move(std::make_unique<int>(2)));
    auto node3 = std::make_shared<TreeNode<int>>(node1,
            std::move(std::make_unique<int>(3)));
    EXPECT_EQ(node2.use_count(), 1);
    EXPECT_EQ(node3.use_count(), 1);
    EXPECT_EQ(node1.use_count(), 3);
    EXPECT_EQ(node2->IsRoot(), node3->IsRoot());
}
