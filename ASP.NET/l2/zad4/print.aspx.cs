using System;

namespace zad4
{
    public partial class print : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            //PreparePrintRedirect();
            PreparePrintSession();
        }

        private void PreparePrintRedirect()
        {
            var query = Request.QueryString;
            foreach (var q in query.AllKeys)
            {
                Print.Text += q + ": " + query[q] + "<br />";
            }
        }

        private void PreparePrintSession()
        {
            for(int i = 0; i < Session.Count; i++)
            { 
                Print.Text += Session.Keys[i] + ":" + Session[Session.Keys[i]] + "<br />";
            }
        }
    }
}