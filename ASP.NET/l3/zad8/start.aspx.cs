using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace zad8
{
    public partial class start : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(Session["login"] == null)
            {
                Session["start"] = "start.aspx";
                Response.Redirect("login.aspx");
            } else
            {
                potwierdzenie.Text = "Użytkownik zalogowany: " + Session["login"];
            }
        }
    }
}