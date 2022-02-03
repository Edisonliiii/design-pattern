#ifndef LOKI_TYPELIST_INC_
#define LOKI_TYPELIST_INC_

#include "NullType.h"
#include "TypelistMacros.h"

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

 /**
  * @brief Why TypeList
  * When do the design patterns like Abstract Factory
  * The code volumn will increase as the subtype goes up
  * For example, tho we got HotDrinkFactory,
  * we still need to define and implement(overload) CoffeeFactory/TeaFactory
  * and if we need more, we need to impl more.
  *
  * but if we can do
  * typedef HotDrinkFactory<Coffee, Tea, Milk, Juice> DrinkFacotry
  * things will get better
  *
  * And the TypeList is a certain useful technique to realize such convience
  */
namespace Loki {
  /**
   * @brief The only use of TypeList is to carry type per se
   * without anything else, no values, no methods, no anything else, just type
   *
   * @tparam T
   * @tparam U
   */
  template<class T, class U>
  struct TypeList
  {
    typedef T Head; // first element, a non-typelist type by convention
    typedef U Tail; // second element, can be any typelist
  }; // TypeList def

  namespace TL { // typelist utility algorithms

    template
      <
      typename T1 = NullType, typename T2 = NullType, typename T3 = NullType,
      typename T4 = NullType, typename T5 = NullType, typename T6 = NullType,
      typename T7 = NullType, typename T8 = NullType, typename T9 = NullType,
      typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
      typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
      typename T16 = NullType, typename T17 = NullType, typename T18 = NullType
      >
      struct MakeTypeList
    {
    private:
      typedef typename MakeTypeList
        <
        T2, T3, T4,
        T5, T6, T7,
        T8, T9, T10,
        T11, T12, T13,
        T14, T15, T16,
        T17, T18
        >::Result TailResult;
    public:
      typedef TypeList<T1, TailResult> Result;
    }; // MakeTypeList sub-temp

    template<>
    struct MakeTypelist<>
    {
      typedef NullType Result;
    }; // MakeTypelist primary temp

    typedef TypeList<int, NullType> OneTypeOnly;

    // [3.3] linearizing typelist creation
    // Here SingedIntegrals is a TypeList
    typedef TypeList<signed char, TypeList<short int, TypeList<int, TypeList<long int, NullType> > > > SingedIntegrals;
    // Here, using recursive way to define a typelist, will benefit code reuseability
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

    // [3.6.1] TypeAtNonStrict
    template<class TList, unsigned int index, typename DefaultType = NullType>
    struct TypeAtNoneStrict
    {
      typedef DefaultType Result;
    }; // TypeAtNoneStrict

    template<class Head, class Tail, typename DefaultType>
    struct TypeAtNoneStrict<TypeList<Head, Tail>, 0, DefaultType>
    {
      typedef Head Result;
    };

    template<class Head, class Tail, unsigned int i, typename DefaultType>
    struct TypeAtNoneStrict<TypeList<Head, Tail>, i, DefaultType>
    {
      typedef typename TypeAtNoneStrict<Tail, i - 1, DefaultType>::Result Result;
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
    /**
     * @brief
     * if (TList is NullType and T is NullType):
     *  Result is NullType
     * else:
     *  if (TList is NullType and T is a single(nontypelist) type)
     *    Result is a typelist having T as its only element
     *  else:
     *    if (Tlist is Nulltype and T is a typelist):
     *      Result is T itself
     *    else if (TList is non-null):
     *      Result is a typelist having TList::Head as its head and
     *      the result of appending T to TList::Tail as its tail
     *
     * @tparam TList
     * @tparam T
     * @returns Result: the final result should be a specific type
     */
    template <class TList, class T> struct Append;

    template <>
    struct Append <NullType, NullType>
    {
      typedef NullType Result;
    };

    // if TList is null then the first inserted ele is the Result
    template <class T>
    struct Append <NullType, T>
    {
      typedef TYPELIST_1(T) Result;
    };
    template <class Head, class Tail>
    struct Append<NullType, TypeList<Head, Tail>>
    {
      typedef TypeList<Head, Tail> Result;
    };
    // unified Append operation for single types and typelists
    template <class Head, class Tail, class T>
    struct Append<TypeList<Head, Tail>, T>
    {
      typedef TypeList<Head, typename Append<Tail, T>::Result> Result;
    };
    // when we use it
    typedef Append<SingedIntegrals, TYPELIST_3(float, double, long double)>::Result SignedTypes;


    /**
     * @brief [3.9] Erasing a Type from a TypeList
     * There are two operations:
     * 1. erase only the first occurance
     * 2. erase all occurances of a given type
     *
     * input: TypeList TList, type T
     * output: Inner type definition Result
     *
     * if TList is NullType:
     *  Result is NullType
     * else
     *  if T is the same as TList::Head
     *    Result is TList::Tail
     *  else
     *    Result is a typelist having TList::Head as its head and the result of applying
     *    Erase to TList::Tail and T as its tail
     */
    template <class TList, class T> struct Erase;

    template <class T>
    struct Erase <NullType, T>
    {
      typedef NullType Result;
    };

    template<class T, class Tail>
    struct Erase <TypeList<T, Tail>, T>
    {
      // once we encounter T, we result the rest part of the typelist directly
      typedef Tail Result;
    };

