#include <iostream>
#include <mr/common>

int main() {
	printf("Hello, this is a demo of libmr version %s\n", mr::version.toString().c_str());
}