#ifndef LOKI_SEQUENCE_INC_
#define LOKI_SEQUENCE_INC_

#include <loki/Typelist.h>

namespace Loki {
template <class T01 = NullType, class T02 = NullType, class T03 = NullType,
          class T04 = NullType, class T05 = NullType, class T06 = NullType,
          class T07 = NullType, class T08 = NullType, class T09 = NullType,
          class T10 = NullType, class T11 = NullType, class T12 = NullType,
          class T13 = NullType, class T14 = NullType, class T15 = NullType,
          class T16 = NullType, class T17 = NullType, class T18 = NullType,
          class T19 = NullType, class T20 = NullType>
struct Seq {
 private:
  typedef typename Seq<T02, T03, T04, T05, T06, T07, T08, T09, T10, T11, T12,
                       T13, T14, T15, T16, T17, T18, T19, T20>::Type TailResult;

 public:
  typedef TypeList<T01, TailResult> Type;
};  // Seq

template <>
struct Seq<> {
  typedef NullType Type;
};  // Seq <>
};  // namespace Loki

#endif