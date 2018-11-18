using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Canvas
{
    class User
    {
        public string userID { get; set; }
        public string firstName { get; set; }
        public string lastName { get; set; }

        public override string ToString() => $"{firstName} {lastName}";
    }
}
