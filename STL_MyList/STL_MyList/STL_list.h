////////////////////////////////////////////////////////////////////////////////
// list���, �ṩ˫���������
////////////////////////////////////////////////////////////////////////////////
//  --------           --------           --------           --------
//  | next |---------->| next |---------->| next |---------->| next |
//  --------           --------           --------           --------
//  | prev |<----------| prev |<----------| prev |<----------| prev |
//  --------           --------           --------           --------
//  | data |           | data |           | data |           | data |
//  --------           --------           --------           --------
////////////////////////////////////////////////////////////////////////////////

template <class T>
struct __list_node
{
	typedef void* void_pointer;
	void_pointer next;
	void_pointer prev;
	T data;
};

// ����Ϊʲô��ʹ��Ĭ�ϲ���, �������Ϊ��һЩ�����������ṩ�Ƶ�����,
// �������ֲ���ά�����ݴ���, �ʲ�ʹ��Ĭ�ϲ���
template<class T, class Ref, class Ptr>
struct __list_iterator
{
	typedef __list_iterator<T, T&, T*>             iterator;   // STL��׼ǿ��Ҫ��
	typedef __list_iterator<T, Ref, Ptr>           self;

	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	link_type node;   //�������ڲ���ȻҪ��һ����ָͨ�룬ָ��list�Ľڵ�

	__list_iterator(link_type x) : node(x) {}
	__list_iterator() {}
	__list_iterator(const iterator& x) : node(x.node) {}

	// ��STL�㷨����Ҫ�������ṩ֧��
	bool operator==(const self& x) const { return node == x.node; }
	bool operator!=(const self& x) const { return node != x.node; }

	// ���¶Ե�����ȡֵ��dereference��,ȡ���ǽڵ������ֵ
	reference operator*() const { return (*node).data; }

	// �����ǵ������ĳ�Ա��ȡ�����ӵı�׼����
	pointer operator->() const { return &(operator*()); }

	// ǰ׺�Լӣ��Ե������ۼ�1������ǰ��һ���ڵ�
	self& operator++()
	{
		node = (link_type)((*node).next);
		return *this;
	}

	// ��׺�Լ�, ��Ҫ�Ȳ��������һ������, Ȼ���ٶ��������, ��󷵻ظ���
	self operator++(int)
	{
		self tmp = *this;
		++*this;
		return tmp;
	}

	// ǰ׺�Լ�
	self& operator--()
	{
		node = (link_type)((*node).prev);
		return *this;
	}

	self operator--(int)
	{
		self tmp = *this;
		--*this;
		return tmp;
	}
};

////////////////////////////////////////////////////////////////////////////////
// list�����Ǹ�˫������, ���һ���һ����״˫������
////////////////////////////////////////////////////////////////////////////////
//       end()              ͷ���             begin()
//         ��                  ��                  ��
//      --------           --------           --------           --------
// ---->| next |---------->| next |---------->| next |---------->| next |------
// |    --------           --------           --------           --------     |
// |  --| prev |<----------| prev |<----------| prev |<----------| prev |<--| |
// |  | --------           --------           --------           --------   | |
// |  | | data |           | data |           | data |           | data |   | |
// |  | --------           --------           --------           --------   | |
// |  |                                                                     | |
// |  | --------           --------           --------           --------   | |
// ---|-| next |<----------| next |<----------| next |<----------| next |<--|--
//    | --------           --------           --------           --------   |
//    ->| prev |---------->| prev |---------->| prev |---------->| prev |----
//      --------           --------           --------           --------
//      | data |           | data |           | data |           | data |
//      --------           --------           --------           --------
////////////////////////////////////////////////////////////////////////////////

// Ĭ��allocatorΪalloc, �����ʹ�ð汾�����<stl_alloc.h>
template <class T, class Alloc = alloc>
class list
{
protected:
	typedef void* void_pointer;
	typedef __list_node<T> list_node;

	// ר��֮�ռ���������ÿ������һ���ڵ��С
	typedef simple_alloc<list_node, Alloc> list_node_allocator;

public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef list_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef __list_iterator<T, T&, T*>             iterator;

protected:
	link_type node ;     // ֻҪһ��ָ�룬��ɱ�ʾ������״˫������
	// ����һ���½��, ע�����ﲢ�����й���,
	// ���콻��ȫ�ֵ�construct, ��<stl_stl_uninitialized.h>
	link_type get_node() { return list_node_allocator::allocate(); }

	// �ͷ�ָ�����, ����������, ��������ȫ�ֵ�destroy
	void put_node(link_type p) { list_node_allocator::deallocate(p); }

	// ���������ò����죩һ���ڵ�, ���ȷ����ڴ�, Ȼ����й���
	// ע: commit or rollback
	link_type create_node(const T& x)
	{
		link_type p = get_node();
		construct(&p->data, x);
		return p;
	}

