using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace zad2
{
    public partial class start : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            //ustawianie ciastek
            HttpCookie a = new HttpCookie("a");
            a.Value = "b";
            a.Expires = DateTime.Now.AddMinutes(5);
            Response.SetCookie(a);

            //odczytywanie ciastek
            HttpCookie aRead = Request.Cookies["a"];

            //usuwanie ciastek
            a.Expires = DateTime.Now.AddMinutes(-30d);
            Response.SetCookie(a);
        }
    }
}