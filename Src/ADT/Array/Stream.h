/*
 * #-----------------------------------------------------# *
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

#pragma once
#include <vector>

namespace Typed::ADT::Array
{
    namespace Pmr
    {
        template <
            typename T,
            typename Container
        >
        class Stream
            : public Container
        {
        protected:
            // Current read index for streaming
            size_t read_index = 0;

        public:
            // Inherit constructors from base class
            using Container::Container;

            /*
             * @brief Get the next element in the stream and advance the read index.
             *
             * @return Reference to the next element.
             * @throws std::out_of_range when the read index exceeds the vector length.
             */
            T &Next()
            {
                if (read_index >= this->size())
                {
                    throw std::out_of_range("Out of range");
                }

                return this->operator[](read_index++);
            }

            /*
             * @brief Get the previous element in the stream and move back the read index.
             *
             * @return Reference to the previous element.
             * @throws std::out_of_range when the read index is at the beginning.
             */
            T &Prev()
            {
                if (read_index == 0)
                {
                    throw std::out_of_range("Out of range");
                }

                return this->data[--read_index];
            }

            /*
             * @brief Get the next element in the stream without changing the read index.
             *
             * @return Reference to the next element.
             * @throws std::out_of_range when the read index is out of bounds.
             */
            T &Peek()
            {
                if (read_index >= this->size())
                {
                    throw std::out_of_range("Out of range");
                }

                return this->operator[](read_index);
            }

            /*
             * @brief Get the current element in the stream without changing the read index.
             *
             * @return Reference to the current element.
             * @throws std::out_of_range when the read index is out of bounds.
             */
            T &Curr()
            {
                if (read_index == 0 || read_index >= this->size())
                {
                    throw std::out_of_range("Out of range");
                }

                return this->operator[](read_index - 1);
            }

            /*
             * @brief Jump to the specified index in the stream.
             *
             * @param n The index to jump to.
             * @return Reference to the element at index n.
             * @throws std::out_of_range when n is out of bounds.
             */
            T &Nth(size_t n)
            {
                if (n >= this->len)
                {
                    throw std::out_of_range("Out of range");
                }

                read_index = n + 1;
                return this->data[n];
            }

            /*
             * @brief Check if there is a next element in the stream.
             *
             * @return true if there is a next element, false otherwise.
             */
            [[nodiscard]] bool HasNext() const noexcept
            {
                return read_index < this->size();
            }

            /*
             * @brief Check if there is a previous element in the stream.
             *
             * @return true if there is a previous element, false otherwise.
             */
            [[nodiscard]] bool HasPrev() const noexcept
            {
                return read_index > 0;
            }

            /*
             * @brief Set the current read position in the stream.
             *
             * @param pos The position to set the read index to.
             */
            void SetPos(size_t pos) noexcept
            {
                read_index = pos;
            }

            /*
             * @brief Get the current read position in the stream.
             *
             * @return The current read index.
             */
			[[nodiscard]] size_t Pos() const noexcept
            {
                return read_index;
            }
        };
    }

    template <typename T>
    using Stream = Pmr::Stream<
        T,
        std::vector<T>
    >;
}