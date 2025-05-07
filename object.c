#if !defined(__GNUC__) && !defined(__clang__) && !defined(__INTELLISENSE__)
    #error This program uses GCC/Clang extensions. Please use a compatible compiler.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include <stdint.h>

#define concat(x, y) x ## y

#define strTokenize(x) # x

#define expand(x) x

#define decorate(returntype, function, identifier, ...)\
    returntype expand(concat(function, identifier)) (void) {\
        return function(__VA_ARGS__);\
    }

#define decorate_void(function, identifier, ...)\
    void expand(concat(function, identifier)) (void) {\
        function(__VA_ARGS__);\
    }

#define expanded_decorate(returntype, function, identifier, arg1Type, arg1Name, ...)\
    returntype expand(concat(function, identifier)) (expand(arg1Type) arg1Name) {\
        return function(__VA_ARGS__, arg1Name);\
    }

#define expanded_decorate_void(function, identifier, arg1Type, arg1Name, ...)\
    void expand(concat(function, identifier)) (expand(arg1Type) arg1Name) {\
        function(__VA_ARGS__, arg1Name);\
    }

#define double_expanded_decorate_void(function, identifier, arg1Type, arg1Name, arg2Type, arg2Name, ...)\
    void expand(concat(function, identifier)) (expand(arg1Type) arg1Name, expand(arg2Type) arg2Name) {\
        function(__VA_ARGS__, arg1Name, arg2Name);\
    }

#ifdef __INTELLISENSE__
    #define constructObject(arg1) *internalObjectAllocator(arg1) 
#else // prevents IntelliSense from complaining about the GCC-specific macro
    #define constructObjectInternal(arraySize, identifier) ({\
        object returnObject = *(internalObjectAllocator(arraySize));\
        decorate(size_t, lengthFunc, identifier, &returnObject);\
        decorate(char *, stringFunc, identifier, &returnObject);\
        decorate_void(deleteFunc, identifier,  &returnObject);\
        decorate_void(sortFunc, identifier,  &returnObject);\
        expanded_decorate_void(resizeFunc, identifier, size_t, newArraySize, &returnObject);\
        expanded_decorate_void(fillFunc, identifier, int, value, &returnObject);\
        expanded_decorate(int *, atFunc, identifier, size_t, index, &returnObject);\
        expanded_decorate(int, getFunc, identifier, size_t, index, &returnObject);\
        double_expanded_decorate_void(setFunc, identifier, size_t, index, int, value, &returnObject);\
        returnObject.id = strTokenize(identifier);\
        returnObject.length = expand(concat(lengthFunc, identifier));\
        returnObject.resize = expand(concat(resizeFunc, identifier));\
        returnObject.at = expand(concat(atFunc, identifier));\
        returnObject.get = expand(concat(getFunc, identifier));\
        returnObject.set = expand(concat(setFunc, identifier));\
        returnObject.string = expand(concat(stringFunc, identifier));\
        returnObject.delete = expand(concat(deleteFunc, identifier));\
        returnObject.sort = expand(concat(sortFunc, identifier));\
        returnObject.fill = expand(concat(fillFunc, identifier));\
        returnObject;\
    })

    #define constructObject(arraySize) constructObjectInternal(arraySize, __COUNTER__)
#endif

#define type_size1 int8_t
#define type_size2 int16_t
#define type_size4 int32_t
#define type_size8 int64_t

#define sizeCast(item, size) (type_size##size)item
#define sizeCastPointer(item, size) (type_size##size *)item

typedef struct object {
    char *id;
    int *array;
    size_t size;
    size_t (*length)(void);
    char *(*string)(void);
    char *stringAllocator;
    void (*resize)(size_t newArraySize);
    int *(*at)(size_t index);
    void (*set)(size_t index, int value);
    void (*fill)(int value);
    int (*get)(size_t index);
    void (*sort)(void);
    void (*delete)(void);
} object;

size_t lengthFunc(object *self) {
    return self -> size;
}

void resizeFunc(object *self, size_t newArraySize) {
    self -> size = newArraySize;
    self -> array = (int *)realloc(self -> array, newArraySize * sizeof(int));
    return;
}

int *atFunc(object *self, size_t index) {
    if (index >= self -> size) {
        fprintf(stderr, "Index out of bounds. Terminating");
        exit(1);
    }
    return self -> array + index;
}

int getFunc(object *self, size_t index) {
    return *atFunc(self, index);
}

void setFunc(object *self, size_t index, int value) {
    *atFunc(self, index) = value;
    return;
}

void fillFunc(object *self, int value) {
    for (size_t i=0; i < self -> length(); i++) {
        self -> set(i, value);
    }
    return;
}

char *stringFunc(object *self) {
    if (self -> stringAllocator) {
        free(self -> stringAllocator);
        self -> stringAllocator = NULL;
    }
    char *output = (char *)malloc(self -> size * 12 + 4); // ten digits each, plus comma and space, plus braces and null terminator
    output[0] = '\0';
    strcat(output, "{");
    char buffer[256];
    for (size_t i = 0; i < self -> size - 1; i++) {
        sprintf(buffer, "%d, ", self -> array[i]);
        strcat(output, buffer);
    }
    sprintf(buffer, "%d}", self -> array[self -> size - 1]);
    strcat(output, buffer);
    self -> stringAllocator = output;
    return output;
}

void deleteFunc(object *self) {
    if (self -> stringAllocator) {
        free(self -> stringAllocator);
    }
    free(self);
    return;
}

void sortFunc(object *self) {
    mergeSort(self -> array, self -> size);
}

object *internalObjectAllocator(size_t arraySize) {
    if (!arraySize) {
        fprintf(stderr, "Array size must be positive.\n");
        exit(1);
    }
    object *returnValue = (object *)malloc(sizeof(object));
    returnValue -> array = (int *)calloc(arraySize, sizeof(int));
    returnValue -> size = arraySize;
    returnValue -> stringAllocator = NULL;
    return returnValue;
}

int main() {
    object myObject = constructObject(10);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    myObject.resize(15);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    myObject.fill(12);
    myObject.set(3, 82);
    myObject.sort();
    printf("Object %s at index 0: %d\n", myObject.id, myObject.get(0));
    printf("%s\n", myObject.string());
}