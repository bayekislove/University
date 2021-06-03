using System;
using System.Net;
using System.Net.Sockets;

namespace _2._3._5
{
    class Program
    {
        static void Main(string[] args)
        {
            //pobranie pliku z użyciem WebClient
            using( WebClient a = new WebClient() )
            {
                string url = "https://img.pixers.pics/pho_wat(s3:700/FO/35/27/50/13/700_FO35275013_8b6830d0464e71471067b4f5f60485d0.jpg,700,700,cms:2018/10/5bd1b6b8d04b8_220x50-watermark.png,over,480,650,jpg)/naklejki-kotek-na-bialym-tle.jpg.jpg";
                Uri b = new Uri(url);
                a.DownloadFile(b, "webClientKotek.jpg");
            }
            //usunięcie pliku z serwera z użyciem FTPWebRequest

            /*FtpWebRequest ftp = (FtpWebRequest)WebRequest.Create("ftp://facebook.com/jakis_plik.txt");
            ftp.Method = WebRequestMethods.Ftp.DeleteFile;

            FtpWebResponse ftr = (FtpWebResponse)ftp.GetResponse();
            Console.WriteLine("Udało się? " + ftr.StatusDescription);
            ftr.Close();*/

            // Nie wiem, jaki prefiks dodać żeby nie dostać odmowy dostępu : ( 

            //using (HttpListener list = new HttpListener())
            //{
            //    list.Start();
            //    Console.WriteLine("Już słucham");

            //    list.Prefixes.Add("https://google.com/");

            //    HttpListenerContext listContext = list.GetContext();
            //    System.IO.Stream outStr = listContext.Response.OutputStream;

            //    byte[] buf = System.Text.Encoding.UTF8.GetBytes("Whats the point of my existence?");
            //    outStr.Write(buf, 0, buf.Length);
            //    outStr.Close();

            //    list.Stop();
            //}
            //Console.WriteLine(":A");

            //nawiązanie połączenia TCP i wysłanie wiadomosc
            string serv = "";
            using( TcpClient cl = new TcpClient(serv, 3000))
            {
                Byte[] data = System.Text.Encoding.ASCII.GetBytes("Hej");
                NetworkStream a = cl.GetStream();

                a.Write(data, 0, data.Length);
                a.Close();
            }
        }
    }
}
