using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace zad4
{
    public partial class start : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            //submitButton.Click += new EventHandler(submitClickRedirect);
            submitButton.Click += new EventHandler(submitClickSession);
        }

        private void prepareOutput()
        {
            for(int i = 1; i < 10; i++)
            {
                var control = (TextBox)FindControl("z" + i.ToString() + "Box");
                if (control.Text.Length == 0)
                    control.Text = "0";
            }
        }

        void submitClickRedirect(Object sender, EventArgs e)
        {
            prepareOutput();
            string redirectString = "/print.aspx?imie=" + NameField.Text + "&nazwisko=" + SurnameField.Text + "&data=" + DateField.Text + "&przedmiot=" + SubjectField.Text + "&numer=" + NoField.Text;
            for(int i = 1; i < 11; i++)
            {
                redirectString += "&z" + i.ToString() + "=" + ((TextBox)FindControl("z" + i.ToString() + "Box")).Text;
            }
            this.Response.Redirect(redirectString);
        }

        void submitClickSession(Object sender, EventArgs e)
        {
            prepareOutput();
            Session.Add("imie",NameField.Text);
            Session.Add("nazwisko", SurnameField.Text);
            Session.Add("data", DateField.Text);
            Session.Add("przedmiot", SubjectField.Text);
            Session.Add("numer", NoField.Text);

            for(int i = 1; i < 11; i++)
            {
                Session.Add("z" + i.ToString(), ((TextBox)FindControl("z" + i.ToString() + "Box")).Text);
            }
            Response.Redirect("/print.aspx");
        }
    }
}