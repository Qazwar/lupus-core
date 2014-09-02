using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lupus;

namespace AutoIncrementVersion
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args == null) {
                Console.WriteLine("Usage:");
                Console.WriteLine("-v: Variablename(s) to set.");
                Console.WriteLine("-p: Section name in Versin.ini.");
                Console.WriteLine("-i: Increment version number.");
                Console.WriteLine("-f: Path to file with version string.");
                Console.WriteLine("-h: Print this message.");
                Console.WriteLine("Press enter to end this program.");
                Console.ReadLine();
                return;
            }

            IniReader reader = new IniReader("./Version.ini");
            Arguments arguments = new Arguments(args);

            if (arguments["p"] == null || arguments["v"] == null || arguments["f"] == null || arguments["h"] != null) {
                Console.WriteLine("Usage:");
                Console.WriteLine("-v: Variablename(s) to set.");
                Console.WriteLine("-p: Section name in Versin.ini.");
                Console.WriteLine("-i: Increment version number.");
                Console.WriteLine("-f: Path to file with version string.");
                Console.WriteLine("-h: Print this message.");
                Console.WriteLine("Press enter to end this program.");
                Console.ReadLine();
                return;
            }

            string file = File.ReadAllText(args[1], Encoding.UTF8);
            string[] variables = args[5].Split(' ');
            string[] increment = args[7].Split(' ');

            foreach (string variable in variables) {
                if (variable.Length == 0) {
                    continue;
                }

                try {
                    string v = variable + " = ";
                    int vi = file.IndexOf(v);
                    int semicolon = file.IndexOf(';', vi);
                    int length = semicolon - vi;
                    int version = reader.ReadInteger(args[3], variable);

                    if (increment.Contains(variable)) {
                        reader.Write(args[3], variable, ++version);
                    }

                    file = file.Replace(file.Substring(vi, length), v + version.ToString());
                } catch (Exception e) {
                    Console.WriteLine(e.Message);
                    continue;
                }
            }

            Console.WriteLine("Finished.");
            File.WriteAllText(args[1], file, Encoding.UTF8);
        }
    }
}
