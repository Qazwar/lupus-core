using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GPL
{
    class Program
    {
        static void Main(string[] args)
        {
            const string gpl = @"/**
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
";

            var directory = new DirectoryInfo(".");

            foreach (var f in directory.GetFiles("*.h"))
            {
                var text = File.ReadAllText(f.FullName);
                if (text.Contains(gpl)) continue;
                var newText = gpl + text;
                File.WriteAllText(f.FullName, newText);
            }
        }
    }
}
