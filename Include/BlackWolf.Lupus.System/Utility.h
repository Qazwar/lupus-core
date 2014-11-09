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

#ifdef _MSC_VER
#pragma warning(disable: 4290)
#define NOEXCEPT throw()

#ifdef LUPUSSYSTEM_EXPORT
#define LUPUSSYSTEM_API __declspec(dllexport)
#else
#define LUPUSSYSTEM_API __declspec(dllimport)
#endif

#else
#define NOEXCEPT noexcept

#ifdef LUPUSSYSTEM_EXPORT

#ifdef __CYGWIN__
#define LUPUSSYSTEM_API __attribute__ ((dllexport))
#else
#define LUPUSSYSTEM_API __attribute__ ((visibility ("default")))
#endif

#else

#ifdef __CYGWIN__
#define LUPUSSYSTEM_API __attribute__ ((dllimport))
#else
#define LUPUSSYSTEM_API __attribute__ ((visibility ("default")))
#endif

#endif
#endif
