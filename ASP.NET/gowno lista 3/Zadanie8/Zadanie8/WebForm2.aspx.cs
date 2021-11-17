using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Zadanie8
{
    public partial class WebForm2 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["user"] == null)
            {
                if (Session["user"] as string == "user" && Session["haslo"] as string == "123")
                {

                }
                else
                {
                    Session["site"] = "WebForm2.aspx";
                    Response.Redirect("Login.aspx");
                }
            }
            else
            {
                Session["site"] = "WebForm2.aspx";
                Response.Redirect("Login.aspx");
            }
        }
    }
}