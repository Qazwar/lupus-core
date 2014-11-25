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
#include <cstdlib>
#include <BlackWolf.Lupus.Core/String.h>
#include <BlackWolf.Lupus.Core/Stream.h>
#include <BlackWolf.Lupus.Core/IPAddress.h>
#include <BlackWolf.Lupus.Core/IPEndPoint.h>
#include <BlackWolf.Lupus.Core/Version.h>
#include <BlackWolf.Lupus.Core/Uri.h>
#include <BlackWolf.Lupus.Core/Encoding.h>
#include <BlackWolf.Lupus.Core/HttpListenerRequest.h>


using namespace Lupus;
using namespace Lupus::Text;
using namespace Lupus::Net;

const String testRequest1 = "GET /tutorials/other/top-20-mysql-best-practices/ HTTP/1.1\r\n"
"Host: net.tutsplus.com\r\n"
"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR 3.5.30729)\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
"Accept-Language: en-us,en;q=0.5\r\n"
"Accept-Encoding: gzip,deflate\r\n"
"Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
"Keep-Alive: 300\r\n"
"Connection: keep-alive\r\n"
"Cookie: PHPSESSID=r2t5uvjq435r4q7ib3vtdjq120\r\n"
"Pragma: no-cache\r\n"
"Cache-Control: no-cache\r\n\r\n";

const String testRequest2 = "GET /tutorials/other/top-20-mysql-best-practices/test.php HTTP/1.1\r\n"
"Host: net.tutsplus.com\r\n"
"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR 3.5.30729)\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
"Accept-Language: en-us,en;q=0.5\r\n"
"Accept-Encoding: gzip,deflate\r\n"
"Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
"Keep-Alive: 300\r\n"
"Connection: keep-alive\r\n"
"Cookie: PHPSESSID=r2t5uvjq435r4q7ib3vtdjq120\r\n"
"Pragma: no-cache\r\n"
"Cache-Control: no-cache\r\n\r\n";

int wmain(int argc, wchar_t** argv)
{
    auto request = MakePointer<HttpListenerRequest>(Encoding::ASCII()->GetBytes(testRequest1), nullptr, nullptr);

    wprintf(request->RawHeader().Data());
    wprintf(request->HttpMethod().Data());
    wprintf(L" ");
    wprintf(request->Url()->FullPath().Data());
    wprintf(L" ");
    wprintf((L"HTTP/" + request->ProtocolVersion()->ToString() + L"\r\n").Data());
    wprintf(request->Url()->ToString().Data());
    wprintf(L"\r\n\r\n");

    request = MakePointer<HttpListenerRequest>(Encoding::ASCII()->GetBytes(testRequest2), nullptr, nullptr);

    wprintf(request->RawHeader().Data());
    wprintf(request->HttpMethod().Data());
    wprintf(L" ");
    wprintf(request->Url()->FullPath().Data());
    wprintf(L" ");
    wprintf((L"HTTP/" + request->ProtocolVersion()->ToString() + L"\r\n").Data());
    wprintf(request->Url()->ToString().Data());

    getchar();

    return EXIT_SUCCESS;
}
