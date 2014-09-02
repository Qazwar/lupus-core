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
            if (args == null) {
                Console.WriteLine("Usage:");
                Console.WriteLine("-e --endings:     File endings to search for (default: .h .hpp .hxx .c .cpp .cxx, .cs).");
                Console.WriteLine("-d --directories: Directories seperated by space.");
                Console.WriteLine("-h --help:        Prints this message.");
                return;
            }

            string[] endings = { "*.h", "*.hpp", "*.c", "*.cpp", "*.cs" };
            string[] directories = new string[0];
            Arguments arguments = new Arguments(args);

            if (arguments["help"] != null || arguments["h"] != null) {
                Console.WriteLine("Usage:");
                Console.WriteLine("-e --endings:     File endings to search for (default: .h .hpp .c .cpp .cs).");
                Console.WriteLine("-d --directories: Directories seperated by space (default: .).");
                Console.WriteLine("-h --help:        Print this message.");
                Console.WriteLine("Press enter to end the program.");
                return;
            }

            if (arguments["endings"] != null) {
                endings = arguments["endings"].Split(' ');
            } else if (arguments["e"] != null) {
                endings = arguments["e"].Split(' ');
            }

            if (arguments["directories"] != null) {
                directories = arguments["directories"].Split(' ');
            } else if (arguments["d"] != null) {
                directories = arguments["d"].Split(' ');
            } else {
                Console.WriteLine("Usage:");
                Console.WriteLine("-e --endings:     File endings to search for (default: .h .hpp .c .cpp .cs).");
                Console.WriteLine("-d --directories: Directories seperated by space (default: .).");
                Console.WriteLine("-h --help:        Print this message.");
                Console.WriteLine("Press enter to end the program.");
                Console.ReadLine();
                return;
            }

            foreach (var dir in directories) {
                foreach (var end in endings) {
                    foreach (var f in new DirectoryInfo(args[1]).GetFiles(end, SearchOption.AllDirectories)) {
                        string s = File.ReadAllText(f.FullName);
                        File.WriteAllText(f.FullName, s, Encoding.UTF8);
                        Console.WriteLine(f.FullName);
                    }
                }
            }
        }
    }
}
