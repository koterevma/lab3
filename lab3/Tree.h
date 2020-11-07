#pragma once
#include <functional>
#include <exception>
#include <string>

#include <iostream>

class TreeException : public std::exception
{
	std::string _error;
public:
	TreeException(std::string error);
	char* what();
};

template <class T, typename U = std::less<void>>
class Tree
{
public:
	Tree() noexcept;
	Tree(const Tree<T, U>& cop);
	Tree(Tree<T, U>&& per) noexcept;

	void add(const T& val);
	void add(Tree<T, U> cop);
	bool find(const T& val) noexcept;
	Tree<T, U> subTree(const T& val) const;
	void delSubTree(const T& val);
	void del_elem(T val);

	template <class T1, typename U1>
	friend std::ostream& operator<< (std::ostream& os, const Tree<T1, U1>& tree);
	void lpk(std::ostream& os = std::cout) const;

	~Tree();

	struct Root
	{
		T _value;
		Root* _left;
		Root* _right;
		Root(const T& val);
	};

	typedef Tree<T, U>::Root* pRoot;

protected:
	U u;
	pRoot _root;

	static pRoot recursive_copy(const pRoot& cop);
	void recursive_add(pRoot& root, const T& val);
	static void recursive_del(pRoot& root);
	static void recursive_lpk(pRoot root, std::ostream& os);
	pRoot& recursive_search(pRoot& root, const T& val);
};

template<class T, typename U>
inline Tree<T, U>::Tree() noexcept : _root(nullptr)
{
	u = U();
}

template<class T, typename U>
inline Tree<T, U>::Tree(const Tree<T, U>& cop)
{
	u = U();
	_root = recursive_copy(cop._root);
}

template<class T, typename U>
inline Tree<T, U>::Tree(Tree<T, U>&& per) noexcept
{
	u = U();
	_root = per->_root;
	per->_root = nullptr;
}

template<class T, typename U>
inline void Tree<T, U>::add(const T& val)
{
	recursive_add(_root, val);
}

template<class T, typename U>
inline void Tree<T, U>::add(Tree<T, U> cop)
{
	recursive_search(this->_root, cop._root->_value) = recursive_copy(cop._root);
}

template<class T, typename U>
inline bool Tree<T, U>::find(const T& val) noexcept
{
	return recursive_search(this->_root, val) != nullptr;
}

template<class T, typename U>
inline Tree<T, U> Tree<T, U>::subTree(const T& val) const
{
	Tree<T, U> ret_tree;
	ret_tree._root = recursive_copy(recursive_search(_root, val));
	return ret_tree;
}

template<class T, typename U>
inline void Tree<T, U>::delSubTree(const T& val)
{
	pRoot& found = recursive_search(_root, val);
	if (found == nullptr)
		throw TreeException("Element was not found");
	else
		recursive_del(found);
}

template<class T, typename U>
inline void Tree<T, U>::lpk(std::ostream& os) const
{
	recursive_lpk(_root, os);
}

template<class T, typename U>
inline Tree<T, U>::~Tree()
{
	recursive_del(_root);
}

template<class T, typename U>
typename Tree<T, U>::pRoot Tree<T, U>::recursive_copy(const Tree<T, U>::pRoot& cop)
{
	Tree<T, U>::pRoot ret;
	if (cop != nullptr)
	{
		ret = new Root(cop->_value);
		if (ret == nullptr)
			throw TreeException("Memory error");
		ret->_left = recursive_copy(cop->_left);
		ret->_right = recursive_copy(cop->_right);
	}
	else
		ret = nullptr;
	return ret;
}

template<class T, typename U>
void Tree<T, U>::recursive_add(pRoot& root, const T& val)
{
	if (root == nullptr)
	{
		root = new Root(val);
		if (root == nullptr)
			throw TreeException("Memory error");
	}
	else
	{
		if (u(val, root->_value))
			recursive_add(root->_left, val);
		else
			recursive_add(root->_right, val);
	}
}

template<class T, typename U>
void Tree<T, U>::recursive_del(pRoot& root)
{
	if (root != nullptr)
	{
		recursive_del(root->_left);
		recursive_del(root->_right);
		pRoot deleting = root;
		root = nullptr;
		delete deleting;
	}
}

template<class T, typename U>
void Tree<T, U>::recursive_lpk(pRoot root, std::ostream& os)
{
	if (root != nullptr)
	{
		recursive_lpk(root->_left, os);
		os << root->_value << ' ';
		recursive_lpk(root->_right, os);
	}
}

template<class T, typename U>
typename Tree<T, U>::pRoot&
	Tree<T, U>::recursive_search(typename Tree<T, U>::pRoot& root, const T& val)
{
	if (root != nullptr)
	{
		if (root->_value == val)
			return root;
		else
		{
			if (u(val, root->_value))
				return recursive_search(root->_left, val);
			else
				return recursive_search(root->_right, val);
		}
	}
	else
		return root;
}

template<class T, typename U>
inline Tree<T, U>::Root::Root(const T& val) : _left(nullptr), _right(nullptr), _value(val) {}

template<class T1, typename U1>
inline std::ostream& operator<<(std::ostream& os, const Tree<T1, U1>& tree)
{
	tree.lpk(os);
	return os;
}
