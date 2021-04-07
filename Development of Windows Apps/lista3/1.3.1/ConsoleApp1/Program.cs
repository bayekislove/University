using System;

namespace ConsoleApp1
{
    public static class StringExtensions
    {
        public static bool isPalindrome( this string s )
        {
            s = s.ToLower();
            int start = 0;
            int toStop = s.Length;
            int end = s.Length - 1;
            while( start < toStop )
            {
                if ( !Char.IsLetter( s[start] ) )
                {
                    start++;
                    continue;
                }
                if ( !Char.IsLetter( s[end] ) )
                {
                    end--;
                    continue;
                }
                if (s[end] != s[start])
                    return false;
                start++;
                end--;
            }
            return true;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Kobyła ma mały bok.".isPalindrome());
            Console.WriteLine("Kobyła".isPalindrome());
        }
    }
}
