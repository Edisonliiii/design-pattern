// $Id$

// ----------------------------------------------------------------------------

#include <loki/SmallObj.h>

#include <cassert>
#include <climits>
#include <vector>
#include <bitset>


//#define DO_EXTRA_LOKI_TESTS
//#define USE_NEW_TO_ALLOCATE
//#define LOKI_CHECK_FOR_CORRUPTION

#ifdef DO_EXTRA_LOKI_TESTS
#include <iostream>
#endif

#if !defined( nullptr )
#define nullptr 0
#endif


namespace Loki
{
  namespace Private
  {
    class Chunk
    {
    private:
      friend class FixedAllocator;
      /// ptr to array of allocated blocks
      unsigned char* pData_;
      /// index of first empty block
      unsigned char firstAvailableBlock_;
      /// count of empty blocks
      unsigned char blocksAvailable_;

      bool Init(::std::size_t blockSize, unsigned char blocks);
      void* Allocate(::std::size_t blockSize);
      /**
       * @brief Deallocate a block within a Chunk.
       * O(1),
       *
       * @param p
       * @param blockSize
       */
      void Deallocate(void* p, ::std::size_t blockSize);
      void Reset(::std::size_t blockSize, unsigned char blocks);

      void Release();
      /** Determines if the Chunk has been corrupted.(check-wise check)
        @param numBlocks Total # of blocks in the Chunk.
        @param blockSize # of bytes in each block.
        @param checkIndexes True if caller wants to check indexes of available blocks for corruption.  If false, then caller wants to skip some tests tests just to run faster.  (Debug version does more checks, but release version runs faster.)
        @return True if Chunk is corrupt.
        */
      bool IsCorrupt(unsigned char numBlocks, ::std::size_t blockSize, bool checkIndexes) const;
      /** Determines if block is available. (chunk-wise check)
        @param p Address of block managed by Chunk.
        @param numBlocks Total # of blocks in the Chunk.
        @param blockSize # of bytes in each block.
        @return True if block is available, else false if allocated.
        */
      bool IsBlockAvailable(void* p, unsigned char numBlocks, ::std::size_t blockSize) const;

      // return true if block at address P is inside this chunk
      inline bool HashBlock(void* p, ::std::size_t chunkLength) const
      {
        unsigned char* pc = static_cast<unsigned char*> (p);
        return (pData_ <= pc) && (pc < pData_ + chunkLength);
      }

      inline bool HasAvailable(unsigned char numBlocks) const
      {
        return (blocksAvailable_ == numBlocks);
      }

      inline bool IsFilled(void) const
      {
        return (0 == blocksAvailable_);
      }
    }; // class Chunk

    class FixedAllocator
    {
    private:
      void DoDeallocate(void* p);
      /**
       * @brief Creates an empty Chunk and adds it to the end of
       * the ChunkList.
       *
       * @return true for success
       * @return false for failure
       */
      bool MakeNewChunk(void);
      Chunk* VicinityFind(void* p) const;
      // disable copy c'tor and assignment operator
      FixedAllocator(const FixedAllocator&) = delete;
      FixedAllocator& operator=(const FixedAllocator&);

      /// type of container used to hold Chunks
      typedef ::std::vector<Chunk> Chunks;
      typedef Chunks::iterator ChunkIter;
      typedef Chunks::const_iterator ChunkCIter; // for const container

      /// some important numbers
      static unsigned char MinObjectsPerChunk_;
      static unsigned char MaxObjectsPerChunk_;

      // # of bytes in a single block within a Chunk
      ::std::size_t blockSize_;
      // # of blocks managed by each Chunk
      unsigned char numBlocks_;

      // Container of Chunks
      Chunks chunks_;
      // ptr to chunk used for last/next allocation
      Chunk* allocChunk_;
      // ptr to chunk used for last/next deallocation
      Chunk* deallocChunk_;
      // ptr to the only empty Chunk if there is one, else nullptr
      Chunk* emptyChunk_;

