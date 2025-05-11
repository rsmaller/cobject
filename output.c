# 0 "object.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "object.c"
# 1 "cobjects.h" 1
# 9 "cobjects.h" 2
# 2 "object.c" 2

#include <stdio.h>

# 3 "object.c"
int main() {
    int x[5] = {1,2,3,4,5};
    typedef int* intPtr ; typedef struct intPtrObject_Internal { char *id; char *internalType; intPtr *array; size_t capacity; int filledIndex; char *stringAllocator; size_t (*length)(void); char *(*string)(void); void (*resize)(size_t newArraySize); intPtr *(*at)(size_t index); void (*set)(size_t index, intPtr value); void (*fill)(intPtr value); void (*push)(intPtr value); intPtr (*pop)(void); intPtr (*get)(size_t index); void (*sort)(void); void (*delete)(void); void (*clear)(void); } intPtrObject_Internal; typedef struct intPtrObject { char const * const id; char const * const internalType; intPtr *array; size_t capacity; int filledIndex; char *stringAllocator; size_t (* const length)(void); char *(* const string)(void); void (* const resize)(size_t newArraySize); intPtr *(* const at)(size_t index); void (* const set)(size_t index, intPtr value); void (* const fill)(intPtr value); void (* const push)(intPtr value); intPtr (* const pop)(void); intPtr (* const get)(size_t index); void (* const sort)(void); void (* const delete)(void); void (* const clear)(void); } intPtrObject; size_t lengthFuncintPtr(intPtrObject_Internal *self) { return self -> filledIndex + 1; } intPtr *atFuncintPtr(intPtrObject_Internal *self, size_t index) { if (index >= self -> capacity) { fprintf(
# 5 "object.c" 3
                          (__acrt_iob_func(2))
# 5 "object.c"
                          , "Index out of bounds. Terminating"); exit(1); } return self -> array + index; } void pushFuncintPtr(intPtrObject_Internal *self, intPtr value) { self -> filledIndex++; self -> array[self -> length() - 1] = value; if (self -> filledIndex >= self -> capacity / 2) { self -> capacity *= 2; self -> array = (intPtr *)realloc(self -> array, self -> capacity * sizeof(intPtr)); if (!self -> array) { fprintf(
# 5 "object.c" 3
                          (__acrt_iob_func(2))
# 5 "object.c"
                          , "Object reallocation failure. Terminating\n"); exit(1); } } } intPtr popFuncintPtr(intPtrObject_Internal *self) { if (self -> filledIndex < 0) { return 0; } intPtr returnValue = self -> array[self -> length() - 1]; self -> filledIndex--; return returnValue; } intPtr getFuncintPtr(intPtrObject_Internal *self, size_t index) { return *atFuncintPtr(self, index); } void setFuncintPtr(intPtrObject_Internal *self, size_t index, intPtr value) { *atFuncintPtr(self, index) = value; if (index > self -> filledIndex) { self -> filledIndex = index; } if (self -> filledIndex >= self -> capacity / 2) { self -> capacity *= 2; self -> array = (intPtr *)realloc(self -> array, self -> capacity * sizeof(intPtr)); if (!self -> array) { fprintf(
# 5 "object.c" 3
                          (__acrt_iob_func(2))
# 5 "object.c"
                          , "Object reallocation failure. Terminating\n"); exit(1); } } return; } void fillFuncintPtr(intPtrObject_Internal *self, intPtr value) { for (size_t i=0; i < self -> length(); i++) { self -> set(i, value); } return; } char *stringFuncintPtr(intPtrObject_Internal *self) { if (self -> filledIndex < 0) { char *returnValue = (char *)malloc(3 * sizeof(char)); returnValue[0] = '{'; returnValue[1] = '}'; returnValue[2] = '\0'; return returnValue; } char *startFormatter; char *endFormatter; if (__builtin_classify_type(intPtr) == 5) { if (sizeof(intPtr) == 8) { startFormatter = "0x%llx, "; endFormatter = "0x%llx}"; } else { startFormatter = "0x%x, "; endFormatter = "0x%x}"; } } else if (sizeof(intPtr) == 1) { startFormatter = "%c, "; endFormatter = "%c}"; } else if ((intPtr)0 - 1 > 0) { startFormatter = "%llu, "; endFormatter = "%llu}"; } else { startFormatter = "%lld, "; endFormatter = "%lld}"; } if (self -> stringAllocator) { free(self -> stringAllocator); self -> stringAllocator = 
# 5 "object.c" 3 4
                          ((void *)0)
# 5 "object.c"
                          ; } char *output = (char *)malloc(self -> length() * 12 + 10); output[0] = '\0'; strcat(output, "{"); char buffer[256]; for (size_t i = 0; i < self -> length() - 1; i++) { sprintf(buffer, startFormatter, self -> array[i]); strcat(output, buffer); } sprintf(buffer, endFormatter, self -> array[self -> length() - 1]); strcat(output, buffer); self -> stringAllocator = output; return output; } void deleteFuncintPtr(intPtrObject_Internal *self) { if (self -> stringAllocator) { free(self -> stringAllocator); } return; } void clearFuncintPtr(intPtrObject_Internal *self) { if (self -> stringAllocator) { free(self -> stringAllocator); self -> stringAllocator = 
# 5 "object.c" 3 4
                          ((void *)0)
# 5 "object.c"
                          ; } self -> filledIndex = -1; return; } void mergeintPtr(intPtr *array1, intPtr *array2, size_t size1, size_t size2) { intPtr *internalArray = (intPtr *)malloc((size1 + size2) * sizeof(intPtr)); if (!internalArray) { fprintf(
# 5 "object.c" 3
                          (__acrt_iob_func(2))
# 5 "object.c"
                          , "Merge sort allocation failure. Terminating\n"); exit(1); } size_t array1Index = 0; size_t array2Index = 0; size_t totalSize = size1 + size2; while ((array1Index < size1) && (array2Index < size2)) { if (array1[array1Index] < array2[array2Index]) { internalArray[array1Index + array2Index] = array1[array1Index]; array1Index++; } else { internalArray[array1Index + array2Index] = array2[array2Index]; array2Index++; } } while (array1Index < (size1)) { internalArray[array1Index + array2Index] = array1[array1Index]; array1Index++; } while (array2Index < (size2)) { internalArray[array1Index + array2Index] = array2[array2Index]; array2Index++; } memcpy(array1, internalArray, totalSize * sizeof(intPtr)); free(internalArray); return; } size_t partitionintPtr(size_t size) { return size / 2UL; } void mergeSortintPtr(intPtr *array1, size_t sizeTotal) { size_t partition2Index = partitionintPtr(sizeTotal); intPtr *array2 = array1 + partition2Index; size_t size1 = partition2Index; size_t size2 = sizeTotal - partition2Index; if (sizeTotal <=1) return; mergeSortintPtr(array1, size1); mergeSortintPtr(array2, size2); mergeintPtr(array1, array2, size1, size2); return; } void sortFuncintPtr(intPtrObject_Internal *self) { mergeSortintPtr(self -> array, self -> length()); };
    typedef struct intObject_Internal { char *id; char *internalType; int *array; size_t capacity; int filledIndex; char *stringAllocator; size_t (*length)(void); char *(*string)(void); void (*resize)(size_t newArraySize); int *(*at)(size_t index); void (*set)(size_t index, int value); void (*fill)(int value); void (*push)(int value); int (*pop)(void); int (*get)(size_t index); void (*sort)(void); void (*delete)(void); void (*clear)(void); } intObject_Internal; typedef struct intObject { char const * const id; char const * const internalType; int *array; size_t capacity; int filledIndex; char *stringAllocator; size_t (* const length)(void); char *(* const string)(void); void (* const resize)(size_t newArraySize); int *(* const at)(size_t index); void (* const set)(size_t index, int value); void (* const fill)(int value); void (* const push)(int value); int (* const pop)(void); int (* const get)(size_t index); void (* const sort)(void); void (* const delete)(void); void (* const clear)(void); } intObject; size_t lengthFuncint(intObject_Internal *self) { return self -> filledIndex + 1; } int *atFuncint(intObject_Internal *self, size_t index) { if (index >= self -> capacity) { fprintf(
# 6 "object.c" 3
   (__acrt_iob_func(2))
# 6 "object.c"
   , "Index out of bounds. Terminating"); exit(1); } return self -> array + index; } void pushFuncint(intObject_Internal *self, int value) { self -> filledIndex++; self -> array[self -> length() - 1] = value; if (self -> filledIndex >= self -> capacity / 2) { self -> capacity *= 2; self -> array = (int *)realloc(self -> array, self -> capacity * sizeof(int)); if (!self -> array) { fprintf(
# 6 "object.c" 3
   (__acrt_iob_func(2))
# 6 "object.c"
   , "Object reallocation failure. Terminating\n"); exit(1); } } } int popFuncint(intObject_Internal *self) { if (self -> filledIndex < 0) { return 0; } int returnValue = self -> array[self -> length() - 1]; self -> filledIndex--; return returnValue; } int getFuncint(intObject_Internal *self, size_t index) { return *atFuncint(self, index); } void setFuncint(intObject_Internal *self, size_t index, int value) { *atFuncint(self, index) = value; if (index > self -> filledIndex) { self -> filledIndex = index; } if (self -> filledIndex >= self -> capacity / 2) { self -> capacity *= 2; self -> array = (int *)realloc(self -> array, self -> capacity * sizeof(int)); if (!self -> array) { fprintf(
# 6 "object.c" 3
   (__acrt_iob_func(2))
# 6 "object.c"
   , "Object reallocation failure. Terminating\n"); exit(1); } } return; } void fillFuncint(intObject_Internal *self, int value) { for (size_t i=0; i < self -> length(); i++) { self -> set(i, value); } return; } char *stringFuncint(intObject_Internal *self) { if (self -> filledIndex < 0) { char *returnValue = (char *)malloc(3 * sizeof(char)); returnValue[0] = '{'; returnValue[1] = '}'; returnValue[2] = '\0'; return returnValue; } char *startFormatter; char *endFormatter; if (__builtin_classify_type(int) == 5) { if (sizeof(int) == 8) { startFormatter = "0x%llx, "; endFormatter = "0x%llx}"; } else { startFormatter = "0x%x, "; endFormatter = "0x%x}"; } } else if (sizeof(int) == 1) { startFormatter = "%c, "; endFormatter = "%c}"; } else if ((int)0 - 1 > 0) { startFormatter = "%llu, "; endFormatter = "%llu}"; } else { startFormatter = "%lld, "; endFormatter = "%lld}"; } if (self -> stringAllocator) { free(self -> stringAllocator); self -> stringAllocator = 
# 6 "object.c" 3 4
   ((void *)0)
# 6 "object.c"
   ; } char *output = (char *)malloc(self -> length() * 12 + 10); output[0] = '\0'; strcat(output, "{"); char buffer[256]; for (size_t i = 0; i < self -> length() - 1; i++) { sprintf(buffer, startFormatter, self -> array[i]); strcat(output, buffer); } sprintf(buffer, endFormatter, self -> array[self -> length() - 1]); strcat(output, buffer); self -> stringAllocator = output; return output; } void deleteFuncint(intObject_Internal *self) { if (self -> stringAllocator) { free(self -> stringAllocator); } return; } void clearFuncint(intObject_Internal *self) { if (self -> stringAllocator) { free(self -> stringAllocator); self -> stringAllocator = 
# 6 "object.c" 3 4
   ((void *)0)
# 6 "object.c"
   ; } self -> filledIndex = -1; return; } void mergeint(int *array1, int *array2, size_t size1, size_t size2) { int *internalArray = (int *)malloc((size1 + size2) * sizeof(int)); if (!internalArray) { fprintf(
# 6 "object.c" 3
   (__acrt_iob_func(2))
# 6 "object.c"
   , "Merge sort allocation failure. Terminating\n"); exit(1); } size_t array1Index = 0; size_t array2Index = 0; size_t totalSize = size1 + size2; while ((array1Index < size1) && (array2Index < size2)) { if (array1[array1Index] < array2[array2Index]) { internalArray[array1Index + array2Index] = array1[array1Index]; array1Index++; } else { internalArray[array1Index + array2Index] = array2[array2Index]; array2Index++; } } while (array1Index < (size1)) { internalArray[array1Index + array2Index] = array1[array1Index]; array1Index++; } while (array2Index < (size2)) { internalArray[array1Index + array2Index] = array2[array2Index]; array2Index++; } memcpy(array1, internalArray, totalSize * sizeof(int)); free(internalArray); return; } size_t partitionint(size_t size) { return size / 2UL; } void mergeSortint(int *array1, size_t sizeTotal) { size_t partition2Index = partitionint(sizeTotal); int *array2 = array1 + partition2Index; size_t size1 = partition2Index; size_t size2 = sizeTotal - partition2Index; if (sizeTotal <=1) return; mergeSortint(array1, size1); mergeSortint(array2, size2); mergeint(array1, array2, size1, size2); return; } void sortFuncint(intObject_Internal *self) { mergeSortint(self -> array, self -> length()); };
    intObject myObject = ({ size_t sizeValue = 10; if (!sizeValue) { fprintf(
# 7 "object.c" 3
                        (__acrt_iob_func(2))
# 7 "object.c"
                        , "Array size must be positive.\n"); exit(1); } else if (sizeValue < 4) { sizeValue = 4; } intObject_Internal returnObject; size_t lengthFuncint0 (void) { return lengthFuncint(&returnObject); }; int popFuncint0 (void) { return popFuncint(&returnObject); }; char * stringFuncint0 (void) { return stringFuncint(&returnObject); }; void deleteFuncint0 (void) { deleteFuncint(&returnObject); }; void clearFuncint0 (void) { clearFuncint(&returnObject); }; void sortFuncint0 (void) { sortFuncint(&returnObject); }; void fillFuncint0 (int value) { fillFuncint(&returnObject, value); }; void pushFuncint0 (int value) { pushFuncint(&returnObject, value); }; int * atFuncint0 (size_t index) { return atFuncint(&returnObject, index); }; int getFuncint0 (size_t index) { return getFuncint(&returnObject, index); }; void setFuncint0 (size_t index, int value) { setFuncint(&returnObject, index, value); }; returnObject = (intObject_Internal){ .array = (int *)calloc(sizeValue, sizeof(int)), .capacity = sizeValue, .filledIndex = -1, .stringAllocator = 
# 7 "object.c" 3 4
                        ((void *)0)
# 7 "object.c"
                        , .id = "0", .internalType = "int", .length = lengthFuncint0, .at = atFuncint0, .get = getFuncint0, .set = setFuncint0, .string = stringFuncint0, .delete = deleteFuncint0, .clear = clearFuncint0, .sort = sortFuncint0, .fill = fillFuncint0, .push = pushFuncint0, .pop = popFuncint0 }; if (!returnObject.array) { fprintf(
# 7 "object.c" 3
                        (__acrt_iob_func(2))
# 7 "object.c"
                        , "Object construction failure. Terminating\n"); exit(1); } intObject castedReturnObject = *(intObject *)&returnObject; castedReturnObject;});

    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    printf("Object %s type: %s\n", myObject.id, myObject.internalType);
    myObject.push(x[0]);
    myObject.push(x[1]);
    myObject.push(x[2]);
    printf("Object %s size after pushing 15, 200, and 30: %llu\n", myObject.id, myObject.length());
    printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
    myObject.sort();
    printf("Object %s after sort: %s\n", myObject.id, myObject.string());
    myObject.clear();
    printf("Object %s after clear: %s\n", myObject.id, myObject.string());
    myObject.push(x[3]);
    printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
    myObject.push(x[4]);
    printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
    myObject.delete();
    printf("\n\n");

    intPtrObject myObject2 = ({ size_t sizeValue = 10; if (!sizeValue) { fprintf(
# 27 "object.c" 3
                            (__acrt_iob_func(2))
# 27 "object.c"
                            , "Array size must be positive.\n"); exit(1); } else if (sizeValue < 4) { sizeValue = 4; } intPtrObject_Internal returnObject; size_t lengthFuncintPtr1 (void) { return lengthFuncintPtr(&returnObject); }; intPtr popFuncintPtr1 (void) { return popFuncintPtr(&returnObject); }; char * stringFuncintPtr1 (void) { return stringFuncintPtr(&returnObject); }; void deleteFuncintPtr1 (void) { deleteFuncintPtr(&returnObject); }; void clearFuncintPtr1 (void) { clearFuncintPtr(&returnObject); }; void sortFuncintPtr1 (void) { sortFuncintPtr(&returnObject); }; void fillFuncintPtr1 (intPtr value) { fillFuncintPtr(&returnObject, value); }; void pushFuncintPtr1 (intPtr value) { pushFuncintPtr(&returnObject, value); }; intPtr * atFuncintPtr1 (size_t index) { return atFuncintPtr(&returnObject, index); }; intPtr getFuncintPtr1 (size_t index) { return getFuncintPtr(&returnObject, index); }; void setFuncintPtr1 (size_t index, intPtr value) { setFuncintPtr(&returnObject, index, value); }; returnObject = (intPtrObject_Internal){ .array = (intPtr *)calloc(sizeValue, sizeof(intPtr)), .capacity = sizeValue, .filledIndex = -1, .stringAllocator = 
# 27 "object.c" 3 4
                            ((void *)0)
# 27 "object.c"
                            , .id = "1", .internalType = "intPtr", .length = lengthFuncintPtr1, .at = atFuncintPtr1, .get = getFuncintPtr1, .set = setFuncintPtr1, .string = stringFuncintPtr1, .delete = deleteFuncintPtr1, .clear = clearFuncintPtr1, .sort = sortFuncintPtr1, .fill = fillFuncintPtr1, .push = pushFuncintPtr1, .pop = popFuncintPtr1 }; if (!returnObject.array) { fprintf(
# 27 "object.c" 3
                            (__acrt_iob_func(2))
# 27 "object.c"
                            , "Object construction failure. Terminating\n"); exit(1); } intPtrObject castedReturnObject = *(intPtrObject *)&returnObject; castedReturnObject;});
    printf("Object %s size: %llu\n", myObject2.id, myObject2.length());
    printf("Object %s type: %s\n", myObject2.id, myObject2.internalType);
    myObject2.push(x);
    myObject2.push(x+1);
    myObject2.push(x+2);
    printf("Object %s size after pushing 15, 200, and 30: %llu\n", myObject2.id, myObject2.length());
    printf("Object %s after pushing: %s\n", myObject2.id, myObject2.string());
    myObject2.sort();
    printf("Object %s after sort: %s\n", myObject2.id, myObject2.string());
    myObject2.clear();
    printf("Object %s after clear: %s\n", myObject2.id, myObject2.string());
    myObject2.push(x+3);
    printf("Object %s after pushing: %s\n", myObject2.id, myObject2.string());
    myObject2.push(x+4);
    printf("Object %s after pushing: %s\n", myObject2.id, myObject2.string());
    myObject2.delete();

    return 0;
}