	// �������Ԫ��, ���ͷ��ڴ�
	void destroy_node(link_type p)
	{
		destroy(&p->data);
		put_node(p);
	}

protected:
	// ���ڿ�����Ľ���
	void empty_initialize()
	{
		node = get_node();   // ����һ���ڵ�ռ䣬��nodeָ����
		node->next = node;   // ��nodeͷβ��ָ���Լ�������Ԫ��ֵ
		node->prev = node;
	}

	// ����ֵΪvalue��n����������
	// ע: commit or rollback
	void fill_initialize(size_type n, const T& value)
	{
		empty_initialize();
		__STL_TRY
		{
			// �˴��������ʱ�临�Ӷ�O(1)
			insert(begin(), n, value);
		}
		__STL_UNWIND(clear(); put_node(node));
	}


public:
	list() { empty_initialize(); }

	iterator begin() { return (link_type)((*node).next); }

	// ����ɻ�, ��ָ����ͷ�ڵ�Ҳ����end
	iterator end() { return node; }

	// ͷ���ָ������˵����������Ԫ��
	bool empty() const { return node->next == node; }

	// ʹ��ȫ�ֺ���distance()���м���, ʱ�临�Ӷ�O(n)
	size_type size() const
	{
		size_type result = 0;
		distance(begin(), end(), result);
		return result;
	}

	size_type max_size() const { return size_type(-1); }
	reference front() { return *begin(); }
	reference back() { return *(--end()); }

	////////////////////////////////////////////////////////////////////////////////
	// ��ָ��λ�ò���Ԫ��
	////////////////////////////////////////////////////////////////////////////////
	//       insert(iterator position, const T& x)
	//                       ��
	//                 create_node(x)
	//                 p = get_node();-------->list_node_allocator::allocate();
	//                 construct(&p->data, x);
	//                       ��
	//            tmp->next = position.node;
	//            tmp->prev = position.node->prev;
	//            (link_type(position.node->prev))->next = tmp;
	//            position.node->prev = tmp;
	////////////////////////////////////////////////////////////////////////////////

	iterator insert(iterator position, const T& x)
	{
		link_type tmp = create_node(x);   // ����һ���ڵ�
		// ����˫��ָ�룬ʹtmp�����ȥ
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(link_type(position.node->prev))->next = tmp;
		position.node->prev = tmp;
		return tmp;
	}

	// ָ��λ�ò���n��ֵΪx��Ԫ��, ��ϸ������ʵ�ֲ���
	void insert(iterator pos, size_type n, const T& x);
	void insert(iterator pos, int n, const T& x)
	{
		insert(pos, (size_type)n, x);
	}
	void insert(iterator pos, long n, const T& x)
	{
		insert(pos, (size_type)n, x);
	}

	// ������ǰ�˲�����
	void push_front(const T& x) { insert(begin(), x); }
	// ��������������
	void push_back(const T& x) { insert(end(), x); }

	// �Ƴ�������position��ָ�ڵ�
	iterator erase(iterator position)
	{
		link_type next_node = link_type(position.node->next);
		link_type prev_node = link_type(position.node->prev);
		prev_node->next = next_node;
		next_node->prev = prev_node;
		destroy_node(position.node);
		return iterator(next_node);
	}

	// ����һ������Ľ��, ��ϸ������ʵ�ֲ���
	iterator erase(iterator first, iterator last);

	void resize(size_type new_size, const T& x);
	void resize(size_type new_size) { resize(new_size, T()); }
	void clear();

	// ɾ�������һ�����
	void pop_front() { erase(begin()); }
	// ɾ���������һ�����
	void pop_back()
	{
		iterator tmp = end();
		erase(--tmp);
	}

	list(size_type n, const T& value) { fill_initialize(n, value); }
	list(int n, const T& value) { fill_initialize(n, value); }
	list(long n, const T& value) { fill_initialize(n, value); }

	~list()
	{
		// �ͷ����н��  // ʹ��ȫ�ֺ���distance()���м���, ʱ�临�Ӷ�O(n)
		size_type size() const
		{
			size_type result = 0;
			distance(begin(), end(), result);
			return result;
		}
		clear();
		// �ͷ�ͷ���
		put_node(node);
	}

	list<T, Alloc>& operator=(const list<T, Alloc>& x);

protected:

