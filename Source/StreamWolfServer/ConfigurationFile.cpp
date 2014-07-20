#include "ConfigurationFile.h"

#include <pugixml/pugixml.hpp>

using namespace std;
using namespace pugi;

namespace StreamWolf {
    namespace Application {
        void ConfigurationFile::Load(const string& path)
        {
            xml_document doc;
            xpath_node_set nodes;

            if (doc.load_file(path.c_str()) != xml_parse_status::status_ok) {
                throw io_error();
            }

            nodes = doc.select_nodes("/Config/Services/Service");

            for (auto& i : nodes) {
                string path;
                vector<string> attr;
                auto node = i.node();
                
                for (auto& j : node.attributes()) {
                    if (j.name() == "path") {
                        path = j.value();
                    } else {
                        attr.push_back(j.value());
                    }
                }

                mNodes[path] = move(attr);
            }
        }

        const unordered_map<string, vector<string>>& ConfigurationFile::Options() const
        {
            return mNodes;
        }

        const vector<string>& ConfigurationFile::operator[](const string& node)
        {
            return mNodes[node];
        }
    }
}
