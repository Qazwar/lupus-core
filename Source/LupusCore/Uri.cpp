#include "Uri.h"

using namespace std;

namespace Lupus {
    Uri::Uri(const string& uriString) :
        mOriginalString(uriString)
    {
        int isch = uriString.find("://");
        int ipor = uriString.find(":", isch);
        int ipat = uriString.find("/", ipor);
        int ique = uriString.find("?", ipat);

        mSchema = uriString.substr(0, isch);
        mHost = uriString.substr(isch + 3, ipor);
        mPort = uriString.substr(ipor + 1, ipat);
        mPath = uriString.substr(ipat, ique);
        mQuery = uriString.substr(ique);
    }

    Uri::Uri(shared_ptr<Uri> baseUri, const string& uriString) :
        Uri(baseUri->ToString() + uriString)
    {
    }

    Uri::Uri(shared_ptr<Uri> baseUri, shared_ptr<Uri> relativeUri) :
        Uri(baseUri->ToString() + relativeUri->ToString())
    {
    }

    const string& Uri::Host() const
    {
        return mHost;
    }

    const string& Uri::Port() const
    {
        return mPort;
    }

    const string& Uri::Path() const
    {
        return mPath;
    }

    const string& Uri::Query() const
    {
        return mQuery;
    }

    const string& Uri::Schema() const
    {
        return mSchema;
    }

    string Uri::PathAndQuery() const
    {
        return mPath + mQuery;
    }

    const string& Uri::OriginalString() const
    {
        return mOriginalString;
    }

    vector<string> Uri::Segments() const
    {
        vector<string> segments;
        size_t n = mPath.find("/");

        while (n != mPath.npos) {
            auto m = mPath.find("/", n);
            auto sub = m == mPath.npos ? mPath.substr(n + 1) : mPath.substr(n + 1, m - 1);
            segments.push_back(sub);
        }

        return segments;
    }

    string Uri::ToString() const
    {
        string uri;

        uri += mSchema.size() > 0 ? mSchema + "://" : "";
        uri += mHost.size() > 0 ? mHost : "";
        uri += mPort.size() > 0 ? ":" + mPort : "";
        uri += mPath.size() > 0 ? mPath : "";
        uri += mQuery.size() > 0 ? mQuery : "";

        return uri;
    }
}
