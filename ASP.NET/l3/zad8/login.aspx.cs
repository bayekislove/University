using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace zad8
{
    public partial class login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["login"] != null)
            {
                Response.Redirect("start.aspx");
            }
        }

        protected void Validate(object sender, EventArgs e)
        {
            if(pwd.Text == "admin")
            {
                Session["login"] = lgn.Text;
                Response.Redirect(Session["start"].ToString());
            }
            else
            {
                result.Text = "Jeszcze raz";
                lgn.Text = "";
                pwd.Text = "";
            }
        }
    }
}