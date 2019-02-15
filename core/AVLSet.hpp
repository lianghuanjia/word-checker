// AVLSet.hpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.  The balancing is actually optional,
// with a bool parameter able to be passed to the constructor to explicitly
// turn the balancing on or off (on is default).  If the balancing is off,
// the AVL tree acts like a binary search tree (e.g., it will become
// degenerate if elements are added in ascending order).
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to implement your AVL tree
// using your own dynamically-allocated nodes, with pointers connecting them,
// and with your own balancing algorithms used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <functional>
#include "Set.hpp"
#include <algorithm>


template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet() noexcept;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;


private:
    // You'll no doubt want to add member variables and "helper" member
    // functions here.
    
    struct AVL_Node
    {
    ElementType data;
    AVL_Node* left;
    AVL_Node* right;
    };

    int total_size;

    bool supposedBalance;

    AVL_Node* root;

    int get_height( AVL_Node* current) const ;

    bool IsIn(const ElementType& data, AVL_Node* current) const;   

    AVL_Node* single_right(AVL_Node* current); // LL
    
    AVL_Node* single_left(AVL_Node* current); // single_left_ro
    
    int get_balance(AVL_Node* current);

    AVL_Node* insert_helper(AVL_Node* current, const ElementType& data);

    void copy_helper(AVL_Node* current, const AVL_Node* src);

    void delete_helper(AVL_Node* current);

    void preorder_helper(AVL_Node* current, VisitFunction visit) const;

    void inorder_helper(AVL_Node* current, VisitFunction visit) const;

    void postorder_helper(AVL_Node* current, VisitFunction visit) const;

};

//-------------------------------------------------------------------------------------------------

template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
{
    if (shouldBalance == true)
        supposedBalance = true;
    else
        supposedBalance = false;
    root = nullptr;
    total_size = 0;
}


template <typename ElementType>
void AVLSet<ElementType>::delete_helper(AVL_Node* current)
{
if (current == nullptr)
    {
    return;
    }
else
    {
    delete_helper(current -> right);
    delete_helper(current -> left);
    delete current;
    }

}



template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
    delete_helper(root);
}

template<typename ElementType>
void AVLSet<ElementType>::copy_helper(AVL_Node* current, const AVL_Node* src)
{

    if (src == nullptr)
        current = nullptr;
    else
    {
        current = new AVL_Node{src -> data};
        total_size += 1;
        if (src -> right == nullptr && src -> left == nullptr)
            return;
        else
            {
                if (src -> right == nullptr && src -> left != nullptr)
                {
                current -> right = nullptr;
                copy_helper(current -> left, src -> left);
                }
                else if (src -> left == nullptr && src -> right != nullptr)
                {
                current -> left = nullptr;
                copy_helper(current -> right,src -> right);
                }
                else
                {
                copy_helper(current -> right, src -> right);
                copy_helper(current -> left, src -> left);
                }
            }
    }

}
//niralee

template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
{
    if (s.root == nullptr)
    {
    root = nullptr;
    total_size = 0;
    supposedBalance = s.supposedBalance;
    }
    else
    root = nullptr;
    total_size = 0;
    //should I initialize the supposedBalance as true first or just leave it?
    copy_helper(root, s.root);
    supposedBalance = s.supposedBalance;
    // in here, should I copy the total_size and supposedBalance too?
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
{
    root = nullptr;
    total_size = 0;
    //should I initialize the balance as true? What value should it be ? true or first when initialized?
    std::swap(root, s.root);
    std::swap(total_size, s.total_size);
    std::swap(supposedBalance, s.supposedBalance);
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    delete_helper(root);
    total_size = 0;
    root = nullptr;
    copy_helper(root, s.root);
    supposedBalance = s.supposedBalance;
    return *this;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
    std::swap(root, s.root); 
    std::swap(total_size, s.total_size);
    std::swap(supposedBalance, s.supposedBalance);
    return *this;
}


template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}

template <typename ElementType>
typename AVLSet<ElementType>::AVL_Node* AVLSet<ElementType>::single_right(AVL_Node* current) // LL
    {
        AVL_Node* x = current -> left;
        AVL_Node* T2 = x -> right;

        //rotation
        x -> right = current;
        current -> left = T2;

        return x;
    }

template <typename ElementType>
typename AVLSet<ElementType>::AVL_Node* AVLSet<ElementType>::single_left(AVL_Node* current) // single_left_ro
    {   
        AVL_Node* y = current -> right;
        AVL_Node* T2 = y -> left;

        y -> left = current;
        current -> right = T2;

        return y;
    }