    public:
      /**
       * @brief Create a FixedAllocator which manages blocks of 'blockSize'
       *
       */
      FixedAllocator();
      ~FixedAllocator();
      void Initialize(::std::size_t blockSize, ::std::size_t pageSize);
      /**
       * @brief  returns a ptr to allocated memory block of fixed size
       *
       * @return void*
       */
      void* Allocate(void);
      /**
       * @brief Deallocate a memory block previously allocated
       * with Allocate. If the block is not owned by this
       * FixedAllocator, it returns false so that SmallObjAll-
       * can call the default deallocator. If the block was found
       * this returns true
       *
       * @param p
       * @param hint
       * @return true
       * @return false
       */
      bool Deallocate(void* p, Chunk* hint);
      inline ::std::size_t BlockSize() const { return blockSize_; }
      /**
       * @brief Release the memory used by the empty Chunk.
       * This will take O(1) time under any situation
       *
       * @return true if empty chunk found and release
       * @return false if none empty
       */
      bool TrimEmptyChunk(void);
      bool TrimChunkList(void);
      /**
       * @brief Returns count of mepty Chunk held by this
       * allocator.
       *
       * @return ::std::size_t
       */
      ::std::size_t CountEmptyChunks(void) const;
      bool IsCorrupt(void) const;
      const Chunk* HasBlock(void* p) const;
      inline Chunk* HasBlock(void* p)
      {
        return const_cast<Chunk*> (
          const_cast<const FixedAllocator*> (this)->HasBlock(p)
          );
      }
    };// class FixedAllocator

    unsigned char FixedAllocator::MinObjectsPerChunk_ = 8;
    unsigned char FixedAllocator::MaxObjectsPerChunk_ = UCHAR_MAX;

    // FixedAllocator -------------------------------------------
    FixedAllocator::FixedAllocator()
      : blockSize_(0)
      , numBlocks_(0)
      , chunks_(0)
      , allocChunk_(nullptr)
      , deallocChunk_(nullptr)
      , emptyChunk_(nullptr) {}

    ~FixedAllocator::FixedAllocator()
    {
#ifdef DO_EXTRA_LOKI_TESTS
      TrimEmptyChunk();
      assert(chunks_.empty() && "Memory leak detected!");
#endif
      for (ChunkIter i(chunks_.begin()); i != chunks_.end(); ++i)
      {
        i->Release();
      }
    }

    void FixedAllocator::Initialize(::std::size_t blockSize, ::std::size_t pageSize)
    {
      assert(blockSize > 0);
      assert(pageSize >= blockSize);
      blockSize_ = blockSize;

      ::std::size_t numBlocks = pageSize / blockSize;
      if (numBlocks > MaxObjectsPerChunk_) numBlocks = MaxObjectsPerChunk_;
      else if (numBlocks < MinObjectsPerChunk_) numBlocks = MinObjectsPerChunk_;
      numBlocks_ = static_cast<unsigned char> (numBlocks);
      assert(numBlocks_ == numBlocks);
    }

    ::std::size_t FixedAllocator::CountEmptyChunks(void) const
    {
# ifdef DO_EXTRA_LOKI_TESTS
      ::std::size_t count = 0;
      for (ChunkCIter it(chunks_.begin()); it != chunks_.end(); ++it)
      {
        const Chunk& chunk = *it;
        if (chunk.HasAvailable(numBlocks_)) ++count;
      }
      return count;
# else
      return (nullptr == emptyChunk_) ? 0 : 1;
# endif
    }

    bool FixedAllocator::IsCorrupt(void) const
    {
      const bool isEmpty = chunks_.empty();
      ChunkCIter start(chunks_.begin());
      ChunkCIter last(chunks_.end());
      const ::std::size_t emptyChunkCount = CountEmptyChunks();

      if (isEmpty)
      {
        if (start != last)
        {
          assert(false); // check the current condition is met or not
          return true;
        }
        if (0 < emptyChunkCount)
        {
          assert(false);
          return true;
        }
        if (nullptr != deallocChunk_)
        {
          assert(false);
          return true;
        }
        if (nullptr != allocChunk_)
        {
          assert(false);
          return true;
        }
        if (nullptr != emptyChunk_)
        {
          assert(false);
          return true;
        }
      }
      else
      {
        const Chunk* front = &chunks_.front();
        const Chunk* back = &chunks_.back();
        if (start >= last)
        {
          assert(false);
          return true;
        }
        if (back < deallocChunk_)
        {
          assert(false);
          return true;
        }
        if (back < allocChunk_)
        {
          assert(false);
          return true;
        }
        if (front > deallocChunk_)
        {
          assert(false);
          return true;
        }
        if (front > allocChunk_)
        {
          assert(false);
          return true;
        }

        switch (emptyChunkCount)
        {
        case 0:
          if (emptyChunk_ != nullptr)
          {
            assert(false);
            return true;
          }
          break;
        case 1:
          if (emptyChunk_ == nullptr)
          {
            assert(false);
            return true;
          }
          if (back < emptyChunk_)
          {
            assert(false);
            return true;
          }
          if (front > emptyChunk_)
          {
            assert(false);
            return true;
          }
          if (!emptyChunk_->HasAvailable(numBlocks_))
          {
            // This may imply somebody tried to delete a block twice.
            assert(false);
            return true;
          }
          break;
        default:
          assert(false);
          return true;
        }

        for (ChunkCIter it(start); it != last; ++it)
        {
          const Chunk& chunk = *it;
          if (chunk.IsCorrupt(numBlocks_, blockSize_, true))
          {
            return true;
          }
        }
      }
      return false;
    }

