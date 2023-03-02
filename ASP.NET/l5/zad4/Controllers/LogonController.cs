using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Security;
using zad4.Models;

namespace zad4.Controllers
{
    public class LogonController : Controller
    {
        // GET: Logon
        [HttpGet]
        public ActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Index(User model)
        {
            if( model.username != "" && new MyMembershipProvider().ValidateUser(model.username, model.password))
            {
                FormsAuthenticationTicket ticket = new FormsAuthenticationTicket(1, model.username, DateTime.Now, DateTime.Now.AddMinutes(10), false, "");
                HttpCookie cookie = new HttpCookie(FormsAuthentication.FormsCookieName, FormsAuthentication.Encrypt(ticket));
                Response.AppendCookie(cookie);
                return RedirectToAction("Index", "Home");
            }
            return View();
        }
    }
}