	////////////////////////////////////////////////////////////////////////////////
	// ��[first, last)�ڵ�����Ԫ���ƶ���position֮ǰ
	// ���last == position, ���൱�������仯, �����в���
	////////////////////////////////////////////////////////////////////////////////
	// ��ʼ״̬
	//                   first                             last
	//                     ��                                 ��
	//      --------   --------   --------     --------   --------   --------
	//      | next |-->| next |-->| next |     | next |-->| next |-->| next |
	//  ... --------   --------   -------- ... --------   --------   -------- ...
	//      | prev |<--| prev |<--| prev |     | prev |<--| prev |<--| prev |
	//      --------   --------   --------     --------   --------   --------
	//
	//                           position
	//                               ��
	//      --------   --------   --------   --------   --------   --------
	//      | next |-->| next |-->| next |-->| next |-->| next |-->| next |
	//  ... --------   --------   --------   --------   --------   -------- ...
	//      | prev |<--| prev |<--| prev |<--| prev |<--| prev |<--| prev |
	//      --------   --------   --------   --------   --------   --------
	//
	// ������ɺ�״̬
	//                           first
	//                             |
	//               --------------|--------------------------------------
	//               | ------------|------------------------------------ |   last
	//               | |           ��                                   | |     ��
	//      -------- | |        --------   --------     --------       | |  --------   --------
	//      | next |-- |  ----->| next |-->| next |     | next |-----  | -->| next |-->| next |
	//  ... --------   |  |     --------   -------- ... --------    |  |    --------   -------- ...
	//      | prev |<---  |  ---| prev |<--| prev |     | prev |<-- |  -----| prev |<--| prev |
	//      --------      |  |  --------   --------     --------  | |       --------   --------
	//                    |  |                                    | |
	//                    |  ------                               | |
	//                    ------- |  ------------------------------ |
	//                          | |  |                              |
	//                          | |  |  -----------------------------
	//                          | |  |  |
	//                          | |  |  |  position
	//                          | |  |  |     ��
	//      --------   -------- | |  |  |  --------   --------   --------   --------
	//      | next |-->| next |-- |  |  -->| next |-->| next |-->| next |-->| next |
	//  ... --------   --------   |  |     --------   --------   --------   -------- ...
	//      | prev |<--| prev |<---  ------| prev |<--| prev |<--| prev |<--| prev |
	//      --------   --------            --------   --------   --------   --------
	////////////////////////////////////////////////////////////////////////////////
	void transfer(iterator position, iterator first, iterator last)
	{
		if (position != last)   // ���last == position, ���൱�������仯, �����в���
		{
			(*(link_type((*last.node).prev))).next = position.node;
			(*(link_type((*first.node).prev))).next = last.node;
			(*(link_type((*position.node).prev))).next = first.node;
			link_type tmp = link_type((*position.node).prev);
			(*position.node).prev = (*last.node).prev;
			(*last.node).prev = (*first.node).prev;
			(*first.node).prev = tmp;
		}
	}

public:
	// ������x�ƶ���position��ָλ��֮ǰ
	void splice(iterator position, list& x)
	{
		if (!x.empty())
			transfer(position, x.begin(), x.end());
	}

	// ��������iָ��������ƶ���position֮ǰ
	void splice(iterator position, list&, iterator i)
	{
		iterator j = i;
		++j;
		if (position == i || position == j) return;
		transfer(position, i, j);
	}

	// ��[first, last}Ԫ���ƶ���position֮ǰ
	void splice(iterator position, list&, iterator first, iterator last)
	{
		if (first != last)
			transfer(position, first, last);
	}

	void remove(const T& value);
	void unique();
	void merge(list& x);
	void reverse();
	void sort();

};

// �������н��, �������ÿ�
template <class T, class Alloc>
void list<T, Alloc>::clear()
{
	link_type cur = (link_type) node->next;
	while (cur != node)
	{
		link_type tmp = cur;
		cur = (link_type) cur->next;
		destroy_node(tmp);
	}
	// �ָ�nodeԭʼ״̬
	node->next = node;
	node->prev = node;
}

// ����ֵ����
// �����ǰ����Ԫ������x����, ����������Ԫ��,
// ���򽫵���insert����x��ʣ���Ԫ��
template <class T, class Alloc>
list<T, Alloc>& list<T, Alloc>::operator=(const list<T, Alloc>& x)
{
	if (this != &x)
	{
		iterator first1 = begin();
		iterator last1 = end();
		const_iterator first2 = x.begin();
		const_iterator last2 = x.end();
		while (first1 != last1 && first2 != last2) *first1++ = *first2++;
		if (first2 == last2)
			erase(first1, last1);
		else
			insert(last1, first2, last2);
	}
	return *this;
}


// �Ƴ����������е����ڵ��ظ����
// ʱ�临�Ӷ�O(n)
// �û��Զ�������������Ҫ�ṩoperator ==()����
template <class T, class Alloc>
void list<T, Alloc>::unique()
{
	iterator first = begin();
	iterator last = end();
	if (first == last) return;
	iterator next = first;
	while (++next != last)
	{
		if (*first == *next)
			erase(next);
		else
			first = next;
		next = first;
	}
}

// ���赱ǰ������x������, ��֤�������ϲ�����Ȼ����
template <class T, class Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& x)
{
	iterator first1 = begin();
	iterator last1 = end();
	iterator first2 = x.begin();
	iterator last2 = x.end();

	// ע�⣺ǰ���ǣ�����lists���Ѿ���������
	while (first1 != last1 && first2 != last2)
		if (*first2 < *first1)
		{
			iterator next = first2;
			transfer(first1, first2, ++next);
			first2 = next;
		}
		else
			++first1;
	if (first2 != last2)
		transfer(last1, first2, last2);
}