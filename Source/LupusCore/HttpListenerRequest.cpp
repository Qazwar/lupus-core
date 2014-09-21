#include "HttpListenerRequest.h"
#include "Encoding.h"
#include "Version.h"
#include "Uri.h"
#include "IPEndPoint.h"
#include "Stream.h"

using namespace std;
using namespace Lupus::Text;
using namespace Lupus::Net::Sockets;

namespace Lupus {
    namespace Net {
        HttpListenerRequest::HttpListenerRequest(shared_ptr<Lupus::InputStream> stream, shared_ptr<IPEndPoint> local, shared_ptr<IPEndPoint> remote) :
            mStream(stream), mLocalEP(local), mRemoteEP(remote)
        {
            vector<uint8_t> buffer(stream->Length());
            stream->Position(0);
            stream->Read(buffer, 0, stream->Length());
            stream->Position(0);

            String content = Encoding::UTF8()->GetString(buffer);
            vector<String> lines = content.Split({ "\n" }, StringSplitOption::RemoveEmptyEntries);
            vector<String> fields(begin(lines) + 1, end(lines));
            String version = lines[0].Substring(lines[0].LastIndexOf("/") + 1);
            
            mMethod = lines[0].Substring(0, lines[0].IndexOf(" "));
            mVersion = Version::Parse(version);

            for (String str : fields) {
                vector<String> field = str.Split({ ": " });
                mHeaders[field[0]] = field[1];
            }

            mUrl = make_shared<Uri>(mHeaders["Host"] + lines[0].Substring(lines[0].IndexOf(" "), lines[0].LastIndexOf(" ")));
            String query = mUrl->Query();
            String cookie = mHeaders.find("Cookie") != end(mHeaders) ? mHeaders["Cookie"] : "";
            String language = mHeaders.find("Accept-Language") != end(mHeaders) ? mHeaders["Accept-Language"] : "";
            String charset = mHeaders.find("Accept-Charset") != end(mHeaders) ? mHeaders["Accept-Charset"] : "";
            String accepttypes = mHeaders.find("Accept") != end(mHeaders) ? mHeaders["Accept"] : "";

            mContentType = mHeaders.find("Content-Type") != end(mHeaders) ? mHeaders["Content-Type"] : "";
            mUserAgent = mHeaders.find("User-Agent") != end(mHeaders) ? mHeaders["User-Agent"] : "";

            mAcceptedTypes = accepttypes.IsEmpty() ? vector<String>() : accepttypes.Split({ ";" })[0].Split({ "," }, StringSplitOption::RemoveEmptyEntries);
            mLanguages = language.IsEmpty() ? vector<String>() : language.Split({ ";" })[0].Split({ "," }, StringSplitOption::RemoveEmptyEntries);
            auto queries = query.IsEmpty() ? vector<String>() : query.Split({ "?" }, StringSplitOption::RemoveEmptyEntries)[0].Split({ "&" }, StringSplitOption::RemoveEmptyEntries);

            for (auto str : queries) {
                auto nameValuePair = str.Split({ "=" });
                mQuery[nameValuePair[0]] = nameValuePair[1];
            }

            auto cookies = cookie.Split({ ";" }, StringSplitOption::RemoveEmptyEntries);

            for (auto str : cookies) {
                auto nameValuePair = str.Split({ "=" });
                mCookies[nameValuePair[0]] = nameValuePair[1];
            }

            if (charset.IsEmpty()) {
                mEncoding = Encoding::UTF8();
            } else {
                auto encodings = charset.Split({ ";" }, StringSplitOption::RemoveEmptyEntries)[0].Split({ "," }, StringSplitOption::RemoveEmptyEntries);

                for (auto enc : encodings) {
                    if (!mEncoding) {
                        mEncoding = Encoding::GetEncoding(enc);
                    } else {
                        break;
                    }
                }

                if (!mEncoding) {
                    mEncoding = Encoding::UTF8();
                }
            }
        }
    }
}
