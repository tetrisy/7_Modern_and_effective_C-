#pragma once

#include <functional>
#include <initializer_list>
#include <memory>
#include <ranges>
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
    LinkedList() = default;
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    LinkedList(std::initializer_list<T> init) {
        for (const T& val : std::views::reverse(init)) {
            push_front(val);
        }
    }

    LinkedList(LinkedList&& other) noexcept {
        m_head = std::move(other.m_head);
        m_size = std::move(other.m_size);
        other.m_size = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            m_head = std::move(other.m_head);
            m_size = std::move(other.m_size);
            other.m_size = 0;
        }

        return *this;
    }

    ~LinkedList() {
        clear();
    }

    LinkedList<T> split_when(SplitPredicate<T> condition) {
        LinkedList<T> newList;

        if (!m_head) {
            return newList;
        }

        if (condition(m_head->data)) {
            newList.m_head = std::move(m_head);
            newList.m_size = std::move(m_size);
            m_size = 0;

            return newList;
        }

        Node* current = m_head.get();
        std::size_t index = 1;

        while (current->next != nullptr) {
            if (condition(current->next->data)) {
                newList.m_head = std::move(current->next);
                newList.m_size = m_size - index;
                this->m_size = index;
            }
            else {
                current = current->next.get();
                index++;
            }
        }

        return newList;
    }

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

    void pop_front() {
        if (m_size != 0) {
            m_head = std::move(m_head->next);
            m_size--;
        }
    }

    std::size_t size() const noexcept {
        return m_size;
    }

    bool empty() const noexcept {
        return (m_size == 0);
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    T& front() {
        return m_head->data;
    }

    const T& front() const {
        return m_head->data;
    }

    class Iterator {
    private:
        Node* m_current;
    public:
        Iterator(Node* node) : m_current(node) {}

        T& operator*() const {
            return m_current->data;
        }

        Iterator& operator++() {
            m_current = m_current->next.get();
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return (m_current != other.m_current);
        }
    };

    Iterator begin() const {
        return Iterator(m_head.get());
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};