#include <iostream>
#include "DrinkFactory.h"

int main(int argc, char const *argv[])
{
    DrinkWithVolumeFactory df;
    df.make_drink("coffee", 1000);
    df.make_drink("coffee", 155);
    df.make_drink("coffee", 154245);
    df.make_drink("coffee", 15);
    df.make_drink("coffee", 245);
	return 0;
}