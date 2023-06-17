#ifndef __STACK__QUEUE__
#define __STACK__QUEUE__

template<class valueType>
struct Node{
    valueType *value;
    struct Node* next;
};

template<class valueType>
void InitNode(struct Node<valueType> &node){
    node.value = NULL;
    node.next = NULL;
}

template<class valueType>
Node<valueType>* CreateNode(valueType &value){
    Node<valueType> *node = new Node<valueType>;
    node->value = &value;
    node->next = NULL;
    return node;
}

template<class valueType>
struct Stack{
    Node<valueType>* front;
};

template<class valueType>
void InitStack(struct Stack<valueType> &stack){
    stack.front = NULL;
}

template<class valueType>
void pushStack(Stack<valueType> &stack, valueType &value){
    Node<valueType> *newNode = CreateNode(value);
    newNode->next = stack.front;
    stack.front = newNode;
}
     
template<class valueType>
void popStack(Stack<valueType> &stack){
    stack.front = stack.front->next;
}

template<class valueType>
valueType* topStack(Stack<valueType> &stack){
    return stack.front->value;
}

template<class valueType>
bool emptyStack(Stack<valueType> &stack){
    return stack.front == NULL;
}

template<class valueType>
struct Queue{
    Node<valueType>* front;
    Node<valueType>* rear;
};

template<class valueType>
void InitQueue(Queue<valueType> &queue){
    queue.front = NULL;
    queue.rear = NULL;
}

template<class valueType>
void pushQueue(Queue<valueType> &queue,valueType &value){
    Node<valueType> *newNode = CreateNode(value);
    if(queue.front == NULL){
        queue.front = queue.rear = newNode; 
    }else{
        queue.rear->next = newNode;
        queue.rear = newNode;
    }
}
     
template<class valueType>
void popQueue(Queue<valueType> &queue){
    if(queue.front == NULL){
        return;
    }
    queue.front = queue.front->next;
    queue.rear = queue.front ? queue.rear : NULL;
}

template<class valueType>
valueType *frontQueue(Queue<valueType> &queue){
    return queue.front->value;
}

template<class valueType>
bool emptyQueue(Queue<valueType> &queue){
    return queue.front == NULL;
}

#endif