template <typename ElementType>
int AVLSet<ElementType>::get_balance(AVL_Node* current)
{
    int gap = 0;
    if (current == nullptr)
        return 0;
    else if (current -> left == nullptr && current -> right != nullptr)
        {
        gap = get_height(current -> left) - (get_height(current -> right) + 1);
        }
    else if (current -> left != nullptr && current -> right == nullptr)
        {
        gap = (get_height(current -> left) + 1) - (get_height(current -> right));
        }
    else
        {
        gap = (get_height(current -> left)+1) - (get_height(current -> right)+1);
        }
    return gap;
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{
    if (contains(element) == true)
        return;
    root = insert_helper(root, element);
}


template <typename ElementType>
typename AVLSet<ElementType>::AVL_Node* AVLSet<ElementType>::insert_helper(AVL_Node* current, const ElementType& data)
    //use this in add. BE CAREFUL, in the add, need to examine if the data is existed or not.
    {
    if (current == nullptr)
        {
        AVL_Node* new_node = new AVL_Node;
        new_node -> data = data;
        new_node -> right = nullptr;
        new_node -> left = nullptr;
        ++total_size;
        return new_node;
        }
    else if (data < current -> data)
        current -> left = insert_helper(current -> left , data);
    else  //(data > current -> data)
        current -> right = insert_helper(current -> right, data);
    //    return current;//the data has existed.
    if (supposedBalance == true)
    {
        int balance = get_balance(current);

        if (balance > 1 && (data < (current -> left -> data))) // left height is greater than right height
            {
                return single_right(current);
            }
        else if (balance < -1 && (data > (current -> right -> data)))
            {
                return single_left(current);
            }   
        else if(balance > 1 && (data > (current -> left -> data)))
            {
                current -> left = single_left(current -> left);
                return single_right(current);
            }
        else if(balance < -1 && (data < (current -> right -> data)))
            {
                current -> right = single_right(current -> right);
                return single_left(current);
            }
        return current;

    }
    else
        return current;
    }




template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
    bool result =  IsIn(element, root);
    return result;
}


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    return total_size;
}


template <typename ElementType>
int AVLSet<ElementType>::height() const
{
    if (root == nullptr)
        return -1;
    else
    {
        int result = get_height(root);
        return result;
    }
}


template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
    preorder_helper(root, visit);
}


template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    inorder_helper(root, visit);
}


template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    postorder_helper(root, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::preorder_helper(AVL_Node* current, VisitFunction visit) const
{
    if (current != nullptr)
    {
    visit(current -> data);
    preorder_helper(current -> left, visit);
    preorder_helper(current ->right, visit);
    }
}

template <typename ElementType> 
void AVLSet<ElementType>::inorder_helper(AVL_Node* current, VisitFunction visit) const
{
    if (current != nullptr)
    {
    inorder_helper(current -> left, visit);
    visit(current -> data);
    inorder_helper(current -> right, visit);
    }
}

template <typename ElementType>
void AVLSet<ElementType>::postorder_helper(AVL_Node* current, VisitFunction visit) const
{
    if (current != nullptr)
    {
    postorder_helper(current -> left, visit);
    postorder_helper(current -> right, visit);
    visit(current -> data);
    }
}

//int get_height(const AVL_Node* current);

template <typename ElementType>
int AVLSet<ElementType>::get_height( AVL_Node* current) const //what if the current is nullptr
{
    int l;
    int r;
    if (current == nullptr)
        return 0;
    else if (current -> left == nullptr && current -> right == nullptr)
        return 0;
    else
        {
        if (current -> left == nullptr)
            {
            l = 0;
            r = get_height(current -> right);
            }
        else if (current -> right ==  nullptr)
            {
            r = 0;
            l = get_height(current -> left);
            }
        else
            l = get_height(current -> left);
            r = get_height(current -> right);
        if (l < r)
            return r + 1;
        else
            return l + 1;
        }

}

template <typename ElementType>
bool AVLSet<ElementType>::IsIn(const ElementType& data,  AVL_Node* current) const
{
    if (current == nullptr)
        return false;
    else if ((current != nullptr) && (current -> data == data))
            return true;
    else if ((current != nullptr) && (data > (current -> data)))
        return IsIn(data, current -> right);
    else if ((current != nullptr) && (data < (current -> data)))
        return IsIn(data, current -> left);
    else
        return false;
}






#endif // AVLSET_HPP

