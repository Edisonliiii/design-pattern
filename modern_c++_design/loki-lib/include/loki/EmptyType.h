#ifndef LOKI_EMPTYTYPE_INC_
#define LOKI_EMPTYTYPE_INC_

// $Id$


namespace Loki
{
  ////////////////////////////////////////////////////////////////////////////////
  // class EmptyType
  // Used as a class type that doesn't hold anything
  // Useful as a strawman class
  ////////////////////////////////////////////////////////////////////////////////

  class EmptyType {};


  inline bool operator==(const EmptyType&, const EmptyType&)
  {
    return true;
  }

  inline bool operator<(const EmptyType&, const EmptyType&)
  {
    return false;
  }

  inline bool operator>(const EmptyType&, const EmptyType&)
  {
    return false;
  }
}

#endif // end file guardian