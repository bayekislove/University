using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace zad3.Controllers
{
    public class HomeController : Controller
    {
        // GET: Home
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult A()
        {
            return Content("A");
        }

        public ActionResult B()
        {
            return Content("B");
        }

        public ActionResult C()
        {
            return Content("C");
        }
    }
}