    template <class Head, class Tail, class T>
    struct Erase <TypeList<Head, Tail>, T>
    {
      // once we want to remove something, we build a new TypeList and named it as result
      typedef TypeList<Head, typename Erase<Tail, T>::Result> Result;
    };

    template <class TList, class T> struct EraseAll;
    template <class T>
    struct EraseAll <NullType, T>
    {
      typedef NullType Result;
    };

    template <class T, class Tail>
    struct EraseAll <TypeList<T, Tail>, T>
    {
      // go all the way down the list removing the type
      typedef typename EraseAll<Tail, T>::Result Result;
    };

    template <class Head, class Tail, class T>
    struct EraseAll <TypeList<Head, Tail>, T>
    {
      typedef TypeList<Head, typename EraseAll<Tail, T>::Result> Result;
    };

    /**
     * @brief [3.10] Erasing Duplicates
     * Make sure that each type appears only once
     *
     * TYPELIST_6(Widget, Button, Widget, TextField,
     * ScrollBar, Button)
     *
     * We need to turn it into
     *
     * TYPELIST_4(Widget, Button, TextField, ScrollBar)
     *
     * input: Typelist TList
     * output: inner type definitio Result
     *
     * If TList is NullType:
     *   Result is NullType
     * Else
     *   Apply NoDuplicates to TList::Tail, obtaining a temp typelist L1
     *   Apply Erase to L1 and TList::Head, obtain L2 as result
     *   Result is a typelist whose head is TList::Head and whose tail is L2
     */

    template <class TList> struct NoDuplicates;

    template <>
    struct NoDuplicates<NullType>
    {
      typedef NullType Result;
    };

    template<class Head, class Tail>
    struct NoDuplicates <TypeList<Head, Tail>>
    {
    private:
      // this recursion will finish first
      typedef typename NoDuplicates<Tail>::Result L1;
      // we only start erase after there is no dup
      typedef typename Erase<L1, Head>::Result L2;
    public:
      typedef TypeList<Head, L2> Result;
    };

    /**
     * @brief [3.11] Replacing an element in a typelist
     *
     * Replace type T with type U in a typelist TList
     *
     * inputs: TList, T
     * output: inner type def Result
     *
     * If TList is NullType
     *   Result is NullType
     * Else
     *   if the head of TList is T
     *     Result is a typelist with U as its head and TList::Tail is its tail
     *   else
     *     Result is a typelist with TList::Head as its head and
     */
    template <class TList, class T, class U> struct Replace;

    template <class T, class U>
    struct Replace <NullType, T, U>
    {
      typedef NullType Result;
    };

    template<class T, class Tail, class U>
    struct Replace <TypeList<T, Tail>, T, U>
    {
      typedef TypeList<U, Tail> Result;
    };

    template <class Head, class Tail, class T, class U>
    struct Replace <TypeList<Head, Tail>, T, U>
    {
      typedef TypeList<Head, typename Replace<Tail, T, U>::Result> Result;
    };

    ////////////////////////////////////////////////////////////////////////////////
    // class template ReplaceAll
    // Replaces all occurences of a type in a typelist, with another type
    // Invocation (TList is a typelist, T, U are types):
    // Replace<TList, T, U>::Result
    // returns a typelist in which all occurences of T is replaced with U
    ////////////////////////////////////////////////////////////////////////////////

    template<class TList, class T, class U> struct ReplaceAll;
    template<class T, class U>
    struct ReplaceAll <NullType, T, U>
    {
      typedef NullType Result;
    };

    // partial-specialization only if the first element of TypeList is same as the element we want to replace
    template<class T, class Tail, class U>
    struct ReplaceAll<TypeList<T, Tail>, T, U>
    {
      typedef TypeList<U, typename ReplaceAll<Tail, T, U>::Result> Result;
    };

    template<class Head, class Tail, class T, class U>
    struct ReplaceAll<TypeList<Head, Tail>, T, U>
    {
      typedef TypeList<Head, typename ReplaceAll<Tail, T, U>::Result> Result;
    };

    ////////////////////////////////////////////////////////////////////////////////
    // class template Reverse
    // Reverses a typelist
    // Invocation (TList is a typelist):
    // Reverse<TList>::Result
    // returns a typelist that is TList reversed
    ////////////////////////////////////////////////////////////////////////////////
    template<class TList> struct Reverse;

    template<>
    struct Reverse <NullType>
    {
      typedef NullType Result;
    };

    template<class Head, class Tail>
    struct Reverse <TypeList<Head, Tail>>
    {
      typedef typename Append<typename Reverse<Tail>::Result, Head>::Result Result;
    };

    ////////////////////////////////////////////////////////////////////////////////
    // class template MostDerived
    // Finds the type in a typelist that is the most derived from a given type
    // Invocation (TList is a typelist, T is a type):
    // MostDerived<TList, T>::Result
    // returns the type in TList that's the most derived from T
    ////////////////////////////////////////////////////////////////////////////////
    template <class TList, class T> struct MostDerived;

    template <class T>
    struct MostDerived<NullType, T>
    {
      typedef T Result;
    };

    template <class Head, class Tail, class T>
    struct MostDerived<TypeList<Head, Tail>, T>
    {
    private:
      typedef typename MostDerived<Tail, T>::Result Candidate;
    public:
      ;
    }

  };// namespace TL
}; //namespace Loki

#endif