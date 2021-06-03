using System;
using System.IO;
using System.Security.Cryptography;
using System.IO.Compression;

namespace _2._3._3
{
    class Program
    {
        static void Main(string[] args)
        {
            string original = File.ReadAllText(".//zad.txt");
            byte[] enc;
            string text = "";

            using (Aes myAes = Aes.Create())
            {
                using (MemoryStream msEncrypt = new MemoryStream())
                {
                    using (CryptoStream csEnc = new CryptoStream(msEncrypt,
                                                             myAes.CreateEncryptor(myAes.Key, myAes.IV),
                                                             CryptoStreamMode.Write))
                    {
                        using (GZipStream zStr = new GZipStream(csEnc, CompressionMode.Compress))
                        {
                            using (StreamWriter swEncrypt = new StreamWriter(zStr))
                            {
                                swEncrypt.Write(original);
                            }
                            enc = msEncrypt.ToArray();
                        }
                    }
                }
                

                using (MemoryStream msDecrypt = new MemoryStream(enc))
                {
                    using (CryptoStream csDecrypt = new CryptoStream(msDecrypt,
                                                                 myAes.CreateDecryptor(myAes.Key, myAes.IV),
                                                                 CryptoStreamMode.Read))
                    {
                        using (GZipStream zipStream = new GZipStream(csDecrypt, CompressionMode.Decompress))
                        {
                            using (StreamReader srDecrypt = new StreamReader(zipStream))
                            {
                                text = srDecrypt.ReadToEnd();
                            }
                        }
                    }
                }
            }

            Console.WriteLine("Po enkrypcji i dekrypcji " + text);
            Console.ReadLine();
        }
    }
}
