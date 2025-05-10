#include "cobjects.h"

// int main() {
//     typedef unsigned int uint;
//     declareObjectType(uint);
//     uintObject myObject = _Object(10, uint);
//     printf("Object %s size: %llu\n", myObject.id, myObject.length());
//     myObject.push(15);
//     myObject.push(200);
//     myObject.push(30);
//     printf("Object %s size after pushing 15, 200, and 30: %llu\n", myObject.id, myObject.length());
//     printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
//     myObject.sort();
//     printf("Object %s after sort: %s\n", myObject.id, myObject.string());
//     myObject.clear();
//     printf("Object %s after clear: %s\n", myObject.id, myObject.string());
//     myObject.push(30);
//     printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
//     myObject.push(30);
//     printf("Object %s after pushing: %s\n", myObject.id, myObject.string());
//     myObject.delete();
//     return 0;
// }

int main() {
    typedef unsigned int uint to declareObjectType(uint) done
    uintObject myObject = _Object(10, uint) done
    print("Object %s size: %llu\n", myObject attribute id, myObject method length()) done
    myObject method push(15) done
    myObject method push(200) done
    myObject method push(30) done
    print("Object %s size after pushing 15, 200, and 30: %llu\n", myObject attribute id, myObject method length()) done
    print("Object %s after pushing: %s\n", myObject attribute id, myObject method string()) done
    myObject method sort() done
    print("Object %s after sort: %s\n", myObject attribute id, myObject method string()) done
    myObject method clear() done
    print("Object %s after clear: %s\n", myObject attribute id, myObject method string()) done
    myObject method push(30) done
    print("Object %s after pushing: %s\n", myObject attribute id, myObject method string()) done
    myObject method push(30) done
    print("Object %s after pushing: %s\n", myObject attribute id, myObject method string()) done
    myObject method delete() done
    return 0 done
}