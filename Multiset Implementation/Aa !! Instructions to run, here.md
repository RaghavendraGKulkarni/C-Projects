Multiset is a data structure which maintains the elements in a sorted order, allowing duplicate elements. The various operations implemented in this project, their description 
and the respective time complexities are as follows:

I) int* insert(int*,int*,int): This function insertes an element into the multiset, irrespective of whether the element is already present or not. It accepts the pointer to the 
                                first element of the array, the pointer to the size of the array and the element to be inserted. It returns the pointer to the first element of
                                the altered array after inserting the element.
                                Time Complexity: Linear {O(n)}
                                Space Complexity: Constant {O(1)}

II) bool find(int*,int,int): This function searches for an element in the multiset. It accepts the pointer to the first element of the array, the size of the array and the 
                              elementcto be searched. It returns the boolean value:
                              a) true, if the element is present in the multiset.
                              b) false, otherwise.
                              Note: The function does not provide any information about the location or the frequency of the element in the multiset.
                              Time Complexity: Logarithmic {O(log(n))}
                              Space Complexity: Constant {O(1)}

III) int greaterThan(int*,int,int): This function counts the number of elements which are strictly greater than the given element. It accepts the pointer to the first element of
                                    the array, the size of the array and the tight lower bound element. It returns the count of elements satisfying the condition.
                                    Time Complexity: Logarithmic {O(log(n))}
                                    Space Complexity: Constant {O(1)}

IV) int smallerThan(int*,int,int): This function counts the number of elements which are strictly smaller than the given element. It accepts the pointer to the first element of
                                    the array, the size of the array and the tight upper bound element. It returns the count of elements satisfying the condition.
                                    Time Complexity: Logarithmic {O(log(n))}
                                    Space Complexity: Constant {O(1)}

V) int* erase(int*,int*,int): This function erases all the occurrences of an element from the multiset. It accepts the pointer to the first element of the array, the pointer to 
                              the size of the array and the element to be inserted. It returns the pointer to the first element of the altered array after erasing the elements.
                              Time Complexity: Linear {O(n)}
                              Space Complexity: Constant {O(1)}

VI) int count(int*,int,int): This function counts all the occurrences the given element. It accepts the pointer to the first element of the array, the size of the array and the
                              element whose occurrence is to be counted. It returns the frequency of the element.
                              Time Complexity: Logarithmic {O(log(n))}
                              Space Complexity: Constant {O(1)}

VII) int nextElement(int*,int,int): This function finds the next greater element of the given element in the multiset. It accepts the pointer to the first element of the array, 
                                    the size of the array and the element whose next greater element is to be found. It returns:
                                    a) the next greater element of the given element if it exists.
                                    b) infinity, otherwise.
                                    Time Complexity: Logarithmic {O(log(n))}
                                    Space Complexity: Constant {O(1)}

VIII) int nextElement(int*,int,int): This function finds the previous smaller element of the given element in the multiset. It accepts the pointer to the first element of the
                                     array, the size of the array and the element whose previous smaller element is to be found. It returns:
                                      a) the previous smaller element of the given element if it exists.
                                      b) -infinity, otherwise.
                                      Time Complexity: Logarithmic {O(log(n))}
                                      Space Complexity: Constant {O(1)}
