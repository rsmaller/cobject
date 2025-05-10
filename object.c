#include "cobjects.h"

int main() {
    declareObjectType(uint32_t);
    uint32_tObject myObject = _Object(10, uint32_t);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    myObject.push(15);
    myObject.push(200);
    myObject.push(30);
    printf("Object %s size after pushing 15, 200, and 30: %llu\n", myObject.id, myObject.length());
    printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
    myObject.sort();
    printf("Object %s after sort: %s\n", myObject.id, myObject.string());
    myObject.clear();
    printf("Object %s after clear: %s\n", myObject.id, myObject.string());
    myObject.push(30);
    printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
    myObject.push(30);
    printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
    myObject.delete();
    return 0;
}