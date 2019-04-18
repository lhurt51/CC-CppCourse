#include "LinkedList.class.hpp"

template<typename T>
Node<T>::Node(const T& data) : data(data), next(nullptr)
{}

template<typename T>
Node<T>::~Node(void)
{
    data = nullptr;
    next = nullptr;
}

template<typename T>
List<T>::List(void)
{
    m_head = nullptr;
}

template<typename T>
List<T>::List(const T& data)
{
    m_head = new Node<T>(data);
}

template<typename T>
List<T>::~List(void)
{
    Node<T>* lst = m_head;
    Node<T>* tmp;

    if (!lst) return;
    while (lst)
    {
        tmp = lst->next;
        delete lst;
        lst = tmp;
    }
    m_head = nullptr;
}

template<typename T>
void List<T>::Push(const T& data)
{
    Node<T>* lst = m_head;

    if (!lst)
    {
        m_head = new Node<T>(data);
        return;
    }
    while (lst->next)
        lst = lst->next;
    lst->next = new Node<T>(data);
}

template<typename T>
void List<T>::Pop(void)
{
    Node<T>* lst = m_head;
    Node<T>* prev;

    if (!lst) return;
    while (lst->next)
    {
        prev = lst;
        lst = lst->next;
    }
    prev->next = nullptr;
    delete lst;
}

template<typename T>
void List<T>::Insert(unsigned index, const T& data)
{
    Node<T>* lst = m_head;
    Node<T>* prev;

    if (index >= Size()) return;
    while (lst)
    {

    }
}

template<typename T>
void List<T>::Remove(unsigned index)
{

}

template<typename T>
void List<T>::Clear(void)
{

}

template<typename T>
T& List<T>::GetNode(unsigned index)
{

}

template<typename T>
unsigned List<T>::Size(void)
{
    Node<T>* lst = m_head;
    unsigned size = 0;

    while (lst)
    {
        lst = lst->next;
        size++;
    }
    return size;
}
