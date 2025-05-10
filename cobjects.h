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

#define to ;

#define method .

#define attribute .

#define done ;

#define print printf

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

#define TYPESTRUCT(type)\
    typedef struct type##Object_Internal {\
        char *id;\
        type *array;\
        size_t capacity;\
        int filledIndex;\
        size_t (*length)(void);\
        char *(*string)(void);\
        char *stringAllocator;\
        void (*resize)(size_t newArraySize);\
        type *(*at)(size_t index);\
        void (*set)(size_t index, type value);\
        void (*fill)(type value);\
        void (*push)(type value);\
        type (*pop)(void);\
        type (*get)(size_t index);\
        void (*sort)(void);\
        void (*delete)(void);\
        void (*clear)(void);\
    } type##Object_Internal;\
\
    typedef struct type##Object {\
        char const * const id;\
        type *array;\
        size_t capacity;\
        int filledIndex;\
        size_t (* const length)(void);\
        char *(* const string)(void);\
        char *stringAllocator;\
        void (* const resize)(size_t newArraySize);\
        type *(* const at)(size_t index);\
        void (* const set)(size_t index, type value);\
        void (* const fill)(type value);\
        void (* const push)(type value);\
        type (* const pop)(void);\
        type (* const get)(size_t index);\
        void (* const sort)(void);\
        void (* const delete)(void);\
        void (* const clear)(void);\
    } type##Object;\

