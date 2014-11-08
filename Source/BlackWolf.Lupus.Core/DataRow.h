/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <memory>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "String.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Data {
        class DataColumn;

        class LUPUSCORE_API DataRow : public boost::noncopyable
        {
        public:

            explicit DataRow(std::unordered_map<String, boost::any>&);
            virtual ~DataRow() = default;

            virtual boost::any& operator[](unsigned) throw(std::out_of_range);
            virtual const boost::any& operator[](unsigned) const throw(std::out_of_range);

            virtual boost::any& operator[](const String&) throw(std::invalid_argument);
            virtual const boost::any& operator[](const String&) const throw(std::invalid_argument);

            virtual boost::any& operator[](std::shared_ptr<DataColumn>) throw(std::invalid_argument, null_pointer);
            virtual const boost::any& operator[](std::shared_ptr<DataColumn>) const throw(std::invalid_argument, null_pointer);

            virtual size_t Count() const NOEXCEPT;
            virtual bool IsEmpty() const NOEXCEPT;
            virtual std::unordered_map<String, boost::any> Items() const NOEXCEPT;

        private:

            std::unordered_map<String, boost::any> mItems;
            std::vector<boost::any*> mRefItems;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
