#include "cobjects.h"

int main() {
    declareObjectType(char);
    declareObjectType(uint32_t);
    uint32_tObject myObject = constructObject(10, uint32_t);
    charObject myObject2 = constructObject(20, char);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    myObject.resize(15);
    printf("Object %s size: %llu\n", myObject.id, myObject.length());
    myObject.fill(12);
    myObject.set(3, 82);
    myObject.sort();
    printf("Object %s at index 0: %d\n", myObject.id, myObject.get(0));
    printf("%s\n", myObject.string());
    printf("\n");
    printf("Object %s size: %llu\n", myObject2.id, myObject2.length());
    myObject2.resize(30);
    printf("Object %s size: %llu\n", myObject2.id, myObject2.length());
    myObject2.fill(97);
    myObject2.set(3, 99);
    myObject2.sort();
    printf("Object %s at index 0: %d\n", myObject2.id, myObject2.get(0));
    printf("%s\n", myObject2.string());
}