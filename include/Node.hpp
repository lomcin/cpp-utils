#ifndef _H_NODE_H_
#define _H_NODE_H_

#include <unordered_map>
#include <typeinfo>
#include <atomic>
#include <cstdlib>
#include <stdexcept>

typedef enum NodeTypeEnum
{
    NodeType_Unknown = 0,
    NodeType_Variable,
    NodeType_Function,
    NodeType_Object
} NodeType;

class Node;

typedef struct NodeData_s
{
    NodeType type;
    void *content;
    size_t content_type_hash;
    bool changed;
    Node *parent;
} NodeData;

typedef struct NodeInfo_s
{
    std::atomic<int> count;
    NodeData *data;
} NodeInfo;

namespace NodeScope
{
    std::unordered_map<void *, NodeInfo *> nodes;
};

class Node
{
protected:
    NodeData *data;
    Node(const Node &node)
    {
        removeNodeInfoFromNodeScope();
        data = node.data;
    }

    Node()
    {
        data = nullptr;
    }

    ~Node()
    {
        removeNodeInfoFromNodeScope();
    }

    template <typename T>
    void assignContentToData(const T &content)
    {
        // We should not expect this to happen!
        if (data == nullptr)
            throw std::runtime_error("Something really wrong happened here.\n");
        // We cannot use different types for initialization of setting in already defined nodes
        if (data->content_type_hash == 0)
        {
            throw std::runtime_error("Node type is not initialized.");
        }
        else
        {
            if (typeid(T).hash_code() == data->content_type_hash)
            {
                T *ptr = reinterpret_cast<T *>(data->content);
                if (ptr == nullptr)
                    throw std::runtime_error("This node content points to NULL.\n");
                if (*ptr != content)
                {
                    data->changed = true;
                }
                *ptr = content;
            }
            else
            {
                throw std::runtime_error("Invalid node type initialization.");
            }
        }
    }

    template <typename T>
    void initDataInNodeScope(T *ptr, const T &content)
    {
        initDataInNodeScope(ptr);
        assignContentToData(content);
    }

    template <typename T>
    void initDataInNodeScope(T *ptr)
    {
        void *vptr = reinterpret_cast<void *>(ptr);
        // Find if we don't have NodeInfo for this pointer 'ptr'
        if (NodeScope::nodes.find(vptr) == NodeScope::nodes.end())
        {
            // Data Initialization
            if (data == nullptr)
            {
                // Create node data for given pointer
                data = new NodeData();
                memset(data, 0, sizeof(NodeData));
                data->content_type_hash = typeid(T).hash_code();
                data->content = vptr;

                // Increase count
                NodeInfo *nodeInfo = new NodeInfo();
                nodeInfo->count++;
                nodeInfo->data = data;

                // Add the node info to node scope
                NodeScope::nodes[vptr] = nodeInfo;
            }
            else
            {
                throw std::runtime_error("Something really wrong happened here.");
            }
        }
        else
        {
            // We found NodeInfo for this so we use it
            NodeInfo *nodeInfo = NodeScope::nodes[vptr];

            // We should not expect this to happen!
            if (nodeInfo->data == nullptr)
                throw std::runtime_error("Node Info data is NULL.");

            // We cannot use different types for initialization of setting in already defined nodes
            if (nodeInfo->data->content_type_hash != 0 && typeid(T).hash_code() != nodeInfo->data->content_type_hash)
                throw std::runtime_error("Invalid node type initialization.");

            // Increase count to avoid deletion before using data
            nodeInfo->count++;

            // We point to node info data
            data = nodeInfo->data;
        }
    }

    void removeNodeInfoFromNodeScope()
    {
        if (data != nullptr)
        {
            void *vptr = reinterpret_cast<void *>(this->data->content);
            if (NodeScope::nodes.find(vptr) != NodeScope::nodes.end())
            {
                NodeInfo *nodeInfo = NodeScope::nodes[vptr];
                nodeInfo->count--;
                if (nodeInfo->count == 0)
                {
                    NodeScope::nodes.erase(NodeScope::nodes.find(vptr));
                    delete nodeInfo->data;
                    delete nodeInfo;
                }
            }
        }
    }

public:
    NodeType type()
    {
        return data->type;
    }

    template <typename T>
    Node &set(T *ptr, const T &content)
    {
        initDataInNodeScope(ptr, content);
        return *this;
    }

    template <typename T>
    Node &set(T *ptr)
    {
        initDataInNodeScope(ptr);
        return *this;
    }

    template <typename T>
    Node &set(const T &content)
    {
        assignContentToData(content);
        return *this;
    }

    template <typename T>
    Node &operator=(const T &content)
    {
        return set(content);
    }

    template <typename T>
    T &get()
    {
        assert(data->content != nullptr);
        assert(data->content_type_hash == 0 || typeid(T).hash_code() == data->content_type_hash);
        return *reinterpret_cast<T *>(data->content);
    }

    Node &parent()
    {
        return *(data->parent);
    }
};

class VariableNode : public Node
{
public:
    template <typename T>
    VariableNode(T *ptr, const T &content)
    {
        set(ptr, content);
        data->type = NodeType_Variable;
    }

    template <typename T>
    VariableNode(T *ptr)
    {
        set(ptr);
        data->type = NodeType_Variable;
    }
};

class FunctionNode : public Node
{
public:
    template <typename T>
    FunctionNode(T *ptr, const T &content)
    {
        data->type = NodeType_Function;
        set(ptr, content);
    }

    template <typename T>
    FunctionNode(T *ptr)
    {
        data->type = NodeType_Function;
        set(ptr);
    }
};

class ObjectNode : public Node
{
public:
    template <typename T>
    ObjectNode(T *ptr, const T &content)
    {
        data->type = NodeType_Object;
        set(ptr, content);
    }

    template <typename T>
    ObjectNode(T *ptr)
    {
        data->type = NodeType_Object;
        set(ptr);
    }
};

// Just defining some aliases
typedef VariableNode VarNode;
typedef FunctionNode FuncNode;
typedef ObjectNode ObjNode;

#endif // _H_NODE_H_