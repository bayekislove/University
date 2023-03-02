using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace zad2
{
    public partial class register : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void submit_Click(object sender, EventArgs e)
        {
            string toHash = passwodBox.Text + "nf9b3gf97oaedDH08H3";
            string hashedBytes;

            using (var hasher = MD5.Create())
            {
                var toHashBytes = Encoding.UTF8.GetBytes(toHash);
                for (int i = 0; i < 5; i++)
                {
                    toHashBytes = hasher.ComputeHash(toHashBytes);
                }
                hashedBytes = BitConverter.ToString(toHashBytes);
            }

            using(var context = new UsersDataContext())
            {
                context.USERs.InsertOnSubmit(new USER
                {
                    Salt = "nf9b3gf97oaedDH08H3",
                    Login = loginBox.Text,
                    PasswordShort = hashedBytes,
                    HashesNo = 5,
                    Email = emailBox.Text,
                    CreationDate = DateTime.Now
                });
                context.SubmitChanges();
            }
            Response.Redirect("./login.aspx");
        }
    }
}