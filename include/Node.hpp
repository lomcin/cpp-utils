/*
MIT License

Copyright (c) 2020-2024 Lucas Maggi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _H_NODE_H_
#define _H_NODE_H_

#include <unordered_map>
#include <typeinfo>
#include <atomic>
#include <cstdlib>
#include <stdexcept>

typedef enum NodeTypeEnum
{
    NodeType_Undefined = 0,
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
    static std::unordered_map<void *, NodeInfo *> nodes;
};

class Node
{

protected:
    NodeData *data;

    template <typename T>
    void assignContentToData(const T &content)
    {
        // We should not expect this to happen!
        if (data == nullptr)
            throw std::runtime_error("Something really wrong happened here in assignContentToData.\n");
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
                throw std::runtime_error("Something really wrong happened in initDataInNodeScope.");
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
    template <typename T>
    Node(T *ptr, const T &content) : data(nullptr)
    {
        set(ptr, content);
        data->type = NodeType_Variable;
    }

    template <typename T>
    Node(T *ptr) : data(nullptr)
    {
        set(ptr);
        data->type = NodeType_Variable;
    }

    Node(const Node &node) : data(nullptr)
    {
        removeNodeInfoFromNodeScope();
        data = node.data;
    }

    Node() : data(nullptr)
    {
    }

    ~Node()
    {
        removeNodeInfoFromNodeScope();
    }
    NodeType type()
    {
        return data->type;
    }

    template <typename T>
    Node &set(T *ptr, const T &content)
    {
        initDataInNodeScope(ptr, content);
        data->type = NodeType_Variable;
        return *this;
    }

    template <typename T>
    Node &set(T *ptr)
    {
        initDataInNodeScope(ptr);
        data->type = NodeType_Variable;
        return *this;
    }

    template <typename T>
    Node &set(const T &content)
    {
        assignContentToData(content);
        data->type = NodeType_Variable;
        return *this;
    }

    template <typename T>
    Node &operator=(const T &content)
    {
        return set(content);
    }

    Node &operator=(const Node &node)
    {
        if (node.data == nullptr)
            throw std::runtime_error("Node data is NULL.");
        if (data != nullptr && node.data->type != data->type)
            throw std::runtime_error("Node is from different type, therefore we cannot assign it.");
        removeNodeInfoFromNodeScope();
        data = node.data;
        return *this;
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

#endif // _H_NODE_H_