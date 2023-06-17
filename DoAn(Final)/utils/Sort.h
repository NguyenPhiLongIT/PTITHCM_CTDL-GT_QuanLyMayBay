#ifndef __SORT__
#define __SORT__

template<class valueType>
void Swap(valueType &a, valueType &b){
    valueType temp;
    temp = a;
    a = b;
    b = temp;
}

template<class valueType>
bool Asc(valueType &a, valueType &b){
    return a > b;
}

template<class valueType>
bool Desc(valueType &a, valueType &b){
    return a < b;
}

template<class valueType>
void Quicksort(valueType *array, int low, int up, bool (*compare)(valueType &a, valueType &b) = Asc){
    
    valueType temp;
    int left, right;

    //Setting the index
    left = low;
    right = up;
    temp = array[(left + right)/2];
	    
    //Loop till pivot is placed at proper place in the sublist
    while(left < right){
        while(compare(array[left], temp))
            ++left;
        
        while(compare(temp, array[right]))
            --right;
        
        if(left <= right){
            Swap(array[left], array[right]);
            ++left;
            --right;
        }
    }
    if(low < right)
        Quicksort(array, low, right, compare);
    if(left < up)
        Quicksort(array, left, up, compare);
}

#endif
