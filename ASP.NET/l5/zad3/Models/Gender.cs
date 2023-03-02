using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace zad3.Models
{
    public class Student
    {
        public Gender studentGender { get; set; }
        public string password { get; set; }
        public string year;
        public bool ifEngNative;
    }

    public enum Gender
    {
        Male,
        Female,
        Other
    }
}