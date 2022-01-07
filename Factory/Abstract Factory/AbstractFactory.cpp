#include <iostream>
#include <memory>

#include "DrinkFactory.h"


int main(int argc, char const *argv[])
{
    DrinkFactory df;
    df.make_drink("coffee", 100);
	return 0;
}