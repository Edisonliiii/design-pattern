# include <iostream>
# include <string>
# include <vector>


#include "Person.h"
#include "PersonBuilder.h"
#include "PersonBuilderBase.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"


/* Builder设计思路
   1. Builder can have a fluent interface that is usable for complicated construction using a single invocation chain
      To support this, builder functions should return this / *this

   2. To force the user of the API to use a Builder, we can make the target obj's c'tor inaccessible and then define a static build()
      function that returns the builder

   3. A single builder interface can expose multiple subbuilders.
      Through clever use of inheritance and fluent interfaces, on can jump from one builder to another with ease.
 */


int main(int argc, char const *argv[])
{
    Person p =   Person::build().lives().at("123 London Road")
                                        .with_postcode("Sw1 1GB")
                                        .in("London")
                                .works().at("Google")
                                        .as_a("Software Engieer")
                                        .earning(10e6);

    std::cout << p << std::endl;
    return 0;
}
