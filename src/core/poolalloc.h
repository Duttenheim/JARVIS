#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::PoolAlloc
	
    Implements a pool-based custom memory allocator.
    
    Concept and most code from:
    https://github.com/floooh/oryol/blob/master/code/Modules/Core/Memory/poolAllocator.h
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Core
{
template <class TYPE, uint16 CHUNKSIZE, uint16 MAXCHUNKS>
class PoolAlloc
{
public:
    /// constructor
    PoolAlloc();
    /// destructor
    virtual ~PoolAlloc();
    
    /// create instance
    template <class... ARGS> TYPE* Create(ARGS&&...);
    /// delete instance
    void Destroy(TYPE* obj);
    
private:

    enum class NodeState : uint8
    {
        Initial,
        Free,
        Used
    };
    
    using NodeId = uint32;
    
    
    // calculate size of header, i.e. size of state, id and next
    static constexpr uint32 NodeHeaderSize = sizeof(NodeState) + sizeof(NodeId) + sizeof(NodeId);
    
    struct Node
    {
        NodeState state;
        NodeId id;          // lower 16 bits is chunk index, upper 16 bits is index within chunk
        NodeId next;
        byte padding[16 - NodeHeaderSize]; // pad to 16 bytes
        TYPE data;
    };
    
    struct Chunk
    {
        Chunk* next;
        Node* elements;
    };
    
    /// get next free node, alloc if all are used
    Node* Alloc();
    /// free node, and make it free for Alloc
    void Free(Node* obj);
    /// create a new chunk
    void Grow();
    
    std::atomic<NodeId> head;
    std::atomic<uint32> numChunks;
    Chunk chunks[MAXCHUNKS];
};

//------------------------------------------------------------------------------
/**
*/
template <class TYPE, uint16 CHUNKSIZE, uint16 MAXCHUNKS>
PoolAlloc<TYPE, CHUNKSIZE, MAXCHUNKS>::PoolAlloc()
{
    this->head.exchange(-1);
    Memory::Fill(chunks, MAXCHUNKS, 0x0);
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE, uint16 CHUNKSIZE, uint16 MAXCHUNKS>
PoolAlloc<TYPE, CHUNKSIZE, MAXCHUNKS>::~PoolAlloc()
{
    uint32 chunks = this->numChunks.load(std::memory_order_consume);
    for (uint32 i = 0; i < chunks; i++)
    {
        Memory::Free(this->chunks[i].elements);
        this->chunks[i].elements = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE, uint16 CHUNKSIZE, uint16 MAXCHUNKS>
template <class... ARGS>
TYPE*
PoolAlloc<TYPE, CHUNKSIZE, MAXCHUNKS>::Create(ARGS&&... args)
{
    Node* element = this->Alloc();
    if (element == nullptr)
    {
        this->Grow();
        element = this->Alloc();
    }
    j_assert(element != nullptr);
    
    TYPE* obj = new(&element->data) TYPE(std::forward<ARGS>(args)...);
    return obj;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE, uint16 CHUNKSIZE, uint16 MAXCHUNKS>
void
PoolAlloc<TYPE, CHUNKSIZE, MAXCHUNKS>::Destroy(TYPE* obj)
{
    // call destructor
    obj->~TYPE();
    
    // retrieve Node* from data, which should be - size of node - size of TYPE bytes from data location
    char* ptr = (char*)obj;
    Node* node = (Node*)(ptr - (sizeof(Node) - sizeof(TYPE)));
    this->Free(node);
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE, uint16 CHUNKSIZE, uint16 MAXCHUNKS>
typename PoolAlloc<TYPE, CHUNKSIZE, MAXCHUNKS>::Node*
PoolAlloc<TYPE, CHUNKSIZE, MAXCHUNKS>::Alloc()
{
    while (true)
    {
        NodeId id = this->head.load(std::memory_order_consume);
        if (id == -1) return nullptr;
        uint32 chunkId = id & 0xFFFF0000;
        uint32 elemId = id & 0xFFFF;
        Node* node = &this->chunks[chunkId].elements[elemId];
        NodeId next = node->next;
        if (this->head.compare_exchange_weak(id, next))
        {
            node->next = -1;
            node->state = NodeState::Used;
            return node;
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE, uint16 CHUNKSIZE, uint16 MAXCHUNKS>
void
PoolAlloc<TYPE, CHUNKSIZE, MAXCHUNKS>::Free(Node* node)
{
    j_assert(node->state == NodeState::Initial || node->state == NodeState::Used);
    node->state = NodeState::Free;
    NodeId oldHead = this->head.load(std::memory_order_relaxed);
    while (true)
    {
        node->next = oldHead;
        if (this->head.compare_exchange_weak(oldHead, node->id)) break;
    }
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE, uint16 CHUNKSIZE, uint16 MAXCHUNKS>
void
PoolAlloc<TYPE, CHUNKSIZE, MAXCHUNKS>::Grow()
{
    // add chunk id
    uint32 newChunkId = this->numChunks.fetch_add(1, std::memory_order_relaxed);
    
    // allocate chunk memory
    this->chunks[newChunkId].elements = Memory::Alloc<Node>(CHUNKSIZE);
    
    // now go through and setup nodes
    int32 nodeIndex;
    for (nodeIndex = CHUNKSIZE-1; nodeIndex >= 0; nodeIndex--)
    {
        Node* node = &this->chunks[newChunkId].elements[nodeIndex];
        node->next = -1;
        node->id = (newChunkId << 16) | nodeIndex;
        node->state = NodeState::Initial;
        this->Free(node);
    }
}

}} // namespace JARVIS::Core