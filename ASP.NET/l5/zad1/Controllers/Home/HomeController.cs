using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace zad1.Controllers
{
    public class HomeController : Controller
    {
        [HttpGet]
        public ActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public ActionResult Index(string q)
        {
            string result = "Imię: " + Request.Form["imie"] + "<br/>";
            result += "Nazwisko: " + Request.Form["nazwisko"] + "<br/>"; 
            result += "Przedmiot: " + Request.Form["przedmiot"] + "<br/>"; 
            result += "Data: " + Request.Form["data"] + "<br/>";
            for(int i = 0; i < 10; i++)
            {
                string pkt = Request.Form[$"zad{i.ToString()}"];
                result += "Zad" + (i+1).ToString() + ": " + (pkt == "" ? "0" : pkt) + "<br/>";
            }
            return Content(result);
        }
    }
}