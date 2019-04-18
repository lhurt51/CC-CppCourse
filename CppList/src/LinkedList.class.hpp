#ifndef LINKED_LIST_HPP
    #define LINKED_LIST_HPP

    #include <iostream>

    template<typename T> struct Node;

    template <typename T>
    struct Node {
        T data;
        Node* next;

        Node(const T& data);
        virtual ~Node(void);

    };

    template <typename T>
    class List {

        Node<T>* m_head;

    public:

        List(void);
        List(const T& data);
        //List(const Node* data);
        virtual ~List(void);

        void Push(const T& data);
        void Pop(void);

        void Insert(unsigned index, const T& data);
        void Remove(unsigned index);
        void Clear(void);

        T& GetNode(unsigned index);
        unsigned Size(void);

        friend std::ostream&    operator<<(std::ostream& o, const List& i) { return o << "Nodes: " << i ; };

    };



#endif /* end of include guard:  */
