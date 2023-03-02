using DotNetOpenAuth.OAuth2;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Web;

namespace OAuth2Demo
{
    public class GoogleClient : WebServerClient
    {
        private static readonly AuthorizationServerDescription GoogleDescription =
            new AuthorizationServerDescription
            {
                TokenEndpoint         = new Uri("https://accounts.google.com/o/oauth2/token"),
                AuthorizationEndpoint = new Uri("https://accounts.google.com/o/oauth2/auth"),
                ProtocolVersion       = ProtocolVersion.V20,
            };

        public const string ProfileEndpoint = "https://openidconnect.googleapis.com/v1/userinfo";

        public const string OpenId       = "openid";
        public const string ProfileScope = "profile";
        public const string EmailScope   = "email";

        public GoogleClient()
            : base(GoogleDescription)
        {
        }
    }

    public class GoogleProfileAPI
    {
        public string email { get; set; }
        public string given_name { get; set; }
        public string family_name { get; set; }

        private static DataContractJsonSerializer jsonSerializer =
            new DataContractJsonSerializer(typeof(GoogleProfileAPI));

        public static GoogleProfileAPI Deserialize(Stream jsonStream)
        {
            try
            {
                if (jsonStream == null)
                {
                    throw new ArgumentNullException("jsonStream");
                }

                return (GoogleProfileAPI)jsonSerializer.ReadObject(jsonStream);
            }
            catch (Exception ex)
            {
                return new GoogleProfileAPI();
            }
        }
    }

    public class MyAuthorizationTracker : IClientAuthorizationTracker
    {

        public IAuthorizationState GetAuthorizationState(
            Uri callbackUrl,
            string clientState)
        {
            return new AuthorizationState
            {
                Callback = new Uri(callbackUrl.GetLeftPart(UriPartial.Path))
            };
        }

    }
}