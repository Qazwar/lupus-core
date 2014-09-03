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
            if (args == null || args.Length == 0) {
                Console.WriteLine("No arguments provided.");
                return;
            }

            string iniFileName = "./" + args[0] + ".ini";
            IniReader reader = new IniReader(iniFileName);
            string file = File.ReadAllText(reader.ReadString(args[0], "File"), Encoding.UTF8);
            string[] variables = reader.ReadString(args[0], "Variables").Split(' ');
            string[] increment = reader.ReadString(args[0], "Increment").Split(' ');

            foreach (string variable in variables) {
                if (variable.Length == 0) {
                    continue;
                }

                try {
                    string v = variable + " = ";
                    int vi = file.IndexOf(v);
                    int semicolon = file.IndexOf(';', vi);
                    int length = semicolon - vi;
                    int version = reader.ReadInteger(args[0], variable);

                    if (increment.Contains(variable)) {
                        reader.Write(args[0], variable, ++version);
                    }

                    file = file.Replace(file.Substring(vi, length), v + version.ToString());
                } catch (Exception e) {
                    Console.WriteLine(e.Message);
                    continue;
                }
            }

            Console.WriteLine("Finished.");
            File.WriteAllText(reader.ReadString(args[0], "File"), file, Encoding.UTF8);
        }
    }
}
