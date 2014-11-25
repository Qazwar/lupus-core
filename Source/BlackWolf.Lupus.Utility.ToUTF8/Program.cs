using System;
using System.IO;
using System.Text;

namespace ToUTF8
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args == null || args.Length == 0)
            {
                Console.WriteLine("No arguments provide.");
            }
            else
            {
                foreach (var End in args)
                {
                    foreach (var f in new DirectoryInfo(".").GetFiles(End, SearchOption.AllDirectories))
                    {
                        var s = File.ReadAllText(f.FullName);
                        File.WriteAllText(f.FullName, s, Encoding.UTF8);
                        Console.WriteLine(f.FullName);
                    }
                }
            }

        }
    }
}
