# include <iostream>
# include <stdlib.h>
/**
 * @file typelist.h
 * @author your name (you@domain.com)
 * @brief typelist experiment code
 * @version 0.1
 * @date 2022-01-02
 *
 * @copyright Copyright (c) 2022
 *
 */

class NullType {}; // NullType

template<class T, class U>
struct TypeList
{
  typedef T Head; // first element, a non-typelist type by convention
  typedef U Tail; // second element, can be any typelist
}; // TypeList def

typedef TypeList<int, NullType> OneTypeOnly;

// [3.3] linearizing typelist creation
typedef TypeList<signed char, TypeList<short int, TypeList<int, TypeList<long int, NullType> > > > SingedIntegrals;

# define TYPELIST_1(T1) TypeList<T1, NullType>
# define TYPELIST_2(T1, T2) TypeList<T1, TYPELIST_1(T2)>
# define TYPELIST_3(T1, T2, T3) TypeList<T1, TYPELIST_2(T2, T3)>
# define TYPELIST_4(T1, T2, T3, T4) TypeList<T1, TYPELIST_3(T2,T3,T4)>

// ... 
// same drill can be used for infinima
// Therefore SingedIntegrals could be represented as
typedef TYPELIST_4(signed char, short int, int, long int)SingedIntegrals;

// drawback: still clumsy, for instance accessing 
// the last ele in Singed Integrals requires using
SingedIntegrals::Tail::Tail::Head fakeVariable;

// [3.4] Calculating Length
template<class TList> struct Length;

template<>
struct Length<NullType>
{
  enum { value = 0 };
}; // the length of a null typelist is 0

template<class T, class U>
struct Length<TypeList<T, U> >
{
  enum { value = 1 + Length<U>::value };
}; // recursive calculate length

// Therefore, we can allowcate 4 elements for intsRtti
std::type_info* intsRtti[Length<SingedIntegrals>::value];


// [3.5] Intermezzo
// All compile-time values are immutable
// 1. after define an integral constant, say enumerate val, you can not change it
// 2. type defintions have the same rule
// Therefore there is no way to make the above resursive method interactive


// [3.6] Indexed Access
// declare of a template for an indexed operation
// should have one class, then we can do partial specialization

// this is primary template
// Primary template Do NOT have template argument list
template <class TList, unsigned int index> struct TypeAt; // TypeAt

// Template parameters specified in a primary template but not used in a partial specialization are omitted from the template parameter list of the partial specialization.
// 这里 primary template中定义出来的template parameter list直接会被omitted
template <class Head, class Tail>       // this is template parameters list
struct TypeAt<TypeList<Head, Tail>, 0>  // this is template argument list
{
  typedef Head Result;
};

template<class Head, class Tail, unsigned int i>
struct TypeAt <TypeList<Head, Tail>, i>
{
  typedef typename TypeAt<Tail, i - 1>::Result Result;
};

// [3.7] Searching Typelists
// Inputs: TypeList: TList, type T (type we are trying to search)
// Output: Inner compile-time constant value (the idx of type in the TList)
// primary template
template <class TList, class T> struct IndexOf;
// if TList == NullType
template<class T>
struct IndexOf<NullType, T>
{
  enum { value = -1 };
};
// if the head of TList is T
template<class T, class Tail>
struct IndexOf<TypeList<T, Tail>, T>
{
  enum { value = 0 };
};

template <class Head, class Tail, class T>
struct IndexOf<TypeList<Head, Tail>, T>
{
private:
  enum { temp = IndexOf<Tail, T>::value }; // will unfold from here first
public:
  enum { value = temp == -1 ? -1 : 1 + temp }; // unfold from here secondly
};

// [3.8] appending to typelists
template <class TList, class T> struct Append;

template <>
struct Append <NullType, NullType>
{
  typedef NullType Result;
};

template <class T>
struct Append <NullType, T>
{
  typedef TYPELIST_1(T) Result;
};

