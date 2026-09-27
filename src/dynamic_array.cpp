#include <iostream>
namespace MY_DA
{

    template <typename T>
    class dynamic_array
    {
    private:
        T *head = nullptr;
        unsigned int cap = 0;
        unsigned int len = 0;

    public:
        dynamic_array(unsigned int count = 4)
        {
            cap = count <= 4 ? 4 : count;

            head = static_cast<T *>(
                ::operator new(sizeof(T) * cap));

            len = 0;
        }

        ~dynamic_array()
        {
            for (unsigned int i = 0; i < len; ++i)
            {
                head[i].~T();
            }

            ::operator delete(head);
        }

        void grow()
        {
            if (len < cap)
            {
                return;
            }

            unsigned int new_cap = cap * 2;
            T *new_head = static_cast<T *>(
                ::operator new(sizeof(T) * new_cap));

            // 把旧对象移动到新内存
            for (unsigned int i = 0; i < len; ++i)
            {
                new (new_head + i) T(std::move(head[i]));
            }

            // 销毁旧对象
            for (unsigned int i = 0; i < len; ++i)
            {
                head[i].~T();
            }

            // 释放旧内存
            ::operator delete(head);

            head = new_head;
            cap = new_cap;
        }

        void push_back(const T &t)
        {
            grow();
            new (head + len) T(t);
            len++;
        }

        void push_back(T &&t)
        {
            grow();
            new (head + len) T(std::move(t));
            len++;
        }

        T &operator[](unsigned int index)
        {
            return head[index];
        }

        const T &operator[](unsigned int index) const
        {
            return head[index];
        }

        dynamic_array(const dynamic_array &a)
        {
            cap = a.cap;
            len = 0;

            head = static_cast<T *>(
                ::operator new(sizeof(T) * cap));

            for (unsigned int i = 0; i < a.len; ++i)
            {
                new (head + i) T(a.head[i]);
                ++len;
            }
        }

        dynamic_array &operator=(const dynamic_array &a)
        {
            if (this == &a)
                return *this;
            T *new_head = static_cast<T *>(::operator new(sizeof(T) * a.cap));
            for (int i = 0; i < a.len; i++)
            {
                new (new_head + i) T(a.head[i]);
            }
            for (int i = 0; i < a.len; i++)
            {
                head[i].~T();
            }
            ::operator delete(head);

            head = new_head;
            cap = a.cap;
            len = a.len;
            return *this;
        }

        dynamic_array(dynamic_array &&other)
        {
            head = other.head;
            cap = other.cap;
            len = other.len;

            other.head = nullptr;
            other.cap = 0;
            other.len = 0;
        }
        dynamic_array &operator=(dynamic_array &&other)
        {
            if (this == &other)
                return *this;

            for (unsigned int i = 0; i < len; ++i)
            {
                head[i].~T();
            }

            ::operator delete(head);

            head = other.head;
            cap = other.cap;
            len = other.len;
            other.head = nullptr;
            other.cap = 0;
            other.len = 0;
            return *this;
        }
        template<typename... Args>
        void emplace_back(Args&&... args)
        {
            grow();
            new (head + len) T(std::forward<Args>(args)...);
            len++;
        }
    };

};