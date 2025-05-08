#if !defined(__GNUC__) && !defined(__clang__) && !defined(__INTELLISENSE__)
    #error This program uses GCC/Clang extensions. Please use a compatible compiler.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    #define constructObject(arg1, arg2) {0}
    #define declareObjectType(type) typedef struct {char *id; type *array; size_t size; size_t (*length)(void); char *(*string)(void); char *stringAllocator; void (*resize)(size_t newArraySize); type *(*at)(size_t index); void (*set)(size_t index, type value); void (*fill)(type value); type (*get)(size_t index); void (*sort)(void); void (*delete)(void);} type##Object;
#else // prevents IntelliSense from complaining about the GCC-specific macro
    #define constructObjectInternal(arraySize, type, identifier) ({\
        type##Object returnObject = internalObjectAllocator##type(arraySize);\
        decorate(size_t, lengthFunc##type, identifier, &returnObject);\
        decorate(char *, stringFunc##type, identifier, &returnObject);\
        decorate_void(deleteFunc##type, identifier,  &returnObject);\
        decorate_void(sortFunc##type, identifier,  &returnObject);\
        expanded_decorate_void(resizeFunc##type, identifier, size_t, newArraySize, &returnObject);\
        expanded_decorate_void(fillFunc##type, identifier, type, value, &returnObject);\
        expanded_decorate(type *, atFunc##type, identifier, size_t, index, &returnObject);\
        expanded_decorate(type, getFunc##type, identifier, size_t, index, &returnObject);\
        double_expanded_decorate_void(setFunc##type, identifier, size_t, index, type, value, &returnObject);\
        returnObject.id = strTokenize(identifier);\
        returnObject.length = expand(concat(lengthFunc##type, identifier));\
        returnObject.resize = expand(concat(resizeFunc##type, identifier));\
        returnObject.at = expand(concat(atFunc##type, identifier));\
        returnObject.get = expand(concat(getFunc##type, identifier));\
        returnObject.set = expand(concat(setFunc##type, identifier));\
        returnObject.string = expand(concat(stringFunc##type, identifier));\
        returnObject.delete = expand(concat(deleteFunc##type, identifier));\
        returnObject.sort = expand(concat(sortFunc##type, identifier));\
        returnObject.fill = expand(concat(fillFunc##type, identifier));\
        returnObject;\
    })

    #define constructObject(arraySize, type) constructObjectInternal(arraySize, type, __COUNTER__)

    #define declareObjectType(type) \
    typedef struct type##Object {\
        char *id;\
        type *array;\
        size_t size;\
        size_t (*length)(void);\
        char *(*string)(void);\
        char *stringAllocator;\
        void (*resize)(size_t newArraySize);\
        type *(*at)(size_t index);\
        void (*set)(size_t index, type value);\
        void (*fill)(type value);\
        type (*get)(size_t index);\
        void (*sort)(void);\
        void (*delete)(void);\
    } type##Object;\
    \
    size_t lengthFunc##type(type##Object *self) {\
        return self -> size;\
    }\
    \
    void resizeFunc##type(type##Object *self, size_t newArraySize) {\
        self -> size = newArraySize;\
        self -> array = (type *)realloc(self -> array, newArraySize * sizeof(type));\
        return;\
    }\
    \
    type *atFunc##type(type##Object *self, size_t index) {\
        if (index >= self -> size) {\
            fprintf(stderr, "Index out of bounds. Terminating");\
            exit(1);\
        }\
        return self -> array + index;\
    }\
    \
    type getFunc##type(type##Object *self, size_t index) {\
        return *atFunc##type(self, index);\
    }\
    \
    void setFunc##type(type##Object *self, size_t index, type value) {\
        *atFunc##type(self, index) = value;\
        return;\
    }\
    \
    void fillFunc##type(type##Object *self, type value) {\
        for (size_t i=0; i < self -> length(); i++) {\
            self -> set(i, value);\
        }\
        return;\
    }\
    \
    char *stringFunc##type(type##Object *self) {\
        char *startFormatter;\
        char *endFormatter;\
        if (sizeof(type) == 1) {\
            startFormatter = "%c, ";\
            endFormatter = "%c}";\
        } else if ((type)0 - 1 > 0) {\
            startFormatter = "%llu, ";\
            endFormatter = "%llu}";\
        } else {\
            startFormatter = "%lld, ";\
            endFormatter = "%lld}";\
        }\
        if (self -> stringAllocator) {\
            free(self -> stringAllocator);\
            self -> stringAllocator = NULL;\
        }\
        char *output = (char *)malloc(self -> size * 12 + 4);\
        output[0] = '\0';\
        strcat(output, "{");\
        char buffer[256];\
        for (size_t i = 0; i < self -> size - 1; i++) {\
            sprintf(buffer, startFormatter, self -> array[i]);\
            strcat(output, buffer);\
        }\
        sprintf(buffer, endFormatter, self -> array[self -> size - 1]);\
        strcat(output, buffer);\
        self -> stringAllocator = output;\
        return output;\
    }\
    \
    void deleteFunc##type(type##Object *self) {\
        if (self -> stringAllocator) {\
            free(self -> stringAllocator);\
        }\
        free(self);\
        return;\
    }\
    \
    void merge##type(type *array1, type *array2, size_t size1, size_t size2) {\
        type *internalArray = (type *)malloc((size1 + size2) * sizeof(type));\
        size_t array1Index = 0; \
        size_t array2Index = 0;\
        size_t totalSize = size1 + size2;\
        while ((array1Index < size1) && (array2Index < size2)) {\
            if (array1[array1Index] < array2[array2Index]) {\
                internalArray[array1Index + array2Index] = array1[array1Index];\
                array1Index++;\
            } else {\
                internalArray[array1Index + array2Index] = array2[array2Index];\
                array2Index++;\
            }\
        }\
        while (array1Index < (size1)) {\
            internalArray[array1Index + array2Index] = array1[array1Index];\
            array1Index++;\
        }\
        while (array2Index < (size2)) {\
            internalArray[array1Index + array2Index] = array2[array2Index];\
            array2Index++;\
        }\
        memcpy(array1, internalArray, totalSize * sizeof(type));\
        free(internalArray);\
        return;\
    }\
    \
    size_t partition##type(size_t size) {\
        return size / 2UL;\
    }\
    \
    void mergeSort##type(type *array1, size_t sizeTotal) {\
        size_t partition2Index = partition##type(sizeTotal);\
        type *array2 = array1 + partition2Index;\
        size_t size1 = partition2Index;\
        size_t size2 = sizeTotal - partition2Index;\
        if (sizeTotal <=1) return;\
        mergeSort##type(array1, size1);\
        mergeSort##type(array2, size2);\
        merge##type(array1, array2, size1, size2);\
        return;\
    }\
    \
    void sortFunc##type(type##Object *self) {\
        mergeSort##type(self -> array, self -> size);\
    }\
    \
    type##Object internalObjectAllocator##type(size_t arraySize) {\
        if (!arraySize) {\
            fprintf(stderr, "Array size must be positive.\n");\
            exit(1);\
        }\
        type##Object returnValue;\
        returnValue.array = (type *)calloc(arraySize, sizeof(type));\
        returnValue.size = arraySize;\
        returnValue.stringAllocator = NULL;\
        return returnValue;\
    }
#endif