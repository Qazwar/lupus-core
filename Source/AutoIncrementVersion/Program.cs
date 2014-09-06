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

            string iniFileName = args[0];
            IniReader reader = new IniReader(iniFileName);
            string file = File.ReadAllText(reader.ReadString("Version", "File"), Encoding.UTF8);
            string[] variables = reader.ReadString("Version", "Variables").Split(' ');
            string[] increment = reader.ReadString("Version", "Increment").Split(' ');

            foreach (string variable in variables) {
                if (variable.Length == 0) {
                    continue;
                }

                try {
                    string v = variable + " = ";
                    int vi = file.IndexOf(v);
                    int semicolon = file.IndexOf(';', vi);
                    int length = semicolon - vi;
                    int version = reader.ReadInteger("Version", variable);

                    if (increment.Contains(variable)) {
                        reader.Write("Version", variable, ++version);
                    }

                    file = file.Replace(file.Substring(vi, length), v + version.ToString());
                } catch (Exception e) {
                    Console.WriteLine(e.Message);
                    continue;
                }
            }

            Console.WriteLine("Finished.");
            File.WriteAllText(reader.ReadString("Version", "File"), file, Encoding.UTF8);
        }
    }
}
