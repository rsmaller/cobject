#if !defined(__GNUC__) && !defined(__clang__)
    #error This program uses GCC/Clang extensions. Please use a compatible compiler.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define concat(x, y) x ## y

#define expand(x) x

#define checkVoid(x) x == void

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

#ifdef __INTELLISENSE__
    #define constructObject(arg1, arg2) *construct_object_internal(arg1) 
#else // prevents IntelliSense from complaining about the GCC-specific macro
    #define constructObject(arraySize, identifier)\
    ({\
        object returnObject = *(construct_object_internal(arraySize));\
        decorate(size_t, lengthFunc, identifier, &returnObject);\
        expanded_decorate_void(resizeFunc, identifier, size_t, newArraySize, &returnObject);\
        returnObject.length = expand(concat(lengthFunc, identifier));\
        returnObject.resize = expand(concat(resizeFunc, identifier));\
        returnObject;\
    })
#endif

typedef struct object {
    int *array;
    size_t size;
    size_t (*length)(void);
    void (*resize)(size_t);
} object;

size_t lengthFunc(object *self) {
    return self -> size;
}

void resizeFunc(object *self, size_t newArraySize) {
    self -> size = newArraySize;
    self -> array = (int *)realloc(self -> array, newArraySize);
}

object *construct_object_internal(size_t arraySize) {
    object *returnValue = (object *)malloc(sizeof(object));
    returnValue -> array = (int *)malloc(arraySize * sizeof(int));
    returnValue -> size = arraySize;
    return returnValue;
}

int main() {
    object myObject = constructObject(100, 1);
    printf("%llu\n", myObject.length());
    myObject.resize(150);
    printf("%llu\n", myObject.length());
}