using Lupus;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace to_utf8
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args == null || args.Length == 0) {
                Console.WriteLine("No arguments provide.");
            }

            string iniFileName = "./" + args[0] + ".ini";
            IniReader reader = new IniReader(iniFileName);
            string[] endings = reader.ReadString(args[0], "Endings").Split(' ');

            foreach (var end in endings) {
                foreach (var f in new DirectoryInfo(".").GetFiles(end, SearchOption.AllDirectories)) {
                    string s = File.ReadAllText(f.FullName);
                    File.WriteAllText(f.FullName, s, Encoding.UTF8);
                    Console.WriteLine(f.FullName);
                }
            }
        }
    }
}