#define constructObjectInternal(arraySize, type, identifier) ({\
    size_t sizeValue = arraySize;\
    if (!sizeValue) {\
        fprintf(stderr, "Array size must be positive.\n");\
        exit(1);\
    } else if (sizeValue < 4) {\
        sizeValue = 4;\
    }\
    type##Object_Internal returnObject;\
    decorate(size_t, lengthFunc##type, identifier, &returnObject);\
    decorate(type, popFunc##type, identifier, &returnObject);\
    decorate(char *, stringFunc##type, identifier, &returnObject);\
    decorate_void(deleteFunc##type, identifier,  &returnObject);\
    decorate_void(clearFunc##type, identifier,  &returnObject);\
    decorate_void(sortFunc##type, identifier,  &returnObject);\
    expanded_decorate_void(fillFunc##type, identifier, type, value, &returnObject);\
    expanded_decorate_void(pushFunc##type, identifier, type, value, &returnObject);\
    expanded_decorate(type *, atFunc##type, identifier, size_t, index, &returnObject);\
    expanded_decorate(type, getFunc##type, identifier, size_t, index, &returnObject);\
    double_expanded_decorate_void(setFunc##type, identifier, size_t, index, type, value, &returnObject);\
    returnObject = (type##Object_Internal){\
        .array              = (type *)calloc(sizeValue, sizeof(type)),\
        .capacity           = sizeValue,\
        .filledIndex        = -1,\
        .stringAllocator    = NULL,\
        .id                 = strTokenize(identifier),\
        .length             = expand(concat(lengthFunc##type, identifier)),\
        .at                 = expand(concat(atFunc##type, identifier)),\
        .get                = expand(concat(getFunc##type, identifier)),\
        .set                = expand(concat(setFunc##type, identifier)),\
        .string             = expand(concat(stringFunc##type, identifier)),\
        .delete             = expand(concat(deleteFunc##type, identifier)),\
        .clear              = expand(concat(clearFunc##type, identifier)),\
        .sort               = expand(concat(sortFunc##type, identifier)),\
        .fill               = expand(concat(fillFunc##type, identifier)),\
        .push               = expand(concat(pushFunc##type, identifier)),\
        .pop                = expand(concat(popFunc##type, identifier))\
    };\
    if (!returnObject.array) {\
        fprintf(stderr, "Object construction failure. Terminating\n");\
        exit(1);\
    }\
    type##Object castedReturnObject = *(type##Object *)&returnObject;\
    castedReturnObject;\
})

#define _Object(arraySize, type) constructObjectInternal(arraySize, type, __COUNTER__)

#define declareObjectType(type) \
    TYPESTRUCT(type) \
    \
    size_t lengthFunc##type(type##Object_Internal *self) {\
        return self -> filledIndex + 1;\
    }\
    \
    type *atFunc##type(type##Object_Internal *self, size_t index) {\
        if (index >= self -> capacity) {\
            fprintf(stderr, "Index out of bounds. Terminating");\
            exit(1);\
        }\
        return self -> array + index;\
    }\
    \
    void pushFunc##type(type##Object_Internal *self, type value) {\
        self -> filledIndex++;\
        self -> array[self -> length() - 1] = value;\
        if (self -> filledIndex >= self -> capacity / 2) {\
            self -> capacity *= 2;\
            self -> array = (type *)realloc(self -> array, self -> capacity * sizeof(type));\
            if (!self -> array) {\
                fprintf(stderr, "Object reallocation failure. Terminating\n");\
                exit(1);\
            }\
        }\
    }\
    type popFunc##type(type##Object_Internal *self) {\
        if (self -> filledIndex < 0) {\
            return 0;\
        }\
        type returnValue = self -> array[self -> length() - 1];\
        self -> filledIndex--;\
        return returnValue;\
    }\
    \
    type getFunc##type(type##Object_Internal *self, size_t index) {\
        return *atFunc##type(self, index);\
    }\
    \
    void setFunc##type(type##Object_Internal *self, size_t index, type value) {\
        *atFunc##type(self, index) = value;\
        if (index > self -> filledIndex) {\
            self -> filledIndex = index;\
        }\
        if (self -> filledIndex >= self -> capacity / 2) {\
            self -> capacity *= 2;\
            self -> array = (type *)realloc(self -> array, self -> capacity * sizeof(type));\
            if (!self -> array) {\
                fprintf(stderr, "Object reallocation failure. Terminating\n");\
                exit(1);\
            }\
        }\
        return;\
    }\
    \
    void fillFunc##type(type##Object_Internal *self, type value) {\
        for (size_t i=0; i < self -> length(); i++) {\
            self -> set(i, value);\
        }\
        return;\
    }\
    \
    char *stringFunc##type(type##Object_Internal *self) {\
        if (self -> filledIndex < 0) {\
            char *returnValue = (char *)malloc(3 * sizeof(char));\
            returnValue[0] = '{';\
            returnValue[1] = '}';\
            returnValue[2] = '\0';\
            return returnValue;\
        }\
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
        char *output = (char *)malloc(self -> length() * 12 + 4);\
        output[0] = '\0';\
        strcat(output, "{");\
        char buffer[256];\
        for (size_t i = 0; i < self -> length() - 1; i++) {\
            sprintf(buffer, startFormatter, self -> array[i]);\
            strcat(output, buffer);\
        }\
        sprintf(buffer, endFormatter, self -> array[self -> length() - 1]);\
        strcat(output, buffer);\
        self -> stringAllocator = output;\
        return output;\
    }\
    \
    void deleteFunc##type(type##Object_Internal *self) {\
        if (self -> stringAllocator) {\
            free(self -> stringAllocator);\
        }\
        return;\
    }\
    \
    void clearFunc##type(type##Object_Internal *self) {\
        if (self -> stringAllocator) {\
            free(self -> stringAllocator);\
            self -> stringAllocator = NULL;\
        }\
        self -> filledIndex = -1;\
        return;\
    }\
    \
    void merge##type(type *array1, type *array2, size_t size1, size_t size2) {\
        type *internalArray = (type *)malloc((size1 + size2) * sizeof(type));\
        if (!internalArray) {\
            fprintf(stderr, "Merge sort allocation failure. Terminating\n");\
            exit(1);\
        }\
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
    void sortFunc##type(type##Object_Internal *self) {\
        /* Applies only to filled data. */\
        mergeSort##type(self -> array, self -> length());\
    }\


#ifdef __INTELLISENSE__ // prevents IntelliSense from complaining about the GCC-specific macro
    #define _Object(arg1, arg2) {0}
    #define declareObjectType(type) TYPESTRUCT(type)
#endif