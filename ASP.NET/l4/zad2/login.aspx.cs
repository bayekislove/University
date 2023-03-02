using System;
using System.Linq;
using System.Web;
using System.Web.Security;

namespace zad2
{
    public partial class login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
           
        }

        protected void redirectToRegister_Click(object sender, EventArgs e)
        {
            Response.Redirect("/register.aspx");
        }

        protected void submit_Click(object sender, EventArgs e)
        {
            if (new MyMembershipProvider().ValidateUser(loginBox.Text, passwodBox.Text))
            {
                FormsAuthenticationTicket ticket = new FormsAuthenticationTicket(1, loginBox.Text, DateTime.Now, DateTime.Now.AddMinutes(10), false, "");
                HttpCookie cookie = new HttpCookie(FormsAuthentication.FormsCookieName, FormsAuthentication.Encrypt(ticket));
                Response.AppendCookie(cookie);
                Response.Redirect("./start.aspx");
            }
            else
            {
                resultLabel.Text = "Błędna nazwa użytkownika lub hasło";
            }
        }
    }
}