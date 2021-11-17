using System;
using System.Web;

namespace zad4
{
    public partial class start : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            label.Text = PseudoApplication.a() + PseudoItems.a() + PseudoSession.a(); 
        }

        public class PseudoApplication
        {
            public static string a()
            {
                if (HttpContext.Current.Application["ses"] == null)
                {
                    HttpContext.Current.Application["ses"] = new Random().Next();
                }
                return "<br>Wartość aplication: " + HttpContext.Current.Application["ses"].ToString() + "</br>";
            }
        }

        public class PseudoSession
        {
            public static string a()
            {
                if (HttpContext.Current.Session["ses"] == null)
                {
                    HttpContext.Current.Session["ses"] = new Random().Next();
                }
                return "<br>Wartość sesji: " + HttpContext.Current.Session["ses"].ToString() + "</br>";
            }
        }

        public class PseudoItems
        {
            public static string a()
            {
                if (HttpContext.Current.Items["ses"] == null)
                {
                    HttpContext.Current.Items["ses"] = new Random().Next();
                }
                return "<br>Wartość items: " + HttpContext.Current.Items["ses"].ToString() + "</br>";
            }
        }
    }
}