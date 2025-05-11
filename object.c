#include "cobjects.h"

int main() {
    int x[5] = {1,2,3,4,5};
    typedef int* intPtr to declareObjectType(intPtr);
    declareObjectType(int);
    intObject myObject = _Object(10, int);

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

    intPtrObject myObject2 = _Object(10, intPtr);
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