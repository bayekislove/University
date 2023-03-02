using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication1.Controllers
{
    public class EditController : Controller
    {
        [HttpGet]
        public ActionResult Index()
        {
            using (var context = new KsiazkiDataContext())
            {
                var tab = context.Ksiazkis.Where(x => x.id == int.Parse(Request.QueryString[0])).First();
                return View(new { Author = tab.Autor, Title = tab.Tytul, PublicationYear = tab.Rwydania });
            }
        }

        [HttpPost]
        public ActionResult Index(string q)
        {
            string title = Request.Form["Title"];
            string author = Request.Form["Author"];
            int pYear = int.Parse(Request.Form["PublicationYear"] != "" ? Request.Form["PublicationYear"] : "-1");

            if (title == "" || author == "" || pYear == -1)
            {
                return View();
            }
            using (var context = new KsiazkiDataContext())
            {
                var tab = context.Ksiazkis.Where(x => x.id == int.Parse(Request.Form["id"])).First();
                tab.Rwydania = pYear;
                tab.Tytul = title;
                tab.Autor = author;
                context.SubmitChanges();
            }
            return Redirect("/");
        }
    }
}