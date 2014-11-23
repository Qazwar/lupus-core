/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#define BUILD_INCREMENT 8
#define LUPUS_STRINGIFY(x) #x
#define LUPUS_XSTRINGIFY(x) LUPUS_STRINGIFY(x)

#define LUPUS_GRAPHIC_MAJOR 0
#define LUPUS_GRAPHIC_MINOR 1
#define LUPUS_GRAPHIC_BUILD 0
#define LUPUS_GRAPHIC_REVISION BUILD_INCREMENT

#define LUPUS_GRAPHIC_VERSION LUPUS_GRAPHIC_MAJOR,LUPUS_GRAPHIC_MINOR,LUPUS_GRAPHIC_BUILD,LUPUS_GRAPHIC_REVISION
#define LUPUS_GRAPHIC_VERSION_STRING LUPUS_XSTRINGIFY(LUPUS_GRAPHIC_MAJOR) "." LUPUS_XSTRINGIFY(LUPUS_GRAPHIC_MINOR) "." LUPUS_XSTRINGIFY(LUPUS_GRAPHIC_BUILD) "." LUPUS_XSTRINGIFY(LUPUS_GRAPHIC_REVISION)
