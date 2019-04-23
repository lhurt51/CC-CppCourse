/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 4/20/2019																		*
*																				*
* Assignment Requirement:                                                       *
*                       														*
* Write a class that replicates a NODE in a link-list object. The NODE should   *
* be tested by inserting a item anywhere in the link list and remove a link any *
* where in the link list. Keep it simple and don't forget the header.           *
*																				*
\*******************************************************************************/

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
void List<T>::Insert(Node<T>& n, const T& data)
{
    Node<T>* nextN;
    Node<T>* tmp = new Node<T>(data);

    nextN = n.next;
    n.next = tmp;
    tmp->next = nextN;
}

template<typename T>
void List<T>::Remove(unsigned index)
{
    Node<T>* lst = m_head;
    Node<T>* prev;

    if (index >= Size()) return;
    while (lst)
    {
        if (index == 0 || index >= Size()) break;
        prev = lst;
        lst = lst->next;
        index--;
    }
    Node<T>* tmp = lst->next;
    prev->next = tmp;
    delete lst;
}

template<typename T>
void List<T>::Remove(Node<T>& n)
{
    Node<T>* lst = m_head;
    Node<T>* prev;

    while (lst)
    {
        if (lst == &n)
        {
            Node<T>* tmp = lst->next;
            prev->next = tmp;
            delete lst;
            return;
        }
        prev = lst;
        lst = lst->next;
    }
}

template<typename T>
void List<T>::Clear(void)
{
    Node<T>* tmp;

    while (m_head)
    {
        tmp = m_head;
        delete m_head;
        m_head = tmp->next;
    }
    m_head = nullptr;
}

template<typename T>
Node<T>* List<T>::GetNode(unsigned index) const
{
    Node<T>* lst = m_head;

    if (index >= Size()) return nullptr;
    while (lst)
    {
        if (index == 0 || index >= Size())
            return lst;
        lst = lst->next;
        index--;
    }
    return nullptr;
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
Node<T>& List<T>::operator[](int i)
{
    return *GetNode(i);
}

template struct							Node<int>;
template class							List<int>;
template struct							Node<float>;
template class							List<float>;
