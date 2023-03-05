//
//  main.cpp
//  Abstract_Container
//
//  Created by MacBook Air M1 on 20.02.23.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
class Abstract_Container{
public:
    virtual int Size() = 0;
    virtual bool IsEmpty() =0;
};
class Abstract_Stack : public Abstract_Container{
public:
    virtual void Push(int value) = 0;
    virtual void Pop() = 0;
    virtual int Top() = 0;
};
struct Node{
    int data;
    Node* next;
};
class ListStack : public Abstract_Stack{
public:
    ListStack():
    head(nullptr), size_(0){
    }
    int Size(){
    return size_;
    }
    bool IsEmpty(){
        if(size_==0) return true;
        return false;
    }
    void Push(int value){
        if(IsEmpty()){
        Node* new_head=new Node{value,NULL};
        head = new_head;
        }
        else{
        Node* new_head= new Node{value,head};
        head = new_head;
        }
        size_++;
    }
    void AddBack(int value){
        if(IsEmpty()){
        Node* new_head=new Node{value,NULL};
        head = new_head;
        }
        else{
        //Node* new_tail=new Node{value,};
            Node* curr = head;
            while(curr->next!=NULL){
            curr=curr->next;
            }
        Node* new_tail=new Node{value,NULL};
            curr->next = new_tail;
        }
        size_++;
    }
    void Pop(){
    if(IsEmpty()) return;
    Node* old_head =head;
    head=head->next;
    delete old_head;
    old_head=nullptr;
    size_--;
    }
    void PopBack(){
        if(IsEmpty()) return;
        Node* curr = head;
        while(curr->next->next!=NULL){
        curr=curr->next;
        }
        Node* old_tail = curr->next;
        delete old_tail;
        curr->next=NULL;
    }
    int IndexOfNode(int value){
        Node* curr=head; int count =0;
        while(curr!=NULL){
        if(curr->data==value) return count;
        curr=curr->next;
        count++;
        }
        return -1;
    }
    int Top(){
    return head->data;
    }
    void Show(){
        Node* curr = head;
        while(curr!=NULL){
        cout << curr->data << " ";
        curr=curr->next;
        }
        cout << endl;
    }
private:
    Node* head;
    int size_;
};
class LimitedStack : public Abstract_Stack{
public:
    LimitedStack():
    size_(0), limstack(nullptr){
    }
    LimitedStack(int size){
        if(size>limit) throw runtime_error("Entered size is greater that maximal possible:(");
        else {size_ = size;
        limstack = new int[size_];
        for(int i=0; i<size_; i++){
            limstack[i] = 0;
        }
      }
    }
    LimitedStack(const LimitedStack& other){
        size_ = other.size_;
        limstack = new int[size_];
        for(int i=0; i<size_; i++){
        limstack[i] = other.limstack[i];
        }
    }
    LimitedStack(LimitedStack&& other){
        size_ = other.size_;
        limstack=other.limstack;
        other.limstack=NULL;
        other.size_=0;
    }
    int Size(){
        return size_;
    }
    LimitedStack& operator=(LimitedStack&& other){
        if(this==&other) return *this;
        delete limstack;
        size_=other.size_;
        limstack=other.limstack;
        other.limstack=NULL;
        other.size_=0;
        return *this;
    }
    LimitedStack& operator=(const LimitedStack& other){
        if(this == &other) return *this;
        size_ = other.size_;
        delete [] limstack;
        limstack = new int[other.size_];
        for(int i=0; i<size_; i++){
        limstack[i] = other.limstack[i];
        }
        return *this;
    }
    void Push(int value){
    if(size_==limit) throw runtime_error("Size cannot be increased!");
    else{
    int* new_stack = new int[size_+1];
        for(int i=0; i<size_; i++){
        new_stack[i] = limstack[i];
        }
        delete [] limstack;
        limstack = new_stack;
        limstack[size_] = value;
        size_++;
    }
    }
    bool IsEmpty(){
    if(size_==0) return true;
    return false;
    }
    void Pop(){
    if(IsEmpty()) return;
    else{
    int* new_stack = new int[size_-1];
        for(int i=0; i<size_-1; i++){
        new_stack[i] = limstack[i+1];
        }
        delete [] limstack;
        limstack = new_stack;
        size_--;
    }
    }
    int Top(){
    if(IsEmpty()) return -1;
    else return limstack[0];
    }
    void Show(){
        for(int i=0; i<size_; i++){
        cout << limstack[i] << " ";
        }
        cout << endl;
    }
private:
    int size_;
    int* limstack;
    int limit = 1000;
};
class RealUnLimitedStack : public Abstract_Stack{
public:
    int Size(){
    return size_;
    }
    bool IsEmpty(){
        if(size_==0) return true;
        return false;
    }
    RealUnLimitedStack(int size){
        size_ = size;
        unlimstack = new int[size_];
        for(int i=0; i<size_; i++){
        unlimstack[i] =0;
        }
    }
    RealUnLimitedStack():
        size_(0),unlimstack(nullptr) {

        }
        RealUnLimitedStack(const RealUnLimitedStack& other){
            size_ = other.size_;
            delete unlimstack;
            unlimstack = new int[size_];
            for(int i=0; i<size_; i++){
            unlimstack[i] = other.unlimstack[i];
            }
    }
    RealUnLimitedStack(RealUnLimitedStack&& other){
        size_=other.size_;
        unlimstack=other.unlimstack;
        other.unlimstack=NULL;
        other.size_=0;
    }
    RealUnLimitedStack& operator=(RealUnLimitedStack&& other){
        if(this==&other) return *this;
        delete unlimstack;
        size_=other.size_;
        unlimstack=other.unlimstack;
        other.unlimstack=NULL;
        other.size_=0;
        return *this;
    }
    RealUnLimitedStack& operator=(const RealUnLimitedStack& other){
        if(this == &other) return *this;
        size_ = other.size_;
        unlimstack = new int[size_];
        for(int i=0; i<size_; i++){
        unlimstack[i] = other.unlimstack[i];
        }
        return *this;
    }
    void Push(int value){
    int* new_stack = new int[size_+1];
        for(int i=0; i<size_; i++){
        new_stack[i] = unlimstack[i];
        }
        delete [] unlimstack;
        unlimstack = new_stack;
        unlimstack[size_] = value;
        size_++;
    }
    void Pop(){
    if(size_==0) return;
    int* new_stack = new int[size_-1];
        for(int i=0; i<size_-1; i++){
        new_stack[i] = unlimstack[i+1];
        }
        delete [] unlimstack;
        unlimstack = new_stack;
        size_--;
    }
    int Top(){
    if(IsEmpty()) return -1;
    return unlimstack[0];
    }
    void Show(){
        for(int i=0; i<size_; i++){
        cout << unlimstack[i] << " ";
        }
        cout << endl;
    }
private:
    int size_;
    int* unlimstack;
    
};
class Abstract_Queue : public Abstract_Container{
    virtual void EnQueue(int value) = 0;
    virtual int DeQueue() = 0;
    virtual int Peek() = 0;
    virtual int Count() =0;
    
};
class ListQueue : public Abstract_Queue{
public:
    ListQueue():
    size_(0),head(nullptr){
    }
    void EnQueue(int value){ // AddFront
        if(size_==0) head = new Node{value,NULL};
        else{
        Node* new_head = new Node{value,head};
        head = new_head;
        size_++;
        }
    }
    int DeQueue(){
        Node* curr = head;
        while(curr->next->next!=NULL){
        curr=curr->next;
        }
        Node* old_tail = curr->next;
        int res = old_tail->data;
        delete old_tail;
        curr->next = NULL;
        return res;
    }
    void Show(){
        Node* curr = head;
        while(curr!=NULL){
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    int Peek(){
        Node* curr = head;
        while(curr->next!=nullptr){
        curr=curr->next;
        }
        return curr->data;
    }
    int Count(){
    return size_;
    }
    bool IsEmpty(){
        if(size_==0) return true;
        return false;
    }
    int Size(){
        return size_;
    }
private:
    int size_;
    Node* head;
};
class ArrayQueue{
public:
    ArrayQueue():
    size_(0),queue(NULL){
    }
    ArrayQueue(int size){
        size_ = size;
        queue = new int[size_];
        for(int i=0; i<size_; i++){
            queue[i]= 0;
        }
    }
    ArrayQueue(const ArrayQueue& other){
        size_ = other.size_;
        queue = new int[size_];
        for(int i=0; i<size_; i++){
        queue[i] = other.queue[i];
        }
    }
    ArrayQueue(ArrayQueue&& othr){
        size_ = othr.size_;
        queue = othr.queue;
        othr.queue=NULL;
        othr.size_=0;
    }
    ArrayQueue& operator=(ArrayQueue&& other){
        if(this==&other) return *this;
        delete queue;
        size_=other.size_;
        queue=other.queue;
        other.queue=NULL;
        other.size_=0;
        return *this;
    }
    ArrayQueue& operator=(const ArrayQueue& other){
        if(&other == this) return *this;
        size_ = other.size_;
        delete queue;
        queue = new int[size_];
        for(int i=0; i<size_; i++){
        queue[i] = other.queue[i];
        }
        return *this;
    }
    int Size(){
        return size_;
    }
    bool IsEmpty(){
        if(size_==0) return true;
        return false;
    }
    void Enqueue(int value){
        int* new_arr = new int[size_+1];
        for(int i=0; i<size_; i++){
        new_arr[i] = queue[i];
        }
        delete queue;
        queue = new_arr;
        queue[size_] = value;
    }
    int Dequeue(){
        int* new_arr = new int[size_-1];
        for(int i=0; i<size_-1; i++){
        new_arr[i] = queue[i];
        }
        int res = queue[size_-1];
        delete queue;
        queue = new_arr;
        return res;
    }
    int Peek(){
    return queue[size_-1];
    }
    int Count(){
        return size_;
    }
    int Top(){
    return queue[0];
    }
private:
    int size_;
    int* queue;
};
int main(int argc, const char * argv[]) {
    RealUnLimitedStack unlimstack; // stack
    LimitedStack limstack; // stack
    ListStack liststack; // stack
    ListQueue listqueue;// queue
    ArrayQueue arr_queue; // queue
    return 0;
}
