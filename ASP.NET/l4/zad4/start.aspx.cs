using System;
using System.Collections.Generic;
using System.IdentityModel.Services;
using System.IdentityModel.Tokens;
using System.Linq;
using System.Security.Claims;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace zad4
{
    public partial class start : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            ClaimsPrincipal principal = this.User as ClaimsPrincipal;
            foreach (Claim claim in principal.Claims)
            {
                if(claim.Type == ClaimTypes.DateOfBirth && DateTime.Parse(claim.Value) < DateTime.UtcNow)
                {
                    Response.Redirect("https://google.com");
                }
            }
        }

        protected void aaaa_Click(object sender, EventArgs e)
        {
            var identity = new ClaimsIdentity("custom");
            identity.AddClaim(new Claim(ClaimTypes.Name, "a"));
            identity.AddClaim(new Claim(ClaimTypes.DateOfBirth, "01.01.1970"));
            SessionAuthenticationModule sam = FederatedAuthentication.SessionAuthenticationModule;
            var token = sam.CreateSessionSecurityToken(new ClaimsPrincipal(identity),
                                                       string.Empty,
                                                       DateTime.Now.ToUniversalTime(),
                                                       DateTime.Now.AddHours(1).ToUniversalTime(),
                                                       false);
            sam.WriteSessionTokenToCookie(token);
        }
    }
}