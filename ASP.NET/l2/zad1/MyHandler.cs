using System;
using System.IO;
using System.Web;

namespace zad1
{
    public class MyHandler : IHttpHandler
    {
        /// <summary>
        /// You will need to configure this handler in the Web.config file of your 
        /// web and register it with IIS before being able to use it. For more information
        /// see the following link: https://go.microsoft.com/?linkid=8101007
        /// </summary>
        #region IHttpHandler Members

        public bool IsReusable
        { 
            get { return true; }
        }

        public void ProcessRequest(HttpContext context)
        {
            context.Response.AppendHeader("Content-type", "text/html");
            context.Response.Write("Pełny adres: " + context.Request.RawUrl  + "<br>");
            context.Response.Write("Rodzaj żądania: " + context.Request.HttpMethod + "<br>");
            context.Response.Write("Nagłówki: " + "<br>");
            foreach(var naglowek in context.Request.Headers)
            {
                context.Response.Write(naglowek.ToString() + "<br>");
            }
            if(context.Request.HttpMethod == "POST")
            {
                string req_txt;
                StreamReader reader = new StreamReader(HttpContext.Current.Request.InputStream);
                req_txt = reader.ReadToEnd();
                if(req_txt.Length != 0)
                {
                    context.Response.Write("Treść żądania POST: " + req_txt + "<br>");
                }
            }
        }

        #endregion
    }
}
