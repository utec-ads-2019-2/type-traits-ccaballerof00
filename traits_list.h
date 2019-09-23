#ifndef TRAITS_LIST_H
#define TRAITS_LIST_H

#include "node.h"

template <typename Tr>
class TraitsList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
      
    private:
        Node<T>* head;
        Node<T>* tail;
        Operation cmp;
        int siz;

        bool find(T data, Node<T> **&pointer)
        {
            for(pointer = &this->head; (*pointer)!=nullptr;pointer = &((*pointer)->next))
            {
                if((*pointer)->data ==  data)
                {
                    return true;
                }
            }
            return false;
        }
              
    public:
        TraitsList() : tail(nullptr), head(nullptr), siz(0) {};
             
        bool insert(T data) {
            Node<T>** chunte;
            if(!this->find(data,chunte))
            {
                // Si ya tienes la ubicación en chute (después del find), ya no es necesaria todo esta lógica
                if(size()!=0)
                {
                    auto temp = this->head;
                    auto temp2 = new Node<T>(data);
                    this->siz++;
                    while(temp!=nullptr)
                    {
                        if(cmp(data,temp->data))
                        {
                            if(temp == head)
                            {
                                this->head->prev = temp2;
                                temp2->next = this->head;
                                this->head = temp2;
                                return true;
                            }
                            else
                            {
                                    temp2->prev = temp->prev;
                                    temp2->next = temp;
                                    temp->prev->next = temp2;
                                    temp->next->prev = temp2;
                                    return true;
                            }
                        }
                        temp = temp->next;
                    }
                    this->tail->next = temp2;
                    temp2->prev = this->tail;
                    this->tail = temp2;
                    return true;
                }
                else
                {
                    auto temp = new Node<T>(data);
                    this->head = temp;
                    this->tail = temp;
                    this->head->next = this->tail;
                    this->tail->prev = this->head;
                    this->tail->next = nullptr;
                    this->siz++;
                    return true;
                }
            }
            return false;
        }
             
        bool remove(T data) {
            Node<T>** chunte;
            if(find(data,chunte))
            {
                // Lo mismo que el caso del insert
                if((*chunte)==(this->head))
                {
                    auto aux = this->head;
                    this->head = this->head->next;
                    this->head->prev = nullptr;
                    delete aux;
                    siz--;
                    return true;
                }
                if((*chunte)->data==this->tail->data)
                {
                    auto aux = this->tail;
                    this->tail = this->tail->prev;
                    this->tail->next = nullptr;
                    delete aux;
                    siz--;
                    return true;
                }
                else {
                    auto aux = *chunte;
                    auto temp = (*chunte)->prev;
                    (*chunte)->prev->next = (*chunte)->next;
                    (*chunte)->prev = temp;
                    delete aux;
                    siz--;
                    return true;
                }
            }
            return false;
        }  

        bool find(T data) {
            Node<T> ** chunte;
            this->find(data,chunte);
        }
             
        int size() {
            return this->siz;
        }

        void print() {
            auto temp = this->head;
            while(temp!=nullptr)
            {
                std::cout<<temp->data<<" ";
                temp = temp->next;
            }
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

    void printa() {
        auto temp = this->tail;
        while(temp!=nullptr)
        {
            std::cout<<temp->data<<" ";
            temp = temp->prev;
        }
    }

        ~TraitsList() {
            this->head->killSelf();
        }         
};

#endif