/*
 * #                                                     # *
 * #                           Typed                     # *
 * #                   A text formatting DSL             # *
 * #                                                     # *
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #         Created by Rodrigo R. & Contributors        # *
 * #         Released under the Apache License 2.0       # *
 * #            Check LICENSE.MD for more info           # *
 * #                                                     # *
 * #-----------------------------------------------------# *
*/

//
// Created by Rodrigo on 5/23/26.
//

#pragma once
#include "ADT/Map/Dense.h"
#include "Support/Allocator/Monotonic.h"

namespace Typed::ADT::Scope
{
    template <
        typename Key,
        typename Value,
        typename Hash = ankerl::unordered_dense::hash<Key>,
        typename Equal = std::equal_to<Key>
    >
    struct Scope
    {
        Map::Dense<Key, Value, Hash, Equal> map{};
        Scope *parent = nullptr;
    };

    template <
        typename Key,
        typename Value,
        typename Hash = ankerl::unordered_dense::hash<Key>,
        typename Equal = std::equal_to<Key>,
        typename Allocator = Support::Allocator::Monotonic<
            Scope<Key, Value, Hash, Equal>
        >
    >
    class Stack
    {
        using InnerScope =
            Scope<Key, Value, Hash, Equal>;

        using InnerMap =
            Map::Dense<Key, Value, Hash, Equal>;

        InnerScope *top = nullptr;

    public:
        struct FakeIterator
        {
            InnerScope *scope = nullptr;
            InnerMap::iterator it;

            FakeIterator(
                InnerScope *scope,
                InnerMap::iterator it
            ) :
                scope(scope),
                it(it)
            {}

            bool IsEnd()
            {
                return it == scope->map.end();
            }
        };

        void PushScope()
        {
            auto scope = Allocator::Allocate();
            scope->parent = top;
            top = scope;
        }

        void PopScope()
        {
            Allocator::Deallocate(top);
            top = top->parent;
        }

        FakeIterator Get(const Key &key)
        {
            if (top == nullptr)
            {
                throw Celery::Except::OutOfRange();
            }

            auto scope = top;
            while (scope != nullptr)
            {
                auto it = scope->map.find(key);
                if (it != scope->map.end())
                {
                    return {
                        scope,
                        it
                    };
                }

                scope = scope->parent;
            }

            // By this point, we should've searched all
            // existing scopes
            return {
                top,
                top->map.end()
            };
        }

        void Emplace(
            const Key &key,
            auto &&...args
        )
        {
            // Insert at the top stack so the stack is scoped
            top->map.try_emplace(
                key,
                std::forward<decltype(args)>(args)...
            );
        }

        ~Stack()
        {
            while (top != nullptr)
            {
                PopScope();
            }
        }
    };
}