    const Chunk* FixedAllocator::HasBlock(void* p) const
    {
      const ::std::size_t chunkLength = numBlocks_ * blockSize_;
      for (ChunkCIter it(chunks_.begin()); it != chunks_.end(); ++it)
      {
        const Chunk& chunk = *it;
        if (chunk.HasBlock(p, chunkLength))
        {
          return &chunk;
        }
      }
      return nullptr;
    }

    bool FixedAllocator::TrimEmptyChunk(void)
    {
      assert((nullptr == emptyChunk_) || (emptyChunk_->HasAvailable(numBlocks_)));
      if (nullptr == emptyChunk_)
      {
        return false;
      }

      // if emptyChunk_ points to valid Chunk, then chunk list is not empty
      assert(!chunks_.empty());
      // And there should be exactly 1 empty Chunk
      assert(1 == CountEmptyChunks());

      Chunk* lastChunk = &chunks_.back();
      if (lastChunk != emptyChunk_)
      {
        ::std::swap(*emptyChunk_, *lastChunk);
      }
      assert(lastChunk->HasAvailable(numBlocks_));
      lastChunk->Release();
      chunks_.pop_back();

      if (chunks_.empty())
      {
        allocChunk_ = nullptr;
        deallocChunk_ = nullptr;
      }
      else
      {
        if (deallocChunk_ == emptyChunk_)
        {
          deallocChunk_ = &chunks_.front();
          assert(deallocChunk_->blocksAvailable_ < numBlocks_);
        }
        if (allocChunk_ == emptyChunk_)
        {
          allocChunk_ = &chunks_.back();
          assert(allocChunk_->blocksAvailable_ < numBlocks_);
        }
      }
      emptyChunk_ = nullptr;
      assert(0 == CountEmptyChunks());
      return true;
    }

    bool FixedAllocator::TrimChunkList(void)
    {
      if (chunks_.empty())
      {
        assert(nullptr == allocChunk_);
        assert(nullptr == deallocChunk_);
      }
      if (chunks_.size() == chunks_.capacity())
      {
        return false;
      }

      {
        // use the "make-a-temp-and-swap" trick to remove excess capacity
        Chunks temp(chunks_);
        temp.swap(chunks_);
      }

      if (chunks_.empty())
      {
        deallocChunk_ = nullptr;
        allocChunk_ = nullptr;
      }
      else
      {
        deallocChunk_ = &chunks_.front();
        allocChunk_ = &chunks_.back();
      }
      return true;
    }

    bool FixedAllocator::MakeNewChunk(void)
    {
      bool allocated = false;
      try
      {
        ::std::size_t size = chunks_.size();
        if (chunks_.capacity() == size)
        {
          if (0 == size) size = 4;
          chunks_.reserve(size * 2);
        }
        Chunk newChunk;
        allocated = newChunk.Init(blockSize_, numBlocks_);
        if (allocated)
        {
          chunks_.push_back(newChunk);
        }
      }
      catch (...)
      {
        allocated = false;
      }
      if (!allocated) return false;

      allocChunk_ = &chunks_.back();
      deallocChunk_ = &chunks_.front();
      return true;
    }

    void* FixedAllocator::Allocate(void)
    {
      // prove emptyChunk points to nowhere or a truly empty Chunk
      assert((nullptr == emptyChunk_) || (emptyChunk_->HasAvailable(numBlocks_)));
      assert(CountEmptyChunks() < 2);

      if ((nullptr == allocChunk_) || allocChunk_->IsFilled())
      {
        if (nullptr != emptyChunk_) // if emptyChunk is empty
        {
          allocChunk_ = emptyChunk_;
          emptyChunk_ = nullptr;
        }
        else
        {
          for (ChunkIter i(chunks_.begin()); ; ++i)
          {
            if (chunks_.end() == i)
            {
              if (!MakeNewChunk()) { return false; }
              break;
            }
            if (!i->IsFilled()) // if discover an empty chunk
            {
              allocChunk_ = &*i;
              break;
            }
          }
        }
      }
      else if (allocChunk_ == emptyChunk_)
      {
        // detach emptyChunk from allocChunk, cuz
        // after calling allocChunk -> Allocate(blockSize)
        // the chunk is no longer empty
        emptyChunk_ = nullptr;
      }
      assert(allocChunk_ != nullptr);
      assert(!allocChunk_->IsFilled());
      void* place = allocChunk_->Allocate(blockSize_);
      // prove either emptyChunk_ points nowhere, or points to a truly empty Chunk.
      assert((nullptr == emptyChunk_) || (emptyChunk_->HasAvailable(numBlocks_)));
      assert(CountEmptyChunks() < 2);
# ifdef LOKI_CHECK_FOR_CORRUPTION
      if (allocChunk_->IsCorrupt(numBlocks_, blockSize_, true))
      {
        assert(false);
        return nullptr;
      }
# endif
      return place;
    }

