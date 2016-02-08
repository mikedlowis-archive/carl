// Unit Test Framework Includes
#include "atf.h"

// File To Test
#include <data/list.h>

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(List) {
    //-------------------------------------------------------------------------
    // list_init
    //-------------------------------------------------------------------------
    TEST(Verify_list_init_initializesr_the_list)
    {
        list_t list;
        list_init(&list);
        CHECK(list.head == NULL);
    }

    //-------------------------------------------------------------------------
    // list_empty
    //-------------------------------------------------------------------------
    TEST(Verify_list_empty_returns_true_when_list_is_empty)
    {
        list_t list = { NULL };
        CHECK(true == list_empty(&list));
    }

    TEST(Verify_list_empty_returns_false_when_list_is_not_empty)
    {
        list_t alist = { (list_node_t*)0x1234 };
        CHECK(false == list_empty(&alist));
    }

    //-------------------------------------------------------------------------
    // list_size
    //-------------------------------------------------------------------------
    TEST(Verify_list_size_should_return_0)
    {
        list_t list = { 0 };
        CHECK(0 == list_size(&list));
    }

    TEST(Verify_list_size_should_return_1)
    {
        list_node_t node = { NULL };
        list_t list = { &node };
        CHECK(1 == list_size(&list));
        CHECK(node.next == NULL);
    }

    TEST(Verify_list_size_should_return_2)
    {
        list_node_t node2 = { NULL };
        list_node_t node1 = { &node2 };
        list_t list = { &node1 };
        CHECK(2 == list_size(&list));
        CHECK(node1.next == &node2);
        CHECK(node2.next == NULL);
    }

    //-------------------------------------------------------------------------
    // list_front
    //-------------------------------------------------------------------------
    TEST(Verify_list_front_should_return_the_head)
    {
        list_node_t node2 = { NULL };
        list_node_t node1 = { &node2 };
        list_t list = { &node1 };
        CHECK(&node1 == list_front(&list));
    }

    //-------------------------------------------------------------------------
    // list_push_front
    //-------------------------------------------------------------------------
    TEST(Verify_list_push_front_should_push_the_node_to_the_head)
    {
        list_node_t node = { NULL };
        list_t list = { 0 };
        list_push_front(&list, &node);
        CHECK(!list_empty(&list));
        CHECK(list.head == &node);
    }

    TEST(Verify_list_front_should_return_the_head_if_only_one_item_in_list)
    {
        list_node_t node = { NULL };
        list_t list = { &node, &node };
        CHECK(&node == list_front(&list));
    }

    TEST(Verify_list_front_should_return_the_first_item_if_two_items_in_list)
    {
        list_node_t node1 = { .next = NULL, .prev = NULL };
        list_node_t node2 = { .next = NULL, .prev = NULL };
        list_t list = { 0 };
        list_push_front(&list, &node2);
        list_push_front(&list, &node1);
        CHECK(&node1 == list_front(&list));
    }

    //-------------------------------------------------------------------------
    // list_pop_front
    //-------------------------------------------------------------------------
    TEST(Verify_list_pop_front_should_do_nothing_if_list_empty)
    {
        list_t list = { NULL };
        CHECK(NULL == list_pop_front(&list));
        CHECK(NULL == list.head);
    }

    TEST(Verify_list_pop_front_should_remove_the_head_element_from_the_list_and_return_it)
    {
        list_node_t node = { NULL };
        list_t list = { &node };
        CHECK(&node == list_pop_front(&list));
        CHECK(list_empty(&list));
        CHECK(list.head == NULL);
    }

    TEST(Verify_list_pop_back_should_remove_the_first_item_in_the_list)
    {
        list_node_t node1 = { 0 };
        list_node_t node2 = { 0 };
        list_t list = { 0 };
        list_push_back(&list, &node1);
        list_push_back(&list, &node2);
        CHECK(&node1 == list_pop_front(&list));
        CHECK(&node2 == list.head);
        CHECK(&node2 == list.tail);
        CHECK(NULL == list.head->next);
    }

    //-------------------------------------------------------------------------
    // list_back
    //-------------------------------------------------------------------------
    TEST(Verify_list_back_should_return_NULL_if_the_list_is_empty)
    {
        list_t list = { NULL };
        CHECK(NULL == list_back(&list));
    }

    TEST(Verify_list_back_should_return_the_head_if_only_one_item_in_list)
    {
        list_node_t node = { NULL };
        list_t list = { &node, &node };
        CHECK(&node == list_back(&list));
    }

    TEST(Verify_list_back_should_return_the_last_item_if_two_items_in_list)
    {
        list_node_t node1 = { .next = NULL, .prev = NULL };
        list_node_t node2 = { .next = NULL, .prev = NULL };
        list_t list = { .head = &node1, .tail = &node2 };
        CHECK(&node2 == list_back(&list));
    }

    //-------------------------------------------------------------------------
    // list_push_back
    //-------------------------------------------------------------------------
    TEST(Verify_list_push_back_should_push_to_the_head)
    {
        list_node_t node = { NULL };
        list_t list = { NULL };
        list_push_back(&list, &node);
        CHECK(&node == list.head);
    }

    TEST(Verify_list_push_back_should_push_to_the_tail)
    {
        list_node_t node1 = { NULL };
        list_node_t node2 = { NULL };
        list_t list = { 0 };
        list_push_back(&list, &node1);
        list_push_back(&list, &node2);
        CHECK(&node2 == list.head->next);
        CHECK(&node2 == list.tail);
        CHECK(&node1 == list.tail->prev);
    }

    //-------------------------------------------------------------------------
    // list_pop_back
    //-------------------------------------------------------------------------
    TEST(Verify_list_pop_back_should_do_nothing_if_list_empty)
    {
        list_t list = { NULL };
        CHECK(NULL == list_pop_back(&list));
        CHECK(NULL == list.head);
    }

    TEST(Verify_list_pop_back_should_remove_the_only_item_in_the_list)
    {
        list_node_t node = { 0 };
        list_t list = { 0 };
        list_push_back(&list, &node);
        CHECK(&node == list_pop_back(&list));
        CHECK(NULL == list.head);
    }

    TEST(Verify_list_pop_back_should_remove_the_last_item_in_the_list)
    {
        list_node_t node1 = { 0 };
        list_node_t node2 = { 0 };
        list_t list = { 0 };
        list_push_back(&list, &node1);
        list_push_back(&list, &node2);
        CHECK(&node2 == list_pop_back(&list));
        CHECK(&node1 == list.head);
        CHECK(NULL == list.head->next);
    }

    //-------------------------------------------------------------------------
    // list_node_has_next
    //-------------------------------------------------------------------------
    TEST(Verify_list_has_next_should_return_false_if_null)
    {
        list_node_t node = { .next = NULL };
        CHECK(!list_node_has_next(&node));
    }

    TEST(Verify_list_has_next_should_return_false_if_not_null)
    {
        list_node_t node = { .next = (list_node_t*)0x1234 };
        CHECK(list_node_has_next(&node));
    }

    //-------------------------------------------------------------------------
    // list_node_next
    //-------------------------------------------------------------------------
    TEST(Verify_list_node_next_should_return_the_next_node)
    {
        list_node_t node = { .next = (list_node_t*)0x1234 };
        CHECK((list_node_t*)0x1234 == list_node_next(&node));
    }

    //-------------------------------------------------------------------------
    // list_node_has_prev
    //-------------------------------------------------------------------------
    TEST(Verify_list_has_prev_should_return_false_if_null)
    {
        list_node_t node = { .prev = NULL };
        CHECK(!list_node_has_prev(&node));
    }

    TEST(Verify_list_has_prev_should_return_false_if_not_null)
    {
        list_node_t node = { .prev = (list_node_t*)0x1234 };
        CHECK(list_node_has_prev(&node));
    }

    //-------------------------------------------------------------------------
    // list_node_prev
    //-------------------------------------------------------------------------
    TEST(Verify_list_node_prev_should_return_the_prev_node)
    {
        list_node_t node = { .prev = (list_node_t*)0x1234 };
        CHECK((list_node_t*)0x1234 == list_node_prev(&node));
    }
}

