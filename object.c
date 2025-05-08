#include "cobjects.h"

int main() {
    declareObjectType(uint32_t);
    uint32_tObject myObject = constructObject(10, uint32_t);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    myObject.push(15);
    myObject.push(20);
    myObject.push(30);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    printf("Object %s: %s\n", myObject.id, myObject.string());
}