    bool FixedAllocator::Deallocate(void* p, Chunk* hint)
    {
      assert(!chunks_.empty());
      // check address relationships (to prove if it was a part
      // of the current FixedAllocator), make sure those two ptrs
      // are pointing at the legit range
      assert(&chunks_.front() <= deallocChunk_);
      assert(&chunks_.back() >= deallocChunk_);
      assert(&chunks_.front() <= allocChunk_);
      assert(&chunks_.back() >= allocChunk_);
      assert(CountEmptyChunks() < 2);

      Chunk* foundChunk = nullptr;
      const ::std::size_t chunkLength = numBlocks_ * blockSize_;
      if ((nullptr != hint) && (hint->HashBlock(p, chunkLength)))
      {
        foundChunk = hint;
      }
      else if (deallocChunk_->HashBlock(p, chunkLength))
      {
        foundChunk = deallocChunk_;
      }
      else if (allocChunk_->HashBlock(p, chunkLength))
      {
        foundChunk = allocChunk_;
      }
      else
      {
        foundChunk = VicinityFind(p);
      }
      if (nullptr == foundChunk)
      {
        return false;
      }

      assert(foundChunk->HashBlock(p, chunkLength));
#ifdef LOKI_CHECK_FOR_CORREPUTION
      if (foundChunk->IsCorrupt(numBlocks_, blockSize_, true))
      {
        assert(false);
        return false;
      }
      if (foundChunk->IsBlockAvailable(p, numBlocks_, blockSize_))
      {
        assert(false);
        return false;
      }
#endif
      deallocChunk_ = foundChunk;
      DoDeallocate(p);
      assert(CountEmptyChunks() < 2);
      return true;
    }

    Chunk* FixedAllocator::VicinityFind(void* p) const
    {
      if (chunks_.empty())
      {
        return nullptr;
      }
      assert(deallocChunk_);

      const ::std::size_t chunkLength = numBlocks_ * blockSize_;
      Chunk* lo = deallocChunk_;
      Chunk* hi = deallocChunk_ + 1;
      const Chunk* loBound = &chunks_.front();
      const Chunk* hiBound = &chunks_.back() + 1;

      if (hi == hiBound) { hi = nullptr; }
      for (;;)
      {
        if (lo)
        {
          if (lo->HashBlock(p, chunkLength)) { return lo; }
          if (lo == loBound)
          {
            lo = nullptr;
            if (nullptr == hi) { break; }
          }
          else { --lo; }
        }
      }
    }

    // Chunk ----------------------------------------------------
    bool Chunk::Init(::std::size_t blockSize, unsigned char blocks)
    {
      assert(blockSize > 0);
      assert(blocks > 0);
      // overflow check
      const ::std::size_t allocSize = blockSize * blocks;
      assert(allocSize / blockSize == blocks);
# ifdef USE_NEW_TO_ALLOCATE
      // if this new operator fails, it will throw, and the exception will get caught one layer up
      pData_ = static_cast<unsigned char*> (::operator new (allocSize));
# else
      // use malloc
      pData_ = static_cast<unsigned char*> (::std::malloc(allocSize));
      if (nullptr == pData_) return false;
# endif
      Reset(blockSize, blocks);
      return true;
    }

    void Chunk::Reset(::std::size_t blockSize, unsigned char blocks)
    {
      assert(blockSize > 0);
      assert(blocks > 0);
      // overflow check
      assert((blockSize * blocks) / blockSize == blocks);

      firstAvailableBlock_ = 0;
      blocksAvailable_ = blocks;

      unsigned char i = 0;
      for (unsigned char* p = pData_; i != blocks; p += blockSize)
      {
        *p = ++i;
      }
    }

