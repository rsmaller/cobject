#if !defined(__GNUC__) && !defined(__clang__) && !defined(__INTELLISENSE__)
    #error This program uses GCC/Clang extensions. Please use a compatible compiler.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        expanded_decorate_void(resizeFunc, identifier, size_t, newArraySize, &returnObject);\
        expanded_decorate(int *, atFunc, identifier, size_t, index, &returnObject);\
        expanded_decorate(int, getFunc, identifier, size_t, index, &returnObject);\
        double_expanded_decorate_void(setFunc, identifier, size_t, index, int, value, &returnObject);\
        returnObject.id = strTokenize(identifier);\
        returnObject.length = expand(concat(lengthFunc, identifier));\
        returnObject.resize = expand(concat(resizeFunc, identifier));\
        returnObject.at = expand(concat(atFunc, identifier));\
        returnObject.get = expand(concat(getFunc, identifier));\
        returnObject.set = expand(concat(setFunc, identifier));\
        returnObject;\
    })

    #define constructObject(arraySize) constructObjectInternal(arraySize, __COUNTER__)
#endif

typedef struct object {
    char *id;
    int *array;
    size_t size;
    size_t (*length)(void);
    void (*resize)(size_t newArraySize);
    int *(*at)(size_t index);
    void (*set)(size_t index, int value);
    int (*get)(size_t index);
} object;

size_t lengthFunc(object *self) {
    return self -> size;
}

void resizeFunc(object *self, size_t newArraySize) {
    self -> size = newArraySize;
    self -> array = (int *)realloc(self -> array, newArraySize);
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

object *internalObjectAllocator(size_t arraySize) {
    object *returnValue = (object *)malloc(sizeof(object));
    returnValue -> array = (int *)calloc(arraySize, sizeof(int));
    returnValue -> size = arraySize;
    return returnValue;
}

int main() {
    object myObject = constructObject(100);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    myObject.resize(150);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    object myObject2 = constructObject(200);
    printf("Object %s size: %llu\n", myObject2.id, myObject2.length());
    myObject2.resize(250);
    printf("Object %s size: %llu\n", myObject2.id, myObject2.length());
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    printf("Object %s at index 0: %d\n", myObject.id, myObject.get(0));
    myObject.set(0, 1);
    printf("Object %s at index 0: %d\n", myObject.id, myObject.get(0));
}