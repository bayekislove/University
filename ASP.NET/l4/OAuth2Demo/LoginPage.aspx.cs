using DotNetOpenAuth.OAuth2;
using System;
using System.Collections.Generic;
using System.IdentityModel.Services;
using System.Linq;
using System.Net;
using System.Security.Claims;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace OAuth2Demo
{
    public partial class LoginPage : System.Web.UI.Page
    {
        public readonly GoogleClient gClient = new GoogleClient
        {
            AuthorizationTracker       = new MyAuthorizationTracker(),
            ClientIdentifier           = "poprawny_client_id",
            ClientCredentialApplicator = ClientCredentialApplicator.PostParameter("poprawny_client_secret")
        };

        protected void Page_Load(object sender, EventArgs e)
        {
            IAuthorizationState authorization = gClient.ProcessUserAuthorization();
            // Is this a response from the Identity Provider
            if (authorization == null)
            {
                // no

                // Google will redirect back here
                Uri uri = new Uri("http://localhost:52228/LoginPage.aspx");
                // Kick off authorization request with OAuth2 scopes
                gClient.RequestUserAuthorization(returnTo: uri,
                    scope: new[] { GoogleClient.OpenId, GoogleClient.ProfileScope, GoogleClient.EmailScope });
            }
            else
            {
                // yes

                var request = WebRequest.Create(GoogleClient.ProfileEndpoint);
                // add an OAuth2 authorization header
                // if you get 403 here, turn ON Google+ API on your app settings page
                request.Headers.Add(
                     HttpRequestHeader.Authorization,
                     string.Format("Bearer {0}", Uri.EscapeDataString(authorization.AccessToken)));
                // Go to the profile API
                using (var response = request.GetResponse())
                {
                    using (var responseStream = response.GetResponseStream())
                    {
                        var profile = GoogleProfileAPI.Deserialize(responseStream);
                        if (profile != null &&
                            !string.IsNullOrEmpty(profile.email))
                        {
                            // forms authentication
                            // FormsAuthentication.RedirectFromLoginPage(profile.email, false);

                            // session authentication
                            var identity = new ClaimsIdentity("custom");
                            identity.AddClaim(new Claim(ClaimTypes.Name, profile.email));

                            var principal = new ClaimsPrincipal(identity);

                            SessionAuthenticationModule sam = FederatedAuthentication.SessionAuthenticationModule;
                            var token =
                                sam.CreateSessionSecurityToken(principal, string.Empty,
                                     DateTime.Now.ToUniversalTime(), DateTime.Now.AddMinutes(20).ToUniversalTime(), false);

                            sam.WriteSessionTokenToCookie(token);

                            // przekierowanie
                            string ReturnUrl =
                                !string.IsNullOrEmpty(this.Request.QueryString["ReturnUrl"])
                                ? this.Request.QueryString["ReturnUrl"]
                                : FormsAuthentication.DefaultUrl;

                            this.Response.Redirect(ReturnUrl);
                        }
                    }
                }
            }
        }
    }
}