#pragma once

#include <functional>
#include <memory>
#include <utility>

// Predicate type
template<typename T>
using SplitPredicate = std::function<bool(const T& value)>;

// Proposed function signature
template<typename T>
class LinkedList
{
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(const T& value) : data(value), next(nullptr) {}
        Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };

    std::unique_ptr<Node> m_head;
    std::size_t m_size = 0;
public:

    LinkedList<T> split_when(SplitPredicate<T> condition);

    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(m_head);
        m_head = std::move(newNode);
        m_size++;
    }

    void push_front(T&& value) {
        auto newNode = std::make_unique<Node>(std::move(value));
        newNode->next = std::move(m_head);
        m_head = std::move(newNode);
        m_size++;
    }

    std::size_t size() const noexcept {
        return m_size;
    }

    bool empty() const noexcept {
        return (m_size == 0);
    }
};