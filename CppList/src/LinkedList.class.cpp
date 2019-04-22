#include "LinkedList.class.hpp"

template<typename T>
Node<T>::Node(const T& data) : data(data), next(nullptr)
{}

template<typename T>
Node<T>::~Node(void)
{
    data = 0;
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
    Node<T>* tmp = lst->next;

    if (!lst) return;
    m_head = tmp;
    delete lst;
}

template<typename T>
void List<T>::Insert(unsigned index, const T& data)
{
    Node<T>* lst = m_head;
    Node<T>* prev;

    if (index > Size()) return;
    if (index == 0)
    {
        Node<T>* tmp = new Node<T>(data);
        tmp->next = lst;
        m_head = tmp;
        return;
    }
    while (lst)
    {
        if (index == 0 || index > Size()) break;
        prev = lst;
        lst = lst->next;
        index--;
    }
    Node<T>* tmp = new Node<T>(data);
    prev->next = tmp;
    tmp->next = lst;
}

template<typename T>
void List<T>::Remove(unsigned index)
{
    Node<T>* lst = m_head;
    Node<T>* prev;

    if (index >= Size()) return;
    while (lst)
    {
        if (index == 0 || index >= Size())
            break;
        prev = lst;
        lst = lst->next;
        index--;
    }
    Node<T>* tmp = lst->next;
    prev->next = tmp;
    delete lst;
}

template<typename T>
void List<T>::Clear(void)
{
    Node<T>* lst = m_head;
    Node<T>* tmp;

    while (lst)
    {
        tmp = lst;
        delete lst;
        lst = tmp->next;
    }
    m_head = nullptr;
}

template<typename T>
T& List<T>::GetNode(unsigned index) const
{
    Node<T>* lst = m_head;

    if (index >= Size()) return lst->data;
    while (lst)
    {
        if (index == 0 || index > Size())
            return lst->data;
        lst = lst->next;
        index--;
    }
    return lst->data;
}

template<typename T>
unsigned List<T>::Size(void) const
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

template<typename T>
bool List<T>::Empty(void) const
{
    if (m_head) return false;
    return true;
}

template<typename T>
std::ostream&    operator<<(std::ostream& o, const List<T>& i)
{
    Node<T>* lst = i.m_head;
    o << "List Size: " << i.Size() << std::endl;
    while (lst)
    {
        o << *lst << std::endl;
        lst = lst->next;
    }
    return o;
}

template struct							Node<int>;
template class							List<int>;
template struct							Node<float>;
template class							List<float>;