    void Chunk::Release()
    {
      assert(nullptr != pData_);
# ifdef USE_NEW_TO_ALLOCATE
      ::operator delete (pData_);
# else
      ::std::free(static_cast<void*>(pData_));
# endif
    }

    void* Chunk::Allocate(::std::size_t blockSize)
    {
      if (IsFilled()) { return nullptr; }
      assert((firstAvailableBlock_ * blockSize) / blockSize == firstAvailableBlock_);
      // here, we use multiplication is to make the ptr offset from the beginning addr of the chunk
      unsigned char* pResult = pData_ + (firstAvailableBlock_ * blockSize);
      firstAvailableBlock_ = *pResult;
      --blocksAvailable_;
      return pResult;
    }

    void Chunk::Deallocate(void* p, ::std::size_t blockSize)
    {
      assert(p >= pData_);
      unsigned char* toRelease = static_cast<unsigned char*> p;
      // alignment check
      assert((toRelease - pData_) % blockSize == 0);
      // calculate the offset of the current index
      unsigned char index = static_cast<unsigned char> ((toRelease - pData_) / blockSize);
# if defined(DEBUG) || defined(_DEBUG)
      // check if block was already deleted
      if (0 < blocksAvailable_)
      {
        assert(firstAvailableBlock_ != index)
      }
# endif
      * toRelease = firstAvailableBlock_;
      firstAvailableBlock_ = index;
      // truncation check
      assert(firstAvailableBlock_ == (toRelease - pData_) / blockSize);
      ++blocksAvailable_;
    }

    bool Chunk::IsCorrupt(unsigned char numBlocks, ::std::size_t blockSize, bool checkIndexes) const
    {
      if (numBlocks < blocksAvailable_)
      {
        // contents at this Chunk corrupted.
        assert(false);
        return true;
      }

      if (IsFilled())
      {
        return false;
      }
      unsigned char index = firstAvailableBlock_;
      if (numBlocks <= index)
      {
        assert(false);
        return true;
      }

      if (!checkIndexes)
      {
        return false
      }
      /* if the bit at index was set in foundBlocks,
          then the stealth index was found on the linked-list
        */
      ::std::bitset<UCHAR_MAX> foundBlocks;
      unsigned char* nextBlock = nullptr;
      /* It can NOT check inside allocated blocks for corruption
          since such blocks are NOT within the linked-list

          Here are the types of corrupted link-lists which can be verified. The corrupt index is shown with asterisks in each example

          a. Index is too big
          numBlocks = 64
          blocksAvailable == 7
          firstAvilableBlock -> 17 -> 29 -> *101*

          b. index is repeated
          numBlocks == 64
          blocksAvailable_ == 5
          firstAvailableBlock_ -> 17 -> 29 -> 53 -> *17* -> 29 -> 53
        */
      for (unsigned char cc = 0;;)
      {
        nextBlock = pData_ + (index * blockSize);
        foundBlocks.set(index, true);
        ++cc;
        if (cc >= blocksAvailable_)
        {
          break;
        }
        index = *nextBlock;
        if (numBlocks <= index)
        {
          // type 1
          assert(false);
          return true;
        }

        if (foundBlocks.test(index))
        {
          // type 2
          assert(false);
          return true
        }
      }

      if (foundBlocks.count() != blocksAvailable_)
      {
        assert(false);
        return true;
      }
      return false;
    }

    bool Chunk::IsBlockAvailable(void* p, unsigned char numBlocks, ::std::size_t blockSize) const
    {
      // cast type
      (void)numBlocks;
      if (IsFilled())
      {
        return false;
      }

      unsigned char* place = static_cast<unsigned char*> (p);
      // alignment check
      assert((place - pData_) % blockSize == 0);
      unsigned char blockIndex = static_cast<unsigned char> ((place - pData_) / blockSize);
      unsigned char index = firstAvailableBlock_;
      assert(numBlocks > index);
      if (index == blockIndex)
      {
        return true;
      }

      /* if the bit at index was set in foundBlocks,
         then the stealth index was found on the linked-list
       */
      ::std::bitset<UCHAR_MAX> foundBlocks;
      unsigned char* nextBlock = nullptr;
      for (unsigned char cc = 0;;)
      {
        nextBlock = pData_ + (index * blockSize);
        foundBlocks.set(index, true);
        ++cc;
        if (cc >= blocksAvailable_)
        {
          break; // couted off number of nodes in linkedlist
        }
        index = *nextBlock;
        if (index == blockIndex)
        {
          return true;
        }
        assert(numBlocks > index);
        assert(!foundBlocks.test(index));
      }
      return false;
    }

  }; // namespace Private
}; // namespace Loki


























