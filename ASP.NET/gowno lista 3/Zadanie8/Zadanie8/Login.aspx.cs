using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Zadanie8
{
    public partial class Login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Page.IsPostBack)
            {
                if (login.Text == "user" && haslo.Text == "123")
                {
                    Session["user"] = "user";
                    Session["haslo"] = "123";
                    Response.Redirect(Session["site"] as string);
                    
                }
            }
        }
        protected void OnMove(object sender, EventArgs e)
        {
            if (login.Text == "user" && haslo.Text == "123")
            {
                Session["user"] = "user";
                Session["haslo"] = "123";
                bt.PostBackUrl = Session["site"] as string;
                Response.Redirect(Session["site"] as string);
            }
        }
    }
}