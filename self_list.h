#ifndef SELF_LIST_H
#define SELF_LIST_H

#include "node.h"
#include <iostream>

template <typename T>
class SelfList {
    public: 
        enum Method {
            Move, Count, Transpose
        };

    protected:
        Node<T>* head;
        Method method;
        int siz;

    public:
        SelfList(Method method) : method(method),head(nullptr),siz(0) {};

        bool insert(T data) {
                if(size()==0)
                {
                    auto temp = new Node<T>(data);
                    this->head = temp;
                }
                else {
                    auto temp = new Node<T>(data);
                    temp->next = this->head;
                    this->head->prev = temp;
                    this->head = temp;
                }
                this->siz++;
                return true;
        }
             
        bool remove(T data)
        {
            if(this->head == nullptr)throw std::exception();
            auto temp = this->head;
            while(temp != nullptr)
            {
                if(temp->data == data && temp!=this->head && temp->next != nullptr)
                {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                    return true;
                }
                else if(temp == this->head && temp->data == data)
                {
                    this->head = this->head->next;
                    this->head->prev = nullptr;
                    delete temp;
                    return true;
                }
                else if (temp->next == nullptr && temp->data == data)
                {
                    temp->prev->next = nullptr;
                    delete temp;
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }  

        bool find(T data) {
            if(size()==0)throw std::exception();
            auto temp = this->head;
            bool found = false;
            while(temp!=nullptr)
            {
                if(temp->data == data) {
                    found = true;
                    break;
                }
                temp = temp->next;
            }
            if(found) {
                // Está bueno separarlo en métodos, pero deberían ser privados
                switch (this->method)
                {
                    case Move:
                        {
                            _Move(temp);
                            return true;
                        }
                    case Transpose:
                        {
                            _Transpose(temp);
                            return true;
                        }
                    case Count:
                        {
                            _Count(temp);
                            return true;
                        }
                }
            }
            return false;
        }

        T operator [] (int index) {
            if(index >= size())throw std::exception();
            auto temp = this->head;
            for(int i = 0; i< index; i++)
            {
                temp=temp->next;
            }
            return temp->data;
        }
             
        int size() {
            return this->siz;
        }

        void print() {
            if(size()!=0) {
                auto temp = this->head;
                while (temp != nullptr) {
                    std::cout << temp->data << " ";
                    temp = temp->next;
                }
            }
            else
                throw std::exception();
        }

        // t no es un buen nombre :)
        void  _Move(Node<T>* t)
        {
            if(t->prev!=nullptr)
            {
                if(t->next==nullptr)
                {
                    t->prev->next = nullptr;
                    t->next = this->head;
                    this->head->prev = t;
                    t->prev = nullptr;
                    this->head = t;
                }
                else {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    t->next = this->head;
                    this->head->prev = t;
                    t->prev = nullptr;
                    this->head =  t;
                }
            }
        }

        void _Transpose(Node<int>* t)
        {
            if(t->prev !=nullptr)
            {
                T temp = t->prev->data;
                t->prev->data = t->data;
                t->data = temp;
            }
        }

        void _Count(Node<int>* t)
        {
            t->count++;
            bool not_ordered = true;
            while (not_ordered) {
                not_ordered = false;
                auto temp = this->head;
                while(temp->next!=nullptr){
                    if (temp->count < temp->next->count) {
                        int dt = temp->data;
                        int ct = temp->count;
                        temp->data = temp->next->data;
                        temp->next->data = dt;
                        temp->count = temp->next->count;
                        temp->next->count = ct;
                        not_ordered=true;
                    }
                    temp = temp->next;
                }
            }

        }

        ~SelfList() {
            this->head->killSelf();
        }  
};

#endif